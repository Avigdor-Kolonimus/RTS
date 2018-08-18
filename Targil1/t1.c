#include <stdio.h>
#include <dos.h>
#include <time.h>
int counter;	//counter for counting interrupt 8
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
  int  num1, num2, answer, answerT=0, sdm,question=0;
  //num1-first number; num2-second number; sdm:0-addition,1-subtraction,3-multiplication;
  //answerT-counter for correct answers; question-counter for question
  //answer-answer entered by the user  
  printf("START TEST\n");
  Int8Save = getvect(8);
  setvect(8,  my_int8);
  srand(time(NULL));
  counter = 0;
  while(counter <= 180){
    num1 = 1 + rand() % 1000;
	num2 = 1 + rand() % 1000;
	sdm = rand() % 3;
	switch (sdm)
		{
			case 0:								//addition
				printf("%d+%d=",num1,num2);
				question++;
				scanf("%d", &answer);
				if (answer == num1 + num2 && counter <= 180)
					answerT++;
				break;
			case 1:								//subtraction
				printf("%d-%d=", num1, num2);
				question++;
				scanf("%d", &answer);
				if (answer == num1 - num2 && counter <= 180)
					answerT++;
				break;
			default:							//multiplication
				printf("%d*%d=", num1, num2);
				question++;
				scanf("%d", &answer);
				if (answer == num1 * num2 && counter <= 180)
					answerT++;
				break;
		}	
  }
  setvect(8,Int8Save);
  printf("END TEST\n");
  printf("You have true answer %d in %d question\n",answerT,question);
  return;
}