#ifndef _SHAPES_RENDERER_
#define _SHAPES_RENDERER_

#include <Core/GenericSingleton.h>

class HealthyBunny;
class InfectedBunny;
class Player;

class IShapesRenderer
{
public:
	virtual void DrawHealthyBunny(HealthyBunny *healthyBunny) = 0;
	virtual void DrawInfectedBunny(InfectedBunny *infectedBunny) = 0;
	virtual void DrawPlayer(Player *player) = 0;
};

#endif

