



#include "WaveTableOsc.h"





namespace NWAVESHAPE_TYPE
{
	typedef enum {
		SAW_WAVE, 
		TRI_WAVE, 
		SQUARE_WAVE, 
		EXT_WAVE
	} WAVESHAPE_TYPE;
}






class WaveForm {
	
	public:
	//WaveForm(WAVESHAPE_TYPE TRI_WAVE); //type);
	//~WaveForm();
	
	
	void setOsc(WaveTableOsc *osc, float baseFreq);	
	
	
	private:
	//WAVESHAPE_TYPE wavetype;
	void fft(int N, myFloat *ar, myFloat *ai);
	void defineShape(int len, int numHarmonics, myFloat *ar, myFloat *ai);
	float makeWaveTable(WaveTableOsc *osc, int len, myFloat *ar, myFloat *ai, myFloat scale, double topFreq);
	}; 
	
