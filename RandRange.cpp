
#include "RandRange.h"

using namespace plogue::biduleSDK;
using namespace acme;

uint32_t xor128(void)
{
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;
	uint32_t t;
	t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

RandRange::RandRange(BiduleHost *host) : BidulePlugin(host)
{
	_caps = 0;
	_numAudioIns = 1;
	_numAudioOuts = 1;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;

	_numParams = 2;

	_maxValue = 1.0;
	_minValue = -1.0;
	_value = 0;
}

RandRange::~RandRange()
{
}

bool RandRange::init()
{
	return true;
}

void RandRange::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Trigger");
}

void RandRange::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("Value");
}

void RandRange::getParametersInfos(ParameterInfo *pinfos)
{
	pinfos[0].id = 0;
	strcpy(pinfos[0].name, "Min Value");
	pinfos[0].type = DOUBLEPARAM;
	pinfos[0].ctrlType = GUICTRL_SLIDER;
	pinfos[0].linkable = 1;
	pinfos[0].saveable = 1;
	pinfos[0].paramInfo.pd.defaultValue = -1.0;
	pinfos[0].paramInfo.pd.minValue = -22050;
	pinfos[0].paramInfo.pd.maxValue = +22050;

	pinfos[1].id = 1;
	strcpy(pinfos[1].name, "Max Value");
	pinfos[1].type = DOUBLEPARAM;
	pinfos[1].ctrlType = GUICTRL_SLIDER;
	pinfos[1].linkable = 1;
	pinfos[1].saveable = 1;
	pinfos[1].paramInfo.pd.defaultValue = +1.0;
	pinfos[1].paramInfo.pd.minValue = -22050;
	pinfos[1].paramInfo.pd.maxValue = +22050;
}

void RandRange::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void RandRange::parameterUpdate(long id)
{
	if (id == 0)
		getParameterValue(0, _minValue);
	if (id == 1)
		getParameterValue(1, _maxValue);
}

void RandRange::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
						Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{

	Sample *in0 = sampleIn[0];
	Sample *out0 = sampleOut[0];

	long sampleFrames = _dspInfo.bufferSize;

	while (--sampleFrames >= 0)
	{
		Sample inVal = (*in0++);
		if (inVal == 1.f)
			_value = _minValue + (_maxValue - _minValue) * ((double)xor128() / UINT32_MAX);
		(*out0++) = _value;
	}
}
