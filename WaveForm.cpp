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
#include "WaveTableOsc.h"
#include "WaveForm.h"



//WaveForm::WaveForm(wavetype) {										// constr
	//WAVESHAPE_TYPE type;
	//wavetype = type;
//}


//WaveForm::~WaveForm(type) {										// destr
 
//}

// setSawtoothOsc

// make set of wavetables for sawtooth oscillator

void WaveForm::setOsc(WaveTableOsc *osc, float baseFreq) {    
    // calc number of harmonics where the highest harmonic baseFreq and lowest alias an octave higher would meet
    int maxHarms = sampleRate / (3.0 * baseFreq) + 0.5;					// + 0.5 pour round
    // round up to nearest power of two
    unsigned int v = maxHarms;
    v--;            // so we don't go up if already a power of 2
    v |= v >> 1;    // roll the highest bit into all lower bits...
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;            // and increment to power of 2
    int tableLen = v * 2 * overSamp;  // double for the sample rate, then oversampling
	
    myFloat ar[tableLen], ai[tableLen];   // for ifft

    double topFreq = baseFreq * 2.0 / sampleRate;
    myFloat scale = 0.0;
    for (; maxHarms >= 1; maxHarms >>= 1) {
        defineShape(tableLen, maxHarms, ar, ai);
        scale = makeWaveTable(osc, tableLen, ar, ai, scale, topFreq);
        topFreq *= 2;
        if (tableLen > constantRatioLimit) // variable table size (constant oversampling but with minimum table size)
            tableLen >>= 1;
    }
}


float WaveForm::makeWaveTable(WaveTableOsc *osc, int len, myFloat *ar, myFloat *ai, myFloat scale, double topFreq) {
    fft(len, ar, ai);
    
    if (scale == 0.0) {
        // calc normal
        myFloat max = 0;
        for (int idx = 0; idx < len; idx++) {
            myFloat temp = fabs(ai[idx]);
            if (max < temp)
                max = temp;
        }
        scale = 1.0 / max * .999;        
    }
    
    // normalize
    float wave[len];
    for (int idx = 0; idx < len; idx++)
        wave[idx] = ai[idx] * scale;
        
    if (osc->addWaveTable(len, wave, topFreq))
        scale = 0.0;
    
    return scale;
}

//
// defineSawtooth
//
// prepares sawtooth harmonics for ifft
//
void WaveForm::defineShape(int len, int numHarmonics, myFloat *ar, myFloat *ai) {
    if (numHarmonics > (len >> 1))
        numHarmonics = (len >> 1);
    
    // clear
    for (int idx = 0; idx < len; idx++) {
        ai[idx] = 0;
        ar[idx] = 0;
    }
    
    for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
			myFloat temp = idx & 0x01 ? 1.0 / idx : 0.0;            		// if ( idx & 0x01 ) 1.0 / idx else 0.0;
			ar[idx] = -temp;
			ar[jdx] = temp;
			}
			
    //switch ( wavetype ) {
		//case TRI_WAVE :
			//float sign = 1;
			//for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
			//myFloat temp = idx & 0x01 ? 1.0 / (idx * idx) * (sign = -sign) : 0.0;
			//ar[idx] = -temp;
			//ar[jdx] = temp;
			//}
			//break;
		//case SQUARE_WAVE :
			//for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
			//myFloat temp = idx & 0x01 ? 1.0 / idx : 0.0;            		// if ( idx & 0x01 ) 1.0 / idx else 0.0;
			//ar[idx] = -temp;
			//ar[jdx] = temp;
			//}
			//break;
		//case EXT_WAVE :
			//break;
		//default:      //sawtooth
			//for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
			//myFloat temp = -1.0 / idx;
			//ar[idx] = -temp;
			//ar[jdx] = temp;
			//}
			//break;
//}
}


//
// fft
//
// I grabbed (and slightly modified) this Rabiner & Gold translation...
//
// (could modify for real data, could use a template version, blah blah--just keeping it short)
//
void WaveForm::fft(int N, myFloat *ar, myFloat *ai)
/*
 in-place complex fft
 
 After Cooley, Lewis, and Welch; from Rabiner & Gold (1975)
 
 program adapted from FORTRAN 
 by K. Steiglitz  (ken@princeton.edu)
 Computer Science Dept. 
 Princeton University 08544          */
{    
    int i, j, k, L;            /* indexes */
    int M, TEMP, LE, LE1, ip;  /* M = log N */
    int NV2, NM1;
    myFloat t;               /* temp */
    myFloat Ur, Ui, Wr, Wi, Tr, Ti;
    myFloat Ur_old;
    
    // if ((N > 1) && !(N & (N - 1)))   // make sure we have a power of 2
    
    NV2 = N >> 1;
    NM1 = N - 1;
    TEMP = N; /* get M = log N */
    M = 0;
    while (TEMP >>= 1) ++M;
    
    /* shuffle */
    j = 1;
    for (i = 1; i <= NM1; i++) {
        if(i<j) {             /* swap a[i] and a[j] */
            t = ar[j-1];     
            ar[j-1] = ar[i-1];
            ar[i-1] = t;
            t = ai[j-1];
            ai[j-1] = ai[i-1];
            ai[i-1] = t;
        }
        
        k = NV2;             /* bit-reversed counter */
        while(k < j) {
            j -= k;
            k /= 2;
        }
        
        j += k;
    }
    
    LE = 1.;
    for (L = 1; L <= M; L++) {            // stage L
        LE1 = LE;                         // (LE1 = LE/2) 
        LE *= 2;                          // (LE = 2^L)
        Ur = 1.0;
        Ui = 0.; 
        Wr = cos(M_PI/(float)LE1);
        Wi = -sin(M_PI/(float)LE1); // Cooley, Lewis, and Welch have "+" here
        for (j = 1; j <= LE1; j++) {
            for (i = j; i <= N; i += LE) { // butterfly
                ip = i+LE1;
                Tr = ar[ip-1] * Ur - ai[ip-1] * Ui;
                Ti = ar[ip-1] * Ui + ai[ip-1] * Ur;
                ar[ip-1] = ar[i-1] - Tr;
                ai[ip-1] = ai[i-1] - Ti;
                ar[i-1]  = ar[i-1] + Tr;
                ai[i-1]  = ai[i-1] + Ti;
            }
            Ur_old = Ur;
            Ur = Ur_old * Wr - Ui * Wi;
            Ui = Ur_old * Wi + Ui * Wr;
        }
    }
}
