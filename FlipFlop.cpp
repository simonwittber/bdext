
#include "FlipFlop.h"

using namespace plogue::biduleSDK;
using namespace acme;

FlipFlop::FlipFlop(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 1;
	_numAudioOuts = 1;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;

	_numParams = 1;

	_state = 0;
}

FlipFlop::~FlipFlop()
{
}

bool FlipFlop::init()
{
	return true;
}

void FlipFlop::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Trigger");
}

void FlipFlop::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("State");
}

void FlipFlop::getParametersInfos(ParameterInfo *pinfos)
{
	pinfos[0].id = 0;
	strcpy(pinfos[0].name, "State");
	pinfos[0].type = BOOLPARAM;
	pinfos[0].ctrlType = GUICTRL_CHECKBOX;
	pinfos[0].linkable = 1;
	pinfos[0].saveable = 1;
}

void FlipFlop::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void FlipFlop::parameterUpdate(long id)
{
	if (id == 0)
	{
		//        getParameterValue(0, (double)_state);
	}
}

void FlipFlop::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
					   Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{

	Sample *in0 = sampleIn[0];
	Sample *out0 = sampleOut[0];

	long sampleFrames = _dspInfo.bufferSize;

	while (--sampleFrames >= 0)
	{
		Sample inVal = (*in0++); //get value for sample and increment pointer

		if (inVal == 1.f)
			_state = _state == 0 ? 1 : 0;

		(*out0++) = _state; //set value for sample and increment pointer
	}
}
