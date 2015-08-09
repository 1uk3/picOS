;Copyright (c) 2015, HARTUNG Lukas
;All rights reserved.
;
;Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
;
;1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
;
;2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
;   in the documentation and/or other materials provided with the distribution.
;
;3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from 
;   this software without specific prior written permission.
;   
;4. You may not use this software to operate nuclear facilities, life support, mission critical application where human life or property may be at stake or in any
;   weapon systems.
;   
;5. For non-military use only.
;
;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
;THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
;BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
;OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
;OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



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