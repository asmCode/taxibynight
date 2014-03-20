#include "ScreenKeyboard.h"
#include "IScreenKeyboardObserver.h"
#include <Utils/StringUtils.h>

ScreenKeyboard* ScreenKeyboard::m_instance;

ScreenKeyboard::ScreenKeyboard() :
	m_observer(NULL)
{
}

ScreenKeyboard::~ScreenKeyboard()
{
}

ScreenKeyboard* ScreenKeyboard::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new ScreenKeyboard();
	}

	return m_instance;
}

void ScreenKeyboard::SetObserver(IScreenKeyboardObserver* observer)
{
	m_observer = observer;
}

void ScreenKeyboard::Show()
{
}

void ScreenKeyboard::Hide()
{
	// well, there is no hide
}

std::string ScreenKeyboard::GetText()
{
	return "majak";
}

void ScreenKeyboard::SetText(const std::string& text)
{
}
