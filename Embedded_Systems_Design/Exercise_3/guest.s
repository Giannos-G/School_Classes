.text
.global main
.extern printf
.extern tcsetattr

str_man:	/* gets input string in r0, outputs number of char in r1 and char in r2 */
  stmfd sp!, {r4-r6, ip, lr}
  mov r4, #0
  mov r2, r0
  mov r3, r0
  str_man_loop:
    ldrb r1, [r3]	/* load test char in r1 */
    tst r1, r1		/* check if end of string */
    beq str_man_cnt
    ldrb r1, [r3], #1
    bl strcmp		/* strcmp returns number of current char in r0 */
    cmp r0, r4		/* find if this char is the most common so far */
    blt str_man_loop	/* if not continue with next char */
    beq str_man_equal	/* if it is equal with the previous, compare their ASCII codes */
    mov r5, r1		/* else it is, so r5 holds output char */
    mov r4, r0		/* and r4 holds number of output char */
    b str_man_loop
  str_man_equal:
    cmp r1, r5
    bge str_man_loop
    mov r5, r1
    b str_man_loop
  str_man_cnt:
    mov r1, r4		/* r0 holds number */
    mov r2, r5		/* r1 holds char */
    ldmfd sp!, {r4-r6, ip, lr}
    bx lr
	
strcmp:		/* gets string in r2, test char in r1 */
  stmfd sp!, {r1-r3, ip, lr}
  mov r0, #0
  strcmp_loop:
    ldrb r3, [r2]
    tst r3, r3		/* find end of string */
    beq strcmp_cnt
    ldrb r3, [r2], #1
    cmp r1, r3
    bne strcmp_loop
    add r0, r0, #1	/* return output in r0 */
    b strcmp_loop
  strcmp_cnt:
    ldmfd sp!, {r1-r3, ip, lr}
    bx lr

main:
	stmfd sp!, {r4-r9}
	
	/* open device */
	ldr r0, =pathname
	ldr r2, =flags
	ldr r1, [r2]
	mov r7, #5
	swi 0
	mov r6, r0		/* store file descriptor of serial port in r6 */
	
set_device:
	mov r0, r6
	mov r1, #0
	ldr r2, =options	/* load options memory address */
	bl tcsetattr

	mov r8, #0		/* r8 holds counter for chars we have read */

read:
	/* read input char */
	mov r0, r6	 		/* r6 has file descriptor of serial port */
	ldr r1, =input_char
	mov r2, #1
	mov r7, #3
	swi 0
	cmp r0, #1
	bne read	/* if 0 bytes are read, read again */
	
	/* create string */
	ldr r0, =input_char
	ldr r1, [r0]
	ldr r2, =string
	str r1, [r2, r8]

	add r8, r8, #1

	ldr r1, =input_char
	ldrb r2, [r1]
	cmp r2, #0
	bne read	/* if character is null stop reading */

	/* string manipulation */
	ldr r0, =string
	bl str_man

	/* return to host the most common char and its frequency */
	mov r8, r1	/* r8 gets frequency of most common char */
	mov r9, r2	/* r9 gets most common char */

	/* snprintf writes first part (format_2) on buffer output */
	push {ip, lr}
	ldr r0, =output
	mov r1, #35
	ldr r2, =format_2
	mov r3, r9
	bl snprintf
	pop {ip, lr}

	/* write string that is stored in buffer output back to host through serial port*/
	mov r0, #1
	ldr r1, =output
	mov r2, #34
	mov r7, #4
	swi 0
 
	/* snprintf for second part (format_3) */
	push {ip, lr}
	ldr r0, =output
	mov r1, #28
	ldr r2, =format_3
	mov r3, r8
	bl snprintf
	pop {ip, lr}

	/* write */
	mov r0, #1
	ldr r1, =output
	mov r2, #27		//escape
	mov r7, #4 		//end of transmition
	swi 0
exit:
	/* close fd of serial port */
	mov r0, r6
	mov r7, #6
	swi 0

	/* exit */
	ldmfd sp!, {r4-r9}
	mov r0, #0	/* status = 0, everything ok */
	mov r7, #1	/* exit*/
	swi 0

.data
	pathname: .asciz "/dev/ttyAMA0"
	flags: .word 0x00000902
	string: .space 64
	format_2: .asciz "The most frequent character is '%c'"
	format_3: .asciz " and it appeared %d times.\n"
	input_char: .asciz "a"
	output: .space 35

	options:	.word 0x000000c3	/* c_iflag	*/
			.word 0x00000000	/* c_oflag 	*/
			.word 0x000008bd	/* c_cflag 	*/
			.word 0x00007f00	/* c_lflag 	*/
			.byte 0x00		/* c_line 	*/
			.word 0x00000000	/* c_cc[0-3] 	*/
			.word 0x00010000	/* c_cc[4-7] 	*/
			.word 0x00000000	/* c_cc[8-11] 	*/
			.word 0x00000000	/* c_cc[12-15] 	*/
			.word 0x00000000	/* c_cc[16-19] 	*/
			.word 0x00000000	/* c_cc[20-23] 	*/
			.word 0x00000000	/* c_cc[24-27] 	*/
			.word 0x00000000	/* c_cc[28-31] 	*/
			.byte 0x00		/* padding 	*/
			.hword 0x0000		/* padding 	*/
			.word 0x0000000		/* c_ispeed 	*/
			.word 0x0000000		/* c_ospeed 	*/


/*		--oct--		----binary----
 * BAUDRATE	0000015		0000 0000 1101
 * CS8		0000060		0000 0011 0000
 * CREAD	0000200		0000 1000 0000
 * CLOCAL	0004000		1000 0000 0000
 *
 * FLAG:	0004275		1000 1011 1101	
 *
 * bin:100010111101
 * hex: 0x000008bd
 * dec: 2237
 */	
