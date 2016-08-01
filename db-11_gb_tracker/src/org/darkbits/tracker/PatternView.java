package org.darkbits.tracker;

import java.awt.event.KeyEvent;

import org.darkbits.tracker.Pattern.Entry;

public class PatternView extends View {
	private static String KEYBOARD_NOTES = "zsxdcvgbhnjmq2w3er5t6y7ui9o0p";
	private static String HEX_VALUES = "0123456789abcdef";
	private int editRow = 0;
	private int editColumn = 0;
	private int editPattern = 0;
	private boolean editMode = false;
	private int auditionChannel = 0;
	private int octave = 3;
	private int add = 1;
	
	public PatternView(Screen screen, int x, int y, int height) {
		super(screen, x, y, 12, height);
		
	}
	
	@Override
	public void update(State state) {
		Song song = state.getSong();
		Pattern pattern = song.getPattern(editPattern);
		
		if (state.getFocusedView() == this) {
			
			getScreen().putBox(getX() - 1, getY() - 1, getWidth() + 2, getHeight() + 2, Screen.CYAN);
			
			if (state.getInput().wasKeyPressed(KeyEvent.VK_DOWN)) {
				editRow = (editRow + 1) % pattern.getLength();
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_UP)) {
				editRow = (editRow + pattern.getLength() - 1) % pattern.getLength();
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_PAGE_DOWN)) {
				editRow = Math.min(editRow + 8, pattern.getLength() - 1);
			}
			if (state.getInput().wasKeyPressed(KeyEvent.VK_PAGE_UP)) {
				editRow = Math.max(editRow - 8, 0);
			}
			for (int i = 0; i <= 9; i++) {
				if (state.getInput().wasKeyPressed(KeyEvent.VK_0 + i)) {
					if (state.getInput().isKeyDown(KeyEvent.VK_SHIFT)) {
						octave = i;
					}
					if (state.getInput().isKeyDown(KeyEvent.VK_CONTROL)) {
						add = i;
					}
				}
			}
			
			if (state.getInput().wasKeyPressed(KeyEvent.VK_LEFT)) {
				editColumn = editColumn < 1 ? editColumn : editColumn - 1;
			}
			else if (state.getInput().wasKeyPressed(KeyEvent.VK_RIGHT)) {
				editColumn = editColumn > 3 ? editColumn : editColumn + 1;
			}
			
