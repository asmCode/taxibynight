#include "LeaderboardScreen.h"
#include "SummaryPanel.h"
#include "InterfaceProvider.h"
#include "GameProps.h"
#include "GameController.h"
#include "Leaderboard.h"
#include "Inflater.h"
#include "Environment.h"
#include "Control.h"
#include "Label.h"
#include "Player.h"
#include "ScreenKeyboard.h"
#include <Utils/Log.h>
#include <Graphics/Content/Content.h>
#include <Graphics/SpriteBatch.h>
#include <Audio/SoundManager.h>
#include <stdio.h>
#include <assert.h>

LeaderboardScreen::LeaderboardScreen(GameController *gameController) :
	m_gameController(gameController),
	m_leaderboardPanel(NULL),
	m_currentTab(LeaderboardScreen::Tab_Top)
{
}

LeaderboardScreen::~LeaderboardScreen(void)
{
}

bool LeaderboardScreen::InitResources()
{
	m_leaderboardPanel = Inflater::Inflate(TaxiGame::Environment::GetInstance()->GetBasePath() + "data/gui/LeaderboardPanel.xml");

	if (m_leaderboardPanel == NULL)
	{
		assert(false);
		return false;
	}

	m_changeNameButton = m_leaderboardPanel->FindChild("change_name");
	m_backButton = m_leaderboardPanel->FindChild("back");
	m_refreshButton = m_leaderboardPanel->FindChild("refresh");
	m_playerNameLabel = dynamic_cast<Label*>(m_leaderboardPanel->FindChild("player_name"));

	assert(m_changeNameButton != NULL);
	assert(m_backButton != NULL);
	assert(m_refreshButton != NULL);
	assert(m_playerNameLabel != NULL);

	ObsCast(IControlEventsObserver, m_changeNameButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_backButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_refreshButton)->AddObserver(this);

	m_playerNameLabel->SetText(Player::Instance->m_name);

	Leaderboard::GetInstance()->AddObserver(this);
	ScreenKeyboard::GetInstance()->SetObserver(this);

	return true;
}

bool LeaderboardScreen::ReleaseResources()
{
	if (m_leaderboardPanel != NULL)
		delete m_leaderboardPanel;

	return true;
}

void LeaderboardScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_leaderboardPanel->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void LeaderboardScreen::Update(float time, float seconds)
{
	m_leaderboardPanel->Update(time, seconds);
}

void LeaderboardScreen::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_leaderboardPanel->HandlePress(pointId, point);
}

void LeaderboardScreen::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_leaderboardPanel->HandleRelease(pointId, point);
}

void LeaderboardScreen::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_leaderboardPanel->HandleMove(pointId, point);
}

void LeaderboardScreen::Enter()
{
	RefreshCurrentView();
}

void LeaderboardScreen::LeaderOffline()
{

}

void LeaderboardScreen::LeaderTopLoaded()
{
	SetPlayerStats(Leaderboard::GetInstance()->GetTopLadder());
}

void LeaderboardScreen::LeaderPlayerLoaded()
{
	SetPlayerStats(Leaderboard::GetInstance()->GetPlayerLadder());
}

void LeaderboardScreen::PointsUpdated(int playerId)
{
//	m_youTab->SetVisible(true);
//	m_topTab->SetVisible(true);
//	m_leaderboard->SetOnline();

	Player* p = Player::Instance;

	if (p->m_id != playerId && playerId != 0)
	{
		p->m_id = playerId;
		p->Save();
	}
}

void LeaderboardScreen::SetTab(LeaderboardScreen::Tab tab)
{
	m_currentTab = tab;
}

void LeaderboardScreen::RefreshCurrentView()
{
	if (m_currentTab == Tab_Top)
		Leaderboard::GetInstance()->RefreshTopLadder();
	else if (m_currentTab == Tab_You)
		Leaderboard::GetInstance()->RefreshSurrLadder(Player::Instance->m_totalMoney);
}

void LeaderboardScreen::ClearTable()
{
	for (unsigned int i = 0; i < m_tableLabels.size(); i++)
	{
		m_leaderboardPanel->RemoveChild(m_tableLabels[i]);
		delete m_tableLabels[i];
	}

	m_tableLabels.clear();
}

void LeaderboardScreen::SetPlayerStats(const std::vector<PlayerStats>& playerStats)
{
	ClearTable();

	FontRenderer *font = InterfaceProvider::GetFontRenderer("fenix_18");

	int yBase = 80;

	for (unsigned int i = 0; i < playerStats.size(); i++)
	{
		Color color = Color::White;

		if (playerStats[i].m_id != 0 &&
			playerStats[i].m_id == Player::Instance->m_id)
			color = Color(234, 60, 7);

		int yPos = yBase + i * RowHeight;

		char numberStr[32];

		sprintf(numberStr, "%d", playerStats[i].m_place);
		Label* placeLabel = new Label("", numberStr, font, 1.0f, color, PlaceColumnShift, yPos);

		Label* nameLabel = new Label("", playerStats[i].m_name, font, 1.0f, color, NameColumnShift, yPos);

		sprintf(numberStr, "%d", playerStats[i].m_reward);
		Label* pointsLabel = new Label("", numberStr, font, 1.0f, color, PointsColumnShift, yPos);

		sprintf(numberStr, "%d", playerStats[i].m_courses);
		Label* levelsLabel = new Label("", numberStr, font, 1.0f, color, LevelColumnShift, yPos);

		m_leaderboardPanel->AddChild(placeLabel);
		m_leaderboardPanel->AddChild(nameLabel);
		m_leaderboardPanel->AddChild(pointsLabel);
		m_leaderboardPanel->AddChild(levelsLabel);

		m_tableLabels.push_back(placeLabel);
		m_tableLabels.push_back(nameLabel);
		m_tableLabels.push_back(pointsLabel);
		m_tableLabels.push_back(levelsLabel);
	}
}

void LeaderboardScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_backButton)
	{
		m_gameController->ShowMainMenuScreen();
	}
	else if (control == m_refreshButton)
	{
		RefreshCurrentView();
	}
	else if (control == m_changeNameButton)
	{
		ScreenKeyboard::GetInstance()->SetText(Player::Instance->m_name);
		ScreenKeyboard::GetInstance()->Show();
	}
}

void LeaderboardScreen::ScreenKeyboardDone(const std::string& text)
{
	std::string text2 = text;

	if (text2.size() > 18)
		text2 = text2.substr(0, 18);

	//if (PlayerData::GetInstance()->m_name != text2)
	{
		Log::LogT("Updating player name (%s)", text2.c_str());

		Player::Instance->m_name = text2;
		Player::Instance->Save();

		int playerId = Player::Instance->m_id;
		std::string playerName = Player::Instance->m_name;
		float reward = Player::Instance->m_totalMoney;
		int courses = Player::Instance->m_totalCourses;

		Leaderboard::GetInstance()->SendPlayerPoints(
			playerId,
			playerName,
			reward,
			courses);

		m_playerNameLabel->SetText(playerName);
	}
}

void LeaderboardScreen::ScreenKeyboardCanceled()
{

}