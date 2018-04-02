TITLE Program 5     (program5.asm)

; Author: Prathyoosha Chaya, chayap@oregonstate.edu
; Course / Project ID: CS 271 Sec. 001				Due Date: 03/04/2018
; Description: Assignment 5. This program receives a number from the user for the max number of random 
;		numbers to generate. It then fills this number of elements with random numbers, sorts it, 
;		and displays the pre-sorted and sorted values. It finally finds the median value and prints it.
INCLUDE Irvine32.inc

.data
; Constants used:
INPUT_MAX		EQU			200					; used to check if inputted value is in range
INPUT_MIN		EQU			10	
LO				EQU			100					; ranges for random numbers
HI				EQU			999
N				EQU			900					; (N = HI - LO + 1). N-1 is used for RandomRange call
NUMS_PER_LINE	EQU			10					; numbers per row of display

; Output messages, all are used globally with exception of display Unsorted and displaySorted
prompt1			BYTE		"Sorting Random Integers, Programmed by Prathyoosha Chaya", 10, 0
prompt2			BYTE		"This program generates random numbers in the range [100 .. 999], ", 10, 0
prompt3			BYTE		"displays the original list, sorts the list, and calculates the ", 10, 0
prompt4			BYTE		"median value.  Finally, it displays the list sorted in descending order. ", 10, 0
promptNum		BYTE		"How many numbers should be generated? [10 .. 200]: ", 0
promptOoR		BYTE		"Out of range. Please enter a number in [10, 200].", 10, 0
displayUnsorted	BYTE		"The unsorted random numbers: ", 0
medianPrompt	BYTE		"The median is ", 0
displaySorted	BYTE		"The sorted list: ", 10, 0
goodbye			BYTE		"That's all. Goodbye!", 10, 0
spaces			BYTE		"    ", 0
test1			BYTE		"even", 0

; Values/data to be used
request			DWORD		?					; Holds user-inputted max number of random ints to fill
arr				DWORD		INPUT_MAX DUP(?)	; Array holding random ints
ooRange			DWORD		0					; out of range flag

.code
main PROC
	call	introduction
	
	; passing request by address to getData
	push	OFFSET request
	call	getData

	; pass request by value and arr as reference to fillArray
	push	request
	push	OFFSET arr
	call	fillArray
	
	; DISPLAY UNSORTED: pass request by value, arr as reference, and title by value to displayArray
	push	request
	push	OFFSET arr		
	push	OFFSET displayUnsorted			
	call	displayArray

	; pass request by value and arr by reference to sortList
	push	request
	push	OFFSET arr
	call	sortList

	; DISPLAY SORTED: pass request by value, arr as reference, and title by value to displayArray
	push	request
	push	OFFSET arr		
	push	OFFSET displaySorted			
	call	displayArray

	push	request
	push	OFFSET arr
	call	displayMedian

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
	mov		edx, OFFSET prompt2
	call	WriteString
	mov		edx, OFFSET prompt3
	call	WriteString
	mov		edx, OFFSET prompt4
	call	WriteString
	call	Crlf

	ret
introduction ENDP	

; ------------------------------------------------------i
; getData
;
; Receives user inputted integer for request, then validates that request is in range [10,200].
; Receives: @request.
; Returns: updated request.
; ------------------------------------------------------
getData PROC
	;pushad
    push	ebp											; to save ebp to return to original value later
	mov		ebp, esp									; set ebp to stack pointer
	;pushad

	mov		ebx, [ebp + 8]								; mov value of @request to ebx

	Begin:
		mov		edx, OFFSET promptNum
		call	WriteString
		call	ReadInt
		call	Crlf

		; Compare request to range limits, if not within limits, then preserve value
		cmp		eax, INPUT_MAX
		jg		DisplayOoR
		cmp		eax, INPUT_MIN
		jl		DisplayOoR
		
		mov     [ebx], eax								; Store eax as value of @ebx (which is @request, or ebp+8)
		jmp		ExitGetData								; value must be in range, so exit

		; Display out of range
	DisplayOoR:
		mov		edx, OFFSET promptOoR
		call	WriteString
		call	Crlf
		jmp		Begin

	ExitGetData:
		pop		ebp
		ret		8										; return stack with original ebp
getData ENDP


; ------------------------------------------------------
; fillArray
;
; Fills the array with random integers in the range 
; Receives: request (by value), array (currently unsorted, by reference).
; Returns: arr filled with random ints, until index specified by request.
; ------------------------------------------------------
fillArray PROC
	push	ebp											; to save ebp to return to original value later
	mov		ebp, esp									; set ebp to stack pointer
	
	mov		ecx, [ebp+12]								; set loop counter to request value
	mov		esi, [ebp+8]								; set esi to base address of arr

	call	Randomize									; set random seed based on system clock

	FillArr:
		mov		eax, N
		call	RandomRange								; uses eax value(N) - 1, thus finds a random int in range [0, 899]
		add		eax, LO									; LO = 100, changes range from [0, 899] to desired [100, 999]
		mov		[esi], eax								; store random int into current arr value
		add		esi, 4									; increment to next element by adding TYPE DWORD
		loop	FillArr

	ExitFillArray:
		pop		ebp
		ret		8										; return stack with original ebp	
fillArray ENDP

