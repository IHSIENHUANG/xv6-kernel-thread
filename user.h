struct stat;
struct rtcdate;
struct lock_t;
// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int clone(void*,int);//BR
int texit(void);//BR

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

//thread.c
void thread_create(void *(*start_routine)(void*), void *arg);
void thread_join();
void lock_init(struct lock_t *);
void lock_acquire(struct lock_t *);
void lock_release(struct lock_t *);
//for array base lock
int array_lock_acquire(struct lock_t *,int*,int);//even if get acquire return value will check wheher the right thread
void array_lock_release(int,struct lock_t *,int*);
void array_lock_init(struct lock_t*,int*);
//for seqlock
void seqlock_init(struct lock_t *);
int reader(struct lock_t*,int);
void seqlock_writer(struct lock_t*);
