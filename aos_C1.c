#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define SIZE 50000000
#define BLOCK 8
#define QO SIZE/BLOCK

typedef struct {
  float a,b,c,d,e,f,g,h;
} s_t;

typedef struct {
  float gtmp;
} s_t_temp;




void init_bd_gtmp(s_t_temp *btmp, s_t_temp *dtmp, int i){
  int j, jj, jjj;
  j = (i-1)*BLOCK;
  for(jj=0; jj<BLOCK; jj++){
    jjj = j+jj;
    btmp[jj].gtmp=dtmp[jj].gtmp=1./(jjj+1);
    //fprintf(stderr,"jjj= %d  co= %f a[%d].a= %f \n",jjj, 1./(jjj+1), jj,   a[jj].a);
  }
}

  void init_s_t(s_t *a, int i){
    int j, jj, jjj;
    j = (i-1)*BLOCK;
    for(jj=0; jj<BLOCK; jj++){
      jjj = j+jj;
      a[jj].a=a[jj].b=a[jj].c=a[jj].d=a[jj].e=a[jj].f=a[jj].g=a[jj].h=1./(jjj+1);
      //fprintf(stderr,"jjj= %d  co= %f a[%d].a= %f \n",jjj, 1./(jjj+1), jj,   a[jj].a);
    }
  }

void wr_time(int echo, double sum_main, double sum){
  int j;
  FILE *fpp;
  fpp = fopen ("time.txt", "a");
  if(echo == 0){fputs("temps cpu:    main          func compute   \n", fpp );}
  else{fprintf(fpp, "aos_C1.c %f   %f  \n", sum_main, sum );}
  fclose(fpp);
}

