package Graphics;
import DataOutput.*;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;

import Timer.*;
import demo.sphinx.helloworld.*;
//create all shit to be pressed
public class View extends JFrame {
	/**
	 * 
	 */
	float userResult1;
	int totalCorrect=0;
	String master;
	ArrayList<Float> bufferTimes;
	private static final long serialVersionUID = 1L;
	
	//the master view
	private Model model;
	private Audio_Store audioReadIn = null;
	private Graphing graph = new Graphing(this);
	//stuff
	DefaultListModel<String> listModel;
	//menu for options if needed
	private JMenu menuFile;
	private JMenu menuSettings;
	private JMenu menuLoad; 
	private JMenuItem option1;
	private JMenuItem option2;
	private JMenuItem option3;
	//test user display for now
	private JPanel userDisplay;
	private JPanel programDisplay;
	//Panel to hold user interaction and panel to hold buttons
	JPanel userPanel;
	JPanel userSouth;
	JPanel userNorth;
	JPanel userCenter;
	JPanel userEast;
	JPanel userWest;
	JScrollPane wordPane;
	JList<?> currentWordList;
	//buttons for pressing for user to interact with
	JButton userRecord;
	JButton userOpenFile;
	JButton userPlay;
	JButton userStop;
	JButton userPause;
	//what the font will be
	private Font buttonFont = new Font("San-sarif", Font.BOLD, 20);
	private Font menuFont = new Font("Times New Roman",Font.BOLD, 14);
	//master tab pane that will have stuff
	private JTabbedPane tabview;
	private JPanel mainTab;
	private JLabel userInput;
	private JLabel programLabel;
	private JLabel userInputQuick;
	//grade tab shit
	JPanel gradeTab;
	JPanel gradePanel;
	JPanel gradeNorth;
	JPanel gradeSouth;
	JPanel gradeEast;
	JPanel gradeWest;
	JPanel gradeCenter;
	JLabel gradeTopLabel;
	JButton outputButton;
	JLabel outPutUser;
	JLabel bufferLabel;
	JLabel userSaid;
	JLabel userResultLabel;
	JLabel masterLabel;
	//timer
	private JPanel timerPanel;
	public TimerClass timer;

