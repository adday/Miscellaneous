/*************************************************************************************************************
 * n00627606.java																		Alexander Day
 * 
 * This program demonstrates a variety of GUI related tasks. Specifically, it places objects in a borderpane. 
 * The top pane is a bouncing rectangle with a slider to control speed. The left pane contains checkboxes to 
 * italicize or bold the font. The right pane contains radio buttons to change the color of the font. The center 
 * contains the font being altered, my name, on the left and a video with controls on the right. The bottom pane
 * contains buttons to adjust the position of the font up and down. 
 *************************************************************************************************************/

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleGroup;
import javafx.util.Duration;

public class VideoDemoWindow extends Application {

	public void start(Stage stage) {
		Scene scene = new Scene(new AndFinallyTheTop(), 700, 500);//Add horizontal box to scene and set dimensions
		stage.setTitle("Assignment 7");
		stage.getIcons().add(new Image("http://www.unf.edu/~n00627606/icon.jpg"));
		stage.setScene(scene); // Place the scene in the stage
		stage.show(); // Display the stage
	}

	public static void main(String[] args) {
		launch(args);
	}
}

class Center extends BorderPane{
	protected Text t = new Text();

	public Center(){
		Pane textpane = new Pane();
		t.setText("Alexander");
		t.setFill(Color.BLACK);
		t.setTranslateY(20);
		textpane.getChildren().add(t);
		Media video = new Media("http://www.unf.edu/~n00627606/video.mp4");
		MediaPlayer mediaPlayer = new MediaPlayer(video);
		MediaView mediaview = new MediaView(mediaPlayer);
		
		Button playButton = new Button("||");
		playButton.setStyle("-fx-background-color: linear-gradient(#f0ff35, #a9ff00), radial-gradient(center 50% -40%, radius 200%, #b8ee36 45%, #80c800 50%); -fx-background-radius: 6, 5; -fx-background-insets: 0, 1;  -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.4) , 5, 0.0 , 0 , 1 );-fx-text-fill: #395306;");
		playButton.setOnAction(e -> {
			if (playButton.getText().equals(">")) {
				mediaPlayer.play();
				playButton.setText("||");
			} else {
				mediaPlayer.pause();
				playButton.setText(">");
			}
		});
		
		Button rewindButton = new Button("<<");
		rewindButton.setStyle("-fx-background-color: linear-gradient(#f0ff35, #a9ff00), radial-gradient(center 50% -40%, radius 200%, #b8ee36 45%, #80c800 50%); -fx-background-radius: 6, 5; -fx-background-insets: 0, 1;  -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.4) , 5, 0.0 , 0 , 1 );-fx-text-fill: #395306;");
		rewindButton.setOnAction(e -> mediaPlayer.seek(Duration.ZERO));

		Slider slVolume = new Slider();
		slVolume.setPrefWidth(150);
		slVolume.setMaxWidth(Region.USE_PREF_SIZE);
		slVolume.setMinWidth(10);
		slVolume.setValue(50);
		mediaPlayer.volumeProperty().bind(slVolume.valueProperty().divide(100));

		HBox controls = new HBox(10);
		Label volLabel = new Label("Volume");
		volLabel.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		controls.getChildren().addAll(playButton, rewindButton, volLabel, slVolume);
		controls.setLayoutY(controls.getLayoutBounds().getMinY());
		VBox rightcenter = new VBox();
		mediaview.setPreserveRatio(false);
		mediaview.fitWidthProperty().bind(this.widthProperty().subtract(210));
		mediaview.fitHeightProperty().bind(rightcenter.heightProperty().subtract(40));
		mediaview.setLayoutY(0);
		rightcenter.getChildren().addAll(mediaview,controls);

		BorderPane center = new BorderPane();
		center.setMinHeight(200);
		center.setMinWidth(300);
		center.setLeft(textpane);
		center.setRight(rightcenter);
		center.setStyle("-fx-background-color: darkgrey;");
		
		mediaPlayer.play();
		setCenter(center);      
		setMinHeight(300);
	}
}

class Bottom extends Center{ 
	public Bottom(){

		Button upBt = new Button("UP");
		upBt.setStyle("-fx-background-color: linear-gradient(#f0ff35, #a9ff00), radial-gradient(center 50% -40%, radius 200%, #b8ee36 45%, #80c800 50%); -fx-background-radius: 6, 5; -fx-background-insets: 0, 1;  -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.4) , 5, 0.0 , 0 , 1 );-fx-text-fill: #395306;");
		upBt.setOnAction(e->{
			if(t.getY() > 10)
				t.setY(t.getY() - 10);
		});

		Button downBt = new Button("DOWN");
		downBt.setStyle("-fx-background-color: linear-gradient(#f0ff35, #a9ff00), radial-gradient(center 50% -40%, radius 200%, #b8ee36 45%, #80c800 50%); -fx-background-radius: 6, 5; -fx-background-insets: 0, 1;  -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.4) , 5, 0.0 , 0 , 1 );-fx-text-fill: #395306;");
		downBt.setOnAction(e->{
			if(t.getY() < 500)
				t.setY(t.getY() + 10);
		});

		HBox bottom = new HBox(10);
		bottom.setAlignment(Pos.BOTTOM_LEFT);
		Label controlLbl = new Label("Text Position Controls:");
		controlLbl.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		bottom.getChildren().addAll(controlLbl, upBt,downBt); 
		bottom.setStyle("-fx-background-color: darkgrey;");
		setBottom(bottom);
	}
}

