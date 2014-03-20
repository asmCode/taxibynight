#ifndef SCREENKEYBOARD_H_
#define SCREENKEYBOARD_H_

#include <string>

class IScreenKeyboardObserver;

class ScreenKeyboard
{
public:
	virtual ~ScreenKeyboard();

	static ScreenKeyboard* GetInstance();

	void Show();
	void Hide();

	std::string GetText();
	void SetText(const std::string& text);
	void SetObserver(IScreenKeyboardObserver* observer);

private:
	static ScreenKeyboard* m_instance;

	IScreenKeyboardObserver* m_observer;

	ScreenKeyboard();
};

#endif /* SCREENKEYBOARD_H_ */
