#ifndef __Sphere_hpp__
#define __Sphere_hpp__

#include "mwTPoint3d.hpp"

//!This class represents a sphere.
/*!The sphere is a 3d point as a center and radius.
*/
class Sphere
{
public:

    // Sets default sphere
    inline Sphere()
    {
        mCenter = cadcam::mwTPoint3d<double>();
        mRadius = 1;
    };

    // Sets sphere to given center and set given radius 
    inline Sphere(const cadcam::mwTPoint3d<double> &center, const double &radius)
    {
        mCenter = center;
        mRadius = radius;
    };

    // Copy sphere
    inline Sphere(const Sphere &sp)
    {
        mRadius = sp.mRadius;
        mCenter = sp.mCenter;
    };

    //!Assigment operator
	/*!Assigns one sphere object to another
	   returns current sphere with copied information
	*/
    inline const Sphere &operator=( const Sphere &sp )
	{
		if( this != &sp )
		{
			mCenter = sp.mCenter;
			mRadius = sp.mRadius;
		}

		return *this;
	};

    // Get radius of sphere
    inline double getRadius() const
    {
        return mRadius;
    }; 

    // Get center of sphere
    inline cadcam::mwTPoint3d<double> getCenter() const
    {
        return mCenter;
    };

    // Moves sphere to new center
    inline void moveTo(const cadcam::mwTPoint3d<double> &newCenter)
    {
        mCenter = newCenter;
    };

private:
    cadcam::mwTPoint3d<double> mCenter;
    double mRadius;
};

#endif //__Sphere_hpp__