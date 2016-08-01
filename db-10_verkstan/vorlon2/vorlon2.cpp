// This is the main DLL file.

#include "Vorlon2.h"
#include "synth.h"

namespace Vorlon2 {
	VorlonSynth::VorlonSynth()
	{
		synth = new Synth(0);
	}

	VorlonSynth::~VorlonSynth()
	{
		delete synth;
	}

	int VorlonSynth::PlayFrame()
	{
		return synth->playFrame();
	}

	void VorlonSynth::MidiInput(unsigned int input)
	{
		synth->midiInput(input);
	}

	int VorlonSynth::SampleRate::get() { return Synth::sampleRate; };

	int VorlonSynth::FrameSize::get() { return Synth::frameSize; };
}