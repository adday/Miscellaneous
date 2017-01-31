
public class StableMatching {

	public static void main(String[] args) {
		
		//establish environment variables
		boolean freeman = true;
		String[] mname = {"Joe","Eric","Bob"};
		String[] wname ={"Sally","Kate","Veronica"};
		Man[] men = new Man[3];
		Woman[] women = new Woman[3];
		
		//initialize arrays
		for(int i=0;i<3;i++){
			men[i] = new Man(mname[i]);
			women[i] = new Woman(wname[i]);}
		
		//build preference lists
		for(int i=0;i<3;i++){;
			if(i == 0){
				men[i].prefer[0] = women[0];
				men[i].prefer[1] = women[1];
				men[i].prefer[2] = women[2];
				women[i].prefer[0] = men[2];
				women[i].prefer[1] = men[1];
				women[i].prefer[2] = men[0];
			}
			if(i == 1){
				men[i].prefer[0] = women[0];
				men[i].prefer[1] = women[1];
				men[i].prefer[2] = women[2];
				women[i].prefer[0] = men[0];
				women[i].prefer[1] = men[1];
				women[i].prefer[2] = men[2];
			}
			if(i == 2){
				men[i].prefer[0] = women[0];
				men[i].prefer[1] = women[1];
				men[i].prefer[2] = women[2];
				women[i].prefer[0] = men[1];
				women[i].prefer[1] = men[2];
				women[i].prefer[2] = men[0];
			}
		}//end for
		
		//start matching
		while(freeman){
			//check for free men
			for(int i=0;i<3;i++){
				if(men[i].engaged == false){
					System.out.println(men[i].name + " is single so we continue");
					freeman = true;
					break;}
				else{
					System.out.println(men[i].name + " is engaged");
					freeman = false;
					}
				}
			if(freeman == false)
				break;
			
			int j=0;
			while(men[j].engaged == true)
				j++;
			
			//start proposals
			System.out.println("Next man is " + men[j].name);
			if(men[j].engaged == false && men[j].asked[0] == false){
				System.out.println(men[j].name + " proposes to " + men[j].prefer[0].name);
				men[j].propose(men[j].prefer[0]);
				men[j].asked[0] = true;
				}
			if(men[j].engaged == false && men[j].asked[1] == false){
				System.out.println(men[j].name + " proposes to " + men[j].prefer[1].name);
				men[j].propose(men[j].prefer[1]);
				men[j].asked[1] = true;
				}
			if(men[j].engaged == false && men[j].asked[2] == false){
				System.out.println(men[j].name + " proposes to " + men[j].prefer[2].name);
				men[j].propose(men[j].prefer[2]);
				men[j].asked[2] = true;
				}
			//end proposals
			
		}
		
		for(int i=0;i<3;i++)
			System.out.println(men[i].name + "'s match is " + men[i].match.name);

	}//end main
	
}
