#define _USE_MATH_DEFINES
#include <cmath>

#include <windows.h>
#include <GL/gl.h>

#include "slotmachine.h"

static const float SLOTS = 5;
static const int PARTS = 9;
static const float ROLL_TIME = 3.0f;
static const float STOP_TIME = 0.5f;

SlotMachine::SlotMachine()
: state_( SMS_Stoped )
, texture_( "slot.bmp" )
, timeStart_( 0.0f )
, time_( 0.0f )
, stopedSlots_( 0 )
{
	for( size_t index = 0; index < SLOTS; ++index )
	{
		slots_.push_back( Slot( &texture_, PARTS ) );

		slots_[ index ].setPosition( Vec3( index * 1.0f, 0.0f, 0.0f ) );

		slots_[ index ].stop();
	}

	stopedSlots_ = slots_.size();
}

void SlotMachine::update( float dt )
{
	time_ += dt;

	//вращение
	if( SMS_Rolling == state_ )
	{
		if( time_ - timeStart_ > ROLL_TIME )
		{
			//stop all slots
			state_ = SMS_Stopping;
			timeStart_ = time_;
		}
	}
	//остановка
	else if( SMS_Stopping == state_ )
	{
		if( time_ - timeStart_ > STOP_TIME )
		{
			slots_[ stopedSlots_++ ].stop();
			timeStart_ = time_;

			if( slots_.size() == stopedSlots_ )
			{
				state_ = SMS_Stoped;
			}
		}
	}

	for( size_t index = 0; index < slots_.size(); ++index )
	{
		slots_[ index ].update( dt );
	}
}

void SlotMachine::draw()
{
	texture_.create();
	glPushMatrix();

	glTranslatef( -2.0f, 0.0f, 0.0f );
	
	for( size_t index = 0; index < slots_.size(); ++index )
	{
		slots_[ index ].draw();
	}
	glPopMatrix();
}

void SlotMachine::roll()
{
	if( SMS_Stoped == state_ )
	{
		timeStart_ = time_;
		stopedSlots_ = 0;
		state_ = SMS_Rolling;

		for( size_t index = 0; index < slots_.size(); ++index )
		{
			//от двух до 7 оборотов в секунду
			slots_[ index ].setVelocity( 2.0f + 0.05f * ( rand() % 100 ) );
			slots_[ index ].roll();
		}
	}
}

SlotMachineState SlotMachine::state() const
{
	return state_;
}