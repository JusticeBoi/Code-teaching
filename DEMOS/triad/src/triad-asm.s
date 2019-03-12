.intel_syntax noprefix
.data
.align 64
SCALAR:
.double 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0

.text
.globl triad_asm
.type triad_asm, @function
triad_asm :
push rbp
mov rbp, rsp
push rbx
push r12
push r13
push r14
push r15

xor   rax, rax
.align 16
1:
vmovaps ymm1, [rdx + rax*8]
vmovaps ymm2, [rdx + rax*8+32]
vmovaps ymm3, [rdx + rax*8+64]
vmovaps ymm4, [rdx + rax*8+96]
vmulpd  ymm1, ymm1, [rcx + rax*8]
vaddpd  ymm1, ymm1, [r8 + rax*8]
vmulpd  ymm2, ymm2, [rcx + rax*8+32]
vaddpd  ymm2, ymm2, [r8 + rax*8+32]
vmulpd  ymm3, ymm3, [rcx + rax*8+64]
vaddpd  ymm3, ymm3, [r8 + rax*8+64]
vmulpd  ymm4, ymm4, [rcx + rax*8+96]
vaddpd  ymm4, ymm4, [r8 + rax*8+96]
vmovaps [rsi + rax*8], ymm1
vmovaps [rsi + rax*8+32], ymm2
vmovaps [rsi + rax*8+64], ymm3
vmovaps [rsi + rax*8+96], ymm4
addq rax, 16
cmpq rax, rdi
jl 1b

pop r15
pop r14
pop r13
pop r12
pop rbx
mov  rsp, rbp
pop rbp
ret
.size triad_asm, .-triad_asm

