
#define ENABLE_TRACE
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>

#include <windows.h>  // for MS Windows
#include <glut/glut.h>  // GLUT, include glu.h and gl.h
#include <set>

#include "PrintOutputHeader.h"
#include "Node.h"
#include "Sleep.h"
#include "GameWorld.h"



using namespace ds;
using namespace std;

int _WINDOW_WIDTH = 640;
int _WINDOW_HEIGHT = 480;

//int windowWidth  = 640;     // Windowed mode's width
//int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y

// global variables and constants
const unsigned int TARGET_FPS = 40;
double time_per_frame ;
double timeInterval = 0;
int start_time;
int frameCount;
bool SHOW_FPS = true;
double current_time = 0;
double previous_time = 0;
double last_time = 0;
bool fullScreenMode = false;
float fps = 0 ;
ds::Node startNode ;// = Node();
ds::Node targetNode ;//= Node();

GameWorld game_world ;

void initGL() {
	// Set "clearing" or background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
	start_time = glutGet(GLUT_ELAPSED_TIME);
    frameCount = 0;

	game_world.WorldInit();
	//game_world.createGrid();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
	
	game_world.delta_time = time_per_frame/1000;
	//First AI Update for game world
	game_world.AIupdate();

	game_world.renderGame();
	
	// Define shapes enclosed within a pair of glBegin and glEnd
	
	//Sleep(0.01);
	glutSwapBuffers();  // Render now
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	_WINDOW_WIDTH = width;
	_WINDOW_HEIGHT = height;

	if (_WINDOW_HEIGHT == 0) _WINDOW_HEIGHT = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)_WINDOW_WIDTH / (GLfloat)_WINDOW_HEIGHT;

	// Set the viewport to cover the new window
	glViewport(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (_WINDOW_WIDTH >= _WINDOW_HEIGHT) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		gluOrtho2D(0.0, _WINDOW_WIDTH, 0.0, _WINDOW_HEIGHT);
	} else {
		// aspect < 1, set the width to -1 to 1, with larger height
		gluOrtho2D(0.0, _WINDOW_WIDTH, 0.0 / aspect, _WINDOW_HEIGHT / aspect);
	}

	//	float height_of_each_grid =  _WINDOW_HEIGHT / _GRID_RESOLUTION_Y_AXIS;
	//	float width_of_each_grid = _WINDOW_WIDTH  / _GRID_RESOLUTION_X_AXIS;




	//for(int x=0; x < _GRID_RESOLUTION_X_AXIS; x++)
	//{
	//	//float current_X_coord = x * width_of_each_grid;

	//	for(int y=0; y < _GRID_RESOLUTION_Y_AXIS; y++)
	//	{
	//		float current_Y_coord = y * height_of_each_grid;
	//		glm::vec3 a = glm::vec3(width_of_each_grid * (x), height_of_each_grid * (y), 0);
	//		glm::vec3 b = glm::vec3(width_of_each_grid * (x+1), height_of_each_grid * (y), 0);
	//		glm::vec3 c = glm::vec3(width_of_each_grid * (x+1), height_of_each_grid * (y+1), 0);
	//		glm::vec3 d = glm::vec3(width_of_each_grid * (x), height_of_each_grid * (y+1), 0);

	//			float half_width = width_of_each_grid * (x+0.5);

	//		float half_height = height_of_each_grid * (y+0.5);
	//		glm::vec3 center = glm::vec3(half_width, half_height , 0);
	//		
	//		float proximity=0;
	//		if(width_of_each_grid<height_of_each_grid)
	//			proximity = width_of_each_grid;
	//		else
	//			proximity = height_of_each_grid;
	//		//nodes[x][y].setCubeCoordinates(CubeGeomerty(a,b,c,d, glm::vec3(x,y,0.0)));
	//		m_map[x][y].setCubeCoordinates(CubeGeomerty(a,b,c,d,center,proximity,glm::vec3(x,y,0.0)));
	//	}
	//}
}

void calculateFPS()
{
    //  Increase frame count
    frameCount++;

    //  Get the number of milliseconds since glutInit called 
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
	current_time = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
	timeInterval = current_time - previous_time;

	time_per_frame = current_time - last_time ;

	//cout<< "\n delta time:"<<time_per_frame/1000;

    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);

        //  Set time
        previous_time = current_time;

        //  Reset frame count
        frameCount = 0;
    }

	last_time= current_time;
}


 void idle ()
{
	
    glutPostRedisplay();
	calculateFPS();

}




 /* Callback handler for special-key event */
void specialKeys(int key, int x, int y) {
	int mod = glutGetModifiers();
   switch (key) {
      case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
         fullScreenMode = !fullScreenMode;         // Toggle state
         if (fullScreenMode) {                     // Full-screen mode
            windowPosX   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
            windowPosY   = glutGet(GLUT_WINDOW_Y);
            _WINDOW_WIDTH  = glutGet(GLUT_WINDOW_WIDTH);
            _WINDOW_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);
            glutFullScreen();                      // Switch into full screen
         } else {                                         // Windowed mode
            glutReshapeWindow(_WINDOW_WIDTH, _WINDOW_HEIGHT); // Switch into windowed mode
            glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
         }
         break;
	  case GLUT_KEY_RIGHT: 
		  if(mod == GLUT_ACTIVE_CTRL)
		  {
			  game_world.m_player->direction = glm::vec3(1.0f,0.0f,0.0f);
		  }
		   else{
			  game_world.m_player->move_right();
		  }
		   game_world.updatePF();
		  break;
	  case GLUT_KEY_LEFT:
		    if(mod == GLUT_ACTIVE_CTRL)
		  {
			  game_world.m_player->direction = glm::vec3(-1.0f,0.0f,0.0f);
		  }
		   else{
			  game_world.m_player->move_left();
		  }
		    game_world.updatePF();
		  break;
	  case GLUT_KEY_UP:
		    if(mod == GLUT_ACTIVE_CTRL)
		  {
			  game_world.m_player->direction = glm::vec3(0.0f,1.0f,0.0f);
		  }
		  else{
			  game_world.m_player->move_up();
		  }
		   game_world.updatePF();
		  break;
	  case GLUT_KEY_DOWN:
		  if(mod == GLUT_ACTIVE_CTRL)
		  {
			  game_world.m_player->direction = glm::vec3(0.0f,-1.0f,0.0f);
		  }
		   else{
			  game_world.m_player->move_down();
		  }
		    game_world.updatePF();
		  break;

   }
}

 void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:     // ESC key
         exit(0);
         break;
   }
}


 /* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   //glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);          // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);   // Set the window's initial width & height - non-square
	glutInitWindowPosition(windowPosX, windowPosY); // Position the window's initial top-left corner
	glutCreateWindow("Viewport Transform");  // Create window with the given title
    if(fullScreenMode)
	glutFullScreen();
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutIdleFunc(idle);	
	glutSpecialFunc(specialKeys); // Register callback handler for special-key event
	glutKeyboardFunc(keyboard);
	//glutTimerFunc(0, Timer, 0);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}