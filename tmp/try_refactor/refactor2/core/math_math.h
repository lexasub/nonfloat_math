#pragma once
#include <cstddef>
#include "types.h"
#include "list.h"
#include <iostream>
using namespace std;
class math_math
{
  public:
    bool sign = 0;//0 +, 1 -
    void* arg;
    type_arg _type = type_null;
     
    math_math():_type(type_null), arg(NULL), sign(0){};
    math_math(const int& c);
    math_math(const math_math& c);
    math_math(math_math& a, math_math& b, const type_arg __type);//a,b должны быть константами, но тогда тучу static_cast прийдется писать
    ~math_math();
    
    math_math* add(math_math& c);//if return pointer diff от указателя объекта над которым работали, то delete над которым работали
    math_math* c_add(math_math& c);//copy add
    math_math* sub(math_math& c);
    math_math* c_sub(math_math& c);
    math_math* mul(math_math& c);
    math_math* c_mul(math_math& c);
    math_math* div(math_math& c);
    math_math* c_div(math_math& c);
     
    void init(math_math& c);//when we want do op& _type == type_null
    void fork_childs();
    void print(ostream& os, const int cnt_tabes);
};
