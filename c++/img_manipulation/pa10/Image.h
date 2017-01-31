#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;  

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
	inline void fpixelReserve(int size){fpixels.reserve(size);}
	inline void setfPixelRow(vector<double> & row){fpixels.push_back(row);}


	//methods
	void avg(void);
        string input(void);
	int rescale(void); 
	int output(string outfile);
        string parseHeader(ifstream& istr);
	int parseComment(ifstream& istr);
	string binaryPGMParse(ifstream& istr);
	string asciiPGMParse(ifstream& istr);
	string maskPGMParse(ifstream& istr);

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
	double average;
};


//Non-member functions applicable to Image class
int find_the_cat(const Image & img, const Image & mask, Image & out);
int normalize(vector<vector<double>> & normalized, const Image & img, int left, int right, int upper, int lower);


#endif
