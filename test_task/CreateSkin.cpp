#include "CreateSkin.hpp"
#include "Segment.hpp"
#include "FileWriter.hpp"
#include <iostream>

void CreateSkin( const cadcam::mwTPoint3d<double> refPoint, 
				const unsigned long nx, const unsigned long ny, 
				const unsigned long nz, const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName )
{

	double workingzone[4] = {0,0,0,0}; 		    //declaration and initial initialization of future working zone
	Sphere sphere(refPoint, sphereRad);		    //initial initialization of sphere
	cadcam::mwTPoint3d<double> nextCenter = func.Evaluate(func.GetBeginParameter());  //evaluate function in t0
	std::pair<double, double> *arrayOfPairs = new std::pair<double, double>[(nx+1)*(ny+1)];   // create array of 
	CreateArrayOfPoints(arrayOfPairs, nx, ny, delta);										  // points presented as (x,y)
	FileWriter filewriter(skinFileName, arrayOfPairs, (nx +1) * (ny +1), nz / delta);         // initialization of filewriter

	for(double i = func.GetBeginParameter(); i < func.GetEndParameter(); i += deltaT )  // for each step of discrete function
	{
		sphere.moveTo(nextCenter);

		if(i >= func.GetEndParameter() - deltaT)      // this check is to escape problems with floating point 
		{                                             // 0.01 * 100 is not actually 1
			nextCenter = func.Evaluate(func.GetEndParameter()); 
		}
		else 
		{
			nextCenter = func.Evaluate(i + deltaT);
		}

		Segment segment = Segment(sphere.getCenter(), nextCenter);  // creating segment with current and next positions of sphere
		segment.workingZone(sphereRad, workingzone);				// creating working zone in 2d plane where
		RoundToDelta(delta, workingzone);                           // we'll look for deleted 3d points

		for(double k = workingzone[0]; k <= workingzone[1] && k >= refPoint[0] && k <= nx; k+=delta)     //
		{																								 // for each unique (x,y)
			for(double j = workingzone[2]; j <= workingzone[3] && j >= refPoint[1] && j <= ny; j+=delta) //
			{
				double t = nz * delta;
				for(;segment.minimalDistance(cadcam::mwTPoint3d<double>(k, j, t)) <= sphereRad && t >= refPoint[2]; t-= delta){}
				filewriter.ChangeValue(std::pair<double, double>(k, j), t);    // finding the first 3d point which was not deleted
			}
		}
	} 

	filewriter.WriteToFile();

}

void RoundToDelta(const double delta, double* workingzone)
{
	for(int i = 0; i <= 3; i++)
	{
		double roundedvalue = 0;
		while (workingzone[i] - delta >= 0)
		{
			roundedvalue += delta;
			workingzone[i]-= delta;
		}
		workingzone[i] = roundedvalue;
	}
}

void CreateArrayOfPoints(std::pair<double, double> *arrayOfPairs, unsigned long nx, unsigned long ny, double delta)
{
	int t = 0;
	for(double i = 0; i <= nx/delta; i++)
	{
		for(double j = 0; j <= ny/delta; j++)
		{
			arrayOfPairs[t] = std::pair<double, double>(i*delta, j*delta);
			t++;
		}
	}
}