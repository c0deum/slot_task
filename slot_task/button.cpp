#include <windows.h>
#include <Gl/gl.h>
#include <GL/glu.h>

#include "external/glut.h"

#include "utils.h"

#include "button.h"

static const float HALF_TEXT_HEIGHT = 12.0f;
static const float HEIGHT_SHIFT = 0.25f * HALF_TEXT_HEIGHT; 

Button::Button( const std::string &text, const Vec2 &position )
: text_( text )
, pos_( position )
, size_( Vec2( textWidth( GLUT_BITMAP_TIMES_ROMAN_24, text_.c_str() ), 2.0f * ( HALF_TEXT_HEIGHT + HEIGHT_SHIFT ) ) )
, alpha_( 0.0f )
, deltaSign_( 1.0f )
, enabled_( false )
{

}

void Button::setPosition( const Vec2 &position )
{
	pos_ = position;
}

void Button::update( float dt )
{
	if( enabled_ )
	{
		alpha_ += deltaSign_ * dt;
		if( alpha_ > 1.0f )
		{
			alpha_ = 1.0f;
			deltaSign_ = -1.0f;
		}
		else if( alpha_ < 0.0f )
		{
			alpha_ = 0.0f;
			deltaSign_ = 1.0f;
		}
	}
}

void Button::draw()
{
	if( enabled_ )
	{
		float halfTextWidth = textWidth( GLUT_BITMAP_TIMES_ROMAN_24, text_.c_str() ) * 0.5f;

		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_BLEND );

		glColor4f( 1.0f, 1.0f, 0.0f, alpha_ );

		glBegin( GL_LINES );
			glVertex2f( pos_.x - halfTextWidth, pos_.y + HALF_TEXT_HEIGHT + HEIGHT_SHIFT );
			glVertex2f( pos_.x + halfTextWidth, pos_.y + HALF_TEXT_HEIGHT + HEIGHT_SHIFT );

			glVertex2f( pos_.x - halfTextWidth, pos_.y - HALF_TEXT_HEIGHT - HEIGHT_SHIFT );
			glVertex2f( pos_.x + halfTextWidth, pos_.y - HALF_TEXT_HEIGHT - HEIGHT_SHIFT );
		glEnd();

		glRasterPos2f( pos_.x - halfTextWidth, pos_.y - HALF_TEXT_HEIGHT + 2.0f * HEIGHT_SHIFT );

		drawText( GLUT_BITMAP_TIMES_ROMAN_24, text_.c_str() );
	
		glDisable( GL_BLEND );
	}
}

void Button::enable( bool flag )
{
	enabled_ = flag;

	if( !enabled_ )
	{
		alpha_ = 0.0f;
		deltaSign_ = 1.0f;
	}
}

const Vec2& Button::size() const
{
	return size_;
}

const Vec2& Button::position() const
{
	return pos_;
}