	private View View;
	ProgramInstructions programInstruction = new ProgramInstructions();
	public View(Model model,Audio_Store audio, TimerClass timer){
	
		super("Translation Grader v.7");
		this.audioReadIn = audio;
		
		//create the MENU BAR that holds the menu buttons
		//create Menu Bar for file options
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		
		//Creating what the gobal declared menu items will say
		//create menu item file for exit options
		menuFile = new JMenu("File");
		menuBar.add(menuFile);
		
		//create menu item settings for settings options
		menuSettings = new JMenu("Settings");
		menuBar.add(menuSettings);
		//set Fonts of menu buttons
		menuSettings.setFont(menuFont);
		menuFile.setFont(menuFont);
		
		//adding stuff to the JMENU items
		//add load options
		menuLoad = new JMenu("Load a Option");
		menuFile.add(menuLoad);
		//add load options
		option1 = new JMenuItem("Option1");
		option2 = new JMenuItem("Option2");
		option3 = new JMenuItem("Option3");
		menuLoad.add(option1);
		menuLoad.add(option2);
		menuLoad.add(option3);
		//add exit to under File
		JMenuItem exit = new JMenuItem("Exit");
		menuFile.add(exit);
		
		//add options under settings
		JMenuItem options = new JMenuItem("Options");
		menuSettings.add(options);

		
		//tab view for 1.0
		tabview = new JTabbedPane();
		tabview.setTabPlacement(JTabbedPane.BOTTOM);
		//add to view
		getContentPane().add(tabview);
		
		//different tabs
		//main tab
		
		mainTab = new JPanel();
		mainTab.setLayout(new BorderLayout());
		//mainTab.setBackground(Color.RED);
		tabview.addTab("mainTab", mainTab);
		
		//mainpanel
		userPanel = new JPanel();
		userSouth = new JPanel();
		userNorth = new JPanel();
		userCenter = new JPanel();
		userEast = new JPanel();
		userWest = new JPanel();
		
		//userPanel split up
		userPanel.setLayout(new BorderLayout());
		userPanel.setBackground(Color.WHITE);
		mainTab.add(userPanel);
		
		//split userpanel into 5 sections the north,south,center,east,west
		userPanel.add(userSouth,BorderLayout.SOUTH);
		userPanel.add(userNorth,BorderLayout.NORTH);
		userPanel.add(userCenter,BorderLayout.CENTER);
		userPanel.add(userEast,BorderLayout.EAST);
		userPanel.add(userWest,BorderLayout.WEST);
		
		//set size of the sections of userpanels
		//also sets buffer between panels so stuff isnt stack on top of eachother
		userSouth.setPreferredSize(new Dimension(200,200));
		userSouth.setMinimumSize(new Dimension(200,200));
		userNorth.setPreferredSize(new Dimension(200,300));
		userNorth.setMinimumSize(new Dimension(200,300));
		userCenter.setPreferredSize(new Dimension(200,600));
		userCenter.setMinimumSize(new Dimension(200,600));
		userEast.setPreferredSize(new Dimension(200,200));
		userEast.setMinimumSize(new Dimension(200,200));
		userWest.setPreferredSize(new Dimension(200,200));
		userWest.setMinimumSize(new Dimension(200,200));
		
		//set colors so i know where everything is
		userSouth.setBackground(Color.WHITE);
		userNorth.setBackground(Color.WHITE);
		userCenter.setBackground(Color.WHITE);
		userEast.setBackground(Color.WHITE);
		userWest.setBackground(Color.WHITE);
		//buttons that go in the south
		userRecord = new JButton("Start");
		userRecord.setBackground(Color.GREEN);
		userPause = new JButton("Pause");
		userPause.setBackground(Color.gray);
		userStop = new JButton("Stop");
		userStop.setBackground(Color.ORANGE);
		//add to view
		
		userSouth.add(userRecord);
		userSouth.add(userPause);
		userSouth.add(userStop);
		
		//set where buttons are going to be
		
		
		
		//program view  in the north winter is comming
		programDisplay = new JPanel();
		programDisplay.setBackground(Color.WHITE);
		//add to north
		userNorth.add(programDisplay,BorderLayout.CENTER);
		//set where its at
		programDisplay.setPreferredSize(new Dimension(700,200));
		programDisplay.setMinimumSize(new Dimension(700,200));
		//add border
		 TitledBorder titleProgramDisplay = BorderFactory.createTitledBorder("Program Display");
		 programDisplay.setBorder(titleProgramDisplay);
		//program label
		programLabel=new JLabel("These are where the instructions will be");
		programDisplay.add(programLabel);
		this.refreshProgramDisplay(programInstruction.getmsg1());
		//user view that has user stuff non buttons
		
		
		//user display in the center
		userDisplay = new JPanel();
		userDisplay.setBackground(Color.WHITE);
		//add to center
		userCenter.add(userDisplay);
		//create border
		 TitledBorder titleUserDisplay = BorderFactory.createTitledBorder("Quick Compare grade");
		 userDisplay.setBorder(titleUserDisplay);
		//set where its at
		userDisplay.setPreferredSize(new Dimension(700,200));
		userDisplay.setMinimumSize(new Dimension(700,200));
		
		//label that has all user stuff on it
		userInput = new JLabel("Welcome to Team Swooty Project.");
		userInputQuick = new JLabel("");
		userDisplay.add(userInput);
		userDisplay.add(userInputQuick);
		
		
		//gradeTab
		 gradeTab = new JPanel();
		gradeTab.setLayout(new BorderLayout());
		tabview.addTab("gradeTab",gradeTab);
		
		//timer
		this.timer = timer;
		TitledBorder titleTimer = BorderFactory.createTitledBorder("Timer");
		
		timer.setBorder(titleTimer);
		timer.setBackground(Color.WHITE);
		timer.setPreferredSize(new Dimension(100,100));
		timer.setMinimumSize(new Dimension(100,100));
		
		 userWest.add(timer);
		 //add jlist of words to view 
		 listModel = new DefaultListModel<String>();
		 currentWordList = new JList(listModel);
		 wordPane = new JScrollPane(currentWordList);
		 userEast.add(wordPane,BorderLayout.CENTER);
		 TitledBorder titleWordList = BorderFactory.createTitledBorder("Current Words");
		 wordPane.setBorder(titleWordList);
		 wordPane.setPreferredSize(new Dimension(200,100));
		 wordPane.setMinimumSize(new Dimension(200,100));
		 currentWordList.setVisibleRowCount(5);
		 
		
	}

	
	//add click abiltiy to all the buttons in the view
	public void registerListener(Controller controller)
	{
		
		
		
		//add clickablility to the File Menu
		Component[] components = menuFile.getMenuComponents();
		for(Component component : components){
			if(component instanceof AbstractButton){
				AbstractButton button = (AbstractButton) component;
				button.addActionListener(controller);
				button.setFont(menuFont);
			}
		}
		components = menuLoad.getMenuComponents();
		for(Component component : components){
			if(component instanceof AbstractButton){
				AbstractButton button = (AbstractButton) component;
				button.addActionListener(controller);
				button.setFont(menuFont);
			}
		}
		//add Clickability to the Settings Menu
		components = menuSettings.getMenuComponents();
		for(Component component : components){
			if(component instanceof AbstractButton){
				AbstractButton button = (AbstractButton) component;
				button.addActionListener(controller);
				button.setFont(menuFont);
			}
		}
		components = userSouth.getComponents();
		for(Component component : components){
			if(component instanceof AbstractButton){
				AbstractButton button = (AbstractButton) component;
				button.addActionListener(controller);
				button.setFont(buttonFont);
			}
		}
		
	}
	public void userImportView(Controller controller){
		//mainTab stuff
				//everything below here will handle the middle of the screen for all the user input stuff
		//remove the buttoms at and bottom and change the view to be a 
		/*BorderLayout layout = (BorderLayout) userPanel.getLayout();
		userNorth.remove(layout.getLayoutComponent(BorderLayout.SOUTH));
		userSouth.remove(layout.getLayoutComponent(BorderLayout.CENTER));
		userEast.remove(layout.getLayoutComponent(BorderLayout.NORTH));
		userWest.remove(layout.getLayoutComponent(BorderLayout.WEST));
		userCenter.remove(layout.getLayoutComponent(BorderLayout.EAST));*/
				//userPanel for all user output
				 
				userPanel.setLayout(new GridBagLayout());
				//create 5x5grid
				GridBagConstraints c = new GridBagConstraints();
				 c.fill = GridBagConstraints.HORIZONTAL;
				
				userPanel.setBackground(Color.WHITE);
				mainTab.add(userPanel,BorderLayout.CENTER);
				
				//userPanel Components
				//stop play button position
				userPlay = new JButton("Play");
			    userStop = new JButton("Stop");
				userPlay.setBackground(Color.GREEN);
				userStop.setBackground(Color.RED);
				userPlay.setPreferredSize(new Dimension(120,60));
				userStop.setPreferredSize(new Dimension(120,60));
				c.anchor = GridBagConstraints.PAGE_END;
				c.weighty = 2.0;
				//c.weightx = 2.0;
				c.gridx = 0;
				 c.gridy = 2;
				userPanel.add(userPlay, c);
				c.gridx = 3;
				 c.gridy = 2;
				userPanel.add(userStop, c);
				c.fill = GridBagConstraints.HORIZONTAL;
				c.ipady = 40;      
				c.weightx = 0.0;
				c.gridwidth = c.fill;
				c.gridx = 0;
				c.gridy = 1;
				//gray jpanel
				userDisplay = new JPanel();
				userDisplay.setBackground(Color.RED);
				userPanel.add(userDisplay,c);
				Component[] components = userPanel.getComponents();
				for(Component component : components){
					if(component instanceof AbstractButton){
						AbstractButton button = (AbstractButton) component;
						button.addActionListener(controller);
						button.setFont(buttonFont);
					}
				}
				//this.revalidate();
	}


