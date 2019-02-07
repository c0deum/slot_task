#ifndef SLOT_H
#define SLOT_H

#include <vector>
#include "vec3.h"
#include "vec2.h"

class Texture;

enum SlotState
{
	State_Stoped,	//����������
	State_Rolling,	//���������
};

class Slot
{
public:
	Slot( Texture *texture, int parts );

	void setVelocity( float velocity );

	void setPosition( const Vec3 &pos );

	SlotState state() const;
	
	void update( float dt );
	void draw();

	void roll();
	void stop();

private:
	Texture *texture_;
	int parts_;
	float velocity_;
	float currentAngle_;
	float partAngle_; //���� �������� - � �������� ���� ������� ������ �����

	Vec3 pos_;

	SlotState state_;
	
	std::vector< Vec3 > vertecies_;
	std::vector< Vec2 > texCoords_;
};

#endif