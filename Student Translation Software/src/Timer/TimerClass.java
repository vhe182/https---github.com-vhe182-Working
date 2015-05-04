package Timer;

import java.awt.event.*;
import java.awt.*;

import javax.swing.*;

public class TimerClass extends JPanel {
	
	JLabel promptLabel, timerLabel;
	int counter;
	JTextField tf;
	JButton button;
	Timer timer;
	static int fakeTime;
	public TimerClass(){
		setLayout(new GridLayout(2,2,5,5));
		
		//button = new JButton("Start timer");
		//add(button);
		
		timerLabel = new JLabel("Waiting...", SwingConstants.CENTER);
		add(timerLabel);
		
		event e = new event();
		//button.addActionListener(e);
	}

	//start stop the timer
	public void changeTimer(int i){
		if(i == 0)
		{
			TimeClass tc = new TimeClass(0);
			timer = new Timer(1000, tc);
			timer.start();
		
		}
		else if ( i == 1)
		{
		timerLabel.setText("Stopped!");
		if(timer != null)
		timer.stop();
		}
		else if(i == 2)
		{	
			//logic for pause needs to go here	
		}
	}
	public class event implements ActionListener {
		public void actionPerformed(ActionEvent e){
			TimeClass tc = new TimeClass(0);
			timer = new Timer(1000, tc);
			timer.start();
		}
	}
	public class TimeClass implements ActionListener {
		int counter; 
		public TimeClass(int counter){
			this.counter = counter;
			
		}
		
		public void actionPerformed(ActionEvent tc){
			counter++;
			fakeTime = counter;
			if(counter > -1){
				timerLabel.setText("" + counter);
			}
		}
		// added this to communicate with other classes
		public int getCounter(){
			return counter;
		}
	}
	public int getfakeTimer(){
		return fakeTime;
	}
	//only non view gui
	//this creates a gui of a gid layout so i can minupulate it in Graphics package
	public static void main(String args[]){
		TimerClass gui = new TimerClass();
		//gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		gui.setSize(100, 100);
		//gui.setTitle("Timer Program");
		
		gui.setVisible(true);
	}


}



















