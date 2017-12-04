#include "types.h"
#include "user.h"
#include "mmu.h"
#include "spinlock.h"
#include "x86.h"
#include "thread.h"
//#define PGSIZE (4096)
#define DEBUG 0
#define TEST 0 
static int num =0;
static int SEQ =1;
static int WORKNUM =0;
static int DATA=0;
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
	for(i=0;i<600;i++)
		flag[i]=0;
	flag[0]=1;
}
int array_lock_acquire(struct lock_t *lk,int* flag,int id)
{
	while( xchg(&lk->locked,1));
	num++;
	//printf(1,"number is %d\n",num);
	if(((num-1)%20)!=id)
	{
		
	 	num--;
		//printf(1,"id %d in wrong place num is %d\n",id,num);
		return -1;
	}
	else
	{
		int ticket = (num-1)%20;//thread 0~numofthread ticket 1~
		//printf(1,"id %d is waiting \n",id); 
		while(flag[ticket]==0);
		//xchg(&lk->locked,0);
		//printf(1,"id %d is finished\n",id);
//		printf(1,"right place num is %d\n",ticket);
	//	if(num<=60)
	//	printf(1,"pass no :%d thread %d is pass the token ot thread %d\n",num,ticket,ticket+1);
		return ticket ;//right thread get the resource
	}


}
void array_lock_release(int ticket,struct lock_t *lk,int* flag)
{
	xchg(&lk->locked,0);
	flag[ticket]=0;
	int nextone = ticket+1;
	//if(nextone ==20) nextone=0;
	flag[nextone]=1;
	//printf(1,"next start is %d\n",nextone);
}
//this part is for seq_lock
void seqlock_init(struct lock_t *lk)
{
	lk->locked=0;
}

int reader(struct lock_t *lk,int pidnum)
{
	int r1=0;
	int seq0=0,seq1=0;
	do{
		seq0= SEQ;
		r1=DATA;
		seq1= SEQ;
		sleep(1);
		if(WORKNUM==pidnum)
		{
			if(SEQ%2==0)
			{
				if((seq0) == (seq1))
					break;
			}
		}

	}while( 1 );//odd means writer do the work
	SEQ++;//make it become odd again and it turns to writer time
	WORKNUM++;
	if(WORKNUM==20)
		WORKNUM=0;
	return r1;
	
}
void seqlock_writer(struct lock_t *lk)
{
	while(xchg(&lk->locked,1)!=0);
	DATA++;
	SEQ++;
//	printf(1,"SEQ = %d",SEQ);
}

