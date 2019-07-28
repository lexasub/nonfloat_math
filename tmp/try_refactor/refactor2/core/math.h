#pragma once
#include "math_math.h"
#include <cmath>
#include "types.h"
#include <iostream>
using namespace std;
class math_math;
class math
{
  private:
    math_math* obj;
  public:
  math():obj(new math_math){};
  math(const math& arg);
  math(const math_math& arg);
  math(const int arg);
  ~math();
  
  bool operator <(int arg);
  bool operator >(int arg);
  bool operator ==(int arg);
  bool operator !=(int arg);
  bool operator <=(int arg);
  bool operator >=(int arg);

  math& operator +(int arg);
  math& operator -(int arg);
  math& operator *(int arg);
  math& operator /(int arg);
  math& operator %(int arg);//пока что забили на его реализацию//но он будет в ядре

  math& operator +=(int arg);
  math& operator -=(int arg);
  math& operator *=(int arg);
  math& operator /=(int arg);
  math& operator %=(int arg);

  math& operator =(int arg);
   
  math& operator >>(int arg);
  math& operator <<(int arg);
  math& operator <<=(int arg);
  math& operator >>=(int arg);
	
  bool operator <(math& arg);
  bool operator >(math& arg);
  bool operator ==(math& arg);
  bool operator !=(math& arg);
  bool operator <=(math& arg);
  bool operator >=(math& arg);

  math& operator +(math& arg);
  math& operator -(math& arg);
  math& operator *(math& arg);
  math& operator /(math& arg);
  math& operator %(math& arg);

  math& operator +=(math& arg);
  math& operator -=(math& arg);
  math& operator *=(math& arg);
  math& operator /=(math& arg);
  math& operator %=(math& arg);

  math& operator =(math& arg);
   
  math& operator >>(math& arg);
  math& operator <<(math& arg);
  math& operator <<=(math& arg);
  math& operator >>=(math& arg);
	
  math& operator ++();//++A
  math& operator --();
  math& operator ++(int k);//k - unusable//A++
  math& operator --(int k);

  math& simpy();
  math& build();
  float eval();

  friend ostream& operator <<(ostream& os, math& m);
};
