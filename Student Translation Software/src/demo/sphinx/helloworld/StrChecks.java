package demo.sphinx.helloworld;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;



/**
 * string compare class. from what I understand we will compare the user and
 * master strings when the user presses stop. This class compares the user
 * string in tokens against the master string in tokens.
 * 
 * @author Stephen's Laptop
 *
 */

public class StrChecks {
	// array list for user and master string
	private ArrayList<String> userstring;

	private List<String> masterString;
	// boolean trueOrFalse array, keeps track of which word indexes in the
	// actual string were correct. if we don't need this let me know
	private boolean[] matchValues;
	// total number of correct matches
	private float totalCorrectMatches;

	private float totalNumWords;
	//private Grading grade;
	/**
	 * constructor passes in the audio store user array list and the master
	 * string. master string is split into an array list based on white-spaces
	 * 
	 * @param aud
	 * @param mString
	 */
	public StrChecks(Audio_Store aud, String mString) {
		totalCorrectMatches = 0;
		masterString = new ArrayList<String>(Arrays.asList(mString.split(" ")));
		matchValues = new boolean[masterString.size()];
		Arrays.fill(matchValues, false); // fill the array with false values
		userstring = aud.getUserArrayList();
		totalNumWords = masterString.size();
	}

	/**
	 * compares the words by token. for a word to be a match the user string
	 * current index must be equal to its master string equivalent
	 */
	public void strComp() {
		System.out.printf("total word: %d", userstring.size());
		int i = 0, j = 0, k = 0;
		while (i < userstring.size() ) {
			if (userstring.get(i++).equalsIgnoreCase(masterString.get(j++))) {
				// user said correct word. update the array and total number of
				// matches
				matchValues[k] = true;
				totalCorrectMatches++;
			} 
			k++;
		}

	}
	
	public boolean[] getMatchValues(){
		return matchValues;
	}

	// return total number of matches for the grading and output java classes
	public float getTotalCorrectMatches() {
		return totalCorrectMatches;
	}
	
	public float getTotalNumWords(){
		return totalNumWords;
	}

}
