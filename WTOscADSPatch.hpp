

#include "WaveTableOsc.h"
#include "ADSR.h"

// oscillator
#define baseFrequency (c1)  /* starting frequency of first table */  // c1 = 32.7 Hz


class WTOscADSPatch : public Patch {

private:
  WaveTableOsc *osc1;
  WaveForm *wf;
  
  FloatParameter freq;
  
public:
  WTOscADSPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();	
	  wf->setOsc(osc1, baseFrequency);
	  freq = getFloatParameter("Frequency", baseFrequency, c5, c3, 0.97, 0.0, Patch::EXP);
  }  
  ADSR *env = new ADSR();
  
  void processAudio(AudioBuffer &buffer) {
	
	//float freq = getParameterValue(PARAMETER_A)*2000 + 20;
    float Atime = getParameterValue(PARAMETER_B);
    float Dtime = getParameterValue(PARAMETER_C) +0.15;
    float Rtime = 0.0;
    float Slevel = getParameterValue(PARAMETER_D);
    
	env->setAttackRate(Atime * sampleRate); 
	env->setDecayRate(Dtime * sampleRate);
	env->setReleaseRate(Rtime * sampleRate);
	env->setSustainLevel(Slevel);
	env->gate(isButtonPressed(PUSHBUTTON));
	//env->gate(getParameterValue(PARAMETER_E));
    
    osc1->setFrequency(freq/sampleRate);
	
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() ) * env->process() * 0.5 ;  	    // process(osc.getNextSample())*env->process();
		osc1->updatePhase();        
    
  }
  }
};

