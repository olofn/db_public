package org.darkbits.tracker;

public class SaveSongFileHandler implements FileHandler {

	private State state;
	
	public SaveSongFileHandler(State state) {
		this.state = state;
	}
	@Override
	public void fileSelected(String filename) {
		System.out.println("Saving song to filename " + filename);
		Song.dumpToFile(state.getSong(), filename);
	}
}
