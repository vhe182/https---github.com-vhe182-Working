package demo.sphinx.helloworld;

import Timer.TimerClass.TimeClass;

/**
 * get the number of words and time it took to say them
 * 
 * @author Stephen's Laptop
 *
 */

public class WordsPerSec {
	// holds words said per second
	private double wps;
	// words user spoke
	private int wordsSaid;
	// total user time taken
	private int timeElapsed;
	// total words user spoke
	private int total;
	// to get counter from timer class
	private TimeClass timer;
	
	/**
	 * instantiate class. assign TimeClass to timer
	 * @param t
	 */
	public WordsPerSec(TimeClass t) {
		timer = t;
		wordsSaid = 0;
		timeElapsed = 0;
		wps = 0;
		total = 0;
	}
	/**
	 * gets words spoken per second. very rough implementation
	 * @return
	 */
	public double calcWrdPerSec() {
		// doubles for division
		double tempCounter = timer.getCounter();
		double tempWordsSaid = wordsSaid;
		// user did not speak. counter is 0 is not allowed? may change
		if (tempCounter > 0 || tempWordsSaid == 0)
			return wps = 0;
		else
			wps = tempWordsSaid / tempCounter;
		// add words and time to total variables
		total += wordsSaid;
		timeElapsed += tempCounter;
		return wps;
	}
	// gets final result of user stream
	public double getfinalResult() {
		return total / timeElapsed;
	}
	/**
	 * getters and setters.
	 * setWPS may not be needed depending on how the calcWrdPerSec is called
	 * @param wordsSpoken
	 */
	public void setWPS(int wordsSpoken) {
		wordsSaid = wordsSpoken;
	}
	
	public int getTotalWords(){
		return wordsSaid;
	}
	
	public int getTimeElapsed(){
		return timeElapsed;
	}

	
}
