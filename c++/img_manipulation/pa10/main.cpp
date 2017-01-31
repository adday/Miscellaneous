/*-----------------------------------------------------------------------------------------------------
	CS253 PA10: Finding the Cat- Optimized
	Author: Alexander Day 830 523 317
-------------------------------------------------------------------------------------------------------*/
#include <Image.h>       
#include <string.h>
   
int Usage(char* arg1, string message){    
  cerr << endl << "Message: " << message << endl;       
  cerr << "File:   " << arg1<< endl<<endl;            
  return -1;//error
}  
    
/*====================main====================*/
int main(int argc, char* argv[]){   
  string buf;
  //check for the correct number of arguments 
  if (argc != 4) 
	return Usage(argv[0],"Wrong number of arguments");
  if(!strcmp(argv[1],argv[3]))
	return Usage(argv[1], "Identical image names cause overwrite");
  Image in(argv[1]);//read in image  
  buf = in.input();//store parse return code
  if(buf != "success")
	return Usage(argv[1], buf);
  if(in.getType() != 2)
	if(in.getType() != 5)
		return Usage(argv[1], "Incorrect file format for input file");
  Image mask(argv[2]);//edge image to be constructed
  buf = mask.input();//store parse return code
  if(buf != "success")
	return Usage(argv[2], buf);
  Image out(argv[3]);
  if(find_the_cat(in,mask,out) != 0)//if not successful
	return Usage(argv[3], "Error rescaling output image");
  if(out.output(argv[3]) != 0)
	return Usage(argv[3], "Error writing output image");
  return 0;//success
} 
