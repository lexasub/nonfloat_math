math_mul::math_mul()
{
  if(args = (math_something*)malloc(sizeof(math_something) * num_alloc))
    n_alloced = num_alloc;
}

math_mul::math_mul(math_mul& arg)
{
  n = arg.n;
  n_alloced = arg.n_alloced;
  args = arg.args;
  fork_childs();
}

math_mul::math_mul(math_something& arg)
{
  if(args = (math_something*)malloc(sizeof(math_something) * num_alloc))
  {
    n_alloced = num_alloc;
    n = 1; 
    memcpy(args, &arg, sizeof(math_something));
    args[0].fork_childs();
  }
}

math_mul::~math_mul()
{
  while(n--) args[n].~math_something();
  free(args);
  n_alloced = 0;
}

void math_mul::fork_childs()
{
  math_something* tmp = args;
  if(args = (math_something*)malloc(sizeof(math_something) * n_alloced))
  {
    memcpy(args, tmp, sizeof(math_something) * n_alloced);
    int i = n;
    while(i--) args[i].fork_childs();
  }
}

math_mul& math_mul::mul(math_something& arg)
{
  if(n>=n_alloced)
  {
    if(args = (math_something*)realloc(arggs, (n_alloced + num_alloc) * sizeof(math_something)))
      n_alloced += num_alloc;
    else return *this;//throw exception
  }
  if(args[n].some = realloc(args[n].some, arg.size_type()))
  {
    //hmm, if i want add too mul это производит походу  mul(mul(a),mul(b))), а надо mul(a, b)
    memcpy(args[n].some, arg.some, arg.size_type());
    arg[n].fork_childs();
    n++;
  }
}

void math_mul::simply()
{
  int mul = 1;//пока что в инт копим// пытаемся запихать инты в произведение(2*obj*3=6*obj)
  int cnt = 0;//кол-во интов
  for(register unsigned int i = 0; i < n; i++)
  {
    args[i].simply();
    if(args[i].arg_type == t_int)
    {
      cnt++;
      if(args[i].sign)
        mul*=-(*((int*)(args[i].some)));
      else
        mul*=(*((int*)(args[i].some)));
      args[i].~math_something();
    }
  }
  if(cnt)
  {
    cnt = n - cnt + (mul != 1);//+1 мы же должны в сумму добавить число
    n_alloced = cnt + (cnt % num_alloc);
    math_something *tmp = new math_something[n_alloced];//это не надо сокращать//что если есть такие элементы которые запрещают складывать, например что-то типа неассоциативности умножения матриц только для сложения
    if(mul) tmp[0].add_int(mul);
    int j = (mul != 1);
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

math_something* math_mul::build_ph0()
{
  if(math_something::ph0_mul(args, n))
    return args;//только в первом элементе остаются данные. текущий объект надо на них заменить
  return NULL;
}
