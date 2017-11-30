#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
int main ( int argc , char * argv [])
{
	
	int size = 4096;
	int* stack[3];
	int i = 0 ;
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
	if(child_pid >0)
		printf(1,"parent's pid num is %d\n",getpid());
	if(child_pid ==0)
		printf(1,"child's pid num is %d\n",getpid());

	wait();
	wait();
	exit ();
}
