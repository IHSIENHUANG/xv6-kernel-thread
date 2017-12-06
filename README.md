# xv6-kernel-thread
* purpose: make a frisbee game with different lock <br>
* make a system call clone(void *stack, int size) use clone and thread_create() to bulid a tread library <br>
* create a thread library and use frisbee game to test it <br>
## Test and set spin lock
* frisbee.c : a test for spin lock <br>
it means each thread should keep trying to get the lock resource. <br>
And the thread get the resource still need to check whether it should work this round.<br>
* thread.c : store the library about lock_init, lock_create, lock_release, lock_create().<br>
## Array-based queue lock
Ref:https://en.wikipedia.org/wiki/Array_Based_Queuing_Locks <br>
* Each thread waits in a while loop with a ticket, until the flag[ticket]!=MUSt_WAIT <br>
* frisbee_array.c <br>
* thread.c <br>
## seqlock
* writer is higher priority to reader
* reader() and writer() <br>
* frisbee_seqlock.c<br>
* reader(struct lock_t*,int),writer(struct lock_t*)<br>


