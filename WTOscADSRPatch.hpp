

#include "WaveTableOsc.h"
#include "WaveForm.h"
#include "ADSR.h"


// oscillator
#define baseFrequency (c1)  /* starting frequency of first table */  // c1 = 32.7 Hz


class WTOscADSRPatch : public Patch {
private:
  WaveTableOsc *osc1;
  
  WaveForm *wf;
  FloatParameter freqA;
public:
  WTOscADSRPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();	
	  wf->setOsc(osc1, baseFrequency);
	  //freq = getFloatParameter("Frequency", baseFrequency, c6, c3, 0.8, 0.0, Patch::EXP);
	  registerParameter(PARAMETER_A, "Frequency");
  }
  ADSR *env = new ADSR();
  void processAudio(AudioBuffer &buffer) {
    //float freqA = getParameterValue(PARAMETER_A)*getParameterValue(PARAMETER_A)*2000 + 20;
    float Atime = getParameterValue(PARAMETER_B);
    float Dtime = getParameterValue(PARAMETER_C) * 2.0;
    float Rtime = getParameterValue(PARAMETER_D) * 3.0;
    float note = getParameterValue(PARAMETER_A)*49 + 25;
    float freqA = exp2f((note-69)/12.0)*440.0;
    
    env->setAttackRate(Atime * sampleRate);  
	env->setDecayRate(Dtime * sampleRate);
	env->setReleaseRate(Rtime * sampleRate);
	env->setSustainLevel(0.7);
	env->gate(isButtonPressed(PUSHBUTTON));
	//env->gate(getParameterValue(PARAMETER_E));
	int teststate = env->getState();
    osc1->setFrequency(freqA/sampleRate);
    
    debugMessage("state", teststate, teststate);
    float amp = getParameterValue(PARAMETER_B);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() ) * env->process();
		osc1->updatePhase();        
    
  }
  }
};
