#include "../include/curves_3d.h"

Elipse::Elipse()
{
    center = {0.0, 0.0, 0.0};
    radius_a = 1.0;
    radius_b = 1.0;
    this->type = CurveType::Elipse;

    this->x_function = ParametricFunctions::CircleFunctionX;
    this->y_function = ParametricFunctions::CircleFunctionY;
    this->z_function = ParametricFunctions::FlatFunction;

    this->x_derivation = ParametricFunctions::CircleDerivationX;
    this->y_derivation = ParametricFunctions::CircleDerivationY;
    this->z_derivation = ParametricFunctions::FlatFunction;
}

Elipse::Elipse(Point3 center, double radius_a, double radius_b) : Elipse()
{
    this->center = center;
    this->radius_a = radius_a;
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

Point3 Elipse::getDerivateAt(double parameter) const
{
    return Point3({x_derivation(parameter,radius_a),
                   y_derivation(parameter,radius_b),
                   0.0});
}
