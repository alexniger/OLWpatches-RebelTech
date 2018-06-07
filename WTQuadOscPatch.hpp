#include "Patch.h"
using namespace std;


#include "WaveTableOsc.h"


// oscillator
//#define baseFrequency (1280)  /* starting frequency of first table */



class WTThreeOscPatch : public Patch {
private:
  WaveTableOsc *osc1;
  WaveTableOsc *osc2;
  WaveTableOsc *osc3;
  WaveTableOsc *osc4;
  WaveForm *wf;
  FloatParameter freqA;
  FloatParameter freqC;
  FloatParameter multB;
  FloatParameter multD
  
public:
  WTThreeOscPatch() {																		
	  osc1 = new WaveTableOsc();																
	  osc2 = new WaveTableOsc();															
	  osc3 = new WaveTableOsc();																
	  osc4 = new WaveTableOsc();
	  wf1 = new WaveForm();	
	  wf2 = new WaveForm();			
	  
	  wf1->setSawtoothOsc(osc1, baseFrequency);
	  wf1->setSawtoothOsc(osc2, baseFrequency);
	  wf2->setSawtoothOsc(osc3, baseFrequency);
	  wf2->setSawtoothOsc(osc4, baseFrequency);
	  
	  freqA = getFloatParameter("Frequency", baseFrequency, 18000, 523.25, 0.967, 0.0, Patch::EXP);   // c3: 130.81  to c5: 523.25  to c8: 4186.01     OU     c6: 1046.5  to c9: 8372    
	  
	  
  }
  void processAudio(AudioBuffer &buffer) {
    //float freq = getParameterValue(PARAMETER_A)*2000 + 20;
    
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
