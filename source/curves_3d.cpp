#include "../include/curves_3d.h"

Point3 Curve3D::getCenter() const
{
    return center;
}

void Curve3D::setCenter(Point3 center)
{
    this->center = center;
}

CurveType Curve3D::getCurveType() const
{
    return type;
}
