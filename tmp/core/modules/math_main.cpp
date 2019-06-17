math::math(){}
math::math(math& arg)
{
  _arg.sign = arg.sign;
  _arg.some = arg.some;
  _arg.arg_type = arg.arg_type;
  _arg.fork_childs();
}

math::math(int arg)
{
  _arg.add_int(arg);
}
