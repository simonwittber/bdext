#ifndef TriggerSelector16_H
#define TriggerSelector16_H

#include <string>
#include "../common/BiduleSDK.h"

namespace acme
{
using namespace plogue::biduleSDK;
class TriggerSelector16 : public BidulePlugin
{

public:
	TriggerSelector16(BiduleHost *host);
	virtual ~TriggerSelector16();
	virtual bool init();
	virtual void getAudioInNames(std::vector<std::string> &vec);
	virtual void getAudioOutNames(std::vector<std::string> &vec);

	virtual void parameterUpdate(long id);
	virtual void getParametersInfos(ParameterInfo *pinfos);
	virtual void getParameterChoices(long id, std::vector<std::string> &vec);

	virtual void process(Sample **sampleIn, Sample **sampleOut, MIDIEvents *midiIn, MIDIEvents *midiOut, Frequency ***freqIn, Frequency ***freqOut, Magnitude ***magIn, Magnitude ***magOut, SyncInfo *syncIn, SyncInfo *syncOut);

protected:
	int _state;
};
}; // namespace acme

#endif
