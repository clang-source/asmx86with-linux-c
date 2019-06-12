#include <stdio.h>

//success
int diy_add1(int a, int b){

    int ret;
    __asm__ __volatile__("movl %2, %%eax;movl %1, %%ebx;addl %%ebx, %%eax;movl %%eax, %0"       
                :"=m"(ret)
                :"m"(a),"m"(b)
                :"eax","ebx","memory"
                );
    return ret;
}

//success
int user_add0(int a,int b){
	int ret =0;
	
	////lock ;movl %1,%%eax ; 加lock wrong，因为lock有针对性的某些指令 比如 x开头的指令，addl inc subl dec 等操作
	__asm__ __volatile__(
		"   movl %1,%%eax ;\
		    movl %2,%%ebx;\
			addl %%eax,%%ebx;\
			movl %%ebx,%0"
			:"=m"(ret)
			:"m"(a),"r"(b)   
			:"eax","ebx","memory"
	);
	return  ret;
}

int user_add2(int a){
	int ret =0;
	int c =100;

	__asm__ __volatile__(
		"xaddl %2 ,%1; "  //"lock;addl %2 ,%1; " 控制台 报错：非法指令 (核心已转储) ，所以直接换成带x的指令类型
		:"=a"(ret)		
		:"0"(a),"r"(c)
		:"memory","cc"
		);
	
	return ret;
}


//inline 版函数实现
int main(int argc,const char *argvs[]){

  	int a=10,b=100;
	int ret=0;
//success
/****
	__asm__ volatile(
		"movl %1,%%eax;  movl %2,%%ebx;addl %%eax,%%ebx;mov %%ebx,%0"
		:"=r"(ret)
		:"m"(a),"m"(b)
		:"eax","ebx","memory"
	);
****/
	printf("res= %d\n",user_add2(a));
	return 0;
}



