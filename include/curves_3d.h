#ifndef CURVES_3D_H
#define CURVES_3D_H
#include <cmath>
#include <functional>

#define M_PI 3.14159265358979323846

struct Point3
{
    double x = 0.0, y = 0.0, z = 0.0;
};


enum CurveType
{
    ELIPSE,
    CIRCLE,
    HELIX
};

namespace ParametricFunctions
{
    double FlatFunction(double parameter, double radius)
    {
        return 0.0;
    }

    double CircleFunctionX(double parameter, double radius)
    {
        return radius * std::cos(parameter);
    }

    double CircleFunctionY(double parameter, double radius)
    {
        return radius * std::sin(parameter);
    }

    double HelixFunctionZ(double parameter, double step)
    {
        return (step * parameter)/(2*M_PI);
    }

    double CircleDerivationX(double parameter, double radius)
    {
        return (-radius * std::sin(parameter));
    }

    double CircleDerivationY(double parameter, double radius)
    {
        return (radius * std::cos(parameter));
    }

    double HelixDerivationZ(double parameter, double step)
    {
        return ((step)/(2*M_PI));
    }
}

class Curve3D
{
public:
    virtual Point3 getCartesianAt(double parameter) const = 0;
    virtual Point3 getDerivateAt(double parameter) const = 0;

    Point3 getCenter() const;
    CurveType getCurveType() const;

    void setCenter(Point3 center);

protected:

    std::function<double(double parameter, double value)> x_function;
    std::function<double(double parameter, double value)> y_function;
    std::function<double(double parameter, double value)> z_function;

    std::function<double(double parameter, double value)> x_derivation;
    std::function<double(double parameter, double value)> y_derivation;
    std::function<double(double parameter, double value)> z_derivation;

    Point3 center;
    CurveType type;
};


class Elipse : public Curve3D
{
public:
    Elipse();
    Elipse(Point3 center, double radius_a, double radius_b);

    virtual Point3 getCartesianAt(double parameter) const override;
    virtual Point3 getDerivateAt(double parameter) const override;

    double getRadiusA() const;
    double getRadiusB() const;

    void setRadiusA(double radius);
    void setRadiusB(double radius);

private:
    double radius_a;
    double radius_b;
};


class Circle : public Curve3D
{
public:
    Circle();
    Circle(Point3 center, double radius);

    virtual Point3 getCartesianAt(double parameter) const override;
    virtual Point3 getDerivateAt(double parameter) const override;

    double getRadius() const;

    void setRadius(double radius);

private:
    double radius;
};


class Helix : public Curve3D
{
public:
    Helix();
    Helix(Point3 center, double radius, double step);

    virtual Point3 getCartesianAt(double parameter) const override;
    virtual Point3 getDerivateAt(double parameter) const override;

    double getRadius() const;
    double getStep() const;

    void setRadius(double radius);
    void setStep(double step);

private:
    double radius, step;
};

#endif // CURVES_3D_H
