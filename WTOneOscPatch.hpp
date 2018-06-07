

using namespace std;



#include "WaveTableOsc.h"


// oscillator

//#define baseFrequency (20)  /* starting frequency of first table */




class WTOneOscPatch : public Patch {
private:
  WaveTableOsc *osc1;
  WaveForm *wf;
  FloatParameter freq;
public:
  WTOneOscPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();
	  wf->setSawtoothOsc(osc1, baseFrequency);
	  freq = getFloatParameter("Frequency", baseFrequency, 18000, 523.25, 0.97, 0.0, Patch::EXP);
  }
  void processAudio(AudioBuffer &buffer) {
    //float freq = getParameterValue(PARAMETER_A)*(20000-baseFrequency) + baseFrequency;
	//float C = getParameterValue(PARAMETER_C);
    //float multC = pow(2.0 , ((C - (pow((C-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    osc1->setFrequency(freq/sampleRate);
    
    debugMessage ("freq/samplerate", freq, (float) sampleRate);
    float amp = getParameterValue(PARAMETER_B);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput()*amp)  ;
		osc1->updatePhase();        
    
  }
  }
};



