
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
