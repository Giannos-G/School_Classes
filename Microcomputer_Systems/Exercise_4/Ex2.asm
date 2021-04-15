.include "m16def.inc"
.DEF A=r16		;dilosi katathoriton
.DEF B=r17
.DEF C=r18
.DEF CN=r19
.DEF D=r20
.DEF t=r21
.DEF F0=r22
.DEF F1=r23
.DEF temp=r24

.cseg
.org 0			;dieuthinsi ekkinisis
main: 
ser t			;1111111111111
in  t, pina	;diavazei apo to PORT A
out DDRB,t		;PORT B as output

mov A,t			;vazw to A sto lsb tou katatoriti A=r16
lsr t			;deksia olisthisi->lsb = B
mov B,t			;vazw to B sto lsb tou katatoriti B=r17
lsr t			;deksia olitshtisi->lsb=C
mov C,t
mov CN,t
com CN			;simpliroma tou C
lsr t			;deksia olisthisi->lsb = D
mov D,t

mov temp,A		;temp=A
and temp,B		;temp=A*B
and temp,C		;temp=A*B*C
and CN,D		;CN=CN*D
or temp,CN		;temp=ABC+C'D
com temp		;temp=(ABC+C'D)'
mov F0,temp		;F0=(ABC+C'D)'
andi F0,1		;apomonosi LSB

or A,B			;A=A+B
or C,D			;C=C+D
and A,C			;A=(A+B)(C+B)
mov F1,A		;F1=(A+B)(C+B)
andi F1,1		;apomonosi LSB
lsl F1			;aristeri olisthisi
add F0,F1
out PORTB, F0
rjmp main