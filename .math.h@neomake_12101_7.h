#include <cmath>

enum t_arg{t_null, t_fraction, t_sum};

class math_something
{
  public:
  bool sign = 0;//0 -> +, 1 -> -
  void *some;
  t_arg arg_type;
  math_something();
  math_something(void *arg, t_arg type);
  void deep_copy(void *arg, void *p);
  int size_type(t_arg type);
  void ch_sign();
  //math_something& operator ->();//for get obj with type;//ну нафиг, лучше методы прописать
};

class math_sum
{
  public:
  int n = 0, n_alloced = 0;
  const int num_alloc = 2;//количестов элементов за одну аллокацию
  math_something *args;
  math_sum();
  math_sum(math_sum& sum);
  math_sum(math_something* arg);//0-я summ
  ~math_sum();
  void deep_copy(math_something *_args, math_something *p);
  math_sum& add(math_something& arg);
  math_sum& sub(math_something& arg);  
};

class math_fraction
{
  public:
  int n_n = 0, n_d = 0, n_n_alloced = 0, n_d_alloced = 0;
  const int num_alloc = 2;//количество элементов за одну аллокацию
  void deep_copy(math_fraction& a, math_fraction& b);//...
  math_something *num,*div;
  math_fraction();
  math_fraction(math_fraction& fract);
  math_fraction(math_something *num, math_something *div, int n_n, int n_d);
  ~math_fraction();
  math_fraction& mult(math_something *num, math_something *div, int n_n, int n_d);
  math_fraction& mult(int num);
  math_fraction& mult(int *num, int n);
  math_fraction& div(int div);
  math_fraction& div(int *div, int n);
};

class math
{
  public:
  math();
  math(math& expr);
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
