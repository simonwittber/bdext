
#include "Register.h"

using namespace plogue::biduleSDK;
using namespace acme;

Register::Register(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 3;
	_numAudioOuts = 1;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;
	_numParams = 0;

	_value = 0;
}

Register::~Register()
{
}

bool Register::init()
{
	return true;
}

void Register::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Forward");
	vec.push_back("Reverse");
	vec.push_back("Reset");
}

void Register::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("Value");
}

void Register::getParametersInfos(ParameterInfo *pinfos)
{
}

void Register::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void Register::parameterUpdate(long id)
{
}

void Register::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
					   Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{
	Sample *fwd = sampleIn[0];
	Sample *rev = sampleIn[1];
	Sample *reset = sampleIn[2];

	Sample *out0 = sampleOut[0];

	long sampleFrames = _dspInfo.bufferSize;

	while (--sampleFrames >= 0)
	{
		Sample fwdVal = (*fwd++);
		Sample revVal = (*rev++);
		Sample resetVal = (*reset++);

		if (fwdVal == 1.f)
			_value += 1;

		if (revVal == 1.f)
			_value -= 1;

		(*out0++) = _value;
	}
	updateDisplayName(std::to_string(_value));
}
