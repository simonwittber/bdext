
#include "Latch.h"

using namespace plogue::biduleSDK;
using namespace acme;

Latch::Latch(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 1;
	_numAudioOuts = 2;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;

	_numParams = 0;

	_lastValue = 0;
}

Latch::~Latch()
{
}

bool Latch::init()
{
	return true;
}

void Latch::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Signal");
}

void Latch::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("Trigger On Rise");
	vec.push_back("Trigger On Fall");
}

void Latch::getParametersInfos(ParameterInfo *pinfos)
{
}

void Latch::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void Latch::parameterUpdate(long id)
{
}

void Latch::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
					Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{
	Sample *in0 = sampleIn[0];
	Sample *out0 = sampleOut[0];
	Sample *out1 = sampleOut[1];

	long sampleFrames = _dspInfo.bufferSize;

	while (--sampleFrames >= 0)
	{
		Sample inVal = (*in0++);
		float rise = 0;
		float fall = 0;
		if (_lastValue <= 0 && inVal > 0)
			rise = 1;
		if (_lastValue > 0 && inVal <= 0)
			fall = 1;
		_lastValue = inVal;
		(*out0++) = rise;
		(*out1++) = fall;
	}
}
