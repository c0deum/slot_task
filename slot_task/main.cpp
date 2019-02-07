#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ctime>

#include "external/glut.h"

#include "fpsmonitor.h"
#include "button.h"
#include "slotmachine.h"

#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "GLAUX.lib")

static int windowWidth = 1024;
static int windowHeight = 600;

static const char WINDOW_TITLE[] = "Slot Task";

SlotMachine slotMachine;
Button buttonStart( "Press Space to Start" );

void init();
void display();
void reshape( int width, int height );
void idle();
void keyboard( unsigned char key, int x, int y );
void mouse( int button, int state, int x, int y );

void draw3d();
void draw2d();

int main( int argc, char* argv[] )
{
	srand( time( 0 ) );

	glutInit( &argc, argv );

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

	glutInitWindowSize( windowWidth, windowHeight );
	glutInitWindowPosition( ( glutGet( GLUT_SCREEN_WIDTH ) - windowWidth ) / 2, ( glutGet( GLUT_SCREEN_HEIGHT ) - windowHeight ) / 2 );
	
	glutCreateWindow( WINDOW_TITLE );

	init();

	glutDisplayFunc( display );	
	glutReshapeFunc( reshape );
	glutIdleFunc( idle );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	
	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor( 0.0f, 0.5f, 0.0f, 1.0f );

	buttonStart.setPosition( Vec2( windowWidth * 0.5f, 16.0f ) );
	buttonStart.enable( true );
}

void display()
{
	glClear( GL_COLOR_BUFFER_BIT );

	draw3d();

	draw2d();

	glutSwapBuffers();
}

void reshape( int width, int height )
{
	windowWidth = width;
	windowHeight = height;

	glViewport( 0, 0, windowWidth, windowHeight );

	buttonStart.setPosition( Vec2( windowWidth * 0.5f, 16.0f ) );
}

void idle()
{
	static GLuint oldTime = glutGet( GLUT_ELAPSED_TIME );
	GLuint time = glutGet( GLUT_ELAPSED_TIME );
	
	float dt = 0.001f * ( time - oldTime );

	slotMachine.update( dt );

	buttonStart.enable( SMS_Stoped == slotMachine.state() );

	buttonStart.update( dt );
	FpsMonitor::instance().update( dt );

	oldTime = time;

	glutPostRedisplay();
}

void draw3d()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective( 45,( windowHeight == 0 ) ? 1.0: ( 1.0 * windowWidth / windowHeight ), 1, 10);
	glOrtho( -2.5f, 2.5f, -2.0f, 2.0f, 1, 4 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt( 0, 0, 4, 0, 0, 0, 0, 1, 0 );

	slotMachine.draw();
}

void draw2d()
{			
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0.0, windowWidth, 0.0, windowHeight );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	buttonStart.draw();
	FpsMonitor::instance().draw( windowWidth, windowHeight );
}

void keyboard( unsigned char key, int x, int y )
{
 	if( ' ' == key )
	{
		slotMachine.roll();
	}
}

void mouse( int button, int state, int x, int y )
{
	if( GLUT_DOWN != state )
		return;
	if( GLUT_LEFT_BUTTON != button )
		return;
	
	float left = buttonStart.position().x - buttonStart.size().x * 0.5f;
	float right = buttonStart.position().x + buttonStart.size().x * 0.5f;
	float top = windowHeight - ( buttonStart.position().y - buttonStart.size().y * 0.5f );
	float bottom = windowHeight - ( buttonStart.position().y + buttonStart.size().y * 0.5f );

	if( ( x >= left ) && ( x <= right ) && ( y <= top ) && ( y >= bottom ) )
	{
		slotMachine.roll();
	}
}