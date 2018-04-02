TITLE Program 6b     (program6b.asm)

; Author: Prathyoosha Chaya, chayap@oregonstate.edu
; Course / Project ID: CS 271 Sec. 001				Due Date: 03/18/2018
; Description: Assignment 6 Option B. This prorgam serves as practice for combinatorics problems.
;		This program provides the user with a random n value and r value, then calculates the number of combinations of r 
;		items taken from a set of n items (i.e., nCr ). The user is asked to input their answer, and the program responds 
;		with if the student's answer is correct or incorrect. The program repeats this practice until the student chooses to quit the program.
INCLUDE Irvine32.inc

; Macro that displays a given input string
mDisplayString MACRO inputString
	push	edx 
	mov		edx, offset inputString 
	call	WriteString
	pop		edx
ENDM

; Macro to display a given decimal 
mDisplayDec MACRO inputDec
	push	eax 
	mov		eax, inputDec
	call	WriteDec
	pop		eax
ENDM


.data
; Constants used:
MAX_N			EQU			12					; used to check if inputted n value is in range
MIN_N			EQU			3
N_RANGE			EQU			10					; N_RANGE = MAX_N - MIN_N + 1, used for randomization
MIN_R			EQU			1					; used to check if inputted r value is in range
INPUT_MAX		EQU			10

; Output messages, all are used globally with exception of display Unsorted and displaySorted
prompt1				BYTE		"Welcome to the Combinations Calculator", 10, 0
prompt2				BYTE		9, "Programmed by Prathyoosha Chaya", 10, 0
promptEC			BYTE		"**EC: This program numbers each problem and keeps the user's score. ", 10, 0
prompt3				BYTE		"I will give you a combinations problem.  You enter your answer, ", 10, 0
prompt4				BYTE		"and I will let you know if you are right. ", 10, 0
problemHeader		BYTE		"Problem #", 0
promptN				BYTE		"Number of elements in the set: ", 0
promptR				BYTE		"Number of elements to choose from the set: ", 0
promptAnswer		BYTE		"How many ways can you choose?: ", 0
promptNotInt		BYTE		"Invalid answer. Not an integer.", 10, 0
displayAnswer1		BYTE		"There are  ", 0
displayAnswer2		BYTE		" combinations of ", 0
displayAnswer3		BYTE		" items from a set of ", 0
displayAnswer4		BYTE		".", 10, 0
displayCorrect		BYTE		"You are correct!", 10, 0
displayWrong		BYTE		"Your answer is wrong. You need more practice.", 10, 0
displayRepeat		BYTE		"Another problem? (y/n): ", 0
displayInvalid		BYTE		"Invalid response.  ", 0
displayTotals		BYTE		"Here is your total score: ", 10, 0
displayCorrectNum	BYTE		"Questions answered correctly: ", 0
displayWrongNum		BYTE		"Questions answered wrong: ", 0
goodbye				BYTE		"Ok... goodbye!", 10, 0


; Values/data to be used
n				DWORD		?
r				DWORD		?
result			DWORD		?					; Holds result of nCr calculation.
userAnswerStr	BYTE		INPUT_MAX DUP(?)	; Holds user answer, prior to validation
userAnswer		DWORD		?					; Holds the user's answer, after int validation
giveAnother		BYTE		INPUT_MAX DUP(?)	; for storing user's answer to solve another problem
problemNum		DWORD		1					; counts the problem number
numCorrect		DWORD		0					; keeps track of number of problems answered right/wrong
numWrong		DWORD		0

