/* train2.c - C solution for exercise 2 in training.pdf */
#include <stdio.h>
#include <dos.h>
volatile int flag5=0; 
void interrupt (*Int5Save) (void);
/* My ISR for INT 5 */
void interrupt my_int5(void)
{
	/* Call original ISR - NOT MUST
	asm{
		PUSHF
		CALL DWORD PTR Int5Save
	}*/
	flag5 = 1;
}
void main ()
{
  int n;
  printf("Please Enter A Number to Print On Screen\n");
  scanf("%d", &n);
  Int5Save = getvect(5);
  flag5 = 0;
  setvect(5,  my_int5);
  /* wait for PrntScr */
  while(flag5 == 0) ;
  printf("Your Number is: %d\n",n);   
  setvect(5,Int5Save);
  printf("Terminating the program\n");
  return;
}