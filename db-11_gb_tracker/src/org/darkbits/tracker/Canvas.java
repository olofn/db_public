package org.darkbits.tracker;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Canvas extends JPanel {
	private final Screen screen;
	private BufferedImage buffer;
	
	public Canvas(Screen screen, int scale) {
		super();
		this.screen = screen;
		int w = Screen.WIDTH * screen.getFont().getWidth();
		int h = Screen.HEIGHT * screen.getFont().getHeight();
		setSize(w * scale + 2, h * scale + 2);
		setPreferredSize(getSize());
		setBackground(Color.BLACK);
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		g.setColor(Color.BLACK);
		g.fillRect(0, 0, getWidth(), 1);
		g.fillRect(0, 0, 1, getHeight());
		g.fillRect(0, getHeight() - 1, getWidth(), 1);
		g.fillRect(getWidth() - 1, 0, 1, getHeight());
		g.drawImage(buffer, 1, 1, getWidth() - 2, getHeight() - 2, null);
	}
	
	public void drawFrame() {
		if (buffer == null) {
			int w = Screen.WIDTH * screen.getFont().getWidth();
			int h = Screen.HEIGHT * screen.getFont().getHeight();
			buffer = getGraphicsConfiguration().createCompatibleImage(w, h);
		}
		Graphics2D g2 = (Graphics2D)buffer.getGraphics();
		screen.render(g2, getGraphicsConfiguration());
		g2.dispose();
		
		super.repaint();
	}
}
