#include <Image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "omp.h"
using namespace std;

//====================non-member functions=========================
int find_the_cat(const Image & img, const Image & mask, Image & out){
  if(mask.getWidth() > img.getWidth() || mask.getHeight() > img.getHeight())
	return -1;//convolution will fail 
  if(mask.getMax() == mask.getMin())
	return -1;//normalization will fail
  vector<vector<double>> normal_mask;
  if(normalize(normal_mask,mask,0,mask.getWidth(),0,mask.getHeight()) == -1)
	return -1;//mask normalization failed
  double max = -10000, min = 10000;
  out.setType(img.getType());
  out.setHeight(img.getHeight() - mask.getHeight() + 1);
  out.setWidth(img.getWidth() - mask.getWidth() + 1);
  out.setSize(out.getHeight() * out.getWidth());
  out.fpixelReserve(out.getHeight());
  for(int y=0;y<out.getHeight();y++){
	vector<double> row;
	row.reserve(out.getWidth());
	for(int x=0;x<out.getWidth();x++){
		double fpixel = 0;
		vector<vector<double>> normal_img_region;
		normalize(normal_img_region, img,x,x+mask.getWidth(),y,y+mask.getHeight());
		for(int q=0;q<mask.getHeight();q++){
			for(int p=0;p<mask.getWidth();p++){
				fpixel += normal_mask.at(q).at(p)  * normal_img_region.at(q).at(p);}}
		row.push_back(fpixel);
		min = min < fpixel?min:fpixel;
		max = max > fpixel?max:fpixel;
	}//end for width
	out.setfPixelRow(row);	
  }//end for height
  out.setMax(max);
  out.setMin(min);
  return out.rescale();//success
}//end find_the_cat

//normalizes the region denote by the left to right limits and
//the upper to lower limits (right/lower is exclusive) [upper,lower,left,right correspond to visual dimension]
int normalize(vector<vector<double>> & normalized, const Image & img, int left, int right, int upper, int lower){
  //compute region average and store pixels into return vector for manipulation
  double sum,average;
  sum = 0;
  int width = right-left;
  int height = lower-upper;
  int size = width * height;
  normalized.reserve(height);
  for (int j=upper;j<lower;j++){
	vector<double> row;
	row.reserve(width);
	for(int i=left;i<right;i++){
		if(img.getType() == 0){//mask
			sum+= img.getMaskVal(i,j);
			row.push_back(img.getMaskVal(i,j));}
		else{
			sum+= img.getPixel(i,j);
			row.push_back(img.getPixel(i,j));}
  			}//end for left->right
	normalized.push_back(row);
		}//end for upper->lower
  average = sum / size;
  //compute M1(i,j)
  //subtract average and compute sum for magnitude computation
  sum = 0;
  for(int i=0;i<height;i++)
	for(int j=0;j<width;j++){
		normalized.at(i).at(j) = normalized.at(i).at(j) - average;
		sum += normalized.at(i).at(j) * normalized.at(i).at(j);}
  double magnitude = sqrt(sum);
  //if magnitude is 0 division fails -> set all pixels to 0 and return
  if(magnitude == 0){
	if(img.getType() == 0)
		return -1;//will be an all zero mask
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			normalized.at(i).at(j) = 0;
	}
  //compute M2(i,j)
  else
  	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			normalized.at(i).at(j) = normalized.at(i).at(j) / magnitude;
  return 0;
}//end normalize




//=======================class methods==========================

//operator = for assignment
Image& Image::operator=(const Image& rhs){
  name = rhs.getName();
  type = rhs.getType();
  height = rhs.getHeight();
  width = rhs.getWidth();
  declared_max = rhs.getDeclared_max();
  size = rhs.getSize();
  pixels = rhs.getPixels();
  avg();//complete fields min,max and average
  return *this;
}//end operator =





//Returns 0 for successful resize
//        -1 error: if min == max formula fails
int Image::rescale(void){
 //handles rescale for pixels represented as both ints and doubles
 //as pixels could have been stored as either doubles or ints
 if(pixels.size() != 0){
	 if(max == min)
		return -1;
 	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			pixels.at(i).at(j)=rint((255.0*static_cast<double>(pixels.at(i).at(j)-min)/(max-min))); 
 	min = 0;
	max = 255;}
 else{
 	if(max - min < 0.0000001)
		return -1;
	pixels.reserve(height);
	 for(int i=0;i<height;i++){
		vector<int> row;
		row.reserve(width);
		for(int j=0;j<width;j++)
	  		row.push_back(rint(255.0*(fpixels.at(i).at(j)-min)/(max-min))); 
		pixels.push_back(row);
	}//end outer for
	min = 0;
 	max = 255;}
 return 0;
}//end rescale






void Image::avg(void){
  int sum;
  min = 255;
  max = sum = 0;
  for (int i=0;i<height;i++)
	for(int j=0;j<width;j++){
		min = min < pixels.at(i).at(j)?min:pixels.at(i).at(j);
		max = max > pixels.at(i).at(j)?max:pixels.at(i).at(j);
		sum+= pixels.at(i).at(j);
  	}
  average = (double) sum / size;
}//end avg




