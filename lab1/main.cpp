// Name: Aranya Meas
// Quarter, Year: Spring, 2014
// Lab: 1
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <iostream>
#include "const.h"
#include "object.h"
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

Point2D p = Point2D(400.0, 400.0);
Circle2D circle = Circle2D(p, 25.0, VIOLET, true);
Balls2D balls = Balls2D(circle, 1500.0, 1000.0);
Color colors(0.5, 0.0, 1.0);

int currentTime = 0;
int previousTime = 0;
float elapsed = 0.0;

float randFloat()
{
	return rand() / static_cast<float>(RAND_MAX);
}
float randFloat(float min, float max)
{
	return randFloat() * (max - min) + min;
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
	float r = randFloat(0.0, 1.0);
	float g = randFloat(0.0, 1.0);
	float b = randFloat(0.0, 1.0);
	
	colors.r = r;
	colors.b = b;
	colors.g = g;
	
	balls.c.render(colors);
	
    glutSwapBuffers();
}

void update()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int diffTime = currentTime - previousTime;
	previousTime = currentTime;
	
	elapsed = (diffTime / 1000.0);
	
	balls.move(balls.x * elapsed, balls.y * elapsed);
}

void bounds()
{
	if(balls.c.center.y + balls.c.radius >= WINDOW_HEIGHT)
	{
		balls.y *= -1;
	}
	else if(balls.c.center.x + balls.c.radius >= WINDOW_WIDTH)
	{
		balls.x *= -1;
	}
	else if(balls.c.center.x - balls.c.radius <= 0)
	{
		balls.x *= -1;
	}
	else if(balls.c.center.y - balls.c.radius <= 0)
	{
		balls.y *= -1;
	}
}

void GLGameLoop()
{
	//update the balls position
	update();
	
	//handle the ball with the screen's bounds
	bounds();
	
	//Notify the next glutMainLoop iteration to run GLrender
	glutPostRedisplay();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CS 134 - Aranya Meas");
	
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
	
	glutDisplayFunc(GL_render);
	// ...
	// Complete this function
	// ...
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutIdleFunc(GLGameLoop);
	
	glutMainLoop();

	return 0;
}
