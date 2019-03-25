#ifndef CURVE_H
#define CURVE_H

#include "line.h"

class Curve{
public:
	Curve(): points(new Point[4]), numPoints(0), maxPoints(4) {}

	~Curve(){ delete[] points; }

	void addPoint(int x, int y);	//Adds a point to the points array
	Point getPoint(float u);			//Returns a point within the curve using the u-value
	int getNumPoints();						//Returns the number of points collected (numPoints)
	bool haveAllPoints();					//Returns whether all points have been collected
  void clearPoints();						//Clears points from the array

private:
  int factorial(int n);			//Used to calculate the factorial of an integer n
  int calculateCi(int i);		//Calculates the Ci value from the Bernstein plynomial
	Point* points;						//Pointer that points to an array of points that define the curve
	int numPoints;						//Number of points collected
	int maxPoints;						//Maximum number of points allowed
};
#endif
