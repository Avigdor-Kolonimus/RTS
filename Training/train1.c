#include <stdio.h>
#include <conf.h>
#include <kernel.h>
#include <bufpool.h>
char**  alloc_large_mem(unsigned int memory_size);
int poolid;
int xmain()
{
	char** memArr; /* Array of pointers */
	int i, arrSize ;
	poolinit();
	poolid = mkpool(64,50);       
	memArr = alloc_large_mem (200);
	printf("The Array is:\n");
	arrSize = 4; /*(200/64)+1*/
	for (i=0; i< arrSize;i++) 
		printf ("%d ", memArr[i]);
	return 0;
}
char**  alloc_large_mem(unsigned int memory_size)
{
	char** resP;
	char** p;
	char* buf;
	int num_of_buf, i;
	*resP = (char*) getbuf(poolid);
	num_of_buf = memory_size/64;
	if(memory_size%64 != 0) num_of_buf++;
	p=resP;
	for(i=0; i<num_of_buf; i++){
		buf = (char*) getbuf(poolid);
        	*p = buf;  			/*resP[i] = buf; */
		p++;
	}
    return resP;
}