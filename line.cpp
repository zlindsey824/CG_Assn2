#include <cstdlib>
#include "line.h"

//Adds a point to the points array
void Line::addPoint(int x, int y){
	if (numPoints < 2){
		Point newPoint = {x,y};
		points[numPoints] = newPoint;
		numPoints++;
	}
}

//Returns a point within the curve using the u-value
Point Line::getPoint(int index) {return points[index];}

//Returns the number of points collected (numPoints)
int Line::getNumPoints(){
	return numPoints;
}

//Returns whether all points have been collected
bool Line::haveAllPoints(){return numPoints == maxPoints;}

//Clears points from the array
void Line::clearPoints(){
  delete[] points;								//Deletes it
  points = new Point[maxPoints];	//Instantiates a new one
  numPoints = 0;									//Resets numPoints to 0
}

//Returns the difference between x2 and x1
int Line::getXdiff(){
	return points[1].x-points[0].x;
}

//Returns the difference between y2 and y1
int Line::getYdiff(){
	return points[1].y-points[0].y;
}

//Returns the slope of the line that passes through point 1 and point 2
float Line::getSlope(){
	return (float)getYdiff()/getXdiff();
}

//Returns the inverted slope used for when incrementing on Y
float Line::getInvSlope(){
  return (float)getXdiff()/getYdiff();
}
