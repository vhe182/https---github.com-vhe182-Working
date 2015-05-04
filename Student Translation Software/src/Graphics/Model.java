package Graphics;
import java.applet.AudioClip;

import Timer.*;
import AudioTest.*;
import demo.sphinx.helloworld.*;
public class Model {
	public SuperAudioTest test;
	public HelloWorld voice;
	public TimerClass timer;
	public AudioClip clip;
	AudioMan manny;
	public Model(SuperAudioTest test,  TimerClass timer){
		this.test = test;
		
		this.timer = timer;
		
	}
	
	public void userImport(int i){
		clip = test.clipReturn();
		
		//test.Play();
	}
	
	public void userRecord(){
		
		//String temp;
		//temp = voice.begin_Audio(null);
		//t1 = new Thread(new HelloW());
		//t1.start();
	}
	public void userStart(){
		if(clip != null)
		{
		 manny = new AudioMan(clip);
		manny.AudioRun();
		}
		timer.changeTimer(0);
		
	}
	public void userStop(){
		//System.out.printf("%d\n",timer.getfakeTimer());
		//send a flag to helloW
		//voice.something(1);
		//SuperAudioTest.Manny.AudioStop();
		
		timer.changeTimer(1);
	}
	public void userPause(){
		//need to do somthing here 
		timer.changeTimer(2);
	}
}
