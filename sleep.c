#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int parse_int(char *raw_int){
  int result = 0; 
  char *cursor = raw_int;

  while (*cursor >= '0' && *cursor <= '9') {
    result = result * 10 + (*cursor - '0');
    cursor ++;
  }

  return result; 
}



int main(int argc , char *argv[]){
  if (argc != 2) {
    printf("Usage: sleep NUMBER\n Pause for NUMBER seconds \n");
    return 1;
  }
  char *raw_seconds = argv[1];
  long seconds = parse_int(raw_seconds);

  printf("sleeping for %d seconds \n",seconds);
  sleep(seconds);
  return 0;
}

void _start(){
  long rsp;

  __asm__ __volatile__("mov %%rsp, %0" : "=r" (rsp));
  long argc = *(long *)rsp; 
  char **argv = (char **)(rsp + 8);

  main((int)argc , argv);
}



















