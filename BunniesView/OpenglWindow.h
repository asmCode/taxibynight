#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

class OpenglWindow
{
private:
	HWND hwnd;
	HWND parentWindow;

	int windowWidth;
	int windowHeight;

	HDC hdc;
	HGLRC hrc;

	bool fullscreen;
	bool createOwnWindow;

public:
	OpenglWindow(void);
	~OpenglWindow(void);

	bool Initialize(HWND parent, const char * title, int width, int height,
		int bpp, int freq, bool fullscreen, bool createOwnWindow, void *params);
	void Release();

	void Resize(int width, int height);
	int GetWindowWidth();
	int GetWindowHeight();

	void SetCurrentContext();
	void SwapBuffers();

	HDC GetHDC();
	HWND GetHwnd();
};
