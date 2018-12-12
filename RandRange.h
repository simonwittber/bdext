#ifndef RandRange_H
#define RandRange_H

#include <string>
#include "../common/BiduleSDK.h"

namespace acme
{
using namespace plogue::biduleSDK;
class RandRange : public BidulePlugin
{

public:
	RandRange(BiduleHost *host);
	virtual ~RandRange();
	virtual bool init();
	virtual void getAudioInNames(std::vector<std::string> &vec);
	virtual void getAudioOutNames(std::vector<std::string> &vec);

	virtual void parameterUpdate(long id);
	virtual void getParametersInfos(ParameterInfo *pinfos);
	virtual void getParameterChoices(long id, std::vector<std::string> &vec);

	virtual void process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut, Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut);

protected:
	double _maxValue;
	double _minValue;
	double _value;
};
}; // namespace acme

#endif
