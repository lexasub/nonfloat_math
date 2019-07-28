#include "math_math.h"
#include <iostream>

math_math::math_math(const int& c): sign(0), arg(new int), _type(type_int)
{
  *(reinterpret_cast<int *>(arg)) = c;
}

math_math::math_math(const math_math& c): sign(c.sign), _type(c._type)
{
  arg = c.arg;
  fork_childs();
}

math_math::math_math(math_math& a, math_math& b, const type_arg __type): sign(0)//__type!=type_int, type_null
{
  if((__type == type_int) || (__type == type_null)) return;//throw exception
  if(a._type == type_null) {arg = b.arg;sign = b.sign;_type = b._type;fork_childs();return;}
  if(b._type == type_null) {arg = a.arg;sign = a.sign;_type = a._type;fork_childs();return;}

  if(a._type == __type)
  {
    if((__type == type_add) || (__type == type_mul))
    {
      arg = new list(a);
      _type = __type;
      //fork_childs();форкать же не надо, мы list создали
      (static_cast<list *>(arg))->push(b);
      return;
    } 
    if(__type == type_div)//а иначе не может быть(пока что)
    {
      arg = new list(a);
      _type = type_div;
      //fork_childs();
      if(__type == b._type)//(a/b)/(c/d) -> (a*d)/(b*c)
      {
        math_math *tmp = (static_cast<list *>(arg))->first()->mul(*((static_cast<list*>(b.arg))->last()));
        (static_cast<list *>(arg))->ch_first(*tmp);
        tmp = (static_cast<list *>(arg))->last()->mul(*((static_cast<list*>(b.arg))->first()));
        (static_cast<list *>(arg))->ch_last(*tmp);
        return;
      }
      (static_cast<list *>(arg))->ch_last(*((static_cast<list *>(arg))->last()->mul(b)));
      return;
    }
  }

  if((a._type == type_mul)&&(__type == type_div))
  {
    sign = a.sign ^ b.sign;
    _type = type_div;
    if(b._type == type_div)
    {
      arg = new list(*((static_cast<list *>(b.arg))->last()), *((static_cast<list *>(b.arg))->first()));//a/b -> b/a
      (static_cast<list *>(arg))->ch_first(*((static_cast<list *>(arg))->first()->mul(a)));
      return;
    }
    arg = new list(a, b);
    return;
  }

  if((a._type == type_div)&&(__type == type_mul))
  {
    arg = new list (a);
    _type = type_div;
    //fork_childs();
    math_math* t;
    if(b._type == type_div)
    {
      t = (static_cast<list*>(b.arg))->first();
      t = (static_cast<list *>(arg))->first()->mul(*t);//циклические вызовы
//      (static_cast<list *>(arg))->ch_first(*t);
   //  t =  (static_cast<list *>(arg))->last()->mul(*((static_cast<list*>(b.arg))->last()));
  //    (static_cast<list *>(arg))->ch_last(*t);
      return;
    }
    t = (static_cast<list *>(arg))->first()->mul(b);
    (static_cast<list *>(arg))->ch_first(*t);
    return;
  }

  if(a._type == type_int)
  {
    _type = __type;
    if((__type == type_add) || (__type == type_mul))
    {
      arg = new list(b);
      sign = b.sign;
      //fork_childs();
      (static_cast<list *>(arg))->push(a);//int коммутативен
      return;
    }
    if(__type == type_div)
    {
      sign = a.sign ^ b.sign;
      if(b._type == type_div)//a/(b/c) -> (a*c)/b
      {
        math_math* tmp = new math_math(a, *((static_cast<list*>(b.arg))->last()), type_mul);//a*c
        arg = new list(*tmp, (*(static_cast<list *>(b.arg))->first()));//(a*c)/b
        delete tmp;
        return;
      }
      arg = new list(a, b);
      return;
    }
  }
  _type = __type;
  arg = new list(a, b);
}

