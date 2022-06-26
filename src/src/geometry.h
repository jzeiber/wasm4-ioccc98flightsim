#pragma once

struct Point2D
{
    Point2D();
    Point2D(const int x, const int y);

    int x;
    int y;
};

struct FPoint2D
{
    FPoint2D();
    FPoint2D(const double x, const double y);

    double x;
    double y;
};

struct FPoint3D
{
    FPoint3D();
    FPoint3D(const float x, const float y, const float z);

    float x;
    float y;
    float z;
};

struct Edge
{
    Edge();
    Edge(const FPoint3D &p1, const FPoint3D &p2);

    bool BehindViewport(const float z) const;    // returns true if both points are behind viewport, false otherwise
    void ClipToViewport(const float z);

    FPoint3D p1;
    FPoint3D p2;
};

int orientation(Point2D p, Point2D q, Point2D r);
int orientation(FPoint2D p, FPoint2D q, FPoint2D r);
bool doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2);
bool IntersectScreen(Point2D p1, Point2D q1);
