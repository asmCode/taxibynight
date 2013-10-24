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
#include <Utils/StringUtils.h>
#include <Graphics/TexPart.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/Content/Content.h>
#include <Utils/Log.h>
//#include "MessageBox.h"
//#include "SoundManager.h"

SummaryPanel::SummaryPanel() :
	Control("SummaryPanel")
{
	SetFill(true);
}

SummaryPanel *SummaryPanel::Create(GameScreen *gameScreen)
{	
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();
	SummaryPanel *ret = new SummaryPanel();

	Control *content = Inflater::Inflate(basePath + "data/gui/SummaryPanel.xml");

	ret->AddChild(content);
	
	ret->m_earnLabel = dynamic_cast<Label*>(ret->FindChild("earn_value"));
	assert(ret->m_earnLabel != NULL);
	ret->m_coursesLabel = dynamic_cast<Label*>(ret->FindChild("courses_value"));
	assert(ret->m_coursesLabel != NULL);
	ret->m_totalEarnLabel = dynamic_cast<Label*>(ret->FindChild("total_money_value"));
	assert(ret->m_totalEarnLabel != NULL);
	ret->m_totalCoursesLabel = dynamic_cast<Label*>(ret->FindChild("total_courses_value"));
	assert(ret->m_totalCoursesLabel != NULL);

	return ret;
}

void SummaryPanel::Clicked(Control *control, uint32_t x, uint32_t y)
{
}

void SummaryPanel::OnDraw(float time, float seconds)
{
	this->Control::OnDraw(time, seconds);
}

void SummaryPanel::SetContent(
		float earn,
		int courses,
		float totalEarn,
		int totalCourses)
{
	m_earnLabel->SetText(StringUtils::ToString(earn));
	m_coursesLabel->SetText(StringUtils::ToString(courses));
	m_totalEarnLabel->SetText(StringUtils::ToString(totalEarn));
	m_totalCoursesLabel->SetText(StringUtils::ToString(totalCourses));
	//bool m_record;
}
