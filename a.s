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
	subq	$80, %rsp
	.cfi_def_cfa_offset 96
	.cfi_offset %rbx, -16
	movl	$0, 8(%rsp)
	movl	$65, 12(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	jne	.LBB0_2
	.p2align	4, 0x90
.LBB0_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	imull	$137, 12(%rsp), %eax
	movl	8(%rsp), %ecx
	leal	221(%rax,%rcx), %eax
	cltq
	imulq	$680390859, %rax, %rdx  # imm = 0x288DF0CB
	movq	%rdx, %rsi
	shrq	$63, %rsi
	sarq	$36, %rdx
	addl	%esi, %edx
	imull	$101, %edx, %edx
	subl	%edx, %eax
	movl	%eax, 12(%rsp)
	movslq	8(%rsp), %rdx
	movl	%eax, 16(%rsp,%rdx,4)
	incl	%ecx
	movl	%ecx, 8(%rsp)
	cmpl	$16, %ecx
	jl	.LBB0_1
.LBB0_2:                                # %after
	leaq	16(%rsp), %rbx
	movl	$.L__unnamed_1, %edi
	movq	%rbx, %rsi
	movl	$16, %edx
	callq	PrintArray
	movq	%rbx, %rdi
	movl	$16, %esi
	callq	BubbleSort
	movl	$.L__unnamed_2, %edi
	movq	%rbx, %rsi
	movl	$16, %edx
	callq	PrintArray
	xorl	%eax, %eax
	addq	$80, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function BubbleSort
	.type	BubbleSort,@function
BubbleSort:                             # @BubbleSort
	.cfi_startproc
# %bb.0:                                # %BubbleSort
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, 16(%rsp)
	movl	%esi, 12(%rsp)
	movb	$1, 7(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	je	.LBB1_1
.LBB1_6:                                # %after4
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
	.p2align	4, 0x90
.LBB1_5:                                # %after
                                        #   in Loop: Header=BB1_1 Depth=1
	.cfi_def_cfa_offset 32
	cmpb	$0, 7(%rsp)
	je	.LBB1_6
.LBB1_1:                                # %loop
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_2 Depth 2
	movl	$0, 8(%rsp)
	movb	$0, 7(%rsp)
	movl	12(%rsp), %eax
	decl	%eax
	testl	%eax, %eax
	jg	.LBB1_2
	jmp	.LBB1_5
	.p2align	4, 0x90
.LBB1_4:                                # %merge
                                        #   in Loop: Header=BB1_2 Depth=2
	movl	8(%rsp), %eax
	incl	%eax
	movl	%eax, 8(%rsp)
	movl	12(%rsp), %ecx
	decl	%ecx
	cmpl	%ecx, %eax
	jge	.LBB1_5
.LBB1_2:                                # %loop3
                                        #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	16(%rsp), %rax
	movslq	8(%rsp), %rcx
	movl	(%rax,%rcx,4), %edx
	incl	%ecx
	movslq	%ecx, %rcx
	cmpl	(%rax,%rcx,4), %edx
	jle	.LBB1_4
# %bb.3:                                # %then
                                        #   in Loop: Header=BB1_2 Depth=2
	movq	16(%rsp), %rax
	movslq	8(%rsp), %rcx
	leaq	(%rax,%rcx,4), %rdi
	incl	%ecx
	movslq	%ecx, %rcx
	leaq	(%rax,%rcx,4), %rsi
	callq	swap
	movb	$1, 7(%rsp)
	jmp	.LBB1_4
.Lfunc_end1:
	.size	BubbleSort, .Lfunc_end1-BubbleSort
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function swap
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:                                # %swap
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movl	(%rdi), %eax
	movl	%eax, -20(%rsp)
	movl	(%rsi), %eax
	movl	%eax, (%rdi)
	movl	-20(%rsp), %eax
	movq	-16(%rsp), %rcx
	movl	%eax, (%rcx)
	retq
.Lfunc_end2:
	.size	swap, .Lfunc_end2-swap
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function PrintArray
	.type	PrintArray,@function
PrintArray:                             # @PrintArray
	.cfi_startproc
# %bb.0:                                # %PrintArray
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, 16(%rsp)
	movq	%rsi, 8(%rsp)
	movl	%edx, 4(%rsp)
	callq	writeString
	movl	$0, (%rsp)
	cmpl	$0, 4(%rsp)
	jg	.LBB3_1
.LBB3_4:                                # %after
	movl	$.L__unnamed_3, %edi
	callq	writeString
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
	.p2align	4, 0x90
.LBB3_3:                                # %merge
                                        #   in Loop: Header=BB3_1 Depth=1
	.cfi_def_cfa_offset 32
	movq	8(%rsp), %rax
	movslq	(%rsp), %rcx
	movl	(%rax,%rcx,4), %edi
	callq	writeInteger
	movl	(%rsp), %eax
	incl	%eax
	movl	%eax, (%rsp)
	cmpl	4(%rsp), %eax
	jge	.LBB3_4
.LBB3_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$0, (%rsp)
	jle	.LBB3_3
# %bb.2:                                # %then
                                        #   in Loop: Header=BB3_1 Depth=1
	movl	$.L__unnamed_4, %edi
	callq	writeString
	jmp	.LBB3_3
.Lfunc_end3:
	.size	PrintArray, .Lfunc_end3-PrintArray
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_4,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_4:
	.asciz	", "
	.size	.L__unnamed_4, 3

	.type	.L__unnamed_3,@object   # @1
.L__unnamed_3:
	.asciz	"\n"
	.size	.L__unnamed_3, 2

	.type	.L__unnamed_1,@object   # @2
.L__unnamed_1:
	.asciz	"Initial array: "
	.size	.L__unnamed_1, 16

	.type	.L__unnamed_2,@object   # @3
.L__unnamed_2:
	.asciz	"Sorted array: "
	.size	.L__unnamed_2, 15

	.section	".note.GNU-stack","",@progbits
