#pragma once

class Delay
{
public:
	Delay() :
	  writePointer(0),
	  activeLastFrame(false),
	  lastTime(0.0f)
	{
		clearBuffer();
	}

	void process(float *left, float *right, int length, float time, float feedback, float wet)
	{
		if (wet == 0.0f)
		{
			activeLastFrame = false;
			return;
		}
		else
		{
			if (!activeLastFrame) {
				lastTime = time;
				clearBuffer();
			}

			activeLastFrame = true;
		}

		time = lastTime * 0.95f + time * 0.05f;

		float startDelayTime = (lastTime * 0.9f + 0.05f) * BUFFER_SIZE;
		float endDelayTime = (time * 0.9f + 0.05f) * BUFFER_SIZE;
		lastTime = time;
		for(int i = 0; i < length; i++)
		{
			float inLeft = left[i];
			float inRight = right[i];
			float delayedLeft, delayedRight;
			float delayTime = (startDelayTime * (length - i) + endDelayTime * i) / length;
			get(delayTime, delayedLeft, delayedRight);
			put(inLeft + feedback * delayedLeft, inRight + feedback * delayedRight);
			left[i] = wet * delayedLeft + inLeft;
			right[i] = wet * delayedRight + inRight;
		}		
	}

private:
	void clearBuffer() 
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			leftBuffer[i] = 0.0f;
		}

		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			rightBuffer[i] = 0.0f;
		}
	}

	void put(float l, float r)
	{
		leftBuffer[writePointer] = l;
		rightBuffer[writePointer] = r;
		writePointer = (writePointer + 1) % BUFFER_SIZE;
	}

	void get(float t, float &outR, float &outL)
	{
		t = writePointer - t + 2 * BUFFER_SIZE;
		int r1 = ((int)t) % BUFFER_SIZE;
		int r2 = ((int)t + 1) % BUFFER_SIZE;
		float f = t - (int)t;
		outL = leftBuffer[r1] * (1.0f - f) + leftBuffer[r2] * f;
		outR = rightBuffer[r1] * (1.0f - f) + rightBuffer[r2] * f;
	}

	static const int BUFFER_SIZE = 20480;
	int writePointer;
	float leftBuffer[BUFFER_SIZE];
	float rightBuffer[BUFFER_SIZE];
	float lastTime;
	bool activeLastFrame;
};