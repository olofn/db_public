package org.darkbits.tracker;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;

public class Pattern {
	public static final int EMPTY_VALUE = 0x10000;
	
	public static class Entry implements Cloneable {
		public int note = EMPTY_VALUE;
		public int volume = EMPTY_VALUE;
		public int effect;
		
		@Override
		public Entry clone() {
			try {
				return (Entry)super.clone();
			} catch (CloneNotSupportedException e) {
				throw new RuntimeException(e);
			}
		}
		
		public String toString() {
			final String[] notes = new String[] { "C-", "C#", "D-", "D#", "E-", "F-", "F#", "G-", "G#", "A-", "A#", "B-" };
			int octave = note / 12;
			String noteString =  note == EMPTY_VALUE ? "..." : notes[note % 12] + octave;
			String volumeString = volume == EMPTY_VALUE ? "." : HexUtils.toHex(volume, 1);
			String effectString = effect == 0 ? "..." : HexUtils.toHex(effect, 3);
			return noteString + " " + volumeString + " " + effectString; 
		}

		public static void dumpToStream(Entry entry, ObjectOutputStream stream) throws IOException {
			stream.writeInt(entry.note);
			stream.writeInt(entry.volume);
			stream.writeInt(entry.effect);
		}
		
		public static Entry createFromStream(ObjectInputStream stream) throws IOException {
			Entry entry = new Entry();
			entry.note = stream.readInt();
			entry.volume = stream.readInt();
			entry.effect = stream.readInt();
			return entry;
		}
	}

	private final List<Entry> entries = new ArrayList<Entry>();

	public Pattern(int length) {
		for (int i = 0; i < length; i++) {
			entries.add(new Entry());
		}
	}
	
	public Entry get(int index) {
		return entries.get(index).clone();
	}
	
	public void set(int index, Entry entry) {
		entries.set(index, entry.clone());
	}
	
	public int getLength() {
		return entries.size();
	}

	public static void dumpToStream(Pattern pattern, ObjectOutputStream stream) throws IOException {
		stream.writeInt(pattern.entries.size());
		for (Entry entry: pattern.entries) {
			Entry.dumpToStream(entry, stream);
		}
	}
	
	public static Pattern createFromStream(ObjectInputStream stream) throws IOException {
		int length = stream.readInt();
		Pattern pattern = new Pattern(length);
		for (int i = 0; i < length; i++) {
			Entry entry = Entry.createFromStream(stream);
			pattern.entries.set(i, entry);
		}
		return pattern;
	}
}
