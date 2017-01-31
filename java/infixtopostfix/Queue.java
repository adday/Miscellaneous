import java.util.ArrayList;


public class Queue implements QueueIF {

        // This class implements the Queue Interface  QueueIF

	// maintains expression
	private ArrayList<String> expQueue;
	
	// debug controls debug reporting
	private boolean debug;
	
	// initialze expQueue and debug
	public Queue(boolean debug){
		this.debug = debug;
		expQueue = new ArrayList<String>();
	}
	
        public static void main(String[] args) throws QueueException{
    	Queue q = new Queue(false);
    	q.dequeue();
    }
        
    	//enqueue String token at the end of expQueue
    	// In debug mode print "enqueue: " + enqueued value
    	public void enqueue(String token){
    		if(debug)
    			System.out.println("enqueue: " + token);
    		expQueue.add(expQueue.size(), token);
    	}
    	
    	/* dequeue token from the front of the expQueue
    	 * If expQueue empty, throw QueueException "dequeueing empty queue!!"
    	 * In debug mode print "dequeue: " + dequed value
    	 */ 
    	public String dequeue() throws QueueException{
    		if(debug)
    			System.out.println("dequeue: " + expQueue.get(0));
    		if(!expQueue.isEmpty())
    			return expQueue.remove(0);
    		else
    			throw new QueueException("dequeueing empty queue!!");
    		
    	}
    	
    	// returns size (#elements) of the queue
    	public int size(){
    		return expQueue.size();
    	}
}
