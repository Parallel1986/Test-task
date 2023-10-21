#include "../include/curves_3d.h"

Helix::Helix()
{
    this->center = {0.0, 0.0, 0.0};
    this->radius = 1.0;
    this->step = 0.0;
    this->type = CurveType::Helix;

    this->x_function = ParametricFunctions::CircleFunctionX;
    this->y_function = ParametricFunctions::CircleFunctionY;
    this->z_function = ParametricFunctions::HelixFunctionZ;

    this->x_derivation = ParametricFunctions::CircleDerivationX;
    this->y_derivation = ParametricFunctions::CircleDerivationY;
    this->z_derivation = ParametricFunctions::HelixDerivationZ;
}

Helix::Helix(Point3 center, double radius, double step) : Helix()
{
    this->center = center;
    this->radius = radius;
    this->step = step;
}

double Helix::getRadius() const
{
    return radius;
}

double Helix::getStep() const
{
    return step;
}

void Helix::setRadius(double radius)
{
    this->radius = radius;
}

void Helix::setStep(double step)
{
    this->step = step;
}

Point3 Helix::getCartesianAt(double parameter) const
{
    return Point3({center.x + x_function(parameter,radius),
                   center.y + y_function(parameter,radius),
                   center.z + z_function(parameter, radius)});
}

Point3 Helix::getDerivateAt(double parameter) const
{
    return Point3({x_derivation(parameter,radius),
                   y_derivation(parameter,radius),
                   z_derivation(parameter, step)});
}
