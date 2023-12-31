#include "../include/curves_3d.h"

Elipse::Elipse()
{
    center = {0.0, 0.0, 0.0};
    radius_a = 1.0;
    radius_b = 1.0;

    this->x_function = circleFunctionX;
    this->y_function = circleFunctionY;
    this->z_function = flatFunction;

    this->x_derivation = circleDerivationX;
    this->y_derivation = circleDerivationY;
    this->z_derivation = flatFunction;
}

Elipse::Elipse(Point3 center, double radius_a, double radius_b) : Elipse()
{
    this->center = center;
    if (radius_a < 0)
        this->radius_a = -1*radius_a;
    else
        this->radius_a = radius_a;

    if (radius_b < 0)
        this->radius_b = -1*radius_b;
    else
        this->radius_b = radius_b;
}

double Elipse::getRadiusA() const
{
    return radius_a;
}

double Elipse::getRadiusB() const
{
    return radius_b;
}

void Elipse::setRadiusA(double radius)
{
    this->radius_a = radius;
}

void Elipse::setRadiusB(double radius)
{
    this->radius_b = radius;
}

Point3 Elipse::getCartesianAt(double parameter) const
{
    return Point3({center.x + x_function(parameter,radius_a),
                   center.y + y_function(parameter,radius_b),
                   center.z});
}

Vector3 Elipse::getDerivateAt(double parameter) const
{
    auto start = getCartesianAt(parameter);

    auto end = Point3({start.x + x_function(parameter, radius_a),
                       start.y + y_function(parameter, radius_b),
                       0.0});

    return Vector3({start,end});
}
