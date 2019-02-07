#include "external/glut.h"
#include "utils.h"

int textWidth( void *font, const char *text )
{
	int width = 0;
	while( *text )
	{
		width += glutBitmapWidth( font, *text );
		++text;
	}
	return width;
}

void drawText( void *font, const char *text )
{
	while( *text )
	{
		glutBitmapCharacter( font, *text );
		++text;
	}
}