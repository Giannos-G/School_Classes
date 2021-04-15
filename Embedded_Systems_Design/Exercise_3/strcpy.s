.text
.align 4 		// code alignment
.global strcpy

.type strcpy, %function

strcpy:
    mov r3, r0 		// save destination for later
    sub r1, r1, #1	// for the first loop

strcpy_loop:
    ldrb r2, [r1, #1]!	// load r1+1 to r2 
    strb r2, [r0], #1	// copy to r0 and then r0 = r0 +1 
    cmp r2, #0		// if we reached the end 
    bne strcpy_loop

exit:
    mov r0, r3		// copy to r3 to be returned 
    bx lr
.data
