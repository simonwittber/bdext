
#include "TriggerSelector16.h"

using namespace plogue::biduleSDK;
using namespace acme;

TriggerSelector16::TriggerSelector16(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 2;
	_numAudioOuts = 16;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;
	_numParams = 0;
	_state = 0;
}

TriggerSelector16::~TriggerSelector16()
{
}

bool TriggerSelector16::init()
{
	return true;
}

void TriggerSelector16::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Trigger");
	vec.push_back("Selector");
}

void TriggerSelector16::getAudioOutNames(std::vector<std::string> &vec)
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
	vec.push_back("T9");
	vec.push_back("TA");
	vec.push_back("TB");
	vec.push_back("TC");
	vec.push_back("TD");
	vec.push_back("TE");
	vec.push_back("TF");
}

void TriggerSelector16::getParametersInfos(ParameterInfo *pinfos)
{
}

void TriggerSelector16::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void TriggerSelector16::parameterUpdate(long id)
{
}

void TriggerSelector16::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
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
