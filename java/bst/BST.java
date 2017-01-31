

public class BST {
	// this Binary Search Tree is used for the implementation of the 
	// symbol tables containing Symbols: (key,value) pairs
	// A Symbol is a Comparable object containing a String Identifier key  
	// and an Integer value 
	private BSTNode<Symbol> root;

	//empty tree
	public BST(){
		this.root = null;
	}

	public boolean isEmpty(){
		return root==null;
	}

	public void insertItem(Symbol item) throws BSTException{
		root = insertItem(root, item);
	}

	private BSTNode<Symbol> insertItem(BSTNode<Symbol> node, Symbol item) throws BSTException{
		BSTNode newSubTree;
		if(node == null){
			node = new BSTNode(item);
			return node;}
		String tok = node.getItem().getKey();
		if(item.getKey().compareTo(tok) < 0){
			newSubTree = insertItem(node.getLeft(),item);
			node.setLeft(newSubTree);
			return node;}
		if(item.getKey().compareTo(tok) > 0){
			newSubTree = insertItem(node.getRight(), item);
			node.setRight(newSubTree);
			return node;
		}
		//ERROR: inserting existing item
		else
			throw new BSTException("Inserting exisiting item!");
	}

	public Symbol retrieveItem(String key){
		return retrieveItem(root,key);
	}
	
	private Symbol retrieveItem(BSTNode<Symbol> node, String key){
		Symbol treeItem;
		if(node==null)
			treeItem = null;
		else{
			Symbol nodeItem = node.getItem();
			if(key.compareTo(nodeItem.getKey()) == 0)
				//found
				treeItem = nodeItem;
			else if(key.compareTo(nodeItem.getKey()) < 0)
				//search left
				treeItem = retrieveItem(node.getLeft(), key);
			else
				// search right
				treeItem = retrieveItem(node.getRight(), key);
		}
		return treeItem;
	}
	

	public void preorderTraverse(){
		if (!isEmpty())
			preorderTraverse(root,"");
		else
			System.out.println("root is null");
	}

	public void preorderTraverse(BSTNode<Symbol> node, String indent){
		System.out.println(indent+node.getItem());		
		if(node.getLeft()!=null) {
			System.out.println(indent+"left");
			preorderTraverse(node.getLeft(),indent+" ");
		}

		if(node.getRight()!=null) {
			System.out.println(indent+"right");
			preorderTraverse(node.getRight(),indent+" ");
		}
	}

}
