// Palindrome.java
// Author: Alexander Day
// Date: 02/04/2015
// Class: cs200
// R3
public class Palindrome {

	private void generatePalindromeRecursive(String s,int index)
	{
		// first print the character, then recurse on the next character index
		System.out.print(s.charAt(index));
		if(index<s.length()-1)
		{
			// question: will index++ or ++index work on the method call below?
			generatePalindromeRecursive(s,index+1);
		}
		System.out.print(s.charAt(index));
		
	}
	
	public void generatePalindrome(String s) {
		// generate palindrome by concatenating the reverse of s to s
		generatePalindromeStack(s,s.length()-1);
		System.out.println();
		
	}
	
	private void generatePalindromeStack(String s, int length){
		Stack stack = new Stack();
		int i = 0;
		while(length >= 0){
			System.out.print(s.charAt(i));
			stack.push(s.charAt(i));
			i++;
			length--;
		}
		while(!stack.isEmpty()){
			System.out.print(stack.pop());
		}
	}
	
	public static void main(String[] args) {
	    Palindrome p = new Palindrome();
		p.generatePalindrome("h");

	}
}
