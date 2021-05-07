#include <iostream>
#include "simap.h"
#include "EasyBMP/EasyBMP.h"
#include <math.h>
#include <iomanip>
//#include <string>
#include <fstream>

// using namespace std;

int main(int argc, char *argv[]){

	if(argc < 2){
		std::cout << "Please include the filename of the BMP image as a commandline argument" << std::endl;
		return 1;
	}
	if(argc > 2){
		std::cout << "Too many arguments" << std::endl;
		return 1;
	}

	std::string filename = argv[1];

	double lowrange = 60;
	double highrange = 10000;
	unsigned int resolution = 0;
	

	BMP Image;
	Image.ReadFromFile(filename.c_str());
	
	if(Image.TellWidth() != Image.TellHeight()) throw std::invalid_argument("image is not square");
	resolution = Image.TellWidth();

	std::vector<point> coor;
	
	bool ifcomplete = recurse(resolution, coor);	
	if(ifcomplete) throw std::runtime_error("hilbert: failed"); 

	readimage(filename.c_str(), coor);



	std::cout << std::endl << "Image successfully loaded!" << std::endl;
	std::cout << std::endl << "Commands:" << std::endl;
	std::cout << "DISPLAYGRID – to print out the pixel data in a 2D grid" << std::endl;
	std::cout << "DISPLAY – to print out the pixel data in the order of Hilbert's Curve" << std::endl;
	std::cout << "SAVE – to output the pixel data in the order of Hilbert's Curve to a txt file in the current directory" << std::endl;
	std::cout << "CONVERTGREY – to convert the input color image to a greyscale image" << std::endl;
	std::cout << "QUIT – to close the program" << std::endl << std::endl;
	std::cout << " $ ";

	std::string input;
	std::cin >> input;

	if(input == "DISPLAYGRID"){
		printgrid(coor);
	}
	else if(input == "DISPLAY"){
		printcoor(coor);
	}
	else if(input == "SAVE"){
		outtext(coor, "freqout.txt", filename, resolution, lowrange, highrange);
	}
	else if(input == "CONVERTGREY"){
		convertgrey(filename.c_str());	
	}
	else if(input == "QUIT"){
		return 0;
	}
	else{
		std::cout << "Error: invalid command" << std::endl;

	}



	return 0;

}

void outtext(const std::vector<point> &coor, std::string ofilename, std::string filename, unsigned int resolution, double lowrange,
	double highrange){

	if(coor.size()==0){
		std::cout << "Please read in the image first" << std::endl;
		return;
	}

	std::ofstream ofile(ofilename.c_str());
	ofile << "File: " << filename << " " << std::endl << "Dimensions: " << resolution << "x" 
		<< resolution << std::endl << "Frequency Range: " << lowrange << "-" << highrange << std::endl << std::endl;

	for(std::vector<point>::const_iterator it = coor.begin(); it!=coor.end(); ++it){
		ofile << it->_value << std::endl;
	}

	ofile.close();


}

void convertgrey(const char* filename){
	BMP Image;
	Image.ReadFromFile(filename);

	for(int j = 0; j < Image.TellHeight(); j++){
		for(int i = 0; i < Image.TellWidth(); i++){
			
			int temp = (int) floor( 0.299*Image(i, j)->Red + 
			0.587*Image(i, j)->Green + 
			0.114*Image(i, j)->Blue);
			ebmpBYTE TempBYTE = (ebmpBYTE) temp;
			Image(i, j)->Red = TempBYTE;
			Image(i, j)->Green = TempBYTE;
			Image(i, j)->Blue = TempBYTE;
		}
	}
	if(Image.TellBitDepth() < 16) CreateGrayscaleColorTable(Image);

	std::string greyscalename = "gs";
	std::string writefile = parsedirectory(filename) + greyscalename + parsefilename(filename);
	Image.WriteToFile(writefile.c_str());

}

std::string parsedirectory(std::string filename){

	int pos;

	for(size_t i = 0; i < filename.length(); i++){
		if (filename[i] == '/') pos = i;
	}

	filename.erase(filename.begin() + pos + 1,   filename.end());
	return filename;
}

