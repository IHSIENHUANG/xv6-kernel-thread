#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
static int output =0;
static int numofthread;
//static int passnum=0;
//static pidnum =4;
void* worker();
int main ( int argc , char * argv [])
{
	numofthread =10;
	int i = 0 ;
	lock_init(lock);
	for(i=0;i<numofthread;i++)
	{
		//	stack[i]  = (int*)malloc(size*sizeof(int));
		thread_create(worker,(void *)0);

	}
	wait();
	exit();
#if DEBUG
	if(pid >0)
		printf(1,"parent's pid num is %d\n",getpid());
	if(pid ==0)
		printf(1,"child's pid num is %d\n",getpid());
#endif


#if DEBUD
	printf(1,"lock_test = %d\n",lock->locked);
#endif 
	/*lock_acquire(lock);
	  printf(1,"output : %d\n",output);
	  output++;
	  numofthread--;
	  lock_release(lock);	
	  */
}
void* worker()
{
	//lock_init(&ttable.lock);
	printf(1,"child's pid num is %d\n",getpid());
	while(1)
	{
		lock_acquire(lock);
		output++;
		printf(1,"pass number no:%d is thread %d is passing the token to ",output,getpid());
		printf(1," %d\n",getpid()+1);
		lock_release(lock);
		sleep(5);
	}
	while(output!=10);
	printf(1,"time to end\n");
	exit();
}

