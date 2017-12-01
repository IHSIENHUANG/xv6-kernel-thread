#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
int main ( int argc , char * argv [])
{
	int pid;//retrun from clone
	static int numofthread =10;
	int size = 4096;
	int* stack[9];
	int i = 0 ;
	static int output=0;//it's really necessry to use static, since the variable are shared between the threads
	printf(1,"@@@@@@@@ %d\n",getpid);
	for(i=0;i<9;i++)
	{
		stack[i]  = (int*)malloc(size*sizeof(int));
		pid = clone(stack[i],size);
		if(pid==0)//only parent do the copy
			break;
	}
#if DEBUG
	if(pid >0)
		printf(1,"parent's pid num is %d\n",getpid());
	if(pid ==0)
		printf(1,"child's pid num is %d\n",getpid());
#endif
	lock_init(lock);
	
#if DEBUD
	printf(1,"lock_test = %d\n",lock->locked);
#endif 
	lock_acquire(lock);
		printf(1,"output : %d\n",output);
		output++;
	lock_release(lock);
	numofthread--;
	while(1)
	{
		if(numofthread==0) goto LEAVING;
	}
	LEAVING:
        //lock_acquire(lock);
        	printf(1,"time to leave\n");
		exit();
	//lock_release(lock);	
	
}
