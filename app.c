#include <stdio.h>
#define M_PI 3.141

int main(){
  #pragma omp parallel pthread_create(&TID,Null,&myfme,Nuce);
  printf("My PID %d",getpid());
  return EXIT_SUCCESS;
}