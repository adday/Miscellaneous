import java.util.Hashtable;

public class Tree {
    private TreeNode root;
    
    //empty tree
    public Tree(){
    	this.root = null;
    }
    
    // rootItem, empty children
    public Tree(TreeNode root){
    	this.root = root;
    }
    public TreeNode root(){
    	return this.root;
    }
    
    public boolean isEmpty(){
    	return root == null;
    }
    
    
    public void preorderTraverse(){
    	if (!isEmpty())
    		preorderTraverse(root,"");
    	else
    		System.out.println("root is null");
    }
    
	public void preorderTraverse(TreeNode node, String indent){
		System.out.println(indent+node.getItem());
		if(node.getLeft()!=null) preorderTraverse(node.getLeft(),indent+" ");
		if(node.getRight()!=null) preorderTraverse(node.getRight(),indent+" ");
		
	}
	
	//evaluates an expression containing numbers and identifiers
	public Integer postorderEval(TreeNode node, String indent, Hashtable<String,Integer> symTab){
    	Integer res = null;
    	Integer leftVal = null;
    	Integer rightVal = null;
    	if(isEmpty())//tree is empty
    		return null;  	
    	this.root = node.getLeft();
    	leftVal = postorderEval(this.root, indent, symTab);
    	this.root = node.getRight();
    	rightVal = postorderEval(this.root, indent, symTab); 	
    	if(node.getItem().matches("[0-9]+") && (node.getLeft() == null && node.getRight() == null) )//root is a number
    		res = Integer.parseInt(node.getItem());
    	else if(node.getItem().matches("[A-Za-z0-9]*")){
    		try{//try used as symbol may not exist in symTab
    			res = symTab.get(node.getItem());}
    		catch(Exception e){
    			System.out.println("undefined identifier: " + node.getItem());
    		}}
    	//evaluate left and right with appropriate operand
    	if(node.getItem().equals("+"))
    		res = leftVal + rightVal;
    	else if(node.getItem().equals("-"))
    		res = leftVal - rightVal;
    	else if(node.getItem().equals("*"))
    		res = leftVal * rightVal;
    	else if(node.getItem().equals("/"))
    		res = leftVal / rightVal;		
    	return res;
    }
}