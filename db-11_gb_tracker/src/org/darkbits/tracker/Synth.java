package org.darkbits.tracker;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.Random;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.SourceDataLine;

public class Synth {
	public static final int FX_PORTATMENTO_UP = 0x1;
	public static final int FX_PORTATMENTO_DOWN = 0x2;
	public static final int FX_DUTY_CYCLE = 0x4;
	public static final int FX_NOISE_PERIOD = 0x4;
	public static final int FX_VOLUME_ENV_UP = 0x5;
	public static final int FX_VOLUME_ENV_DOWN = 0x6;
	public static final int FX_LENGTH = 0x7;
	public static final int FX_VOLUME = 0x10;

	private static abstract class Voice {
		public boolean useLength;
		public int length;
		public int pos;
		public double phase;

		public boolean isPlaying() {
			return !useLength || pos > 0;
		}

		public abstract void renderFrame(float[] buffer, long frameCount);
	}

	private static class Pulse extends Voice {
		public int sweepTime;
		public int sweepShift;
		public int sweepDirection;
		public int duty;
		public int volume;
		public int startVolume = 15;
		public int envDelta = -1;
		public int envTime = 2;
		public int freq;
		public int startFreq;

		@Override
		public void renderFrame(float[] buffer, long frameCount) {
			double dt = (1.0 / 256.0) / buffer.length;
			double freq = 131072.0 / (2048.0 - this.freq);
			double dp = dt * freq;
			double threshold = Math.max(0.125, this.duty * 0.25);
			float volume = this.volume / 31.0f;

			for (int i = 0; i < buffer.length; i++) {
				phase += dp;
				phase -= Math.floor(phase);
				buffer[i] = phase < threshold ? -volume : volume;
			}

			if (sweepTime != 0 && frameCount % (sweepTime * 2) == 0) {
				int sweepAmount = this.freq / (1 << sweepShift);
				this.freq += sweepDirection * sweepAmount;

				if (this.freq < 0) {
					this.freq = 0;
				}
			}

			if (envTime != 0 && frameCount % (envTime * 4) == 0) {
				this.volume += envDelta;

				if (this.volume > 15) {
					this.volume = 15;
				}

				if (this.volume < 0) {
					this.volume = 0;
				}
			}

			if (useLength && frameCount % 4 == 0) {
				pos--;
			}
		}

		@Override
		public boolean isPlaying() {
			return super.isPlaying() && this.freq < 0x800;
		}
	}

	private static class Wave extends Voice {
		public int[] data = new int[] { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab,
				0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
		public int volumeShift = 4;
		public int freq;
		
		private int samplePos = 0;
		private int sampleData = 7;
		
		{
			useLength = true;
			length = 32;
		}
		
		@Override
		public void renderFrame(float[] buffer, long frameCount) {
			double dt = (1.0 / 256.0) / buffer.length;
			double freq = 131072.0 / (2048.0 - this.freq);
			double dp = dt * freq * 32;
			
			for (int i = 0; i < buffer.length; i++) {
				phase += dp;
				if (phase > 1.0) {
					phase -= Math.floor(phase);
					samplePos = (samplePos + 1) % 32;
					sampleData = data[samplePos / 2];
					sampleData = samplePos % 2 == 0 ? sampleData & 0xf : (sampleData >> 4) & 0xf;
					sampleData -= 7;
				}
				;
				buffer[i] = (sampleData >> volumeShift) / 8.0f;
			}

			if (useLength && frameCount % 4 == 0) {
				pos--;
			}
		}
	}

	static class Noise extends Voice {
		public int volume;
		public int envDelta = -1;
		public int envTime = 2;
		public boolean shortPeriod = false;
		public int frequencyShift;
		public int frequencyDivider;

		public float currentValue;
		public int seed = 1;

		@Override
		public void renderFrame(float[] buffer, long frameCount) {
			int d = (frequencyDivider == 0) ? 8 : frequencyDivider * 16;
			double freq = 4194304.0 / (d << frequencyShift);
			double dt = (1.0 / 256.0) / buffer.length;
			double dp = dt * freq;
			float volume = this.volume / 31.0f;

			for (int i = 0; i < buffer.length; i++) {
				phase += dp;
				if (phase > 1.0) {
					phase -= Math.floor(phase);
					currentValue = (new Random(seed * 997 * seed).nextInt() & 0x100000) != 0 ? -1.0f
							: 1.0f;
					seed = (seed + 1) % (shortPeriod ? 127 : 32767);
				}
				buffer[i] = currentValue * volume;
			}

			if (envTime != 0 && frameCount % (envTime * 4) == 0) {
				this.volume += envDelta;

				if (this.volume > 15) {
					this.volume = 15;
				}

				if (this.volume < 0) {
					this.volume = 0;
				}
			}

			if (useLength && frameCount % 4 == 0) {
				pos--;
			}
		}
	}

