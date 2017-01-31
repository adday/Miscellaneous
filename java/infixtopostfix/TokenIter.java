
import java.util.Iterator;
import java.util.StringTokenizer;


public class TokenIter implements Iterator<String>{

        // This class builds a Token Iterator, that produces 
        // Strings containing numbers (sequences of digits) and 
        // special characters: "(" ")" "+" "-"  "*" "/"	
	//input line to be tokenized
	private String line;
	
	// the next Token, null if no next Token
	private String nextToken;
	
	StringTokenizer strTok;
	
	public TokenIter(String line){
		this.line = line.trim();
		strTok = new StringTokenizer(this.line, " +-*/()", true);
	}

	@Override
	public void remove() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException();
	}
	

	public static void main(String[] args){
		String line = "  15*(26+37) - 489/5*61 - (723-8456789)   ";
		System.out.println("line: [" + line + "]");
		TokenIter tokIt = new TokenIter(line);
                // print tokens in square brackets to check absence of white space
		while(tokIt.hasNext()){
			System.out.println("next token: [" + tokIt.next() + "]");
		}
	}
	
	@Override
	public boolean hasNext(){
		if(line.isEmpty())
			return false;
		return strTok.hasMoreTokens();
	}
	
	@Override
	public String next(){
		nextToken = strTok.nextToken();
		while(nextToken.matches(" "))
			nextToken = strTok.nextToken();
		return nextToken;
	}
}
