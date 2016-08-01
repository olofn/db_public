#define WIN32_LEAN_AND_MEAN
#define _INC_STDLIB // To get rid of stdlib.h included by windows.h
#define NOMINMAX
#include <windows.h>
#include <mmreg.h>
#include <dsound.h>

#include "sounddevice.h"

inline short toShort(float f) 
{
	int i = (int)(f * 0x8000);
	return i < -32768 ? -32768 : (i > 32767 ? 32767 : (short)i);
}

SoundDevice::SoundDevice(HWND hwnd, int sampleRate, int bufferSize) :
	dsObject(0),
	dsBuffer(0),
	writeOffset(0)
{
	this->sampleRate = sampleRate;
	this->bufferSize = bufferSize;

	DirectSoundCreate8(NULL, &dsObject, NULL);
	dsObject->SetCooperativeLevel(hwnd ? hwnd : GetDesktopWindow(), DSSCL_PRIORITY);

	if (dsObject)
	{
		dsBuffer = createBasicBuffer(sampleRate, 16, bufferSize);

		if (dsBuffer) {
			LPVOID ptr1;
			DWORD bytes1;
			LPVOID ptr2;
			DWORD bytes2;

			HRESULT lockResult = dsBuffer->Lock(
				0,
				0,
				&ptr1,
				&bytes1,
				&ptr2,
				&bytes2,
				DSBLOCK_ENTIREBUFFER);

			if (lockResult == DS_OK) 
			{
				ZeroMemory(ptr1, bytes1);

				if (ptr2) 
				{
					ZeroMemory(ptr2, bytes2);
				}

				dsBuffer->Unlock(ptr1, bytes1, ptr2, bytes2);
			}

			dsBuffer->SetCurrentPosition(0);
			dsBuffer->Play(0, 0, DSBPLAY_LOOPING);
		}
	}
	
	// TODO: Fix primary buffer sheisse
}

SoundDevice::~SoundDevice()
{
	if (dsBuffer)
	{
		// TODO: Free soundbuffer somehow?	
	}

	if (dsObject)
    {
        IDirectSound_Release(dsObject);
    } 
}

void SoundDevice::play(float *left, float *right, int length)
{
	if (!dsBuffer) 
	{
		return;
	}
	
	void *ptr1, *ptr2;
	unsigned long bytes1, bytes2;

	int bytesPerSample = 4;
	lock(&ptr1, &bytes1, &ptr2, &bytes2, length * bytesPerSample);
	
	unsigned long samples1 = bytes1 / bytesPerSample;
	unsigned long samples2 = bytes2 / bytesPerSample;

	int i = 0;

	for (unsigned int pos = 0; pos < samples1; pos++) {
		unsigned short l = toShort(left[i]);
		unsigned short r = toShort(right[i]);
		((unsigned char*)ptr1)[pos * 4 + 0] = l & 0xff;
		((unsigned char*)ptr1)[pos * 4 + 1] = l >> 8;
		((unsigned char*)ptr1)[pos * 4 + 2] = r & 0xff;
		((unsigned char*)ptr1)[pos * 4 + 3] = r >> 8;
		i++;
	}

	for (unsigned int pos = 0; pos < samples2; pos++) {
		unsigned short l = toShort(left[i]);
		unsigned short r = toShort(right[i]);
		((unsigned char*)ptr1)[pos * 4 + 0] = l & 0xff;
		((unsigned char*)ptr1)[pos * 4 + 1] = l >> 8;
		((unsigned char*)ptr1)[pos * 4 + 2] = r & 0xff;
		((unsigned char*)ptr1)[pos * 4 + 3] = r >> 8;
		i++;
	}

	dsBuffer->Unlock(ptr1, bytes1, ptr2, bytes2);
}

void SoundDevice::lock(void **ptr1, unsigned long *bytes1, void **ptr2, unsigned long *bytes2, int length)
{
	if (dsBuffer) 
	{		
		while (true) {
			unsigned long playPosition;
			dsBuffer->GetCurrentPosition(&playPosition, NULL);
			int r1 = playPosition;
			int r2 = playPosition + bufferSize;
			int w1 = writeOffset;
			int w2 = writeOffset + length;

			if ((w2 < r1) || (w1 > r1 && w2 < r2)) {
				break;
			} else {
				Sleep(1);//__max((500 * length) / sampleRate, 1));
			}
		};

		
		HRESULT lockResult = dsBuffer->Lock(
			writeOffset,
			length,
			ptr1,
			bytes1,
			ptr2,
			bytes2,
			0);

		writeOffset = (writeOffset + length) % bufferSize;

		if (lockResult == DS_OK) 
		{
			if (!*ptr1) *bytes1 = 0;
			if (!*ptr2) *bytes2 = 0;

			return;				
		}
			
	} 

	ptr1 = ptr2 = 0;
	bytes1 = bytes2 = 0;
}

LPDIRECTSOUNDBUFFER SoundDevice::createBasicBuffer(int sampleRate, int bps, int bufferSize)
{ 
  WAVEFORMATEX wfx; 
  DSBUFFERDESC dsbdesc; 
  LPDIRECTSOUNDBUFFER pDsb = NULL;
  HRESULT hr; 
 
  // Set up WAV format structure. 

  memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
  wfx.wFormatTag = WAVE_FORMAT_PCM; 
  wfx.nChannels = 2; 
  wfx.nSamplesPerSec = sampleRate; 
  wfx.nBlockAlign = 4; 
  wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign; 
  wfx.wBitsPerSample = bps; 
 
  // Set up DSBUFFERDESC structure. 
 
  memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
  dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
  dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2; 
  dsbdesc.dwBufferBytes = bufferSize; 
  dsbdesc.lpwfxFormat = &wfx; 
 
  // Create buffer. 
  hr = dsObject->CreateSoundBuffer(&dsbdesc, &pDsb, NULL);
  return pDsb;
} 


