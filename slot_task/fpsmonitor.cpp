#include <sstream>
#include <windows.h>
#include <Gl/gl.h>
#include <Gl/glu.h>
#include "external/glut.h"

#include "utils.h"
#include "fpsmonitor.h"

static const float LIMIT = 1.0f;

FpsMonitor FpsMonitor::monitor_;

FpsMonitor& FpsMonitor::instance()
{
	return monitor_;
}

FpsMonitor::FpsMonitor()
: calls_( 0 )
, time_( 0 )
, text_()
{
}

void FpsMonitor::update( float dt )
{
	time_ += dt;
	if( time_ > LIMIT )
	{
		std::ostringstream oss;

		oss << "FPS: " << calls_; 
		text_ = oss.str();

		calls_ = 0;
		time_ -= LIMIT;
	}
	calls_++;
}

void FpsMonitor::draw( int windowWidth, int windowHeight )
{
	glColor3f( 1.0f, 1.0f, 0.0f );

	glRasterPos2f( windowWidth - textWidth( GLUT_BITMAP_TIMES_ROMAN_10, text_.c_str() ), 10 );

	drawText( GLUT_BITMAP_TIMES_ROMAN_10, text_.c_str() );
}