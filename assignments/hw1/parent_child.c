#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 

int main()
{
int i;
for (i = 0; i < 3; i++) {
int pid  = fork();
if (pid == 0) {
printf("Child sees i = %d\n", i);
exit(1);
} else {
printf("Parent sees i = %d\n", i);
}
}
}

