#pragma once

class SoundDevice {
public:
	SoundDevice(HWND hwnd, int sampleRate, int bufferSize);

	~SoundDevice();

	void play(float *left, float *right, int length);
	
private:
	void lock(void **ptr1, unsigned long *bytes1, void **ptr2, unsigned long *bytes2, int length);

	LPDIRECTSOUNDBUFFER createBasicBuffer(int sampleRate, int bps, int bufferSize);	

	int bufferSize;
	int sampleRate;
	int writeOffset;
	LPDIRECTSOUND8 dsObject;
	LPDIRECTSOUNDBUFFER dsBuffer;

};
