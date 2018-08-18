; q2rts1.asm - Assembly file for Question 2 in RTS01

    .MODEL LARGE
    .STACK 100h
    .DATA
orgISR5   DD 0 ; original ISR
flag   DB  0
endStr DB 'Program Terminated', 13,10,'$'
    
     .CODE
     .386

; My Print Screen ISR

my5 PROC FAR

     PUSHF
     CALL DWORD PTR orgISR5   
     
     mov flag,1

     IRET    
my5 ENDP

      

main:
	MOV AX,@DATA
	MOV DS,AX
	

	; Preserve original ISR pointers
     	MOV  BX,0
     	MOV  ES,BX
     	MOV  EBX,ES:[20]         
     	MOV  orgISR5,EBX

	; Change IV to point to Timer
     	CLI
     	MOV  WORD PTR ES:[20],OFFSET my5
     	MOV  ES:[22],CS
     	STI

	
whileloop:
	CMP flag,1
	
	JNE whileloop

	; print
	MOV AH,9
	MOV DX, OFFSET endStr 
	INT 21h


	; Restore IV
		   
     	MOV  BX,0
     	MOV  ES,BX
     	MOV  EBX,orgISR5        
     	MOV  ES:[20], EBX

	MOV AH, 4Ch
	INT 21h

     END main





