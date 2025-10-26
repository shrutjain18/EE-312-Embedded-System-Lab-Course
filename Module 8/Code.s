.section .data 
led_base:  .word 0xff200000  @ label for led base address 
seg_base: .word 0xff200020 @ label for 7segment base address 
seg_patterns: .byte 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 
0x6F 
 
.section .text 
.global _start 
_start: 
    ldr r0, =led_base 
    ldr r0, [r0]  @ loading base address value into r0 
    ldr r1, =seg_base 
    ldr r1, [r1] @ loading 7-segments' base address into r1 
    ldr r8, =seg_patterns 
     
 @ clear all bits  
    mov r2, #0 
    str r2, [r0]  
    str r2, [r1]  
     
    mov r2, #0x21 @ value for north-red east-green 
    mov r3, #0x0c @ value for north-green east-red 
    mov r4, #0x12 @ value for all yellow 
     
    mov r5, #150 @ counter for 150 seconds 
    mov r6, #030 @ counter for 30 seconds 
     
loop: 
 
    @ north south red, east west green 
    str r2, [r0] @ set LEDs 
    mov r7, r5 
    bl _delay @ 150sec timer 
  
    @ all yellow 
    str r4, [r0] @ set LEDs 
    mov r7, r6 
    bl _delay @ 30sec timer 
  
    @ north-south green, east west red     
    str r3, [r0] @ set LEDs 
    mov r7, r5 
    bl _delay @ 150sec timer 
  
    @ all yellow 
    str r4, [r0] @ set LEDs 
    mov r7, r6 
    bl _delay @ 30sec timer 
     
    b loop 
 
_delay:     
    push {lr}  @ Save the link register 
_delay_loop: 
    sub r7, r7, #1 
    bl display 
 cmp r7, #0 
    bne _delay_loop 
    pop {pc}  @ Return to the caller 
 
display: 
    push {lr}  @ Save registers we'll be using 
    @displaying in 7segment 
    mov r9, r7 @ will have ones digit 
    mov r10, #0 @ tens 
    mov r11, #0 @ hundreds 
     
    @extract hundreds 
hundreds_loop: 
    cmp r9, #100 
    blt hundreds_done 
    sub r9, r9, #100 
    add r11, r11, #1 
    b hundreds_loop 
hundreds_done: 
    @ r11 has hundreds digit 
     
    @ get tens 
tens_loop: 
    cmp r9, #10 
    blt tens_done 
    sub r9, r9, #10 
    add r10, r10, #1 
    b tens_loop 
tens_done: 
    @ r9 has ones digit 
    @ r10 has tens digit 
     
    @ display 100s 
    ldrb r12, [r8, r11] 
    strb r12, [r1, #2] 
     
    @ display 10s 
    ldrb r12, [r8, r10] 
    strb r12, [r1, #1] 
     
    @ display 1s 
    ldrb r12, [r8, r9] 
    strb r12, [r1] 
     
    pop {pc}  @ Restore registers and return
