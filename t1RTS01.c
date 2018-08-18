#include <stdio.h>
#include <dos.h>

int counter; 

void interrupt (*Int8Save) (void);

/* My ISR for INT 8 */
void interrupt my_int8(void)
{
	/* Call original ISR */
	asm{
		PUSHF
		CALL DWORD PTR Int8Save
	}
	counter++;

}

void main ()
{
  int  i, n;

  printf("Please Enter number of sec\n");
  scanf("%d", &n);

  Int8Save = getvect(8);
  
  setvect(8,  my_int8);
   
  counter = 0;
  for (i=0; i<=n; i++){
	printf("After %d seconds...\n", i);	
	counter = 0;  	
	while(counter <= 18) ;
  }
	
  
  setvect(8,Int8Save);
  
  printf("Terminating the program.\n");

  return;
}