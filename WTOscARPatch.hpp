

#include "WaveTableOsc.h"
#include "ADSR.h"



// oscillator
#define baseFrequency (c1)  /* starting frequency of first table */  // c1 = 32.7 Hz


class WTOscARPatch : public Patch {

private:
  WaveTableOsc *osc1;
  WaveForm *wf;
  FloatParameter freqA;
  
public:
  WTOscARPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();	
	  wf->setOsc(osc1, baseFrequency);
	//freqA = getFloatParameter("Frequency", baseFrequency, c6, c3, 0.77, 0.0, Patch::EXP);
	  //TargRatio = getFloatParameter("TargetRation", 0.0001, 100, 0.0001, 0.97, 0.0, Patch::EXP);
	  registerParameter(PARAMETER_A, "Frequency");
  }  
  ADSR *env = new ADSR();
  
  void processAudio(AudioBuffer &buffer) {
	
	//float freq = getParameterValue(PARAMETER_A)*2000 + 20;
    float Atime = getParameterValue(PARAMETER_B)*2;
    float Dtime = 0.1;
    float Rtime = getParameterValue(PARAMETER_C)*2;
    float Slevel = 0.98;
    float TargRatio = exp(log(10)*(getParameterValue(PARAMETER_D) * 6 - 4));
    
    float note = getParameterValue(PARAMETER_A)*49 + 25;
    float freqA = exp2f((note-69)/12.0)*440.0;
    
	env->setAttackRate(Atime * sampleRate);  
	env->setDecayRate(Dtime * sampleRate);
	env->setReleaseRate(Rtime * sampleRate);
	env->setSustainLevel(Slevel);
	env->trig(isButtonPressed(PUSHBUTTON));
	env->setTargetRatioA(TargRatio);
	env->setTargetRatioDR(TargRatio);
	
    
    osc1->setFrequency(freqA/sampleRate);
	
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() ) * env->process() * 0.5 ;  	
		osc1->updatePhase();        
    
  }
  }
};

