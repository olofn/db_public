package org.darkbits.tracker.util;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import javax.imageio.ImageIO;

public class ImageConverter {

	private static final int[] palette = new int[] { 0xff000000, 0xff0000a8,
		0xff00a800, 0xff00a8a8, 0xffa80000, 0xffa800a8, 0xffa85400,
		0xffa8a8a8, 0xff545454, 0xff5454fc, 0xff54fc54, 0xff54fcfc,
		0xfffc5454, 0xfffc54fc, 0xfffcfc54, 0xfffcfcfc };
	
	private static enum ColorBlendMode
	{
		BLEND25,
		BLEND50
	}
	
	private static class Color {
		
		public Color(int c) {
			r = (c >> 16) & 0x000000ff;
			g = (c >> 8) & 0x000000ff;
			b = c & 0x000000ff;
		}
		
		public Color(int c1, int c2, ColorBlendMode mode) {
			int r1 = (c1 >> 16) & 0x000000ff;
			int r2 = (c2 >> 16) & 0x000000ff;
			int g1 = (c1 >> 8) & 0x000000ff;
			int g2 = (c2 >> 8) & 0x000000ff;
			int b1 = (c1) & 0x000000ff;
			int b2 = (c2) & 0x000000ff;
			
			if (mode == ColorBlendMode.BLEND25) {
				r = Math.min((int)(r1 * 0.25f + r2 * 0.75f), 255);
				g = Math.min((int)(g1 * 0.25f + g2 * 0.75f), 255);
				b = Math.min((int)(b1 * 0.25f + b2 * 0.75f), 255);
			}
			else if (mode == ColorBlendMode.BLEND50) {
				r = Math.min((int)(r1 * 0.5f + r2 * 0.5f), 255);
				g = Math.min((int)(g1 * 0.5f + g2 * 0.5f), 255);
				b = Math.min((int)(b1 * 0.5f + b2 * 0.5f), 255);
			}
		}
		
		public int r;
		public int g;
		public int b;
		
		public int compare(Color color) {
			return (int)(Math.abs(color.r - r) + Math.abs(color.g - g) + Math.abs(color.b - b));
		}
		
		public String toString() {
			return "[r="+r+";g="+g+";b="+b+";]";
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + b;
			result = prime * result + g;
			result = prime * result + r;
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Color other = (Color) obj;
			if (b != other.b)
				return false;
			if (g != other.g)
				return false;
			if (r != other.r)
				return false;
			return true;
		}
	}
	
	private static class Tile
	{
		public Tile(int image, int fgColor, int bgColor) {
			this.image = image;
			this.fgColor = fgColor;
			this.bgColor = bgColor;
		}
		public int image;
		public int fgColor;
		public int bgColor;
	}
	
	private Map<Color, Tile> colorToTile = new HashMap<Color, Tile>();
	

	public void generateColors() {
		for (int i = 0; i < 16; i++) {
			for (int j = i; j < 16; j++) {
				if (i == 0 && j > 8) {
					continue;
				}
				
				if (i == 0 && j == 7) {
					continue;
				}
				
				if (i == 8 && j == 15) {
					continue;
				}
				
				int rc1 = palette[i];
				int rc2 = palette[j];
	
				Color c1 = new Color(rc1);
				Tile t1 = new Tile(219, i, j);
				colorToTile.put(c1, t1);
				
				Color c2 = new Color(rc1, rc2, ColorBlendMode.BLEND25);
				Tile t2 = new Tile(178, j, i);
				colorToTile.put(c2, t2);
				
				Color c3 = new Color(rc1, rc2, ColorBlendMode.BLEND50);
				Tile t3 = new Tile(177, j, i);
				colorToTile.put(c3, t3);
				
				Color c5 = new Color(rc2, rc1, ColorBlendMode.BLEND25);
				Tile t5 = new Tile(178, i, j);
				colorToTile.put(c5, t5);
				
				Color c4 = new Color(rc2);
				Tile t4 = new Tile(219, j, i);
				colorToTile.put(c4, t4);
			}
		}
	}
	
	public void convert(String filename, String prefix) {
		File file = new File(filename);
		BufferedImage image;
		try {
			image = ImageIO.read(file);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		 
		StringBuilder result = new StringBuilder();
		result.append("static final int ");
		result.append(prefix);
		result.append("_WIDTH = ");
		result.append(image.getWidth());
		result.append(";\n");
		result.append("static final int ");
		result.append(prefix);
		result.append("_HEIGHT = ");
		result.append(image.getHeight());
		result.append(";\n");
		result.append("static final int[] ");
		result.append(prefix);
		result.append("_DATA = {");
		int i = 0;
		for (int y = 0; y < image.getHeight(); y++) {
			for (int x = 0; x < image.getWidth(); x++) {
				Color c = new Color(image.getRGB(x, y));
				Tile t = null;
				int score = Integer.MAX_VALUE;
				for (Entry<Color, Tile> entry: colorToTile.entrySet()) {
					int s = entry.getKey().compare(c);
					if (s < score) {
						t = entry.getValue();
						score = s;
					}
				}
				
				result.append(t.image);
				result.append(",");
				result.append(t.fgColor);
				result.append(",");
				result.append(t.bgColor);
				if (!(y + 1 == image.getHeight() && x + 1 == image.getWidth())) {
					result.append(",");
				}
				i++;
				if (i % 16 == 0) {
					//result.append("\n");
				}
			}
		}
		result.append("};\npublic static void put_");
		result.append(prefix);
		result.append("(Screen screen, int x, int y) {for (int sy = 0; sy < Generated.");
		result.append(prefix);
		result.append("_HEIGHT; sy++) { for (int sx = 0; sx < Generated.");
		result.append(prefix);
		result.append("_WIDTH; sx++) {int index = (sx + sy * Generated.");
		result.append(prefix);
		result.append("_WIDTH) * 3;char c = (char)Generated.");
		result.append(prefix);
		result.append("_DATA[index];int fgColor = Generated.");
		result.append(prefix);
		result.append("_DATA[index + 1];int bgColor = Generated.");
		result.append(prefix);
		result.append("_DATA[index + 2];screen.put(x + sx, y + sy, c, fgColor, bgColor);}}}");
		System.out.println(result);
	}
	
	public static void main(String[] args) {
		ImageConverter ic = new ImageConverter();
		ic.generateColors();
		ic.convert("C:/tmp/asciidarkbits3.bmp", "DARKBITS_LOGO_3");
	}
}
