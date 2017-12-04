/*
   this time use atomic operation to implement seqlokc
   reader always read until the writer finished 
   therefore it will improve the performance for the reason that reader do not stuck on the spinlock 
   */
#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
//static int output =0;
static int numofthread;
static int passnum;
//static int workpid=0;//this time should be no workpid's time to work
//static int *flag ;
void* worker();
int main ( int argc , char * argv [])
{
	numofthread =atoi(argv[1]);// num of threads is decided by the parameter passed by user
	passnum = atoi(argv[2]);
	int i = 0 ;

	printf(1,"DEBUG\n");
	seqlock_init(lock);
	for(i=0;i<numofthread;i++)
	{
		thread_create(worker,(void *)i);
	}
	int round =0;
	while(1)
	{
		seqlock_writer(lock);
		if(++round>passnum)break;
	//	printf(1,"writer a new num \n");	
	}
	wait();
	exit();
}
/*worker is thr function passed into the threads
 * each thread after created will do the function
 * arg is the parameter passed into the thread_create
 * and make "arg" as the id of each thread
 * in while loop every thread acquire the lock and the thread get the lock stil need to check pid num
 * 1 pass token to 2,2 to 3 and so on.
 * if the thread get the lock does not the thread should work
 * it will sleep and release the lock
 * */
void* worker(void *arg)
{
	int pidnum = (int)arg;
	int value =0;
	while(value<passnum)//when pass time  bigger than it should be passed
	{
		value = reader(lock,pidnum);//make sure the right id get the value
		if(value > passnum)
			break;
		int nextnum = pidnum+1;
		if(nextnum==20)	nextnum=0;
		printf(1,"pass number no:%d is thread %d is passing the token to %d\n",value,pidnum,nextnum);
		lock_release(lock);
	}
	lock_release(lock);
	printf(1,"time to end\n");
	sleep(5);
	exit();
}

