



#include "WaveTableOsc.h"
#include "WaveForm.h"


// oscillator

#define baseFrequency (c1)  /* starting frequency of first table */  // c1 = 32.7 Hz




class WTOneOscPatch : public Patch {
private:
  WaveTableOsc *osc1;
  WaveForm *wf;
  FloatParameter freqA;
public:
  WTOneOscPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();
	  wf->setOsc(osc1, baseFrequency);
	  //freq = getFloatParameter("Frequency", baseFrequency, c5, c3, 0.97, 0.0, Patch::EXP);
	  registerParameter(PARAMETER_A, "Frequency");
  }
  void processAudio(AudioBuffer &buffer) {
    //float freq = getParameterValue(PARAMETER_A)*(20000-baseFrequency) + baseFrequency;
	//float C = getParameterValue(PARAMETER_C);
    //float multC = pow(2.0 , ((C - (pow((C-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    float note = getParameterValue(PARAMETER_A)*49 + 25;
    float freqA = exp2f((note-69)/12.0)*440.0;
    osc1->setFrequency(freqA/sampleRate);
    
    float amp = getParameterValue(PARAMETER_B);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput()*amp)  ;
		osc1->updatePhase();        
    
	}
	}
};



