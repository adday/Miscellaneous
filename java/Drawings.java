import javafx.application.Application;

import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;

import java.util.Calendar; 
import java.util.GregorianCalendar;

import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Arc;
import javafx.scene.shape.ArcType;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.text.Text;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;

public class Drawings extends Application {
	  
	  public void start(Stage primaryStage) {
	    
	    HBox pane = new HBox();
	    pane.getChildren().add(ClockPane.makeClock());
	    pane.getChildren().add(new HangingManPane());
	    pane.getChildren().add(new FanPane());
	    
	    // Create a scene and place it in the stage
	    Scene scene = new Scene(pane,500,200);
	    primaryStage.setTitle("Three Figures"); // Set the stage title
	    primaryStage.setScene(scene); // Place the scene in the stage
	    primaryStage.show(); // Display the stage
	  }

	  public static void main(String[] args) {
	    launch(args);
	  }
	}

class FanPane extends Pane{
	public FanPane(){
		paintFanPane();
	}
	
	public void paintFanPane(){
		double centerX = getWidth() / 2;
	    double centerY = getHeight() / 2;
	    
	    Circle circle = new Circle();
	    circle.setCenterX(centerX + 25);
	    circle.setCenterY(centerY + 50);
	    circle.setRadius(30);
	    circle.setFill(null);
	    circle.setStroke(Color.BLACK);
	    
	    Arc arc1 = new Arc(centerX + 25, centerY + 50, 25, 25, 30, 35);
	    arc1.setFill(Color.BLACK);
	    arc1.setType(ArcType.ROUND);
	    Arc arc2 = new Arc(centerX + 25, centerY + 50, 25, 25, 30 + 90, 35);
	    arc2.setFill(Color.BLACK);
	    arc2.setType(ArcType.ROUND);
	    Arc arc3 = new Arc(centerX + 25, centerY + 50, 25, 25, 30 + 180, 35);
	    arc3.setFill(Color.BLACK);
	    arc3.setType(ArcType.ROUND);
	    Arc arc4 = new Arc(centerX + 25, centerY + 50, 25, 25, 30 + 270, 35);
	    arc4.setFill(Color.BLACK);
	    arc4.setType(ArcType.ROUND);
	    
	    Circle circle2 = new Circle();
	    circle2.setCenterX(centerX + 100);
	    circle2.setCenterY(centerY + 50);
	    circle2.setRadius(30);
	    circle2.setFill(null);
	    circle2.setStroke(Color.BLACK);
	    
	    Arc arc1a = new Arc(centerX + 100, centerY + 50, 25, 25, 30, 35);
	    arc1a.setFill(Color.BLACK);
	    arc1a.setType(ArcType.ROUND);
	    Arc arc2a = new Arc(centerX + 100, centerY + 50, 25, 25, 30 + 90, 35);
	    arc2a.setFill(Color.BLACK);
	    arc2a.setType(ArcType.ROUND);
	    Arc arc3a = new Arc(centerX + 100, centerY + 50, 25, 25, 30 + 180, 35);
	    arc3a.setFill(Color.BLACK);
	    arc3a.setType(ArcType.ROUND);
	    Arc arc4a = new Arc(centerX + 100, centerY + 50, 25, 25, 30 + 270, 35);
	    arc4a.setFill(Color.BLACK);
	    arc4a.setType(ArcType.ROUND);
	    
	    Circle circle3 = new Circle();
	    circle3.setCenterX(centerX + 25);
	    circle3.setCenterY(centerY + 125);
	    circle3.setRadius(30);
	    circle3.setFill(null);
	    circle3.setStroke(Color.BLACK);
	    
	    Arc arc1b = new Arc(centerX + 25, centerY + 125, 25, 25, 30, 35);
	    arc1b.setFill(Color.BLACK);
	    arc1b.setType(ArcType.ROUND);
	    Arc arc2b = new Arc(centerX + 25, centerY + 125, 25, 25, 30 + 90, 35);
	    arc2b.setFill(Color.BLACK);
	    arc2b.setType(ArcType.ROUND);
	    Arc arc3b = new Arc(centerX + 25, centerY + 125, 25, 25, 30 + 180, 35);
	    arc3b.setFill(Color.BLACK);
	    arc3b.setType(ArcType.ROUND);
	    Arc arc4b = new Arc(centerX + 25, centerY + 125, 25, 25, 30 + 270, 35);
	    arc4b.setFill(Color.BLACK);
	    arc4b.setType(ArcType.ROUND);
	    
	    Circle circle4 = new Circle();
	    circle4.setCenterX(centerX + 100);
	    circle4.setCenterY(centerY + 125);
	    circle4.setRadius(30);
	    circle4.setFill(null);
	    circle4.setStroke(Color.BLACK);
	    
	    Arc arc1c = new Arc(centerX + 100, centerY + 125, 25, 25, 30, 35);
	    arc1c.setFill(Color.BLACK);
	    arc1c.setType(ArcType.ROUND);
	    Arc arc2c = new Arc(centerX + 100, centerY + 125, 25, 25, 30 + 90, 35);
	    arc2c.setFill(Color.BLACK);
	    arc2c.setType(ArcType.ROUND);
	    Arc arc3c = new Arc(centerX + 100, centerY + 125, 25, 25, 30 + 180, 35);
	    arc3c.setFill(Color.BLACK);
	    arc3c.setType(ArcType.ROUND);
	    Arc arc4c = new Arc(centerX + 100, centerY + 125, 25, 25, 30 + 270, 35);
	    arc4c.setFill(Color.BLACK);
	    arc4c.setType(ArcType.ROUND);
	    
	    getChildren().addAll(circle, arc1, arc2, arc3, arc4, circle2, arc1a, arc2a, arc3a, arc4a, circle3, arc1b, arc2b, arc3b, arc4b, circle4, arc1c, arc2c, arc3c, arc4c);    
	    
	}
}