void wr(s_t *a){
  int j;
  FILE *fp;
  fp = fopen ("val_C1.txt", "a");
  fputs("j    .a          .b         .d   \n", fp );

  for(j=0; j<BLOCK; j++){
    fprintf(fp, "%d   %f   %f   %f \n",j, a[j].a,a[j].b,a[j].d );
  }
  fclose(fp);
}
void compute(s_t *a) {
  int i;
  for (i=4; i<8; i++) {//boucle elements
    a[i].a=(a[i-1].b * 0.42 + a[i-3].d * .32);
    //fprintf(stderr,"B47 i=%d %f %f %f %f\n",i,a[i].a,a[i-1].b,a[i-3].d,0.42*a[i-1].b+0.32*a[i-3].d);
    a[i].b = a[i].c / 7.56+ a[i].f;
    a[i].c = a[i].d + a[i].g*a[i].d;
    a[i].d = .567111/sqrt(a[i].f*a[i].f + a[i].h*a[i].h);
    a[i].e*=exp(-a[i].d);
    if (a[i].f + a[i].g>1e-3)
      a[i].f = (a[i].f - a[i].g)*(a[i].f + a[i].g);
    a[i].g = a[i-4].g + .1;
    a[i].h = .3*a[i].h + .2;
  }
}
void compute_s_t(s_t *a, s_t_temp *gtmp, s_t_temp *btmp, s_t_temp *dtmp, int it) {
int i, j;
int temps;
for(temps=0; temps<100; temps++){//boucle temps

    for(j=0;j<BLOCK-1;j++){btmp[j].gtmp=a[j].c / 7.56+ a[j].f;}
    for(j=0;j<BLOCK-3;j++){dtmp[j].gtmp=.567111/sqrt(a[j].f*a[j].f + a[j].h*a[j].h);}
    //a[i].a=(a[i-1].b * 0.42 + a[i-3].d * .32);
    a[0].a=(btmp[7].gtmp * 0.42 + dtmp[5].gtmp * .32);
    //fprintf(stderr,"$$temps= %d a7.b %f a5.d %f \n", temps, btmp[7].gtmp, dtmp[5].gtmp);
    //fprintf(stderr, "temps= %d \n",temps);
    //a[0].a=(a[3].b * 0.42 + a[1].d * .32);
    //fprintf(stderr, "%d   %f   %f   %f \n",temps, a[0].a,a[3].b,a[1].d );
    a[1].a=(btmp[0].gtmp * 0.42 + dtmp[6].gtmp * .32);
    a[2].a=(btmp[1].gtmp * 0.42 + dtmp[7].gtmp * .32);
    a[3].a=(btmp[2].gtmp * 0.42 + dtmp[0].gtmp * .32);
    //fprintf(stderr,"!!temps= %d a2.b %f a0.d %f \n", temps, a[2].b, a[0].d);
    a[4].a=(btmp[3].gtmp * 0.42 + dtmp[1].gtmp * .32);
    //fprintf(stderr, "%d   %f   %f   %f \n",temps, a[4].a,a[3].b,a[1].d );
    a[5].a=(btmp[4].gtmp * 0.42 + dtmp[2].gtmp * .32);
    //fprintf(stderr,"??temps= %d a4.b %f a0.d %f \n", temps, a[4].b, a[4].d);
    a[6].a=(btmp[5].gtmp * 0.42 + dtmp[3].gtmp * .32);
    a[7].a=(btmp[6].gtmp * 0.42 + dtmp[4].gtmp * .32);

    //a[i].b = a[i].c / 7.56+ a[i].f;
    a[0].b = a[0].c / 7.56+ a[0].f;
    a[1].b = a[1].c / 7.56+ a[1].f;
    a[2].b = a[2].c / 7.56+ a[2].f;
    a[3].b = a[3].c / 7.56+ a[3].f;
    a[4].b = a[4].c / 7.56+ a[4].f;
    a[5].b = a[5].c / 7.56+ a[5].f;
    a[6].b = a[6].c / 7.56+ a[6].f;
    a[7].b = a[7].c / 7.56+ a[7].f;

//SWAP:
  //for(j=0;j<BLOCK;j++){btmp[j].gtmp=a[j].b;}
  //fprintf(stderr,"temps= %d a7.b %f a5.d %f \n", temps, a[7].b, a[5].d);

    //a[i].c = a[i].d + a[i].g*a[i].d;
    a[0].c = a[0].d + a[0].g*a[0].d;
    a[1].c = a[1].d + a[1].g*a[1].d;
    a[2].c = a[2].d + a[2].g*a[2].d;
    a[3].c = a[3].d + a[3].g*a[3].d;
    a[4].c = a[4].d + a[4].g*a[4].d;
    a[5].c = a[5].d + a[5].g*a[5].d;
    a[6].c = a[6].d + a[6].g*a[6].d;
    a[7].c = a[7].d + a[7].g*a[7].d;


    //a[i].d = .567111/sqrt(a[1].f*a[i].f + a[i].h*a[i].h);
    /*a[].d = .567111/sqrt(a[].f*a[].f + a[].h*a[].h);*/
    a[0].d = .567111/sqrt(a[0].f*a[0].f + a[0].h*a[0].h);
    a[1].d = .567111/sqrt(a[1].f*a[1].f + a[1].h*a[1].h);
    a[2].d = .567111/sqrt(a[2].f*a[2].f + a[2].h*a[2].h);
    a[3].d = .567111/sqrt(a[3].f*a[3].f + a[3].h*a[3].h);
    a[4].d = .567111/sqrt(a[4].f*a[4].f + a[4].h*a[4].h);
    a[5].d = .567111/sqrt(a[5].f*a[5].f + a[5].h*a[5].h);
    a[6].d = .567111/sqrt(a[6].f*a[6].f + a[6].h*a[6].h);
    a[7].d = .567111/sqrt(a[7].f*a[7].f + a[7].h*a[7].h);

    //SWAP:
    //  for(j=0;j<BLOCK;j++){dtmp[j].gtmp=a[j].d;}

    //a[i].e*=exp(-a[i].d);
    a[0].e *= exp(-a[0].d);
    a[1].e *= exp(-a[1].d);
    a[2].e *= exp(-a[2].d);
    a[3].e *= exp(-a[3].d);
    a[4].e *= exp(-a[4].d);
    a[5].e *= exp(-a[5].d);
    a[6].e *= exp(-a[6].d);
    a[7].e *= exp(-a[7].d);

    for(i=0; i<BLOCK; i++){
      //if (a[i].f + gm[i].gtmp>1e-3){a[i].f = (a[i].f - gm[i].gtmp)*(a[i].f + gm[i].gtmp);}
      if (a[i].f + a[i].g>1e-3){a[i].f = (a[i].f - a[i].g)*(a[i].f + a[i].g);}
    }

    //a[i].g = a[i-4].g + .1;
    a[0].g = gtmp[0].gtmp + 0.1;
    a[1].g = gtmp[1].gtmp + 0.1;
    a[2].g = gtmp[2].gtmp + 0.1;
    a[3].g = gtmp[3].gtmp + 0.1;
    a[4].g = gtmp[4].gtmp + 0.1;
    a[5].g = gtmp[5].gtmp + 0.1;
    a[6].g = gtmp[6].gtmp + 0.1;
    a[7].g = gtmp[7].gtmp + 0.1;
    //gtmp[0:7].gtmp = a[0:7].g;
    /*gtmp[0].gtmp = a[4].g;
    gtmp[1].gtmp = a[5].g;
    gtmp[2].gtmp = a[6].g;
    gtmp[3].gtmp = a[7].g;
    gtmp[4].gtmp = a[4].g//+ .1;
    gtmp[5].gtmp = a[5].g//+ .1;
    gtmp[6].gtmp = a[6].g//+ .1;
    gtmp[7].gtmp = a[7].g//+ .1;*/

    //a[i].h = .3*a[i].h + .2;
    a[0].h = .3*a[0].h + .2;
    a[1].h = .3*a[1].h + .2;
    a[2].h = .3*a[2].h + .2;
    a[3].h = .3*a[3].h + .2;
    a[4].h = .3*a[4].h + .2;
    a[5].h = .3*a[5].h + .2;
    a[6].h = .3*a[6].h + .2;
    a[7].h = .3*a[7].h + .2;
//wr(a);
    //for(j=0;j<BLOCK;j++){fprintf(stderr,"temps= %d [8:15] j=%d a.a %f a.h %f \n", temps, j, a[j].a, a[j].h);}
  }

}

