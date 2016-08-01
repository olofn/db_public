package org.darkbits.tracker;

import java.awt.event.KeyEvent;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class FileView extends View {

	private static class FoundFile implements Comparable<FoundFile>
	{
		public boolean directory;
		public String name;
		public String path;
		
		public String toString() {
			return "[director="+directory+" name="+name+" path="+path+"]";
		}

		@Override
		public int compareTo(FoundFile f) {
			return name.compareTo(f.name);
		}
	}
	
	private String path;
	private List<FoundFile> foundFiles = new ArrayList<FoundFile>();
	private int selectedRow;
	private String name = "";
	private Stack<Integer> selectedRowStack = new Stack<Integer>();
	private int listOffset;
	private String title = "title";
	
	public FileView(Screen screen) {
		super(screen, 5, 10, 70, 40);
	}

	public void init() {
		selectedRow = 0;
		enter(".");
	}
	
	@Override
	public void update(State state) {
		
		if (state.getFocusedView() != this) {
			return;
		}
		
		if (state.getInput().wasKeyPressed(KeyEvent.VK_UP)){
			selectedRow--;
			if (selectedRow < 0) {
				selectedRow = 0;
			}
			if (!foundFiles.get(selectedRow).directory) {
				name = foundFiles.get(selectedRow).name;
			} else {
				name = "";
			}
		}
		
		if (state.getInput().wasKeyPressed(KeyEvent.VK_DOWN)){
			selectedRow++;
			if (selectedRow >= foundFiles.size()) {
				selectedRow = foundFiles.size() - 1;
			}
			if (!foundFiles.get(selectedRow).directory) {
				name = foundFiles.get(selectedRow).name;
			}else {
				name = "";
			}
		}
		
		for (char c : state.getInput().getTypedText().toCharArray()) {
			if (c == 27) {
				state.setDialogView(null);
				return;
			}
			if (c == 8) {
				if (name.length() > 0) {
					name = name.substring(0, name.length() - 1);
				}
				continue;
			} 
			if (c == 13 || c == 10) {
		
				if (name.length() > 0) {
					state.getFileHandler().fileSelected(path + "\\" + name);
					state.setDialogView(null);
					return;
				}
				FoundFile f = foundFiles.get(selectedRow);
				if (f.directory) {
					enter(f.path);
				
					if (f.name.equals("..")) {
						if (selectedRowStack.size() > 0) {
							selectedRow = selectedRowStack.pop();
						} else {
							selectedRow = 0;
						}
					} else {
						selectedRowStack.push(selectedRow);
						selectedRow = 0;
					}
				}
			
				continue;
			}
			
			name += c;
		}
		
		getScreen().putThickBox(getX() - 1, getY() - 1, getWidth() + 2, getHeight() + 2, Screen.CYAN, Screen.BLACK);
		getScreen().putBackgroundColor(getX(), getY(), getWidth(), 1, Screen.CYAN);
		getScreen().put(getX() + getWidth() / 2 - title.length() / 2 - 1, getY(), title, Screen.WHITE | Screen.BRIGHT);
		int numberToDisplay = getHeight() - 5;
		if (selectedRow >= listOffset + numberToDisplay) {
			listOffset++;
			if (listOffset >= foundFiles.size()) {
				listOffset = foundFiles.size() - 1;
			}
		}
		if (selectedRow < listOffset) {
			listOffset--;
			if (listOffset < 0) {
				listOffset = 0;
			}
		}
		int y = 3;
		for (int i = listOffset; i < listOffset + numberToDisplay; i++){	
			if (i >= foundFiles.size()){
				break;
			}
			FoundFile file = foundFiles.get(i);
			int fgColor = Screen.WHITE;
			if (file.directory) {
				fgColor |= Screen.BRIGHT;
			}
			int bgColor = Screen.BLACK;
			if (selectedRow == i)
			{
				bgColor = Screen.CYAN;
			}
			String fname = file.name;
			if (fname.length() >= getWidth() - 3) {
				fname = "..."+fname.substring(fname.length() - getWidth() + 6);
			}
			getScreen().put(getX() + 1, getY() + y, fname, fgColor, bgColor);
			y++;
		}
		
		getScreen().put(getX(), getY() + 1, path, Screen.WHITE | Screen.BRIGHT);
		String fname =  "Name:"+name;
		if (name.length() >= getWidth() - 7) {
			fname = "Name:"+fname.substring(fname.length() - getWidth() + 5);
		}
		getScreen().put(getX(), getY() + getHeight() - 1, fname, Screen.WHITE | Screen.BRIGHT);
	}
	
	private void enter(String directoryPath){
		foundFiles.clear();
		File dir = new File(directoryPath);
		try {
			path = dir.getCanonicalPath();
			if (path.length() > getWidth()) {
				path = path.substring(0, 3) + "..." + path.substring(path.length() - getWidth() + 6);
			}
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		try
		{
			List<FoundFile> foundDirectories = new ArrayList<FoundFile>();
			List<FoundFile> foundNonDirectories = new ArrayList<FoundFile>();
			FoundFile back = new FoundFile();
			back.directory = true;
			back.name = "..";
			back.path = dir.getCanonicalPath() + "/..";
			foundDirectories.add(back);
			File[] files = dir.listFiles();
			if (files.length != 0) {
				for (File file : files) {
					
					FoundFile foundFile = new FoundFile();
					foundFile.directory = file.isDirectory();
					foundFile.name = file.getName();
					foundFile.path = file.getCanonicalPath();
					
					if (foundFile.directory) {
						foundDirectories.add(foundFile);
					} else {
						foundNonDirectories.add(foundFile);
					}
				}
			}
			Collections.sort(foundDirectories);
			Collections.sort(foundNonDirectories);
			foundFiles.addAll(foundDirectories);
			foundFiles.addAll(foundNonDirectories);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getTitle() {
		return title;
	}
}
