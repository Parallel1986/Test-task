#ifndef CURVES_3D_H
#define CURVES_3D_H

#if defined(_WIN32) || defined(_WIN64)

	#define MYLIB_EXPORT __declspec(dllexport)
	#define MYLIB_IMPORT __declspec(dllimport)
	
#else
	#define MYLIB_EXPORT __attribute__((visibility("default")))
	#define MYLIB_IMPORT __attribute__((visibility("default")))
	#define MYLIB_HIDDEN __attribute__((visibility("hidden")))
#endif

#include <cmath>
#include <functional>

#define M_PI 3.14159265358979323846

struct MYLIB_EXPORT Point3
{
    double x = 0.0, y = 0.0, z = 0.0;
};

class MYLIB_EXPORT Curve3D
{
public:
    virtual Point3 getCartesianAt(double parameter) const = 0;
    virtual Point3 getDerivateAt(double parameter) const = 0;

    Point3 getCenter() const;

    void setCenter(Point3 center);

protected:
    std::function<double(double parameter, double value)> x_function;
    std::function<double(double parameter, double value)> y_function;
    std::function<double(double parameter, double value)> z_function;

    std::function<double(double parameter, double value)> x_derivation;
    std::function<double(double parameter, double value)> y_derivation;
    std::function<double(double parameter, double value)> z_derivation;

    static double flatFunction(double parameter, double radius);
    static double circleFunctionX(double parameter, double radius);
    static double circleFunctionY(double parameter, double radius);
    static double helixFunctionZ(double parameter, double step);
    static double circleDerivationX(double parameter, double radius);
    static double circleDerivationY(double parameter, double radius);
    static double helixDerivationZ(double parameter, double step);

    Point3 center;
};


class MYLIB_EXPORT Elipse : public Curve3D
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


class MYLIB_EXPORT Circle : public Curve3D
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


class MYLIB_EXPORT Helix : public Curve3D
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
