
#include "Valve.h"

using namespace plogue::biduleSDK;
using namespace acme;

Valve::Valve(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 2;
	_numAudioOuts = 2;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;

	_numParams = 1;

	_state = 0;
}

Valve::~Valve()
{
}

bool Valve::init()
{
	return true;
}

void Valve::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Signal");
	vec.push_back("Trigger");
}

void Valve::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("Signal Accept");
	vec.push_back("Signal Reject");
}

void Valve::getParametersInfos(ParameterInfo *pinfos)
{
	pinfos[0].id = 0;
	strcpy(pinfos[0].name, "State");
	pinfos[0].type = BOOLPARAM;
	pinfos[0].ctrlType = GUICTRL_CHECKBOX;
	pinfos[0].linkable = 1;
	pinfos[0].saveable = 1;
}

void Valve::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void Valve::parameterUpdate(long id)
{
	if (id == 0)
	{
		//        getParameterValue(0, (double)_state);
	}
}

void Valve::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
					Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{

	Sample *in0 = sampleIn[0];
	Sample *in1 = sampleIn[1];
	Sample *out0 = sampleOut[0];
	Sample *out1 = sampleOut[1];

	long sampleFrames = _dspInfo.bufferSize;

	while (--sampleFrames >= 0)
	{
		Sample inVal = (*in0++);
		Sample gateVal = (*in1++);
		if (gateVal == 1.f)
			_state = _state == 0 ? 1 : 0;

		(*out0++) = _state ? inVal : 0; //set value for sample and increment pointer
		(*out1++) = _state ? 0 : inVal; //set value for sample and increment pointer
	}
}
