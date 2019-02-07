#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "vec2.h"

class Button
{
public:
	Button( const std::string &text = std::string(), const Vec2 &position = Vec2() );

	void setPosition( const Vec2 &position );

	void update( float dt );
	void draw();

	void enable( bool flag );

	const Vec2& size() const;

	const Vec2& position() const;

private:
	std::string text_;
	Vec2 pos_;
	Vec2 size_;
	float alpha_;
	float deltaSign_;
	bool enabled_;
};
//TODO: callback for mouse
#endif