.code
main PROC
	call	introduction
	
	call	Randomize									; set random seed based on system clock for use in showProblem prodecure

	; Label for providing another problem to user
	GoAgain:
		call	Crlf
		; show problem to user
		push	OFFSET n
		push	OFFSET r
		push	OFFSET problemNum
		call	showProblem

		; get user's answer and validate
		push	OFFSET userAnswer
		push	OFFSET userAnswerStr
		call	getData

		; compute combination
		push	n
		push	r
		push	OFFSET result
		call	combinations

		;mDisplayDec	result

		push	OFFSET numCorrect
		push	OFFSET numWrong
		push	n
		push	r
		push	result
		push	userAnswer
		call	showResults

	; Asks user if they would like to solve another problem
	AskRunAgain:
		inc problemNum

		mDisplayString displayRepeat
		mov		ecx, INPUT_MAX
		mov		edx, OFFSET giveAnother
		call	ReadString

		; Compare size of user input to 1 (should not be larger)
		cmp		eax, 1
		ja		InvalidResponse

		mov		ecx, eax
		mov		esi, OFFSET giveAnother
		cld

		; Then compare to Y/y or N/n
		lodsb
		cmp		al, 89
		je		GoAgain
		cmp		al, 121
		je		GoAgain

		cmp		al, 78
		je		ExitMain
		cmp		al, 110
		je		ExitMain

	; Invalid response to (y/n)
	InvalidResponse:
		mDisplayString displayInvalid
		jmp		AskRunAgain


	ExitMain:
		call	Crlf
		mDisplayString	displayTotals
		mDisplayString	displayCorrectNum
		mDisplayDec		numCorrect
		call	Crlf
	
		mDisplayString	displayWrongNum
		mDisplayDec		numWrong
		call	Crlf

		mDisplayString	goodbye
		call	Crlf

	exit
main ENDP

; ------------------------------------------------------
; introduction
;
; Displays introductory statements for user
; Receives: none.
; Returns: none.
; Preconditions: none
; Registers changed: edx
; ------------------------------------------------------
introduction PROC
	mDisplayString	prompt1
	mDisplayString	prompt2
	mDisplayString	promptEC
	call	Crlf
	mDisplayString	prompt3
	mDisplayString	prompt4
	call	Crlf

	ret
introduction ENDP	

; ------------------------------------------------------
; showProblem
;
; Generates the random numbers and displays the problem.
; Receives: n, r, and problemNum by reference.
; Returns: generated n and r values.
; Preconditions: none
; Registers changed: eax, ebx, ecx, edx
; ------------------------------------------------------
showProblem PROC
	push	ebp
	mov		ebp, esp
	mov		edx, [ebp + 16]								; move value of @n to edx
	mov		ecx, [ebp + 12]								; move value of @r to ecx
	mov		ebx, [ebp + 8]								; move value of @problemNum to ebx

	; Generate a random n value
	mov		eax, N_RANGE
	call	RandomRange									; find random num in range of 9, then add MIN_N to get number in range [3, 12].
	add		eax, MIN_N
	mov		[edx], eax

	; Generate a random r value
	mov		eax, [edx]
	call	RandomRange									; finds a random number in range [0, n-1]
	add		eax, MIN_R									; adjust random number to be in range [1, n]
	mov		[ecx], eax


	; Show the user the generated problem
	mDisplayString	problemHeader						; display problem #
	mDisplayDec		[ebx]
	call	Crlf

	mDisplayString	promptN
	mDisplayDec		[edx]
	call	Crlf

	mDisplayString	promptR
	mDisplayDec		[ecx]
	call	Crlf


	pop		ebp
	ret 12
showProblem ENDP

; ------------------------------------------------------
; getData
;
; Prompts the user for their answer, then validates that it is an integer.
; Receives: userAnswer and userAnswerStr by reference.
; Returns: user's answer as an integer
; Preconditions: none
; Registers changed: eax, ebx, ecx, edx, esi, edi
; ------------------------------------------------------
getData PROC
	push	ebp
	mov		ebp, esp

	; Read user input as a string
	GetUserAnswer:
		mDisplayString	promptAnswer
		mov		edx, [ebp + 8]							; move offset of userAnswerStr to ReadString buffer 
		mov		ecx, INPUT_MAX
		call	ReadString
		call	Crlf

		; Move size of inputted string to ecx for looping and clear DF to increment through esi
		mov		ecx, eax
		mov		esi, [ebp + 8]
		mov		edx, 0
		cld

	; Validate each bit to ensure that it is in the range 0-9. If it is, then 
	ValidateInput:
		lodsb											; load esi into AL
		; Check that current bit is within integers 0-9 (48-57 char values)
		cmp		al, 48
		jb		NotInt
		cmp		al, 57
		ja		NotInt
		
		; Convert the string to integer if bit is integer
		movzx	edi, al									; move al to eax, while zero-extending
		mov		ebx, 10
		mov		eax, edx
		mul		ebx										; multiply current integer value by 10
		mov		edx, eax

		sub		edi, 48
		add		edx, edi								; add the integer equivalent to the multiplied value in edx

		loop	ValidateInput
		jmp		ExitGetData

	NotInt:
		mDisplayString	promptNotInt
		call	Crlf
		jmp		GetUserAnswer


	ExitGetData:
		mov		ebx, [ebp + 12]
		mov		[ebx], edx
		; mDisplayDec	[ebx]

	pop		ebp
	ret 8