std::string parsefilename(std::string filename){

	int pos;

	for(size_t i = 0; i < filename.length(); i++){
		if (filename[i] == '/') pos = i;
	}

	filename.erase(filename.begin() + 0,  filename.begin() + pos + 1);
	return filename;	

}

void readimage(const char* filename, std::vector<point> &coor){
	BMP Image;
	Image.ReadFromFile(filename);


	
	for(std::vector<point>::iterator it = coor.begin(); it!=coor.end(); ++it){
		int temp = (int) floor( 0.299*Image(it->_x,it->_y)->Red + 
			0.587*Image(it->_x,it->_y)->Green + 
			0.114*Image(it->_x,it->_y)->Blue);

		it->_value = temp;
	}


}

void printgrid(const std::vector<point> &coor){
	std::cout<< "   ";
	for(size_t i = 0; i<sqrt(coor.size()); i++){
		std::cout<< std::left << std::setw(3) << std::setfill(' ') << i;
	
	}
	std::cout << std::endl << std::endl;
	for(size_t i = 0; i<sqrt(coor.size()); i++){
		// std::cout<<i << " ";
		std::cout<< std::left << std::setw(3) << std::setfill(' ') << i;


		for(size_t j = 0; j<sqrt(coor.size()); j++){
			for(std::vector<point>::const_iterator it = coor.begin(); it!=coor.end(); ++it){
				if(it->_x == j && it->_y == i){
					// std::cout<<it->_value << "        ";
					std::cout<< std::left << std::setw(3) << std::setfill(' ') << it->_value;
				}
				//**runtime can be improved by deleting the coordinates already printed here
			}
	
		}
		std::cout<<std::endl;

	
	}


}

void printcoor(const std::vector<point> &coor){
	std::cout<<"x, y   value" << std::endl;
	for(std::vector<point>::const_iterator it = coor.begin(); it!=coor.end(); ++it){
		std::cout << it->_x << ", " << it->_y << "   " << it->_value << std::endl;

	}	
}

int recurse(const unsigned int& length, std::vector<point> &coor){
	bool ifcomplete;
	if(coor.size() == (unsigned)(length*length)) return 0;
	else if(coor.size() > (unsigned)(length*length)) return 1;
	else if(coor.size() == 0){
		point point1(0, 1, 0);
		coor.push_back(point1);

		point point2(0, 0, 0);
		coor.push_back(point2);

		point point3(1, 0, 0);
		coor.push_back(point3);

		point point4(1, 1, 0);
		coor.push_back(point4);

		ifcomplete = recurse(length, coor);
	}
	else{

		std::vector<point> bl; //bottom left
		std::vector<point> tr(coor); //top right
		std::vector<point> br; //bottom right

		//initialize top right
		for(std::vector<point>::iterator it = tr.begin(); it!=tr.end(); ++it){
			it->_x += sqrt(tr.size());
		}
		
		//initialize bottom right
		for(std::vector<point>::iterator it = coor.begin(); it!=coor.end(); ++it){


			int newx = (it->_y) + sqrt(coor.size());
			int newy = (it->_x) + sqrt(coor.size());

			point temp(newx, newy, 0.0);
			br.push_back(temp);
		}

		//initialize bottom left
		for(std::vector<point>::iterator it = br.begin(); it!=br.end(); ++it){

			int newx = (2*sqrt(coor.size())-1) - it->_x;
			int newy = it->_y;


			point temp(newx, newy, 0.0);
			bl.insert(bl.begin(), temp);
		}
 
		coor.insert(coor.begin(), bl.begin(), bl.end());
		coor.insert(coor.end(), tr.begin(), tr.end());
		coor.insert(coor.end(), br.begin(), br.end());



		ifcomplete = recurse(length, coor);
	}

 	if(!ifcomplete) return 0;
 	else return 1;
}



point::point(int x, int y, double value) : 
_x(x), _y(y), _value(value)
{}
