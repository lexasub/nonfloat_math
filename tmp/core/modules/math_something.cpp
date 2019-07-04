struct math_shift
{
  math_something arg1;
  math_something arg2;// в последствии мы его в int превращаем
}

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
    case t_shift:
      ((math_shift*)some)->arg1.~math_fraction;
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
      case t_shift:
        math_shift *tmp = (math shift*)some;
        some = malloc(sizeof(math_shift));
        math_shift *tmp2 = (math_shift*)some;
        tmp2->arg2.sign = tmp->arg2.sign;
        tmp2->arg2.some = tmp->arg2.some;
        tmp2->arg2.arg_type = tmp->arg2.arg_type;
        tmp2->arg1.fork_childs();
        tmp2->arg1.sign = tmp->arg1.sign;
        tmp2->arg1.some = tmp->arg1.some;
        tmp2->arg1.arg_type = tmp->arg1.arg_type;
        tmp2->arg1.fork_childs();
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
    case t_shift:
      return sizeof(math_shift);
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
  some = malloc(sizeof(math_shift));
  math_something* tmp = &(((math_shift*)some)->arg1);
  tmp->sign = a.sign;
  tmp->some = a.some;
  tmp->arg_type = a.arg_type;
  tmp->fork_childs();
  
  tmp = &(((math_shift*)some)->arg2);
  tmp->sign = b.sign;
  if(direction) tmp->sign = !tmp->sign;
  tmp->some = b.some;
  tmp->arg_type = b.arg_type;
  tmp->fork_childs();
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

void math_something::push_shift(math_something& arg, bool direction=0)// 0 << 1>>
{
  math_shift* tu = malloc(sizeof(math_shift));
  math_something* tmp = &(tu->arg1);
  tmp->sign = sign;
  tmp->some = some;
  tmp->arg_type = arg_type;
  //tmp.fork_childs();//таак, форкать тут не надо т к мы берем текущий объект
  
  tmp = &(tu->arg2);
  tmp->sign = arg.sign;
  if(direction) tmp->sign = !tmp->sign;
  tmp->some = arg.some;
  tmp->arg_type = arg.arg_type;
  tmp->fork_childs();//а тут надо так как это переданный аргумент
  
  arg_type = t_shift;
  some = tu;
  sign = 0;//сбрасываем знак
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

/*
 *вызывает функции упрощения внутри классов
 *по сути работает только на листочках графа(концах - на них расположены бызовые типы - пока что int)
 *это упрощение на уровне чисел
 */
void math_something::simply()
{
  switch(arg_type)
  {
    case t_fraction:
      ((math_fraction*)some)->simply();
      if((((math_fraction*)some)->div.arg_type == t_int) && ((*((int*)(((math_fraction*)some)->div.some))) == 1))
      {
        void *tmp = some;
        sign = (math_fraction*)tmp->num.sign;
        arg_type = (math_fraction*)tmp->num.arg_type;
        some = (math_fraction*)tmp.num.some;
        fork_childs();
        (math_fraction*)tmp.~math_fraction();
      }
      return;
    case t_sum:
      ((math_sum*)some)->simply();
      if(((math_sum*)some)->n == 1)//если один аргумент то переносим заменяем "текущий" obj на 0-й арг  
      {
        sign = ((math_sum*)some)->args[0].sign;
        arg_type = ((math_sum*)some)->args[0].arg_type;
        free(((math_sum*)some)->args);
        void *_some = some;
        some = ((math_sum*)some)->args[0].some;
        free(_some);
      }
      return;
    case t_mul:
      ((math_mul*)some)->simply();
      if(((math_mul*)some)->n == 1)
      {
        sign = ((math_sum*)some)->args[0].sign;
        arg_type = ((math_sum*)some)->args[0].arg_type;
        free(((math_sum*)some)->args);
        void *_some = some;
        some = ((math_sum*)some)->args[0].some;
        free(_some);
      }
      return;
    case t_shift:
      ((math_shift*)some)->arg1.simply();
      ((math_shift*)some)->arg1.simply();
  }
}

/*
 *разделение по фазам(более медленно но более надежно и тесты наверно проще написать)
 *эта фаза пытается объеденить аргументы с одноименной функцией (a*b)*c-> a*b*c a*(b/c)->(a*b)/c
 *
 */
void math_something::build_ph0()
{
  //simply();
  switch(arg_type)
  {
    case t_fraction:
      math_fraction *t = (math_fraction*)some
      math_something* tmp = t->build_ph0();
      if(tmp)//not null
      {
        some = tmp->some;
        arg_type = tmp->arg_type;
        if(tmp->sign) sign = !sign;
        fork_childs();
        t->~math_fraction();
        free(t);
      }
      return;
    case t_sum:
//len'
    case t_mul:
      math_mul *t = (math_mul*)some;
      math_something* tmp = t)build_ph0();
      if(tmp)
      {
        some = tmp->some;
        arg_type = tmp->arg_type;
        if(tmp->sign) sign = !sign;
        fork_childs();
        t->~math_mul();
        free(t)
      }
  }
}

bool math_something::ph0_div(math_something& arg)
{
  if(arg.arg_type == t_fraction)
  {
    math_fraction* _arg = (math_fraction*)(arg.some);
    switch(arg_type)
    {
     case t_fraction:
        math_fraction* tmp = ((math_fraction*)some);
        tmp->num.push_mul(_arg->div);
        tmp->div.push_mul(_arg->num);
        if(arg.sign) sign = !sign;
        arg.~math_something();//так, второй арг нам уже не нужен
        return true;
      case t_mul:
        math_mul* tmp = ((math_mul*)some);
        push_mul(_arg->div);
        push_div(_arg->num);
        if(arg.sign) sign = !sign;
        arg.~math_something();
        tmp->~math_mul();//push_div поменял some -> осталась выделенная память от старого some
        free(tmp);
        return true;
      case t_int:
        int* tmp = ((int*)some);
        push_mul(_arg->div);
        free(tmp);
        tmp = (int*)some;
        push_div(_arg->num);
        free(tmp);
        if(arg.sign) sign = !sign;
        arg.~math_something();
        return true;
      default: return false;
    }
  }
  else if((arg.arg_type == t_mul) && (arg_type == t_fraction))
  { 
    math_mul* _arg = (math_mul*)(arg.some);
    math_fraction* tmp = ((math_fraction*)some);
    tmp->div.push_mul(_arg);
    if(arg.sign) sign = !sign;
    arg.~math_something();
    return true;
  }
  return false;
}

bool math_something::ph0_mul(math_something* args, int n)
{
  for(int i = 0; i < n; i++)
  {
  //и что тут делать? (кроме вызова build_ph0())
    args[i].build_ph0();
  }
}
/*
 *это фаза оптимизаций - эвклид для math_something
 *
 *
 */

void math_something::build_ph1()
{

}
