#pragma once

#include "IScreen.h"
#include <Math/Matrix.h>

class IShapesRenderer;
class Street;
class ManCam;
class Taxi;
class PedsManager;
class Arrow;
class PlaceIndicator;

class GameScreen : public IScreen
{
public:
	GameScreen(void);
	~GameScreen(void);

	bool Initialize();

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandlePress(uint32_t pointIndex, const sm::Vec2 &point);
    void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleMove(uint32_t pointIndex, const sm::Vec2 &point);

private:
	Street *m_street;
	Taxi *m_taxi;
	PedsManager *m_pedsManager;
	Arrow *m_arrow;
	PlaceIndicator *m_placeIndicator;

	sm::Matrix m_viewMatrix;
	sm::Matrix m_projMatrix;

	ManCam *m_manCam;

	void SimulatePress();

	void TurnLeftButtonPressed();
	void TurnRightButtonPressed();
	void AccelerationButtonPressed();
};

