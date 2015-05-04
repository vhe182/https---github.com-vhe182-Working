package DataOutput;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
/**
 * TestFileOutput Class is used in conjunction 
 * with the Grading class. Outputs user result to a file
 * when input stream is finished
 * @author 
 *
 */
public class TestFileOutput {
	
	private static String lines = "--------------------";
	
	private ArrayList<Float> fileBuffTime;
	
	private String fileMasterString;
	
	private boolean[] fileMatches;
	
	private float fileUserResult;
	
	private PrintWriter pw;
	
	public TestFileOutput(){
		fileBuffTime = new ArrayList<Float>();
		try {
			pw = new PrintWriter("User_Output.txt", "UTF-8");
		} catch (FileNotFoundException | UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	/**
	 * Outputs to the file various statistics about
	 * the User's attempt.  
	 */
	
	public void setFileMasterString(String masterString){
		this.fileMasterString = masterString;
	}
	
	public void setFileMatches(boolean[] matches){
		System.out.println("match: " + matches);
		this.fileMatches = matches;
	}
	
	public void writeResults(float userResult, String master){
		pw.println("User Grade: " + userResult);
		pw.println("The Master String: " + master);
	}
	
	public void writeMatch(boolean match){
		pw.print(match + " ");
	}
	
	public void writeBuffTimes(Float match){
		pw.print("\n" + match +  " ");
	}
	
	public void closefile(){
		pw.close();
	}
	
	//public static void TestFileOutput(){

		//Needs data inputed in Grading.java before we can properly use
		
		//try {
			/*
			Grading grades = new Grading(null);
			PrintWriter writer = new PrintWriter("User_Output.txt", "UTF-8");
			writer.println("User Lesson Overview");
			writer.println(lines);
			writer.println("Lesson 1 Overview");
			writer.println("Master String: " + grades.getMASTER_STRING_1());
			writer.println("User String: " + grades.getUser_string_1());
			writer.println("Shadow Time: " + grades.getSpeak_time_1());
			writer.println("Correctness: " + grades.CompareString(grades.getMASTER_STRING_1(), grades.getUser_string_1()));
			writer.println(lines);
			writer.println("Lesson 2 Overview");
			writer.println("Master String: " + grades.getMASTER_STRING_2());
			writer.println("User String: " + grades.getUser_string_2());
			writer.println("Shadow Time: " + grades.getSpeak_time_2());
			writer.println("Correctness: " + grades.CompareString(grades.getMASTER_STRING_2(), grades.getUser_string_2()));
			writer.println(lines);
			writer.println("Lesson 3 Overview");
			writer.println("Master String: " + grades.getMASTER_STRING_3());
			writer.println("User String: " + grades.getUser_string_3());
			writer.println("Shadow Time: " + grades.getSpeak_time_3());
			writer.println("Correctness: " + grades.CompareString(grades.getMASTER_STRING_3(), grades.getUser_string_3()));
			writer.println(lines);
			writer.println("Information");
			writer.println("Average Shadowing Time: " + grades.AverageTime(grades.getSpeak_time_1(), 
					grades.getSpeak_time_2(), grades.getSpeak_time_3()));
			
			writer.println("Number of Correct Strings: " + grades.NumberCorrect());
			
			
			writer.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
	}
//}
