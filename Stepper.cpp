
#include "Stepper.h"

using namespace plogue::biduleSDK;
using namespace acme;

Stepper::Stepper(BiduleHost *host) : BidulePlugin(host)
{
	//fill in plugin capabilities as a mask
	//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
	_caps = 0;

	_numAudioIns = 4;
	_numAudioOuts = 1;
	_numMIDIIns = 0;
	_numMIDIOuts = 0;
	_numFreqIns = 0;
	_numFreqOuts = 0;
	_numMagIns = 0;
	_numMagOuts = 0;
	_numParams = 0;

	_position = 0;
}

Stepper::~Stepper()
{
}

bool Stepper::init()
{
	return true;
}

void Stepper::getAudioInNames(std::vector<std::string> &vec)
{
	vec.push_back("Forward");
	vec.push_back("Reverse");
	vec.push_back("Lower");
	vec.push_back("Upper");
}

void Stepper::getAudioOutNames(std::vector<std::string> &vec)
{
	vec.push_back("Step");
}

void Stepper::getParametersInfos(ParameterInfo *pinfos)
{
}

void Stepper::getParameterChoices(long id, std::vector<std::string> &vec)
{
}

void Stepper::parameterUpdate(long id)
{
}

void Stepper::process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut,
					  Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut)
{
	Sample *fwd = sampleIn[0];
	Sample *rev = sampleIn[1];
	Sample *lower = sampleIn[2];
	Sample *upper = sampleIn[3];

	Sample *out0 = sampleOut[0];

	long sampleFrames = _dspInfo.bufferSize;

	while (--sampleFrames >= 0)
	{
		Sample fwdVal = (*fwd++);
		Sample revVal = (*rev++);
		Sample lowerVal = (*lower++);
		Sample upperVal = (*upper++);

		if (fwdVal == 1.f)
		{
			_position = lowerVal;
			_direction = 1;
		}
		else if (revVal == 1.f)
		{
			_position = upperVal;
			_direction = -1;
		}
		else
		{
			_position += _direction;
		}

		if (_position < lowerVal)
			_position = lowerVal;
		if (_position >= upperVal)
			_position = upperVal - 1;

		(*out0++) = _position;
	}
}
