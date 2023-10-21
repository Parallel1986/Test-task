#include "include/curves_3d.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>


#define MAX_CURVES 20
#define MIN_CURVES 5
#define X_MIN -50
#define X_MAX 50
#define Y_MIN -50
#define Y_MAX 50
#define Z_MIN -50
#define Z_MAX 50
#define RAD_MAX 100
#define RAD_MIN 0.1
#define STEP_MAX 10


Point3 generateCenter()
{
    double x = (double)(rand()%(X_MAX - X_MIN)) + X_MIN;
    double y = (double)(rand()%(Y_MAX - Y_MIN)) + Y_MIN;
    double z = (double)(rand()%(Z_MAX - Z_MIN)) + Z_MIN;
    return Point3({x,y,z});
}

double generateRadius()
{
    return (double)(rand()%(RAD_MAX)) + RAD_MIN;
}

double generateStep()
{
    return (double)(rand()%(STEP_MAX));
}

std::shared_ptr<Curve3D> generateCircle()
{
    auto center = generateCenter();
    auto radius = generateRadius();

    std::shared_ptr<Curve3D> circle(new Circle(center,radius));
    return circle;
}

std::shared_ptr<Curve3D> generateElipse()
{
    auto center = generateCenter();
    auto radius_a = generateRadius();
    auto radius_b = generateRadius();

    std::shared_ptr<Curve3D> elipse(new Elipse(center,radius_a,radius_b));
    return elipse;
}

std::shared_ptr<Curve3D> generateHelix()
{
    auto center = generateCenter();
    auto radius = generateRadius();
    auto step = generateStep();

    std::shared_ptr<Curve3D> helix(new Helix(center,radius,step));
    return helix;
}

std::shared_ptr<Curve3D> makeRandomCurve()
{
    int rand_type = rand()%3;

    switch (rand_type)
    {
    case 0:
        return(std::shared_ptr<Curve3D> (generateCircle()));
    case 1:
        return(std::shared_ptr<Curve3D>(generateElipse()));
    case 2:
        return(std::shared_ptr<Curve3D>(generateHelix()));

    //Shouldn't get here
    default:
        throw (std::exception("makeRandomCurve(): unknown curve"));
        break;
        }
}

std::vector<std::shared_ptr<Curve3D>> generateVector()
{
    int circle_count = 0;
    auto size = std::rand()%MAX_CURVES + MIN_CURVES;

    std::vector<std::shared_ptr<Curve3D>> vector;

    for (int i = 0; i < size; ++i)
    {
        std::shared_ptr<Curve3D> curve (makeRandomCurve());

        if (curve->getCurveType() == CurveType::CIRCLE)
            ++circle_count;
    }

    while (circle_count == 0)
    {
        vector.pop_back();
        vector.emplace_back(generateCircle());
    }

    return vector;
}

int main()
{
    std::srand(std::time(nullptr));

    std::vector<std::shared_ptr<Curve3D>> curves (generateVector());

    std::vector<std::shared_ptr<Circle>> circles;

    int counter = 0;
    for (auto& curve : curves)
    {
        auto center = curve->getCenter();
        std::printf("Curve #%d, center (%f1, %f1, %f1)\n", counter,center.x,center.y,center.z);

        auto point = curve->getCartesianAt(M_PI/4);
        std::printf("Point at PI/4 : (%f1, %f1, %f1)\n", point.x, point.y, point.z);

        point = curve->getDerivateAt(M_PI/4);
        std::printf("Point at PI/4 : (%f1, %f1, %f1)\n\n", point.x, point.y, point.z);

        if (curve->getCurveType() == CurveType::CIRCLE)
        {
            std::shared_ptr<Circle> static_pointer_cast(std::shared_ptr<Curve3D>& curve);
            std::shared_ptr<Circle> circle (static_cast<Circle*>(curve.get()));
            circles.emplace_back(circle);
        }

    }


}
