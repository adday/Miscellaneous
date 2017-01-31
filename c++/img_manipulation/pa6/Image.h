#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class RGBPixel{
  public:
	RGBPixel(int r,int b,int g){red = r;blue = b;green = g;}
	//accessors
	inline int getRed() const{return red;}	
	inline int getGreen() const{return green;}	
	inline int getBlue() const{return blue;}	
	//mutators
	inline void setRed(int r){red = r;} 
	inline void setGreen(int g){green = g;} 
	inline void setBlue(int b){blue = b;} 

  private:
	int red,blue,green;
};

// images: ascii or binary format .pgm files
class Image{
   public:
	Image(string filename){name = filename;}

	//accessors
	inline string getName() const{return name;}
 	inline int getWidth() const{return width;}
	inline int getHeight() const{return height;}
	inline int getDeclared_max() const{return declared_max;};
	inline int getMax() const{return max;}
	inline int getMin() const{return min;}
	inline long int getSize() const{return size;}
	inline double getAverage() const{return average;}
	inline int getType() const{return type;}
	inline vector<vector<int>> getPixels() const{return pixels;}
	inline int getPixel(int x, int y) const{if( (x>=width) || (x<0)||//if pixel is out of range return 0
									      (y>=height) || (y<0) ){return 0;}
									  return pixels.at(y).at(x);} //else return pixel value
	inline vector<vector<RGBPixel>> getColors() const{return colors;}

	//mutators
	inline void setName(string fn){name = fn;}
	inline void setWidth(int w){width = w;}
	inline void setHeight(int h){height = h;}
	inline void setDeclared_max(int dm){declared_max = dm;}
	inline void setMax(int m){max = m;}
	inline void setMin(int m){min = m;}
	inline void setSize(long int s){size = s;}
	inline void setType(int t){type = t;}
	inline void setPixels(vector<vector<int>> pix){pixels = pix;};
	inline void setPixel(int x, int y, int pixVal){pixels.at(y).at(x) = pixVal;}
	inline void setColors(vector<vector<RGBPixel>> c){colors = c;}
	inline void setColor(int x,int y, RGBPixel rgb){colors.at(y).at(x) = rgb;}

	//methods
	void avg(void);
        string input(void);
	int rescale(void); 
	int output(string outfile);
        string parseHeader(ifstream& istr);
	int parseComment(ifstream& istr);
	string binaryPGMParse(ifstream& istr);
	string asciiPGMParse(ifstream& istr);
	string binaryPPMParse(ifstream& istr);
	string asciiPPMParse(ifstream& istr);
    	int matchSize(Image img);
	void compare(Image img1,Image img2);

	//overloaded operators
	Image & operator=(const Image& rhs);

   private:
	string name;
	int width,height,declared_max,max,min,pixel,type;
        long int size;
	vector< vector<int> > pixels;
	vector< vector<RGBPixel> > colors;
	double average;
};

//Non-member functions applicable to Image class
int detectEdges(const Image & img, Image & E);

#endif
