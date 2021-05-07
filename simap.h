#ifndef SIMAP_H
#define SIMAP_H
#include <vector>
#include <string>


struct point
{
	unsigned int _x;
	unsigned int _y;
	int _value;
	point(int x, int y, double value);
};

std::string parsedirectory(std::string filename);
std::string parsefilename(std::string filename);
void readimage(const char* filename, std::vector<point> &coor);
int recurse(const unsigned int& length, std::vector<point> &coor);
void printcoor(const std::vector<point> &coor);
void printgrid(const std::vector<point> &coor);
void convertgrey(const char* filename);
void outtext(const std::vector<point> &coor, std::string ofilename, std::string filename,
	unsigned int resolution, double lowrange, double highrange);





#endif