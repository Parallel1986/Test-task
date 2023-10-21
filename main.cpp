#include "include/curves_3d.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>


#define MAX_CURVES 20
#define MIN_CURVES 5
#define X_MIN -50
#define X_MAX 50
#define Y_MIN -50
#define Y_MAX 50
#define Z_MIN -50
#define Z_MAX 50
#define RAD_MAX 100.0
#define RAD_MIN -50.0
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
    std::random_device rd;
    std::mt19937_64 gen{rd()};

    return std::generate_canonical<double,10>(gen)*RAD_MAX;
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
        vector.emplace_back(curve);
        if (dynamic_cast<Circle*>(curve.get()))
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

    std::cout <<"Initial curve vector\n";
    int counter = 0;
    for (auto& curve : curves)
    {
        auto center = curve->getCenter();
        std::printf("Curve #%d, center \t\t(%.1f, %.1f, %.1f)\n", counter,center.x,center.y,center.z);

        auto point = curve->getCartesianAt(M_PI/4);
        std::printf("Point at PI/4 : \t\t(%.1f, %.1f, %.1f)\n", point.x, point.y, point.z);

        point = curve->getDerivateAt(M_PI/4);
        std::printf("Derivation at PI/4 : \t(%.1f, %.1f, %.1f)\n", point.x, point.y, point.z);

        if (dynamic_cast<Circle*>(curve.get()))
        {
            circles.emplace_back(std::dynamic_pointer_cast<Circle>(curve));
            auto rad = circles.back()->getRadius();
            std::printf("It is a circle with radius: \t%.1f\n", rad);
        }
        ++counter;
        std::cout << std::endl;
    }

    counter = 0;
    std::cout << "Vector of circles:\n";
    for (auto& circle:circles)
    {
        std::cout << "Circle #" << counter << " radius = " << circle->getRadius() << std::endl;
        ++counter;
    }

    std::sort(circles.begin(),circles.end(),[](std::shared_ptr<Circle> first, std::shared_ptr<Circle> second){
            return first->getRadius()<second->getRadius();
        });

    std::cout <<"\nSorted vector of circles:\n";
    counter = 0;
    double radii_sum = 0.0;
    for (auto& circle:circles)
    {
        std::cout << "Circle #" << counter << " radius = " << circle->getRadius() << std::endl;
        radii_sum += circle->getRadius();
        ++counter;
    }
    std::cout << "\nTotal radii sum = " << radii_sum << std::endl;

    std::cin >> counter;
}
