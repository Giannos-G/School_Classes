.include "m16def.inc"

reset: 
ldi r24 , low(RAMEND) ; initialize stack pointer
out SPL , r24
ldi r24 , high(RAMEND)
out SPH , r24
ser r24 ; initialize PORTB for output
out DDRB , r24
clr r26 ; clear counter
clr r27  ; clear time counter
ldi r26, 1				; load number 1

main: 
in r18, pina		;check if PA0 is pressed
andi r18, 0x01		;
cpi r18, 0x01		;
breq main			;
out PORTB , r26
ldi r24 , low(500)		; load r25:r24 with 500
ldi r25 , high(500)		
rcall wait_msec			; delay 0.5 seconds
lsl r26					;shift left logical 
cpi r26 , 128			; compare counter with 128, the last bit 2^7
brlo main				; if lower goto main, else go backwards shift right logical

back:
in r18, pina		;check if PA0 is pressed
andi r18, 0x01		;
cpi r18, 0x01		;
breq back			;
out PORTB , r26				
lsr r26					; shift right logical
cpi r26 , 1				; compare time counter with 1, the first bit 2^0
breq main				; if equal go to main, else keep going backwards
ldi r24 , low(500)		; load r25:r24 with 500
ldi r25 , high(500)		; delay 0.5 seconds
rcall wait_msec
rjmp back

wait_msec:
push r24 ; 2 κύκλοι (0.250 μsec)
push r25 ; 2 κύκλοι
ldi r24 , low(498) ; φόρτωσε τον καταχ. r25:r24 με 998 (1 κύκλος - 0.125 μsec)
ldi r25 , high(498) ; 1 κύκλος (0.125 μsec)
rcall wait_usec ; 3 κύκλοι (0.375 μsec), προκαλεί συνολικά καθυστέρηση 998.375 μsec
pop r25 ; 2 κύκλοι (0.250 μsec)
pop r24 ; 2 κύκλοι
sbiw r24 , 1 ; 2 κύκλοι
brne wait_msec ; 1 ή 2 κύκλοι (0.125 ή 0.250 μsec)
ret ; 4 κύκλοι (0.500 μsec)

wait_usec:
sbiw r24 ,1 ; 2 κύκλοι (0.250 μsec)
nop ; 1 κύκλος (0.125 μsec)
nop ; 1 κύκλος (0.125 μsec)
nop ; 1 κύκλος (0.125 μsec)
nop ; 1 κύκλος (0.125 μsec)
brne wait_usec ; 1 ή 2 κύκλοι (0.125 ή 0.250 μsec)
ret ; 4 κύκλοι (0.500 μsec)