class HangingManPane extends Pane{
	
	public HangingManPane(){
		paintHangingMan();
	}
	
	public void paintHangingMan(){
		double centerX = getWidth() / 2;
	    double centerY = getHeight() / 2;
	    
	    Circle circle = new Circle();
	    circle.setCenterX(centerX + 120);
	    circle.setCenterY(centerY + 50);
	    circle.setRadius(20);
	    circle.setStroke(Color.BLACK);
	    circle.setFill(null);
	     
	    Line line1 = new Line(centerX + 120, centerY + 30, centerX + 120, centerY + 10);
	    Line line2 = new Line(centerX + 120, centerY + 10, centerX + 30, centerY + 10);
	    Line line3 = new Line(centerX + 30, centerY + 10, centerX + 30, centerY + 180);
	    Line line4 = new Line(centerX + 120, centerY + 70, centerX + 120, centerY + 120);
	    Line line5 = new Line(centerX + 110, centerY + 67, centerX + 70, centerY + 110);
	    Line line6 = new Line(centerX + 130, centerY + 67, centerX + 170, centerY + 110);
	    Line line7 = new Line(centerX + 120, centerY + 120, centerX + 90, centerY + 150);
	    Line line8 = new Line(centerX + 120, centerY + 120, centerX + 150, centerY + 150);
	    Arc arc = new Arc(centerX + 30, centerY + 200, 50, 20, 0, 180);
	    arc.setType(ArcType.OPEN);
	    arc.setFill(null);
	    arc.setStroke(Color.BLACK);
	
	    getChildren().clear();
	    getChildren().addAll(circle, line1, line2, line3, line4, line5, line6, line7, line8, arc);
	}
}

class ClockPane extends Pane {
	  private int hour;
	  private int minute;
	  private int second;
	  
	  /** Construct a default clock with the current time*/
	  public ClockPane() {
	    setCurrentTime();
	  }