			for (char c : state.getInput().getTypedText().toLowerCase().toCharArray()) {
				Entry entry = pattern.get(editRow);
				int note = KEYBOARD_NOTES.indexOf(c);
				int hexValue = HEX_VALUES.indexOf(c); 
				
				if (c == '+') {
					editPattern++;
				}
				
				if (c == '-') {
					editPattern = Math.max(0, editPattern - 1);
				}
				
				if (c == ' ') {
					editMode = !editMode;
				}
				
				if (note >= 0 && editColumn == 0) {
					note += octave * 12;
					song.noteOn(auditionChannel, note);
				}
				
				if (c == 127) {
					note = Pattern.EMPTY_VALUE;
					hexValue = Pattern.EMPTY_VALUE;
				}
				
				if (!editMode) {
					continue;
				}
				
				switch(editColumn) {
				case 0:
					if (note >= 0) {
						entry.note = note;
						pattern.set(editRow, entry);
						editRow = (editRow + add) % pattern.getLength();
					}
					break;
				case 1:
					if (hexValue >= 0) {
						entry.volume = hexValue;
						pattern.set(editRow, entry);
						editRow = (editRow + add) % pattern.getLength();
					}
					break;
				case 2:
				case 3:
				case 4:
					if (hexValue >= 0) {
						if (hexValue == Pattern.EMPTY_VALUE) {
							entry.effect = 0;
						} else {
							int digit = editColumn - 2;
							char[] current = HexUtils.toHex(entry.effect, 3).toCharArray();
							current[digit] = c;
							entry.effect = Integer.parseInt(new String(current), 16);
						}
						pattern.set(editRow, entry);
						editRow = (editRow + add) % pattern.getLength();
						break;
					}
				}
			}
		}
		
		int titleFgColor = Screen.WHITE | Screen.BRIGHT;
		int titleBgColor = Screen.BLACK | Screen.BRIGHT;
		if (state.getFocusedView() == this) {
			titleBgColor = Screen.CYAN;
			titleFgColor = Screen.WHITE | Screen.BRIGHT;
		}
		getScreen().put(getX(), getY(), " PATTERN " + HexUtils.toHex(editPattern, 2) + " ", titleFgColor, titleBgColor);
		getScreen().put(getX(), getY()+1, "Oct " + HexUtils.toHex(octave, 1) + "  Add " + HexUtils.toHex(add, 1), Screen.WHITE, Screen.BLACK | Screen.BRIGHT);
		
		boolean isPlayingPattern = song.isPlayingPattern(editPattern);
		
		for (int y = 2; y < getHeight(); y++) {
			int row = (y - 2) + editRow - (getHeight() - 2) / 2;
			if (row < 0 || row >= pattern.getLength()) {
				continue;
			}
			
			Entry entry = pattern.get(row); 
			
			boolean isOnEditRow = (row == editRow);
			boolean isOnPlayRow = (row == song.getPatternPosition() && isPlayingPattern);
			int fgColor = isOnPlayRow ? Screen.GREEN | Screen.BRIGHT : Screen.WHITE;
			fgColor = isOnEditRow ? Screen.WHITE | Screen.BRIGHT : fgColor;
			int editRowBgColor = (editMode && state.getFocusedView() == this) ? Screen.RED : Screen.BLACK | Screen.BRIGHT;
			int rowBgColor = isOnEditRow ? editRowBgColor : Screen.BLACK;
			int editCellBgColor = editMode ? Screen.RED | Screen.BRIGHT : Screen.WHITE;
			if (state.getFocusedView() != this) {
				editCellBgColor = editRowBgColor;
			}
			int editColumnBgColor = isOnEditRow ? editCellBgColor : Screen.BLACK;
			int rowColor = row % 4 == 0 ? fgColor | Screen.BRIGHT : fgColor;
				
			final String[] notes = new String[] { "C-", "C#", "D-", "D#", "E-", "F-", "F#", "G-", "G#", "A-", "A#", "B-" };
			int octave = entry.note / 12;
			String noteString =  entry.note == Pattern.EMPTY_VALUE ? "\u00fa\u00fa\u00fa" : notes[entry.note % 12] + octave;
			String volumeString = entry.volume == Pattern.EMPTY_VALUE ? "\u00fa" : HexUtils.toHex(entry.volume, 1);
			String effectString = entry.effect == 0 ? "\u00fa\u00fa\u00fa" : HexUtils.toHex(entry.effect, 3);
			
			getScreen().putBackgroundColor(getX(), getY() + y, 12, 1, rowBgColor);
			
			if (editColumn == 0)
			{
				getScreen().putBackgroundColor(getX() + 3, getY() + y, 3, 1, editColumnBgColor);
			}
			else if (editColumn == 1)
			{
				getScreen().putBackgroundColor(getX() + 7, getY() + y, 1, 1, editColumnBgColor);
			}
			else if (editColumn == 2)
			{
				getScreen().putBackgroundColor(getX() + 9, getY() + y, 1, 1, editColumnBgColor);
			}
			else if (editColumn == 3)
			{
				getScreen().putBackgroundColor(getX() + 10, getY() + y, 1, 1, editColumnBgColor);
			}
			else if (editColumn == 4)
			{
				getScreen().putBackgroundColor(getX() + 11, getY() + y, 1, 1, editColumnBgColor);
			}
			
			getScreen().put(getX(), getY() + y, HexUtils.toHex(row, 2), rowColor);
			getScreen().put(getX() + 3, getY() + y, noteString, fgColor);
			getScreen().put(getX() + 7, getY() + y, volumeString, fgColor);
			getScreen().put(getX() + 9, getY() + y, effectString, fgColor);
		}
	}
	
	public void setAuditionChannel(int auditionChannel) {
		this.auditionChannel = auditionChannel;
	}
	
	public void setEditPattern(State state, int editPattern) {
		this.editPattern = editPattern;
		editRow = Math.min(editRow, state.getSong().getPattern(editPattern).getLength());
	}
}