; ------------------------------------------------------
; displayArray
;
; Displays the array (called for both unsortted and sorted array)
; Receives: request (by value), array (currently unsorted, by reference), and the title (reference).
; Returns: none.
; ------------------------------------------------------
displayArray PROC
	push	ebp											; to save ebp to return to original value later
	mov		ebp, esp									; set ebp to stack pointer

	mov		ecx, [ebp+16]								; set loop counter to request value
	mov		esi, [ebp+12]								; set esi to base address of arr
	mov		edx, [ebp+8]								; title value, wither displayUnsorted or displaySorted
	mov		ebx, NUMS_PER_LINE							; column count

	call	Crlf
	call	WriteString									; print the respective title, either sorted or unsorted
	call	CrLf

	DisplayElement:
		mov		eax, [esi]								; move currrent arr value to be displayed
		call	WriteDec
		mov		edx, OFFSET spaces
		call	WriteString
		add		esi, 4									; look at next element in arr, by adding TYPE DWORD

		; Check if 10th number to print new line
		dec		ecx
        mov		eax, ecx
		inc		ecx
        mov		ebx, NUMS_PER_LINE						; divide by max numbers per line (10) by loop count to check mod value stored in edx
        xor		edx, edx                     
        div		ebx										; divides by 10, if R=0 then 10 numbers on line

        cmp		edx, 0									; edx is 0 if there are 10 numbers per line
        jne		LessThan10								; prints or does not print new line
          
        call CrLf

        LessThan10:
			loop	DisplayElement

	pop		ebp
	ret		8											; return stack with original ebp	
displayArray ENDP

; ------------------------------------------------------
; sortList
;
; Sorts the unsorted array of random ints.
; Receives: request (by value) and array (currently unsorted, by reference).
; Returns: arr with sorted ints.
; ------------------------------------------------------
sortList PROC
	push	ebp											; to save ebp to return to original value later
	mov		ebp, esp									; set ebp to stack pointer

	mov		ecx, [ebp+12]								; set loop counter to request value - 1
	dec		ecx
	
	; This first loop will reset the arr address to compare to the first value, and execute it's inner loop until request-1 elements are reached.
	ResetLoop:
		mov		esi, [ebp+8]							; set esi to base address of arr
		push	ecx										; push ecx in order to preserve value
		; This loop compares the values within the first element of arr and the current index (incremented until arr is fully traversed.)
		CompareLoop:
			mov		ebx, [esi+4]
			cmp		[esi], ebx							; compare current element to proceeding element by accessing esi + TYPE DWORD
			jle		ExchangeValues
			jg		Ignore

			; esi+4 is greater than esi, so push arguments and call the exchange procedure
			ExchangeValues:
				push	esi
				mov		edi, esi
				add		edi, 4
				push	edi
				call	exchangeElements

			; esi is greater than esi+4, so increment esi to check next two values.
			Ignore:
				add		esi, 4
				loop	CompareLoop

			pop		ecx
			loop	ResetLoop
			
	pop		ebp
	ret		8
sortList ENDP

; ------------------------------------------------------
; exchangeElements
;
; A utility procedure used by sortList that given two array indexes, will swap the values held.
; Receives: arr index 1 (by reference) and arr index 2 (by reference).
; Returns: arr with values ar indices exchanged.
; ------------------------------------------------------
exchangeElements PROC
	push	ebp
	mov		ebp, esp
	pushad												; preserve old register values

	; First store arr value that is greater (pushed as edi by sortList procedure)
	mov		eax, [ebp+8]
	mov		ecx, [eax]

	; Next store arr value that is smaller (pushed as esi by sortList procedure)
	mov		ebx, [ebp+12]
	mov		edx, [ebx]

	; Exchange values of both arr indexes
	xchg	edx, ecx				; swap values

	; Write the swapped values into back into arr
	mov		[ebx], edx				; implement values
	mov		[eax], ecx


	popad												; restore old gen-purpose register values
	pop		ebp
	ret		8											; return stack with original ebp

exchangeElements ENDP

; ------------------------------------------------------
; displayMedian
;
; This procedure finds the median of the sorted values and displays it.
; Receives: arr by reference and request by value.
; Returns: median value.
; ------------------------------------------------------
displayMedian PROC
	push	ebp
	mov		ebp, esp

	; Display message
	call	Crlf
	mov		edx, OFFSET medianPrompt
	call	WriteString	

	mov		esi, [ebp+8]								; set esi to base address of arr

	; Divide request by 2 to determine if there are an odd or even number of elements in arr
	mov		eax, [ebp+12]								; [ebp+12] holds value of request
	mov		ebx, 2
	xor		edx, edx
	div		ebx

	; If R=0 from previous division, then request is even. In this case, the average must be found.
	cmp		edx, 0
	jne		FindMedian									; odd number of elements, so immedietly print values in EAX
	je		FindAveragedMedian							; even number, so additional calculation must be done

	FindAveragedMedian:
		; EAX holds request /2, which can be used to find the middle value.
		mov		ebx, 4
		mul		ebx
		add		esi, eax								; go to median value of array (or first value to be averaged, in case of even request)
		mov		eax, [esi]								; move value of median element to eax to be printed

		; First average the two median values
		xor		edx, edx
		add		eax, [esi+4]							; add to next element (esi + TYPE DWORD)	
		mov		ebx, 2
		div		ebx

		; Add the remainder to the result to round. If the remainder is 0, then no rounding is necessary.
		; If the remainder is 1, then we must round to the next integer
		add		eax, edx
		jmp		ExitDisplayMedian

	FindMedian:
		; EAX holds request /2, which can be used to find the middle value.
		mov		ebx, 4
		mul		ebx
		add		esi, eax									; go to median value of array (or first value to be averaged, in case of even request)
		mov		eax, [esi]									; move value of median element to eax to be printed

	ExitDisplayMedian:
		call		WriteDec
		call		CrLf
		pop		ebp
		ret		8
displayMedian ENDP

; ------------------------------------------------------
; farewell
;
; Displays farewell message to user.
; Receives: none.
; Returns: none.
; ------------------------------------------------------
farewell PROC
	call	Crlf
	mov		edx, OFFSET goodbye
	call	WriteString
	call	Crlf

	ret
farewell ENDP


END main