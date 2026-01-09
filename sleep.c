#define SYS_write 1 
#define SYS_exit 60
#define SYS_nanosleep 35 

typedef struct timespec {
	long tv_sec; 
	long tv_nsec; 
} timespec;

// we named this function syscall1 because 1 represent the number of args this function takes 
// if this function takes 2 arguments then we would call it syscall2 and so on until we reach 6.
long syscall1(long number, long arg1){
		long result; 
		__asm__ __volatile__(
			"syscall"
			: "=a" (result)
			: "a" (number), "D" (arg1)
			: "rcx", "r11", "memory"
				);

		return result;
}
long syscall2(long number, long arg1, long arg2){
		long result; 
		__asm__ __volatile__(
			"syscall"
			: "=a" (result)
			: "a" (number), "D" (arg1), "S" (arg2)
			: "rcx", "r11", "memory"
				);

		return result;
}
long syscall3(long number, long arg1, long arg2, long arg3){
		long result; 
		__asm__ __volatile__(
			"syscall"
			: "=a" (result)
			: "a" (number), "D" (arg1), "S" (arg2), "d" (arg3)
			: "rcx", "r11", "memory"
				);

		return result;
}


int parse_int(char *raw_int){
  int result = 0; 
  char *cursor = raw_int;

  while (*cursor >= '0' && *cursor <= '9') {
    result = result * 10 + (*cursor - '0');
    cursor ++;
  }

  return result; 
}

long unsigned strlen(char *string){
	char *cursor = string;
	while(*cursor){
		cursor++;
	}
	long unsigned result = cursor - string;
	return result;
}


int print(char *string){
	syscall3(SYS_write,1, (long) string , strlen(string));
}

void sleep(long seconds){
	timespec duration = {0};
	duration.tv_sec = seconds; 
	syscall2(SYS_nanosleep, (long)(&duration) , 0);	
}

int main(int argc , char *argv[]){
  if (argc != 2) {
    print("Usage: sleep NUMBER\n Pause for NUMBER seconds \n");
    return 1;
  }
  char *raw_seconds = argv[1];
  long seconds = parse_int(raw_seconds);

  print("sleeping for ");
  print(raw_seconds);
  print(" seconds \n");
  sleep(seconds);
  return 0;
}

void exit(int code){
	syscall1(SYS_exit, code);

	for(;;) {}
}



__attribute__((naked)) void _start(){
  __asm__ __volatile__(
		  "xor %ebp, %ebp\n"
		  "mov (%rsp), %rdi\n"
		  "lea 8(%rsp), %rsi\n"
		  "and $-16, %rsp\n"
		  "call main\n"
		  "mov %rax, %rdi\n"
		  "call exit\n"
	);
}
