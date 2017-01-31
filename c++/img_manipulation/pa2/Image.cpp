#include <Image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

void Image::rescale(void){
 for(int i = 0;i < size;i++){
	pixels[i] = round((double)255*(pixels[i] - min)/(max - min)); 
	}
 min = 0;
 max = 255;
}//end rescale

int Image::output(string outfile){
  try{//check the file extension
	string extension = outfile.substr (outfile.rfind("."));
  	if(extension != ".pgm")
		return 1;
	}
  catch(const out_of_range& oor){
	return 1;//"." not found so extension is not valid
	}      
  FILE *file;
  file = fopen(outfile.c_str(), "w");
  if(!file){//ensure the file is valid to write 
    	return 1;
	}
  fprintf(file,"P2\n%d %d\n255\n", width, height);
  for(int i=0;i<size;i++){
	fprintf(file," %d ",pixels[i]);
	}
  fprintf(file,"\n");
  return 0;
}

string Image::input(void)
{
  //test file opening
  ifstream istr(name.c_str());
  if (istr.fail()) 
	return "Failed to open file";
  string junks;
  char junkc;
  bool newline = false;
  //retrieve first line and check formatting
  if(istr.get() != 'P') //first character must be 'P'
	return "First character is incorrect";
  if(istr.get() != '2')//second character must be '2'
	return "Second character is incorrect";
  //clear remainder of first line
  istr.get(junkc);
  while(isspace(junkc) && !istr.eof())
  {
    if(junkc == '\n')//check if newline character
	newline =  true;//indicate not on first line
    istr.get(junkc); 
  }
  if(newline == false)
	return "Invalid character on line 1"; 
  //first line is valid, now clear comments
  else
	while(junkc == '#' && !istr.eof())
	{
	  getline(istr,junks);
	  istr>>junkc;
	}
  istr.putback(junkc);//put back non-# character for next parse
  //comments clear parse width height line
  if(!(istr>>width))
	return "Failed to parse width";
  if(width < 1)//width must be a positive integer
	return "Width is a negative value";
  istr.get(junkc);
  newline = false;//reset for check if width and height are on different lines
  while(isspace(junkc))
  {
    if(junkc == '\n')//check if newline character
	newline = true;//indicate not on same line
    istr.get(junkc);
  }
  istr.putback(junkc);//put back non-whitespace character for next parse
  if(newline == true)
	return "Width and height are not on the same line";
  if(!(istr>>height))//height must be a positive integer
	return "Failed to parse height";
  if(height < 1)
	return "Height is a negative value";
  size = width * height;//compute total pixels
  newline = false;//reset to ensure nothing else on line with width and height
  istr.get(junkc);
  while(isspace(junkc) && !istr.eof())
  {
    if(junkc == '\n')//check if newline character
	newline = true;//indicate not on width height line
    istr.get(junkc);
  }
  if(newline == false)
	return "Invalid character on width height line";
  //width height is valid now clear comments 
  else 
	while(junkc == '#' && !istr.eof())
	{
          getline(istr,junks);
	  istr>>junkc;
	}
  istr.putback(junkc);
  //comments clear parse declared max line
  if(!(istr>>declared_max))
	return "Failed to parse declared max";
  newline = false;//reset to ensure nothing on line with max declared
  istr.get(junkc);
  while(isspace(junkc) && !istr.eof())
  {
    if(junkc == '\n')//check if newline character
	newline = true;//indicate not on same line as
    istr.get(junkc);
  }
  if(newline == false)
	return "Invalid character on declared max line";
  istr.putback(junkc);
  //declared max line is valid now parse pixels
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
  }//end parse 

void Image::avg(void)
{
  int sum;
  min = max = sum = pixels[0];
  for (int i=1;i<size;i++)
  { 
	min = min < pixels[i]?min:pixels[i];
	max = max > pixels[i]?max:pixels[i];
	sum+= pixels[i];
  }
  average = (double) sum / size;
}//end stats


