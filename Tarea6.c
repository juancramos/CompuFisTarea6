#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

float funcion_x(float x, float y, float z);
float funcion_y(float x, float y, float z);
float funcion_z(float x, float y, float z);
float *runge_kutta_step(float h, float t, float x, float y, float z);


int main(void){
	/*define el paso del método como 0.01, es el paso con el que el método avanza*/
  float h=0.01;
  /*contadores*/
  int i;
  int j;
  int n_points;
  float *t;
  float *x;
  float *y;
  float *z;
  float *num_rand;
  FILE *fileout;
  float slope_x;
  float slope_y;
  float slope_z;
    
/*establece tantos intervalos como quepan en 30 y suma 1, en este caso (con 0.01) serán 3000*/
  n_points = (int)((30.0+h)/h);

/*inicialice las variables que conservan el punto actual en 3 dimensiones y tiempo*/
  t = malloc(n_points * sizeof(float));
  x = malloc(n_points * sizeof(float));
  y = malloc(n_points * sizeof(float));
  z = malloc(n_points * sizeof(float));
  num_rand = malloc(30 * sizeof(float));

  if(!t){
    printf("There is something wrong with t\n");
    exit(1);
  }

 if(!x){
    printf("There is something wrong with x\n");
    exit(1);
  }

 if(!y){
    printf("There is something wrong with y\n");
    exit(1);
  }

 if(!z){
    printf("There is something wrong with z\n");
    exit(1);
  }

 if(!num_rand){
    printf("There is something wrong with num_rand\n");
    exit(1);
  }

  for(i=0; i<30; i+=1){
       
      num_rand[i] = rand() % 20 - 10;
       printf("%f random \n ", num_rand[i]);
  }

/*inicializa las pendientes en cada una de las dimensiones*/
 slope_x = 0.0;
 slope_y = 0.0;
 slope_z = 0.0;
    int numDat=0;
    char numData[20];
    
 for(j=0; j<30; j+=3){

   t[0] =0.0;
   x[0] = num_rand[j];
   y[0] = num_rand[j+1];
   z[0] = num_rand[j+2];
     
     sprintf(numData, "%d", numDat);
     fileout = fopen(strcat(numData,"Data.dat"), "w");
     if(!fileout){
         printf("There is something wrong with Data.dat");
         exit(1);
     }

   for(i=0; i<n_points; i++){
       
       float *slopes;
       slopes = runge_kutta_step(h, t[i], x[i], y[i], z[i]);
       slope_x = slopes[0];
       slope_y = slopes[1];
       slope_z = slopes[2];

/*  calcula el método hasta que converge*/
     t[i+1] = t[i] + h;
     x[i+1] = x[i] + h*slope_x;
     y[i+1] = y[i] + h*slope_y;
     z[i+1] = z[i] + h*slope_z;
       
   
       fprintf(fileout, "%f %f %f %f\n", t[i], x[i], y[i], z[i]);  
   
   }
    
     numDat++;
     printf("%f %f %f %f se trabajo con las condiciones iniciales: \n ", t[0], x[0], y[0], z[0]);
 
     fclose(fileout);

 }
   
  return 0;

}


float *runge_kutta_step(float h, float t, float x, float y, float z){
/*el resultado de esta función es la pendiente para definit el siguiente punto*/
/*para cada dimensión se define una pendiente*/
  float *slope;
  float slope_x;
  float slope_y;
  float slope_z;
/*acá se tiene que definir un k de 1 a 4*/
/* para cada dimensión, por eso se declaran 12*/
  float kx_1;
  float kx_2;
  float kx_3;
  float kx_4;
  float ky_1;
  float ky_2;
  float ky_3;
  float ky_4;
  float kz_1;
  float kz_2;
  float kz_3;
  float kz_4;
/*... y se definen también 3 variables de tiempo*/
  float t1;
  float t2;
  float t3;
/*como este método funciona con 3 puntos en el intervalo (inicio, medio y fin)*/
 /*uno para cada dimensión */
  float x1;
  float x2;
  float x3;

  float y1;
  float y2;
  float y3;

  float z1;
  float z2;
  float z3;

/*k1 en runge kutta es simplemente la función sin alteraciones*/
  kx_1 = funcion_x(x,y,z);
  ky_1 = funcion_y(x,y,z);
  kz_1 = funcion_z(x,y,z);
/*el primer paso vuelve a ejecutar la función partiendo de los valores anteriores*/
/*k1, etc según la función definida, es una linealización con los k y recalcula los*/
 /* puntos en el espacio*/
  /*First step*/
  t1 = t + (h/2.0);
  x1 = x + (h/2.0)*kx_1;
  y1 = y + (h/2.0)*ky_1;
  z1 = z + (h/2.0)*kz_1;
/*los siguientes ks se encuentran evaluando la función con los nuevos puntos en el espacio*/
  kx_2 = funcion_x(x1,y1,z1);
  ky_2 = funcion_y(x1,y1,z1);
  kz_3 = funcion_z(x1,y1,z1);
/*así se siguen calculando entre ks y puntos hasta llegar a calcular la pendiente*/
  /*Second step*/
  t2 = t + (h/2.0);
  x2 = x + (h/2.0)*kx_2;
  y2 = y + (h/2.0)*ky_2;
  z2 = z + (h/2.0)*kz_2;

  kx_3 = funcion_x(x2,y2,z2);
  ky_3 = funcion_y(x2,y2,z2);
  kz_3 = funcion_z(x2,y2,z2);

  /*Third step*/
  t3 = t + h;
  x3 = x + h*kx_3;
  y3 = y + h*ky_3;
  z3 = z + h*kz_3;

  kx_4 = funcion_x(x3,y3,z3);
  ky_4 = funcion_y(x3,y3,z3);
  kz_4 = funcion_z(x3,y3,z3);
/*la pendiente se calcula promediando los ks obtenidos para cada dimensión según la definición del método,*/
/* en este caso en un runge kutta de cuarto orden */

  /*Fourth step*/
  slope_x = (kx_1 + 2.0*kx_2 + 2.0*kx_3 + kx_4)/6.0;
  slope_y = (ky_1 + 2.0*ky_2 + 2.0*ky_3 + ky_4)/6.0;
  slope_z = (kz_1 + 2.0*kz_2 + 2.0*kz_3 + kz_4)/6.0;

  slope = malloc(3 * sizeof(float));
  if(!slope){
    printf("There is something wrong with slope\n");
    exit(1);
  }
/*definición del arreglo para el resultado de la función*/
  slope[0] = slope_x;
  slope[1] = slope_y;
  slope[2] = slope_z;

  return slope;

}


/*definición de la función en x*/
float funcion_x(float x, float y, float z){

  return 10.0*(y-x);

}


/*definición de la función en y*/
float funcion_y(float x, float y, float z){

  return x*(28.0-z)-y;

}


/*definición de la función en z*/
float funcion_z(float x, float y, float z){

  return x*y-(8.0/3.0)*z;

}
