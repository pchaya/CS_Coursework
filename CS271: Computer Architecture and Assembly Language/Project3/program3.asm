TITLE Program 3     (program3.asm)

; Author: Prathyoosha Chaya, chayap@oregonstate.edu
; Course / Project ID: CS 271 Sec. 001				Due Date: 02/11/2018
; Description: Assignment 3. This program receives an series of negative integers from the user and displays the number of negative numbers entered, the sum, and the average of the numbers.

INCLUDE Irvine32.inc

.data
MAX				EQU			80					; max characters to read for user_name
INPUT_MAX		EQU			-1					; used to check if inputted value is in range
INPUT_MIN		EQU			-100
prompt1			BYTE		"Integer Accumulator by Prathyoosha Chaya", 10, 0
prompt2			BYTE		"What is your name? ", 0
greeting		BYTE		"Hello, ", 0
excl			BYTE		"!", 0
user_name		BYTE		MAX+1 DUP (?), 0
promptReq		BYTE		"Please enter numbers in [-100, -1].", 10, 0
promptComplete	BYTE		"Enter a non-negative number when you are finished to see results.", 10, 0
promptNum		BYTE		"Enter a number: ", 0
resNum1			BYTE		"You entered ", 0
resNum2			BYTE		" valid numbers.", 10, 0
resSum			BYTE		"The sum of your valid numbers is ", 0
resAvg			BYTE		"The rounded average is ", 0
resNone			BYTE		"You did not enter any valid numbers. Maybe next time!", 0
goodbye			BYTE		"Thank you for playing Integer Accumulator! It's been a pleasure to meet you, ", 0
currNum			DWORD		0
numOfTerms		DWORD		0
sum				DWORD		0
roundedAvg		DWORD		0

.code
main PROC
; Introduction and greeting the user
introduction:
	mov		edx, OFFSET prompt1
	call	WriteString
	mov		edx, OFFSET prompt2
	call	WriteString
	mov		edx, OFFSET user_name		; move user_name to ReadString input buffer
	mov		ecx, MAX					; move buffer size for ReadString
	call	ReadString
	mov		edx, OFFSET greeting
	call	WriteString
	mov		edx, OFFSET user_name
	call	WriteString
	mov		edx, OFFSET excl
	call	WriteString
	call	Crlf

; Prompt user to enter number of terms to display
userInstructions:
	mov		edx, OFFSET promptReq
	call	WriteString
	mov		edx, OFFSET promptComplete
	call	WriteString

; Receive input from the user
getUserData:
	mov		edx, OFFSET promptNum
	call	WriteString
	call	ReadInt
	call	Crlf
	mov		currNum, eax

	; Compare input to range limits, if not within limits, then start display sequence
	cmp		currNum, INPUT_MAX
	jg		displayNone
	cmp		currNum, INPUT_MIN
	jl		displayNone

	; Accumulate values
	inc		numOfTerms
	mov		ebx, currNum
	add		sum, ebx

	; Loop until input is out of range
	jmp		getUserData

; Check for the case where no valid values were entered
displayNone:
	cmp		numOfTerms, 0
	jne		displayResult
	mov		edx, OFFSET resNone
	call	WriteString
	call	Crlf
	jmp		farewell

; Displays the accumulated values
displayResult:
	; Display number of terms
	mov		edx, OFFSET resNum1
	call	WriteString
	mov		eax, numOfTerms
	call	WriteDec
	mov		edx, OFFSET resNum2
	call	WriteString
	call	Crlf

	; Display sum
	mov		edx, OFFSET resSum
	call	WriteString
	mov		eax, sum
	call	WriteInt
	call	Crlf

	; Calculate rounded average
	cdq								; sign extend eax before performing idiv
	mov		ebx, numOfTerms
	idiv	ebx
	mov		roundedAvg, eax

	; Display rounded average
	mov		edx, OFFSET resAvg
	call	WriteString
	mov		eax, roundedAvg
	call	WriteInt
	call	Crlf
	
; Outputs the farewell message to the user
farewell:
	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET user_name
	call	WriteString
	mov		edx, OFFSET excl
	call	WriteString
	call	Crlf

	exit
main ENDP
END main
