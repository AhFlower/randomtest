#include<stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
main()
{
    int i;
    int sum = 0;
    struct timeval start, end;
    gettimeofday( &start, NULL );
    for(i = 0; i < 5; i++){
       sleep(1);
    }
    gettimeofday( &end, NULL );
    int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec; 
    printf("time: %d us=%d\n", timeuse, end.tv_usec - start.tv_usec);

}
