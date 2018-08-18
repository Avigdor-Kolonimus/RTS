; q1rts1.asm - Assembly file for Question 1 in RTS01

    .MODEL LARGE
    .STACK 100h
    .DATA
TimerPtr DD 0 ; original ISR
Counter   DW  0
reqStr DB 'Please Enter number of seconds (1-9)', 13,10,'$'
outputStr DB 13,10,'After X seconds...',13,10,'$'
D18  DW 18 ; there are 18 ticks per sec.
    
     .CODE
     .386

; My timer ISR

Timer PROC FAR

     PUSHF
     CALL DWORD PTR TimerPtr
     
     INC  Counter

     IRET    
Timer ENDP

     
waitsec PROC  FAR

; Compute AX = 18 to convert sec to ticks
; And wait (do nothing) until counter is AX

     MOV AX,  D18

     MOV  Counter,0           ; Init counter

Delay1:     
     CMP  AX,Counter  ; wait for one sec
     JA  Delay1


; return to caller
     RET    
     waitsec ENDP 

main:
	MOV AX,@DATA
	MOV DS,AX
	
	MOV AH,9
	MOV DX, OFFSET reqStr 
	INT 21h

	; Get n (=number of secs)  from user
	MOV AH,1
	INT 21h
	SUB AL, '0'
	MOV AH,0

	; Preserve original ISR pointers
     	MOV  BX,0
     	MOV  ES,BX
     	MOV  EBX,ES:[32]         
     	MOV  TimerPtr ,EBX

	; Change IV to point to Timer
     	CLI
     	MOV  WORD PTR ES:[32],OFFSET Timer
     	MOV  ES:[34],CS
     	STI

	MOV CX,AX
	INC CX
	MOV BL, '0'
forloop:
	CALL waitsec
	MOV outputStr [8],BL
	INC BL
	MOV AH,9
	MOV DX, OFFSET outputStr 
	INT 21h
	LOOP forloop

	; Restore IV
		   
     	MOV  BX,0
     	MOV  ES,BX
     	MOV  EBX,TimerPtr        
     	MOV  ES:[32], EBX

	MOV AH, 4Ch
	INT 21h

     END main





