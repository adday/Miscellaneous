#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//IMAGE CLASS FOR ASCII .pgm FILES
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

	//mutators
	inline void setName(string fn){name = fn;}
	inline void setWidth(int w){width = w;}
	inline void setHeight(int h){height = h;}
	inline void setDeclared_max(int dm){declared_max = dm;}
	inline void setMax(int m){max = m;}
	inline void setMin(int m){min = m;}
	inline void setSize(long int s){size = s;}
	inline void setType(int t){type = t;}

	//methods
	void avg(void);
        string input(void);
	void rescale(void); 
	int output(string outfile);
        string parseHeader(ifstream& istr);
	int parseComment(ifstream& istr);
	string binaryParse(ifstream& istr);
	string asciiParse(ifstream& istr);

   private:
	string name;
	int width,height,declared_max,max,min,pixel,type;
        long int size;
	vector<int> pixels;
	double average;

};

#endif
