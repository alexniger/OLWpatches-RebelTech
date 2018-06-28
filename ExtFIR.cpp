


#include "ExtFIR.h"

ExtFIR::ExtFIR(int M) {
	
    b = FloatArray::create(M+1);
    z = FloatArray::create(M+1);
    b.clear();
    z.clear();
    Fc = 0.50;
}

ExtFIR::ExtFIR(float Fc, int M) {
    setExtFIR(Fc, M);
    z = FloatArray::create(M);
    z.clear();
}

ExtFIR::~ExtFIR() {
}


void ExtFIR::setOrder(int M) {
    this->M = M;
    calcCoef();
}

void ExtFIR::setFc(float Fc) {
    this->Fc = Fc;
    calcCoef();
}

    
void ExtFIR::setExtFIR(float Fc, int M) {
    this->M = M;
    this->Fc = Fc;
}

FloatArray ExtFIR::calcCoef(void) {
    
	for( int n = 0; n < (M+1); n++ ) {
		if( n == (M/2) ) {
			b[n] = 2.0 * Fc;
		}
		else {
			b[n] = 2.0 * Fc * sin( 2.0 * M_PI * Fc * (float)(n - (M/2)) ) / (M_PI * (float)(n - (M/2)));
		}
	}

    return b;
}
