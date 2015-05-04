package AudioTest;

import java.io.File;
import java.applet.*;
import java.net.*;
import javax.swing.JFileChooser;

/**
 * An example of loading and playing a sound using a Clip. This complete class
 * isn't in the book ;)
 */
public class PlaySoundAppletTest {
	/**
	 * File that will be opened for playing 
	 * to the user
	 */
	public static File soundFile;
	/**
	 * importFile method allows the user to select an audio
	 * file and then plays the file or prints Exception if
	 * unable to play.
	 */
	public static void importFile(){
	 

		try {
			JFileChooser chooser = new JFileChooser();
			chooser.showOpenDialog(null);
			soundFile = chooser.getSelectedFile();
			AudioClip clip = Applet.newAudioClip(soundFile.toURI().toURL());
			//URL("file:C:\\Users\\Kevin\\git\\team-swooty\\team-swooty-project\\src\\AudioTest\\I have a dreamMLK_16kb.wav"));
			
			clip.play();
		} catch (MalformedURLException murle) {

			System.out.println(murle);
		}

	}

/**
 * should stop audio clip but have questions about this i will ask tonight
 * @param AudioClip
 */
public static void Stop(AudioClip clip){
	
	clip.stop();
}
}

