/*
    Crapculator plugin for FAR Manager
    Copyright (C) 2009 Alex Yaroslavsky

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <math.h>
#include <errno.h>
#include <string.h>
#include "common.hpp"

static double vars[L'z'-L'a'+1];

static unsigned long long factorial(unsigned long long n)
{
  if (n==0ull || n==1ull)
    return 1ull;

  unsigned long long r=1ull;

  for ( ; n > 1ull; n--)
    r*=n;

  return r;
}

static bool GetNumber(const wchar_t **p, double *n)
{
  if (!IsDigit(**p))
  {
    if (((**p)|0x20) == L'e')
    {
      *n=M_E;
      (*p)++;
      return true;

    }
    if (((**p)|0x20) == L'p')
    {
      (*p)++;
      if (((**p)|0x20) == L'i')
      {
        *n=M_PI;
        (*p)++;
        return true;
      }
      (*p)--;
    }
    return false;
  }

  *n=0;
  while (IsDigit(**p))
  {
    *n=*n*10 + **p - L'0';
    (*p)++;
  }

  if (**p != '.')
    return true;

  (*p)++;

  double r=0;
  double c=10.0;
  while (IsDigit(**p))
  {
    r+=((double)(**p - L'0'))/c;
    (*p)++;
    c*=10.0;
  }

  *n+=r;

  return true;
}

static bool GetAction(const wchar_t **p, int *a)
{
  switch (**p)
  {
    case L'+':
    case L'-':
    case L'*':
    case L'/':
    case L'%':
    case L'^':
      *a = **p;
      break;

    default: return false;
  }

  (*p)++;

  return true;
}

static bool GetUnaryActionPrefix(const wchar_t **p, int *a)
{
  switch (**p)
  {
    case L'+':
    case L'-':
      *a = **p;
      (*p)++;
      return true;
  }

  switch ((**p)|0x20)
  {
    case L'c':
    {
      (*p)++;
      switch ((**p)|0x20)
      {
        case L'o':
          (*p)++; if (((**p)|0x20) != L's') return false;
          *a = L'c';
          break;

        case L'e':
          (*p)++; if (((**p)|0x20) != L'i') return false;
          (*p)++; if (((**p)|0x20) != L'l') return false;
          *a = L'e';
          break;

        default: return false;
      }
      break;
    }

    case L'd':
      (*p)++; if (((**p)|0x20) != L'e') return false;
      (*p)++; if (((**p)|0x20) != L'g') return false;
      *a = L'd';
      break;

    case L'f':
    {
      (*p)++;
      switch ((**p)|0x20)
      {
        case L'a':
          (*p)++; if (((**p)|0x20) != L'c') return false;
          *a = L'!';
          break;

        case L'l':
          (*p)++; if (((**p)|0x20) != L'o') return false;
          (*p)++; if (((**p)|0x20) != L'o') return false;
          (*p)++; if (((**p)|0x20) != L'r') return false;
          *a = L'f';
          break;

        case L'r':
          (*p)++; if (((**p)|0x20) != L'a') return false;
          (*p)++; if (((**p)|0x20) != L'c') return false;
          *a = L'a';
          break;

        default: return false;
      }
      break;
    }

    case L'l':
    {
      (*p)++;
      switch ((**p)|0x20)
      {
        case L'n':
          *a = L'n';
          break;

        case L'o':
          (*p)++; if (((**p)|0x20) != L'g') return false;
          *a = L'l';
          break;

        default: return false;
      }
      break;
    }

    case L'r':
      (*p)++; if (((**p)|0x20) != L'a') return false;
      (*p)++; if (((**p)|0x20) != L'd') return false;
      *a = L'r';
      break;

    case L's':
    {
      (*p)++;
      switch ((**p)|0x20)
      {
        case L'q':
          (*p)++; if (((**p)|0x20) != L'r') return false;
          (*p)++; if (((**p)|0x20) != L't') return false;
          *a = L's';
          break;

        case L'i':
          (*p)++; if (((**p)|0x20) != L'n') return false;
          *a = L'i';
          break;

        default: return false;
      }
      break;
    }

    case L't':
      (*p)++; if (((**p)|0x20) != L'a') return false;
      (*p)++; if (((**p)|0x20) != L'n') return false;
      *a = L't';
      break;

    default: return false;
  }

  (*p)++;

  return true;
}


static bool Action(double x, double y, double *r, int a)
{
  switch (a)
  {
    case L'+': *r=x+y; break;
    case L'-': *r=x-y; break;
    case L'*': *r=x*y; break;
    case L'/': if (!y) return false; *r=x/y; break;
    case L'%': errno=0; *r=fmod(x,y); if (errno) return false; break;
    case L'^': errno=0; *r=pow(x,y); if (errno) return false; break;

    default: return false;
  }

  return true;
}

static bool UnaryAction(double *r, int a)
{
  switch (a)
  {
    case L'+': break;
    case L'-': *r=*r*-1.0; break;

    case L'!': if (*r < 0) return false; *r=factorial(*r); break;

    case L's': errno=0; *r=sqrt(*r); if (errno) return false; break;

    case L'i': errno=0; *r=sin(*r); if (errno) return false; break;
    case L'c': errno=0; *r=cos(*r); if (errno) return false; break;
    case L't': errno=0; *r=tan(*r); if (errno) return false; break;
    case L'd': errno=0; *r=*r/(2.0*M_PI)*360.0; if (errno) return false; break;
    case L'r': errno=0; *r=*r/360.0*(2.0*M_PI); if (errno) return false; break;

    case L'n': errno=0; *r=log(*r); if (errno) return false; break;
    case L'l': errno=0; *r=log10(*r); if (errno) return false; break;

    case L'f': errno=0; *r=floor(*r); if (errno) return false; break;
    case L'e': errno=0; *r=ceil(*r); if (errno) return false; break;
    case L'a': { errno=0; double i; *r=modf(*r, &i); if (errno) return false; break; }

    default: return false;
  }

  return true;
}

#define HIGHEST_PRECEDENCE (1000000)

static int Precedence(int a)
{
  switch (a)
  {
    case L'+':
    case L'-':
      return 10;

    case L'*':
    case L'/':
    case L'%':
      return 100;

    case L'^':
      return 1000;
  }

  return 0;
}

static bool Expression(const wchar_t **p, double *n, int pa, int *b)
{
  if (!**p)
    return false;

  int o=SkipOpenBracket(p);
  *b+=o;

start:

  if (**p == L'$')
  {
    (*p)++; if (**p < L'a' || **p > L'z') return false;

    int v=**p-L'a';

    (*p)++;

    SkipSpace(p);

    if (**p == L':')
    {
      (*p)++;
      SkipSpace(p);

      if (**p != L'=') return false;
      (*p)++;

      int bb=0;
      double nn=0;
      if (!Expression(p, &nn, 0 , &bb) || bb)
        return false;

      (*p)++;
      SkipSpace(p);

      vars[v]=nn;
      goto start;
    }
    else
    {
      *n=vars[v];
    }
  }
  else if (!GetNumber(p, n))
  {
    int u;
    if (!GetUnaryActionPrefix(p,&u))
      return false;

    int d=*b;
    if (!Expression(p, n, HIGHEST_PRECEDENCE , b))
      return false;

    if (!UnaryAction(n, u))
      return false;

    o-=d - *b;
    if (o<0)
      return true;
  }

  SkipSpace(p);

  if (*b)
  {
    int c=SkipCloseBracket(p);
    *b-=c;
    o-=c;
    if (o < 0)
      return true;
  }

  if (*b<0)
    return false;

  while (!IsEnd(**p))
  {
    int a;
    if (pa && o==0)
    {
      const wchar_t *s=*p;

      if (!GetAction(p, &a))
        return false;

      if (pa >= Precedence(a))
      {
        *p = s;
        return true;
      }
    }
    else
    {
      if (!GetAction(p, &a))
        return false;
    }

    double x;
    int d=*b;
    if (!Expression(p, &x, Precedence(a), b))
      return false;

    if (!Action(*n, x, n, a))
      return false;

    o-=d - *b;
    if (o<0)
      return true;
  }

  *b-=SkipCloseBracket(p);

  return true;
}

bool Numerical(const wchar_t **p, double *d)
{
  int b=0;
  *d=0;

  memset(vars,0,sizeof(vars));

  return Expression(p,d,0,&b) && !b;
}
