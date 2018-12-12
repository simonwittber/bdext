
#include "Progress.h"

using namespace plogue::biduleSDK;
using namespace acme;

Progress::Progress(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 1;
	_numAudioOuts = 16;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;
	_numParams = 1;
	_state = 0;
    _states = new double[16];
}

Progress::~Progress()
{
}

bool Progress::init()
{
	return true;
}

void Progress::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Selector");
}

void Progress::getAudioOutNames(std::vector<std::string> &vec)
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

void Progress::getParametersInfos(ParameterInfo *pinfos)
{
	pinfos[0].id = 0;
	strcpy(pinfos[0].name, "Period");
	pinfos[0].type = DOUBLEPARAM;
	pinfos[0].ctrlType = GUICTRL_SLIDER;
	pinfos[0].linkable = 1;
	pinfos[0].saveable = 1;
	pinfos[0].paramInfo.pd.defaultValue = 1;
	pinfos[0].paramInfo.pd.minValue = 0;
	pinfos[0].paramInfo.pd.maxValue = 60;
}

void Progress::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void Progress::parameterUpdate(long id)
{
	if (id == 0)
		getParameterValue(0, _period);
}

void Progress::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
					   Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{

	Sample *in0 = sampleIn[0];

	long sampleFrames = _dspInfo.bufferSize;
	double deltaTime = 1.0 / 44100.0;
	double step = deltaTime / _period;

	for (int sample = 0; sample < sampleFrames; sample++)
	{
		Sample selector = (*in0++);
		int t = (int)selector;
		for (int i = 0; i < _numAudioOuts; i++)
		{
			double s = _states[i];
			if (t == i)
				s += step;
			else
				s -= step;
			if (s < 0)
				s = 0;
			if (s > 1)
				s = 1;
            _states[i] = s;
			sampleOut[i][sample] = s;
		}
	}
}