	static class OutputChannel {
		public final float buffer[];
		public final boolean[] routeChannel = new boolean[4];
		public float volume;

		public OutputChannel(int bufferSize) {
			buffer = new float[bufferSize];
		}
	}

	private final SourceDataLine dataLine;
	private final AudioFormat audioFormat;
	private final Pulse[] pulse = new Pulse[] { new Pulse(), new Pulse() };
	private final Wave wave = new Wave();
	private final Noise noise = new Noise();
	private final Voice[] voices = new Voice[] { pulse[0], pulse[1], wave,
			noise };
	private final float[] voiceBuffer;
	private final OutputChannel[] so = new OutputChannel[2];
	private final int internalFrameSize;
	private boolean masterSoundOn = true;
	private long frameCount = 0;
	private int samplesToRender = 0;

	public Synth() throws LineUnavailableException {
		this(AudioSystem.getSourceDataLine(new AudioFormat(44100, 16, 2, true,
				false)));
	}

	public Synth(SourceDataLine dataLine) throws LineUnavailableException {
		this(dataLine, dataLine.getFormat());
	}

	public Synth(SourceDataLine dataLine, AudioFormat audioFormat)
			throws LineUnavailableException {
		this.dataLine = dataLine;
		this.audioFormat = audioFormat;

		if (audioFormat.getChannels() != 1 && audioFormat.getChannels() != 2) {
			throw new IllegalArgumentException(
					"Invalid number of channels (must be 1 or 2): "
							+ audioFormat.getChannels());
		}

		if (audioFormat.getSampleSizeInBits() != 8
				&& audioFormat.getSampleSizeInBits() != 16) {
			throw new IllegalArgumentException(
					"Invalid sample size (must be 8 or 16 bits): "
							+ audioFormat.getSampleSizeInBits());
		}

		int expectedFormatFrameSize = audioFormat.getChannels()
				* audioFormat.getSampleSizeInBits() / 8;

		if (audioFormat.getFrameSize() != expectedFormatFrameSize) {
			throw new IllegalArgumentException("Audio format frame size was "
					+ audioFormat.getFrameSize() + " expected "
					+ expectedFormatFrameSize);
		}

		internalFrameSize = (int) Math
				.round(audioFormat.getSampleRate() / 256.0);
		this.voiceBuffer = new float[internalFrameSize];
		this.so[0] = new OutputChannel(internalFrameSize);
		this.so[1] = new OutputChannel(internalFrameSize);

		// TODO: Open somewhere else?
		this.dataLine.open(audioFormat, 4096 * 4);
		this.dataLine.start();

		this.so[0].routeChannel[0] = true;
		this.so[1].routeChannel[0] = true;
		this.so[0].routeChannel[1] = true;
		this.so[1].routeChannel[1] = true;
		this.so[0].routeChannel[2] = true;
		this.so[1].routeChannel[2] = true;
		this.so[0].routeChannel[3] = true;
		this.so[1].routeChannel[3] = true;
		this.so[0].volume = 1.0f;
		this.so[1].volume = 1.0f;
		this.masterSoundOn = true;
	}

	public AudioFormat getAudioFormat() {
		return dataLine.getFormat();
	}

	public void renderSamples(int samplesToRender) {
		this.samplesToRender += samplesToRender;

		while (this.samplesToRender > voiceBuffer.length) {
			renderFrame();
			this.samplesToRender -= voiceBuffer.length;
		}
	}

	public int getNeededSamples() {
		return dataLine.available() / (dataLine.getFormat().getFrameSize())
				- samplesToRender;
	}

