#include <stdio.h>
#include <unistd.h>


int main(void)
{

	printf("I am the other one %ld\n", (long)getpid());
	return (0);
}
