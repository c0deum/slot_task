#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
	Texture( const std::string &fileName );

	void create();

	void bind();
private:
	std::string fileName_;
	unsigned int id_;
	bool created_;
};

#endif