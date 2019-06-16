#include "math.h"
#include <cstring>
math_something::math_something():some(NULL),arg_type(t_null){}

math_something::math_something(void *arg, t_arg type)
{
  int sz = size_type(type);
  if(some = realloc(some, sz))//вдруг конструктор принудетельно вызван
    memcpy(some, arg, sz);//скопировали
  //иначе желательно выдавать ошибку
}

int math_something::size_type(t_arg type)
{
  switch(type)
  {
    case t_null:
      return 0;
    case t_fraction:
      return sizeof(math_fraction);
    case t_sum:
      return sizeof(math_sum);
  }
  return 0;
}

void math_something::deep_copy(void *arg, void *p)
{
  switch(arg_type)
  {
    case t_fraction:
      ((math_fraction*)arg)->deep_copy(*((math_fraction*)arg), *((math_fraction*)p));//тут используются объекты потому что надо копировать числитель и знаменатель
      break;
    case t_sum:
      ((math_sum*)arg)->deep_copy(((math_sum*)arg)->args, ((math_sum*)p)->args);
      break;
    //..

  }

}

void math_something::ch_sign()
{
  sign = !sign;
}

math_sum::math_sum()
{
  if(args = (math_something*)realloc(args, num_alloc * sizeof(math_something)))
    n_alloced = num_alloc;
  //иначе желательно выдавать ошибку
}

math_sum::math_sum(math_sum& sum):n(sum.n),n_alloced(sum.n_alloced)
{
  if(args = (math_something*)realloc(args, n_alloced * sizeof(math_something)))
  {
    memcpy(args, sum.args, n * sizeof(math_something));
    deep_copy(sum.args, args);
  }
  else
    n_alloced = 0;
    //желательно выдавать ошибку
}

math_sum::math_sum(math_something* arg):n(1)
{
  if(args = (math_something*)realloc(args, num_alloc * sizeof(math_something)))
  {
    n_alloced = num_alloc;
    memcpy(args, arg, sizeof(math_something));
    deep_copy(arg, args);
  }
  //желательно выдавать ошибку
}

void math_sum::deep_copy(math_something* _args, math_something *p)
{
 for(int i = 0; i<n; i++)
 {
  if(p[i].some = realloc(p[i].some, _args[i].size_type(_args[i].arg_type)))
  {
    memcpy(p[i].some, _args[i].some, _args[i].size_type(_args[i].arg_type));
    _args[i].deep_copy(_args[i].some, p[i].some);
  }
  //желательно выдавать ошибку
 }
}

math_sum& math_sum::add(math_something& arg)
{
  if(n>=n_alloced)
  {
    if(args = (math_something*)realloc(args, (n_alloced + num_alloc) * sizeof(math_something)))
      n_alloced += num_alloc;
    else return *this;
  }
    //лучше ошибку выдавать
  
  if(args[n].some = realloc(args[n].some, arg.size_type(arg.arg_type)))
  {
    memcpy(args[n].some, arg.some, arg.size_type(arg.arg_type));
    args[n].deep_copy(arg.some, args[n].some);
    n++;
  }
  //желательно выдавать ошибку
  return *this;
}

math_sum& math_sum::sub(math_something& arg)
{
  add(arg);
  args[n-1].ch_sign();
  return *this;
}

math_fraction::math_fraction()
{
  if(num = (math_something*)realloc(num, num_alloc * sizeof(math_something)))
  {
    n_n_alloced = num_alloc;
    if(div = (math_something*)realloc(div, num_alloc * sizeof(math_something)))
      n_d_alloced = num_alloc;
  }
  //иначе желательно выдавать ошибку
}

math_fraction::math_fraction(math_fraction& fract)
{
  if(num = (math_something*)realloc(num, fract.n_n_alloced * sizeof(math_something)))
  {
    n_n_alloced = fract.n_n_alloced;
    n_n = fract.n_d;
    memcpy(num, fract.num, n_n_alloced * sizeof(math_something));
    deep_copy();//!!
    if(div = (math_something*)realloc(div, fract.n_d_alloced * sizeof(math_something)))
    {
      n_d_alloced = fract.n_d_alloced;
      n_d = fract.n_d;
      memcpy(div, fract.div, n_d_alloced * sizeof(math_something));
      deep_copy();//!!
    }
  }
  //желательно выдавать ошибку
}

math_fraction::math_fraction(math_something *num, math_something *div, int n_n, int n_d)
{




}
