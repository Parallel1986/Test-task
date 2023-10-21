#include "../include/curves_3d.h"

//namespace ParametricFunctions
//{
    double Curve3D::flatFunction(double parameter, double radius)
    {
        return 0.0;
    }

    double Curve3D::circleFunctionX(double parameter, double radius)
    {
        return radius * std::cos(parameter);
    }

    double Curve3D::circleFunctionY(double parameter, double radius)
    {
        return radius * std::sin(parameter);
    }

    double Curve3D::helixFunctionZ(double parameter, double step)
    {
        return (step * parameter)/(2*M_PI);
    }

    double Curve3D::circleDerivationX(double parameter, double radius)
    {
        return (-radius * std::sin(parameter));
    }

    double Curve3D::circleDerivationY(double parameter, double radius)
    {
        return (radius * std::cos(parameter));
    }

    double Curve3D::helixDerivationZ(double parameter, double step)
    {
        return ((step)/(2*M_PI));
    }
//}

Point3 Curve3D::getCenter() const
{
    return center;
}

void Curve3D::setCenter(Point3 center)
{
    this->center = center;
}
