#include "types.h"
#include "user.h"
#include "mmu.h"
#include "spinlock.h"
#include "x86.h"
#include "thread.h"
//#define PGSIZE (4096)
#define DEBUG 0
#define TEST 0 
int test()
{
	return PGSIZE;
}
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
void thread_join()
{

}