	private void renderFrame() {
		for (int i = 0; i < so.length; i++) {
			Arrays.fill(so[i].buffer, 0.0f);
		}

		if (masterSoundOn) {
			for (int i = 0; i < voices.length; i++) {
				if (!voices[i].isPlaying()) {
					continue;
				}

				voices[i].renderFrame(voiceBuffer, frameCount);

				for (int j = 0; j < so.length; j++) {
					if (so[j].routeChannel[i]) {
						mixBuffers(so[j].buffer, voiceBuffer);
					}
				}
			}

			for (int i = 0; i < so.length; i++) {
				gainBuffer(so[i].buffer, so[i].volume * 0.25f);
			}
		}

		outputFrame();

		frameCount++;
	}

	private void outputFrame() {
		byte[] out = new byte[audioFormat.getFrameSize() * internalFrameSize];

		for (int i = 0; i < internalFrameSize; i++) {
			if (audioFormat.getChannels() == 2) {
				short left = (short) (so[0].buffer[i] * 0x7fff);
				short right = (short) (so[1].buffer[i] * 0x7fff);
				byte leftLo = (byte) left;
				byte leftHi = (byte) (left >> 8);
				byte rightLo = (byte) right;
				byte rightHi = (byte) (right >> 8);

				if (audioFormat.getSampleSizeInBits() == 8) {
					out[i * 2 + 0] = leftHi;
					out[i * 2 + 1] = rightHi;
				} else if (audioFormat.getSampleSizeInBits() == 16) {
					if (audioFormat.isBigEndian()) {
						out[i * 4 + 0] = leftHi;
						out[i * 4 + 1] = leftLo;
						out[i * 4 + 2] = rightHi;
						out[i * 4 + 3] = rightLo;
					} else {
						out[i * 4 + 0] = leftLo;
						out[i * 4 + 1] = leftHi;
						out[i * 4 + 2] = rightLo;
						out[i * 4 + 3] = rightHi;
					}
				}
			} else if (audioFormat.getChannels() == 1) {
				short mono = (short) ((so[0].buffer[i] + so[1].buffer[i]) * 0x3fff);
				byte monoLo = (byte) mono;
				byte monoHi = (byte) (mono >> 8);
				if (audioFormat.getSampleSizeInBits() == 8) {
					out[i] = monoHi;
				} else if (audioFormat.getSampleSizeInBits() == 16) {
					if (audioFormat.isBigEndian()) {
						out[i * 2 + 0] = monoHi;
						out[i * 2 + 1] = monoLo;
					} else {
						out[i * 2 + 0] = monoLo;
						out[i * 2 + 1] = monoHi;
					}
				}
			}
		}

		dataLine.write(out, 0, out.length);
	}

	private static void gainBuffer(float[] dest, float volume) {
		for (int i = 0; i < dest.length; i++) {
			dest[i] *= volume;
		}
	}

	private static void mixBuffers(float[] dest, float[] src) {
		for (int i = 0; i < dest.length; i++) {
			dest[i] += src[i];
		}
	}

	public void noteOn(int channel, int note, int volume) {
		if (channel < 2) {
			noteOnPulse(channel, note, volume);
		}
		
		if (channel == 2) {
			noteOnWave(note, volume);
		}

		if (channel == 3) {
			noteOnNoise(note, volume);
		}
	}

	public void noteOnPulse(int channel, int note, int volume) {
		double freqHz = 440.0 * Math.pow(2.0, (note - 57.0) / 12.0);
		int freqGb = (int) Math.round(2048.0 - 131072.0 / freqHz);
		pulse[channel].startFreq = pulse[channel].freq = freqGb;
		pulse[channel].volume = pulse[channel].startVolume = volume;
		pulse[channel].pos = pulse[channel].length;
	}
	
	public void noteOnWave(int note, int volume) {
		double freqHz = 440.0 * Math.pow(2.0, (note - 57.0) / 12.0);
		int freqGb = (int) Math.round(2048.0 - 131072.0 / freqHz);
		wave.freq = freqGb;
		wave.volumeShift = (int)Math.round(4.0 - 4.0 * (volume / 15.0));
		wave.pos = wave.length;
	}

	public void noteOnNoise(int note, int volume) {
		double freqHz = 440.0 * Math.pow(2.0, (note - 57.0) / 12.0);
		int freqD = (int) Math
				.round((4194304.0 / (freqHz * 127.0 / 8.0)) / 8.0);
		int freqS = 0;
		while (freqD > 0xf) {
			freqD >>>= 1;
			freqS++;
		}

		if (freqD == 1) {
			freqD = 0;
		} else {
			freqD = (freqD / 2);
		}

		if (freqS > 0xf) {
			freqS = 0xf;
		}

		noise.frequencyDivider = freqD;
		noise.frequencyShift = freqS;
		noise.volume = volume;
		noise.pos = noise.length;
	}

