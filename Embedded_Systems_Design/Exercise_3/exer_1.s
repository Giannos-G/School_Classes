.text				//; Executable code follows
    .global 	main		//; main is our main program

    .extern 	printf		//; Using libraries from C
    .extern	scanf
    b		main		//; Start running the main program

/*Registers:
    r0: buffer addr
    r1: length of string 
*/
init_buffer:
    push	{r0-r7, lr}		//lr -> Link Register 
    mov		r2, #0			// Initialization of r2
    init_loop:
        cmp	r1, #0
        beq	end_init
        strb	r2, [r0], #1
        sub	r1, #1			// r1--
        b	init_loop
    end_init:
    pop		{r0-r7, pc}

encrypt:
    push 	{r0-r7, lr}		//Link Register 

    analysis:
        ldrb	r2, [r0]		// r2-> data of r0
        cmp	r2, #65			// Compare with ascii 65-90 -> Uppercase 
        blt	under_upper		// Branch Lower Than- Check if its not upper 
        cmp	r2, #90
        bgt	above_upper		// Branch Greater Than 
            // If it is Uppercase
        add	r2, r2, #32		//adding 32 in ascii - uper->lower
        b	final			//finished with this char

        above_upper:
        cmp		r2, #97 	//Compare with ascii 97-122-> Lowercase 
        blt		final		// Do nothing - been told from the exercise 
        cmp		r2, #122
        bgt		final		// Do nothing - been told from the exercise
            // If if is Lowercase
        sub		r2, #32		//sub 32 in ascii- lower->upper
        b 		final

	under_upper:
            // Check if the char is a number
            cmp		r2, #48		// Ascii 48-57 -> 0-9
            blt		final		// Do nothing 
            cmp		r2, #57
            bgt		final		// DO nothing 
            // If the char is a number
            add		r2, #5		// Been tolf from the exercise 
            cmp		r2, #57		// Compare with 9
            subgt	r2, #10		// sub if gretaer than 9 - To do what is asked from the exercise - 5->0 etc

        final:
        strb	r2, [r0], #1		// the contents of r2 are stored in memory at the address r0 and r0 = r0+1
        cmp	r0, r1			// compare the length of r0 with r1 ->if we reached the end
        bne	analysis
	    // Terminator at the end - Initialization
    	mov	r2, #0			//r2->null
    	strb	r2, [r0]		//store r2 to memory address of r0
last:
    pop		{r0-r7, pc}		// 


main:
main_loop:
    	// Print 
    ldr		r0,= output_str		// variable output_str to be used for printf 
    bl		printf			// r0 buffer addr
    	// Read input until enter is pressed
    ldr		r0, =format		// 
    ldr		r1, =input_str		// variable input_str to be used for scanf and 
    bl		scanf			// stored in r1
   	// Delete newline character from the buffer
    ldr		r0, =format2
    ldr		r1, =tmp		// null - so if we got more than 32 char to be deleted
    bl		scanf
    ldr		r0, =input_str		// in r0 -> string to be encrypted
    ldr		r1, =input_end		// in r1-> length of input_str
	//Check if we read 'Q' or 'q'
    ldrb	r2, [r0] 		// first character is stored to r2
    ldrb	r3, [r0, #1]		// r3 has the value of the next char 
    cmp		r3, #0			// if r3 is "enter" char then we had only 1 character 
    bne		do			// else do the encryption
    ldrb	r2,[r0]
    cmp		r2,#113			// Compare with ascii 'q'
    beq		end
    cmp		r2,#81			// Compare with ascii 'Q'
    beq		end

do:
    	// Encryption of the string
    ldr		r0, =input_str
    ldr		r1, =input_end
    bl		encrypt

    	// Print the encrypted string
    ldr		r0, =input_str		//encrypted string is in r0		
    bl		printf

    	// Print a newline
    ldr		r0, =newline
    bl		printf

    	// Fill the buffer with \0-null to prepare for the next iteration
    ldr		r0, =input_str
    mov		r1, #8			// 8blocks*4-number of char in a block- = 32 (1 char malloc 1byte) 
    bl		init_buffer
   	// Another iteration until 'Q' or 'q' is entered
    b		main_loop

end:
	mov r0, #0 			// exit status 0
	mov r7, #1			// number of exit syscall
	swi 0

.data
    newline: 	.ascii "\n\0"
    format:	.string "%[^\n]"		//all characters except new line 
    format2:	.string "%c"			// numeric character code - ascii

    output_str: .ascii "Please input a string 32 char long: \0"
    output_len 	= . - output_str

    input_str: .ascii "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    input_end	= .

    tmp:	.ascii "\0"
