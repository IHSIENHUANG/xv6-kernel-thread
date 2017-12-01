#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
int main ( int argc , char * argv [])
{

	int size = 4096;
	int* stack[3];
	int i = 0 ;
	static int output=0;//it's really necessry to use static, since the variable are shared between the threads
	printf(1,"@@@@@@@@ %d\n",getpid);
	for(i=0;i<3;i++)
	{
		stack[i]  = (int*)malloc(size*sizeof(int));
	}
	int child_pid = clone(stack[0],size);
	if(child_pid !=0)
	{
		child_pid = clone(stack[1],size);
	}
#if DEBUG
	if(child_pid >0)
		printf(1,"parent's pid num is %d\n",getpid());
	if(child_pid ==0)
		printf(1,"child's pid num is %d\n",getpid());
#endif
	lock_init(lock);
#if DEBUD
	printf(1,"lock_test = %d\n",lock->locked);
#endif 
	lock_acquire(lock);
	{
		printf(1,"output : %d\n",output);
		output++;
	}
	lock_release(lock);
	if(child_pid>0)
	{
		wait();
		wait();
	}
	exit ();
}
