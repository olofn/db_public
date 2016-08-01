package org.darkbits.tracker;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.sound.sampled.LineUnavailableException;

import org.darkbits.tracker.Pattern.Entry;

public class Song {
	private final static int TICKS_PER_16TH = 16;
	private final List<Pattern> patterns = new ArrayList<Pattern>();
	private final List<int[]> song = new ArrayList<int[]>();
	private int ticksPosition;
	private int songPosition;
	private int bpm = 120;
	private boolean playing = false;
	private Synth synth;

	public Song(Synth synth) {
		this.synth = synth;
		patterns.add(new Pattern(64));
	}

	public int getLength() {
		return song.size();
	}

	public int getPatternAt(int row, int channel) {
		return song.get(row)[channel];
	}

	public void putPatternAt(int row, int channel, int pattern) {
		song.get(row)[channel] = pattern;
	}

	public void setLength(int length) {
		if (length < 1) {
			length = 1;
		}

		while (length < song.size()) {
			song.remove(song.size() - 1);
		}
		while (length > song.size()) {
			song.add(new int[synth.getNumberOfChannels()]);
			for (int i = 0; i < synth.getNumberOfChannels(); i++) {
				song.get(song.size() - 1)[i] = -1;
			}
		}
	}

	public Pattern getPattern(int i) {
		while (i >= patterns.size()) {
			patterns.add(new Pattern(64));
		}
		return patterns.get(i);
	}

	public int getPatternPosition() {
		return ticksPosition / TICKS_PER_16TH;
	}

	public int getSongPosition() {
		return songPosition;
	}

	public void setSongPosition(int songPosition) {
		this.songPosition = songPosition;
		this.ticksPosition = 0;
	}
	
	public void update() {
		int neededSamples = synth.getNeededSamples();
		int samplesPerTick = Math.round(((synth.getAudioFormat()
				.getSampleRate() * 60.0f) / bpm)
				/ (4.0f * TICKS_PER_16TH));
		if (playing) {
			if (songPosition >= getLength()) {
				songPosition = 0;
			}

			while (neededSamples > 0) {
				int songPartLength = 0;
				for (int c = 0; c < getNumberOfChannels(); c++) {
					int patternIndex = getPatternAt(songPosition, c);

					if (patternIndex < 0) {
						continue;
					}

					Pattern p = getPattern(patternIndex);
					songPartLength = Math.max(songPartLength, p.getLength());

					if (ticksPosition % TICKS_PER_16TH == 0) {
						// Time to step the sequencer
						int patternPosition = getPatternPosition();
						if (patternPosition < p.getLength()) {
							Entry e = p.get(patternPosition);
							if (e.effect != 0) {
								int fx = e.effect >> 8;
								int value = e.effect & 0xff;
								synth.setFx(c, fx, value);
							}
							
							if (e.note != Pattern.EMPTY_VALUE) {
								int volume = e.volume == Pattern.EMPTY_VALUE ? 15
										: e.volume;
								synth.noteOn(c, e.note, volume);
							} else if (e.volume != Pattern.EMPTY_VALUE) {
								synth.setFx(c, Synth.FX_VOLUME, e.volume);
							}
						}
					}
				}

				synth.renderSamples(samplesPerTick);
				ticksPosition++;
				if (getPatternPosition() >= songPartLength) {
					ticksPosition = 0;
					songPosition = (songPosition + 1) % getLength();
				}
				neededSamples -= samplesPerTick;
			}
		} else {
			synth.renderSamples(neededSamples);
		}
	}

	public void noteOn(int channel, int note) {
		synth.noteOn(channel, note, 15);
	}

	public int getNumberOfChannels() {
		return synth.getNumberOfChannels();
	}

	public boolean isPlayingPattern(int pattern) {
		for (int c = 0; c < getNumberOfChannels(); c++) {
			if (getPatternAt(songPosition, c) == pattern) {
				return true;
			}
		}
		return false;
	}

	public void stop() {
		playing = false;
	}

	public void start() {
		playing = true;
	}

	public boolean isPlaying() {
		return playing;
	}

	public static void dumpToFile(Song song, String filename) {
		File file = new File(filename);
		FileOutputStream fileStream;
		try {
			fileStream = new FileOutputStream(file);
		} catch (FileNotFoundException e) {
			throw new RuntimeException(e);
		}
		ObjectOutputStream stream;
		try {
			stream = new ObjectOutputStream(fileStream);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		try {
			dumpToStream(song, stream);
			stream.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public static Song createFromFile(Synth synth, String filename) {
		File file = new File(filename);
		FileInputStream fileStream;
		try {
			fileStream = new FileInputStream(file);
		} catch (FileNotFoundException e) {
			throw new RuntimeException(e);
		}
		ObjectInputStream stream;
		try {
			stream = new ObjectInputStream(fileStream);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

		try {
			Song song = createFromStream(synth, stream);
			stream.close();
			return song;
		} catch (IOException e) {
			throw new RuntimeException(e);
		} catch (LineUnavailableException e) {
			throw new RuntimeException(e);
		}
	}

	private static void dumpToStream(Song song, ObjectOutputStream stream)
			throws IOException {
		stream.writeInt(song.patterns.size());
		for (Pattern pattern : song.patterns) {
			Pattern.dumpToStream(pattern, stream);
		}
		stream.writeInt(song.song.size());
		for (int i = 0; i < song.song.size(); i++) {
			stream.writeInt(song.song.get(i).length);
			for (int j = 0; j < song.song.get(i).length; j++) {
				stream.writeInt(song.song.get(i)[j]);
			}
		}
	}

	private static Song createFromStream(Synth synth, ObjectInputStream stream)
			throws IOException, LineUnavailableException {
		Song song = new Song(synth);
		int numberOfPatterns = stream.readInt();
		song.patterns.clear();
		for (int i = 0; i < numberOfPatterns; i++) {
			Pattern pattern = Pattern.createFromStream(stream);
			song.patterns.add(pattern);
		}
		int songLength = stream.readInt();
		song.setLength(songLength);
		for (int i = 0; i < songLength; i++) {
			int numberOfChannels = stream.readInt();
			for (int j = 0; j < numberOfChannels; j++) {
				int pattern = stream.readInt();
				song.song.get(i)[j] = pattern;
			}
		}
		return song;
	}
}
