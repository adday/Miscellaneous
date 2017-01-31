
/*
 *      Rule30.java  
 *
		J. Hanna 5/15/2002
		
		from Wired Magazine 6/2002 article on Stephen Wolfram...

 *
 */

import java.awt.*;
import java.applet.*;
import java.awt.event.*;
import java.awt.image.*;

public class RuleThirty extends Applet implements ActionListener, ImageObserver{
	int[][] b;
	int w, h, rule ;
	TextField r;
	Image offScreen;

	public void actionPerformed(ActionEvent e){
		rule = Integer.parseInt(r.getText());
		reDraw();
	}

	public void init() {
		w = getWidth()+300;// wider than applet to hide edge anomalies
		h = getHeight()+300;
		b = new int[h][w];
		b[0][w/2] = 1;
		rule = 256;
		r = new TextField();
		r.setText("256");
		r.addActionListener(this);
		setLayout (new BorderLayout());
		add(r, BorderLayout.NORTH);
		offScreen=createImage(w,h);		
		reDraw();
		repaint();
	}

	private void reDraw(){
		int v, bit, r, c, k;
		Graphics go = offScreen.getGraphics();
		go.setColor(Color.white);
		go.fillRect(0,100,w,h);
		go.setColor(Color.black);	
		//go.drawLine(w/2 - 100, 0, w/2 - 100, 0); // -100 to recenter image in applet
		for(r = 1; r < h; r++)
		{
			for (c = 1; c < w - 1; c++)
			{
	// Rule parser... 
				v=0;
				for (k = -1; k <= 1; k++)
				{
					v = 2 * v + b[r-1][c + k]; 
				}
				bit = (int)Math.pow(2,v);
				if ((bit & rule) == bit)
				{
					b[r][c] = 1;
					go.drawLine(c-100,r,c-100,r);
				}
				else b[r][c] = 0;
			} // for(c
		}//for(r
		repaint();
	}//reDraw();

	public void paint(Graphics g) {
		g.drawImage(offScreen, 0,0,this );
	}//paint()

}//class