//writes image to a pgm file
int Image::output(string outfile){   
  ofstream ostr(outfile.c_str());
  if(ostr.fail()){//ensure the file is valid to write 
    	return 1;
	}
  if(type ==  2 || type  == 3){//print ASCII
	ostr<<"P2\n"<<width<<" "<<height<<"\n255"<<endl;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			ostr<<pixels.at(i).at(j)<<" ";
	ostr<<endl;
  	return 0;}
  else{//print binary
	ostr<<"P5\n"<<width<<" "<<height<<"\n255"<<endl;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		     ostr.write(reinterpret_cast<const char*>(&pixels.at(i).at(j)), 1);
	return 0;}
}//end output



//Determine format of image file to be parsed and pass accordingly
//to function for further parsing
string Image::input(void)
{
  //test file opening
  ifstream istr(name.c_str());
  char junkc;
  //retrieve first line and check formatting
  istr.get();
  istr.get(junkc);
  if(junkc == '2'){
	type = 2;//P2 ASCII pgm
        istr.get(junkc);
	if(junkc == 'M') type = 0;//pgm mask
        else istr.putback(junkc);
 	}
  else if(junkc == '5')
	type = 5;//P5 binary pgm
  else
	return "Second character is incorrect";
  //so far so good...now parse header of image file
  string parseH = parseHeader(istr);//store for possible return
  if(parseH != "success")
	return parseH;
  //Now parse data section
  if(type == 0)//.pgmm mask
	return maskPGMParse(istr);
  else if(type == 2)//ASCII .pgm
	return asciiPGMParse(istr);
  else//binary .pgm
	return binaryPGMParse(istr);
}//end input




string Image::parseHeader(ifstream& istr){
  char junkc;
  if(parseComment(istr))
	return "Formatting not correct in header";
  istr>>width;
  //parse comments and parse height
  if(parseComment(istr))
	return "Formatting not correct in header";
  istr>>height;
  size = width * height;//compute total pixels
  //height is now parsed and valid
  //parse comments and declared max
  if(parseComment(istr))
	return "Formatting not correct in header";
  if(!(istr>>declared_max))
	return "Failed to parse declared max";
  if(declared_max > 255 || declared_max < 0)
	return "Invalid value for declared max";
  istr.get(junkc);
  if(junkc != '\n')
	return "Newline does not immediately follow declared max";
  return "success";
}//end parseHeader




//initial condition: istr points at first whitespace 
// after last successful read in
//post condition: returns 1 for fail in formatting
//	  	  returns 0 for success
int Image::parseComment(ifstream& istr){
  char junkc; 
  string junks;
  bool newline = false;
  if (istr.fail()) 
	return 1;
  istr.get(junkc);
  while(isspace(junkc) && !istr.eof()){
	if(junkc == '\n')//check if newline character
		newline = true;//indicate not on same line
 	if(isdigit(junkc))
		break;
	istr.get(junkc); 
  }
  if(newline == false && !isdigit(junkc))
	return 1; 
  //line is valid, comments now valid so parse them out
  while(junkc == '#' && !istr.eof()){
	  getline(istr,junks);
	  istr>>junkc;}
  istr.putback(junkc);//put back non-# character for next parse
  return 0;
}//end parseComment



//Parse a pgm binary formatted image and returns "success"
//If fails returns the reason why
string Image::binaryPGMParse(ifstream& istr){
  //no commments past this point
  //clear whitespace and check for newline
  int pixel = 0;
  pixels.reserve(height);
  for(int i = 0; i < height; i++){
	vector<int> row;
	row.reserve(width);
	for(int j = 0; j < width; j++){
	    istr.read((char*)&pixel,1);
	    //valid pixel so add to vector
	    row.push_back(pixel);
	  	}
	pixels.push_back(row);	
	}
  avg();//intializes min and max and avg completing data fields for new image
  return "success";
}//end binaryPGMParse



//Parse a pgm ASCII formatted image and return "success"
//If fails returns the reason why
string Image::asciiPGMParse(ifstream& istr){
  //parse pixels
  pixels.reserve(height);
  for (int i = 0; i < height; i++)
	{	
	vector<int> row;
	row.reserve(width);
	for(int j = 0; j < width; j++) 
  		{ 
    		istr >> pixel;
    		//valid pixel so add to vector
    		row.push_back(pixel);
  		}
	pixels.push_back(row);	
	}//end parsing declared amount of pixels
  avg();//intializes min and max and avg completing data fields for new image
  return "success";
  }//end asciiPGMParse 



//Parse a pgm mask formatted image and return "success"
//If fails returns the reason why
string Image::maskPGMParse(ifstream& istr){
  //parse pixels
  mask.reserve(height);
  min = 10000;max = -10000;
  for (int i = 0; i < height; i++){	
	vector<double> row;
	row.reserve(width);
	for(int j = 0; j < width; j++){ 
    		istr >> maskVal;
    		//valid pixel so add to vector
    		row.push_back(maskVal);
		min = min < maskVal?min:maskVal;
		max = max > maskVal?max:maskVal;
  		}
	mask.push_back(row);	
	}//end parsing declared amount of pixels
  return "success";
  }//end maskPGMParse 

