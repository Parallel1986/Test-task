#include "../include/curves_3d.h"

Circle::Circle()
{
    this->center = {0.0, 0.0, 0.0};
    this->radius = 1.0;
    this->type = CurveType::Circle;

    this->x_function = ParametricFunctions::CircleFunctionX;
    this->y_function = ParametricFunctions::CircleFunctionY;
    this->z_function = ParametricFunctions::FlatFunction;

    this->x_derivation = ParametricFunctions::CircleDerivationX;
    this->y_derivation = ParametricFunctions::CircleDerivationY;
    this->z_derivation = ParametricFunctions::FlatFunction;
}

Circle::Circle(Point3 center, double radius) : Circle()
{
    this->center = center;
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

Point3 Circle::getDerivateAt(double parameter) const
{
    return Point3({x_derivation(parameter,radius),
                   y_derivation(parameter,radius),
                   0.0});
}
