

#include "WaveTableOsc.h"


// oscillator
#define baseFrequency (c2)  /* starting frequency of first table */  // c1 = 32.7 Hz



class WT3NotesChordPatch : public Patch {
private:
  WaveTableOsc *osc1;
  WaveTableOsc *osc2;
  WaveTableOsc *osc3;
  WaveForm *wf;
  FloatParameter freqA;
  //FloatParameter multB;
  //FloatParameter multC;
  
public:
  WT3NotesChordPatch() {	
	  																	
	
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
    float B = getParameterValue(PARAMETER_B);
    float multB = pow(2.0 , (B * 2.094 - 1.047));  			
    float C = getParameterValue(PARAMETER_C);
    float multC = pow(2.0 , (C * 2.094 - 1.047));  			// multC = pow(2.0 , ((C - (pow((C-0.5)*7.0/25.0 , 2.0) - 0.07)) * 2.094 - 1.047));
    
    //debugMessage("freqA/multC", freqA, (float) multC);
    osc1->setFrequency(freqA/sampleRate);
    osc2->setFrequency(multB*freqA/sampleRate);
    osc3->setFrequency(multC*freqA/sampleRate);
    
    //osc2->setFrequency(freqA*3/12/sampleRate);
    
      
	float ampA = 0.0;
	float ampB = 0.0;
	float ampC = 0.0;
	int selection;
	float selectD = getParameterValue(PARAMETER_D) * 5.0;
	//float selectD = getFloatParameter("Select", 0.0, 5.0, 0.0, 0.967, 0.0, Patch::LIN);
	debugMessage ("selectD" , selectD, (float) selection);
    
	
	if (selectD >0.5 & selectD <=0.6) {
			selection = 2 ;
		}
		else if (selectD >0.6 & selectD <=1.7) {
			selection = 3 ;
		}
		else if (selectD >1.7 & selectD <=1.8) {
			selection = 4 ;
		}
		else if (selectD >1.8 & selectD <=2.95) {
			selection = 5 ;
		}
		else if (selectD >2.95 & selectD <=3.05) {
			selection = 6 ;
		}
		else if (selectD >3.05 & selectD <=4.15) {
			selection = 7 ; 
		}
		else if (selectD >4.15 & selectD <=4.25) {
			selection = 8 ;
		}
		else if (selectD >4.25 & selectD <=4.95) {
			selection = 9 ;
		}
		else if (selectD >4.95 & selectD <=5.0) {
			selection = 10 ;
		}
		else 	selection = 1 ;
		
	
    switch (selection) {
		case 1 :	
			ampA = selectD * 2.0;
			ampB = 0.0;
			ampC = 0.0;
			break;
		case 2 :	
			
			ampA = 1.0;
			ampB = 0.0;
			ampC = 0.0;
			break;
		case 3 :	
			ampA = 1.0;
			ampB = (selectD - 0.6) / 1.2;
			ampC = 0.0;
			break;
		case 4 :	
			ampA = 1.0;
			ampB = 1.0;
			ampC = 0.0;
			break;
		case 5 :	
			ampA = 1.0;
			ampB = 0.0;
			ampC = (selectD - 1.8) / 1.15;
			break;
		case 6 :	
			ampA = 1.0;
			ampB = 0.0;
			ampC = 1.0;
			break;
		case 7 :	
			ampA = 1.0;
			ampB = (selectD - 3.05) / 1.1;
			ampC = (selectD - 3.05) / 1.1 / 2.0;
			break;
		case 8 :	
			ampA = 1.0;
			ampB = 1.0;
			ampC = 0.5;
			break;
		case 9 :	
			ampA = 1.0;
			ampB = (selectD - 4.25) / 0.7;
			ampC = (selectD - 4.25) / 0.7;
			break;
		case 10 :	
			ampA = 1.0;
			ampB = 1.0;
			ampC = 1.0;
			break;
		default:
			ampA = 0;
			ampB = 0;
			ampC = 0;
			break;
	}
			
    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
    //FloatArray right = buffer.getSamples(RIGHT_CHANNEL);
    for(int n = 0; n<buffer.getSize(); n++){
		left[n] = (osc1->getOutput() * ampA + osc2->getOutput() * ampB + osc3->getOutput() * ampC) * 0.5;				//osc1->getOutput() + osc2->getOutput() + osc3->getOutput()
		//right[n] = (osc2->getOutput()) * 1 * 0.5;	
		osc1->updatePhase();        
		osc2->updatePhase();        
		osc3->updatePhase();        
    
  }
  }
};
