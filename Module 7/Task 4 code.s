.global _start
_start:

    MOV R1, #50          @ R1 = 50
    MOV R2, #200         @ R2 = 200

   
    ADDS R3, R1, R2      @ R3 = R1 + R2, updates NZCV
    @ Check CPSR flags here

   
    SUBS R4, R1, R2      @ R4 = R1 - R2, updates NZCV
    @ Check CPSR flags

   
    MULS R5, R1, R2      @ R5 = R1 * R2, updates N/Z
    @ Check CPSR flags

    
    MOV R6, #0           @ Quotient = 0
    MOV R7, R2           @ Dividend = R2 = 200
    MOV R8, #10          @ Divisor = 10

div_loop:
    CMP R7, R8           @ Compare dividend with divisor
    BLT div_done         @ If dividend < divisor, exit loop
    SUBS R7, R7, R8      @ dividend -= divisor
    ADD R6, R6, #1       @ quotient++
    B div_loop

div_done:
    @ After loop: R6 = quotient, R7 = remainder
    @ Check CPSR flags

    @ ---------- ZERO TEST ----------
    SUBS R9, R6, #20     @ R9 = R6 - 20 (should set Z=1 if R6==20)
    @ Check CPSR flags here

end:
    B end                @ Infinite loop to stop execution
