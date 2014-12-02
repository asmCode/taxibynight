#pragma once

class IGaragePanel
{
public:
	virtual void Enter() {}
	virtual void Leave() {}
	virtual void SetActive(bool active) {}
};
