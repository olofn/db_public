package org.darkbits.tracker;

public class HelpView extends View {

	public HelpView(Screen screen, int x, int y) {
		super(screen, x, y, 51, 35);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void update(State state) {
		
		getScreen().putBox(getX() -1 , getY() - 1, getWidth()+2, getHeight() + 2, Screen.BLACK | Screen.BRIGHT);
		
		int titleColor = Screen.WHITE | Screen.BRIGHT;
		int y = 1;
		
		if (state.getFocusedView().getClass() == PatternView.class) {
			getScreen().put(getX() + 1, getY() + y, "PATTERN EDITOR HELP", titleColor);
			y += 2;
			printHelpRow("Space", "Toggle edit mode", y++);
			printHelpRow("Ctrl+digit", "Set pattern skip", y++);
			printHelpRow("Shift+digit", "Set octave", y++);
			printHelpRow("+/-", "Change pattern", y++);

			y += 2;
			getScreen().put(getX() + 1, getY() + y,  "PATTERN EFFECTS", titleColor);
			y += 2;
			printHelpRow("1xy 2xy", "Portamento up / down (Ch0,Ch1).", y++);
			printHelpRow(null, "x = steplength, y = time.", y++);
			
			printHelpRow("40x", "Pulse duty cycle (Ch0,Ch1).", y++);
			printHelpRow(null, "0=12.5%,1=25%,2=50%,3=75%.", y++);
			
			printHelpRow("40x", "Noise period (Ch3).", y++);
			printHelpRow(null, "0=long,1=short.", y++);

			printHelpRow("5xx 6xx", "Volume env up/down (Ch0,Ch1,Ch3).", y++);
			printHelpRow("7xx", "Note length.", y++);
			
			y += 2;
			getScreen().put(getX() + 1, getY() + y,  "AVAILABLE CHANNELS", titleColor);
			y += 2;
			printHelpRow("Ch0 & Ch1", "Pulse wave.", y++);
			printHelpRow("Ch2", "Triangle wave.", y++);
			printHelpRow("Ch3", "Noise.", y++);
		}
		
		if (state.getFocusedView().getClass() == SongView.class) {
			getScreen().put(getX() + 1, getY() + y, "SONG EDITOR HELP", titleColor);
			y += 2;
			
			printHelpRow("Ctrl+digit", "Set pattern skip", y++);
			printHelpRow("Shift+digit", "Set octave", y++);
			printHelpRow("+/-", "Change song length", y++);
		}
		
		y = 28;
		getScreen().put(getX() + 1, getY() + y, "GENERIC HELP", titleColor);
		y += 2;
		printHelpRow("Tab", "Toggle song / pattern editor", y++);
		printHelpRow("F12", "Load module", y++);
		printHelpRow("F11", "Save module", y++);
		printHelpRow("Alt+F4", "Quit", y++);
	}
	
	public void printHelpRow(String key, String def, int y) {
		if (key != null) {
			getScreen().put(getX() + 2, getY() + y, ".............." , Screen.BLACK | Screen.BRIGHT, Screen.BLACK);
			getScreen().put(getX() + 2, getY() + y, key, Screen.YELLOW | Screen.BRIGHT, Screen.BLACK);
		}
		getScreen().put(getX() + 16, getY() + y, def, Screen.WHITE, Screen.BLACK);
	}

}
