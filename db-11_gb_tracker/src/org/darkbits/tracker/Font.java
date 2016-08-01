package org.darkbits.tracker;

import java.awt.GraphicsConfiguration;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.imageio.ImageIO;

public class Font {
	private final Map<String, BufferedImage> cache = new HashMap<String, BufferedImage>();
	private final BufferedImage data;
	private final int width;
	private final int height;
	
	public Font() throws IOException {
		this.data = ImageIO.read(getClass().getResourceAsStream("font.png"));
		this.width = 8;
		this.height = 8;
	}
	
	public int getWidth() {
		return width;
	}
	
	public int getHeight() {
		return height;
	}
	
	public BufferedImage getGlyph(char c, int fgColor, int bgColor, GraphicsConfiguration gc) {
		String key = c + "_" + fgColor + " " + bgColor;
		
		if (cache.containsKey(key)) {
			return cache.get(key);
		}
		
		BufferedImage glyph = createGlyph(c, fgColor, bgColor, gc);
		cache.put(key, glyph);
		
		return glyph; 
	}
	
	private BufferedImage createGlyph(char c, int fgColor, int bgColor, GraphicsConfiguration gc) {
		int rowLength = data.getWidth() / width; 
		int subx = (c % rowLength) * width;
		int suby = (c / rowLength) * height;
		
		BufferedImage glyph = data.getSubimage(subx, suby, width, height);		
		BufferedImage result = gc.createCompatibleImage(width, height);
		
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				boolean on = (glyph.getRGB(x, y) & 0xff) != 0;
				result.setRGB(x, y, on ? fgColor : bgColor);
			}
		}
		
		return result;
	}
}
