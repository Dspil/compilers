	.text
	.file	"pcl program"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$10, %edi
	movl	$11, %esi
	movl	$12, %edx
	callq	add
	movl	%eax, %edi
	callq	writeInteger
	movl	$10, %edi
	callq	writeChar
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function add
	.type	add,@function
add:                                    # @add
	.cfi_startproc
# %bb.0:                                # %add
	movl	%edi, %eax
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	movl	%edx, -12(%rsp)
	addl	%esi, %eax
	addl	%edx, %eax
	movl	%eax, -16(%rsp)
	retq
.Lfunc_end1:
	.size	add, .Lfunc_end1-add
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
