#pragma once

class Car;
class Model;

class TrafficManager
{
public:
	TrafficManager();
	~TrafficManager();

	bool Initialize();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

private:
	static const int MaxCars = 10;

	Car* m_cars[MaxCars];

	Model *m_carModel;
};