getData ENDP

; ------------------------------------------------------
; combinations
;
; Evaluates nCr by calling the factorial procedure for n!, r!, and (n-r)!. If n and r are the same, then nCr is = 1.
; Follows the formula n!/(r!*(n-r)!)
; Receives: n and r by value, result by address
; Returns: calculation in result
; Preconditions: integer values in n and r (pre-validated)
; Registers changed: eax, ebx, ecx, edx, esi
; ------------------------------------------------------
combinations PROC
	push	ebp
	mov		ebp, esp

	mov		ecx, [ebp + 16]								; eax holds @n
	mov		edx, [ebp + 12]								; ebx holds @r
	mov		eax, 1										; set to 1 in case of n = r.

	; Check case: If n and r are the same, then nCr is = 1.
	cmp		ecx, edx
	je		ExitCombinations

	Calculate:
		; Calculate denominator (r!*(n-r)!)
		; First calculate r!
		push	edx
		call	factorial
		mov		ebx, eax
		
		; Calculate (n-r)!
		mov		eax, [ebp + 16]
		sub		eax, [ebp + 12]
		mov		edx, eax
		push	edx
		call	factorial
		
		; Multiply r! by (n-r)!
		mul		ebx
		mov		ecx, eax
		
		; Calculate numerator (n!)
		mov		edx, [ebp + 16]
		push	edx
		call	factorial
		
		; Divide numerator by denominator
		xor		edx, edx
		div		ecx


	ExitCombinations:
		mov		ecx, [ebp + 8]							; store @result in ecx
		mov		[ecx], eax								; write evaluated combination into result
		
	pop		ebp
	ret 8
combinations ENDP

; ------------------------------------------------------
; factorial
;
; Utility procedure that calculates the factorial of a given integer parameter.
; Receives: integer in edx register
; Returns: resulting integer in eax register
; Preconditions: parameter is integer
; Registers changed: eax, esi
; ------------------------------------------------------
factorial PROC
	push	ebp
	mov		ebp, esp

	mov		eax, [ebp + 8]

	; Base case: if 1 is reached, then stop recursion
	cmp		eax, 1
	jbe		ExitFactorial

	;
	dec		eax
	push	eax
	call factorial

	mov		esi, [ebp + 8]
	mul		esi
	
	ExitFactorial:
		pop		ebp
	ret 4
factorial ENDP

; ------------------------------------------------------
; showResults
;
; Displays the student’s answer, the calculated result, and a 
; brief statement about the student’s performance.
; Receives: n, r, userAnswer, and result by value, and numCorrect and numWrong by reference
; Returns: changed values of numCorrect and numWrong
; Preconditions: all passed parameters have been evaluated/found.
; Registers changed: eax, ebx, ecx, edx
; ------------------------------------------------------
showResults PROC
	push	ebp
	mov		ebp, esp

	mov		eax, [ebp + 20]								; @n
	mov		ebx, [ebp + 16]								; @r
	mov		ecx, [ebp + 12]								; @result
	mov		edx, [ebp + 8]								; @userAnswer stored

	; Display correct answer
	mDisplayString	displayAnswer1
	mDisplayDec		ecx
	mDisplayString	displayAnswer2
	mDisplayDec		ebx
	mDisplayString	displayAnswer3
	mDisplayDec		eax
	mDisplayString	displayAnswer4


	; Check if userAnswer is same as result
	cmp		ecx, edx
	je		Correct

	mDisplayString	displayWrong
	; Increment numWrong
	mov		eax, [ebp + 24]  
	mov		ebx, [eax] 
	inc		ebx 
	mov		[eax], ebx
	jmp		ExitShowResults

	Correct:
		mDisplayString	displayCorrect
		; Increment numCorrect
		mov		eax, [ebp + 28]  
		mov		ebx, [eax] 
		inc		ebx 
		mov		[eax], ebx

	ExitShowResults:
		pop		ebp
	ret 24
showResults ENDP

END main