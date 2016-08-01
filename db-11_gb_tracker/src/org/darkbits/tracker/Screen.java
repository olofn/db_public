package org.darkbits.tracker;

import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.image.BufferedImage;

public class Screen {
	private static final int[] palette = new int[] { 0xff000000, 0xff0000a8,
			0xff00a800, 0xff00a8a8, 0xffa80000, 0xffa800a8, 0xffa85400,
			0xffa8a8a8, 0xff545454, 0xff5454fc, 0xff54fc54, 0xff54fcfc,
			0xfffc5454, 0xfffc54fc, 0xfffcfc54, 0xfffcfcfc };

	public static final int BLACK = 0;
	public static final int BLUE = 1;
	public static final int GREEN = 2;
	public static final int CYAN = 3;
	public static final int RED = 4;
	public static final int MAGENTA = 5;
	public static final int YELLOW = 6;
	public static final int WHITE = 7;
	public static final int BRIGHT = 8;
	
	public static final int WIDTH = 80;
	public static final int HEIGHT = 60;
	
	public static final char CHAR_FILL_0 = 0;
	public static final char CHAR_FILL_25 = 176;
	public static final char CHAR_FILL_50 = 177;
	public static final char CHAR_FILL_75 = 178;
	public static final char CHAR_FILL_100 = 219;
	
	private static class Tile {
		public char character;
		public int bgColor;
		public int fgColor;
		
		public Tile(char character, int fgColor, int bgColor) {
			this.character = character;
			this.bgColor = bgColor;
			this.fgColor = fgColor;
		}
	}
	
	private final Tile[] data = new Tile[WIDTH * HEIGHT];
	private final Font font;
	
	public Screen(Font font) {
		for (int i = 0; i < data.length; i++) {
			data[i] = new Tile(' ', 0, 0);
		}
		this.font = font;
	}
	
	public void clear() {
		for (int i = 0; i < data.length; i++) {
			data[i].character = ' ';
			data[i].bgColor = 0;
			data[i].fgColor = 0;
		}
	}

	public void put(int x, int y, char c, int fgColor) {
		put(x, y, c, fgColor, -1);
	}
	
	public void put(int x, int y, char c, int fgColor, int bgColor) {
		if (x < 0 || x >= WIDTH) {
			return;
		}
		
		if (x < 0 || y >= HEIGHT) {
			return;
		}
		
		data[x + y * WIDTH].character = c;
		data[x + y * WIDTH].fgColor = fgColor;
		if (bgColor != -1)
		{
			data[x + y * WIDTH].bgColor = bgColor;
		}
	}
	
	public void put(int x, int y, String s, int fgColor) {
		put(x, y, s, fgColor, -1);
	}
	
	public void put(int x, int y, String s, int fgColor, int bgColor) {
		for (int i = 0; i < s.length(); i++) {
			put(x + i, y, s.charAt(i), fgColor, bgColor);
		}
	}
	
	public void putBackgroundColor(int x, int y, int width, int height, int bgColor) {
		if (bgColor == -1) {
			return;
		}
			
		for (int yy = y; yy < y + height; yy++) {
			for (int xx = x; xx < x + width; xx++) {
				data[xx + yy * WIDTH].bgColor = bgColor;
			}
		}
	}
	
	public void putBox(int x, int y, int width, int height, int fgColor, int bgColor) {
	
		// Clear box
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				put(x + i, y + j, ' ', fgColor, bgColor);
			}
		}
		
		// Draw frame
		put(x, y, '\u00da', fgColor);
		for (int i = x + 1; i < x + width - 1; i++) {
			put(i, y, '\u00c4', fgColor);
		}
		put(x + width - 1, y, '\u00bf', fgColor);
		for (int i = y + 1; i < y + height - 1; i++) {
			put(x + width - 1, i, '\u00b3', fgColor);
		}
		put(x + width - 1, y + height - 1, '\u00d9', fgColor);
		for (int i = x + 1; i < x + width - 1; i++) {
			put(i, y + height - 1, '\u00c4', fgColor);
		}
		put(x, y + height - 1, '\u00c0', fgColor);
		for (int i = y + 1; i < y + height - 1; i++) {
			put(x, i, '\u00b3', fgColor);
		}	 
	}
	
	public void putBox(int x, int y, int width, int height, int fgColor) {
		putBox(x, y, width, height, fgColor, -1);
	}
	
	public void putThickBox(int x, int y, int width, int height, int fgColor) {
		putThickBox(x, y, width, height, fgColor, -1);
	}
	
	public void putThickBox(int x, int y, int width, int height, int fgColor, int bgColor) {
		
		// Clear box
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				put(x + i, y + j, ' ', fgColor, bgColor);
			}
		}
		
		// Draw frame
		put(x, y, '\u00c9', fgColor);
		for (int i = x + 1; i < x + width - 1; i++) {
			put(i, y, '\u00cd', fgColor);
		}
		put(x + width - 1, y, '\u00bb', fgColor);
		for (int i = y + 1; i < y + height - 1; i++) {
			put(x + width - 1, i, '\u00ba', fgColor);
		}
		put(x + width - 1, y + height - 1, '\u00bc', fgColor);
		for (int i = x + 1; i < x + width - 1; i++) {
			put(i, y + height - 1, '\u00cd', fgColor);
		}
		put(x, y + height - 1, '\u00c8', fgColor);
		for (int i = y + 1; i < y + height - 1; i++) {
			put(x, i, '\u00ba', fgColor);
		}	 
	}

	public Font getFont() {
		return font;
	}
	
//	public void putDarkbitsLogo(int x, int y) {
//		for (int sy = 0; sy < Data.Generated; sy++) {
//			for (int sx = 0; sx < Data.Generated; sx++) {
//			
//				int index = (sx + sy * Data.Generated) * 3;
//			
//				char c = (char)Data.Generated[index];
//				int fgColor = Data.Generated[index + 1];
//				int bgColor = Data.Generated[index + 2];
//				
//				put(x + sx, y + sy, c, fgColor, bgColor);
//			}
//		}
//	}
	
	public void render(Graphics2D g, GraphicsConfiguration gc) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				int xp = x * font.getWidth();
				int yp = y * font.getHeight();
				
				Tile tile = data[x + y * WIDTH];
				BufferedImage glyph = font.getGlyph(tile.character, palette[tile.fgColor], palette[tile.bgColor], gc);
				
				g.drawImage(glyph, xp, yp, null);
			}
		}
	}
}