	/*public void userRecordView(Controller controller) {
		// TODO Auto-generated method stub
		//remove bottom buttons from user view as they have served there purpose
		BorderLayout layout = (BorderLayout) mainTab.getLayout();
		mainTab.remove(layout.getLayoutComponent(BorderLayout.SOUTH));
		userPanel = new JPanel();
		userPanel.setLayout(null);
		userPanel.setBackground(Color.WHITE);
		mainTab.add(userPanel);
		
		userRecord = new JButton("Record");
		userRecord.setBackground(Color.RED);
		userPause = new JButton("Pause");
		userPause.setBackground(Color.gray);
		userStop = new JButton("Stop");
		userStop.setBackground(Color.ORANGE);
		//add to view
		userPanel.add(userRecord);
		userPanel.add(userPause);
		userPanel.add(userStop);
		
		//set where buttons are going to be
		userRecord.setLocation(200,320);
		userRecord.setSize(120, 50);
		userPause.setLocation(500,320);
		userPause.setSize(100, 50);
		userStop.setLocation(350,320);
		userStop.setSize(100, 50);
		
		//program view stuff
		programDisplay = new JPanel();
		programDisplay.setBackground(Color.YELLOW);
		userPanel.add(programDisplay);
		//set where its at
		programDisplay.setLocation(0,0);
		programDisplay.setSize(900,100);
		//program label
		programLabel=new JLabel("These are where the instructions will be");
		programDisplay.add(programLabel);
		//user view that has user stuff non buttons
		userDisplay = new JPanel();
		userDisplay.setBackground(Color.RED);
		userPanel.add(userDisplay);
		//set where its at
		userDisplay.setLocation(0, 100);
		userDisplay.setSize(900, 100);
		//label that has all user stuff on it
		userInput = new JLabel("Welcome to Team Swooty Project. Be prepared to follow instuctions below");
		userDisplay.add(userInput);
		
		//set size and location of user label 
		userInput.setLocation(10,50);
		userInput.setSize(100,100);
		
		Component[] components = userPanel.getComponents();
		for(Component component : components){
			if(component instanceof AbstractButton){
				AbstractButton button = (AbstractButton) component;
				button.addActionListener(controller);
				button.setFont(buttonFont);
			}
		}
	}
	
	
	public void updateView(Audio_Store audio){
		userInput.setText(audio.getAudio_string());
	}*/
	//call this steven
	public void updateWordPane(String word){
		listModel.addElement(word);
	}
	
