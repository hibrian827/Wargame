#!/usr/bin/python3

import tempfile
import os
import subprocess
import sys
import random

def sanitize_asm(asm, whitelists, blacklists):
    asm = asm.lower()

    if len(asm) > 1000:
        print("[-] You don't test the mighty ASMan.")
        print("[-] The mighty ASMan do not want you to go easy way")
        sys.exit(-1)


    if len(whitelists) > 0:
        for line in [x.strip() for x in asm.split("\n")]:
            if ";" in line:
                print("[-] You should speak each assembly in a single line")
                sys.exit(-1)

            if len(line) == 0:
                continue
            matches = [k for k in whitelists if line.startswith(k)]
            if len(matches) == 0:
                print("[-] You don't test the mighty ASMan.")
                print("[-] The mighty ASMan wants you to speak specific words")
                sys.exit(-1)

    for k in blacklists:
        if k in asm:
            print("[-] You don't test the mighty ASMan.")
            print("[-] The mighty ASMan DO NOT want you to speak specific words")
            sys.exit(-1)
    return

def gen_full_asm(asm):
    header = '''	.file	"stub.c"
	.text
	.globl	compute
	.type	compute, @function
compute:
'''

    footer = '''
	ret
	.size	compute, .-compute
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp	#
	movq	%rsp, %rbp	#,
	subq	$16, %rsp	#,
	movl	$0, %eax	#,
	call	compute	#
	movl	%eax, -4(%rbp)	# tmp84, res
	movl	-4(%rbp), %eax	# res, tmp85
	movl	%eax, %esi	# tmp85,
	leaq	.LC0(%rip), %rax	#, tmp86
	movq	%rax, %rdi	# tmp86,
	movl	$0, %eax	#,
	call	printf@PLT	#
	movl	$0, %eax	#, _5
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
'''

    full_asm = header + "\n".join(["\t" + x for x in asm.split("\n")]) + footer
    return full_asm

def build_asm(asm):
    global dn
    asm_fn = os.path.join(dn, "test.s")
    exe_fn = os.path.join(dn, "test.out")

    open(asm_fn, "w").write(asm)
    cmd_str = "gcc %s -o %s" % (asm_fn, exe_fn)
    cmds = cmd_str.split()

    try:
        subprocess.run(cmds, stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE,
                       check=True)
    except subprocess.CalledProcessError as e:
        print("[-] The mighty ASMan wants you to study more")
        sys.exit(-1)
    return exe_fn

def run_prog(exe_fn):
    res = subprocess.check_output(exe_fn, shell=True)
    return res.decode().strip()

def build_and_run(asm, whitelists, blacklists):
    sanitize_asm(asm, whitelists, blacklists)
    full_asm = gen_full_asm(asm)
    exe_fn = build_asm(full_asm)
    your_answer = run_prog(exe_fn)
    return your_answer

def round(whitelists, blacklists):
    global test_answer
    global round_num

    round_num += 1

    if test_answer == None:
       answer = str(random.randint(0, 1000))
    else:
        answer = test_answer

    print()
    print("[*] Round-%d: Write the assembly, which produces %s" % (round_num, answer))
    print("[*] Current whitelists: %s" % ", ".join(whitelists))
    print("[*] Current blacklists: %s" % ", ".join(blacklists))

    print("[*] Provide the assembly below:\n")

    lines = []
    while True:
        line = input()
        if line:
            lines.append(line)
        else:
            break

    asm = "\n".join(lines)
    your_answer = build_and_run(asm, whitelists, blacklists)

    print("[*] Your asm produced [%s]" % your_answer)

    if your_answer != answer:
        print("[-] Wrong")
        sys.exit(-1)

    print("[*] Alright. You passed round-%d" % round_num)
    return

def main(answer = None):
    global round_num
    global dn

    round_num = 0

    print("[*] The mighty ASMan wants you to write assembly.")
    dn = tempfile.mkdtemp(prefix="give-me-asm-")

    REPEAT = 20
    for _ in range(REPEAT):
        round([], ["syscall", "int", "mov", "inc", "dec"])

    for _ in range(REPEAT):
        round(["mov"], ["syscall", "int"])

    for _ in range(REPEAT):
        round(["inc", "shl"], ["syscall", "int"])

    print()
    print("[*] Very good. You passed all!")
    print(open("flag.txt").read())
    return

if __name__ == "__main__":
    if len(sys.argv) > 1:
        test_answer = str(sys.argv[1])
        print(f"[*] Test is on: {test_answer}")
    else:
        test_answer = None
    main()
