#include "WorldBuilder.h"
#include "World.h"
#include <iostream>

using namespace std;

const int BLACK = 0;
const int WHITE = 255;

WorldPtr WorldBuilder::fromImage(std::string path)
{
	CImg<int> img(path.c_str());

	//	int depth = src.depth();
	//	int channels = src.spectrum();
	//
	//	cout << "Size of the image: " << width << "x" << height << "\n";
	//	cout << "Image depth: " << depth << "\n"; //typically equal to 1 when considering usual 2d images
	//	cout << "Number of channels: " << channels << "\n"; //3 for RGB-coded color images
	//

	int width = img.width();
	int height = img.height();

	int min_X = -1;
	int max_X = -1;
	int min_Y = -1;
	int max_Y = -1;
	int numberOfPoints = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int pixel = (int)img.atXY(i, j);

			if (WHITE != pixel) {
				numberOfPoints++;

				if (-1 == min_X) {
					min_X = i;
				}
				else {
					if (i > max_X) {
						max_X = i;
					}
				}

				if (-1 == min_Y) {
					min_Y = j;
				}
				else {
					if (j > max_Y) {
						max_Y = j;
					}
				}
			}
		}
	}

	cout << width << " - " << height << endl;
	cout << min_X << " - " << max_X << endl << min_Y << " - " << max_Y << endl;

	//CImg<unsigned char> bla(max_X - min_X + 1, max_Y - min_Y + 1);

	PointList pointList;

	for (int i = min_X; i <= max_X; i++) {
		for (int j = min_Y; j <= max_Y; j++) {
			int pixel = (int)img.atXY(i, j);

			//(*bla.data(i - min_X, j - min_Y)) = pixel;

			if (WHITE != pixel) {
				//cout << i - min_X << " - " << j - min_Y << endl;
				pointList.push_back(Point(i - min_X, j - min_Y));
			}
		}
	}
	
	//new CImgDisplay(bla);

	return WorldPtr(new World(pointList, max_X-min_X+1, max_Y-min_Y+1));
}

shared_ptr<CImg<unsigned char>> WorldBuilder::toImage(WorldPtr world)
{
	shared_ptr<CImg<unsigned char>> img(new CImg<unsigned char>(world->getWidth(), world->getHeight()));

	for each (const Point& point in world->getPointList()) {
		(*img->data(point.getX(), point.getY())) = BLACK;
	}

	return img;

}
