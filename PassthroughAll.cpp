
#include "PassthroughAll.h"

using namespace plogue::biduleSDK;
using namespace acme;

PassthroughAll::PassthroughAll(BiduleHost* host):
BidulePlugin(host){
	//fill in plugin capabilities as a mask
//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
    _caps = 0; 

	_numAudioIns=1;
	_numAudioOuts=3;
	_numMIDIIns=1;
	_numMIDIOuts=1;
	_numFreqIns=1;
	_numFreqOuts=1;
	_numMagIns=1;
	_numMagOuts=1;

	_numParams=3;

	_dParamValue = 0.0;
	_afConnected = false;
	_dumbAFCounter = 0;
}

PassthroughAll::~PassthroughAll(){
}

bool
PassthroughAll::init() {
    return true;
}

void 
PassthroughAll::getAudioInNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough audio in");
}

void 
PassthroughAll::getAudioOutNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough audio out");
	vec.push_back("Combien tu les vends tes crayons?"); //don't ask... it's a running gag here
	vec.push_back("audio file 1st channels");
}

void 
PassthroughAll::getMIDIInNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough MIDI in");
}

void 
PassthroughAll::getMIDIOutNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough MIDI out");
}

void 
PassthroughAll::getFreqInNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough frequency in");
}

void 
PassthroughAll::getFreqOutNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough frequency out");
}

void 
PassthroughAll::getMagInNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough magnitude in");
}

void 
PassthroughAll::getMagOutNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough magnitude out");
}

void 
PassthroughAll::getParametersInfos(ParameterInfo* pinfos) {

	pinfos[0].id = 0;
	strcpy(pinfos[0].name, "dummy parameter");
	pinfos[0].type = DOUBLEPARAM;
	pinfos[0].ctrlType = GUICTRL_SLIDER;
	pinfos[0].linkable = 1;
	pinfos[0].saveable = 1;
	pinfos[0].paramInfo.pd.defaultValue = 4.0;
	strcpy(pinfos[0].paramInfo.pd.units, "dollars");
	pinfos[0].paramInfo.pd.precision = 3;
	pinfos[0].paramInfo.pd.minValue = 1.0;
	pinfos[0].paramInfo.pd.maxValue = 10.0;
	pinfos[0].paramInfo.pd.scaling = SCALING_LINEAR;	

	pinfos[1].id = 1;
	strcpy(pinfos[1].name, "audiofile");
	pinfos[1].type = MEDIAPOOLPARAM;
	pinfos[1].ctrlType = GUICTRL_CHOICE;
	pinfos[1].linkable = 1;
	pinfos[1].saveable = 1;
	
	pinfos[2].id = 2;
	strcpy(pinfos[2].name, "add to mediapool");
	pinfos[2].type = STRINGPARAM;
	pinfos[2].ctrlType = GUICTRL_MEDIAPOOLSHORTCUT;
	pinfos[2].linkable = 0;
	pinfos[2].saveable = 0;
}

void 
PassthroughAll::getParameterChoices(long id, std::vector<std::string>& vec) {
}

void 
PassthroughAll::parameterUpdate(long id){
	if(id == 0)
		getParameterValue(0, _dParamValue);
	if(id == 1) {
		_afConnected = false;
		_dumbAFCounter = 0;
		std::string filename;
		getParameterValue(1, filename);
		getAudioFile(1, filename, &_af);
		if(_af.numChannels != 0)
			_afConnected = true;
	}
}

void 
PassthroughAll::process(Sample** sampleIn, Sample** sampleOut, MIDIEvents* midiIn, MIDIEvents* midiOut, Frequency*** freqIn, Frequency*** freqOut, 
						Magnitude*** magIn, Magnitude*** magOut, SyncInfo* syncIn, SyncInfo* syncOut){
	
	//VC6 has scope problems with for loop indices
	unsigned int i = 0;
	unsigned int j = 0;
	//1 - you'll always have _dspInfo.bufferSize samples to process
	//2 - you'll always have _dspInfo.fftOverlapPerBuffer overlap per mag/freq channels to process each having _dspInfo.fftWindowSizeHalf bins
	//3 - if you're not synced to anything, syncIn will be NULL
	//4 - midiIn events will always be sorted by bufTick
	//5 - midiOut events will be sorted afterwards so it's at your convenience to create them sorted or not.
	
	for(i = 0; i < _numAudioIns; ++i)
		memcpy(sampleOut[i], sampleIn[i], _dspInfo.bufferSize * sizeof(Sample));

	long sampleFrames = _dspInfo.bufferSize;
	float paramValf = (float)_dParamValue;
	Sample* s1 = sampleOut[1];
	while(--sampleFrames >= 0)
		(*s1++) = paramValf;
		
		
	Sample* s2 = sampleOut[2];
	if(!_afConnected)
		memset(s2, 0, _dspInfo.bufferSize * sizeof(Sample));
	else {
		sampleFrames = _dspInfo.bufferSize;
		while(--sampleFrames >= 0) {
			//dumb, dumb
			if(_dumbAFCounter >= _af.numSamples)
				_dumbAFCounter = 0;
			(*s2++) = _af.channels[0][_dumbAFCounter];
			_dumbAFCounter++;
		}
	}

	for(i = 0; i < _numMIDIIns; ++i) {
		midiOut[i].numEvents = midiIn[i].numEvents;
		for(j = 0; j < midiIn[i].numEvents; ++j) {
			midiOut[i].events[j].midiData[0] = midiIn[i].events[j].midiData[0];
			midiOut[i].events[j].midiData[1] = midiIn[i].events[j].midiData[1];
			midiOut[i].events[j].midiData[2] = midiIn[i].events[j].midiData[2];
			midiOut[i].events[j].midiData[3] = midiIn[i].events[j].midiData[3];
			midiOut[i].events[j].bufTick = midiIn[i].events[j].bufTick;
			midiOut[i].events[j].fdetune = midiIn[i].events[j].fdetune;
		}
	}

	for(i = 0; i < _numFreqIns; ++i)
		for(j = 0; j < (size_t)_dspInfo.fftOverlapPerBuffer; ++j)
			memcpy(freqOut[i][j], freqIn[i][j], _dspInfo.fftWindowSizeHalf * sizeof(Frequency));

	for(i = 0; i < _numMagIns; ++i)
		for(j = 0; j < (size_t)_dspInfo.fftOverlapPerBuffer; ++j)
			memcpy(magOut[i][j], magIn[i][j], _dspInfo.fftWindowSizeHalf * sizeof(Magnitude));

}

