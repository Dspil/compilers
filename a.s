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
	movl	$4, %edi
	callq	test_write
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
	.p2align	4, 0x90         # -- Begin function test_write
	.type	test_write,@function
test_write:                             # @test_write
	.cfi_startproc
# %bb.0:                                # %test_write
	pushq	%rax
	.cfi_def_cfa_offset 16
	incl	%edi
	movl	%edi, 4(%rsp)
	callq	test_write2
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	test_write, .Lfunc_end1-test_write
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function test_write2
	.type	test_write2,@function
test_write2:                            # @test_write2
	.cfi_startproc
# %bb.0:                                # %test_write2
	pushq	%rax
	.cfi_def_cfa_offset 16
	incl	%edi
	movl	%edi, 4(%rsp)
	callq	writeInteger
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	test_write2, .Lfunc_end2-test_write2
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
