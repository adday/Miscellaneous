
public class BoundedBuffer {
	Double[] buffer;
	int in,out,size,len,place;
	
	public BoundedBuffer(int buf_size){
		this.size = buf_size;
		buffer = new Double[size];
		in = out = len = 0;
	}//end BoundedBuffer()
	
	boolean isEmpty(){return len == 0;}
	
	boolean isFull(){return len == size;}
	
	int insert(Double item){
		    int place = in;
		    buffer[in] = item;
		    len++;
		    in = (in+1) % size;
		    return place;
		   }//end insert()

	int remove(){ 
		     int place = out;
		     buffer[out] = null;
		     len--;
		     out = (out+1) % size;
		     return place;
		   }//end remove()

}//end BoundedBuffer.java