math_math::~math_math()
{
  if(_type == type_null) return;
  if(_type == type_int){delete static_cast<int *>(arg); return;}
  delete static_cast<list *>(arg);
}

math_math* math_math::add(math_math& c)
{
  if(c._type == type_null) return this;//это нормально, но стоит писать в лог что это произошло

  if(_type == type_add)
  {
    if(c._type == type_add)
    {
      (static_cast<list *>(arg))->push(static_cast<list *>(c.arg), c.sign);
      return this;
    }
    (static_cast<list *>(arg))->push(c);
    return this;
  }
  return new math_math(*this, c, type_add);
}

math_math* math_math::c_add(math_math& c)
{
  return new math_math(*this, c, type_add);  
}

math_math* math_math::sub(math_math& c)
{
  if((_type == type_add)&&(c._type != type_null))
  {
    if(c._type == type_add)
    {
      (static_cast<list *>(arg))->push(static_cast<list *>(c.arg), !(c.sign));
      return this;
    }
    (static_cast<list *>(arg))->push(c);
    return this;
  }
  math_math* tmp = add(c);
  (static_cast<list *>(tmp->arg))->last()->sign = !((static_cast<list *>(tmp->arg))->last()->sign);//поменяли знак на противоположный
  return tmp;
}

math_math* math_math::c_sub(math_math& c)
{
  math_math* tmp = new math_math(*this, c, type_add);
  (static_cast<list *>(tmp->arg))->last()->sign = !((static_cast<list *>(tmp->arg))->last()->sign);
  return tmp;
}

math_math* math_math::mul(math_math& c)
{
  if(c._type == type_null) return this;//это нармально, но стоит писать в лог что это произошло

  if(_type == type_mul)
  {
    if(c._type == type_mul)
    {
      (static_cast<list *>(arg))->push(static_cast<list *>(c.arg), c.sign);
      return this;
    }
    (static_cast<list *>(arg))->push(c);
    return this;
  }
  return new math_math(*this, c, type_mul);
}

math_math* math_math::c_mul(math_math& c)
{
  return new math_math(*this, c, type_mul);
}

math_math* math_math::div(math_math& c)
{
  if(c._type == type_null) return this;//это нармально, но стоит писать в лог что это произошло
  if(_type == type_div)
  {
    if(c._type == type_div)
    {
      (static_cast<list *>(arg))->ch_first(*((static_cast<list *>(arg))->first()->mul(*((static_cast<list *>(c.arg))->last()))));
      (static_cast<list *>(arg))->ch_last(*((static_cast<list *>(arg))->last()->mul(*((static_cast<list *>(c.arg))->first()))));
      return this;
    }
    (static_cast<list *>(arg))->ch_last(*((static_cast<list *>(arg))->last()->mul(c)));
    return this;
  }

  return new math_math(*this, c, type_div);
}

math_math* math_math::c_div(math_math& c)
{
  return new math_math(*this, c, type_div);
}

void math_math::fork_childs()
{
  if((_type == type_add) || (_type == type_mul) || (_type == type_div))
    arg = new list(static_cast<list *>(arg));
  else
    if(_type == type_int)
    {
      int tmp = *(static_cast<int *>(arg));
      arg = new int;
      *(static_cast<int *>(arg)) = tmp;
    }
}

void math_math::print(ostream& os, const int cnt_tabes)
{
  int t = cnt_tabes;
  os << '\n';
  while(t--) os << '\t';
  os << (sign?'-':'+');
  switch(_type)
  {
    case type_null: os << "type_null";break;
    case type_add: os << "type_add";break;
    case type_mul: os << "type_mul";break;
    case type_div: os << "type_div";break;
    case type_int: os << "type_int";
  }
  os << '{';
  if(_type != type_null)
  {
    if(_type == type_int)
    {
      os << *(static_cast<int *>(arg)) << '}';
      return;
    }
    (static_cast<list *>(arg))->print(os, cnt_tabes + 1);
    os << '\n';
  }
  t = cnt_tabes;
  while(t--) os << '\t';
  os << "}";
}
