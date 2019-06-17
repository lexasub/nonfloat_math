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
    else retrun *this;//тут еще лучше err выдавать
  }
  if(args[n].some = realloc(args[n].some, arg.size_type()))
  {
    memcpy(args[n].some, arg.some, arg.size_type());
    arg[n].fork_childs();
    n++;
  }
  //иначе желательно выдавать err
  return *this;
}

math_sum& math_sum::sub(math_something& arg)
{
  add(arg);
  args[n-1].ch_sign();
  return *this;
}
