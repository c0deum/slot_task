#include <windows.h>
#include <Gl/gl.h>
#include "external/glaux.h"

#include "texture.h"

Texture::Texture( const std::string &fileName )
: fileName_( fileName )
, id_( 0 )
, created_( false )
{
}

void Texture::bind()
{
	if( !created_ )
		create();
	glBindTexture( GL_TEXTURE_2D, id_ );
}

void Texture::create()
{
	if( !created_ )
	{
		AUX_RGBImageRec *texture = auxDIBImageLoadA( fileName_.c_str() );
		glGenTextures( 1, &id_ );
		glBindTexture( GL_TEXTURE_2D, id_ );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		glTexImage2D( GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data );

		created_ = true;
	}
}

