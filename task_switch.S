 AREA    |.text|, CODE, READONLY

save_context  PROC {}
        GLOBAL save_context
        MRS r0, psp
        SUBS r0,r0,#32    ;no memory decreasing read available on cortex m0
                  ;read bottom to top and then reset
        STMEA r0!, {r4-r7}
        MOV r4, r8
        MOV r5, r9
        MOV r6, r10
        MOV r7, r11
        STMEA r0!, {r4-r7}
        SUBS r0,r0,#32  
        MSR psp, r0
        BX LR
        ENDP

load_context  PROC {}
        GLOBAL load_context
        MRS r0, psp
        LDMIA r0!, {r4-r7}
        LDMIA r0!, {r1-r2}
        MOV r8, r1
        MOV r9, r2
        LDMIA r0!, {r1-r2}
        MOV r10, r1
        MOV r11, r2
        MSR psp, r0
        ;movs r0, #3
        ;msr control, r0  ;set PSP next
        ;isb        ;flush pipeline
        MOVS r0, #2;bitwise invert 2 to get 0xFFFFFFFD
        MVNS r0, r0
        BX r0;use PSP after return
        ENDP
        
        END