#include "Control.h"
#include <assert.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/TexPart.h>
#include <Graphics/Color.h>

SpriteBatch *Control::spriteBatch;

void Control::SetSpriteBatch(SpriteBatch *spriteBatch)
{
	Control::spriteBatch = spriteBatch;
}

Control::Control(const std::string &name) :
	m_name(name)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	opacity = 1.0f;
	
	parent		= NULL;
	visible		= true;
	enabled		= true;
}

Control::Control(const std::string &name, int x, int y, int width, int height) :
	m_name(name)
{
	this ->x = x;
	this ->y = y;
	this ->width = width;
	this ->height = height;
	opacity = 1.0f;
	
	parent		= NULL;
	visible		= true;
	enabled		= true;
}

Control::Control(const std::string &name, int x, int y, const TexPart &bg) :
	m_name(name)
{
	this ->x = x;
	this ->y = y;
	this ->width = bg.ImageRect.Width;
	this ->height = bg.ImageRect.Height;
	opacity = 1.0f;
	
	parent = NULL;
	visible = true;
	enabled		= true;
	this ->bg = bg;
}

Control::Control(const std::string &name, int x, int y, int width, int height, const TexPart &bg) :
	m_name(name)
{
	this ->x = x;
	this ->y = y;
	this ->width = width;
	this ->height = height;
	opacity = 1.0f;
	
	parent = NULL;
	visible = true;
	enabled		= true;
	this ->bg = bg;
}

Control::~Control()
{
	std::map<std::string, unsigned char*>::iterator it;
	for (it = userData.begin(); it != userData.end(); it++)
		delete [] it ->second;
}

Control *Control::GetParent()
{
	return parent;
}

void Control::AddChild(Control *control)
{
	if (control ->GetParent() != NULL)
	{
		assert(false && "Control is child of other parent");
		return;
	}

	control ->parent = this;
	children.push_back(control);
}

void Control::SetX(int x)
{
	this->x = x;
}

void Control::SetY(int y)
{
	this->y = y;
}

void Control::SetPosition(int x, int y)
{
	this ->x = x;
	this ->y = y;
}

void Control::SetSize(int width, int height)
{
	this ->width = width;
	this ->height = height;
}

void Control::SetBounds(int x, int y, int width, int height)
{
	SetPosition(x, y);
	SetSize(width, height);
}

sm::Vec2 Control::GetLocalPos()
{
	return sm::Vec2(x, y);
}

sm::Vec2 Control::GetGlobalPos()
{
	sm::Vec2 pos(x, y);
	if (parent != NULL)
		pos += parent ->GetLocalPos();
	return pos;
}

std::string Control::GetName() const
{
	return m_name;
}

void Control::HandleTapGesture(const sm::Vec2 &point)
{
	if (!visible || !enabled)
		return;
	
	std::list<Control*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		(*it) ->HandleTapGesture(sm::Vec2(point.x - this->x, point.y - this->y));
	
	if (HitTest(point.x, point.y))
	{
		OnTouch(point.x - this->x, point.y - this->y);
	}
}

void Control::HandlePanGesture(IGestureHandler::GestureStatus status,
							   const sm::Vec2 &pos,
							   const sm::Vec2 &trans,
							   const sm::Vec2 &velocity)
{
	if (!visible || !enabled)
		return;

	std::list<Control*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		(*it) ->HandlePanGesture(status, pos, trans, velocity);
}


void Control::HandlePress(const sm::Point<int> &point)
{
	if (!visible || !enabled)
		return;

	std::list<Control*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		(*it) ->HandlePress(sm::Point<int>(point.X - this->x, point.Y - this->y));
	
	if (HitTest(point.X, point.Y))
	{
		OnTouchBegin(point.X - this->x, point.Y - this->y);
	}
}

void Control::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
	if (!visible || !enabled)
		return;

	std::list<Control*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		(*it) ->HandleRelease(pointIndex, sm::Vec2(point.x - this->x, point.y - this->y));
	
	if (HitTest(point.x, point.x))
	{
		OnTouchEnd(point.x - this->x, point.y - this->y);
		OnTouch(point.x - this->x, point.y - this->y);
	}
}

bool Control::HitTest(int x, int y) const
{
	return
		(x >= this ->x && x < this ->x + width) &&
		(y >= this ->y && y < this ->y + height);
}

void Control::Update(float time, float ms)
{	
	OnUpdate(time, ms);
	
	std::list<Control*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		(*it) ->Update(time, ms);
}

void Control::Draw(float time, float ms)
{
	assert(spriteBatch != NULL);

	if (!visible)
		return;
	
	OnDraw(time, ms);
	
	std::list<Control*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		(*it) ->Draw(time, ms);	
}

void Control::OnTouch(int x, int y)
{
	ObsCast(IControlEventsObserver, this)->NotifyObservers(&IControlEventsObserver::Clicked, this, x, y);
}

void Control::OnTouchBegin(int x, int y)
{
}

void Control::OnTouchEnd(int x, int y)
{
}

void Control::OnDraw(float time, float ms)
{
	if (bg.Tex != NULL)
	{
		sm::Vec2 globalPos = GetGlobalPos();
		spriteBatch ->Draw(bg,
						   Color(255, 255, 255, (unsigned char)(255.0f * opacity)),
						   (int)globalPos.x,
						   (int)globalPos.y,
						   width,
						   height);
	}
}

void Control::OnUpdate(float time, float ms)
{
}

int Control::GetX() const
{
	return x;
}

int Control::GetY() const
{
	return y;
}

int Control::GetWidth() const
{
	return width;
}

int Control::GetHeight() const
{
	return height;
}

void Control::SetVisible(bool visible)
{
	this->visible = visible;
}

void Control::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool Control::IsVisible() const
{
	return visible;
}

bool Control::IsEnabled() const
{
	return enabled;
}

float Control::GetOpacity() const
{
	return opacity;
}

void Control::SetOpacity(float opacity)
{
	this->opacity = opacity;
}

