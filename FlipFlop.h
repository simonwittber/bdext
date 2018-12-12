#ifndef FLIPFLOP_H
#define FLIPFLOP_H

#include <string>
#include "../common/BiduleSDK.h"

namespace acme
{
using namespace plogue::biduleSDK;
class FlipFlop : public BidulePlugin
{

  public:
	FlipFlop(BiduleHost *host);
	virtual ~FlipFlop();
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
