#include "../include/curves_3d.h"

Helix::Helix()
{
    this->center = {0.0, 0.0, 0.0};
    this->radius = 1.0;
    this->step = 0.0;

    this->x_function = circleFunctionX;
    this->y_function = circleFunctionY;
    this->z_function = helixFunctionZ;

    this->x_derivation = circleDerivationX;
    this->y_derivation = circleDerivationY;
    this->z_derivation = helixDerivationZ;
}

Helix::Helix(Point3 center, double radius, double step) : Helix()
{
    this->center = center;
    if (radius < 0)
        this->radius = -1*radius;
    else
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

Vector3 Helix::getDerivateAt(double parameter) const
{
    auto start = getCartesianAt(parameter);

    auto end = Point3({start.x + x_function(parameter, radius),
                       start.y + y_function(parameter, radius),
                       z_derivation(parameter, step)});

    return Vector3({start,end});
}
