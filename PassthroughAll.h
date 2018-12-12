#ifndef PASSTHROUGHALL_H
#define PASSTHROUGHALL_H

#include <string>
#include "../common/BiduleSDK.h"

namespace acme {
    using namespace plogue::biduleSDK;
    class PassthroughAll: public BidulePlugin {

	    public:
		    PassthroughAll(BiduleHost* host);
			virtual ~PassthroughAll();
            virtual bool init();
			virtual void getAudioInNames(std::vector<std::string>& vec);
			virtual void getAudioOutNames(std::vector<std::string>& vec);
			virtual void getMIDIInNames(std::vector<std::string>& vec);
			virtual void getMIDIOutNames(std::vector<std::string>& vec);
			virtual void getFreqInNames(std::vector<std::string>& vec);
			virtual void getFreqOutNames(std::vector<std::string>& vec);
			virtual void getMagInNames(std::vector<std::string>& vec);
			virtual void getMagOutNames(std::vector<std::string>& vec);

            virtual void parameterUpdate(long id);
			virtual void getParametersInfos(ParameterInfo* pinfos);
			virtual void getParameterChoices(long id, std::vector<std::string>& vec);

			virtual void process(Sample** sampleIn, Sample** sampleOut, MIDIEvents* midiIn, MIDIEvents* midiOut, Frequency*** freqIn, Frequency*** freqOut, Magnitude*** magIn, Magnitude*** magOut, SyncInfo* syncIn, SyncInfo* syncOut);
		protected:
			double _dParamValue;
			AudioFile _af;
			bool _afConnected;
			unsigned long _dumbAFCounter;
    };
};

#endif
