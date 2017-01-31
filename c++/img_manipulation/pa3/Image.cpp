#include <Image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

void Image::rescale(void){
 for(int i = 0;i < size;i++)
	pixels[i] = round((double)255*(pixels[i] - min)/(max - min)); 
 min = 0;
 max = 255;
}//end rescale


void Image::avg(void)
{
  int sum;
  min = max = sum = pixels[0];
  for (int i=1;i<size;i++){ 
	min = min < pixels[i]?min:pixels[i];
	max = max > pixels[i]?max:pixels[i];
	sum+= pixels[i];
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
	for(int i=0;i<size;i++)
		ostr<<pixels[i]<<" ";
	ostr<<endl;
  	return 0;}
  else{//print binary
	ostr<<"P5\n"<<width<<" "<<height<<"\n255"<<endl;
	for(int i=0;i<size;i++)
		ostr.write(reinterpret_cast<const char*>(&pixels[i]), 1);
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
}


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
}

//Parse a binary formatted image and returns "success"
//If fails returns the reason why
string Image::binaryParse(ifstream& istr){
  //no commments past this point
  //clear whitespace and check for newline
  char junkc ;
  int pixel = 0;
  for(int i=0;i<size;i++){
    istr.read((char*)&pixel,1);
    if(pixel > declared_max)
	return "Pixel found larger than declared max";
    if(pixel > 255)
	return "Pixel found larger than 255";
    if(pixel < 0)
	return "Pixel found is less than 0";
    //valid pixel so add to vector
    pixels.push_back(pixel);
  	}
  if(istr>>junkc)
	return "File contains more than declared pixels";
  avg();//intializes min and max and avg completing data fields for new image
  if(max == min)
	return "Cannot rescale image: max = min";
  if(!istr.eof())
	return "EOF not after binary data";
  return "success";
}//end binaryParse


//Parse an ASCII formatted image and return "success"
//If fails returns the reason why
string Image::asciiParse(ifstream& istr){
  //parse pixels
  char junkc;
  for (int i = 0; i < size; i++) 
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
    pixels.push_back(pixel);
  }//end parsing declared amount of pixels
  //check if more than just declared # of pixels
  if(istr>>junkc)
	return "File contains more than declared pixels";
  avg();//intializes min and max and avg completing data fields for new image
  if(max == min)
	return "Cannot rescale image: max = min";
  return "success";
  }//end asciiParse 



