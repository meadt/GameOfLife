
/****************************************************************************
  example3.cpp
  A GLUT program using all the features of the GLUI User Interface Library
  (except columns, featured in example4.cpp)
  -----------------------------------------------------------------------
  9/9/98 Paul Rademacher (rademach@cs.unc.edu)
****************************************************************************/

#ifdef __APPLE__
#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif
#endif

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include <string.h>
#include <glui.h>
#include <math.h>
#include <list>
#include <tuple>
#include <unistd.h>

#include "board.h"
#include "agent.h"
#include "global.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float x_start{-3};
float y_start{-3};

//set offset first and add modifier
// tuples: {y_modifier, x_modifier}

// Take in XY coords for each agent.

void drawSquare(float x_start, float y_start, Agent *agent) {
    
    float x_offset = static_cast<float>(std::get<0>(agent->getPos()));
    float y_offset = static_cast<float>(std::get<1>(agent->getPos()));    
    
    if (agent->checkState()) {
    
        glBegin(GL_QUADS);

            // vertex 1 - left bottom
            glColor3d(0.75, 0, 0);
            glVertex2f((y_start + y_offset) - 0.2, (x_start + x_offset) - 0.2);

            // vertex 2 - right bottom
            glColor3d(0.75, 0, 0);
            glVertex2f((y_start + y_offset) + 0.2, (x_start + x_offset) - 0.2);

            // vertex 3 - right top
            glColor3d(0.75, 0, 0);
            glVertex2f((y_start + y_offset) + 0.2, (x_start + x_offset) + 0.2);

            //vertex 4 - left top
            glColor3d(0.75, 0, 0);
            glVertex2f((y_start + y_offset) - 0.2, (x_start + x_offset) + 0.2);

        glEnd();
    } else {
                
        glBegin(GL_QUADS);

            // vertex 1 - left bottom
            glColor3d(0, 0, 0.75);
            glVertex2f((y_start + y_offset) - 0.2, (x_start + x_offset) - 0.2);

            // vertex 2 - right bottom
            glColor3d(0, 0, 0.75);
            glVertex2f((y_start + y_offset) + 0.2, (x_start + x_offset) - 0.2);

            // vertex 3 - right top
            glColor3d(0, 0, 0.75);
            glVertex2f((y_start + y_offset) + 0.2, (x_start + x_offset) + 0.2);

            //vertex 4 - left top
            glColor3d(0, 0, 0.75);
            glVertex2f((y_start + y_offset) - 0.2, (x_start + x_offset) + 0.2);
        
        glEnd();
    }
}

void drawBoard(Board *board) {
    for (int i = 0; i < board->getWidth(); i++)
            for (int j = 0; j < board->getDepth(); j++) {
                drawSquare(x_start, y_start, board->getAgent(i, j)); 
            }
}

// Take in board.
void renderScene() {
    
        // clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // reset transformations
        glLoadIdentity();
        
        // set the camera
        gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);
        
        BOARDPOINTER->updateState();
        sleep(1);
        drawBoard(BOARDPOINTER);
        
	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int displayGlui(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Git of Life");
        
        // register callbacks
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
        
        glutMainLoop();

	return 1;
}