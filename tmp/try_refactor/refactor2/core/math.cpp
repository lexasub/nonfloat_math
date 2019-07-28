#include "math.h"
#include <iostream>
math::math(const math& arg)
{
  obj = new math_math(*(arg.obj));
}

math::math(const math_math& arg)
{
  obj = new math_math(arg);
}
math::math(const int arg)
{
  obj = new math_math(arg);
}

math::~math()
{
  obj->~math_math();
}

bool math::operator <(int arg)
{
  
}

bool math::operator >(int arg)
{

}

bool math::operator ==(int arg)
{

}

bool math::operator !=(int arg)
{

}

bool math::operator <=(int arg)
{

}

bool math::operator >=(int arg)
{

}


math& math::operator +(int arg)
{
  math_math* tmp = new math_math(arg);
  math* res = new math(*(obj->c_add(*tmp)));
  delete tmp;
  return *res;
}

math& math::operator -(int arg)
{
  math_math* tmp = new math_math(arg);
  math* res = new math(*(obj->c_sub(*tmp)));
  delete tmp;
  return *res;
}

math& math::operator *(int arg)
{
  math_math* tmp = new math_math(arg);
  math* res = new math(*(obj->c_mul(*tmp)));
  delete tmp;
  return *res;
}

math& math::operator /(int arg)
{
  math_math* tmp = new math_math(arg);
  math* res = new math(*(obj->c_div(*tmp)));
  delete tmp;
  return *res;
}

math& math::operator %(int arg)
{

}
//пока что забили на его реализацию//но он будет в ядре

math& math::operator +=(int arg)
{
  math_math* t = new math_math(arg);
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->add(*t);//тут же add, а не c_add надо
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator -=(int arg)
{
  math_math* t = new math_math(-arg);
  
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->add(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator *=(int arg)
{
  math_math* t = new math_math(arg);
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->mul(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;  
}

math& math::operator /=(int arg)
{
  math_math* t = new math_math(arg);
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->div(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator %=(int arg)
{
  return *this;
}


math& math::operator =(int arg)
{
  delete(obj);
  obj = new math_math(arg);
  return *this;
}

 
math& math::operator >>(int arg)
{

}

math& math::operator <<(int arg)
{

}

math& math::operator <<=(int arg)
{
  return *this;
}

math& math::operator >>=(int arg)
{
  return *this;
}


bool math::operator <(math& arg)
{

}

bool math::operator >(math& arg)
{

}

bool math::operator ==(math& arg)
{

}

bool math::operator !=(math& arg)
{

}

bool math::operator <=(math& arg)
{

}

bool math::operator >=(math& arg)
{

}


math& math::operator +=(math& arg)
{
  math_math* t = new math_math(*(arg.obj));
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->add(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator -=(math& arg)
{
  math_math* t = new math_math(*(arg.obj));
  t->sign = !t->sign;
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->add(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator *=(math& arg)
{
  math_math* t = new math_math(*(arg.obj));
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->mul(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator /=(math& arg)
{
  math_math* t = new math_math(*(arg.obj));
  if(obj->_type != type_null)
  {
    math_math* tmp = obj->div(*t);
    delete t;
    if(tmp != obj)
    {
      delete obj;
      obj = tmp;
    }
  }
  else
  {
    delete obj;
    obj = t;
  }
  return *this;
}

math& math::operator %=(math& arg)
{
  return *this;
}


math& math::operator +(math& arg)
{
  math_math* tmp = new math_math(*(arg.obj));
  math* res = new math(*(obj->c_add(*tmp)));
  return *res;
}

math& math::operator -(math& arg)
{
  math_math* tmp = new math_math(*(arg.obj));
  math* res = new math(*(obj->c_sub(*tmp)));
  return *res;
}

math& math::operator *(math& arg)
{
  math_math* tmp = new math_math(*(arg.obj));
  math* res = new math(*(obj->c_mul(*tmp)));
 // return *res;
  return *this;
}

math& math::operator /(math& arg)
{
  math_math* tmp = new math_math(*(arg.obj));
  math* res = new math(*(obj->c_div(*tmp)));
  return *res;
}

math& math::operator %(math& arg)
{

}


math& math::operator =(math& arg)
{
  delete obj;
  obj = new math_math(*(arg.obj));
  return *this;
}

 
math& math::operator >>(math& arg)
{

}

math& math::operator <<(math& arg)
{

}

math& math::operator <<=(math& arg)
{
  return *this;
}

math& math::operator >>=(math& arg)
{
  return *this;
}


math& math::operator ++()
{

}
//++A
math& math::operator --()
{

}

math& math::operator ++(int k)
{

}
//k - unusable//A++
math& math::operator --(int k)
{

}


math& math::simpy()
{

}

math& math::build()
{

}

float math::eval()
{

}

ostream& operator <<(ostream& os, math& m)
{
  m.obj->print(os, 0);//0-tabes
}
