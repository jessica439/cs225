#ifndef IMAGE_H
#define IMAGE_H
#include "png.h"
class Image: public PNG
{
public:
	//flips the image left
	void flipleft();
	//adjusts the image brightness by the given rgb values
	void adjustbrightness(int r, int g, int b);
	//inverts the colors of the image
	void invertcolors();
};
#endif
