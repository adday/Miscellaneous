
public class Woman{
   
	String name;
	boolean engaged;
	Man match;
	Man[] prefer;
	
	public Woman(String name){
		this.name = name;
		engaged = false;
		prefer = new Man[3];
	}
	
	void end(Man newguy){
		System.out.print(" but leaves him for " + newguy.name + "\n");
		this.match.engaged = false;
		this.match = newguy;
		newguy.engaged = true;
		newguy.match = this;
		System.out.println(newguy.name + " is engaged to " + this.name);
	}
}
