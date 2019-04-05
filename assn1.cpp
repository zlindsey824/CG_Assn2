//
//		          Programming Assignment #1
//
//			        Victor Zordan
//
//
//
/***************************************************************************/

                                                   /* Include needed files */
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "line.h"
#include "curve.h"

#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header

#define WIDTH 500
#define HEIGHT 500

//Used to house color values
typedef struct{
	double r;
	double g;
	double b;
} Color;

//These variables are declared at a global scope so that they may
// be called anywhere in the pwogram
Color *colorA, *colorB;			//colorA points to the starting color and colorB points to the end color
Line line;
Curve curve;
const int numOfPoints = 15;
float points[numOfPoints][2];
const int numOfFaces = 2 * 15;
int faces[numOfFaces][3];

//These variables are used in conjuction with the keyboard inputs
//to permit certain functionality depending on the input
bool linesActive = false;
bool curvesActive =  false;
bool erase = false;
bool drawn = false;

int x_last,y_last;

/***************************************************************************/

void init_window()
                 /* Clear the image area, and set up the coordinate system */
{

        					       /* Clear the window */
        glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
        glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
}

/***************************************************************************/

void write_pixel(int x, int y, double redInc, double greenInc, double blueInc) /* Turn on the pixel found at x,y */
{
        glColor3f (colorA->r + redInc, colorA->g + greenInc, colorA->b + blueInc);
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();
}

//***************************************************************************/

void dda(){		//Function implementing the DDA algorithm
  float x = line.getPoint(0).x;
  float y = line.getPoint(0).y;
  float slope = line.getSlope();
  
  //This chunk helps in incrementing from the first color to the second color
  double rDiff = colorA->r;			//This calculates the difference between the red values
  double gDiff = colorA->g;			//This calculates the difference between the green values
  double bDiff = colorA->b;			//This calculates the difference between the blue values
  
  //Chooses this if the |slope| is less than 1 and increments along the x-values
  if (fabs(slope) < 1){
  	int xDiff = line.getPoint(1).x-line.getPoint(0).x;
  	int xInc = 0;
    while (line.haveAllPoints() && x != line.getPoint(1).x){
      write_pixel((int)x, (int)round(y),(rDiff),(gDiff),(bDiff));
      (line.getXdiff() < 0) ? x-- : x++;
      (line.getYdiff() < 0) ? y-=fabs(slope) : y+=fabs(slope);
      xInc++;
    }
  }
  //Chooses this if the |slope| is greater than or equal to 1 and increments along the y-values
  else if (fabs(slope) >= 1){
    slope = line.getInvSlope();
    int yDiff = line.getPoint(1).y-line.getPoint(0).y;
    int yInc = 0;
    while (line.haveAllPoints() && y != line.getPoint(1).y){
      write_pixel((int)round(x), (int)y,(rDiff),(gDiff),(bDiff));
      (line.getXdiff() < 0) ? x-=fabs(slope) : x+=fabs(slope);
      (line.getYdiff() < 0) ? y-- : y++;
      yInc++;
    }
  }
}

//***************************************************************************/

void display ( void )   // Create The Display Function
{

  if (erase){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen
    x_last = -1;
    y_last = -1;
    erase = false;
  }
  //This is used to still draw point clicks
/*  colorA = new Color{0,0,0};
  write_pixel(x_last,y_last,1.0,1.0,1.0);//<-you can get rid of this call if you like
  delete colorA;*/
  
  double r,g,b;
  if (!drawn){
	  for (int n = 0; n < numOfFaces; n++){
		if (!(n%2)){
			int colorDivisions = 100;			//Used to generate color value percentage
			//Generates random color as colorA (the starting color)
			r = (rand() % colorDivisions +1)/(double)colorDivisions;
			g = (rand() % colorDivisions +1)/(double)colorDivisions;
			b = (rand() % colorDivisions +1)/(double)colorDivisions;
		
		}	
		colorA = new Color{r,g,b};
	//	write_pixel(points[n][0],points[n][1],1.0,1.0,1.0);//<-you can get rid of this call if you like
		int point1X = points[faces[n][0]][0];
		int point1Y = points[faces[n][0]][1];
		int point2X = points[faces[n][1]][0];
		int point2Y = points[faces[n][1]][1];
		int point3X = points[faces[n][2]][0];
		int point3Y = points[faces[n][2]][1];
		line.addPoint(point1X,point1Y);
		line.addPoint(point2X,point2Y);
		if (line.haveAllPoints()) {
			dda();
			line.clearPoints();
			printf("\n");
		}
		line.addPoint(point2X,point2Y);
		line.addPoint(point3X,point3Y);
		if (line.haveAllPoints()) {
			dda();
			line.clearPoints();
			printf("\n");
		}
		line.addPoint(point3X,point3Y);
		line.addPoint(point1X,point1Y);
		if (line.haveAllPoints()) {
			dda();
			line.clearPoints();
			printf("\n");
		}
		delete colorA;
	  }
	  drawn = true;
	}  
 
  colorA = nullptr;
  colorB = nullptr;
  glutSwapBuffers();                                      // Draw Frame Buffer
}