int main() {
  int i, j;
  float percent;
  int echo;
  clock_t tm1, tm2, tc1, tc2;
  double sum_main, sum;
  s_t *a;
  s_t_temp *gtmp, *btmp, *dtmp;
  a    = (s_t *)malloc(sizeof(s_t)*BLOCK);
  gtmp = (s_t_temp *)malloc(sizeof(s_t_temp)*BLOCK);
  btmp   = (s_t_temp *)malloc(sizeof(s_t_temp)*BLOCK);
  dtmp   = (s_t_temp *)malloc(sizeof(s_t_temp)*BLOCK);
  tm1 = tm2 = tc1 = tc2 = sum = sum_main = 0.0;
  echo = 0;
  wr_time(echo, sum_main, sum);
  /* Initialization */
  init_s_t(a, 1);
   //wr(a);
  //boucle temps
  for(i=0;i<100;i++){
    /*fprintf(stderr,"temps= %d a7.b %f a5.d %f \n", i, a[7].b, a[5].d);
    fprintf(stderr,"!!temps= %d a2.b %f a0.d %f \n", i, a[2].b, a[0].d);
    fprintf(stderr,"??temps= %d a4.b %f a4.d %f \n", i, a[4].b, a[4].d);*/
    compute(a);
    //wr(a);
    //for(j=0;j<BLOCK;j++){fprintf(stderr,"temps= %d [0:7] j=%d a.h %f a.f %f \n", i, j, a[j].a, a[j].h);}
  }
  tm1 = clock();
  /* Computation */
  for(i=2;i<QO+1;i++) {//boucle elements
    /*INITIALIZATION*/
    btmp[7].gtmp = a[7].b;
    dtmp[7].gtmp = a[7].d;
    dtmp[6].gtmp = a[6].d;
    dtmp[5].gtmp = a[5].d;
    gtmp[0].gtmp = a[4].g;
    gtmp[1].gtmp = a[5].g;
    gtmp[2].gtmp = a[6].g;
    gtmp[3].gtmp = a[7].g;
    gtmp[4].gtmp = a[4].g+0.1;
    gtmp[5].gtmp = a[5].g+0.1;
    gtmp[6].gtmp = a[6].g+0.1;
    gtmp[7].gtmp = a[7].g+0.1;
    init_s_t(a, i);
    //init_bd_gtmp(btmp, dtmp, i-1);
    /*gtmp[0].gtmp = a[0].g+ .1;
    gtmp[1].gtmp = a[1].g+ .1;
    gtmp[2].gtmp = a[2].g+ .1;
    gtmp[3].gtmp = a[3].g+ .1;
    gtmp[4].gtmp = a[0].g+ .2;
    gtmp[5].gtmp = a[1].g+ .2;
    gtmp[6].gtmp = a[2].g+ .2;
    gtmp[7].gtmp = a[3].g+ .2;*/
    //for(j=0;j<BLOCK;j++){fprintf(stderr,"B816 j gtmp.gtmp  j=%d %f \n", j, gtmp[j].gtmp);}
    //fprintf(stderr,"a[%d].a= %f \n", 2,   a[2].a);
    //gtmp[].gtmp = a[].g; //already swap by init_s_t?!

    tc1 =clock();
    //for(j=0;j<BLOCK;j++){fprintf(stderr,"B816 av compute a.g j=%d %f \n", j, a[j].g);}
    compute_s_t(a, gtmp, btmp, dtmp, i);

    //for(j=0;j<BLOCK;j++){fprintf(stderr,"B816 j=%d %f %f \n", j, a[j].a, a[j].g);}

    //if(i==1){
    //fprintf(stderr,"!!! a[%d].a= %f \n", 2,   a[2].a);
      //fprintf(stderr,"%f ",a[2].a);
      //fprintf(stderr,"\n");
    //}
    tc2 =clock();
    if((i == 2) ){fprintf(stderr,"%f \n",a[2].a);}
    sum = sum + ( (double) (tc2-tc1) ) /CLOCKS_PER_SEC ;
    if((i % 10000)==0 ){
      percent = (i* (float) 100) / ((float) QO);
      fprintf(stderr,"\r TPS CODE= %f In progress %f %% ",sum, percent);fflush(stdout);
    }

  }
  tm2 = clock();
  sum_main = ((double) (tm2-tm1))/CLOCKS_PER_SEC;
  fprintf(stderr,"\n");
  //fprintf(stderr,"%f ",a[2].a);
  //fprintf(stderr,"\n");
  fprintf(stderr, "alloc a==s_t: %ld \n",sizeof(s_t)*BLOCK+3*sizeof(s_t_temp)*BLOCK );
  /*for(i=0; i<SIZE; i++){
  fprintf(stderr, "%d   %f   %f   %f \n",i, a[i].a,a[i].b,a[i].c );}
  wr(a);*/
  echo=1;
  wr_time(echo, sum_main, sum);
  free(a);
  free(gtmp);
  free(btmp);
  free(dtmp);
  return 0;
}
