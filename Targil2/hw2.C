/* by Alexey Titov ?????????
	  Denis Sidorovich ????????? 	
 */
#include <conf.h>
#include <kernel.h>
int	winner=0;		/* external variables are shared by all processes */
int prioA=20;		/* external variable are used to indicate priority */
int prioB=20;		/* external variable are used to indicate priority */
/*------------------------------------------------------------------------
 *  xmain  --  A and B processes synchronized with semaphore
 *------------------------------------------------------------------------
 */
xmain()
{
	int	A(), B();
	int	S;
	S = screate(0);	// semaphore
	resume(create(A,INITSTK,prioA,"A",1,S));
	resume(create(B,INITSTK,prioB,"B",1,S));
	sdelete(S);
}
/*------------------------------------------------------------------------
 *  A  --  enters to global variable 1 if it is equal to 0 and print the answer
 *------------------------------------------------------------------------
 */
A(int S)
{
	wait(S);
	sleep(1);
	signal(S);
	if (winner==0)
		winner=1;
	printf("A=1, priority=%d, B=2, priority=%d, Winner is %d\n",prioA,prioB,winner);
	kill(getpid());
}
/*------------------------------------------------------------------------
 *  B  -- enters to global variable 2 if it is equal to 0
 *------------------------------------------------------------------------
 */
B(int S)
{
	wait(S);
	sleep(1);
	signal(S);
	if (winner==0)
		winner=2;
	kill(getpid());
}