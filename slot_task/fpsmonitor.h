#ifndef FPSMONITOR_H
#define FPSMONITOR_H

#include <string>

class FpsMonitor
{
public:

	static FpsMonitor& instance();

	void update( float dt );
	void draw( int windowWidth, int windowHeight );

private:
	FpsMonitor();
	FpsMonitor( const FpsMonitor& );
	FpsMonitor& operator=( const FpsMonitor& );

private:
	static FpsMonitor monitor_;

	int calls_;
	float time_;

	std::string text_;
};

#endif