	 public static Pane makeClock(){
		 // Create a clock and a label
		    ClockPane clock = new ClockPane();
		    String timeString = clock.getHour() + ":" + clock.getMinute() 
		      + ":" + clock.getSecond();
		    Label lblCurrentTime = new Label(timeString);
		    
		   
		    // Place clock and label in border pane
		    BorderPane cpane = new BorderPane();
		    cpane.setCenter(clock);
		    cpane.setBottom(lblCurrentTime);
		    BorderPane.setAlignment(lblCurrentTime, Pos.TOP_CENTER);
		    cpane.setMinHeight(150);
		    cpane.setMinWidth(150);
		    return cpane;
	 }
	 
	  /* Set the current time for the clock */
	  public void setCurrentTime() {
	    // Construct a calendar for the current date and time
	    Calendar calendar = new GregorianCalendar();

	    // Set current hour, minute and second
	    this.hour = calendar.get(Calendar.HOUR_OF_DAY);
	    this.minute = calendar.get(Calendar.MINUTE);
	    this.second = calendar.get(Calendar.SECOND);
	    
	    paintClock(); // Repaint the clock
	  }
	  
	  /** Paint the clock */
	  private void paintClock() {
	    // Initialize clock parameters
	    double clockRadius = 
	      Math.min(getWidth(), getHeight()) * 0.8 * 0.5;
	    double centerX = getWidth() / 2;
	    double centerY = getHeight() / 2;

	    // Draw circle
	    Circle circle = new Circle(centerX, centerY, clockRadius);
	    circle.setFill(Color.WHITE);
	    circle.setStroke(Color.BLACK);
	    Text t1 = new Text(centerX - 5, centerY - clockRadius + 12, "12");
	    Text t2 = new Text(centerX - clockRadius + 3, centerY + 5, "9");
	    Text t3 = new Text(centerX + clockRadius - 10, centerY + 3, "3");
	    Text t4 = new Text(centerX - 3, centerY + clockRadius - 3, "6");
	    Text t5 = new Text(centerX, centerY + 5, "Alex");
	    
	    // Draw second hand
	    double sLength = clockRadius * 0.8;
	    double secondX = centerX + sLength * 
	      Math.sin(second * (2 * Math.PI / 60));
	    double secondY = centerY - sLength * 
	      Math.cos(second * (2 * Math.PI / 60));
	    Line sLine = new Line(centerX, centerY, secondX, secondY);
	    sLine.setStroke(Color.RED);

	    // Draw minute hand
	    double mLength = clockRadius * 0.65;
	    double xMinute = centerX + mLength * 
	      Math.sin(minute * (2 * Math.PI / 60));
	    double minuteY = centerY - mLength * 
	      Math.cos(minute * (2 * Math.PI / 60));
	    Line mLine = new Line(centerX, centerY, xMinute, minuteY);
	    mLine.setStroke(Color.BLUE);
	    
	    // Draw hour hand
	    double hLength = clockRadius * 0.5;
	    double hourX = centerX + hLength * 
	      Math.sin((hour % 12 + minute / 60.0) * (2 * Math.PI / 12));
	    double hourY = centerY - hLength *
	      Math.cos((hour % 12 + minute / 60.0) * (2 * Math.PI / 12));
	    Line hLine = new Line(centerX, centerY, hourX, hourY);
	    hLine.setStroke(Color.GREEN);
	    
	    getChildren().clear();  
	    getChildren().addAll(circle, t1, t2, t3, t4, t5, sLine, mLine, hLine);
	  }

	  public int getHour() {
	    return hour;
	  }
	  public int getMinute() {
		    return minute;
		  }
	  public int getSecond() {
		    return second;
		  }

	  public void setHour(int hour) {
	    this.hour = hour;
	    paintClock();
	  }

	 public void setMinute(int minute) {
	    this.minute = minute;
	    paintClock();
	  }
 

	  public void setSecond(int second) {
	    this.second = second;
	    paintClock();
	  }
	  public void setWidth(double width) {
	    super.setWidth(width);
	    paintClock();
	  }
	 
	  public void setHeight(double height) {
	    super.setHeight(height);
	    paintClock();
	  }
	}
