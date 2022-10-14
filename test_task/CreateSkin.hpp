#ifndef CREATESKIN_HPP
#define CREATESKIN_HPP

#include "mwTPoint3d.hpp"
#include "mwDiscreteFunction.hpp"

void CreateSkin( const cadcam::mwTPoint3d<double> refPoint, 
				const unsigned long nx, const unsigned long ny, 
				const unsigned long nz, const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName );


// Round rectangle working zone considering delta
void RoundToDelta(const double delta, double* workingzone);	

// Creates array of all points in upper layer before all calculations
void CreateArrayOfPoints(std::pair<double, double> *arrayOfPairs, unsigned long nx, unsigned long ny, double delta);

#endif /* CREATESKIN_HPP */
