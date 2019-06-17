#include <cmath>

enum t_arg{t_null, t_fraction, t_sum, t_mul};

class math_something
{
  public:
  bool sign = 0;//0 -> +, 1 -> -
  void *some;
  t_arg arg_type;//may be add var for size of type?
  math_something();
  math_something(math_something& arg);
  math_something(void *arg, t_arg type, bool _sign = 0); 
  ~math_something();
  void child_destructor();
  
  void fork_childs();//first - copy obj, second - fork_child()
  int size_type(t_arg type);
  int size_type();
  void ch_sign();
  void add_int(int& arg);
};

class math_sum
{
  public:
  int n = 0, n_alloced = 0;
  const int num_alloc = 2;//количестов элементов за одну аллокацию
  math_something *args;
  
  math_sum();
  math_sum(math_sum& sum);
  math_sum(math_something& arg);//0-я summ
  ~math_sum();

  void fork_childs();
  math_sum& add(math_something& arg);
  math_sum& sub(math_something& arg);  
};

class math_mul
{
  public:
  int n = 0, n_alloced = 0;
  const int num_alloc = 2;
  math_something* args;
  
  math_mul();
  math_mul(math_mul& arg);//copy
  math_mul(math_something& arg);//add one arg
  ~math_mul();

  void fork_childs();
  math_mul& mul(math_something& arg);
};

class math_fraction
{
  public:
  math_something num,div;
  
  math_fraction();
  math_fraction(math_fraction& arg);
  math_fraction(math_something& _num, math_something& _div);
  ~math_fraction();

  void fork_childs();
};

class math
{
  math_something _arg;
  public:
  math();
  math(math& arg);
  math(int arg);
  ~math();
  
  bool operator <(int arg);
  bool operator >(int arg);
  bool operator ==(int arg);
  bool operator !=(int arg);
  bool operator <=(int arg);
  bool operator >=(int arg);

  math& operator +(int arg);
  math& operator -(int arg);
  math& operator *(int arg);
  math& operator /(int arg);
  math& operator %(int arg);

  math& operator +=(int arg);
  math& operator -=(int arg);
  math& operator *=(int arg);
  math& operator /=(int arg);
  math& operator %=(int arg);

  math& operator =(int arg);
   
  math& operator >>(int arg);
  math& operator <<(int arg);
  math& operator <<=(int arg);
  math& operator >>=(int arg);
	
  math& operator ()(int arg);
  
  bool operator <(math& expr);
  bool operator >(math& expr);
  bool operator ==(math& expr);
  bool operator !=(math& expr);
  bool operator <=(math& expr);
  bool operator >=(math& expr);

  math& operator +(math& expr);
  math& operator -(math& expr);
  math& operator *(math& expr);
  math& operator /(math& expr);
  math& operator %(math& expr);

  math& operator +=(math& expr);
  math& operator -=(math& expr);
  math& operator *=(math& expr);
  math& operator /=(math& expr);
  math& operator %=(math& expr);

  math& operator =(math& expr);
   
  math& operator >>(math& expr);
  math& operator <<(math& expr);
  math& operator <<=(math& expr);
  math& operator >>=(math& expr);
	
  math& operator ()(math& expr);

  math& operator ++();//++A
  math& operator --();
  math& operator ++(int k);//k - unusable//A++
  math& operator --(int k);
};
