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
    else return *this;//тут лучше err выдавать
  }
  if(args[n].some = realloc(args[n].some, arg.size_type()))
  {
    memcpy(args[n].some, arg.some, arg.size_type());
    arg[n].fork_childs();
    n++;
  }
}
