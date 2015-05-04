package AudioTest;

import java.applet.Applet;
import java.applet.AudioClip;
import java.io.File;
import java.net.MalformedURLException;
//import java.net.URL;

import javax.swing.JFileChooser;


public class AudioOptions {
	/**
	 * File that will be opened for playing to the user
	 */
	public static File soundFile;
	public static int setOption;
	
    public static int stop;
	
    public static int play;
    public static AudioClip clip;
	/**
	 * importFile method allows the user to select an audio file and then plays
	 * the file or prints Exception if unable to play.
	 */

	public static void  importFile(int setOption) {
		//int option= Controller.getOption();

		if (setOption==1) {
			try {
				/*
				URL url = new URL(
						"/team-swooty-project/AudioText/civilrightsJFK.wav");
				AudioClip clip = Applet.newAudioClip(url);
				clip.play();
				*/
				JFileChooser chooser = new JFileChooser();
				chooser.showOpenDialog(null);
				soundFile = chooser.getSelectedFile();
				AudioClip clip = Applet.newAudioClip(soundFile.toURI().toURL());
				//Play(clip);
				/*
				if(play==1){
					clip.play();
				}
				
				if(stop==1){
					PlaySoundAppletTest.Stop(clip);
				}
				*/
				
			} catch (MalformedURLException murle) {
				System.out.println(murle);
			}

		}
		if (setOption==2) {
			try {
				/*
				URL url = new URL(
						"/team-swooty-project/AudioText/I have a dreamMLK_16kb.wav");
				AudioClip clip = Applet.newAudioClip(url);
				clip.play();
				*/
				JFileChooser chooser = new JFileChooser();
				chooser.showOpenDialog(null);
				soundFile = chooser.getSelectedFile();
				AudioClip clip = Applet.newAudioClip(soundFile.toURI().toURL());
				/*
				if(play==2){
					clip.play();
				}
				
				if(stop==1){
					PlaySoundAppletTest.Stop(clip);
				}
				*/
			} catch (MalformedURLException murle) {
				System.out.println(murle);
			}
		}
		
		if (setOption==3) {
			try {
				/*
				URL url = new URL(
						"/team-swooty-project/AudioText/womensrighthumanrightsHC.wav");
				AudioClip clip = Applet.newAudioClip(url);
				clip.play();
				*/
				JFileChooser chooser = new JFileChooser();
				chooser.showOpenDialog(null);
				soundFile = chooser.getSelectedFile();
				AudioClip clip = Applet.newAudioClip(soundFile.toURI().toURL());
				/*
				if(play==3){
					clip.play();
				}
				if(stop==1){
					PlaySoundAppletTest.Stop(clip);
				}
				*/
				
			} catch (MalformedURLException murle) {
				System.out.println(murle);
			}
			
		}
		
	}
	public static void Stop(AudioClip clip){
		clip.stop();
	}
	
	public static void Play(AudioClip clip){
		clip.play();
	}
	public void setAudio(AudioClip clip) {
        this.clip = clip;
     }
    public AudioClip getClip() {
        return clip;
    }


}