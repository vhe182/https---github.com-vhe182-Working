package AudioTest;

import java.applet.AudioClip;
/**
 * class that lets us play and play and stop the audio in coordination with the play and stop buttons
 * 
 */
public class AudioMan {
	
	public SuperAudioTest Audio;
	public AudioClip audioClip;
	public AudioMan(AudioClip clip){
		this.audioClip=clip;
	}
	
	/**
	 * Plays the audio clip when you push the play button
	 */
 public void AudioRun(){
	 audioClip.play();
 }
 
 /**
  * stops the audio clip when you push the stop button
  */
		 
 public void AudioStop(){
	 audioClip.stop();
 }
}
