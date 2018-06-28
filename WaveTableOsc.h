//
//  WaveTableOsc.h
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



#include "message.h"
#include "Patch.h"




#define double float			// float needed with Owl processor

#ifndef Test_WaveTableOsc_h
#define Test_WaveTableOsc_h


//#define c1 (32.7) , c4 (261) 

#define sampleRate (48000)

#define constantRatioLimit (130)    /* set to a large number (greater than or equal to the length of the lowest octave table) for constant table size; set to 0 for a constant oversampling ratio (each higher ocatave table length reduced by half); set somewhere between (64, for instance) for constant oversampling but with a minimum limit */

#define overSamp (2)        /* oversampling factor (positive integer) */

#define doLinearInterp 1

#define myFloat float      /* float or double, to set the resolution of the FFT, etc. (the resulting wavetables are always float) */

typedef struct {
    double topFreq;
    int waveTableLen;
    float *waveTable;
} waveTable;

const int numWaveTableSlots = 32;										// 32 si jamais on veut des tiers d'octave (3*10=30)

const float c10 = 16744.03, c9 = c10/2.0, c8 = c9/2.0, c7 = c8/2.0, c6 = c7/2.0, c5 = c6/2.0, c4 = c5/2.0, c3 = c4/2.0, c2 = c3/2.0, c1 = c2/2.0 ;



class WaveTableOsc {
protected:
    double phasor;      // phase accumulator
    double phaseInc;    // phase increment
    double phaseOfs;    // phase offset for PWM
    
    // list of wavetables
public:
    int numWaveTables;
    waveTable waveTables[numWaveTableSlots];
    
public:
    WaveTableOsc(void);
    ~WaveTableOsc(void);
    void setFrequency(double inc);
    void setPhaseOffset(double offset);
    void updatePhase(void);
    float getOutput(void);
    float getOutputMinusOffset(void);
    int addWaveTable(int len, float *waveTableIn, float topFreq);
};


// note: if you don't keep this in the range of 0-1, you'll need to make changes elsewhere
inline void WaveTableOsc::setFrequency(double inc) {
    phaseInc = inc;
}



// note: if you don't keep this in the range of 0-1, you'll need to make changes elsewhere
inline void WaveTableOsc::setPhaseOffset(double offset) {
    phaseOfs = offset;
}



inline void WaveTableOsc::updatePhase() {
    phasor += phaseInc;
    
    if (phasor >= 1.0)
        phasor -= 1.0;													// on conserve le décalage
}



#endif
