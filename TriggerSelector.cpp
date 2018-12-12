
#include "TriggerSelector.h"

using namespace plogue::biduleSDK;
using namespace acme;

TriggerSelector::TriggerSelector(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 2;
	_numAudioOuts = 8;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;
	_numParams = 0;
	_state = 0;
}

TriggerSelector::~TriggerSelector()
{
}

bool TriggerSelector::init()
{
	return true;
}

void TriggerSelector::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Trigger");
	vec.push_back("Selector");
}

void TriggerSelector::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("T0");
	vec.push_back("T1");
	vec.push_back("T2");
	vec.push_back("T3");
	vec.push_back("T4");
	vec.push_back("T5");
	vec.push_back("T6");
	vec.push_back("T7");
	vec.push_back("T8");
}

void TriggerSelector::getParametersInfos(ParameterInfo *pinfos)
{
}

void TriggerSelector::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void TriggerSelector::parameterUpdate(long id)
{
}

void TriggerSelector::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
							  Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{

	Sample *in0 = sampleIn[0];
	Sample *in1 = sampleIn[1];

	long sampleFrames = _dspInfo.bufferSize;

	for (int sample = 0; sample < sampleFrames; sample++)
	{
		Sample trigger = (*in0++);
		Sample selector = (*in1++);
		int t = (int)selector;
		for (int i = 0; i < _numAudioOuts; i++)
		{
			sampleOut[i][sample] = i == t ? trigger : 0;
		}
	}
}
