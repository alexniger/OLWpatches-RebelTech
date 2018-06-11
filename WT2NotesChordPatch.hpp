


#include "WaveTableOsc.h"


// oscillator
   
#define baseFrequency (c2)  /* starting frequency of first table */  // 

class WT2NotesChordPatch : public Patch {
private:
  WaveTableOsc *osc1;
  WaveTableOsc *osc2;
  WaveForm *wf;
  FloatParameter freqA;
  //FloatParameter multC;
  
  //IntParameter multC;
public:
  WT2NotesChordPatch() {																		
	  osc1 = new WaveTableOsc();																
	  osc2 = new WaveTableOsc();
	  wf = new WaveForm();		
	  
	  
	  wf->setOsc(osc1, baseFrequency);
	  wf->setOsc(osc2, baseFrequency);
	  
	  //freqA = getFloatParameter("Frequency", baseFrequency, c6, c4, 0.967, 0.0, Patch::EXP);     
	  //multC = getIntParameter("SemiTone", 1, 12); //, 0.967, 0.0, Patch::LIN);
	  //amp = getFloatParameter("amplitude", 0.0, 1.0, 0.2, 0.967, 0.0, Patch::LIN);
	  registerParameter(PARAMETER_A, "Frequency");
	  
  }
  void processAudio(AudioBuffer &buffer) {
    //float freqA = getParameterValue(PARAMETER_A)*18000 + baseFrequency;
    
    float note = getParameterValue(PARAMETER_A)*49 + 25;
    float freqA = exp2f((note-69)/12.0)*440.0;
    
    float C = getParameterValue(PARAMETER_C);
    float multC = pow(2.0 , (C * 2.094 - 1.047));  			// multC = pow(2.0 , ((C - (pow((C-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    
    osc1->setFrequency(freqA/sampleRate);
    osc2->setFrequency(multC*freqA/sampleRate);
    
    
    
    float ampB = getParameterValue(PARAMETER_B);
    float ampD = getParameterValue(PARAMETER_D);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    FloatArray right = buffer.getSamples(RIGHT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() * ampB + osc2->getOutput() * ampD ) * 0.5;				
		//right[n] = (osc2->getOutput()) * ampD * 0.5;	
		osc1->updatePhase();        
		osc2->updatePhase();          
    
  }
  }
};
