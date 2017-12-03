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
//static int output =0;
static int numofthread;
static int passnum;
//static int workpid=0;//this time should be no workpid's time to work
void* worker();
int main ( int argc , char * argv [])
{
        numofthread =atoi(argv[1]);// num of threads is decided by the parameter passed by user
        passnum = atoi(argv[2]);
        int i = 0 ;
	int *flag = malloc(numofthread*sizeof(int));
	printf(1,"DEBUG\n");
        array_lock_init(lock,&flag[0]);
	printf(1,"DEBUG2\n");
        for(i=numofthread;i<numofthread;i++)
        {
                //      stack[i]  = (int*)malloc(size*sizeof(int));
                thread_create(worker,(void *)i);
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

        //lock_init(&ttable.lock);
        //int pidnum = (int)arg;
#if DEBUG
        printf(1,"child's pid num is %d\n",pidnum);
#endif
        /*while(output<passnum)//when pass time  bigger than it should be passed
        {
                array_lock_acquire(lock);
                if(output==passnum)
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
                        //printf(1,"this is not a correct workpid\n");
                        lock_release(lock);
                        sleep(1);
                }
        }
	*/
        printf(1,"time to end\n");
        exit();
}

