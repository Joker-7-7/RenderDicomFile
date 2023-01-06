#ifndef POINT3D_H
#define POINT3D_H

#include <cmath>

namespace GraphicPrimitives
{
	class Point3D
	{
	public:
		double x;
		double y;
		double z;

    public:
		Point3D() :
            x(0.0),
            y(0.0),
            z(0.0)
        {
        }

		Point3D(const double x, const  double y,const double z) :
            x(x),
            y(y),
            z(z)
        {
        }

		explicit Point3D(const double* value) :
            x(value[0]),
            y(value[1]),
            z(value[2])
        {
        }

		Point3D(const Point3D& point) = default;
		Point3D(Point3D&& point) noexcept = default;
		Point3D& operator= (const Point3D& value) = default;
		Point3D& operator= (Point3D&& value) noexcept = default;
		Point3D& operator= (const double* value);

        void round();
	};
}

#endif // POINT3D_H