#ifndef GRAPHICPRIMITIVES_H
#define GRAPHICPRIMITIVES_H

#include <cmath>

namespace GraphicPrimitives
{
	class Point3D
	{
	public:
		double x;
		double y;
		double z;

		Point3D() : x(0.0), y(0.0), z(0.0)
		{}

		Point3D(const double x, const  double y,const double z) : x(x), y(y), z(z)
		{}

		explicit Point3D(const double* value) : x(value[0]), y(value[1]), z(value[2])
		{}

		Point3D(const Point3D& point)
		{
			x = point.x;
			y = point.y;
			z = point.z;
		}

		Point3D(Point3D&& point) noexcept
		{
			x = point.x;
			y = point.y;
			z = point.z;

			point.x = 0.0;
			point.y = 0.0;
			point.z = 0.0;
		}

		void round()
		{
			x = std::round(x);
			y = std::round(y);
			z = std::round(z);
		}

		Point3D& operator= (const Point3D& value) = default;

		Point3D& operator= (Point3D&& value) noexcept
		{
			x = value.x;
			y = value.y;
			z = value.z;

			value.x = 0.0;
			value.y = 0.0;
			value.z = 0.0;

			return *this;
		}

		Point3D& operator= (const double* value)
		{
			x = value[0];
			y = value[1];
			z = value[2];

			return *this;
		}

	};


}

#endif // GRAPHICPRIMITIVES_H