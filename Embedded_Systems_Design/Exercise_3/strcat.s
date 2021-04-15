.text
.align 4 /* code alignment */
.global strcat

.type strcat, %function

strcat:
    mov r3, r0 		// save the original position of destination
    sub r0, r0, #1 	// this is for the first iteration of the loop end_of_dest
    sub r1, r1, #1 	// this is for the first iteration of the loop strcat_loop 

end_of_dest:
    ldrb r2, [r0, #1]! 	// load byte on r2 from r0 + 1 memory addr 
    cmp r2, #0 		// 0 is the ascii for no more chars - end 
    bne end_of_dest	// until r2 is full with r0 

strcat_loop:
    ldrb r2, [r1, #1]!	// load byte on r2 from r1+1 memory addr 
    strb r2, [r0], #1	// store byte from r2 to r0+1
    cmp r2, #0		// end
    bne strcat_loop

exit: 
    mov r0, r3		// move from r0 to r3 so we have the new string in r3 
    bx lr

.data
