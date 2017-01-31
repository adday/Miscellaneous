
public abstract class Key<KT extends Comparable> {
	private KT key;
	public Key(KT key){
		this.key = key;
	}
	public KT getKey(){
		return key;
	}	
}
