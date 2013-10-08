#include "Shapes.h"

#include <Math\Vec2.h>
#include <Windows.h>
#include <gl\GL.h>

void Shapes::DrawCircle(const sm::Vec2 &position,
						float radius,
						const sm::Vec3 &color)
{
	glColor3f(color.x, color.y, color.z);

	float step = 360.0f / 16.0f;

	sm::Vec2 radiusVector(radius, 0);

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(position.x, position.y);

	for (float radius = 0.0f; radius <= 360.0f; radius += step)
	{
		glVertex2f(radiusVector.x + position.x, radiusVector.y + position.y);
		
		radiusVector.Rotate(rad(step));
	}

	glEnd();
}

