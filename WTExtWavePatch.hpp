


#include "WaveFormExt.h"


//#include "00BigEndianSine.h"
#include "SquareLow.h"
//#include "00.h"


// oscillator

#define baseFrequency (20)  /* starting frequency of first table */  // c1 = 32.7 Hz



class WTExtWavePatch : public Patch {
private:
  WaveTableOsc *ext1;
  WaveFormExt *wfe;
  
  SmoothFloat freqA;
  SmoothFloat amp;
  FloatParameter Fc;
  FloatParameter Pac ;
public:
  WTExtWavePatch() {																		
	  ext1 = new WaveTableOsc();
	  wfe = new WaveFormExt();
	  int foobarlen = 256;
	  FloatArray sample = FloatArray::create(foobarlen);
	  sample.copyFrom(foobar[0], foobarlen);
	  int M = 3550; //1220;
	  int val = wfe->makeWaveTableExt(sample, ext1, baseFrequency, foobarlen, M);
	      //debugMessage("coupure", ext1->numWaveTables, val);
	  //freq = getFloatParameter("Frequency", baseFrequency, c5, c3, 0.97, 0.0, Patch::EXP);
	  registerParameter(PARAMETER_A, "Frequency");
	  registerParameter(PARAMETER_B, "Amp");
	  registerParameter(PARAMETER_C, "Filter");
	  registerParameter(PARAMETER_D, "Q");
    
  }
  void processAudio(AudioBuffer &buffer) {
    //float freq = getParameterValue(PARAMETER_A)*(20000-baseFrequency) + baseFrequency;
	//float C = getParameterValue(PARAMETER_C);
    //float multC = pow(2.0 , ((C - (pow((C-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    float note = getParameterValue(PARAMETER_A)*110 + 25;
    freqA = exp2f((note-69)/12.0)*440.0;
    ext1->setFrequency(freqA/sampleRate);
    
	//debugMessage("coupure", ext1->getOutput(), freqA);
    
    
    
    
    debugMessage("coupure", freqA, (float) 0.0);
    
    amp = getParameterValue(PARAMETER_B);
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (ext1->getOutput() * amp ) * 0.5;				
		//right[n] = (osc2->getOutput()) * ampD * 0.5;	
		ext1->updatePhase();      
    
	}
	}
};



