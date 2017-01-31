
public class Man{
 
	String name;
	boolean engaged;
	Woman match;
	Woman[] prefer;
	boolean[] asked = new boolean[3];
	
	public Man(String name){
		this.name = name;
		engaged = false;
		prefer = new Woman[3];
	}
	
	void propose(Woman w){
		if(w.engaged == false){
			w.match = this;
			this.match = w;
			this.engaged = true;
			w.engaged = true;
			System.out.println(this.name + " is engaged to " + w.name + " because she's single");
		}
		else{
			System.out.print(w.name + " is engaged to " + w.match.name);
			if(w.prefer[0] == this)
				w.end(this);	
			else if(w.prefer[1] == this && w.match != w.prefer[0])
				w.end(this);	
			else
				System.out.println(" and doesn't want to leave him");
			}//end engaged = true					
	}//end propose
	
}//end man
