.text
.align 4 		/* code alignment */
.global strlen

.type strlen, %function

strlen:

    sub r0, r0, #1 	// for first iteration of loop 
    mov r2, #0 		// initialize to zero 

strlen_loop:
    ldrb r1, [r0, #1]!	// load byte from r0 to r1 and increase r0 +1 
    cmp r1, #0		// if we reached the end - null 
    beq exit
    add r2, r2, #1	// increase length 
    b strlen_loop

exit:
    mov r0, r2		// copy length to r0
    bx lr

.data
