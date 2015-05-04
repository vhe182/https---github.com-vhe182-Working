package AudioTest;

import java.io.File;
import java.net.MalformedURLException;
import java.applet.*;

import javax.swing.JFileChooser;

/**
 * SuperAudioTest lets the user select the audio file of their choice and play it
 * 
 */
public class SuperAudioTest   {
  public static	File soundFile;
  public static AudioClip clip;
  public static AudioMan Manny;
	/*
	public static void main(String[] args) throws Exception {
		File soundFile;

				
			
			JFileChooser chooser = new JFileChooser();
			chooser.showOpenDialog(null);
		//chooser.showOpenDialog(null);
			soundFile = chooser.getSelectedFile();
			AudioClip clip = Applet.newAudioClip(soundFile.toURI().toURL());
			// URL("file:C:\\Users\\Kevin\\git\\team-swooty\\team-swooty-project\\src\\AudioTest\\halloween.wav"));

			clip.play();
			}
			*/
		
	
/**
 * selecting and returning the selected clip of the users choice
 * @return
 */
	public AudioClip clipReturn() {
		// TODO Auto-generated method stub
		//File soundFile;

		
		
		JFileChooser chooser = new JFileChooser();
		chooser.showOpenDialog(null);
	//chooser.showOpenDialog(null);
		soundFile = chooser.getSelectedFile();
		AudioClip clip = null;
		try {
			clip = Applet.newAudioClip(soundFile.toURI().toURL());
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// URL("file:C:\\Users\\Kevin\\git\\team-swooty\\team-swooty-project\\src\\AudioTest\\halloween.wav"));

		//clip.play();
		//Manny=new AudioMan(this);
		return clip;
	}
}
