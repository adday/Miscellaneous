/*-----------------------------------------------------------------------------------------------------
	CS253 PA1: Netbpm Image Stats
	Author: Alexander Day 830 523 317
	
	Given a properly formatted .pgm file, displays "min average max" pixel values.
	Informs the user via error stream of incorrect formatting.
-------------------------------------------------------------------------------------------------------*/
#include <Image.h>       
   
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
  if (argc != 2) 
	return Usage(argv[1],"Wrong number of arguments");
  Image img(argv[1]);
  buf = img.parse();
  if(buf != "success")
	return Usage(argv[1], buf);
  //compute and print min, max, and average pixel values
  img.avg();
  return 0;//success
} 
