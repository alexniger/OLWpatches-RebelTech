

#include "WaveTableOsc.h"


// oscillator
#define baseFrequency (c2)  /* starting frequency of first table */  // c1 = 32.7 Hz



class WTThreeOscPatch : public Patch {
private:
  WaveTableOsc *osc1;
  WaveTableOsc *osc2;
  WaveTableOsc *osc3;
  WaveForm *wf;
  FloatParameter freqA;
  //FloatParameter multB;
  //FloatParameter multC;
  
public:
  WTThreeOscPatch() {																		
	  osc1 = new WaveTableOsc();																
	  osc2 = new WaveTableOsc();																
	  osc3 = new WaveTableOsc();
	  wf = new WaveForm();			
	  
	  wf->setOsc(osc1, baseFrequency);
	  wf->setOsc(osc2, baseFrequency);
	  wf->setOsc(osc3, baseFrequency);
	  
	  freqA = getFloatParameter("Frequency", baseFrequency, c6, c4, 0.967, 0.0, Patch::EXP);   // c3: 130.81  to c5: 523.25  to c8: 4186.01     OU     c6: 1046.5  to c9: 8372    
	  //multC = getIntParameter("SemiTone", 1, 12); //, 0.967, 0.0, Patch::LIN);
	  //amp = getFloatParameter("amplitude", 0.0, 1.0, 0.2, 0.967, 0.0, Patch::LIN);
	  
  }
  void processAudio(AudioBuffer &buffer) {
    //float freq = getParameterValue(PARAMETER_A)*getParameterValue(PARAMETER_A)*2000 + 20;
    //freqC=freqA*3/12;
    
    //debugMessage("freqA/multC", freqA, (float) multC);
    float C = getParameterValue(PARAMETER_C);
    float multC = pow(2.0 , (C * 2.094 - 1.047));  			// multC = pow(2.0 , ((C - (pow((C-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    
    //debugMessage("freqA/multC", freqA, (float) multC);
    osc1->setFrequency(freqA/sampleRate);
    osc2->setFrequency(multC*freqA/sampleRate);
    
    //osc2->setFrequency(freqA*3/12/sampleRate);
    
    
    float ampB = getParameterValue(PARAMETER_B);
    float ampD = getParameterValue(PARAMETER_D);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    FloatArray right = buffer.getSamples(RIGHT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput()) * ampB * 0.5;				//osc1->getOutput() + osc2->getOutput() + osc3->getOutput()
		right[n] = (osc2->getOutput()) * ampD * 0.5;	
		osc1->updatePhase();        
		osc2->updatePhase();        
		//osc3->updatePhase();        
    
  }
  }
};
