package demo.sphinx.helloworld;

import java.util.ArrayList;
/**
 * Stores the instruction messages that will be output
 * to the user before, during, and after starting
 * the program.
 * @author 
 *
 */
public class ProgramInstructions {
	/**
	 * introduction string message for user
	 */
	final private String premsg1 = "<html>To Initiate Recording:<br>";
	final private String premsg2 = "<br>1) Go to FILE-><br>";
	final private String premsg3 = "<br>2) Load option 1,2, or 3<br>";
	final private String premsg4 = "<br>4) Click PLAY button<br>";
	final private String premsg5 = "<br>5) Program must recognize 11 words before pressing STOP button\n<br></html>";
	
	/**
	 * Count down string message
	 */
	final private String inprocmsg1 = "3";
	final private String inprocmsg2 = "2";
	final private String inprocmsg3 = "1";
	final private String inprocmsg4 = "START!";
	
	/**
	 * Post User attempt message
	 */
	final private String postmsg1 = "<html>Finish<br>";
	final private String postmsg2 = "<br>Performance Statistics located under the GRADING tab<br>";
	final private String postmsg3 = "<br>Create an audio file (wave format) of the most recent attempt"
			+ " by clicking on the OUTPUT DATA button<br>";
	final private String postmsg4 = "<br>You can now choose a new audio file to try again"
			+ " or exit the program<br></html>";
	/**
	 * String ArrayLists where each message line of the pre,inproc,and post messages are stored
	 */
	private ArrayList < String > msg1;
	/**
	 * String ArrayLists where each message line of the pre,inproc,and post messages are stored
	 */
	private ArrayList < String > msg2;
	/**
	 * String ArrayLists where each message line of the pre,inproc,and post messages are stored
	 */
	private ArrayList < String > msg3;
	
	/**
	 * Constructor that stores all the messages into their respective ArrayLists
	 */
	public ProgramInstructions() {
		msg1 = new ArrayList<String>();
		msg1.add(premsg1);
		msg1.add(premsg2);
		msg1.add(premsg3);
		msg1.add(premsg4);
		msg1.add(premsg5);
		
		msg2 = new ArrayList<String>();
		msg2.add(inprocmsg1);
		msg2.add(inprocmsg2);
		msg2.add(inprocmsg3);
		msg2.add(inprocmsg4);
		
		msg3 = new ArrayList<String>();
		msg3.add(postmsg1);
		msg3.add(postmsg2);
		msg3.add(postmsg3);
		msg3.add(postmsg4);
		
	}
	/**
	 * get ArrayList for message 1
	 * @return ArrayList<String>
	 */
	public ArrayList < String > getmsg1(){
		return msg1;
	}
	/**
	 * get ArrayList for message 2
	 * @return ArrayList<String>
	 */
	public ArrayList < String > getmsg2(){
		return msg2;
	}
	/**
	 * get ArrayList for message 3
	 * @return ArrayList<String>
	 */
	public ArrayList < String > getmsg3(){
		return msg3;
	}
}
