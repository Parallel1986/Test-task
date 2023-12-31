#include "../include/curves_3d.h"

Circle::Circle()
{
    this->center = {0.0, 0.0, 0.0};
    this->radius = 1.0;

    this->x_function = circleFunctionX;
    this->y_function = circleFunctionY;
    this->z_function = flatFunction;

    this->x_derivation = circleDerivationX;
    this->y_derivation = circleDerivationY;
    this->z_derivation = flatFunction;
}

Circle::Circle(Point3 center, double radius) : Circle()
{
    this->center = center;
    if (radius < 0)
        this->radius = -1*radius;
    else
        this->radius = radius;
}

double Circle::getRadius() const
{
    return radius;
}

void Circle::setRadius(double radius)
{
    if (radius >= 0)
        this->radius = radius;
    else
        this->radius = -radius;
}

Point3 Circle::getCartesianAt(double parameter) const
{
    return Point3({center.x + x_function(parameter,radius),
                   center.y + y_function(parameter,radius),
                   center.z});
}

Vector3 Circle::getDerivateAt(double parameter) const
{
    auto start = getCartesianAt(parameter);

    auto end = Point3({start.x + x_function(parameter, radius),
                       start.y + y_function(parameter, radius),
                       0.0});

    return Vector3({start,end});
}
