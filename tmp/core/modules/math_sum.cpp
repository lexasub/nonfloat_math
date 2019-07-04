math_sum::math_sum()
{
  if(args = (math_something*)realloc(args, num_alloc))
    n_alloced = num_alloc;
}

math_sum::math_sum(math_sum& sum)
{
  args = sum.args;
  n_alloced = sum.n_alloced;
  n = sum.n;
  fork_childs(); 
}

math_sum::math_sum(math_something& arg)
{
  if(args = (math_something*)malloc(sizeof(math_something) * n_alloc))
  {
    n_alloced = num_alloc;
    memcpy(args, arg, sizeof(math_something));
    n = 1;
    args[0].fork_childs();
  }
}

math_sum::~math_sum()
{
  while(n--) args[n].~math_something();//все равно n надо занулить
  free(args);
  n_alloced = 0;
}


void math_sum::fork_childs()
{
  math_something *tmp = args;
  if(args = (math_something*)malloc(sizeof(math_something) * n_alloced))
  {
    memcpy(args, tmp, sizeof(math_something) * n_alloced);
    int i = n;
    while(i--) args[i].fork_childs();
  }
}

math_sum& math_sum::add(math_something& arg)
{
  if(n>=n_alloced)
  {
    if(args = (math_something*)realloc(args, (n_alloced + num_alloc) * sizeof(math_something)))
      n_alloced += num_alloc;
    else retrun *this;//throw exception
  }
  if(args[n].some = realloc(args[n].some, arg.size_type()))
  {
    memcpy(args[n].some, arg.some, arg.size_type());
    arg[n].fork_childs();
    n++;
  }
  //throw exception
  return *this;
}

math_sum& math_sum::sub(math_something& arg)
{
  add(arg);
  args[n-1].ch_sign();
  return *this;
}

void math_sum::simply()
{
  int sum = 0;//пока что в инт копим// пытаемся запихать инты в сумму(2+obj+3=5+obj)
  int cnt = 0;//кол-во интов
  for(register unsigned int i = 0; i < n; i++)
  {
    args[i].simply();
    if(args[i].arg_type == t_int)
    {
      cnt++;
      if(args[i].sign)
        sum-=(*((int*)(args[i].some)));
      else
        sum+=(*((int*)(args[i].some)));
      args[i].~math_something();
    }
  }
  if(cnt)
  {
    cnt = n - cnt + (sum != 0);//+1 мы же должны в сумму добавить число
    n_alloced = cnt + (cnt % num_alloc);
    math_something *tmp = new math_something[n_alloced];//это не надо сокращать//что если есть такие элементы которые запрещают складывать, например что-то типа неассоциативности умножения матриц только для сложения
    if(sum) tmp[0].add_int(sum);
    int j = (sum != 0);
    for(register unsigned int i = n; i--;)
      if(args[i].arg_type != t_int)
      {
        memcpy(tmp[j], args[i], sizeof(math_something));//форкать не надо т.к. мы не копируем, а берем старое
        free(args[i]);
        j++;//j<n-cnt по определению
      }
    n = cnt;
    args = tmp;
  }
}
