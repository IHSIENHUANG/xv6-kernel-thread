//#include "types.h"
//#include "user.h"
//#include "mmu.h"
//#include "spinlock.h"
//#include "x86.h"
//#include "proc.h"
//#include "thread.h"
#define PGSIZE (4096)
int test()
{
	return PGSIZE;
}


void lock_init(lock_t *lk)
{
	lk -> locked = 0;//initial situation is unlocked
}
void lock_acqurie(lock_t *lk)
{
	 while(xchg(&lk->locked,1) != 0);
}
void lock_release(lock_t *lock)
{
	xchg(&lock->locked,0);
}
/*
 *start_routine can receive a funtion 
 * */
void thread_create(void(*start_routine)(void*), void *arg))
{
	


}
void thread_join()
{

}