class Right extends Bottom{
	public Right(){

		VBox rbPane = new VBox(20);
		rbPane.setAlignment(Pos.CENTER);
		rbPane.setPadding(new Insets(0,5 , 0, 5)); 
		RadioButton rbPurple = new RadioButton("Purple");
		rbPurple.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		RadioButton rbYellow = new RadioButton("Yellow");
		rbYellow.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		RadioButton rbTeal   = new RadioButton("Teal" + "  ");
		rbTeal.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		rbPane.getChildren().addAll(rbPurple, rbYellow, rbTeal);

		ToggleGroup group = new ToggleGroup();
		rbPurple.setToggleGroup(group);
		rbYellow.setToggleGroup(group);
		rbTeal.setToggleGroup(group);

		rbPurple.setOnAction(e -> {
			if (rbPurple.isSelected()) {
				t.setFill(Color.PURPLE);
			}
		});

		rbYellow.setOnAction(e -> {
			if (rbYellow.isSelected()) {
				t.setFill(Color.YELLOW);
			}
		});

		rbTeal.setOnAction(e -> {
			if (rbTeal.isSelected()) {
				t.setFill(Color.TEAL);
			}
		});

		rbPane.setStyle("-fx-background-color: darkgrey;");
		setRight(rbPane);
	}
}

class Left extends Right{
	public Left(){
		Font fontBoldItalic = Font.font("Calibri", 
				FontWeight.BOLD, FontPosture.ITALIC, 20);
		Font fontBold = Font.font("Calibri", 
				FontWeight.BOLD, FontPosture.REGULAR, 20);
		Font fontItalic = Font.font("Calibri", 
				FontWeight.NORMAL, FontPosture.ITALIC, 20);
		Font fontNormal = Font.font("Calibri", 
				FontWeight.NORMAL, FontPosture.REGULAR, 20);

		t.setFont(fontNormal);

		VBox leftpane = new VBox(20);
		leftpane.setAlignment(Pos.CENTER);
		leftpane.setPadding(new Insets(0, 0, 0, 0)); 
		CheckBox chkBold = new CheckBox("Bold");
		chkBold.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		CheckBox chkItalic = new CheckBox("Italic");
		chkItalic.setStyle("-fx-font-size: 12px; -fx-font-weight: bold; -fx-text-fill: #333333; -fx-effect: dropshadow( gaussian , rgba(255,255,255,0.5) , 0,0,0,1 );");
		leftpane.getChildren().addAll(chkBold, chkItalic);

		chkBold.setOnAction(e -> { 
			if (chkBold.isSelected() && chkItalic.isSelected()) {
				t.setFont(fontBoldItalic); // Both check boxes checked
			}
			else if (chkBold.isSelected()) {
				t.setFont(fontBold); // The Bold check box checked
			}
			else if (chkItalic.isSelected()) {
				t.setFont(fontItalic); // The Italic check box checked
			}      
			else {
				t.setFont(fontNormal); // Both check boxes unchecked
			}});
		
		chkItalic.setOnAction(e -> { 
			if (chkBold.isSelected() && chkItalic.isSelected()) {
				t.setFont(fontBoldItalic); // Both check boxes checked
			}
			else if (chkBold.isSelected()) {
				t.setFont(fontBold); // The Bold check box checked
			}
			else if (chkItalic.isSelected()) {
				t.setFont(fontItalic); // The Italic check box checked
			}      
			else {
				t.setFont(fontNormal); // Both check boxes unchecked
			}});
		
		leftpane.setStyle("-fx-background-color: darkgrey;");
		setLeft(leftpane);
	}
}

class AndFinallyTheTop extends Left{
	Pane bouncepane = new Pane();
	private double deltaX = 1;
	private double deltaY = 1;
	private Timeline loop;
	private int x=40;
	private int y=25;
	private Rectangle r = new Rectangle(x,y,Color.RED);
	
	public AndFinallyTheTop(){
		bouncepane.setMinHeight(100); 
		bouncepane.setStyle("-fx-background-color: darkgrey;");
		
		Slider slSpeed = new Slider();
		slSpeed.setMax(5);
		slSpeed.setLayoutX(0);
		slSpeed.setLayoutY(0);
		slSpeed.setValue(1);
		
		bouncepane.getChildren().addAll(r,slSpeed);
		setTop(bouncepane);
		
		loop = new Timeline(new KeyFrame(Duration.millis(10), e-> moveRect()));
		loop.rateProperty().bind(slSpeed.valueProperty());
		loop.setCycleCount(Timeline.INDEFINITE);
		loop.play();
	}

	private void moveRect() {
		r.setX(r.getX() + deltaX);
		r.setY(r.getY() + deltaY);

		final Bounds bounds = bouncepane.getBoundsInLocal();
		final boolean atRightBorder = r.getX() >= (bounds.getMaxX() - r.getWidth());
		final boolean atLeftBorder = r.getX() <= 0;
		final boolean atBottomBorder = r.getY() >= (bounds.getMaxY() - r.getWidth());
		final boolean atTopBorder = r.getY() <= 0;

		if (atRightBorder || atLeftBorder) {
			deltaX *= -1;
		}
		if (atBottomBorder || atTopBorder) {
			deltaY *= -1;
		}
	}
}
