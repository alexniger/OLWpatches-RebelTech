#include "Patch.h"
//#include "SineOscillator.h"
//#include <ctime>
//#include <iostream>
using namespace std;

//#include <math.h>

#include "WaveTableOsc.h"
#include "ADSR.h"



// oscillator
//#define baseFrequency (20)  /* starting frequency of first table */


class WTOscARPatch : public Patch {

private:
  WaveTableOsc *osc1;
  WaveForm *wf;
  FloatParameter freq;
  
public:
  WTOscARPatch() {																		//constructor
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();	
	  wf->setSawtoothOsc(osc1, baseFrequency);
	  freq = getFloatParameter("Frequency", baseFrequency, 20000, 440, 0.97, 0.0, Patch::EXP);
	  //TargRatio = getFloatParameter("TargetRation", 0.0001, 100, 0.0001, 0.97, 0.0, Patch::EXP);
  }  
  ADSR *env = new ADSR();
  
  void processAudio(AudioBuffer &buffer) {
	
	//float freq = getParameterValue(PARAMETER_A)*2000 + 20;
    float Atime = getParameterValue(PARAMETER_B);
    float Dtime = 0.14;
    float Rtime = getParameterValue(PARAMETER_C)*2;
    float Slevel = 1.0;
    float TargRatio = exp(log(10)*(getParameterValue(PARAMETER_D) * 6 - 4));
    //float ADRtime = Atime + Dtime + Rtime; //ou utilisation de getState.
    
	env->setAttackRate(Atime * sampleRate);  // .1 second
	env->setDecayRate(Dtime * sampleRate);
	env->setReleaseRate(Rtime * sampleRate);
	env->setSustainLevel(Slevel);
	env->trig(isButtonPressed(PUSHBUTTON));
	env->setTargetRatioA(TargRatio);
	env->setTargetRatioDR(TargRatio);
	
	//if (isButtonPressed(PUSHBUTTON)==1) {
		//do {
			//env->gate(1);
		//}
		//while (env->getState() != 0);
	//}
	//else env->gate(0);
    
    //float freq = getParameterValue(PARAMETER_A)*getParameterValue(PARAMETER_A)*2000 + 20;
    
    osc1->setFrequency(freq/sampleRate);
	
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() ) * env->process() * 0.5 ;  	    // process(osc.getNextSample())*env->process();
		osc1->updatePhase();        
    
  }
  }
};