	public void setFx(int channel, int fx, int value) {
		if (channel < 2) {
			setPulseFx(channel, fx, value);
		}
		
		if (channel == 2) {
			setWaveFx(channel, fx, value);
		}
		
		if (channel == 3) {
			setNoiseFx(channel, fx, value);
		}
	}

	private void setPulseFx(int channel, int fx, int value) {
		Pulse p = pulse[channel];
		switch (fx) {
		case FX_PORTATMENTO_UP:
		case FX_PORTATMENTO_DOWN:
			p.sweepDirection = (fx == FX_PORTATMENTO_UP) ? 1 : -1;
			p.sweepShift = value >> 4;
			p.sweepTime = value & 0xf;
			break;
		case FX_DUTY_CYCLE:
			p.duty = value % 4;
			break;
		case FX_VOLUME_ENV_UP:
		case FX_VOLUME_ENV_DOWN:
			p.envDelta = (fx == FX_VOLUME_ENV_UP) ? 1 : -1;
			p.envTime = (value == 0) ? 0 : (0x100 - value);
			break;
		case FX_LENGTH:
			p.length = value;
			p.pos = 0;
			p.useLength = (value != 0);
			break;
		case FX_VOLUME:
			p.volume = value % 0xf;
			break;
		}
	}

	private void setWaveFx(int channel, int fx, int value) {
		Wave p = wave;
		switch (fx) {
		case FX_LENGTH:
			p.length = value;
			p.useLength = (value != 0);
			break;
		case FX_VOLUME:
			p.volumeShift = (int)Math.round(4.0 - 4.0 * (value / 15.0));
			break;
		}
	}
	
	private void setNoiseFx(int channel, int fx, int value) {
		Noise p = noise;
		switch (fx) {
		case FX_NOISE_PERIOD:
			p.shortPeriod = value != 0;
			break;
		case FX_VOLUME_ENV_UP:
		case FX_VOLUME_ENV_DOWN:
			p.envDelta = (fx == FX_VOLUME_ENV_UP) ? 1 : -1;
			p.envTime = (value == 0) ? 0 : (0x100 - value);
			break;
		case FX_LENGTH:
			p.length = value;
			p.useLength = (value != 0);
			break;
		case FX_VOLUME:
			p.volume = value % 0xf;
			break;
		}
	}

	/*
	 * private int pulseSweep(int channel, int value) { pulse[v].sweepShift =
	 * value & 0x7; pulse[v].sweepDirection = (value & (1 << 3)) == 0 ? 1 : -1;
	 * pulse[v].sweepTime = (value >> 4) & 0x7; return value; }
	 * 
	 * private int pulseDuty(int value, int v) { pulse[v].length = 64 - (value &
	 * 0x1f); pulse[v].duty = (value >> 6) & 0x3; return value & 0x60; }
	 * 
	 * private int pulseEnv(int value, int v) { pulse[v].envDelta = (value & (1
	 * << 3)) == 0 ? -1 : 1; pulse[v].startVolume = value >>> 4;
	 * pulse[v].envTime = value & 0x7; return value; }
	 * 
	 * private int pulseFreqLo(int value, int v) { pulse[v].startFreq =
	 * (pulse[v].startFreq & 0xff00) | value; return 0; }
	 * 
	 * private int pulseFreqHi(int value, int v) { pulse[v].startFreq =
	 * (pulse[v].startFreq & 0x00ff) | ((value & 0x7) << 8); pulse[v].useLength
	 * = (value & (1 << 6)) != 0; if ((value & (1 << 7)) != 0) { pulse[v].freq =
	 * pulse[v].startFreq; pulse[v].volume = pulse[v].startVolume; } return
	 * value & (1 << 6); }
	 */

	public void dump(OutputStream os) throws IOException {
		throw new UnsupportedOperationException("Not yet implemented");
	}

	public void load(InputStream is) throws IOException {
		throw new UnsupportedOperationException("Not yet implemented");
	}

	public int getNumberOfChannels() {
		return 4;
	}
}
