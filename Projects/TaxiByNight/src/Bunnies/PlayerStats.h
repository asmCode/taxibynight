#ifndef PLAYERSTATS_H_
#define PLAYERSTATS_H_

#include <string>

class PlayerStats
{
public:
	PlayerStats() :
		m_id(0),
		m_place(0),
		m_reward(0),
		m_courses(0)
	{

	}

	int m_id;
	int m_place;
	std::string m_name;
	int m_reward;
	int m_courses;
};


#endif /* PLAYERSTATS_H_ */
