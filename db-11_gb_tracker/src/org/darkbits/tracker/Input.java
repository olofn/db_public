package org.darkbits.tracker;

import java.awt.AWTEvent;
import java.awt.Point;
import java.awt.event.FocusEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.util.HashSet;
import java.util.Queue;
import java.util.Set;

public class Input {
	private Point mousePosition = new Point();
	private boolean mouseInsideWindow = false;
	private final Set<Integer> keyDown = new HashSet<Integer>();
	private final Set<Integer> keyPressed = new HashSet<Integer>();
	private final Set<Integer> keyReleased = new HashSet<Integer>();
	private int mouseButtonDown = 0;
	private int mouseButtonPressed = 0;
	private int mouseButtonReleased = 0;
	private int mouseWheelDelta = 0;
	private int mouseWheelPos = 0;
	private String typedText = "";
	private boolean focused = false;

	boolean wasKeyPressed(int key) {
		return keyPressed.contains(key);
	}

	boolean wasKeyReleased(int key) {
		return keyReleased.contains(key);
	}

	boolean isKeyDown(int key) {
		return keyDown.contains(key);
	}

	boolean wasMouseButtonPressed(int button) {
		return (mouseButtonPressed & mouseButtonToMask(button)) != 0;
	}

	boolean wasMouseButtonReleased(int button) {
		return (mouseButtonReleased & mouseButtonToMask(button)) != 0;
	}

	boolean isMouseButtonDown(int button) {
		return (mouseButtonDown & mouseButtonToMask(button)) != 0;
	}

	public Point getMousePosition() {
		return mousePosition;
	}

	public int getMouseWheelDelta() {
		return mouseWheelDelta;
	}

	public int getMouseWheelPos() {
		return mouseWheelPos;
	}

	public boolean isMouseInsideWindow() {
		return mouseInsideWindow;
	}

	public boolean isFocused() {
		return focused;
	}

	public String getTypedText() {
		return typedText;
	}

	protected void update(Queue<AWTEvent> inputQueue, Point mousePosition) {
		this.mousePosition = mousePosition;

		mouseWheelDelta = 0;
		mouseButtonPressed = 0;
		mouseButtonReleased = 0;
		keyPressed.clear();
		keyReleased.clear();

		StringBuffer typedChars = new StringBuffer();

		while (true) {
			AWTEvent e = inputQueue.poll();

			if (e == null) {
				break;
			}

			if (e.getID() >= KeyEvent.KEY_FIRST
					&& e.getID() <= KeyEvent.KEY_LAST) {
				KeyEvent keyEvent = (KeyEvent) e;

				switch (keyEvent.getID()) {
				case KeyEvent.KEY_PRESSED:
					keyPressed.add(keyEvent.getKeyCode());
					keyDown.add(keyEvent.getKeyCode());
					break;
				case KeyEvent.KEY_RELEASED:
					keyReleased.add(keyEvent.getKeyCode());
					keyDown.remove(keyEvent.getKeyCode());
					break;
				case KeyEvent.KEY_TYPED:
					if (keyEvent.getKeyChar() != KeyEvent.CHAR_UNDEFINED) {
						typedChars.append(keyEvent.getKeyChar());
					}
					break;
				default:
					throw new RuntimeException("Error");
				}
			} else if (e.getID() >= MouseEvent.MOUSE_FIRST
					&& e.getID() <= MouseEvent.MOUSE_LAST) {
				MouseEvent mouseEvent = (MouseEvent) e;
				int buttonMask = mouseButtonToMask(mouseEvent.getButton());

				switch (mouseEvent.getID()) {
				case MouseEvent.MOUSE_ENTERED:
					mouseInsideWindow = true;
					break;
				case MouseEvent.MOUSE_EXITED:
					mouseInsideWindow = false;
					break;
				case MouseEvent.MOUSE_PRESSED:
					mouseButtonPressed |= buttonMask;
					mouseButtonDown |= buttonMask;
					break;
				case MouseEvent.MOUSE_RELEASED:
					mouseButtonDown &= ~buttonMask;
					mouseButtonReleased |= buttonMask;
					break;
				case MouseEvent.MOUSE_WHEEL:
					mouseWheelDelta += ((MouseWheelEvent) mouseEvent)
							.getWheelRotation();
					mouseWheelPos += ((MouseWheelEvent) mouseEvent)
							.getWheelRotation();
					break;
				case MouseEvent.MOUSE_CLICKED:
					// Do nothing
					break;
				default:
					throw new RuntimeException("Error " + e);
				}
			} else if (e.getID() == FocusEvent.FOCUS_GAINED) {
				focused = true;
			} else if (e.getID() == FocusEvent.FOCUS_LOST) {
				focused = false;
			} else {
				throw new RuntimeException("Error");
			}
		}

		typedText = typedChars.toString();
	}

	private int mouseButtonToMask(int button) {
		return 1 << button;
	}

}
