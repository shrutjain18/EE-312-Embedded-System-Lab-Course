.section .data
.align 2
uart_base: .word 0xFF201000

dj: .asciz "Srishti\n"
rd: .asciz "Shrut\n"
gp: .asciz "Sonal\n"
ab: .asciz "Shibarpita\n"

.align 2
names:
    .word dj
    .word rd
    .word gp
    .word ab


.section .text
.global _start
_start:
    ldr r0, =uart_base        @ r0 = &uart_base
    ldr r0, [r0]              @ r0 = UART base address

    ldr r1, =names            @ r1 = &names
    mov r8, #0                @ r8 = index
    mov r9, #4                @ r9 = number of names

    ldr r10, =0x00002000      @ destination base address in memory


@ -------------------------------
@ Print all names to UART
@ -------------------------------
print_names_loop:
    cmp r8, r9
    bge store_init             @ after printing all, go to store

    ldr r4, [r1, r8, lsl #2]   @ r4 = names[r8]
    bl print_string

    add r8, r8, #1
    b print_names_loop


@ Print null-terminated string pointed by r4
print_string:
    push {lr}
print_loop:
    ldrb r5, [r4], #1
    cmp r5, #0
    beq print_done

wait_loop:
    ldr r2, [r0, #8]
    and r2, r2, #0x20
    cmp r2, #0
    beq wait_loop

    str r5, [r0]
    b print_loop

print_done:
    pop {pc}


@ -------------------------------
@ Store all names to memory 0x2000
@ -------------------------------
store_init:
    mov r8, #0                 @ reset index for storing

store_names_loop:
    cmp r8, r9
    bge end                    @ done

    ldr r4, [r1, r8, lsl #2]   @ r4 = names[r8]
    bl store_string

    add r8, r8, #1
    b store_names_loop


@ Store null-terminated string from r4 to [r10], update r10
store_string:
    push {lr}
store_loop:
    ldrb r5, [r4], #1          @ Load next byte
    strb r5, [r10], #1         @ Store to memory
    cmp r5, #0
    bne store_loop
    pop {pc}


@ -------------------------------
@ Infinite loop to end program
@ -------------------------------
end:
    b end
