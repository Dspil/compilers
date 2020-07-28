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
	subq	$112, %rsp
	.cfi_def_cfa_offset 128
	.cfi_offset %rbx, -16
	movl	$0, 4(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	jne	.LBB0_5
# %bb.1:                                # %loop.preheader
	xorl	%eax, %eax
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_4:                                # %after
                                        #   in Loop: Header=BB0_2 Depth=1
	movl	4(%rsp), %ecx
	incl	%ecx
	movl	%ecx, 4(%rsp)
	cmpl	$5, %ecx
	jge	.LBB0_5
.LBB0_2:                                # %loop
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movl	$0, (%rsp)
	testb	%al, %al
	jne	.LBB0_4
	.p2align	4, 0x90
.LBB0_3:                                # %loop3
                                        #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movslq	4(%rsp), %rcx
	leal	(%rcx,%rcx,4), %edx
	movslq	(%rsp), %rsi
	addl	%esi, %edx
	leaq	(%rcx,%rcx,4), %rcx
	leaq	8(%rsp,%rcx,4), %rcx
	movl	%edx, (%rcx,%rsi,4)
	movl	(%rsp), %ecx
	incl	%ecx
	movl	%ecx, (%rsp)
	cmpl	$5, %ecx
	jl	.LBB0_3
	jmp	.LBB0_4
.LBB0_5:                                # %after12
	movl	$0, 4(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	jne	.LBB0_13
# %bb.6:                                # %loop14.preheader
	xorl	%ebx, %ebx
	jmp	.LBB0_7
	.p2align	4, 0x90
.LBB0_12:                               # %after22
                                        #   in Loop: Header=BB0_7 Depth=1
	movl	4(%rsp), %eax
	incl	%eax
	movl	%eax, 4(%rsp)
	cmpl	$5, %eax
	jge	.LBB0_13
.LBB0_7:                                # %loop14
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_8 Depth 2
	movl	$0, (%rsp)
	testb	%bl, %bl
	je	.LBB0_8
	jmp	.LBB0_12
	.p2align	4, 0x90
.LBB0_10:                               # %else
                                        #   in Loop: Header=BB0_8 Depth=2
	movl	$10, %edi
.LBB0_11:                               # %merge
                                        #   in Loop: Header=BB0_8 Depth=2
	callq	writeChar
	movl	(%rsp), %eax
	incl	%eax
	movl	%eax, (%rsp)
	cmpl	$5, %eax
	jge	.LBB0_12
.LBB0_8:                                # %loop16
                                        #   Parent Loop BB0_7 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movslq	4(%rsp), %rax
	leaq	(%rax,%rax,4), %rax
	leaq	8(%rsp,%rax,4), %rax
	movslq	(%rsp), %rcx
	movl	(%rax,%rcx,4), %edi
	callq	writeInteger
	cmpl	$3, (%rsp)
	jg	.LBB0_10
# %bb.9:                                # %then
                                        #   in Loop: Header=BB0_8 Depth=2
	movl	$44, %edi
	callq	writeChar
	movl	$32, %edi
	jmp	.LBB0_11
.LBB0_13:                               # %after25
	xorl	%eax, %eax
	addq	$112, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
