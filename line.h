#ifndef LINE_H
#define LINE_H

//Used to house point coordinates
typedef struct{
	int x;
	int y;
} Point;


class Line{
public:
	Line(): points(new Point[2]), numPoints(0), maxPoints(2) {}

	~Line(){ delete[] points; }

	void addPoint(int x, int y);	//Adds a point to the points array
	Point getPoint(int index);		//Returns a point within the curve using the u-value
	int getNumPoints();						//Returns the number of points collected (numPoints)
	bool haveAllPoints();					//Returns whether all points have been collected
  void clearPoints();						//Clears points from the array

	int getXdiff();								//Returns the difference between x2 and x1
	int getYdiff();								//Returns the difference between y2 and y1
	float getSlope();							//Returns the slope of the line that passes through point 1 and point 2
  float getInvSlope();					//Returns the inverted slope used for when incrementing on Y
private:
	Point* points;						//Pointer that points to an array of points that define the curve
	int numPoints;						//Number of points collected
	int maxPoints;						//Maximum number of points allowed
};
#endif
