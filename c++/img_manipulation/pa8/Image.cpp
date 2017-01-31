#include <Image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

//====================non-member functions=========================
int convolution(const Image & img, const  Image & mask, Image & out){
  if(mask.getWidth() > img.getWidth() || mask.getHeight() > img.getHeight())
	return -1;//convolution will fail 
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
		for(int q=0;q<mask.getHeight();q++){
			for(int p=0;p<mask.getWidth();p++){
				fpixel += mask.getMaskVal(p,q) * img.getPixel(x+p,y+q);}}
		row.push_back(fpixel);
		min = min < fpixel?min:fpixel;
		max = max > fpixel?max:fpixel;
	}//end for width
	out.setfPixelRow(row);	
  }//end for height
  out.setMax(max);
  out.setMin(min);
  return out.rescale();//success
}



int detectColorEdges(const Image & img, Image & E){
  if(img.getWidth() < 3 || img.getHeight() < 3)
	return -1;//this image will fail after deleting borders
  int IhR,IvR,IhG,IvG,IhB,IvB,EB,EG,ER,min,max;
  min = 10000;//intialize field with high value as some pixel will be lower
  max = -10000; //intialize field with low value as some pixel will be higher
  E.setType(img.getType());//match type with input image
  E.setWidth(img.getWidth()-2);E.setHeight(img.getHeight()-2);
  E.setSize(E.getWidth()*E.getHeight());
  E.colorReserve(E.getHeight());
  //compute E by first computing Iv and Ih for each color and E for each color
  for(int y=1;y<img.getHeight()-1;y++){//for each column
	vector<RGBPixel> row;
	row.reserve(E.getWidth());
	for(int x=1;x<img.getWidth()-1;x++){//for each row
		IhR = img.getColor(x+1,y-1,1)+2*img.getColor(x+1,y,1) +img.getColor(x+1,y+1,1)
			  -img.getColor(x-1,y-1,1)-2*img.getColor(x-1,y,1)-img.getColor(x-1,y+1,1);
		IvR = img.getColor(x-1,y+1,1)+2*img.getColor(x,y+1,1)+img.getColor(x+1,y+1,1)
			  -img.getColor(x-1,y-1,1)-2*img.getColor(x,y-1,1)-img.getColor(x+1,y-1,1);		
		ER = rint(static_cast<double>(sqrt((IhR*IhR)+(IvR*IvR))) );
		min = ER<min ? ER: min;
		max = ER>max ? ER: max;
		IhG = img.getColor(x+1,y-1,2)+2*img.getColor(x+1,y,2) +img.getColor(x+1,y+1,2)
			  -img.getColor(x-1,y-1,2)-2*img.getColor(x-1,y,2)-img.getColor(x-1,y+1,2);
		IvG = img.getColor(x-1,y+1,2)+2*img.getColor(x,y+1,2)+img.getColor(x+1,y+1,2)
			  -img.getColor(x-1,y-1,2)-2*img.getColor(x,y-1,2)-img.getColor(x+1,y-1,2);		
		EG = rint(static_cast<double>(sqrt((IhG*IhG)+(IvG*IvG))) );
		min = EG<min ? EG: min;
		max = EG>max ? EG: max;
		IhB = img.getColor(x+1,y-1,3)+2*img.getColor(x+1,y,3) +img.getColor(x+1,y+1,3)
			  -img.getColor(x-1,y-1,3)-2*img.getColor(x-1,y,3)-img.getColor(x-1,y+1,3);
		IvB = img.getColor(x-1,y+1,3)+2*img.getColor(x,y+1,3)+img.getColor(x+1,y+1,3)
			  -img.getColor(x-1,y-1,3)-2*img.getColor(x,y-1,3)-img.getColor(x+1,y-1,3);		
		EB = rint(static_cast<double>(sqrt((IhB*IhB)+(IvB*IvB))) );
		min = EB<min ? EB: min;
		max = EB>max ? EB: max;
		row.push_back(RGBPixel(ER,EG,EB));
	}//end for width
	E.setColorRow(row);
   }//end for height
  E.setMin(min);
  E.setMax(max);
  //rescale edge image. dec_max set in rescale()
  return E.colorRescale();//return 0 on correct rescale, else -1
}//end detectColorEdges





