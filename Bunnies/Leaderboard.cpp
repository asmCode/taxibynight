#include "Leaderboard.h"
#include "HttpCommunication.h"
#include "ILeaderboardObserver.h"
#include <Utils/StringUtils.h>
#include <Utils/Log.h>
#include <Math/MathUtils.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <math.h>
#include <stdio.h>

Leaderboard* Leaderboard::m_instance;
const std::string Leaderboard::HostAddress = "http://semiseriousgames.com";
const std::string Leaderboard::AddUserAddress = "http://semiseriousgames.com/taxibynight/server/ladder/Points.php?id=%d&n=%s&r=%s&c=%d";
const std::string Leaderboard::TopAddress = "http://semiseriousgames.com/taxibynight/server/ladder/LadderTop.php?l=%d";
const std::string Leaderboard::UserSurroundingAddress = "http://semiseriousgames.com/taxibynight/server/ladder/LadderSurr.php?r=%s&l=%d";

Leaderboard::Leaderboard()
{
	m_httpUser = new HttpCommunication(HostAddress);
	m_httpTop = new HttpCommunication(HostAddress);
	m_httpSurr = new HttpCommunication(HostAddress);

	m_httpUser->AddObserver(this);
	m_httpTop->AddObserver(this);
	m_httpSurr->AddObserver(this);
}

Leaderboard::~Leaderboard()
{
}

Leaderboard* Leaderboard::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new Leaderboard();

	return m_instance;
}

void Leaderboard::AddObserver(ILeaderboardObserver* observer)
{
	m_observers.push_back(observer);
}

void Leaderboard::RefreshTopLadder()
{
	if (m_httpTop->IsBusy())
		return;

	char request[2048];
	sprintf(request, TopAddress.c_str(), TopCount);

	m_httpTop->SendRequest(request);
}

void Leaderboard::RefreshSurrLadder(float playerReward)
{
	if (m_httpSurr->IsBusy())
		return;

	char request[2048];
	sprintf(request, UserSurroundingAddress.c_str(), StringUtils::ToBase64(StringUtils::ToString(playerReward)).c_str(), SurrCount);

	m_httpSurr->SendRequest(request);
}

void Leaderboard::SendPlayerPoints(int id, const std::string& playerName, float reward, int courses)
{
	if (m_httpUser->IsBusy())
		return;

	char request[2048];
	sprintf(request, AddUserAddress.c_str(), id, StringUtils::ToBase64(playerName).c_str(), StringUtils::ToBase64(StringUtils::ToString(reward)).c_str(), courses);

	Log::LogT("request: %s", request);

	m_httpUser->SendRequest(request);
}

const std::vector<PlayerStats>& Leaderboard::GetTopLadder() const
{
	return m_topStats;
}

const std::vector<PlayerStats>& Leaderboard::GetPlayerLadder() const
{
	return m_surrStats;
}

void Leaderboard::Timeount()
{
	for (unsigned int i = 0; i < m_observers.size(); i++)
		m_observers[i]->LeaderOffline();
}

void Leaderboard::Response(HttpCommunication* http, int httpCode, const std::string& data)
{
	if (httpCode != 200)
	{
		Log::LogT("Error http response %d", httpCode);
		return;
	}

	XMLNode *node = XMLLoader::LoadFromString(data);
	if (node == NULL)
	{
		Log::LogT("Couldn't parse http response");
		return;
	}

	if (!node->HasAttrib("result"))
	{
		Log::LogT("Wrong http response format");
		return;
	}

	if (node->GetAttribAsInt32("result") != 0)
	{
		Log::LogT("Http response error");
		return;
	}

	if (http == m_httpTop)
		ProcessTopResponse(node);
	else if (http == m_httpSurr)
		ProcessSurrResponse(node);
	else if (http == m_httpUser)
		ProcessUserResponse(node);
}

void Leaderboard::ProcessTopResponse(XMLNode* node)
{
	m_topStats.clear();

	FetchArrayFromRasult(m_topStats, node, 1);

	for (unsigned int i = 0; i < m_observers.size(); i++)
		m_observers[i]->LeaderTopLoaded();
}

void Leaderboard::ProcessSurrResponse(XMLNode* node)
{
	m_surrStats.clear();

	int rank = 0;
	if (node->HasAttrib("rank"))
		rank = node->GetAttribAsInt32("rank");

	FetchArrayFromRasult(m_surrStats, node, rank);

	for (unsigned int i = 0; i < m_observers.size(); i++)
		m_observers[i]->LeaderPlayerLoaded();
}

void Leaderboard::ProcessUserResponse(XMLNode* node)
{
	int userId = 0;

	if (node->GetChildrenCount() == 1)
	{
		XMLNode* child = node->GetChild(0);
		if (child->GetName() == "user" && child->HasAttrib("id"))
			userId = child->GetAttribAsInt32("id");
	}

	for (unsigned int i = 0; i < m_observers.size(); i++)
		m_observers[i]->PointsUpdated(userId);
}

void Leaderboard::FetchArrayFromRasult(std::vector<PlayerStats>& array, XMLNode* node, int rank)
{
	for (unsigned int i = 0; i < MathUtils::Min((int)node->GetChildrenCount(), 10); i++)
	{
		XMLNode* child = node->GetChild(i);
		if (child == NULL)
			continue;

		PlayerStats stats;

		if (child->HasAttrib("i"))
			stats.m_id = child->GetAttribAsInt32("i");
		if (child->HasAttrib("n"))
		{
			std::string name = child->GetAttribAsString("n");

			stats.m_name = StringUtils::FromBase64(name);
		}
		if (child->HasAttrib("r"))
			stats.m_reward = child->GetAttribAsFloat("r");
		if (child->HasAttrib("c"))
			stats.m_courses = child->GetAttribAsInt32("c");

		stats.m_place = rank++;

		array.push_back(stats);
	}
}
