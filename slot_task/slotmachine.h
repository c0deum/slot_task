#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include <vector>

#include "texture.h"
#include "button.h"
#include "fpsmonitor.h"
#include "slot.h"

enum SlotMachineState
{
	SMS_Stoped,		//�����������
	SMS_Rolling,	//���������
	SMS_Stopping	//���������������
};

class SlotMachine
{
public:
	SlotMachine();

	void update( float dt );

	void draw();

	void roll();

	SlotMachineState state() const;

private:
	SlotMachineState state_;
	Texture texture_;
	float timeStart_;
	float time_;
	size_t stopedSlots_;
	std::vector< Slot > slots_;

};

#endif