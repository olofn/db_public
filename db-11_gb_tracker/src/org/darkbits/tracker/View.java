package org.darkbits.tracker;

public abstract class View {
	
	private final Screen screen;
	private int height;
	private int width;
	private int y;
	private int x;

	public View(Screen screen, int x, int y, int width, int height) {
		this.screen = screen;
		this.setX(x);
		this.setY(y);
		this.setWidth(width);
		this.setHeight(height);
	}

	public abstract void update(State state);
	
	public void setHeight(int height) {
		this.height = height;
	}

	public int getHeight() {
		return height;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getWidth() {
		return width;
	}

	public void setY(int y) {
		this.y = y;
	}

	public int getY() {
		return y;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getX() {
		return x;
	}

	public Screen getScreen() {
		return screen;
	}
}
