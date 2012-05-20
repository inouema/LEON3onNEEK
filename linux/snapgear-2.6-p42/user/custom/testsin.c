#include <math.h>
#include <stdlib.h>
 
int main(int argc,char **argv) {
  double i = 0.00;
  int j = 0; 
  printf("testsin:\n");
  while (i < 100.0) {
    double v = sin(i);  
    printf("float:sin(%f)=%f\n",i,v);
    i = i + 1.0;  
   }  
  printf("exit testsin\n");
  return 0;
} 
