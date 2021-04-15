.text
.align 4 		/* code alignment */
.global strcmp

.type strcmp, %function

strcmp:
    push {r4} 		// Save r4 for recovery according to conventions 
    mov r4, #0 		// result stored in r4 initialization -  we set to 0 
    sub r1, r1, #1 	// for the first time the loop runs 
    sub r0, r0, #1 	// for the first time the loop runs 

strcmp_loop:
    ldrb r2, [r0, #1]! 	// check next char
    ldrb r3, [r1, #1]! 	// check next char 
    cmp r2, r3 		// compare chars 
    beq equal
    cmp r2, r3 
    movgt r4, #1 	// if first string is bigger return 1 
    cmp r2, r3
    blt minus_one 	// calculate minus 1
    b exit

minus_one:		// returns minus one  - 2s Complement 
    mvn r4, #1 		// calculate 1st complement
    add r4, r4, #1 	// add one for two complemet 
    b exit

equal:
    cmp r2, #0 		// if they are equal and one of the two is 0, then both are 0 and we reached the end 
    bne strcmp_loop
    mov r4, #0 		// else if they reach the end of the string return 0 
    b exit

exit:
    mov r0, r4
    pop {r4}
    bx lr

.data
