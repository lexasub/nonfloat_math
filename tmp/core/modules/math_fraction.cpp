math_fraction::math_fraction()
{
  //да вроде ничего тут делать не надо
}

math_fraction::math_fraction(math_fraction& arg)
{
  num.sign = arg.num.sign;
  num.arg_type = arg.num.arg_type;
  num.some = arg.num.some;

  div.sign = arg.div.sign;
  div.arg_type = arg.div.arg_type;
  div.some = arg.div.some;

  fork_childs();//она маленькая но она нужна для гладкой совместимости с something
}

math_fraction::math_fraction(math_something& _num, math_something& _div)
{
  num.sign = _num.sign;
  num.arg_type = _num.arg_type;
  num.some = _num.some;
 
  div.sign = _div.sign;
  div.arg_type = _div.arg_type;
  div.some = _div.some;
 
  fork_childs();
}

math_fraction::~math_fraction()
{
  num.~math_something();
  div.~math_something();
}

void math_fraction::fork_childs()
{
  num.fork_childs();
  div.fork_childs();
}

void math_fraction::simply()
{
  if((num.arg_type == t_int) && (div.arg_type == t_int))
    evklid(*(int*)(num.some), *(int*)(div.some));
  else
  {
    num.simply();
    div.simply();
    simply();//вдруг они int's стали
  }
}

math_something* math_fraction::build_ph0()
{
  //simply();
  if(num.ph0_div(div)) return &num;
  //тогда текущий эл меняем на ребенка(в num содержится ребенок)но поменять мы не можем по этому возвращаем указатель на ребенка
  return NULL;
}
