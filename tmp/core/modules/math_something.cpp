math_something::math_something():some(NULL),arg_type(t_null){}

math_something::math_something(math_something& arg)
{
  sign = arg.sign;
  some = arg.some;
  arg_type = arg.arg_type;
  fork_childs();
}

math_something::math_something(int& arg)
{
  add_int(arg);
}
math_something::math_something(void *arg, t_arg type, bool _sign = 0)
{
  sign = _sign; 
  some = arg;
  arg_type = type;
  fork_childs();
}

math_something::~math_something()
{
  child_destructor();
  free(some);
}

void math_something::child_destructor()
{
  switch(arg_type)
  {
    case t_fraction:
      ((math_fraction*)some)->~math_fraction;
      return;
    case t_sum: 
      ((math_sum*)some)->~math_sum;
      return;
    case t_mul:
      ((math_mul*)some)->~math_mul;
      return;
  }
}

void math_something::fork_childs()
{
  void *tmp = some;
  int sz = size_type();
  if(some = malloc(sz))
  {
    memcpy(some, tmp, sz);
    switch(arg_type)
    {
      case t_fraction:
        ((math_fraction*)some)->fork_childs();
        return;
      case t_sum:
        ((math_sum*)some)->fork_childs();
        return;
      case t_mul:
        ((math_mul*)some)->fork_childs();
        return;
      case t_int:
        int *tmp = some;
        some = malloc(sizeof(int);
        *some = *tmp;
        return;
    }
  }
}

int math_something::size_type(t_arg type)
{
  switch(type)
  {
    case t_null:
      return 0;
    case t_sum:
      return sizeof(math_sum);
    case t_mul:
      return sizeof(math_mul);
    case t_fraction:
      return sizeof(math_fraction);
    case t_int:
      return sizeof(int);
  }
}

int math_something::size_type()
{
  size_type(arg_type);
}

void math_something::ch_sign()
{
  sign = !sign;
}

void math_something::add_int(int& arg)
{
  some = malloc(sizeof(int));
  arg_type = t_int;
  *some = arg;
}

void math_something::add_sum(math_something& a, math_something& b)
{
  some = new math_sum(a);
  arg_type = t_sum;
  ((math_sum*)some)->add(b);
}

void math_something::add_sub(math_something& a, math_something& b)
{
  some = new math_sum(a);
  arg_type = t_sum;
  ((math_sum*)some)->sub(b);
}

void math_something::add_mul(math_something& a, math_something& b)
{
  some = new math_mul(a);
  arg_type = t_mul;
  ((math_mul*)some)->mul(b);
}

void math_something::add_div(math_something& a, math_something& b)
{
  some = new math_fraction(a, b);//просто их(num,div) можно через конструктор вставить
  arg_type = t_fraction;
}

void math_something::add_shift(math_something& a, math_something& b, bool direction=0)//0 <<, 1 >>
{

}

void math_something::push_sum(math_something& arg)
{
  if(arg_type == t_sum)
  {
    ((math_sum*)some)->add(arg);
    return;
  }
  math_something* tmp_a = new math_something(*this);
  some = new math_sum(*tmp_a);//на предыдущем шаге мы сохранили этот объект(по адресу some)
  ((math_sum*)some)->add(arg);
  arg_type = t_sum;
}

void math_something::push_sub(math_something& arg)
{
  if(arg_type == t_sum)
  {
    ((math_sum*)some)->sub(arg);
    return;
  }
  math_something* tmp_a = new math_something(*this);
  some = new math_sum(*tmp_a);//на предыдущем шаге мы сохранили этот объект(по адресу some)
  ((math_sum*)some)->sub(arg);
  arg_type = t_sum;
}

void math_something::push_mul(math_something& arg)
{
  if(arg_type == t_mul)
  {
    ((math_sum*)some)->mul(arg);
    return;
  }
  math_something* tmp_a = new math_something(*this);
  some = new math_mul(*tmp_a);//на предыдущем шаге мы сохранили этот объект(по адресу some)
  ((math_mul*)some)->mul(arg);
  arg_type = t_mul;
}

void math_something::push_div(math_something& arg)
{
  math_something* tmp_a = new math_something(*this);
  some = new math_fraction(*tmp_a, arg);//на предыдущем шаге мы сохранили этот объект(по адресу some)
  arg_type = t_fraction;
}

void math_something::push_shift(math_something& arg, bool direction)
{

}

/*
 *-2 <
 *-1 <=
 *+0 ==
 *+1 >=
 *+2 >
 */
int math_something::compare(math_something& arg)
{
  //1-й способ - привести к двум числам и сравнить
  //2-й способ - убрать функцию (степени одинаковые, логарифмы с одинаковым основанием)
  //3-й способ попробовать вычесть или поделить
  //и тд
}
