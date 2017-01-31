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
	inline string getName(){return name;}
 	inline int getWidth(){return width;}
	inline int getHeight(){return height;}
	inline int getDeclared_max(){return declared_max;};
	inline int getMax(){return max;}
	inline int getMin(){return min;}
	inline long int getSize(){return size;}
	inline double getAverage(){return average;}

	//mutators
	inline void setName(string fn){name = fn;}
	inline void setWidth(int w){width = w;}
	inline void setHeight(int h){height = h;}
	inline void setDeclared_max(int dm){declared_max = dm;}
	inline void setMax(int m){max = m;}
	inline void setMin(int m){min = m;}
	inline void setSize(long int s){size = s;}

	//methods
	void avg(void);
        string input(void);
	void rescale(void); 
	string output(string outfile);

   private:
	string name;
	int width,height,declared_max,max,min,pixel;
        long  int size;
	vector<int> pixels;
	double average;

};

#endif
