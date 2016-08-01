package org.darkbits.tracker;

public class State {
	private final Input input;
	private View focusedView;
	private View dialogView;
	private Song song;
	private Synth synth;
	
	private FileHandler fileHandler;
	
	public State(Input input) {
		super();
		this.input = input;
	}

	public Input getInput() {
		return input;
	}
	
	public View getFocusedView() {
		if (dialogView != null) {
			return dialogView;
		}
		return focusedView;
	}
	
	public void setFocusedView(View focusedView) {
		this.focusedView = focusedView;
	}
	
	public void setDialogView(View dialogView) {
		this.dialogView = dialogView;
	}

	public void setFileHandler(FileHandler fileHandler) {
		this.fileHandler = fileHandler;
	}

	public FileHandler getFileHandler() {
		return fileHandler;
	}

	public void setSong(Song song) {
		this.song = song;
	}

	public Song getSong() {
		return song;
	}

	public void setSynth(Synth synth) {
		this.synth = synth;
	}

	public Synth getSynth() {
		return synth;
	}

}
