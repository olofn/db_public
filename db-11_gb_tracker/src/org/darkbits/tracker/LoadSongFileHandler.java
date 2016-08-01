package org.darkbits.tracker;

public class LoadSongFileHandler implements FileHandler {

	private State state;
	
	public LoadSongFileHandler(State state) {
		this.state = state;
	}
	
	@Override
	public void fileSelected(String filename) {
		System.out.println("Loading song from " + filename);
		Song song = Song.createFromFile(state.getSynth(), filename);
		state.setSong(song);	
	}

}
