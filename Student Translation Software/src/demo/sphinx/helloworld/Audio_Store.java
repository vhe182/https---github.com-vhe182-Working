package demo.sphinx.helloworld;

import java.util.ArrayList;

import DataOutput.Grading;
import Graphics.View;
import Timer.ReturnTime;
import Timer.TimerClass;
import edu.cmu.sphinx.frontend.util.Microphone;
import edu.cmu.sphinx.recognizer.Recognizer;
import edu.cmu.sphinx.result.Result;
import edu.cmu.sphinx.util.props.ConfigurationManager;
import edu.cmu.sphinx.util.props.PropertyException;

/**
 * this class stores the input stream from user in an array list.
 * as each is word is said it is passed and added the array list.
 * also calls the ReturnTime, Grading, and View Classes to update their
 * fields.
 * @author Stephen's Laptop
 *
 */

public class Audio_Store {
	private String[] masterString = {"This", "Nation", "was", "founded", "by", "men", "of", "many", "nations", "and", "backgrounds"};
	private ReturnTime retTime;
	private Grading g;
	private String audio_string;
	private View v;
	private boolean gate = true;
	private TimerClass timer;
	private float time;
	private float result;
	private boolean[] matches;
	//private ReturnTime retTime;
	private ArrayList<String> string_array;
	
	// store the view, timer, buffer time, and create arraylist
	public Audio_Store(View view){
		retTime = new ReturnTime();
		string_array = new ArrayList<String>();
		v = view;
		timer = v.timer;
		time = 0;
	}
	
	/**
	 * generates a grade at the end of user input stream.
	 * also updates the view
	 */
	public void generateGrade(){
		g = new Grading(this);
		g.gradeMatches();
		result = g.usersResult();
		matches = g.getMatchValues();
		v.fillGrade(matches, result, g.getMASTER_STRING_1(), retTime.get_Times());
	}
	
	public int getMasterSize(){
		return masterString.length;
	}
	
	public float getUsersResult(){
		return result;
	}
	
	public boolean[] matches(){
		return matches;
	}
	
	public View getView(){
		return v;
	}

	//call in the model for this to show
	public String getAudio_string() {
		return audio_string;
	}
	
	public ArrayList<String> getUserArrayList(){
		return this.string_array;
	}

	public void setAudio_string(String audio_string) {
		this.audio_string = audio_string;
	}	
	
	public void refreshUserLabel(){
		v.refreshUserInput(string_array);
	}
	/**
	 * method handles the strings from the input stream.
	 * updates the array list, view, and return time
	 * @param userString
	 */
	public void updateStringArray(String userString){
		string_array.add(userString);
		v.updateWordPane(userString);
		getNewTime(); // get the time interval
		retTime.pingBufferTime(time);
		
	}
	
	public void getNewTime(){
		time = timer.getfakeTimer();
	}
	
	public float updateDiffArray(){
		return time;
	}
	
	public void shutgate(){
		this.gate = false;
	}
	
	public boolean getGate(){
		return gate;
	}
}
