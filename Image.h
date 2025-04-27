
// This file contains the main class that provides drawing capabilities.
//
// Simple wrpper for a 2D image with the following functionality:
// * create a view area of given dimensions
// * set and retrieve the color of a pixel
// * save the view area as a PPM image

/* Sample use of this class:  
  
#include "canvas.h"

int main()
{
  Canvas canvas(200, 300);  // 2D region of width=200, height=300

                            // 0,0-------------->x ~ width
                            // |
			    // |          *
                            // |     x=150,y=100
                            // v
                            // y ~ height

  Color color(.5, .5, .5);

  canvas.setPixel(150, 100, color);

  canvas.saveImage("test.ppm");

  return 0;
}

*/

#ifndef CANVAS_H_
#define CANVAS_H_

#include "Color.h"

#include <string>

class Image
{
public:
	/**
	 * Creates a canvas of viewable area with range:
	 *     x in [0, w-1]
	 *     y in [0, h-1]
	 */
	Image(int w, int h);

	Image(string filename);

	/**
	 * Frees the storage used for various buffers.
	 */
	~Image();

	/**
	 * Returns the color of the pixel with the given coordinates (x, y).
	 */
	Color getPixel(int x, int y) const;

	Color getPixel(float x, float y) const;

	Color rgb_uv(float u, float v) const;
	float gray_uv(float u, float v) const;

	Color rgb_wh(float w, float h) const;
	float gray_wh(float w, float h) const;

	pair<float, float> gradient_uv(float u, float v) const;
	pair<float, float> gradient_wh(float w, float h) const;

	/**
	 * Sets the pixel with the given coordinates (x, y) to the given color c.
	 */
	void setPixel(int x, int y, const Color& c) const;

	/**
	 * Saves a PPM image (in raw, i.e.binary format) to a file with the given name.
	 */
	void saveImage(const std::string& file_name) const;

	/**
	 * Erases the canvas. The view area is set to black and border to gray.
	 */
	void clear();

private:
	/**
	 * Fills in the given color a rectangular region anchored at (w0, h0) and
	 * extending *width* units horizontally and *height* units vertically.
	 */
	void fillRegion(int w0, int h0, int width, int height, const Color& c) const;

	/**
	 * Reserves a 2D array for the color buffer of appropriate size (view + border).
	 */
	void makeCanvas();

	/**
	 * Frees the storage used for the color buffer.
	 */
	void destroyCanvas() const;

private:
	// the canvas dimensions
	int width;
	int height;

	// the color buffer
	Color **image;
}; 

#endif