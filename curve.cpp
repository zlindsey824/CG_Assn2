#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "curve.h"

//Adds a point to the points array
void Curve::addPoint(int x, int y){
	if (numPoints < maxPoints){
		Point newPoint = {x,y};
		points[numPoints] = newPoint;
		numPoints++;
	}
}

//Returns a point within the curve using the u-value
Point Curve::getPoint(float u) {
  float uX = 0;
  float uY = 0;
  float n = maxPoints-1;
  //generating the summation
  for(float i = 0; i < maxPoints; i++){
    int C = calculateCi(i);			//Holds the Ci value
    float uI = pow(u,i);				//Holds the u^i value
    float uNI = pow(1-u, n-i);	//Holds the (1-u)^(n-i) value
    //These 2 values sum the x-value and y-value of the point at u
    uX += points[(int)i].x * C * uI * uNI;
    uY += points[(int)i].y * C * uI * uNI;
  }
  //Rounded to fit into an int
  int X = round(uX);
  int Y = round(uY);
  Point calcPoint = {X,Y};
  return calcPoint;

}

//Returns the number of points collected (numPoints)
int Curve::getNumPoints(){
	return numPoints;
}

//Returns whether all points have been collected
bool Curve::haveAllPoints(){return numPoints == maxPoints;}

//Clears points from the array
void Curve::clearPoints(){
  delete[] points;								//Deletes it
  points = new Point[maxPoints];	//Instantiates a new one
  numPoints = 0;									//Resets numPoints to 0
}

//Recursive function that calcuates the factorial value of an integer n
int Curve::factorial(int n){
  if (n == 0 || n == 1)
    return 1;

  return n * factorial(n-1);
}

//Separate function that generates the Ci value of the Bernstein polynomial
int Curve::calculateCi(int i){
  int n = maxPoints - 1;
  int top = factorial(n);
  int bottom = factorial(i) * factorial(n-i);
  return top/bottom;
}
