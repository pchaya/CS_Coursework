TITLE Program 2     (program2.asm)

; Author: Prathyoosha Chaya, chayap@oregonstate.edu
; Course / Project ID: CS 271 Sec. 001				Due Date: 01/28/2018
; Description: Assignment 2. This program receives an integer from the user and displays the corresponding number of terms in the Fibonacci sequence.

INCLUDE Irvine32.inc

.data
MAX = 80				; max characters to read for user_name
INPUT_MAX = 46
INPUT_MIN = 1
prompt1			BYTE		"Fibonacci Numbers by Prathyoosha Chaya", 10, 0
prompt2			BYTE		"What is your name? ", 0
greeting		BYTE		"Hello, ", 0
excl			BYTE		"!", 0
user_name		BYTE		MAX+1 DUP (?), 0
promptTerms		BYTE		"How many Fibonacci terms should I display?", 0
promptNum		BYTE		"Please enter a number between 1 and 46: ", 0
spaces			BYTE		"     ", 0
goodbye			BYTE		"Goodbye, ", 0
terms			DWORD		0
temp			DWORD		?

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
	mov		edx, OFFSET promptTerms
	call	WriteString
	call	Crlf

; Validate the input
getUserData:
	mov		edx, OFFSET promptNum
	call	WriteString
	call	ReadInt
	call	Crlf
	mov		terms, eax

	; Compare input to range limits, post test loop
	cmp		terms, INPUT_MAX
	jg		getUserData
	cmp		terms, INPUT_MIN
	jl		getUserData

; Display Fibonacci sequence to specified terms
	mov		ecx, terms
    mov		eax, 0				; starting terms for Fibonacci sequence
    mov		ebx, 1
; Here, EDX holds previous 1, EBX holds previous 2, and EAX holds the current value, or sum (for ease of displaying)
displayFibs:
    mov		eax, edx 
	mov		temp, edx
    add		eax, ebx
	call	WriteDec			; display addition of ebx and edx
	mov		edx, OFFSET spaces
	call	WriteString
	mov		edx, temp
    mov		edx, ebx			; previous 1 = previous 2
    mov		ebx, eax			; previous 2 = current value
    loop	displayFibs

farewell:
	call	Crlf
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
