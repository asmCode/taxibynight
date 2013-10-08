#pragma once

class IBullet;

class IGun
{
public:
	virtual void PullTrigger() = 0;
	virtual void ReleaseTrigger() = 0;

	virtual void Update(float time, float seconds) = 0;
	virtual void Draw(float time, float seconds) = 0;

	/**
	 * Return NULL if no shot occured at the moment, and IBullet otherwise.
	 * Should be called right after Update().
	**/
	virtual IBullet* GetBullet() const = 0;
};

