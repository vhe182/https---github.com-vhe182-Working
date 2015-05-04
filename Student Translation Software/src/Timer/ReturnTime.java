package Timer;

import java.util.ArrayList;

import Timer.TimerClass.TimeClass;
/**
 * ReturnTime class receives two times,
 * takes the difference and stores
 * the difference in an ArrayList.  Can
 * then be called later by some other
 * @author 
 *
 */
public class ReturnTime {
	
	TimerClass temp = new TimerClass();
	 /**
	 * timediffs stores the buffer time in an
	 * ArrayList (Integer)
	 * and contains methods for accessing the buffer times
	 */
	private ArrayList<Float> timediffs = new ArrayList<Float>();
	/**
	 * the current time should receive whatever second is 
	 * actually displayed on the timer
	 */
	private float currtime;
	/**
	 * stores the previous currtime
	 */
	private float prevtime;

	/**
	 * Sets currtime and prevtime to 0.
	 * 
	 * @param float curr
	 */
	public ReturnTime (){	
		currtime = 0;
		prevtime = 0;
	}
	/**
	 * 
	 * 
	 * @param float curr
	 * @return float
	 */
	public void pingBufferTime(float time){
		this.prevtime = currtime;
		this.currtime = time;
		timediffs.add(currtime - prevtime);
	}
	public ArrayList<Float> get_Times(){
		return timediffs;
	}
}
