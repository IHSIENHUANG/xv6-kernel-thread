#include "types.h"
#include "stat.h"
#include "user.h"
int main ( int argc , char * argv [])
{
	int size = 4096;
	int child_pid = clone(size);
	if(child_pid ==1)
		child_pid = clone(size);
	exit ();
}
