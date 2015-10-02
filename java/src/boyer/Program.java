package boyer;

import java.util.List;

public class Program {

	public static void main(String[] args) {
	    String s = "i had to, Hence, i peed the fence. i don't see the adHence";
	    String pat = "ence";
	    MatchAbleString str = new MatchAbleString(s);
	    Pattern p = new Pattern(pat);
	    p.preprocess();
	
	    List<Integer> l = str.match(p, true);
	
	    for(Integer i : l)
	    {
	        System.out.println(i + " : " + s.substring(i, i + pat.length()));
	    }
	}

}
