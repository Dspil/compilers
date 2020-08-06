	.text
	.file	"pcl program"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$.L__unnamed_1, %edi
	callq	writeString
	callq	readInteger
	movl	%eax, %ebx
	movl	$.L__unnamed_2, %edi
	callq	writeString
	movl	$.L__unnamed_3, %edi
	movl	$.L__unnamed_4, %esi
	movl	$.L__unnamed_5, %edx
	movl	%ebx, %ecx
	callq	hanoi
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function hanoi
	.type	hanoi,@function
hanoi:                                  # @hanoi
	.cfi_startproc
# %bb.0:                                # %hanoi
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, 24(%rsp)
	movq	%rsi, 16(%rsp)
	movq	%rdx, 32(%rsp)
	movl	%ecx, 12(%rsp)
	testl	%ecx, %ecx
	jle	.LBB1_2
# %bb.1:                                # %then
	movq	24(%rsp), %rdi
	movq	32(%rsp), %rsi
	movq	16(%rsp), %rdx
	movl	12(%rsp), %ecx
	decl	%ecx
	callq	hanoi
	movq	24(%rsp), %rdi
	movq	16(%rsp), %rsi
	callq	move
	movq	32(%rsp), %rdi
	movq	16(%rsp), %rsi
	movq	24(%rsp), %rdx
	movl	12(%rsp), %ecx
	decl	%ecx
	callq	hanoi
.LBB1_2:                                # %merge
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	hanoi, .Lfunc_end1-hanoi
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function move
	.type	move,@function
move:                                   # @move
	.cfi_startproc
# %bb.0:                                # %move
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, 16(%rsp)
	movq	%rsi, 8(%rsp)
	movl	$.L__unnamed_6, %edi
	callq	writeString
	movq	16(%rsp), %rdi
	callq	writeString
	movl	$.L__unnamed_7, %edi
	callq	writeString
	movq	8(%rsp), %rdi
	callq	writeString
	movl	$.L__unnamed_8, %edi
	callq	writeString
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	move, .Lfunc_end2-move
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_6,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_6:
	.asciz	"Move from "
	.size	.L__unnamed_6, 11

	.type	.L__unnamed_7,@object   # @1
.L__unnamed_7:
	.asciz	" to "
	.size	.L__unnamed_7, 5

	.type	.L__unnamed_8,@object   # @2
.L__unnamed_8:
	.asciz	".\n"
	.size	.L__unnamed_8, 3

	.type	.L__unnamed_1,@object   # @3
.L__unnamed_1:
	.asciz	"Please, give the number of rings : "
	.size	.L__unnamed_1, 36

	.type	.L__unnamed_2,@object   # @4
.L__unnamed_2:
	.asciz	"\nHere is the solution :\n\n"
	.size	.L__unnamed_2, 26

	.type	.L__unnamed_3,@object   # @5
.L__unnamed_3:
	.asciz	"left"
	.size	.L__unnamed_3, 5

	.type	.L__unnamed_4,@object   # @6
.L__unnamed_4:
	.asciz	"right"
	.size	.L__unnamed_4, 6

	.type	.L__unnamed_5,@object   # @7
.L__unnamed_5:
	.asciz	"middle"
	.size	.L__unnamed_5, 7

	.section	".note.GNU-stack","",@progbits