int detectEdges(const Image & img, Image & E){
  Image Ih = img;//horizontal image
  Image Iv = img;//vertical image
  E.setWidth(img.getWidth());//set dim for edge image
  E.setHeight(img.getHeight());
  E.setType(img.getType());//match type with first param
  E.setPixels(img.getPixels());//initialize size of pixels vector in E to match
  //compute E(x,y) by first computing Iv and Ih
  for(int y=0;y<img.getHeight();y++){//for each column
	for(int x=0;x<img.getWidth();x++){//for each row
		Ih.setPixel(x,y, img.getPixel(x+1,y-1)+2*img.getPixel(x+1,y)
				+img.getPixel(x+1,y+1)-img.getPixel(x-1,y-1)
				-2*img.getPixel(x-1,y)-img.getPixel(x-1,y+1));
		Iv.setPixel(x,y, img.getPixel(x-1,y+1)+2*img.getPixel(x,y+1)
			 	+img.getPixel(x+1,y+1)-img.getPixel(x-1,y-1)
				-2*img.getPixel(x,y-1)-img.getPixel(x+1,y-1));		
		E.setPixel(x,y, rint(static_cast<double>(sqrt((Ih.getPixel(x,y)*Ih.getPixel(x,y)))
				+(Iv.getPixel(x,y)*Iv.getPixel(x,y)))) );
	}//end for width
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
  pixels.reserve(height);
  for(int i = 0;i < height;i++){
	vector<int> row;
	row.reserve(width);
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
 	if(max == min)
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




//Returns 0 for successful resize
//        -1 error: if min == max formula fails
int Image::colorRescale(void){
 if(max == min)
	return -1;
 for(int i=0;i<height;i++){
	for(int j=0;j<width;j++){
	    colors.at(i).at(j).setRed(rint(255*static_cast<double>(colors.at(i).at(j).getRed()-min)/(max-min))); 
	    colors.at(i).at(j).setGreen(rint(255*static_cast<double>(colors.at(i).at(j).getGreen()-min)/(max-min))); 
	    colors.at(i).at(j).setBlue(rint(255*static_cast<double>(colors.at(i).at(j).getBlue()-min)/(max-min)));
	 }//end for width
  }//end for height
 min = 0;
 max = 255;
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




//writes image to a ppm file
//callee image must have colors initialized
//only valid for type 3 or type 6 images
int Image::colorOutput(string outfile){   
  ofstream ostr(outfile.c_str());
  int red,green,blue;
  if(ostr.fail()){//ensure the file is valid to write 
    	return 1;
	}
  if(type  == 3){//print ASCII
	ostr<<"P3\n"<<width<<" "<<height<<"\n255"<<endl;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			ostr<<colors.at(i).at(j).getRed()<<" "<<colors.at(i).at(j).getGreen()<<" "<<colors.at(i).at(j).getBlue()<<" ";
	ostr<<endl;
  	return 0;}
  else{//print binary
	ostr<<"P6\n"<<width<<" "<<height<<"\n255"<<endl;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++){
	   	     red = colors.at(i).at(j).getRed();
		     ostr.write(reinterpret_cast<const char*>(&red), 1);
	   	     green = colors.at(i).at(j).getGreen();
		     ostr.write(reinterpret_cast<const char*>(&green), 1);
	   	     blue = colors.at(i).at(j).getBlue();
		     ostr.write(reinterpret_cast<const char*>(&blue), 1);}
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
  if(junkc == '2'){
	type = 2;//P2 ASCII pgm
        istr.get(junkc);
	if(junkc == 'M') type = 0;//pgm mask
        else istr.putback(junkc);
 	}
  else if(junkc == '5')
	type = 5;//P5 binary pgm
  else if(junkc == '3')
	type = 3;//P3 ASCII ppm
  else if(junkc == '6')
	type = 6;//P6 binary ppm
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
  if(type == 0)//.pgmm mask
	return maskPGMParse(istr);
  else if(type == 2)//ASCII .pgm
	return asciiPGMParse(istr);
  else if(type == 5)//binary .pgm
	return binaryPGMParse(istr);
  else if(type == 3)//ASCII .ppm
	return asciiPPMParse(istr);
  else//binary .ppm
	return binaryPPMParse(istr);
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

//Parse a ppm binary formatted image and returns "success"
//If fails returns the reason why
string Image::binaryPPMParse(ifstream& istr){
  //no commments past this point
  //clear whitespace and check for newline
  char junkc ;
  pixels.reserve(height);
  colors.reserve(height);
  int red = 0, green = 0, blue = 0;
  for(int i = 0; i < height; i++){
	vector<int> row;//holds greyscale values for row
	vector<RGBPixel> rowRGB;//hold RGB values for row
	row.reserve(width);
        rowRGB.reserve(width);
	for(int j = 0; j < width; j++){
	    istr.read((char*)&red,1);
	    if(red > declared_max)
		return "Pixel found larger than declared max";
	    if(red > 255)
		return "Pixel found larger than 255";
	    if(red < 0)
		return "Pixel found is less than 0";
	    istr.read((char*)&green,1);
	    if(green > declared_max)
		return "Pixel found larger than declared max";
	    if(green > 255)
		return "Pixel found larger than 255";
	    if(green < 0)
		return "Pixel found is less than 0";
	    istr.read((char*)&blue,1);
	    if(blue > declared_max)
		return "Pixel found larger than declared max";
	    if(blue > 255)
		return "Pixel found larger than 255";
	    if(blue < 0)
		return "Pixel found is less than 0";
            pixel = rint(static_cast<double>((red+green+blue)/3));
	    //valid pixel so add to vector
	    row.push_back(pixel);
	    rowRGB.push_back(RGBPixel(red,green,blue));
	  	}
	pixels.push_back(row);	
	colors.push_back(rowRGB);
	}
  if(istr>>junkc)
	return "File contains more than declared pixels";
  avg();//intializes min and max and avg completing data fields for new image
  if(!istr.eof())
	return "EOF not after binary data";
  return "success";
}//end binaryPPMParse



//Parse a pgm binary formatted image and returns "success"
//If fails returns the reason why
string Image::binaryPGMParse(ifstream& istr){
  //no commments past this point
  //clear whitespace and check for newline
  char junkc ;
  int pixel = 0;
  pixels.reserve(height);
  for(int i = 0; i < height; i++){
	vector<int> row;
	row.reserve(width);
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
}//end binaryPGMParse



//Parse a ppm ASCII formatted image and return "success"
//If fails returns the reason why
string Image::asciiPPMParse(ifstream& istr){
  //parse pixels
  char junkc;
  pixels.reserve(height);
  colors.reserve(height);
  int red = 0, green = 0, blue = 0;
  for (int i = 0; i < height; i++)
	{	
	vector<int> row;//holds greyscale values for row
	vector<RGBPixel> rowRGB;//hold RGB values for row
	row.reserve(width);
        rowRGB.reserve(width);
	for(int j = 0; j < width; j++) 
  		{ 
    		if(!(istr >> red))//attempt to store as integer
			return "Pixel found is not an integer";
		    //ensure valid value for found integer	
		if(red > declared_max)
			return "Pixel found larger than declared max";
    		if(red > 255)
			return "Pixel found larger than 255";
    		if(red < 0)
			return "Pixel found is less than 0";
                if(!(istr >> green))//attempt to store as integer
			return "Pixel found is not an integer";
		    //ensure valid value for found integer	
		if(green > declared_max)
			return "Pixel found larger than declared max";
    		if(green > 255)
			return "Pixel found larger than 255";
    		if(green < 0)
			return "Pixel found is less than 0";
                if(!(istr >> blue))//attempt to store as integer
			return "Pixel found is not an integer";
		    //ensure valid value for found integer	
		if(blue > declared_max)
			return "Pixel found larger than declared max";
    		if(blue > 255)
			return "Pixel found larger than 255";
    		if(blue < 0)
			return "Pixel found is less than 0";
		pixel = rint(static_cast<double>((red+green+blue)/3));
    		//valid pixel so add to vector
    		row.push_back(pixel);
	    	rowRGB.push_back(RGBPixel(red,green,blue));
  		}
	pixels.push_back(row);	
	colors.push_back(rowRGB);
	}//end parsing declared amount of pixels
  //check if more than just declared # of pixels
  if(istr>>junkc)
	return "File contains more than declared pixels";
  avg();//intializes min and max and avg completing data fields for new image
  return "success";
  }//end asciiPPMParse 




//Parse a pgm ASCII formatted image and return "success"
//If fails returns the reason why
string Image::asciiPGMParse(ifstream& istr){
  //parse pixels
  char junkc;
  pixels.reserve(height);
  for (int i = 0; i < height; i++)
	{	
	vector<int> row;
	row.reserve(width);
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
  }//end asciiPGMParse 



//Parse a pgm mask formatted image and return "success"
//If fails returns the reason why
string Image::maskPGMParse(ifstream& istr){
  //parse pixels
  char junkc;
  mask.reserve(height);
  for (int i = 0; i < height; i++){	
	vector<double> row;
	row.reserve(width);
	for(int j = 0; j < width; j++){ 
    		if(!(istr >> maskVal))//attempt to store as double
			return "Pixel found is not an double";
		    //ensure valid value for found double
		if(maskVal > declared_max)
			return "Pixel found larger than declared max";
    		//valid pixel so add to vector
    		row.push_back(maskVal);
  		}
	mask.push_back(row);	
	}//end parsing declared amount of pixels
  //check if more than just declared # of pixels
  if(istr>>junkc)
	return "File contains more than declared pixels";
  return "success";
  }//end maskPGMParse 

