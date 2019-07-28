#include "list.h"
#include <iostream>
list::list():next(NULL), prev(NULL), arg(new math_math){}

list::list(const math_math& c):next(NULL), prev(NULL)
{
  arg = new math_math(c);
}

list::list(math_math& a, math_math& b):next(NULL), prev(NULL)
{
  arg = new math_math(a);
  push(b);
}

list::list(list* c):prev(NULL)
{
  next = c->next;
  arg = c->arg;
  fork_childs();
}
 
list::list(const list& c):next(c.next), prev(NULL)
{  
  arg = c.arg;
  fork_childs();
}

list::~list()
{
  arg->~math_math();
  if(next != NULL) next->~list();
}

math_math* list::last()
{
  if(next == NULL) return arg;
  return next->last();
}

void list::ch_last(math_math& c)
{
  if(next == NULL)
  {
    delete arg;
    arg = new math_math(c);
  }
  else next->ch_last(c);
}

math_math* list::first()
{
  if(prev == NULL) return arg;//только это и должно срабатывать, но на всякий случай сделаем следующее
  return prev->first();
}

void list::ch_first(math_math& c)
{
  if(prev == NULL)
  {
    delete arg;
    arg = new math_math(c);
  }
  else prev->ch_first(c);
}

void list::push(const math_math& c)
{
  if(next == NULL)
  {
    next = new list(c);
    next->prev = this;
    return;
  }
  next->push(c);
}

void list::push(list* c, const bool sign)
{
  if(next == NULL)
  {
    next = new list(c);
    next->prev = this;
    list *tmp = next;
    while(tmp != NULL)
    {
      tmp->arg->sign = tmp->arg->sign ^ sign;//a+(-1)(d+c)-> a+(-1)d+(-1)c
      tmp = tmp->next;
      tmp = NULL;
    }
    return;
  }
  next->push(c, sign);
}

void list::fork_childs()
{
  arg = new math_math(*arg);
  if(next != NULL)
  {
    next = new list(*next);
    next->prev = this;
    return;
  }
}

void list::print(ostream& os, const int cnt_tabes)
{
  arg->print(os, cnt_tabes);
  if(next != NULL) next->print(os, cnt_tabes);
}
