#include <windows.h>

#include <GL/glew.h>
#include "OpenglWindow.h"
#include "TimeControl.h"
#include "Renderer.h"
#include <stdio.h>
#include <assert.h>

bool GlobalDone;

#if 0
// iPod Touch 4
int ScreenWidth = 960;
int ScreenHeight = 640;
#endif

#if 0
// galaxy S II
int ScreenWidth = 800;
int ScreenHeight = 480;
#endif

#if 0
// galaxy S III
int ScreenWidth = 1280;
int ScreenHeight = 720;
#endif

#if 0
int ScreenWidth = 1024;
int ScreenHeight = 600;
#endif

#if 1
int ScreenWidth = 1280;
int ScreenHeight = 720;
#endif

OpenglWindow *glwnd;
Renderer *renderer;

void APIENTRY OpenglDebugCallback(
	  GLenum source,
	  GLenum type,
	  GLuint id,
	  GLenum severity,
	  GLsizei length,
	  const GLchar* message,
	  void* userParam)
 {
	 int houston = 0;
 }

bool InitGl()
{
	if (glewInit() != GLEW_OK)
	{
		assert(false);
	}

	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	if (versionMajor < 2)
	{
		MessageBoxA(NULL, "You need Opengl 2.0 or higher", "Wrong opengl version", MB_ICONWARNING);
		return false;
	}

#if 0
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenglDebugCallback, NULL);
#endif

	glViewport(0, 0, ScreenWidth, ScreenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0f, 1024.0f / 768, 1.0f, 1000.0f);
	//gluOrtho2D(0, 1024, 760, 0);
	gluOrtho2D(-50, 50, 50, -50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_NORMALIZE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glDisable(GL_LIGHTING);

	return true;
}

HWND hwnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	TimeControl *tc = new TimeControl();

	tc ->Start();
	float time = 0;

	MSG msg;
	BOOL done = false;

	glwnd = new OpenglWindow();
	glwnd ->SetCurrentContext();
	glwnd ->Initialize(NULL, "Taxi by Night", ScreenWidth, ScreenHeight, 32, 0, false, true, NULL);

	if (!InitGl())
		return 0;

	renderer = new Renderer(glwnd);
	renderer ->Initialize();

	while (!GlobalDone)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			float seconds = tc ->CheckFrameMS() / 1000.0f;
			time += seconds;

			renderer->Update(time, seconds);
			renderer ->Render(time, seconds);
		}
	}

	return (int)(msg.wParam);
}

