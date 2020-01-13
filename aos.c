#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SIZE 50000000

typedef struct {
  float a,b,c,d,e,f,g,h;
} s_t;

void wr_time(int echo, double sum_main, double sum){
  int j;
  FILE *fpp;
  fpp = fopen ("time.txt", "a");
  if(echo == 0){fputs("temps cpu:    main          func compute   \n", fpp );}
  fprintf(fpp, " aos.c %f   %f  \n", sum_main, sum );
  fclose(fpp);
}

void wr(s_t *a){
  int j;
  FILE *fp;
  fp = fopen ("val.txt", "a");
  fputs(" j    .a          .b         .d   \n", fp );

  for(j=0; j<32; j++){
    fprintf(fp, "%d   %f   %f   %f \n",j, a[j].a,a[j].b,a[j].d );
  }
  fclose(fp);
}

void compute(s_t *a) {
  int i;
  for (i=4; i<SIZE; i++) {//boucle elements
    a[i].a=(a[i-1].b * 0.42 + a[i-3].d * 0.32);
    //fprintf(stderr,"wwi=%d %f %f %f %f\n",i,a[i].a,a[i-1].b,a[i-3].d,0.42*a[i-1].b+0.32*a[i-3].d);
    a[i].b = a[i].c / 7.56+ a[i].f;
    a[i].c = a[i].d + a[i].g*a[i].d;
    a[i].d = .567111/sqrt(a[i].f*a[i].f + a[i].h*a[i].h);
    a[i].e*=exp(-a[i].d);
    //fprintf(stderr,".g  %f \n",a[i].g);
    if (a[i].f + a[i].g>1e-3){a[i].f = (a[i].f - a[i].g)*(a[i].f + a[i].g);}
    //fprintf(stderr,". i= %d i-4= %d gi-4 %f gi %f bi %f di %f \n",i,i-4,a[i-4].g,a[i].g,a[i].b,a[i].d);
    a[i].g = a[i-4].g + .1;
    //fprintf(stderr,". apres i= %d i-4= %d gi-4 %f gi %f bi %f di %f \n",i,i-4,a[i-4].g,a[i].g,a[i].b,a[i].d);
    //fprintf(stderr,".g  %f \n",a[i].g);
    a[i].h = .3*a[i].h + .2;
  }
}

int main() {
  int i,j;
  float percent;
  clock_t tm1, tm2, tc1, tc2;
  double sum_main, sum;
  s_t *a;
  a=(s_t *)malloc(sizeof(s_t)*SIZE);
  tm1 = tm2 = tc1 = tc2 = sum = 0.0;
  /* Initialization */
  tm1 = clock();
  for (i=0; i<SIZE; i++){a[i].a=a[i].b=a[i].c=a[i].d=a[i].e=a[i].f=a[i].g=a[i].h=1./(i+1);}
    //fprintf(stderr,"%f %f %f %f\n",a[8].a,a[7].b,a[5].d,0.42*a[7].b+0.32*a[5].d);
    //wr(a);
  /* Computation */
  for(i=0;i<100;i++) {//boucle temps
    tc1 =clock();
    //fprintf(stderr,".g av compute  %f \n",a[8].g);
    //for(j=0;j<2*8;j++){fprintf(stderr,"temps= %d j=%d a.b %f a.d %f \n", i, j, a[j].b, a[j].d);}
    compute(a);
    //wr(a);
    //for(j=0;j<2*8;j++){fprintf(stderr,"temps= %d  j=%d a.a %f a.h %f \n", i, j, a[j].a, a[j].h);}
    tc2 =clock();
    sum = sum + ( (double) (tc2-tc1) ) /CLOCKS_PER_SEC ;
    if((i % 10)==0 ){
      percent = (i* (float) 100) / ((float) 99);
      fprintf(stderr,"\r TPS CODE= %f In progress %f %% ",sum, percent);fflush(stdout);
    }
    //fprintf(stderr,".");
    //fprintf(stderr,"*** %f %f %f %f\n",a[8].a,a[7].b,a[5].d,0.42*a[7].b+0.32*a[5].d);
  }
  tm2 = clock();
  sum_main = ((double) (tm2-tm1))/CLOCKS_PER_SEC;
  fprintf(stderr,"%f ",a[10].a);
  fprintf(stderr,"\n");
  fprintf(stderr, "alloc a==s_t: %ld\n",sizeof(s_t)*SIZE );
  /*for(i=0; i<SIZE; i++){
  fprintf(stderr, "%d   %f   %f   %f \n",i, a[i].a,a[i].b,a[i].c );}
  wr(a);*/
  int echo=1;
  wr_time(echo, sum_main, sum);
  free(a);
  return 0;
}
