#include "SummaryPanel.h"
#include "Environment.h"
#include "InterfaceProvider.h"
#include "AnimButton.h"
#include "Label.h"
#include "SpritesMap.h"
#include "GameScreen.h"
#include "Taxi.h"
#include "GameController.h"
#include "Inflater.h"
#include <Graphics/TexPart.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/Content/Content.h>
#include <Utils/Log.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
//#include "MessageBox.h"
//#include "SoundManager.h"

SummaryPanel::SummaryPanel() :
	Control("SummaryPanel")
{
}

SummaryPanel *SummaryPanel::Create(GameScreen *gameScreen)
{	
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();
	SummaryPanel *ret = new SummaryPanel();

	Control *content = Inflater::Inflate(basePath + "data/gui/SummaryPanel.xml");

	ret->AddChild(content);
	
	/*ret->m_totalMoneyLabel = dynamic_cast<Label*>(ret->FindChild("total_money_value"));
	assert(ret->m_totalMoneyLabel != NULL);
	ret->m_totalCoursesLabel = dynamic_cast<Label*>(ret->FindChild("total_courses_value"));
	assert(ret->m_totalCoursesLabel != NULL);
	ret->m_rewardLabel = dynamic_cast<Label*>(ret->FindChild("reward_value"));
	assert(ret->m_rewardLabel != NULL);
	ret->m_timeLeftLabel = dynamic_cast<Label*>(ret->FindChild("time_left_value"));
	assert(ret->m_timeLeftLabel != NULL);*/
	
	return ret;
}

void SummaryPanel::Clicked(Control *control, uint32_t x, uint32_t y)
{
}

void SummaryPanel::OnDraw(float time, float seconds)
{
	this->Control::OnDraw(time, seconds);
}
