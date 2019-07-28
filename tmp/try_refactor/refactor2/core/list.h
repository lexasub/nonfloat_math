#pragma once
#include "math_math.h"
#include <iostream>
using namespace std;
class math_math;
class list
{
  private:
    list *prev, *next;
  public:
    list();
    list(const math_math& c);
    list(math_math& a, math_math& b);
    list(list* c);
    list(const list& c);
    ~list();

    math_math* arg;
    math_math* last();
    void ch_last(math_math& c);
    math_math* first();
    void ch_first(math_math& c);
    void push(const math_math& c);
    void push(list* c, const bool _sign);
    void fork_childs();
    void print(ostream& os, const int cnt_tabes);
};