	public void refreshProgramDisplay(ArrayList<String> userInputArray){
		StringBuilder buf =new StringBuilder();
	
		for(int i = 0; i < userInputArray.size(); i++){
		    buf.append(userInputArray.get(i));
		    if(i < userInputArray.size() -1){
		        buf.append("");
		    }
		}
		programLabel.setText(buf.toString());
		//userInput.setText(word);
		
		this.repaint();
	}
	//steven calls at end
	public void refreshUserInput(ArrayList<String> userInputArray){
		
		StringBuilder buf = new StringBuilder();
		for(int i = 0; i < userInputArray.size(); i++){
		    buf.append(userInputArray.get(i));
		    
		    if(i < userInputArray.size() -1){
		        buf.append(" ");
		    }
		}
		userInput.setText(buf.toString());
		//userInput.setText(word);
		this.repaint();
	}
	public ArrayList<String> getProgramMidInstructions(){
		return programInstruction.getmsg2();
	}
	public void quickgrade(){
		if(userResult1 >= 1 && userResult1 <= 60)
			userInputQuick.setText("F: Try harder");
		if(userResult1 >= 60 && userResult1 <= 70)
			userInputQuick.setText("D: Did you even Try?");
		if(userResult1 >= 70 && userResult1 <= 80)
			userInputQuick.setText("C: Study More");
		if(userResult1 >= 80 && userResult1 <= 90)
			userInputQuick.setText("B: Study More");
		if(userResult1 >= 90 && userResult1 <= 1000)
			userInputQuick.setText("A: Y U no Get A ++!");
		
	}
	public void generateGradeTab(){
		
		quickgrade();
		//create main panel
		gradePanel = new JPanel(new BorderLayout());
		//segment into 5 different sections
		gradeSouth = new JPanel();
		gradeNorth = new JPanel();
		gradeCenter = new JPanel(new BorderLayout());
		gradeEast = new JPanel(new BorderLayout());
		gradeWest = new JPanel(new BorderLayout());
		gradeSouth.setBackground(Color.RED);
		gradeNorth.setBackground(Color.GREEN);
		gradeCenter.setBackground(Color.YELLOW);
		gradeWest.setBackground(Color.YELLOW);
		gradeEast.setBackground(Color.BLACK);
		gradeTab.add(gradePanel);
		gradePanel.add(gradeSouth,BorderLayout.SOUTH);
		gradePanel.add(gradeNorth,BorderLayout.NORTH);
		gradePanel.add(gradeCenter,BorderLayout.CENTER);
		gradePanel.add(gradeEast,BorderLayout.EAST);
		gradePanel.add(gradeWest,BorderLayout.WEST);
		//set dimensions
		gradeSouth.setPreferredSize(new Dimension(333,200));
		gradeSouth.setMinimumSize(new Dimension(333,200));
		gradeNorth.setPreferredSize(new Dimension(333,400));
		gradeNorth.setMinimumSize(new Dimension(333,400));
		gradeCenter.setPreferredSize(new Dimension(333,600));
		gradeCenter.setMinimumSize(new Dimension(333,600));
		
		gradeTopLabel = new JLabel("Grade of current run",SwingConstants.CENTER);
		
		//add to view
		gradeNorth.add(gradeTopLabel,BorderLayout.SOUTH);
		
		//output button
		outputButton = new JButton("Output");
		//gradeSouth.add(outputButton,BorderLayout.SOUTH);
		
		//middle stuff
		userResultLabel = new JLabel(" ",SwingConstants.CENTER);
		userSaid = new JLabel(" ", SwingConstants.CENTER);
		bufferLabel = new JLabel(" ",SwingConstants.CENTER);
		StringBuilder buf = new StringBuilder();
		for(int i = 0; i < bufferTimes.size(); i++){
		    buf.append(bufferTimes.get(i));
		    
		    if(i < bufferTimes.size() -1){
		        buf.append(" ");
		    }
		}
		userResultLabel.setText("Your Resulting Grade Score:" + userResult1);
		bufferLabel.setText("Times inbetween words: " + buf.toString());
		gradeCenter.add(userResultLabel,BorderLayout.NORTH);
		masterLabel = new JLabel("What was played to you:" + master,SwingConstants.CENTER);
		gradeCenter.add(bufferLabel,BorderLayout.SOUTH);
		gradeCenter.add(masterLabel,BorderLayout.CENTER);
		graph.generateGraph();
	}
	//matches is the correct shit 
	//userResult = float and its the grade of words right
	//masterstring is what were testing against
	public void fillGrade(boolean[] matches, float userResult, String masterString,ArrayList<Float> bufferTimes){
		TestFileOutput tfo = new TestFileOutput();
		this.bufferTimes = bufferTimes;
		this.master = masterString;
		//tfo.setFileMatches(matches);
		//tfo.s
		System.out.printf("\nuser result: %f \n",userResult);
		System.out.printf("%s\n",masterString);
		tfo.writeResults(userResult, masterString);
		for(boolean match: matches)
		{
			System.out.print(match + " ");
			tfo.writeMatch(match);
			if(match == true)
				totalCorrect++;
		}
		for(Float match: bufferTimes)
		{
			System.out.print("\n"+  match + " ");
			tfo.writeBuffTimes(match);
			//System.out.print("\n");
		}
		this.userResult1 = userResult;
		tfo.closefile();
	}
}