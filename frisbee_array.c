/*
this time use atomic operation to implement the array bese lock
Therefore, we do not need to check in the function
it will directly checht int the aquire
*/
#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
static int output =0;
static int numofthread;
static int passnum;
//static int workpid=0;//this time should be no workpid's time to work
static int *flag ;
void* worker();
int main ( int argc , char * argv [])
{
        numofthread =atoi(argv[1]);// num of threads is decided by the parameter passed by user
        passnum = atoi(argv[2]);
        int i = 0 ;
	int *flag = malloc((600)*sizeof(int));//flag should be 1-20 not 0->19
	printf(1,"DEBUG\n");
        array_lock_init(lock,&flag[0]);
        for(i=0;i<numofthread;i++)
        {
                //      stack[i]  = (int*)malloc(size*sizeof(int));
                thread_create(worker,(void *)i);
        }
//	sleep(100);
//        wait();
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
	//printf(1,"pid num is %d\n",pidnum);
	int ticket =0 ;
        while(output<passnum)//when pass time  bigger than it should be passed
        {
                ticket=array_lock_acquire(lock,&flag[0],pidnum);
                if(ticket>=0)//means correct thread get the ticket
                {
			output++;
			int nextoken = ((pidnum+1==20)?0:pidnum+1);		
			printf(1,"pass number is no:%d thread %d is passing the token to thread %d\n",output,pidnum,nextoken);
			if(output>=60)
				break;
			array_lock_release(ticket,lock,&flag[0]);
                }
                else
                {
                        //printf(1,"this is not a correct workpid\n");
                        lock_release(lock);
                        sleep(1);
                }
        }
	
        printf(1,"time to end\n");
        exit();
}

