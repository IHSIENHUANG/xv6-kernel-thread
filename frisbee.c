#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
static int output =0;
static int numofthread;
static int passnum;
static int workpid=0;//this time should be no workpid's time to work
void* worker();
int main ( int argc , char * argv [])
{
	numofthread =atoi(argv[1]);// num of threads is decided by the parameter passed by user
	passnum = atoi(argv[2]);
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
	int pidnum = getpid()-4;
#if DEBUG
	printf(1,"child's pid num is %d\n",pidnum);
#endif
	while(output<=passnum)//when pass time  bigger than it should be passed
	{
		lock_acquire(lock);
		if(output>passnum)
			break;
		if(pidnum==workpid)
		{
			
			output++;
			printf(1,"pass number no:%d is thread %d is passing the token to ",output,pidnum);
			workpid++;
			if(workpid ==  numofthread)// because thread num is start from 0 
				workpid = 0 ;	
			printf(1," %d\n",workpid);
			lock_release(lock);
			sleep(1);
		}
		else
		{
			lock_release(lock);
			sleep(1);
		}
	}
	printf(1,"time to end\n");
	exit();
}

