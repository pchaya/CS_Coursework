TITLE Program 4     (program4.asm)

; Author: Prathyoosha Chaya, chayap@oregonstate.edu
; Course / Project ID: CS 271 Sec. 001				Due Date: 02/18/2018
; Description: Assignment 4. This program receives a number from the user and displays all the composite numbers prior to that number.
INCLUDE Irvine32.inc

.data
INPUT_MAX		EQU			400					; used to check if inputted value is in range
INPUT_MIN		EQU			1	
NUMS_PER_LINE	EQU			10					; numbers per row of display
prompt1			BYTE		"Composite Numbers by Prathyoosha Chaya", 10, 0
promptReq		BYTE		"Enter the number of composite numbers you would like to see.", 10, 0
prompt2			BYTE		"I'll accept orders for up to 400 composites. ", 10, 0
promptOoR		BYTE		"Out of range. Please enter a number in [1, 400].", 10, 0
promptNum		BYTE		"Enter a number: ", 0
displayComp1	BYTE		"Printing ", 0
displayComp2	BYTE		" composites... ", 10, 0
goodbye1		BYTE		"Results certified by Prathyoosha Chaya.", 10, 0
goodbye2		BYTE		"Goodbye!", 10, 0
spaces			BYTE		"    ", 0
numofComposites	DWORD		0
currNum			DWORD		3					; will be incremented, first number to test is 4 (1, 2, 3 are all prime)
currDivisor		DWORD		?
ooRange			DWORD		0					; out of range flag

.code
main PROC
	call	introduction
	call	getUserData
	call	showComposites
	call	farewell

	exit
main ENDP

; ------------------------------------------------------
; introduction
;
; Displays introductory statements for user
; Receives: none.
; Returns: none.
; ------------------------------------------------------
introduction PROC
	mov		edx, OFFSET prompt1
	call	WriteString
	mov		edx, OFFSET promptReq
	call	WriteString
	mov		edx, OFFSET prompt2
	call	WriteString
	call	Crlf

	ret
introduction ENDP	

; ------------------------------------------------------
; getUserData
;
; Receives user inputted integer, then calls validation procedure.
; Receives: none.
; Returns: none.
; ------------------------------------------------------
getUserData PROC
Begin:
	mov		edx, OFFSET promptNum
	call	WriteString
	call	ReadInt
	call	Crlf
	mov		numOfComposites, eax

	call	validate
	cmp		ooRange, 1
	je		Begin

	ret
getUserData ENDP

; ------------------------------------------------------
; validate
;
; Subprocedure to getUserdata, validates that data is in range 1-400
; Receives: eax/numOfComposites.
; Returns: ebx/ooRange flag.
; ------------------------------------------------------
validate PROC
	; Compare input to range limits, if not within limits, then start display sequence
	mov		ooRange, 0							; reset ooRange value
	cmp		numOfComposites, INPUT_MAX
	jg		DisplayOoR
	cmp		numOfComposites, INPUT_MIN
	jl		DisplayOoR
	mov		ebx, ooRange						; set ooRange flag to false (already 0)
	
	ret

	; Display out of range
DisplayOoR:
	mov		edx, OFFSET promptOoR
	call	WriteString
	call	Crlf
	mov		ooRange, 1							; set ooRange flag to true
	mov		ebx, ooRange

	ret											; call getUserData to ask for number again

validate ENDP

; ------------------------------------------------------
; showComposites
;
; Displays composites calculated from isComposite. Comtains two loops - one loops over total number of composite numbers displayed, 
; and the other loops over numbers to check if composite.
; Receives: numOfComposites, currNum.
; Returns: none.
; ------------------------------------------------------
showComposites PROC
	mov		edx, OFFSET displayComp1				; Display number of composites to print
	call	WriteString
	mov		eax, numOfComposites
	call	WriteDec
	mov		edx, OFFSET displayComp2
	call	WriteString
	call	Crlf

	mov		ecx, numOfComposites					; set loop counter to number of composites to display

	LoopNextNumber:									; main loop incrementing currNum values until numOfComposites
        LoopUntilCompCheck:							; tests if currNum is composite, if not then keep incrememting until next composite is found.
            inc		currNum						
            call	isComposite
            cmp		eax, 0							; if isComposite returned 0, then number is prime. 
            je		LoopUntilCompCheck
		
		; currNum must contain a composite number, thus display currNum
        mov		eax, currNum
        call	WriteDec
        mov		edx, OFFSET spaces     
        call	WriteString

        ; Check if 10th number to print new line
		mov		eax, numOfComposites
        sub		eax, ecx					; numOfComposites - loop count will give number of composite numbers displayed
        inc		eax
        mov		ebx, NUMS_PER_LINE		; divide by max numbers per line (10) to check mod value stored in edx
        xor		edx, edx                     
        div		ebx                      ; Divides by 10, if R=0 then 10 numbers on line

        cmp		edx, 0					; EDX is 0 if there are 10 numbers per line
        jne		LessThan10              ; Prints or does not print new line
          
        call CrLf

        LessThan10:
        loop LoopNextNumber
     
	ret
showComposites ENDP

; ------------------------------------------------------
; isComposite
;
; Tests if a number(n) is prime by dividing with increasing numbers (starting with 2, until n). 
; If the number is divisible with a remainder of 0, or n is reached, then it must be composite.
; Receives: currNum.
; Returns: EBX returns true(1)/false(0) value based on if number is/is not composite.
; ------------------------------------------------------
isComposite	PROC
	mov		currDivisor, 1			; first number to divide by is 2, incremented at beginning of check

	CompositeCheck:
		inc		currDivisor			; keep incrementing until one of the checks performs a jump.

        ; CHECK 1: if the divisor has reached the compNum, then it is automatically prime
        mov		edx, currDivisor
        cmp		edx, currNum
        je		IsPrime

        ; CHECK 2: perform division, if mod value is 0 then it is automatically composite
        xor		edx, edx
        mov		eax, currNum
        mov		ebx, currDivisor
        div		ebx

        cmp		edx, 0              ; comparing remainder to 0
        je		NotPrime	        ; if R=0, then compNum is a composite

        jmp		CompositeCheck		; the current number is composite according to the divisor we are comparing to. continue to increment divisor.

    NotPrime:
        mov		ebx, 1              ; number is composite, set flag to true and return from isComposite
        jmp		Complete

    IsPrime:
        mov		eax, 0              ; number is prime, set flag to false and return from isComposite

    Complete:
        ret

isComposite ENDP


; ------------------------------------------------------
; farewell
;
; Displays farewell message to user.
; Receives: none.
; Returns: none.
; ------------------------------------------------------
farewell PROC
	call	Crlf
	mov		edx, OFFSET goodbye1
	call	WriteString
	mov		edx, OFFSET goodbye2
	call	WriteString
	call	Crlf

	ret
farewell ENDP


END main