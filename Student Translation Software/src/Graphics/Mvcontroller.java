package Graphics;

import AudioTest.*;
import DataOutput.Grading;

import javax.swing.JFrame;

import Timer.*;
import demo.sphinx.helloworld.*;
/**
 * The actual Main Controller class.  Calls
 * all necessary classes to get the program
 * running.
 */
public class Mvcontroller extends JFrame {
	
	
	/**
	 * Not sure what this does.  Your thoughts, Brandon?
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * Main class that calls all relevant classes and
	 * sets objects to necessary values.
	 * @param args
	 */
	public static void main(String[] args)
	{
		
		Audio_Store audio = null;
		TimerClass timer = new TimerClass();
		SuperAudioTest testSound = new SuperAudioTest();
		Model model = new Model(testSound,timer);
		
		
		View window = new View(model,audio,timer);
		audio = new Audio_Store(window);
		//Grading grader = new Grading(audio);
		Controller controller = new Controller(model,window,audio);
		
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);;
		window.setSize(1200,1000);
		window.registerListener(controller);
		window.setVisible(true);
	}
}