/***************************************************************************/
void mouse(int button, int state, int x, int y)
{
/* This function I finessed a bit, the value of the printed x,y should
   match the screen, also it remembers where the old value was to avoid multiple
   readings from the same mouse click.  This can cause problems when trying to
   start a line or curve where the last one ended */
        static int oldx = 0;
        static int oldy = 0;
	int mag;

	y *= -1;  //align y with mouse
	y += 500; //ignore
	mag = (oldx - x)*(oldx - x) + (oldy - y)*(oldy - y);
	if (mag > 20) {
		printf(" x,y is (%d,%d)\n", x,y);
    if (linesActive)
		  line.addPoint(x,y);
    if (curvesActive)
      curve.addPoint(x,y);
	}
	oldx = x;
	oldy = y;
	x_last = x;
	y_last = y;
}

/***************************************************************************/
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{

	switch ( key ) {
		case 27:              // When Escape Is Pressed...
			exit ( 0 );   // Exit The Program
			break;
    case '1':             // stub for new screen
      printf("New screen\n");
			break;
		case 'l':
      linesActive = true;
      curvesActive =  false;
			printf("Drawing lines\n");
			break;
		case 'c':
      linesActive = false;
      curvesActive =  true;
      printf("Drawing curves\n");
			break;
		case 'e':
      erase = true;
      linesActive = false;
      curvesActive =  false;
      printf("Clearing screen\n");
      printf("Press 'l' to draw lines and 'c' to draw curves\n");
			break;
		default:
			break;
	}
}
/***************************************************************************/

int main (int argc, char *argv[])
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key.						  */


	 FILE *fptr;

	if ((fptr = fopen(argv[1], "r")) == NULL){
		printf("Error! opening file");

		// Program exits if the file pointer returns NULL.
		exit(1);
	}

	char type;
	int count = 0;
	float fileX,fileY;
	while (fscanf(fptr, "%c %f %f", &type, &fileX, &fileY) != EOF){
		
		if (type == 'v'){
			points[count][0] = fileX;
			points[count][1] = fileY;
			count++;
		}
	}
	rewind(fptr);
/*	char set1[6];
	char set2[6];
	char set3[6];*/
	count = 0;
	type = ' ';
	int v1, v2, v3;
	int vt1, vt2, vt3;
	int vn1, vn2, vn3;
	
	int line = 0;
	while (fscanf(fptr, "%c %d/%d/%d %d/%d/%d %d/%d/%d \n", &type, &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3) != EOF){
		printf("%d\n", line);
		if (type == 'f'){
			printf("%c %d/%d/%d %d/%d/%d %d/%d/%d\n", type, v1, vt1, vn1, v2, vt2, vn2, v3, vt3, vn3);
			faces[count][0] = v1-1;
			faces[count][1] = v2-1;
			faces[count][2] = v3-1;
			count++;
		}
		else{
			getline(NULL,0,fptr);
		}
		line++;
	}
	

	srand(time(NULL));
	glutInit            ( &argc, argv );
       	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize  ( 500,500 );
	glutCreateWindow    ( "Computer Graphics" );
	glutDisplayFunc     ( display );
	glutIdleFunc	    ( display );
	glutMouseFunc       ( mouse );
	glutKeyboardFunc    ( keyboard );

        init_window();				             //create_window

	glutMainLoop        ( );                 // Initialize The Main Loop

	fclose(fptr);
}
