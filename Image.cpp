#include "Image.h"
#include "Color.h"

#include <algorithm>
#include <string>
#include <ostream>
#include <fstream>
#include <cassert>

using uchar = unsigned char;

void Image::setPixel(int w, int h, const Color& c) const
{
	image[h][w] = c;
}


Color Image::getPixel(int w, int h) const
{
	// h = (h + height) % height;
	// w = (w + width) % width;
	
	// return image[h][w];

	h = ((h % height) + height) % height;
	w = ((w % width) + width) % width;

	return image[h][w];
}

Color Image::getPixel(float w, float h) const {
	int x = floor(w);
	int y = floor(h);
    
    float i0 = w - x;
    float i1 = 1 - i0;
    
    float j0 = h - y;
    float j1 = 1 - j0;
    
    Color UL = getPixel(x, y);     
    Color UR = getPixel(x + 1, y);   
    Color LL = getPixel(x, y + 1);     
    Color LR = getPixel(x + 1, y + 1);   

    Color C1 = j1 * UL + j0 * LL;
    Color C2 = j1 * UR + j0 * LR;
    
    return i0 * C2 + i1 * C1;
}

Color Image::rgb_uv(float u, float v) const {
	// return getPixel(width * u, height * v);
	return rgb_wh(width * u, height * v);
}

float Image::gray_uv(float u, float v) const {
	// Color color = rgb_uv(u, v);
	// return color.gray();
	return gray_wh(width * u, height * v);
}

Color Image::rgb_wh(float w, float h) const {
	return getPixel(w, h);
}

float Image::gray_wh(float w, float h) const {
	Color color = getPixel(w, h);
	return color.gray();
}

pair<float, float> Image::gradient_uv(float u, float v) const {
	return gradient_wh(u * width, v * height); 
}

pair<float, float> Image::gradient_wh(float w, float h) const {
	Color ui = getPixel(w + 1, h);
	Color li = getPixel(w - 1, h);

	Color uj = getPixel(w, h + 1);
	Color lj = getPixel(w, h - 1);

	float du = (ui.gray() - li.gray()) / 2;
	float dv = (uj.gray() - lj.gray()) / 2;

	return {du, dv}; 
}

Image::Image(int width, int height)
  :
  width(width),
  height(height)
{
	makeCanvas();
	clear();
}

Image::Image(string filename) {
	std::ifstream ifs(filename.c_str(), std::ios::binary);

	string str;
	float colorRange;

	ifs >> str;
	ifs >> width >> height;
	ifs >> colorRange;

	makeCanvas();

	ifs.ignore(1024, '\n'); 
	ifs >> noskipws;

	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			uchar r, g, b;
			ifs >> r >> g >> b;

			Color color(r / colorRange, g / colorRange, b / colorRange);
			setPixel(x, y, color);
		}
	}
}


Image::~Image() 
{
	destroyCanvas();
}


void Image::clear()
{
	//set the whole canvas to black
	fillRegion(0, 0, width, height, BLACK);
}


void Image::saveImage(const std::string& file_name) const
{
	std::ofstream ofs(file_name.c_str(), std::ios::binary);

	// write the header information
	ofs << "P6" << std::endl;
	ofs << width << "\t" << height << std::endl;
	ofs << 255 << std::endl;

	// save the image data one row at a time
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			Color c = getPixel(x, y);
			ofs << uchar(255*c.r()) << uchar(255*c.g()) << uchar(255*c.b());
		}
	}
}


void Image::fillRegion(int w0, int h0, int width, int height, const Color& c) const
{
	int w1 = w0 + width;
	int h1 = h0 + height;

	for(int y = h0; y < h1; ++y) {
		for(int x = w0; x < w1; ++x) {
			setPixel(x, y, c);
		}
	}
}


void Image::makeCanvas()
{
	image = new Color*[height];
	for(int h = 0; h < height; ++h) {
		image[h] = new Color[width];
	}
}


void Image::destroyCanvas() const
{
	for(int h = 0; h < height; ++h) {
		delete [] image[h];
	}
	delete [] image;
}