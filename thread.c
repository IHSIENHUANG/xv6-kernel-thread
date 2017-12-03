#include "types.h"
#include "user.h"
#include "mmu.h"
#include "spinlock.h"
#include "x86.h"
#include "thread.h"
//#define PGSIZE (4096)
#define DEBUG 0
#define TEST 0 
static int num =1;
int test()
{
	return PGSIZE;
}
//this part is for spin lock
void lock_init(struct lock_t *lk)
{
	lk -> locked = 0;//initial situation is unlocked
}
void lock_acquire(struct lock_t *lk)
{
	while(xchg(&lk->locked,1) != 0);
    #if TEST
	while(1)
	{
		int atomic = xchg(&lk->locked,2);
		if(atomic!=0)
		{
		#if DEBUG
			printf(1,"atomic number is %d\n",atomic);
		#endif
			break;
		}
		#if DEBUG
		else
			printf(1,"fail atomic number is %d\n",atomic);
		#endif
	}
    #endif
}
void lock_release(struct lock_t *lock)
{
	xchg(&lock->locked,0);
}

void thread_create(void*(*start_routine)(void*), void *arg)
{
	void* newp = malloc(PGSIZE*2);
	int rc;
	rc = clone(newp,PGSIZE*2);
	if(rc==0)
	{
		 (*start_routine)(arg);
		exit();		

	}

}
//this park is for array base queue lock
void array_lock_init(struct lock_t *lk,int* flag)
{
	lk->locked=0;
	int i =0;
	for(i=0;i<20;i++)
		flag[i]=0;
	flag[1]=1;
}
int array_lock_acquire(struct lock_t *lk,int* flag,int id)
{
	while( xchg(&lk->locked,num));
	num++;
	printf(1,"number is %d\n",num%20);
	if(((num)%20)!=id)
	{
	 	num--;
		xchg(&lk->locked,0);
		return -1;
	}
	else
	{
		int ticket = (num)%20;//thread 0~numofthread ticket 1~
		//printf(1,"id %d is waiting \n",id); 
		while(flag[id]==0);
		xchg(&lk->locked,0);
		//printf(1,"id %d is finished\n",id);
		return ticket ;//right thread get the resource
	}


}
void array_lock_release(int ticket,struct lock_t *lk,int* flag)
{
	//xchg(&lk->locked,0);
	flag[ticket]=0;
	int nextone = ticket+1;
	if(nextone ==20) nextone=0;
	flag[nextone]=1;
	printf(1,"next start is %d\n",nextone);
}
void thread_join()
{

}
