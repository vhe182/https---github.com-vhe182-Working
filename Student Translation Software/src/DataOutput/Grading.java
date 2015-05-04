package DataOutput;

import Graphics.View;
import demo.sphinx.helloworld.Audio_Store;
import demo.sphinx.helloworld.StrChecks;

/**
 *stores the master strings and audio store objects.
 *grade is determined on number of correct words spoken compared
 *to total words. Also keeps track of the index of the words which
 *were spoken correctly
 */


public class Grading {
	
	private Audio_Store audStore;

	private StrChecks sChecks;

	private boolean[] matchValues;

	private float userResult;

	private View v;

	private String MASTER_STRING_1 = "This Nation was founded by men of many nations and backgrounds";

	private String MASTER_STRING_2;

	private String MASTER_STRING_3;

	private String user_string_1;

	private String user_string_2;

	private String user_string_3;

	private int speak_time_1;

	private int speak_time_2;

	private int speak_time_3;

	/**
	 * constructor takes in an audio store object, StrChecks object, and sets a view
	 * @param a
	 */
	public Grading(Audio_Store a) {
		audStore = a;
		this.v = a.getView();
		sChecks = new StrChecks(audStore, MASTER_STRING_1);
	}
    /**
     * call to Strchecks to grade the user input against the master string. compare
     * words by token
     */
	public void gradeMatches() {
		sChecks.strComp();
		matchValues = sChecks.getMatchValues(); // get the boolean values of the compares
	}

	public boolean[] getMatchValues() {
		return matchValues;
	}

	public void displayMatches() {
		for (int i = 0; i < matchValues.length; i++) {
			if (matchValues[i] == true) {
				System.out.println("Right");
			} else {
				System.out.println("Wrong");
			}
		}
	}
 /**
  * the result is the (totalcorrectmatches / totalnumofwords) * 100
  * @return
  */
	public float usersResult() {
		if (sChecks.getTotalCorrectMatches() == 0)
			return 1;
		else {
			userResult = sChecks.getTotalCorrectMatches()
					/ sChecks.getTotalNumWords();
			return userResult * 100;
		}
	}

	public String getMASTER_STRING_1() {
		return MASTER_STRING_1;
	}

	public void setMASTER_STRING_1(String mASTER_STRING_1) {
		MASTER_STRING_1 = mASTER_STRING_1;
	}

	public String getMASTER_STRING_2() {
		return MASTER_STRING_2;
	}

	public void setMASTER_STRING_2(String mASTER_STRING_2) {
		MASTER_STRING_2 = mASTER_STRING_2;
	}

	public String getMASTER_STRING_3() {
		return MASTER_STRING_3;
	}

	public void setMASTER_STRING_3(String mASTER_STRING_3) {
		MASTER_STRING_3 = mASTER_STRING_3;
	}

	public String getUser_string_1() {
		return user_string_1;
	}

	public void setUser_string_1(String user_string_1) {
		this.user_string_1 = user_string_1;
	}

	public String getUser_string_2() {
		return user_string_2;
	}

	public void setUser_string_2(String user_string_2) {
		this.user_string_2 = user_string_2;
	}

	public String getUser_string_3() {
		return user_string_3;
	}

	public void setUser_string_3(String user_string_3) {
		this.user_string_3 = user_string_3;
	}

	public int getSpeak_time_1() {
		return speak_time_1;
	}

	public void setSpeak_time_1(int speak_time_1) {
		this.speak_time_1 = speak_time_1;
	}

	public int getSpeak_time_2() {
		return speak_time_2;
	}

	public void setSpeak_time_2(int speak_time_2) {
		this.speak_time_2 = speak_time_2;
	}

	public int getSpeak_time_3() {
		return speak_time_3;
	}

	public void setSpeak_time_3(int speak_time_3) {
		this.speak_time_3 = speak_time_3;
	}

	/**
	 * Compare two strings
	 */
	public boolean CompareString(String master, String user) {
		if (master.equals(user) == true) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Find the average time
	 */
	public double AverageTime(int t1, int t2, int t3) {
		double aver = t1 + t2 + t3;
		aver = aver / 3;

		return (aver);
	}

	/**
	 * performs 3 checks between the correct/expected string and the string
	 * received from the user.
	 * 
	 * @return 0,1,2,3 as a flag for various true/false configurations and -1 on
	 *         error
	 */
	public int NumberCorrect() {
		boolean comp1;
		boolean comp2;
		boolean comp3;
		comp1 = CompareString(getMASTER_STRING_1(), getUser_string_1());
		comp2 = CompareString(getMASTER_STRING_2(), getUser_string_2());
		comp3 = CompareString(getMASTER_STRING_3(), getUser_string_3());

		if (comp1 == false && comp2 == false && comp3 == false) {
			return (0);
		} else if (comp1 == false && comp2 == false && comp3 == true) {
			return (1);
		} else if (comp1 == false && comp2 == true && comp3 == false) {
			return (1);
		} else if (comp1 == false && comp2 == true && comp3 == true) {
			return (2);
		} else if (comp1 == true && comp2 == false && comp3 == false) {
			return (1);
		} else if (comp1 == true && comp2 == false && comp3 == true) {
			return (2);
		} else if (comp1 == true && comp2 == true && comp3 == false) {
			return (2);
		} else if (comp1 == true && comp2 == true && comp3 == true) {
			return (3);
		} else
			return (-1);
	}

}
