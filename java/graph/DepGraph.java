import java.util.ArrayList;

public class DepGraph {	
	// n: number of nodes
	private int n;
	// number of edges
	private int m;

	// graph has adjLists mapping sources to destination lists 
	private ArrayList<AdjList> graph;
	private boolean debug;

	public DepGraph(boolean debug){
		this.debug = debug;
		graph = new ArrayList<AdjList>();
	}

	public String toString(){
		String res = "Dependence Graph: " + n + " nodes, " + m + " edges\n";
		for (int i = 0; i<graph.size(); i++)
			res += i + ": " + graph.get(i) + "\n";
		return res;
	}

        // return whether graph contains the source
	private boolean graphContains(String source){
		for(int i = 0;i<graph.size();i++)
			if(graph.get(i).getSource().equals(source))
				return true;
		return false;
	}
	
	// add **new** source entry with empty destList to end of graph
	public void addAdjList(String source) throws GraphException{
		if (graphContains(source))
			throw new GraphException(source +" already defined!"); 		
		else{
			graph.add(new AdjList(source));
			n++;
		}
	}
	
	// get the adjList of source
	private AdjList getAdjList(String source) throws GraphException{
		if (!graphContains(source))
			throw new GraphException(source +" undefined!");
		else
			for(int i = 0; i < graph.size(); i++)
	    		if(graph.get(i).getSource().equals(source))
	    			return graph.get(i);
		return null;
	}

	// if dest not in the source AdjList add it to the source adjList
	// increment inDegree in dest adjList
	public void addDest(String source, String dest) throws GraphException{
		if(!getAdjList(source).contains(dest)){
			getAdjList(source).addDest(dest);
			getAdjList(dest).incrInDegree();
			m++;}
		else
			throw new GraphException(dest +" is in source!");
	}


	public static void main(String[] args) throws GraphException{
		DepGraph dG = new DepGraph(false);
		dG.addAdjList("a");
		dG.addAdjList("b");
		dG.addAdjList("c");
		dG.addAdjList("d");
		dG.addAdjList("e");
		//dG.addAdjList("e");  // checking graph exception

		dG.addDest("a","c");
		dG.addDest("a","d");

		dG.addDest("b","c");
		dG.addDest("b","d");

		dG.addDest("c","d");

		dG.addDest("c","e");
		dG.addDest("d","e");

		System.out.println(dG);

	}


}
