#ifndef TriggerPattern_H
#define TriggerPattern_H

#include <string>
#include "../common/BiduleSDK.h"

namespace acme
{
using namespace plogue::biduleSDK;
class TriggerPattern : public BidulePlugin
{

public:
	TriggerPattern(BiduleHost *host);
	virtual ~TriggerPattern();
	virtual bool init();
	virtual void getAudioInNames(std::vector<std::string> &vec);
	virtual void getAudioOutNames(std::vector<std::string> &vec);

	virtual void parameterUpdate(long id);
	virtual void getParametersInfos(ParameterInfo *pinfos);
	virtual void getParameterChoices(long id, std::vector<std::string> &vec);

	virtual void process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut, Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut);

protected:
	int _lower, _length;
	int _index;
	int *_pattern;
	int _minOutBound, _maxOutBound;
};
}; // namespace acme

#endif
