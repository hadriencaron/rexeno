#ifndef TYPES_HH_
# define TYPES_HH_


typedef unsigned long long ms;

struct pos
{
  double x;
  double y;
};

struct Element
{
  Element()
  {
    volt = 0;
    timing = 0;
  }

  double volt;
  ms timing;
};

typedef vector<Element> datas;

#endif
