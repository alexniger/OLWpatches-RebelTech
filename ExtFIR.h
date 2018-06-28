







#ifndef ExtFIR_h
#define ExtFIR_h

#include "Patch.h"
#include "FloatArray.h"

class ExtFIR {
public:
    ExtFIR(int M);
    ExtFIR(float Fc, int M);
    ~ExtFIR();
    void setFc(float Fc);
    void setOrder(int M);
    void setExtFIR(float Fc, int M);
    float process(float in);
    FloatArray calcCoef(void);
    
protected:
    //void calcCoef(void);

    FloatArray b;
    FloatArray z;
    //b = FloatArray::create(M);
    //z = FloatArray::create(M);
    //b.clear();
    //z.clear();
    float Fc;
    int M;
    int n;
};



inline float ExtFIR::process(float in) {
    float out = b[0] * in + z[0];
    for(n=1 ; n<(M+1) ; n++) {
		z[n-1] = in * b[n] + z[n];
	}
    return out;
}

#endif // ExtFIR_h
