import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

public class Producer implements Runnable {
    BoundedBuffer buffer;
    Random rand = new Random();
    int produced, to_produce, max_wait;
    boolean pflag;
    Double bufferElement;
    SimpleDateFormat sdf; 

    public Producer(BoundedBuffer buf, int to_produce, int max_wait, boolean pflag) {
        this.buffer = buf;
        this.to_produce = to_produce;
        this.max_wait = max_wait;
        this.pflag = pflag;
        sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
    }//end Producer()

   private String getTime(){
	return sdf.format(new Date()) + String.valueOf(System.nanoTime()).substring(9,11);
	}

    public synchronized void produce(){

        bufferElement = rand.nextDouble() * 100.0;
	
	//parallel section
    	if(pflag){//true when running in parallel with consumer
	        while(buffer.isFull())
	           	try {
	                	System.out.println("Unable to place, buffer full, at Time: " + getTime() + "\n");
				buffer.wait();
	                }catch (InterruptedException e){}

		System.out.println("Placed at the location: " + buffer.insert(bufferElement) + " at Time: " + getTime() + "\n");
	        buffer.notifyAll();//notifyAll() needed because we could have multiple consumer threads to wake up

        }//end parallel section

	//serialized section when no consumer
	else{	
		if(!buffer.isFull())//if there is room to produce more items
		        System.out.println("Placed at the location: " + buffer.insert(bufferElement) + " at Time: " + getTime()  + "\n");
	    	
	    	else{//buffer is full
	    		System.out.println("Unable to place, buffer full, at Time: " + getTime()  + "\n");
			produced = to_produce;
			}//end else

	}//end serialized section

    }//end produce()

    public void run() {
        while (produced < to_produce) {
            synchronized(buffer){produce();}
            produced++;
            try{Thread.sleep(rand.nextInt(max_wait));}catch(Exception e){}//random wait time
        	}//end while
    }//end run()

}//end Producer.java


