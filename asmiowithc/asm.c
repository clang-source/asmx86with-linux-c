

#include <stdio.h>


static void asignValueDevide(){
	
	int a =100;
	__asm__ __volatile__(
		"mov $2000,%eax"
	);
	__asm__ __volatile__(
		"mov %%eax,%0"
		:"=r"(a)
	);
	printf("asm output result, a=%d\n",a);
}

static void asignValueCompose(int input){
	
	int a =100;
	int ret =0;
	
	__asm__ __volatile__(
		"movl %1,%%eax;\
		 movl %2,%%ebx;\
		 addl %%eax,%%ebx;\
		 movl %%ebx,%0;"\
		 //上面出现了就寄存器，输入输出部，就不能使用了，否则报错
		 /*
		 asm.c:24:2: error: ‘asm’ operand has impossible constraints
			__asm__ __volatile__(
		 **/
		:"=r"(ret)
		:"m"(input),"m"(a)
		:"eax","ebx","memory"
	);

	printf("asm output result, a=%d\n",ret);
}

int main(int argc,const char *argvs[]){

asignValueCompose(10);


	return 0;
}












