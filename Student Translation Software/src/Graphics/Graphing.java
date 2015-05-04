package Graphics;

import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Graphing {
	View view;
	public Graphing(View view){
		this.view = view;
	}
	
	//declarations for the graphic
	JPanel graphPanel;
	JLabel graphLabel;
	JLabel xaxis = new JLabel("Time");
	JLabel yaxis = new JLabel("Number of correct matches");
	JLabel yaxis1 = new JLabel("Time of buffer between Words");
	//generate the view for the graphs
	
	public void generateGraph(){
		//generate the graphics for the graphics
		graphPanel = new JPanel();
		graphPanel.setBackground(Color.BLACK);
		graphPanel.setPreferredSize(new Dimension(300,600));
		graphPanel.setMinimumSize(new Dimension(300,600));
		graphLabel = new JLabel("This is the graph");
		view.gradeNorth.add(graphLabel);
		view.gradeNorth.add(graphPanel);
		
	}
}
