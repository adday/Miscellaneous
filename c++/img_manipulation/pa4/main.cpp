/*-----------------------------------------------------------------------------------------------------
	CS253 PA4: Image Matching
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
  if (argc != 4) 
	return Usage(argv[0],"Wrong number of arguments");
  if(!strcmp(argv[1],argv[3]) || !strcmp(argv[2],argv[3]))
	return Usage(argv[1], "Identical image names cause overwrite");
  Image in1(argv[1]);
  Image in2(argv[2]);
  Image out(argv[3]);
  buf = in1.input();
  if(buf != "success")
	return Usage(argv[1], buf);
  buf = in2.input();
  if(buf != "success")
	return Usage(argv[2], buf); 
  if(in1.matchSize(in2))
	return Usage(argv[1],"Image size in file 1 does not match that in file 2");
  out.compare(in1, in2); 
  if(out.output(argv[3]))
  	return Usage(argv[2],"Problem writing to output file");
  return 0;//success
} 
