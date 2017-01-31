#include <Image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

//====================non-member functions=========================

int detectEdges(const Image & img, Image & E){
  Image Ih = img;//horizontal image
  Image Iv = img;//vertical image
  E.setWidth(img.getWidth());//set dim for edge image
  E.setHeight(img.getHeight());
  E.setType(img.getType());//match type with first param
  E.setPixels(img.getPixels());//initialize size of pixels vector in E to match
  int xp1,xm1,yp1,ym1;
  //compute E(x,y) by first computing Iv and Ih
  for(int y=0;y<img.getHeight();y++){//for each column
	for(int x=0;x<img.getWidth();x++){//for each row
		xp1  = (x+1)  < img.getWidth() ? x+1: 0;
		xm1 = (x-1)   > 0 ? x-1: 0;
		yp1  = (y+1) < img.getHeight() ? y+1: 0;
		ym1 = (y-1)  > 0 ? y-1: 0;
		Ih.setPixel(x,y, img.getPixel(xp1,ym1)+2*img.getPixel(xp1,y)
				+img.getPixel(xp1,yp1)-img.getPixel(xm1,ym1)
				-2*img.getPixel(xm1,y)-img.getPixel(xm1,yp1));
		Iv.setPixel(x,y, img.getPixel(xm1,yp1)+2*img.getPixel(x,yp1)
			 	+img.getPixel(xp1,yp1)-img.getPixel(xm1,ym1)
				-2*img.getPixel(x,ym1)-img.getPixel(xp1,ym1));		
		E.setPixel(x,y, round((double)sqrt((Ih.getPixel(x,y)*Ih.getPixel(x,y))
				+(Iv.getPixel(x,y)*Iv.getPixel(x,y)))) );
		if(x < 10 && y < 10)
			cout<<E.getPixel(x,y)<<" ";
	}//end for width
	if(y < 10)
		cout<<endl;
   }//end for height
  E.avg();//complete fields min, max	
  //rescale edge image. dec_max set in rescale()
  return E.rescale();//return 0 on correct rescale, else -1
}//end detectEdges



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




//return 1 if sizes differ, else 0
int Image::matchSize(Image img){
  if((height != img.getHeight()) || (width != img.getWidth()) )
	return 1;
  else return 0;
}//end matchSize




//compare two images and map comparison into callee image
//precondition: the image sizes of params must be equal
//		--->>>so call matchSize(img1,img2) before use<<---
//also note that this is called on an already made image
//and fills in it's pixels with those of the (img1 - img2)
void Image::compare(Image img1,Image img2){
  type = img1.getType();
  int large_diff = 0;
  height = img1.getHeight();
  width = img1.getWidth();
  size = width * height;
  vector<vector<int>> img1Pix = img1.getPixels();
  vector<vector<int>> img2Pix = img2.getPixels();
  for(int i = 0;i < height;i++){
	vector<int> row;
	for(int j=0;j<width;j++){
		row.push_back(abs(img1Pix.at(i).at(j) - img2Pix.at(i).at(j)));
  		if(row.at(j) > large_diff)
			large_diff = row.at(j);
		}
	pixels.push_back(row);
	}
  declared_max = large_diff;
  avg();
}//end compare




//Returns 0 for successful resize
//        -1 error: if min == max formula fails
int Image::rescale(void){
 if(max == min)
	return -1;
 for(int i=0;i<height;i++)
	for(int j=0;j<width;j++)
	     pixels.at(i).at(j)=round((double)255*(pixels.at(i).at(j)-min)/(max-min)); 
 min = 0;
 max = 255;
 return 0;
}//end rescale




void Image::avg(void)
{
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




int Image::output(string outfile){   
  ofstream ostr(outfile.c_str());
  if(ostr.fail()){//ensure the file is valid to write 
    	return 1;
	}
  if(type ==  2){//print ASCII
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
  if (istr.fail()) 
	return "Failed to open file";
  char junkc;
  //retrieve first line and check formatting
  if(istr.get() != 'P') //first character must be 'P'
	return "First character is incorrect";
  istr.get(junkc);
  if(junkc == '2')
	type = 2;//2 as in 'P2'
  else if(junkc == '5')
	type = 5;//5 as in 'P5'
  else
	return "Second character is incorrect";
  //ensure nothing else is in next character position	
  istr.get(junkc);
  if(!isspace(junkc))
	return "Incorrect format in magic number";
  istr.putback(junkc);
  //so far so good...now parse header of image file
  string parseH = parseHeader(istr);//store for possible return
  if(parseH != "success")
	return parseH;
  //Now parse data section
  if(type == 5)
	return binaryParse(istr);
  else//only other value possible at this point is type = 2
	return asciiParse(istr);
}//end input




string Image::parseHeader(ifstream& istr){
  char junkc;
  if (istr.fail()) 
	return "Failed to open file";
  if(parseComment(istr))
	return "Formatting not correct in header";
  if(!(istr>>width))
	return "Failed to parse width";
  if(width < 1)//width must be a positive integer
	return "Width is a negative value";
  //width is now parsed and valid
  //parse comments and parse height
  if(parseComment(istr))
	return "Formatting not correct in header";
  if(!(istr>>height))//height must be a positive integer
	return "Failed to parse height";
  if(height < 1)
	return "Height is a negative value";
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




//Parse a binary formatted image and returns "success"
//If fails returns the reason why
string Image::binaryParse(ifstream& istr){
  //no commments past this point
  //clear whitespace and check for newline
  char junkc ;
  int pixel = 0;  
  for(int i = 0; i < height; i++)
	{
	vector<int> row;
	for(int j = 0; j < width; j++){
	    istr.read((char*)&pixel,1);
	    if(pixel > declared_max)
		return "Pixel found larger than declared max";
	    if(pixel > 255)
		return "Pixel found larger than 255";
	    if(pixel < 0)
		return "Pixel found is less than 0";
	    //valid pixel so add to vector
	    row.push_back(pixel);
	  	}
	pixels.push_back(row);	
	}
  if(istr>>junkc)
	return "File contains more than declared pixels";
  avg();//intializes min and max and avg completing data fields for new image
  if(!istr.eof())
	return "EOF not after binary data";
  return "success";
}//end binaryParse




//Parse an ASCII formatted image and return "success"
//If fails returns the reason why
string Image::asciiParse(ifstream& istr){
  //parse pixels
  char junkc;
  for (int i = 0; i < height; i++)
	{	
	vector<int> row;
	for(int j = 0; j < width; j++) 
  		{ 
    		if(!(istr >> pixel))//attempt to store as integer
			return "Pixel found is not an integer";
		    //ensure valid value for found integer	
		if(pixel > declared_max)
			return "Pixel found larger than declared max";
    		if(pixel > 255)
			return "Pixel found larger than 255";
    		if(pixel < 0)
			return "Pixel found is less than 0";
    		//valid pixel so add to vector
    		row.push_back(pixel);
  		}
	pixels.push_back(row);	
	}//end parsing declared amount of pixels
  //check if more than just declared # of pixels
  if(istr>>junkc)
	return "File contains more than declared pixels";
  avg();//intializes min and max and avg completing data fields for new image
  return "success";
  }//end asciiParse 



