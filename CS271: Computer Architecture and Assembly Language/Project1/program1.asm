TITLE Program 1    (program1.asm)

; Author: Prathyoosha Chaya
; Course / Project ID: CS 271 Computer Architecture & Assembly, Program 1		    Date: 01/21/2018
; Description: This program serves as an introduction to MASM. Given two numbers by the user, the program outputs arithmetic operations performed on those numbers.

INCLUDE Irvine32.inc

; declaring/initializing variables
.data
author_msg		BYTE	"Elementary Arithmetic by Prathyoosha Chaya, CS 271", 10, 0		; ending of strings end with line feed char, then null char
intro_msg		BYTE	"Hello!! Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder.", 10, 0
num_1_msg		BYTE	"Number 1: ", 0
num_2_msg		BYTE	"Number 2: ", 0
jl_msg			BYTE	"EC: Number 1 seems to be less than number 2!" , 10, 0
jg_msg			BYTE	"EC: Number 1 seems to be greater than number 2!" , 10, 0
je_msg			BYTE	"EC: Number 1 seems to be equal to number 2!" , 10, 0
farewell_msg	BYTE	"That's all! Goodbye!", 0
add_msg			BYTE	" + ", 0
sub_msg			BYTE	" - ", 0
mult_msg		BYTE	" * ", 0
div_msg			BYTE	" / ", 0
eq_msg			BYTE	" = ", 0
remainder_msg	BYTE	" remainder ", 0
num_1			DWORD	?
num_2			DWORD	?
remainder		DWORD	?

.code
main PROC
	call Clrscr
	; display initial welcome message
	mov edx, OFFSET author_msg
	call WriteString
	mov edx, OFFSET intro_msg
	call WriteString

	; read both numbers from user
	mov edx, OFFSET num_1_msg			; output context for number input
	call WriteString
	call ReadInt						; read from user
	mov num_1, eax

	mov edx, OFFSET num_2_msg
	call WriteString
	call ReadInt
	mov num_2, eax

	; output addition message
	mov eax, num_1
	call WriteDec
	mov edx, OFFSET add_msg
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET eq_msg
	call WriteString

	; calculate and output addition value
	add eax, num_1
	call WriteDec
	call Crlf

	; output subtraction message
	mov eax, num_1
	call WriteDec
	mov edx, OFFSET sub_msg
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET eq_msg
	call WriteString

	; calculate and output subtraction value
	mov eax, num_1
	sub eax, num_2						; subtract num_2 from EAX (num_1), then output
	call WriteDec
	call Crlf

	; output multiplication message
	mov eax, num_1
	call WriteDec
	mov edx, OFFSET mult_msg
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET eq_msg
	call WriteString

	; calculate and output multiplication value
	xor edx, edx				; setting edx value to 0 before performing mult, in case of overflow
	mul num_1
	call WriteDec
	call Crlf

	; output division message
	mov eax, num_1
	call WriteDec
	mov edx, OFFSET div_msg
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET eq_msg
	call WriteString

	; calculate and output division value
	mov eax, num_1
	xor edx, edx				; setting edx value to 0 before performing division
	mov ebx, num_2
	div ebx
	call WriteDec				; output quotient already in EAX
	mov remainder, edx
	mov edx, OFFSET remainder_msg
	call WriteString
	mov eax, remainder
	call WriteDec				; output remainder originally in EDX
	call Crlf

	; EXTRA CREDIT OPTION: Validate that the second number is less than the first.
	call Crlf
	mov eax, num_1
	cmp eax, num_2
	jl less
	jg greater
	je equal

	less: 
		mov edx, OFFSET jl_msg
		call WriteString
		jmp done
	greater:
		mov edx, OFFSET jg_msg
		call WriteString
		jmp done
	equal:
		mov edx, OFFSET je_msg
		call WriteString
		

	done:
		call Crlf
		mov edx, OFFSET farewell_msg
		call WriteString
		call Crlf

	exit
main ENDP
END main
