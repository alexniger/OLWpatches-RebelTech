

#include "WaveTableOsc.h"

#include "message.h"
#include "Patch.h"
#include "ExtFIR.h"
#include "FirFilter.h"



class WaveFormExt {
	
	private:
	//WAVESHAPE_TYPE wavetype;
	float filtExt(float filtFreq, int len, int Order);
	
	FirFilter *extFIR = new FirFilter();
	
	ExtFIR *extFilter = new ExtFIR(3550);
	

	
	public:
	//WaveForm(WAVESHAPE_TYPE TRI_WAVE); //type);
	//~WaveForm();
	int makeWaveTableExt(FloatArray sample, WaveTableOsc *ext, float baseFrequency,int WTlen, int M);
	
	}; 
