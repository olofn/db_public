package org.darkbits.tracker;

import java.awt.AWTEvent;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

import javax.sound.sampled.LineUnavailableException;
import javax.swing.JFrame;

public class Main {
	@SuppressWarnings("serial")
	public static void main(String[] args) throws IOException, InterruptedException, LineUnavailableException {
		final Queue<AWTEvent> eventQueue = new ConcurrentLinkedQueue<AWTEvent>();
		Screen screen = new Screen(new Font());
		Canvas canvas = new Canvas(screen, 1);
		Input input = new Input();
		
		JFrame frame = new JFrame("Tracker") {
			{
				enableEvents(AWTEvent.FOCUS_EVENT_MASK | AWTEvent.KEY_EVENT_MASK);
			}
			
			@Override
			protected void processKeyEvent(KeyEvent e) {
				super.processKeyEvent(e);
				eventQueue.add(e);
			}
		};
		frame.setUndecorated(true);
		frame.setContentPane(canvas);
		frame.setResizable(false);
		frame.setLocationByPlatform(false);
		frame.setFocusTraversalKeysEnabled(false);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		int x = (int)(Toolkit.getDefaultToolkit().getScreenSize().getWidth() / 2.0 - frame.getWidth() / 2.0);
		int y = (int)(Toolkit.getDefaultToolkit().getScreenSize().getHeight() / 2.0 - frame.getHeight() / 2.0);
		frame.setLocation(x, y);
		frame.setVisible(true);
		
		
		Synth synth = new Synth();
		
		PatternView patternView = new PatternView(screen, 1, 2, 57);
		SongView songView = new SongView(screen, patternView, 15, 2, 57);
		FileView fileView = new FileView(screen);
		HelpView helpView = new HelpView(screen, 28, 2);
		
		State state = new State(input);
		state.setSong(new Song(synth));
		state.getSong().setLength(4);
		state.setSynth(synth);
		state.setFocusedView(patternView);
		
		SaveSongFileHandler saveSongFileHandler = new SaveSongFileHandler(state);
		LoadSongFileHandler loadSongFileHandler = new LoadSongFileHandler(state);
		
		while (true) {
			input.update(eventQueue, new Point(0, 0));
			
			if (input.wasKeyPressed(KeyEvent.VK_TAB)) {
				if (state.getFocusedView() == patternView) {
					state.setFocusedView(songView);
				} else {
					state.setFocusedView(patternView);
				}
			}
			
			if (input.wasKeyPressed(KeyEvent.VK_F1)) {
				state.setFocusedView(patternView);
			}
			
			if (input.wasKeyPressed(KeyEvent.VK_F2)) {
				state.setFocusedView(songView);
			}
			
			if (input.wasKeyPressed(KeyEvent.VK_F12)) {
				fileView.init();
				fileView.setTitle("LOAD DARKBITS TRACK MODULE");
				state.setFileHandler(loadSongFileHandler);
				state.setDialogView(fileView);
			}
			
			if (input.wasKeyPressed(KeyEvent.VK_F11)) {
				fileView.init();
				fileView.setTitle("SAVE DARKBITS TRACK MODULE");
				state.setFileHandler(saveSongFileHandler);
				state.setDialogView(fileView);
			}
			
			screen.clear();
			screen.put(0, 0, "                           \u00f0 DARKBITS TRACKER v0.1 \u00f0                            ", Screen.YELLOW | Screen.BRIGHT, Screen.RED);
			
			patternView.update(state);
			songView.update(state);
			helpView.update(state);
			
			
			Generated.put_DARKBITS_LOGO(screen, 27, 40);
			screen.put(76, 52, ".org", Screen.WHITE, Screen.BLACK);
			screen.put(50, 59, "by Per Larsson and Olof N\u0091ss\u0082n", Screen.WHITE, Screen.BLACK);
			
			fileView.update(state);
			
			canvas.drawFrame();
			state.getSong().update();
		}
	}
}
