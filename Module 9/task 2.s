.text
        .global _start

_start:
        LDR     r4, =data         @ r4 = base of array

        MOV     r0, #0            @ zero count
        MOV     r1, #0            @ positive count
        MOV     r2, #0            @ negative count

loop2:
        LDR     r3, [r4], #4      @ load element, advance pointer
        CMP     r3, #0x7FFFFFFF   @ compare with sentinel
        BEQ     done2             @ if sentinel, stop

        CMP     r3, #0
        BEQ     incz2
        BGT     incp2
        @ else negative
        ADD     r2, r2, #1
        B       cont2

incz2:
        ADD     r0, r0, #1
        B       cont2

incp2:
        ADD     r1, r1, #1

cont2:
        B       loop2

done2:
        B       done2

        .data
data:
        .word  5, -3, 0, 12, 0, -7, 8, -1, 0, 10, 0x7FFFFFFF
