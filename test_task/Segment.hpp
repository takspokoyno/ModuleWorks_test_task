#ifndef __Segment_hpp__
#define __Segment_hpp__

#include "Sphere.hpp"
#include "mwMathConstants.hpp"

//!This class represents segment.
/*!Segment presented as a two 3d points (edgepoints).
*/
class Segment
{
public:

    // Sets default segment
    inline Segment()
    {
        mFirst = cadcam::mwTPoint3d<double>();
        mSecond = cadcam::mwTPoint3d<double>();
    };

    // Sets segment by two 3d points 
    inline Segment(const cadcam::mwTPoint3d<double> &first, const cadcam::mwTPoint3d<double> &second)
    {
        mFirst = first;
        mSecond = second;
    };

    // Copy segment
    inline Segment(const Segment &sm)
    {
        mSecond = sm.mSecond;
        mFirst = sm.mFirst;
    };

    // Get first edgepoint
    inline cadcam::mwTPoint3d<double> getSecond() const
    {
        return mSecond;
    }; 

    // Get second edgepoint
    inline cadcam::mwTPoint3d<double> getFirst() const
    {
        return mFirst;
    };

    // Returns length of segment
    inline double length() const
    {
        return ~(mSecond - mFirst);
    };

    // Returns distance from first edgepoint to given 3d point
    inline double distanceToFirstEdge(const cadcam::mwTPoint3d<double> &point) const
    {
        return ~(mFirst - point);
    };

    // Returns distance from second edgepoint to given 3d point
    inline double distanceToSecondEdge(const cadcam::mwTPoint3d<double> &point) const
    {
        return ~(mSecond - point);
    };

    // Returns vector product of segment and given 3d point - edgepoint segment
    inline cadcam::mwTPoint3d<double> vectorProduct(const cadcam::mwTPoint3d<double> &point) const
    {
        return ((mSecond - mFirst) % (point - mFirst));
    };

    // Returns distance from given 3d point to line, which contains segment
    inline double distanceToLine(const cadcam::mwTPoint3d<double> &point) const
    {
        return ~(vectorProduct(point)) / length();
    };

    // Returns minimal distance from segment to given 3d point
    inline double minimalDistance(const cadcam::mwTPoint3d<double> &point) const
    {
        double distanceToCloserEdge = cadcam::mw_min(distanceToFirstEdge(point), distanceToSecondEdge(point));
        return cadcam::mw_min(distanceToCloserEdge, distanceToLine(point));
    };

    // Returns rectangle zone in which 2d interpritation of points
    // that are equidistant from segment is located
    /* workingzone[0] - min coordinate x of rectangle zone
       workingzone[1] - max coordinate x of rectangle zone 
       workingzone[2] - min coordinate y of rectangle zone
       workingzone[3] - max coordinate y of rectangle zone
    */  
    inline void workingZone(const double radius, double* workingzone){
        workingzone[0] = ((mFirst[0] <= mSecond[0]) ? mFirst[0] : mSecond[0]) - radius;
        workingzone[1] = ((mFirst[0] >= mSecond[0]) ? mFirst[0] : mSecond[0]) + radius;
        workingzone[2] = ((mFirst[1] <= mSecond[1]) ? mFirst[1] : mSecond[1]) - radius;
        workingzone[3] = ((mFirst[1] >= mSecond[1]) ? mFirst[1] : mSecond[1]) + radius;
    };

private:
    cadcam::mwTPoint3d<double> mFirst;
    cadcam::mwTPoint3d<double> mSecond;
};

#endif //__Segment_hpp__