#include "include_lib/curves_3d.h"
#include "omp.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <memory>
#include <exception>

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
#define RAD_SIGNS_BELOW_ZERO 2
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
    return ((rand()%(int)(RAD_MAX*pow(10,RAD_SIGNS_BELOW_ZERO)))
            /pow(10,RAD_SIGNS_BELOW_ZERO))+RAD_MIN;
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
        throw (std::runtime_error("makeRandomCurve(): unknown curve"));
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

void printCurveInfo(const Curve3D* curve)
{
    auto center = curve->getCenter();
        std::printf("Center \t\t(%.1f, %.1f, %.1f)\n", center.x,center.y,center.z);

        auto point = curve->getCartesianAt(M_PI/4);
        std::printf("Point at PI/4 : \t(%.1f, %.1f, %.1f)\n", point.x, point.y, point.z);

        auto vec = curve->getDerivateAt(M_PI/4);
        std::printf("Derivation at PI/4: start (%.1f, %.1f, %.1f)\t"
                    "end (%.1f, %.1f, %.1f)\n"
                    ,vec.start.x, vec.start.y, vec.start.z
                    ,vec.end.x,vec.end.y,vec.end.z);
}

void printVectorOfCircles(const std::vector<std::shared_ptr<Circle>>& circles)
{
    int count = 0;
    for (auto& circle:circles)
    {
        std::printf("Circle #%d, radius = %.1f\n", count, circle->getRadius());
        ++count;
    }
}

void calculateTotalRadius(std::vector<std::shared_ptr<Circle>>& circles)
{
    double radii_sum = 0.0;

    #pragma omp parallel for reduction(+:radii_sum)
    {
        for (auto& circle:circles)
        {
            radii_sum += circle->getRadius();
        }
    }
    std::printf("\nTotal radii sum = %.1f\n", radii_sum);
}

int main()
{
    std::srand((unsigned int)std::time(nullptr));

    std::vector<std::shared_ptr<Curve3D>> curves (generateVector());
    std::vector<std::shared_ptr<Circle>> circles;

    std::cout <<"Initial curve vector\n";
    int counter = 0;
    for (auto& curve : curves)
    {
        std::cout << "Curve #" << counter << std::endl;
        printCurveInfo(curve.get());

        if (dynamic_cast<Circle*>(curve.get()))
        {
            circles.emplace_back(std::dynamic_pointer_cast<Circle>(curve));
            auto rad = circles.back()->getRadius();
            std::printf("It is a circle with radius: \t%.1f\n", rad);
        }
        ++counter;
        std::cout << std::endl;
    }

    printVectorOfCircles(circles);

    std::sort(circles.begin(),circles.end(),[](std::shared_ptr<Circle> first, std::shared_ptr<Circle> second){
            return first->getRadius()<second->getRadius();
        });

    std::cout <<"\nSorted vector of circles:\n";

    printVectorOfCircles(circles);

    calculateTotalRadius(circles);

    std::cin >> counter;
}
