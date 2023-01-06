#include "Point3D.hpp"

namespace GraphicPrimitives
{
    Point3D operator+(const Point3D& a, const Point3D& b) {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    Point3D operator-(const Point3D& a, const Point3D& b) {
        return {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    Point3D &Point3D::operator=(const double* value) {
        x = value[0];
        y = value[1];
        z = value[2];

        return *this;
    }

    void Point3D::round() {
        x = std::round(x);
        y = std::round(y);
        z = std::round(z);
    }
}
