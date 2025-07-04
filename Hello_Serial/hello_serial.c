#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char hostname[256];
	gethostname(hostname, 256);

	printf("Hello world from %s\n", hostname);

	return 0;
}
