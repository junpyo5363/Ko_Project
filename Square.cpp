/* Implement: Define each function of Square class */
/* Implement: Define area and circumference of square with macro */
/* Implement: Use assert */

#include "Square.h"
#define Area(Y) (Y*Y)
#define CirCumference(Y) ((4)*(Y))
Square::Square(float x, float y, float r, float g, float b, float h, float l)  {
	color[0] = r; color[1] = g; color[2] = b;
	center_pos[0] = x; center_pos[1] = y;
	height = h;
	length = l;
}
;
void Square::draw(bool x)  {
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(this->center_pos[0] , this->center_pos[1] + this->height / 2);
	glVertex2f(this->center_pos[0] , this-> center_pos[1] - this->height / 2);
	if(x==1) glVertex2f(this->center_pos[0] + this->length / 2,  this->center_pos[1] );
	if(x==0) glVertex2f(this->center_pos[0] - this->length / 2,  this->center_pos[1] );
	glEnd();
}

