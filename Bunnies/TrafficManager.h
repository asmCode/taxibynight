#pragma once

class Car;
class Model;
class StreetSegment;

class TrafficManager
{
public:
	TrafficManager();
	~TrafficManager();

	bool Initialize();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void NotifyStreetSegmentVisibilityChanged(StreetSegment *streetSegment);

private:
	static const int MaxCars = 10;

	Car* m_cars[MaxCars];

	Model *m_carModel;

	bool IsOnVisibleSegment(Car *car);
};

