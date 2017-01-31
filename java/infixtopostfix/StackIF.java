
public interface StackIF {
	        // add String op to top of stack
		// In debug mode print "push: " + pushed value
                public void push(String op);
		
		// remove and return item from top of stack
                // In debug mode print "push: " + pushed value
		// throw Stack Exception "popping from empty stack!"  when stack empty
		public String pop() throws StackException;
		
		// return, but do not remove, item from top of stack
		// throw Stack Exception "peeking empty stack!" when stack empty
		public String peek() throws StackException;	
		
		// return true if stack empty, false otherwise
		public boolean isEmpty();

}
