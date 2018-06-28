//——————————————————————————
// The MIT License (MIT)
//
// Copyright (c) 2015 Benjamin Sherlock
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//——————————————————————————
//
// FilterFactory.h
//
//——————————————————————————
//
// Matlab fir1 function is a "Window-based FIR filter design" tool.
// Windowed-Sinc Filters
//
// http://www.labbookpages.co.uk/audio/firWindowing.html
// https://en.wikipedia.org/wiki/Window_function#Hamming_window
//
//——————————————————————————

#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

// Includes
#include "config.h"

#include <vector>
//#include

//! Window Type enum container
struct FilterWindowType {
typedef enum {
RECTANGULAR = 0,
BARTLETT,
HANNING,
HAMMING,
BLACKMAN } Type;
};

//! Filter Type enum container
struct FilterType
{
typedef enum
{
LOWPASS = 0,
HIGHPASS,
BANDPASS,
BANDSTOP,
ALLPASS } Type;
};

//! Filter Properites Holder struct
struct FilterHolderType {
int order;
std::vector<Float> coefficients;
};

//! Filter Factory class
class FilterFactory
{
public:
//! Constructor
FilterFactory();

//! Destructor
virtual ~FilterFactory() {}

//! Create Filter
FilterHolderType createFilter(int order, FilterWindowType::Type windowType, FilterType::Type filterType, Float Fs = 0, Float Fc1 = 0, Float Fc2 = 0);

//! Create Window Weights
std::vector<Float> createWindowWeights(int order, FilterWindowType::Type windowType);

//! Create Sinc Weights
std::vector<Float> createSincWeights(int order, FilterType::Type filterType, Float Fs = 0, Float Fc1 = 0, Float Fc2 = 0);

//! Create Filter Weights – Combines Sinc and Window Weights
std::vector<Float> createFilterWeights(int order, FilterWindowType::Type windowType, FilterType::Type filterType, Float Fs = 0, Float Fc1 = 0, Float Fc2 = 0);

protected:

private:

};

#endif // FILTERFACTORY_H

