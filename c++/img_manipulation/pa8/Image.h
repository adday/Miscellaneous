#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// provides helper functionality for color Images
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

// images: ascii or binary format .pgm, .ppm files
// masks: ascii or binary format .pgmm masks
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
        inline int getColor(int x, int y, int color) const{if(color == 1) return colors.at(y).at(x).getRed();
											     if(color == 2) return colors.at(y).at(x).getGreen();
											     if(color == 3) return colors.at(y).at(x).getBlue();
											     else return 0;}
	inline vector<vector<double>> getMask() const{return mask;}
	inline int getMaskVal(int  x,int y) const{return mask.at(y).at(x);}

	//mutators
	inline void setName(string fn){name = fn;}
	inline void setWidth(int w){width = w;}
	inline void setHeight(int h){height = h;}
	inline void setDeclared_max(int dm){declared_max = dm;}
	inline void setMax(double m){max = m;}
	inline void setMin(double m){min = m;}
	inline void setSize(long int s){size = s;}
	inline void setType(int t){type = t;}
	inline void setPixels(vector<vector<int>> pix){pixels = pix;};
	inline void setPixel(int x, int y, int pixVal){pixels.at(y).at(x) = pixVal;}
	inline void pixelReserve(int size){pixels.reserve(size);}
	inline void setPixelRow(vector<int> & row){pixels.push_back(row);}
	inline void setColors(vector<vector<RGBPixel>> c){colors = c;}
	inline void setColor(int x,int y, RGBPixel rgb){colors.at(y).at(x) = rgb;}
	inline void colorReserve(int size){colors.reserve(size);}
	inline void setColorRow(vector<RGBPixel> & row){colors.push_back(row);}
	inline void fpixelReserve(int size){fpixels.reserve(size);}
	inline void setfPixelRow(vector<double> & row){fpixels.push_back(row);}


	//methods
	void avg(void);
        string input(void);
	int rescale(void); 
	int output(string outfile);
	int colorOutput(string outfile);
        string parseHeader(ifstream& istr);
	int parseComment(ifstream& istr);
	string binaryPGMParse(ifstream& istr);
	string asciiPGMParse(ifstream& istr);
	string binaryPPMParse(ifstream& istr);
	string asciiPPMParse(ifstream& istr);
	string maskPGMParse(ifstream& istr);
    	int matchSize(Image img);
	void compare(Image img1,Image img2);
	int colorRescale(void);

	//overloaded operators
	Image & operator=(const Image& rhs);

   private:
	string name;
	int width,height,declared_max,pixel,type;
	double maskVal, max, min;
        long int size;
	vector< vector<int> > pixels;
	vector<vector<double>> mask;
	vector<vector<double>> fpixels;
	vector< vector<RGBPixel> > colors;
	double average;
};

//Non-member functions applicable to Image class
int detectEdges(const Image & img, Image & E);
int detectColorEdges(const Image & img, Image & E);
int convolution(const Image & img, const  Image & mask, Image & out);

#endif
