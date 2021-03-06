//
//  WaveTableOsc.cpp
//
//  Created by Nigel Redmon on 5/15/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the wavetable oscillator and code,
//  read the series of articles by the author, starting here:
//  www.earlevel.com/main/2012/05/03/a-wavetable-oscillator—introduction/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your own purposes, free or commercial.
//

//#include "WaveTableOsc.h"


//WaveTableExt::WaveTableExt(void) {										// initialisation
    //phasor = 0.0;
    //phaseInc = 0.0;
    //phaseOfs = 0.5;
    //numWaveTables = 0;
    //for (int idx = 0; idx < numWaveTableSlots; idx++) {    				// numWaveTableSlots = maximum arbitraire (> vrai max)
        //waveTables[idx].topFreq = 0;
        //waveTables[idx].waveTableLen = 0;
        //waveTables[idx].waveTable = 0;
    //}
//}


//WaveTableExt::~WaveTableExt(void) {										
    //for (int idx = 0; idx < numWaveTableSlots; idx++) {
        //float *temp = waveTables[idx].waveTable;
        //if (temp != 0)
            //delete [] temp;
    //}
//}


////
//// addWaveTable
////
//// add wavetables in order of lowest frequency to highest
//// topFreq is the highest frequency supported by a wavetable
//// wavetables within an oscillator can be different lengths
////
//// returns 0 upon success, or the number of wavetables if no more room is available
////
//int WaveTableExt::addWaveTable(int len, float *waveTableIn, double topFreq) {
    //if (this->numWaveTables < numWaveTableSlots) {
        //float *waveTable = this->waveTables[this->numWaveTables].waveTable = new float[len];
        //this->waveTables[this->numWaveTables].waveTableLen = len;
        //this->waveTables[this->numWaveTables].topFreq = topFreq;
        //++this->numWaveTables;
        
        //// fill in wave
        //for (long idx = 0; idx < len; idx++)
            //waveTable[idx] = waveTableIn[idx];
        
        //return 0;
    //}
    //return this->numWaveTables;
//}


////
//// getOutput
////
//// returns the current oscillator output
////
//float WaveTableExt::getOutput() {
    //// grab the appropriate wavetable
    //int waveTableIdx = 0;
    
    //waveTable *waveTable = &this->waveTables[waveTableIdx];

//#if !doLinearInterp
    //// truncate
    //return waveTable->waveTable[int(this->phasor * waveTable->waveTableLen)];
//#else
    //// linear interpolation
    //double temp = this->phasor * waveTable->waveTableLen;
    //int intPart = temp;
    //double fracPart = temp - intPart;
    //float samp0 = waveTable->waveTable[intPart];
    //if (++intPart >= waveTable->waveTableLen)
        //intPart = 0;
    //float samp1 = waveTable->waveTable[intPart];
    
    //return samp0 + (samp1 - samp0) * fracPart;
//#endif
//}

