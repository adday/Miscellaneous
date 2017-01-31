/*-----------------------------------------------------------------------------------------------------
	CS253 PA2: Image Scaling
	Author: Alexander Day 830 523 317
	
	Given a properly formatted .pgm file, scale pixel values to use full range from 0 to 255.
	Informs the user via error stream of incorrect formatting otherwise prints rescaled image 
	to file provided.
-------------------------------------------------------------------------------------------------------*/
#include <Image.h>       
#include <string.h>
   
int Usage(char* arg1, string message){    
  cerr << endl << "Message: " << message << endl;       
  cerr << "File:   " << arg1<< endl<<endl;     
  cerr << "Expected format for .pgm file:" << endl;        
  cerr << "First line is 'P2'" << endl; 
  cerr << "Then optional comment lines indicated by first character #"<<endl;
  cerr << "A line contains dimensions (width height)"<<endl;
  cerr << "Then optional comment lines indicated by first character #"<<endl;
  cerr << "A line containing max declared pixel value" << endl;
  cerr << "Then integers between 0 and less than declared max, but no greater than 255" << endl;
  return -1;//error
}  
    
int main(int argc, char* argv[]){   
  string buf;
  //check for the correct number of arguments 
  if (argc != 3) 
	return Usage(argv[1],"Wrong number of arguments");
  if(!strcmp(argv[1],argv[2]))
	return Usage(argv[1], "Identical file names provided");
  Image img(argv[1]);
  buf = img.input();
  if(buf != "success")
	return Usage(argv[1], buf);
  img.rescale();
  if(img.output(argv[2]) != 0)
   	return Usage(argv[2],"Problem writing to output file");
  return 0;//success
} 
