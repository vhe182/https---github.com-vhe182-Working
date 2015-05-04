package Graphics;
import AudioTest.*;

import java.awt.Button;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import Timer.*;
import demo.sphinx.helloworld.*;
//where the buttons will do shit
public class Controller implements ActionListener {
	
	//the master model that is created in MVC
	private Model model;
	
	//the view of the buttons and the menu and user stuff
	private View view;
	private Audio_Store storage;
	Thread t1;
	//save model and view to mess with stuff
	public Controller(Model model, View view,Audio_Store storage){
		this.model = model;
		this.view = view;
		this.storage = storage;
	}
	
	
	@Override
	public void actionPerformed(ActionEvent press) {
		// TODO Auto-generated method stub
		String command = press.getActionCommand();
		if(command.equals("Exit")){
			System.exit(0);
		}
		else if(command.equals("Options")){
			//System.exit(0);
		}
		else if(command.equals("Start")){
			HelloWorld thread = new HelloWorld(view,storage);
			t1 = new Thread(thread);
			t1.start();
			
			model.userStart();
			
		}
		else if(command.equals("Play")){
			System.exit(0);
		}
		else if(command.equals("Stop")){
			ProgramInstructions programInstruction = new ProgramInstructions();
			model.userStop();
			//view.refreshUserInput();
			view.refreshProgramDisplay(programInstruction.getmsg3());
			view.generateGradeTab();
			//view.updateWordPane("string");
			//PlaySoundAppletTest.Stop();
		}
		else if(command.equals("Pause")){
			model.userPause();
		}
		else if(command.equals("Option1")){
			model.userImport(1);
			
			
		}
		else if(command.equals("Option2")){
			model.userImport(2);
			
		}
		else if(command.equals("Option3")){
			model.userImport(3);
			
		}
		else if(command.equals("Output")){
			System.out.print("Shit got pressed");
			
		}
	}

}