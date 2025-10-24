.text
        .global _start

_start:
        @ Setup: address of array, counters
        LDR     r4, =data         @ r4 = base address of the array
        MOV     r5, #10           @ r5 = n (number of elements)

        MOV     r0, #0            @ count_zero = 0
        MOV     r1, #0            @ count_pos = 0
        MOV     r2, #0            @ count_neg = 0

loop:
        CMP     r5, #0
        BEQ     done

        LDR     r3, [r4], #4      @ load *r4 into r3, then r4 += 4
        CMP     r3, #0
        BEQ     inc_zero
        BGT     inc_pos
        @ else negative
        ADD     r2, r2, #1
        B       cont

inc_zero:
        ADD     r0, r0, #1
        B       cont

inc_pos:
        ADD     r1, r1, #1

cont:
        SUB     r5, r5, #1
        B       loop

done:
        @ At this point, r0 = zero count, r1 = positive count, r2 = negative count
        @ You can now e.g. put them somewhere in memory, or loop forever, or use them as outputs.

        B       done      @ infinite loop to end

        .data
data:
        .word  5, -3, 0, 12, 0, -7, 8, -1, 0, 10
