math_something::math_something():some(NULL),arg_type(t_null){}

math_something::math_something(math_something& arg)
{
  sign = arg.sign;
  some = arg.some;
  arg_type = arg.arg_type;
  fork_childs();
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

