
public class TreeNode {
	
        // DON'T CHANGE THIS CODE

	private String item;
	private TreeNode left;
	private TreeNode right;
	
        // constructor for node without children
        // set left and right to null
	public TreeNode(String item){
		this.item = item;
		left = null;
		right = null;
	}

        // constructor for node with children
	public TreeNode(String item, TreeNode left, TreeNode right){
		this.item = item;
		this.left = left;
		this.right = right;
	}
	
	String getItem(){
		return item;
	}
	
	TreeNode getLeft(){
		return left;
	}
	
	TreeNode getRight(){
		return right;
	}
	
	public String toString(){
		if(left==null && right == null)
			return "leaf: " + item;
		else
			return "internal: " + item;
		
	}
	
	public static void main(String[] args){
		TreeNode tn1 = new TreeNode("abc");
		TreeNode tn2 = new TreeNode("stu");
		TreeNode root = new TreeNode("pqr",tn1,tn2);
		
		System.out.println("root: " + root);
		System.out.println("  left:  " + root.getLeft());
		System.out.println("  right: " + root.getRight());
		
	}
	
}
