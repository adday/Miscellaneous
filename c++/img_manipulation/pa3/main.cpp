/*-----------------------------------------------------------------------------------------------------
	CS253 PA3: Binary and ASCII images
	Author: Alexander Day 830 523 317
-------------------------------------------------------------------------------------------------------*/
#include <Image.h>       
#include <string.h>
   
int Usage(char* arg1, string message){    
  cerr << endl << "Message: " << message << endl;       
  cerr << "File:   " << arg1<< endl<<endl;            
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
  if(img.output(argv[2]))
  	return Usage(argv[2],"Problem writing to output file");
  return 0;//success
} 
