package demo.sphinx.helloworld;

import Graphics.*;
import Timer.ReturnTime;
import edu.cmu.sphinx.frontend.util.Microphone;
import edu.cmu.sphinx.recognizer.Recognizer;
import edu.cmu.sphinx.result.Result;
import edu.cmu.sphinx.util.props.ConfigurationManager;
import edu.cmu.sphinx.util.props.PropertyException;

import java.io.File;
import java.io.IOException;
import java.net.URL;

public class HelloWorld implements Runnable {
	public View view;
	public Audio_Store storage;
	public HelloWorld(View view,Audio_Store storage){
		this.view = view;
		this.storage = storage;
	}
		
	public int size;
	
	@Override
	public void run() {
		try {
			int i = 0;
			String temp_string = "";
			URL url;
			
			url = HelloWorld.class.getResource("helloworld.config.xml");

			ConfigurationManager cm = new ConfigurationManager(url);
			Recognizer recognizer = (Recognizer) cm.lookup("recognizer");
			Microphone microphone = (Microphone) cm.lookup("microphone");


			/* allocate the resource necessary for the recognizer */
			
			recognizer.allocate();

			/* the microphone will keep recording until the program exits */
			if (microphone.startRecording()) {
				
				System.out.println("(Good morning | Hello | Fish | Dog | Computer | Good Bye | Stop | Team | Thank you)");
				System.out.println("(This | Nation | Was | Founded | By | Men | Of | Many | Nations | And | Backgrounds)");
				
				size = storage.getMasterSize();
				while (i != size) {
					System.out.println("Start speaking.");

					/*
					 * This method will return when the end of speech
					 * is reached. Note that the endpointer will determine
					 * the end of speech.
					 */ 
					
					Result result = recognizer.recognize();

					if (result != null) {
						String resultText = result.getBestFinalResultNoFiller();

						//FIGURE OUT HOW TO PLAY BACK RECORDING
						
						//Store audio and result string into storage class for later call back
						//Audio_Store check = new Audio_Store(result, resultText);
						
						System.out.println(resultText);
						storage.updateStringArray(resultText);
						System.out.println("You said: " + resultText + "\n");
						temp_string = temp_string + " " + resultText;
					} else {
						System.out.println("Error when recording.");
						//break;
						//return null;
					}
					i = i + 1;
				}
			} else {
				System.out.println("Cannot start microphone.");
				recognizer.deallocate();
				//System.exit(1);
			}	
			System.out.println("Recording is over");
			storage.refreshUserLabel();
			microphone.clear();
		    storage.generateGrade();
		} catch (IOException e) {
			System.err.println("Problem when loading HelloWorld: " + e);
			e.printStackTrace();
		} catch (PropertyException e) {
			System.err.println("Problem configuring HelloWorld: " + e);
			e.printStackTrace();
		} catch (InstantiationException e) {
			System.err.println("Problem creating HelloWorld: " + e);
			e.printStackTrace();
		}

	}
}


