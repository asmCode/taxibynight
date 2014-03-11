#include <windows.h>

#include <gl\gl.h>
#include <gl\glu.h>

#include "OpenglWindow.h"
#include "../Bunnies/ISystemUtils.h"

#include "Input.h"

#include <fstream>

class Renderer : public IInputObserver, public ISystemUtils
{
private:
	OpenglWindow *glwnd;
	
	Input *input;

	float scale;

	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	void MouseMove(int x, int y, int xShift, int yShift);

	void QuitApplication();

public:
	Renderer(OpenglWindow *glwnd);

	void Initialize();

	void Update(float time, float seconds);
	void Render(float time, float seconds);
};

