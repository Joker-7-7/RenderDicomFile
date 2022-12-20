#include "GraphicPrimitives.h"

namespace GraphicPrimitives
{
	Point3D operator + (const Point3D& a, const Point3D& b)
	{
		return {a.x + b.x, a.y + b.y, a.z + b.z};
	}

	Point3D operator - (const Point3D& a, const Point3D& b)
	{
		return {a.x - b.x, a.y - b.y, a.z - b.z};
	}
}
