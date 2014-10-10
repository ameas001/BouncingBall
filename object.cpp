// This file does not need to be modified
// C.P.
/////////////////////////////////////////
#include <GL/glut.h>
#include <cmath>

#include "const.h"
#include "object.h"

void Object2D::render() const
{
	glColor4d(color.r, color.g, color.b, color.a);
}

void Object2D::render(const Color & col) const
{
	glColor4d(col.r, col.g, col.b, col.a);
}

double Point2D::magnitude() const
{
	return sqrt(x * x + y * y);
}

double Point2D::magnitude2() const
{
	return x * x + y * y;
}

Point2D Point2D::normalized() const
{
	return (*this) / magnitude();
}

void Point2D::set(const Point2D & pos)
{
	x = pos.x;
	y = pos.y;
}

void Point2D::move(double dx, double dy) 
{
	x += dx;
	y += dy;
}

void Point2D::render() const
{
	Object2D::render();
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void Point2D::render(const Color & col) const
{
	Object2D::render(col);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

double Circle2D::perimeter() const
{
	return 2 * PI * radius;
}

double Circle2D::area() const
{
	return PI * radius * radius;
}

void Circle2D::set(const Point2D & pos)
{
	center = pos;
}

void Circle2D::move(double dx, double dy)
{
	center.move(dx, dy);
}

void Circle2D::present() const
{
	// May be inefficient to draw 180 segments
	// You can definitely improve this. Yes!? >_>
	const int NUM_SEGMENTS = 180;

	const double ARC_LINE = PI / NUM_SEGMENTS;
	if (filled)
	{	
		glBegin(GL_POLYGON);
		double theta = 0.0;
		while (theta <= 2 * PI)
		{
			glVertex2d(center.x + radius * cos(theta), center.y + radius * sin(theta));
			theta += ARC_LINE;
		}
		glEnd();
	}
	else
	{	
		glBegin(GL_LINE_LOOP);
		double theta = 0.0;
		while (theta <= 2 * PI)
		{
			glVertex2d(center.x + radius * cos(theta), center.y + radius * sin(theta));
			theta += ARC_LINE;
		}
		glEnd();
	}
}

void Circle2D::render() const
{
	Object2D::render();
	present();
}

void Circle2D::render(const Color & col) const
{
	Object2D::render(col);
	present();
}

void Balls2D::render() const
{
	Object2D::render(this->c.color);
	this->c.present();
}

void Balls2D::move(double dx, double dy)
{
	c.move(dx, dy);
}
