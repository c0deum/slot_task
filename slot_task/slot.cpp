#include <windows.h>
#include <Gl/gl.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "texture.h"
#include "slot.h"

static const int PART_SEGMENTS = 32;

Slot::Slot( Texture *texture, int parts )
: texture_( texture )
, parts_( parts )
, velocity_( 1.0f )
, currentAngle_( 0.0f )
, partAngle_( -180.0f / parts )
, pos_( 0.0f, 0.0f, 0.0f )
, state_( State_Stoped )
{
	//create verticies

	float partSize = static_cast< float >( 2.0f * M_PI / parts_ );
	float halfPartSize = 0.5f * partSize;

	int segments = parts * PART_SEGMENTS;

	for( int segment = 0; segment < segments; ++segment )
	{
		float partAngleBegin = static_cast< float >( 2.0f * M_PI / segments * segment );
		float partAngleEnd = static_cast< float >( 2.0f * M_PI / segments * ( ( segment + 1 ) % segments ) );


		vertecies_.push_back( Vec3( -halfPartSize, sin( partAngleBegin ), cos( partAngleBegin ) ) );
		vertecies_.push_back( Vec3( -halfPartSize, sin( partAngleEnd ), cos( partAngleEnd ) ) );
		vertecies_.push_back( Vec3( halfPartSize, sin( partAngleBegin ), cos( partAngleBegin ) ) );
		vertecies_.push_back( Vec3( halfPartSize, sin( partAngleEnd ), cos( partAngleEnd ) ) );

		texCoords_.push_back( Vec2( 0.0f, 1.0f * segment / segments ) );
		texCoords_.push_back( Vec2( 0.0f, 1.0f * ( segment + 1 ) / segments ) );

		texCoords_.push_back( Vec2( 1.0f, 1.0f * segment / segments ) );
		texCoords_.push_back( Vec2( 1.0f, 1.0f * ( segment + 1 ) / segments ) );
	}
}

void Slot::setVelocity( float velocity )
{
	velocity_ = velocity;
}

void Slot::setPosition( const Vec3 &pos )
{
	pos_ = pos;
}

SlotState Slot::state() const
{
	return state_;
}

void Slot::update( float dt )
{
	if( State_Rolling == state_ )
	{
		currentAngle_ += dt * velocity_ * 360.0f;
	}
}

void Slot::draw()
{
	texture_->bind();

	glEnable( GL_TEXTURE_2D );

	glPushMatrix();

	glRotatef( currentAngle_ + partAngle_ , 1.0f, 0.0f, 0.0f );

	glTranslatef( pos_.x, pos_.y, pos_.z );

	glColor3f( 1.0f, 1.0f, 1.0f );

	glBegin( GL_TRIANGLE_STRIP );
	for( int i = 0; i < parts_ * PART_SEGMENTS * 4; ++i )
	{
		glTexCoord2f( texCoords_[ i ].x, texCoords_[ i ].y );
		glVertex3f( vertecies_[ i ].x, vertecies_[ i ].y, vertecies_[ i ].z );
	}
	glEnd();

	glPopMatrix();

	glDisable( GL_TEXTURE_2D );
}

void Slot::roll()
{
	state_ = State_Rolling;
}

void Slot::stop()
{
	//calculate current part

	int angle = static_cast< int >( currentAngle_ );
	angle %= 360;
	currentAngle_ = ( 360.0f / parts_ ) * ( ( angle * parts_ / 360 ) ) ;

	state_ = State_Stoped;
}