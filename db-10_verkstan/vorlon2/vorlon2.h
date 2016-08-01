// Vorlon2.h
#pragma once

class Synth;

//#include "oscillator.h"

namespace Vorlon2 {

	public ref class VorlonSynth
	{
	public:
		VorlonSynth();

		~VorlonSynth();

		int PlayFrame();

		void MidiInput(unsigned int input);

		property int SampleRate { int get(); }

		property int FrameSize { int get(); }

	private:
		Synth *synth;
	};
}
