#include "Patch.h"
using namespace std;


#include "WaveTableOsc.h"
#include "ADSR.h"
//
// some things to tweak for testing and experimenting
//

// oscillator
//#define baseFrequency (20)  /* starting frequency of first table */


class WTOscADSRPatch : public Patch {
private:
  WaveTableOsc *osc1;
  
  WaveForm *wf;
  FloatParameter freq;
public:
  WTOscADSRPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();	
	  wf->setSawtoothOsc(osc1, baseFrequency);
	  freq = getFloatParameter("Frequency", baseFrequency, 18000, 523.25, 0.97, 0.0, Patch::EXP);
  }
  ADSR *env = new ADSR();
  void processAudio(AudioBuffer &buffer) {
    //float freq = getParameterValue(PARAMETER_A)*getParameterValue(PARAMETER_A)*2000 + 20;
    float Atime = getParameterValue(PARAMETER_B);
    float Dtime = getParameterValue(PARAMETER_C);
    float Rtime = getParameterValue(PARAMETER_D);
    
    env->setAttackRate(Atime * sampleRate);  
	env->setDecayRate(Dtime * sampleRate);
	env->setReleaseRate(Rtime * sampleRate);
	env->setSustainLevel(0.09);
	env->gate(isButtonPressed(PUSHBUTTON));
	
    osc1->setFrequency(freq/sampleRate);
    
    debugMessage("freq/phase inc", freq, freq/sampleRate);
    float amp = getParameterValue(PARAMETER_B);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() ) * env->process();
		osc1->updatePhase();        
    
  }
  }
};
