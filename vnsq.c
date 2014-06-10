/* -*- Mode: C; indent-tabs-mode: nil -*- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vnsq.h"

unsigned long vnsq_value = 137;

void
init_vnsq (unsigned long seed)
{
  vnsq_value = seed;
}

unsigned long
vnsq_int32 (void)
{
  unsigned long nextn;
  int nextlen;
  int excess;
  int left_excess;
  int right_excess;
  char decimalrep[50];
  char *nextp;
  nextn = vnsq_value * vnsq_value;
  sprintf (decimalrep, "%lu", nextn);
  nextlen = (int) (strlen (decimalrep));
  excess = nextlen - 6;
  if (excess > 0)
    {
      right_excess = excess / 2;
      left_excess = right_excess + (excess % 2);
      nextp = &decimalrep[left_excess];
      decimalrep[nextlen - right_excess] = 0;
      vnsq_value = atol (nextp);
    }
  else
    {
      vnsq_value = nextn;
    }
  return (nextn);
}
