/*-----------------------------------------------------------------------------------------------------
	CS253 PA7: Color Image Edge Detection
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
  if (argc != 3) 
	return Usage(argv[0],"Wrong number of arguments");
  if(!strcmp(argv[1],argv[2]))
	return Usage(argv[1], "Identical image names cause overwrite");
  Image in(argv[1]);//read in image  
  buf = in.input();//store parse return code
  if(buf != "success")
	return Usage(argv[1], buf);
  Image E(argv[2]);//edge image to be constructed
  if(detectColorEdges(in,E) == 0){//detectEdges returns 0 on success
  	if(E.colorOutput(E.getName()))//write edge image to output file
  		return Usage(argv[2],"Problem writing to output file");
	}//end if(detectEdges)
  else//error in rescaling or image too small
	return Usage(argv[2],"Problem rescaling image E or input image is too small");
  return 0;//success
} 
