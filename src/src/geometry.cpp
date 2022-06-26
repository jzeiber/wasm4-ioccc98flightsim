#include "geometry.h"
#include "miscfuncs.h"
#include "wasm4.h"

Point2D::Point2D():x(0),y(0)
{

}

Point2D::Point2D(const int xval, const int yval):x(xval),y(yval)
{

}

FPoint2D::FPoint2D():x(0),y(0)
{

}

FPoint2D::FPoint2D(const double xval, const double yval):x(xval),y(yval)
{

}

FPoint3D::FPoint3D():x(0),y(0),z(0)
{

}

FPoint3D::FPoint3D(const float xval, const float yval, const float zval):x(xval),y(yval),z(zval)
{

}

Edge::Edge()
{

}

Edge::Edge(const FPoint3D &p1val, const FPoint3D &p2val):p1(p1val),p2(p2val)
{

}

bool Edge::BehindViewport(const float z) const
{
    return (p1.x<z && p2.x<z);
}

void Edge::ClipToViewport(const float z)
{
    // if both points are in front or behind viewport, then return immediately
    // if both points are on same x plane, return immediately (they're either both shown or not if on same plane)
    if((p1.x>=z && p2.x>=z) || (p1.x<z && p2.x<z) || p1.x==p2.x)
    {
        return;
    }
    // clip x,y,z of point that crosses over negative x
    FPoint3D &maxp=(p1.x>p2.x ? p1 : p2);   // get max an min points based on x
    FPoint3D &minp=(p1.x>p2.x ? p2 : p1);
    const double pc=(maxp.x-z)/(maxp.x-minp.x);   // we want to clip at x=0 so get % of line that is positive coords
    minp.x=z;
    minp.y=(-pc*(maxp.y-minp.y))+maxp.y;
    minp.z=(-pc*(maxp.z-minp.z))+maxp.z;
}

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point2D p, Point2D q, Point2D r)
{
    if (q.x <= _max(p.x, r.x) && q.x >= _min(p.x, r.x) &&
        q.y <= _max(p.y, r.y) && q.y >= _min(p.y, r.y))
       return true;
 
    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point2D p, Point2D q, Point2D r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // collinear
 
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int orientation(FPoint2D p, FPoint2D q, FPoint2D r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0.) return 0;  // collinear
 
    return (val > 0.)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}

bool IntersectScreen(Point2D p1, Point2D q1)
{
    // simple bounding box check first
    // if max points are less or min points are more than screen dims, rects don't intersect
    if(_max(p1.x,q1.x)<0 || _max(p1.y,q1.y)<0 || _min(p1.x,q1.x)>=SCREEN_SIZE || _min(p1.y,q1.y)>=SCREEN_SIZE)
    {
        return false;
    }

    if(doIntersect(p1,q1,Point2D(0,0),Point2D(SCREEN_SIZE-1,0))==true)
    {
        return true;
    }
    if(doIntersect(p1,q1,Point2D(SCREEN_SIZE-1,0),Point2D(SCREEN_SIZE-1,SCREEN_SIZE-1))==true)
    {
        return true;
    }
    if(doIntersect(p1,q1,Point2D(0,SCREEN_SIZE-1),Point2D(SCREEN_SIZE-1,SCREEN_SIZE-1))==true)
    {
        return true;
    }
    if(doIntersect(p1,q1,Point2D(0,0),Point2D(0,SCREEN_SIZE-1))==true)
    {
        return true;
    }

    return false;
}
