package org.darkbits.tracker;

import java.awt.event.KeyEvent;

public class SongView extends View {
	
	private static String HEX_VALUES = "0123456789abcdef";
	
	private final PatternView patternView;
	private int editColumn;
	private int editRow;
	private int editDigit;
	
	public SongView(Screen screen, PatternView patternView, int x, int y, int height) {
		super(screen, x, y, 0, height);
		this.patternView = patternView;
	}
	
	@Override
	public void update(State state) {
		
		Song song = state.getSong();
		setWidth(song.getNumberOfChannels() * 3 - 1);
		
		if (state.getInput().wasKeyPressed(KeyEvent.VK_ENTER)) {
			if (song.isPlaying()) {
				song.stop();
			} else {
				song.setSongPosition(editRow);
				song.start();
			}
		}
		
		if (state.getFocusedView() == this) {
			boolean changePatternView = false;
			getScreen().putBox(getX() - 1, getY() - 1, getWidth() + 2, getHeight() + 2, Screen.CYAN);
			
			if (state.getInput().wasKeyPressed(KeyEvent.VK_DOWN)) {
				changePatternView = true;
				editRow = (editRow + 1) % song.getLength();
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_UP)) {
				changePatternView = true;
				editRow = (editRow + song.getLength() - 1) % song.getLength();
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_PAGE_DOWN)) {
				changePatternView = true;
				editRow = Math.min(editRow + 8, song.getLength() - 1);
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_PAGE_UP)) {
				changePatternView = true;
				editRow = Math.max(editRow - 8, 0);
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_LEFT)) {
				changePatternView = true;
				editDigit--;
				if (editDigit < 0) {
					editDigit = 1;
					editColumn--;
					if (editColumn < 0) {
						editColumn = song.getNumberOfChannels() - 1;
					}
				}
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_RIGHT)) {
				changePatternView = true;
				editDigit++;
				if (editDigit > 1) {
					editDigit = 0;
					editColumn++;
					if (editColumn >= song.getNumberOfChannels()) {
						editColumn = 0;
					}
				}
			}
			
			if (changePatternView && song.getPatternAt(editRow, editColumn) >= 0) {
				patternView.setEditPattern(state, song.getPatternAt(editRow, editColumn));
			}	
			
			for (char c : state.getInput().getTypedText().toLowerCase().toCharArray()) {
				if (c == '+') {
					song.setLength(song.getLength() + 1);
					continue;
				}
				
				if (c == '-') {
					song.setLength(song.getLength() - 1);
					if (editRow >= song.getLength()) {
						editRow = song.getLength() - 1;
					}
					continue;
				}
				
				if (c == 127) {
					song.putPatternAt(editRow, editColumn, -1);
					editRow = (editRow + 1) % song.getLength();
					continue;
				}
				
				if (HEX_VALUES.indexOf(c) < 0) {
					continue;
				}
				int value = song.getPatternAt(editRow, editColumn);
				if (value == -1) {
					value = 0;
				}
				char[] current = HexUtils.toHex(value, 2).toCharArray();
				current[editDigit] = c;
				int pattern = Integer.parseInt(new String(current), 16);
				song.putPatternAt(editRow, editColumn, pattern);
				patternView.setEditPattern(state, pattern);
				editRow = (editRow + 1) % song.getLength();
			}
			
			patternView.setAuditionChannel(editColumn);
		}
		
		int titleFgColor = Screen.WHITE | Screen.BRIGHT;
		int titleBgColor = Screen.BLACK | Screen.BRIGHT;
		if (state.getFocusedView() == this) {
			titleBgColor = Screen.CYAN;
			titleFgColor = Screen.WHITE | Screen.BRIGHT;
		}
		getScreen().put(getX(), getY(), "  S O N G  ", titleFgColor, titleBgColor);
		getScreen().put(getX(), getY() + 1, " Channel " + HexUtils.toHex(editColumn, 1) + " ", Screen.WHITE, Screen.BLACK | Screen.BRIGHT);
		
		//for (int i = 0; i < song.getNumberOfChannels(); i++) {
		//	getScreen().put(getX() + i*3, getY(), "c"+i, titleFgColor, titleBgColor);
		//}
		
		for (int y = 2; y < getHeight(); y++) {
			int r = y - 2;
			
			if (r >= song.getLength()) {
				break;
			}
			
			for (int c = 0; c < song.getNumberOfChannels(); c++) {
				
				int value = song.getPatternAt(r, c);
				String stringValue = "\u00fa\u00fa";
				if (value != -1) {
					stringValue = HexUtils.toHex(value, 2);
				}
				
				for (int d = 0; d < 2; d++) {
					int bgColor = Screen.BLACK;
					int fgColor = (song.getSongPosition() == r) ? Screen.GREEN | Screen.BRIGHT : Screen.WHITE;
					if (r == editRow) {
						fgColor |= Screen.BRIGHT;
						if (state.getFocusedView() == this) {
							bgColor = (d == editDigit && c == editColumn) ? Screen.RED | Screen.BRIGHT : Screen.RED;
						} else {
							bgColor = Screen.BLACK | Screen.BRIGHT;
						}
					}
					getScreen().put(getX() + c*3 + d, getY() + y, stringValue.charAt(d), fgColor, bgColor);
				}
			}
		}
		
		
		
	}
}
