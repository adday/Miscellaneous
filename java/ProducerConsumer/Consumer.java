import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

public class Consumer implements Runnable {
    BoundedBuffer buffer;
    Random rand = new Random();
    int consumed,to_consume, max_wait;
    boolean pflag;
    SimpleDateFormat sdf; 

    public Consumer(BoundedBuffer buf, int to_consume, int max_wait, boolean pflag) {
        this.buffer = buf;
        this.to_consume= to_consume;
        this.max_wait = max_wait;
        this.pflag = pflag;
        sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
    }//end Consumer()

   private String getTime(){
	return sdf.format(new Date()) + String.valueOf(System.nanoTime()).substring(9,11);
	}

    public synchronized void consume(){
	//parallel section
    	if(pflag){//true when running in parallel with producer
	        while(buffer.isEmpty())
	           	try {
				System.out.println("Unable to consume, buffer empty, at Time: " + getTime() + "\n");
	           		buffer.wait();
	            }catch (InterruptedException e){}

	       	System.out.println("Removed from location: " + buffer.remove() + " at Time: " + getTime() + " \n");
	        buffer.notifyAll();//notifyAll() needed because we could have multiple producer threads to wake up

        }//end parallel section

	//serialized section when no producer
    	else{
		if(!buffer.isEmpty())//if there are more items to consume
    	        	System.out.println("Removed from location: " + buffer.remove() + " at Time: " + getTime() + "\n");

    		else{//buffer is empty
    			System.out.println("Unable to consume, buffer empty, at Time: " + getTime()  + "\n");
			consumed = to_consume;
			}//end else

		}//end serialized section

    }//end consume()

    public void run() {
        while(consumed < to_consume){
        	synchronized(buffer){consume();}
        	consumed++;
		try{Thread.sleep(rand.nextInt(max_wait));}catch(Exception e){}//random wait time
           	}//end while
    }//end run()

}//end Consumer.java
