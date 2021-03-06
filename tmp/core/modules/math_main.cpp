math::math(math& arg)
{
  _arg.sign = arg.sign;
  _arg.some = arg.some;
  _arg.arg_type = arg.arg_type;
  _arg.fork_childs();
}

math::math(int& arg)
{
  _arg.add_int(arg);
}

math::~math()
{
  _arg.~math_something();
}

bool math::operator <(int arg)
{
  return (_arg.compare(math_something::math_something(arg)) == -2);
}

bool math::operator >(int arg)
{
  return (_arg.compare(math_something::math_something(arg)) == +2);
}

bool math::operator ==(int arg)
{
  return !(_arg.compare(math_something::math_something(arg)));
}

bool math::operator !=(int arg)
{
  return (_arg.compare(math_something::math_something(arg)));
}

bool math::operator <=(int arg)
{
  return (_arg.compare(math_something::math_something(arg)) == -1);
}

bool math::operator >=(int arg)
{
  return (_arg.compare(math_something::math_something(arg)) == +1);
}

bool math::operator <(math& arg)
{
  return (_arg.compare(arg) == -2);
}

bool math::operator >(math& arg)
{
  return (_arg.compare(arg) == +2);
}

bool math::operator ==(math& arg)
{
  return !(_arg.compare(arg));
}

bool math::operator !=(math& arg)
{
  return (_arg.compare(arg));
}

bool math::operator <=(math& arg)
{
  return (_arg.compare(arg) == -1);
}

bool math::operator >=(math& arg)
{
  return (_arg.compare(arg) == +1);
}

math& math::operator +(int arg)
{
  math *tmp = new math();
  tmp->_arg.add_sum(_arg, math_something::math_something(arg));
  return *tmp;
}

math& math::operator -(int arg)
{
  math *tmp = new math();
  tmp->_arg.add_sub(_arg, math_something::math_something(arg));
  return *tmp;
}

math& math::operator *(int arg)
{
  math *tmp = new math();
  tmp->_arg.add_mul(_arg, math_something::math_something(arg));
  return *tmp;
}

math& math::operator /(int arg)
{
  math *tmp = new math();
  tmp->_arg.add_div(_arg, math_something::math_something(arg));
  return *tmp;
}

math& math::operator >>(int arg)
{
  math *tmp = new math();
  tmp->_arg.add_shift(*this, math_something::math_something(arg), 1);
  return *tmp;
}

math& math::operator <<(int arg)
{
  math *tmp = new math();
  tmp->_arg,add_shift(*this, math_something::math_something(arg), 0);
  return *tmp;
}

math& math::operator +(math& arg)
{
  math *tmp = new math();
  tmp->_arg.add_sum(_arg, arg);
  return *tmp;
}

math& math::operator -(math& arg)
{
  math *tmp = new math();
  tmp->_arg.add_sub(_arg, arg);
  return *tmp;
}

math& math::operator *(math& arg)
{
  math *tmp = new math();
  tmp->_arg.add_mul(_arg, arg);
  return *tmp;
}

math& math::operator /(math& arg)
{
  math *tmp = new math();
  tmp->_arg.add_div(_arg, arg);
  return *tmp;
}

math& math::operator >>(math& arg)
{
  math *tmp = new math();
  tmp->_arg.add_shift(_arg, arg, 1);
  return *tmp;
}

math& math::operator <<(math& arg)
{
  math *tmp = new math();
  tmp->_arg.add_shift(_arg, arg, 0);
  return *tmp;
}

math& math::operator +=(int arg)
{
  _arg.push_sum(math_something::math_something(arg));
  return *this;
}

math& math::operator -=(int arg)
{
  _arg.push_sub(math_something::math_something(arg));
  return *this;
}

math& math::operator *=(int arg)
{
  _arg.push_mul(math_something::math_something(arg));
  return *this;
}

math& math::operator /=(int arg)
{
  _arg.push_div(math_something::math_something(arg));
  return *this;
}

math& math::operator >>=(int arg)
{
  _arg.push_shift(math_something::math_something(arg), 1);
  return *this;
}

math& math::operator <<=(int arg)
{
  _arg.push_shift(math_something::math_something(arg), 0);
  return *this;
}

math& math::operator +=(math& arg)
{
  _arg.push_sum(arg);
  return *this;
}

math& math::operator -=(math& arg)
{
  _arg.push_sub(arg);
  return *this;
}

math& math::operator *=(math& arg)
{
  _arg.push_mul(arg);
  return *this;
}

math& math::operator /=(math& arg)
{
  _arg.push_div(arg);
  return *this;
}

math& math::operator >>=(math& arg)
{
  _arg.push_shift(arg, 1);
  return *this;
}

math& math::operator <<=(math& arg)
{
  _arg.push_shift(arg, 0);
  return *this;
}

math& math::operator =(int arg)
{
  _arg.child_destructor();
  _arg.sign = 0;
  _arg.add_int(arg);
  return *this;
}

math& math::simply()
{
  _arg.simply();
  return *this;
}

math& math::build()
{
  _arg.build_ph0();
  _arg.build_ph1();
  return *this;
}

float math::eval()
{
  return _arg.eval();
}

void evklid(int& a, int& b)
{
  register int t_a = a, t_b = b, c;
  while (t_b)
  {
    c = t_a % t_b;
    t_a = t_b;
    t_b = c;
  }
  c = abs(t_a);
  a /= c;
  b /= c;
}
