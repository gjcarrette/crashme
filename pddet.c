/*
 *             COPYRIGHT (c) 1994 BY             *
 *  GEORGE J. CARRETTE, CONCORD, MASSACHUSETTS.  *
 *             ALL RIGHTS RESERVED               *

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all copies
and that both that copyright notice and this permission notice appear
in supporting documentation, and that the name of the author
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
HE BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

The purpose of this routine is to attempt to detect the use of
procedure descriptors by making a note of how far apart the
system allocates pointers to subroutines of different sizes.
If all the subroutines are the same distance apart then
procedure descriptors are probably in use on this architecture.

This file should be compiled without any compiler optimization
such as inlining that would confuse the test. Although base functions
have been made somewhat complex in order to avoid that in any case.

Now if a linker lays out procedures like this:

[DESCRIPTOR][CODE TEXT...][DESCRIPTOR][CODE TEXT...]

Then this code will be confused into thinking descriptors aren't used.
But usually the hallmark of a descriptor architecture is that descriptors
are in a table located away from the program code text.

The -examine <nbytes> argument lets you see in a crude way what
is contained in the pointer to a procedure data.

19-MAY-1994 GJC@WORLD.STD.COM

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct v {long n;double *a;};

struct v *vcons(n,x)
     long n;
     double x;
{struct v *p;
 long j;
 p = (struct v *) malloc(sizeof(struct v));
 p->n = n;
 p->a = (double *) malloc(sizeof(double)*n);
 for(j=0;j<n;++j) p->a[j] = x;
 return(p);}

struct v *vprod(x,y)
     struct v *x,*y;
{struct v *z;
 long j;
 z = vcons(x->n);
 for(j=0;j<x->n;++j) z->a[j] = x->a[j] * y->a[j];
 return(z);}

double vsume(x)
     struct v *x;
{double sum = 0.0;
 long j;
 for(j=0;j<x->n;++j) sum += x->a[j];
 return(sum);}

double viprod(x,y)
     struct v *x,*y;
{return(vsume(vprod(x,y)));}

double vnorm(x)
     struct v *x;
{return(viprod(x,x));}

double case10()
{double acc = 0.0;
 acc += vnorm(vcons((long)vsume(vcons(0,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(1,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(2,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(3,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(4,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(5,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(6,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(7,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(8,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(9,1.0)),2.0));
 return(acc);}

double case20()
{double acc = 0.0;
 acc += vnorm(vcons((long)vsume(vcons(0,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(1,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(2,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(3,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(4,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(5,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(6,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(7,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(8,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(9,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(10,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(11,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(12,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(13,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(14,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(15,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(16,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(17,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(18,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(19,1.0)),2.0));
 return(acc);}

double case30()
{double acc = 0.0;
 acc += vnorm(vcons((long)vsume(vcons(0,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(1,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(2,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(3,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(4,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(5,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(6,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(7,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(8,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(9,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(10,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(11,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(12,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(13,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(14,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(15,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(16,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(17,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(18,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(19,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(20,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(21,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(22,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(23,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(24,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(25,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(26,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(27,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(28,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(29,1.0)),2.0));
 return(acc);}

double case40()
{double acc = 0.0;
 acc += vnorm(vcons((long)vsume(vcons(0,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(1,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(2,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(3,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(4,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(5,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(6,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(7,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(8,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(9,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(10,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(11,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(12,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(13,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(14,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(15,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(16,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(17,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(18,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(19,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(20,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(21,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(22,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(23,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(24,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(25,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(26,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(27,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(28,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(29,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(30,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(31,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(32,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(33,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(34,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(35,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(36,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(37,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(38,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(39,1.0)),2.0));
 return(acc);}

double case50()
{double acc = 0.0;
 acc += vnorm(vcons((long)vsume(vcons(0,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(1,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(2,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(3,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(4,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(5,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(6,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(7,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(8,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(9,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(10,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(11,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(12,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(13,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(14,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(15,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(16,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(17,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(18,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(19,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(20,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(21,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(22,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(23,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(24,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(25,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(26,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(27,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(28,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(29,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(30,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(31,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(32,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(33,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(34,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(35,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(36,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(37,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(38,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(39,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(40,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(41,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(42,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(43,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(44,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(45,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(46,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(47,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(48,1.0)),2.0));
 acc += vnorm(vcons((long)vsume(vcons(49,1.0)),2.0));
 return(acc);}

void sayarch(x)
     char *x;
{printf("This architecture %s procedure descriptors\n",x);}


struct apair {char *name;unsigned long addr;};
struct adelt {long delta; long count;};

int apairl(a,b)
     struct apair *a,*b;
{if (a->addr < b->addr) return(-1);
 else if (a->addr > b->addr) return(1);
 else return(0);}

int adeltl(a,b)
     struct adelt *a,*b;
{if (a->delta < b->delta) return(-1);
 else if (a->delta > b->delta) return(1);
 else return(0);}

main(argc,argv)
     int argc;
     char **argv;
{struct apair all[10];
 struct adelt deltas[10];
 long j,k,n=10,min_delta,max_delta,delta,d,ebytes=0;
 unsigned char *data,*prev_data;
 for(j=1;(j+1)<argc;j += 2)
   {if (strcmp(argv[j],"-examine") == 0)
      ebytes = atol(argv[j+1]);}
 for(j=0;j<n;++j)
   {deltas[j].delta = 0;
    deltas[j].count = 0;}
 all[0].name = "vcons";
 all[0].addr = (unsigned long) vcons;
 all[1].name = "vprod";
 all[1].addr = (unsigned long) vprod;
 all[2].name = "vsume";
 all[2].addr = (unsigned long) vsume;
 all[3].name = "viprod";
 all[3].addr = (unsigned long) viprod;
 all[4].name = "vnorm";
 all[4].addr = (unsigned long) vnorm;
 all[5].name = "case10";
 all[5].addr = (unsigned long) case10;
 all[6].name = "case20";
 all[6].addr = (unsigned long) case20;
 all[7].name = "case30";
 all[7].addr = (unsigned long) case30;
 all[8].name = "case40";
 all[8].addr = (unsigned long) case40;
 all[9].name = "case50";
 all[9].addr = (unsigned long) case50;
 if (ebytes > 0)
   {printf("%10s %10s %s\n","procedure","address","examine");
    for(j=0;j<n;++j)
      {printf("%10s %10d ",all[j].name,all[j].addr);
       data = (unsigned char *) all[j].addr;
       if (j > 0)
	 prev_data = (unsigned char *) all[j-1].addr;
       else
	 prev_data = NULL;
       for(k=0;k<ebytes;++k)
	 if (prev_data && (prev_data[k] == data[k]))
	   printf("..");
	 else
	   printf("%02X",data[k]);
       printf("\n");}}
 qsort(all,n,sizeof(struct apair),apairl);
 printf("%10s %10s %10s\n","procedure","address","delta");
 for(j=0;j<n;++j)
   {if (j>0)
      {delta = all[j].addr - all[j-1].addr;
       if (j == 1)
	 min_delta = max_delta = delta;
       else
	 {if (delta < min_delta) min_delta = delta;
	  if (delta > max_delta) max_delta = delta;}
       for(k=0;k<n;++k)
	 if(deltas[k].count == 0)
	   {deltas[k].delta = delta;
	    deltas[k].count = 1;
	    break;}
	 else if(deltas[k].delta == delta)
	   {++deltas[k].count;
	    break;}}
    else
      delta = 0;
    printf("%10s %10d %10d\n",all[j].name,all[j].addr,delta);}
 printf("min_delta = %d, max_delta = %d\n",min_delta,max_delta);
 if (min_delta == max_delta)
   sayarch("probably uses");
 else
   {qsort(deltas,n,sizeof(struct adelt),adeltl);
    printf("%10s %s\n","delta","count");
    for(d=0,k=0;k<n;++k)
      if (deltas[k].count > 0)
	{printf("%10d %d\n",deltas[k].delta,deltas[k].count);
	 ++d;}
    if (d > 4)
      sayarch("probably does not use");
    else
      sayarch("may be using");}
return(EXIT_SUCCESS);}
