package AudioTest;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.sound.sampled.*;

/**
 * Used with Premission from Professor Richard BaldWin
 * http://www.dickbaldwin.com/
 * 
 * Richard Baldwin is a college professor (at Austin Community College in Austin, TX) and private consultant whose primary focus is a combination of Java, C#, and XML. In addition to the many platform and/or language independent benefits of Java and C# applications, he believes that a combination of Java, C#, and XML will become the primary driving force in the delivery of structured information on the Web.
 * Richard has participated in numerous consulting projects and he frequently provides onsite training at the high-tech companies located in and around Austin, Texas.  He is the author of Baldwin's Programming Tutorials, which has gained a worldwide following among experienced and aspiring programmers. He has also published articles in JavaPro magazine.
 * Richard holds an MSEE degree from Southern Methodist University and has many years of experience in the application of computer technology to real-world problems.

 * Baldwin@DickBaldwin.com
 * 
 */

/**
 * AudioRecord class extends a JFrame to allow the recording of the user's
 * attempt at ghosting.
 * 
 * When the Stop button is clicked, a wave file is created in the following
 * directory:
 * 
 * git\team-swooty\team-swooty-project
 * 
 * The file is automatically named:
 * 
 * junk.wav
 * 
 */
public class AudioRecord extends JFrame {
	/**
	 * audioFormat stores the type of audio that is received.
	 */
	AudioFormat audioFormat;
	/**
	 * targetDataLine is a type of audio file descriptor where audio data can be
	 * read in as bits.
	 */
	TargetDataLine targetDataLine;
	/**
	 * captureBtn stores true or false depending on whether the appropriate
	 * button is pressed.
	 */
	final JButton captureBtn = new JButton("Capture");
	/**
	 * stopBtn stores true or false depending on whether the Stop button is
	 * pressed.
	 */
	final JButton stopBtn = new JButton("Stop");
	/**
	 * JPanel for buttons. Will be removed since the audio record functionality
	 * will be incorporated into the JPanel already created in the GUI package.
	 */
	final JPanel btnPanel = new JPanel();
	/**
	 * btnGroup for buttons. Will be removed since the audio record
	 * functionality will be incorporated into the JPanel already created in the
	 * GUI package.
	 */
	final ButtonGroup btnGroup = new ButtonGroup();
	/**
	 * waveBtn will be used to give the user the option to choose which audio
	 * format they will like their recorded attempt to output as. Currently will
	 * only output to wave format until later revisions/bug fixes.
	 */
	final JRadioButton waveBtn = new JRadioButton("WAVE");

	/**
	 * Main method used for testing the code, will eventually be removed.
	 * 
	 * 
	 * @param args
	 */
	public static void main(String args[]) {
		new AudioRecord();
	}

	/**
	 * AudioRecord Constructor:
	 * 
	 * Sets instance variables capturBtn to true and stopBtn to false. Registers
	 * and ActionListener to captureBtn. Will record input until the stopBtn
	 * registers as true (Stop button is clicked).
	 * 
	 * 
	 */
	public AudioRecord() {// constructor
		captureBtn.setEnabled(true);
		stopBtn.setEnabled(false);

		// Register anonymous listeners
		captureBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				captureBtn.setEnabled(false);
				stopBtn.setEnabled(true);
				// Capture input data from the
				// microphone until the Stop button is
				// clicked.
				captureAudio();
			}// end actionPerformed
		}// end ActionListener
				);// end addActionListener()

		stopBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				captureBtn.setEnabled(true);
				stopBtn.setEnabled(false);
				// Terminate the capturing of input data
				// from the microphone.
				targetDataLine.stop();
				targetDataLine.close();
			}// end actionPerformed
		}// end ActionListener
		);// end addActionListener()

		// Put the buttons in the JFrame
		getContentPane().add(captureBtn);
		getContentPane().add(stopBtn);

		btnGroup.add(waveBtn);
		btnPanel.add(waveBtn);

		// Put the JPanel in the JFrame
		getContentPane().add(btnPanel);

		// Finish the GUI and make visible
		getContentPane().setLayout(new FlowLayout());
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(300, 120);
		setVisible(true);
	}// end constructor

	/**
	 * This method captures audio input from a microphone and saves it in an
	 * audio file.
	 */
	private void captureAudio() {
		try {
			// Get things set up for capture
			audioFormat = getAudioFormat();
			DataLine.Info dataLineInfo = new DataLine.Info(
					TargetDataLine.class, audioFormat);
			targetDataLine = (TargetDataLine) AudioSystem.getLine(dataLineInfo);

			// Create a thread to capture the microphone
			// data into an audio file and start the
			// thread running. It will run until the
			// Stop button is clicked. This method
			// will return after starting the thread.
			new CaptureThread().start();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(0);
		}// end catch
	}// end captureAudio method

	/**
	 * This method creates and returns an AudioFormat object for a given set of
	 * format parameters. If these parameters don't work well for you, try some
	 * of the other allowable parameter values, which are shown in comments
	 * following the declarations.
	 * 
	 * @return AudioFormate
	 */

	private AudioFormat getAudioFormat() {
		float sampleRate = 8000.0F;
		// 8000,11025,16000,22050,44100
		int sampleSizeInBits = 16;
		// 8,16
		int channels = 1;
		// 1,2
		boolean signed = true;
		// true,false
		boolean bigEndian = false;
		// true,false
		return new AudioFormat(sampleRate, sampleSizeInBits, channels, signed,
				bigEndian);
	}// end getAudioFormat

	/**
	 * Inner class to capture data from microphone and write it to an output
	 * audio file.
	 */
	class CaptureThread extends Thread {
		public void run() {
			AudioFileFormat.Type fileType = null;
			File audioFile = null;

			// Set the file type and the file extension
			// based on the selected radio button.
			// if(aifcBtn.isSelected()){

			if (waveBtn.isSelected()) {
				fileType = AudioFileFormat.Type.WAVE;
				audioFile = new File("junk.wav");
			}// end if

			try {
				targetDataLine.open(audioFormat);
				targetDataLine.start();
				AudioSystem.write(new AudioInputStream(targetDataLine),
						fileType, audioFile);
			} catch (Exception e) {
				e.printStackTrace();
			}// end catch

		}// end run
	}// end inner class CaptureThread
}