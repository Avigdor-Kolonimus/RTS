#include <stdio.h>
#include <dos.h>
int counter;		//counter for counting interrupt 8
int counterkey; 	//counter for counting interrupt 9
void interrupt (*Int8Save) (void);
void interrupt (*Int9Save) (void);
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
/* My ISR for INT 9 */
void interrupt my_int9(void)
{
	/* Call original ISR */
	asm{
		PUSHF
		CALL DWORD PTR Int9Save
	}
	counterkey++;
}
void main ()
{
  printf("Please Start Typing For TEN SECONDS\n");
  Int8Save = getvect(8);
  Int9Save = getvect(9);
  setvect(8,  my_int8); 
  setvect(9,  my_int9);
  counterkey=counter = 0;
  while(counter <= 180);
  counterkey=(counterkey-1)/2;
  setvect(8,Int8Save);
  setvect(9,Int9Save);
  printf("The number of characters which have input %d\n",counterkey);
  return;
}