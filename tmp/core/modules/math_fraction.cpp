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
