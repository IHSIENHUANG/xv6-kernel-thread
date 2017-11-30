#include "types.h"
#include "stat.h"
#include "user.h"
int main ( int argc , char * argv [])
{
	int size = 4096;

	int i = 0 ;
	for(i = 0 ; i < 5; i ++)
	{	
		int* stack = (int*)malloc(size*sizeof(int));
		int child_pid = clone(stack,size);
		if(child_pid ==1)
			child_pid = clone(stack,size);	
	}
	exit ();
}
