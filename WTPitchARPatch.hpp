



#include "WaveTableOsc.h"
#include "ADSR.h"



// oscillator
#define baseFrequency (c2)  /* starting frequency of first table */  // c1 = 32.7 Hz

class WTPitchARPatch : public Patch {

private:
  WaveTableOsc *osc1;
  WaveForm *wf;
  FloatParameter freqA;
  
public:
  WTPitchARPatch() {																		
	  osc1 = new WaveTableOsc();
	  wf = new WaveForm();	
	  wf->setOsc(osc1, baseFrequency);
	  //freqA = getFloatParameter("Frequency", baseFrequency, c9, c4, 0.79, 0.0, Patch::EXP);
	  //TargRatio = getFloatParameter("TargetRation", 0.0001, 100, 0.0001, 0.97, 0.0, Patch::EXP);
	  registerParameter(PARAMETER_A, "Frequency");
  }  
  ADSR *envamp = new ADSR();
  ADSR *envpitch = new ADSR();
  
  void processAudio(AudioBuffer &buffer) {
	
	//float freq = getParameterValue(PARAMETER_A)*2000 + 20;
    float Atime = getParameterValue(PARAMETER_B);
    float Dtime = 0.07;
    float Rtime = getParameterValue(PARAMETER_C);
    float Slevel = 1.0;
    float TargRatio = 1.2; //exp(log(10)*(getParameterValue(PARAMETER_D) * 6 - 4));
    
    float note = getParameterValue(PARAMETER_A)*49 + 25;
    float freqA = exp2f((note-69)/12.0)*440.0;
    
	envpitch->setAttackRate(Atime * sampleRate);  
	envpitch->setDecayRate(Dtime * sampleRate);
	envpitch->setReleaseRate(Rtime * sampleRate);
	envpitch->setSustainLevel(Slevel);
	envpitch->trig(isButtonPressed(PUSHBUTTON));
	envpitch->setTargetRatioA(5);
	envpitch->setTargetRatioDR(0.8);
	
	envamp->setAttackRate(Atime * sampleRate);  
	envamp->setDecayRate(Dtime * sampleRate);
	envamp->setReleaseRate((Rtime + 0.25) * sampleRate);				// little more delay to hear the original frequency
	envamp->setSustainLevel(Slevel);
	envamp->trig(isButtonPressed(PUSHBUTTON));
	envamp->setTargetRatioA(5);
	envamp->setTargetRatioDR(0.6);
	
    //float freq = getParameterValue(PARAMETER_A)*getParameterValue(PARAMETER_A)*2000 + 20;
	
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = osc1->getOutput()  * envamp->process() * 0.5 ;  	    
		// left[n] = osc1->getOutput()  * envamp->process() * 0.5 ;
    float D = ((getParameterValue(PARAMETER_D) * 24.0 - 12.0) / 12.0 * 1.06);
    float pitchshift = pow(2.0 , D * envpitch->process()); 				//((D - (pow((D-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    osc1->setFrequency(freqA*pitchshift/sampleRate);
	osc1->updatePhase();        
    
  }
  }
};


