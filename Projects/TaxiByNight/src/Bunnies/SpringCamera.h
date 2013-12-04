#ifndef SPRINGCAMERA_H_
#define SPRINGCAMERA_H_

#include "Camera.h"
#include <Math/Vec3.h>

namespace sm
{

class SpringCamera : public Camera
{
public:
	SpringCamera();

	void SetDestinationPosition(const Vec3& position);
	void SetDestinationLookDirection(const Vec3& direction);

	void Update(float seconds);

private:
	Vec3 m_destinationPosition;
	Vec3 m_destinationDirection;
};

} /* namespace sm */
#endif /* SPRINGCAMERA_H_ */
