#include "math.h"

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

math_something::deep_copy(void *arg, void *p)
{
  switch(type)
  {
    case t_fraction:
      ((math_fraction*)arg)->deep_copy(*((math_fraction*)arg), *((math_fraction*)p));//тут используются объекты потому что надо копировать числитель и знаменатель
    case t_sum:
      ((math_sum*)arg)->deep_copy((math_sum*)arg->args, (math_sum*)p->args);
    //..

  }

}

math_sum::math_sum()
{
  if(args = realloc(args, num_alloc * sizeof(math_something)))
    n_alloced = num_alloc;
  //иначе желательно выдавать ошибку
}

math_sum::math_sum(math_sum& sum):n(sum.n),n_alloced(sum.n_alloced)
{
  if(args = realloc(args, num_alloced * sizeof(math_something)))
  {
    memcpy(args, sum.args, n * sizeof(math_something));
    deep_copy(sum.args, args);
  }
  else
    num_alloced = 0;
    //желательно выдавать ошибку
}

math_sum::math_sum(math_something& arg):n(1)
{
  if(args = realloc(args, num_alloc * sizeof(math_something)))
  {
    num_alloced = num_alloc;
    memcpy(args, sum.args, sizeof(math_something));
    deep_copy(&arg, args);
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






