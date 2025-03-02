	.file	"process_pool.c"
	.text
	.section	.rodata
.LC0:
	.string	"calloc[send fd error]"
.LC1:
	.string	"sendmsg"
.LC2:
	.string	"sendFd %d bytes.\n"
	.text
	.globl	sendFd
	.type	sendFd, @function
sendFd:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movl	%edi, -164(%rbp)
	movl	%esi, -168(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -12(%rbp)
	leaq	-80(%rbp), %rax
	movl	$56, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	leaq	-12(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	$4, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	$1, -56(%rbp)
	movq	$20, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -128(%rbp)
	cmpq	$0, -128(%rbp)
	jne	.L2
	movl	$0, -152(%rbp)
	movl	$-1, -148(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdx
	movl	-148(%rbp), %ecx
	movl	-152(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
	movl	$-1, %eax
	jmp	.L5
.L2:
	movq	-128(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-128(%rbp), %rax
	movl	$1, 8(%rax)
	movq	-128(%rbp), %rax
	movl	$1, 12(%rax)
	movq	-128(%rbp), %rax
	addq	$16, %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movl	-168(%rbp), %edx
	movl	%edx, (%rax)
	movq	-128(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -40(%rbp)
	leaq	-80(%rbp), %rcx
	movl	-164(%rbp), %eax
	movl	$0, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	sendmsg@PLT
	movl	%eax, -156(%rbp)
	cmpl	$-1, -156(%rbp)
	jne	.L4
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$0, -144(%rbp)
	movl	%eax, -140(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rdx
	movl	-140(%rbp), %ecx
	movl	-144(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L4:
	movl	-156(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	-156(%rbp), %eax
.L5:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L6
	call	__stack_chk_fail@PLT
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	sendFd, .-sendFd
	.globl	recvFd
	.type	recvFd, @function
recvFd:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movl	%edi, -148(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -12(%rbp)
	leaq	-80(%rbp), %rax
	movl	$56, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	leaq	-12(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	$4, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	$1, -56(%rbp)
	movq	$20, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -112(%rbp)
	cmpq	$0, -112(%rbp)
	jne	.L8
	movl	$0, -128(%rbp)
	movl	$-1, -124(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rdx
	movl	-124(%rbp), %ecx
	movl	-128(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
	movl	$-1, %eax
	jmp	.L10
.L8:
	movq	-112(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-112(%rbp), %rax
	movl	$1, 8(%rax)
	movq	-112(%rbp), %rax
	movl	$1, 12(%rax)
	movq	-112(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -40(%rbp)
	leaq	-80(%rbp), %rcx
	movl	-148(%rbp), %eax
	movl	$0, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	recvmsg@PLT
	movl	%eax, -132(%rbp)
	movq	-112(%rbp), %rax
	addq	$16, %rax
	movl	(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, (%rax)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	-132(%rbp), %eax
.L10:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	recvFd, .-recvFd
	.section	.rodata
.LC3:
	.string	"child start to handle task..."
	.align 8
.LC4:
	.string	"\346\255\243\345\234\250\347\255\211\345\276\205\346\226\260\347\232\204\346\217\217\350\277\260\347\254\246\345\210\260\346\235\245"
	.align 8
.LC5:
	.string	"\345\267\262\346\216\245\346\224\266\345\210\260\346\226\260\347\232\204\344\273\273\345\212\241\357\274\214peerfd=%d\n"
.LC6:
	.string	"Hello, client.\n"
	.string	""
	.text
	.globl	handleTask
	.type	handleTask, @function
handleTask:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L13:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-20(%rbp), %rdx
	movl	-36(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	recvFd
	movl	%eax, -12(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %eax
	movl	$16, %edx
	leaq	.LC6(%rip), %rcx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$1, -16(%rbp)
	leaq	-16(%rbp), %rcx
	movl	-36(%rbp), %eax
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	jmp	.L13
	.cfi_endproc
.LFE10:
	.size	handleTask, .-handleTask
	.section	.rodata
.LC7:
	.string	"socket"
.LC8:
	.string	"%d"
.LC9:
	.string	"%d\n"
.LC10:
	.string	"setsockopt"
.LC11:
	.string	"bind"
.LC12:
	.string	"listen"
	.text
	.globl	tcp_init
	.type	tcp_init, @function
tcp_init:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movq	%rdi, -120(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -100(%rbp)
	movl	$0, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket@PLT
	movl	%eax, -100(%rbp)
	cmpl	$-1, -100(%rbp)
	jne	.L16
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$1, -96(%rbp)
	movl	%eax, -92(%rbp)
	leaq	.LC7(%rip), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdx
	movl	-92(%rbp), %ecx
	movl	-96(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L16:
	leaq	-32(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movw	$2, -32(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	inet_addr@PLT
	movl	%eax, -28(%rbp)
	movl	$0, -108(%rbp)
	leaq	-108(%rbp), %rdx
	movq	-128(%rbp), %rax
	leaq	.LC8(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	movl	-108(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-108(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	htons@PLT
	movw	%ax, -30(%rbp)
	movl	$1, -104(%rbp)
	leaq	-104(%rbp), %rdx
	movl	-100(%rbp), %eax
	movl	$4, %r8d
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	setsockopt@PLT
	testl	%eax, %eax
	je	.L17
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$0, -88(%rbp)
	movl	%eax, -84(%rbp)
	leaq	.LC10(%rip), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rdx
	movl	-84(%rbp), %ecx
	movl	-88(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L17:
	leaq	-32(%rbp), %rcx
	movl	-100(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	bind@PLT
	testl	%eax, %eax
	je	.L18
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$1, -80(%rbp)
	movl	%eax, -76(%rbp)
	leaq	.LC11(%rip), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rdx
	movl	-76(%rbp), %ecx
	movl	-80(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L18:
	movl	-100(%rbp), %eax
	movl	$64, %esi
	movl	%eax, %edi
	call	listen@PLT
	testl	%eax, %eax
	je	.L19
	movl	-100(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$1, -72(%rbp)
	movl	%eax, -68(%rbp)
	leaq	.LC12(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rdx
	movl	-68(%rbp), %ecx
	movl	-72(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L19:
	movl	-100(%rbp), %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L21
	call	__stack_chk_fail@PLT
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	tcp_init, .-tcp_init
	.section	.rodata
.LC13:
	.string	"socketpair"
.LC14:
	.string	"fork"
	.text
	.globl	make_child_process
	.type	make_child_process, @function
make_child_process:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movl	%esi, -76(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -56(%rbp)
	jmp	.L23
.L28:
	leaq	-16(%rbp), %rax
	movq	%rax, %rcx
	movl	$0, %edx
	movl	$1, %esi
	movl	$1, %edi
	call	socketpair@PLT
	testl	%eax, %eax
	je	.L24
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$-1, -48(%rbp)
	movl	%eax, -44(%rbp)
	leaq	.LC13(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rdx
	movl	-44(%rbp), %ecx
	movl	-48(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L24:
	call	fork@PLT
	movl	%eax, -52(%rbp)
	cmpl	$-1, -52(%rbp)
	jne	.L25
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$-1, -40(%rbp)
	movl	%eax, -36(%rbp)
	leaq	.LC14(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movl	-36(%rbp), %ecx
	movl	-40(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	jmp	.L26
.L25:
	cmpl	$0, -52(%rbp)
	jne	.L27
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	handleTask
	movl	$0, %edi
	call	exit@PLT
.L27:
	movl	-56(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rax, %rdx
	movl	-52(%rbp), %eax
	movl	%eax, (%rdx)
	movl	-56(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, 4(%rdx)
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-56(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 8(%rax)
.L26:
	addl	$1, -56(%rbp)
.L23:
	movl	-56(%rbp), %eax
	cmpl	-76(%rbp), %eax
	jl	.L28
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	make_child_process, .-make_child_process
	.section	.rodata
.LC15:
	.string	"epoll_ctl"
	.text
	.globl	epoll_add_fd
	.type	epoll_add_fd, @function
epoll_add_fd:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movq	%rdx, -48(%rbp)
	movq	-48(%rbp), %rcx
	movl	-40(%rbp), %edx
	movl	-36(%rbp), %eax
	movl	$1, %esi
	movl	%eax, %edi
	call	epoll_ctl@PLT
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	je	.L32
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$0, -16(%rbp)
	movl	%eax, -12(%rbp)
	leaq	.LC15(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movl	-12(%rbp), %ecx
	movl	-16(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L32:
	movl	-20(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	epoll_add_fd, .-epoll_add_fd
	.section	.rodata
.LC16:
	.string	"Usage: %s ip port processNum"
.LC17:
	.string	"make_child_process"
.LC18:
	.string	"epoll_add_fd"
.LC19:
	.string	"epoll_wait"
	.align 8
.LC20:
	.string	"child %d finishs work, and changes state to FREE\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	-16384(%rsp), %r11
.LPSRL0:
	subq	$4096, %rsp
	orq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LPSRL0
	subq	$192, %rsp
	movl	%edi, -16564(%rbp)
	movq	%rsi, -16576(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$4, -16564(%rbp)
	je	.L35
	movq	-16576(%rbp), %rax
	movq	(%rax), %rcx
	movl	$1, -16504(%rbp)
	movl	$0, -16500(%rbp)
	leaq	.LC16(%rip), %rax
	movq	%rax, -16464(%rbp)
	movq	-16464(%rbp), %rdx
	movl	-16500(%rbp), %esi
	movl	-16504(%rbp), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L35:
	movl	$0, -16552(%rbp)
	movq	-16576(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rax
	leaq	-16552(%rbp), %rdx
	leaq	.LC8(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	movl	-16552(%rbp), %eax
	cltq
	movl	$12, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, -16472(%rbp)
	movl	-16552(%rbp), %edx
	movq	-16472(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	make_child_process
	testl	%eax, %eax
	je	.L36
	movl	$1, -16496(%rbp)
	movl	$0, -16492(%rbp)
	leaq	.LC17(%rip), %rax
	movq	%rax, -16456(%rbp)
	movq	-16456(%rbp), %rdx
	movl	-16492(%rbp), %ecx
	movl	-16496(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L36:
	movq	-16576(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rdx
	movq	-16576(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tcp_init
	movl	%eax, -16524(%rbp)
	movl	$0, %edi
	call	epoll_create1@PLT
	movl	%eax, -16520(%rbp)
	movl	-16524(%rbp), %eax
	movl	%eax, -16424(%rbp)
	movl	$1, -16428(%rbp)
	leaq	-16428(%rbp), %rdx
	movl	-16524(%rbp), %ecx
	movl	-16520(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	epoll_add_fd
	testl	%eax, %eax
	je	.L37
	movl	-16524(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$1, -16488(%rbp)
	movl	%eax, -16484(%rbp)
	leaq	.LC18(%rip), %rax
	movq	%rax, -16448(%rbp)
	movq	-16448(%rbp), %rdx
	movl	-16484(%rbp), %ecx
	movl	-16488(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L37:
	movl	$0, -16540(%rbp)
	jmp	.L38
.L39:
	movl	-16540(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %eax
	movl	%eax, -16424(%rbp)
	movl	-16540(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %ecx
	leaq	-16428(%rbp), %rdx
	movl	-16520(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	epoll_add_fd
	addl	$1, -16540(%rbp)
.L38:
	movl	-16552(%rbp), %eax
	cmpl	%eax, -16540(%rbp)
	jl	.L39
	movq	$0, -4112(%rbp)
	movq	$0, -4104(%rbp)
	leaq	-4096(%rbp), %rdx
	movl	$0, %eax
	movl	$510, %ecx
	movq	%rdx, %rdi
	rep stosq
.L55:
	movl	$0, -16516(%rbp)
	leaq	-16400(%rbp), %rsi
	movl	-16520(%rbp), %eax
	movl	$-1, %ecx
	movl	$1024, %edx
	movl	%eax, %edi
	call	epoll_wait@PLT
	movl	%eax, -16516(%rbp)
	cmpl	$-1, -16516(%rbp)
	jne	.L40
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	$0, -16480(%rbp)
	movl	%eax, -16476(%rbp)
	leaq	.LC19(%rip), %rax
	movq	%rax, -16440(%rbp)
	movq	-16440(%rbp), %rdx
	movl	-16476(%rbp), %ecx
	movl	-16480(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	error@PLT
	nop
.L40:
	movl	$0, -16536(%rbp)
	jmp	.L41
.L54:
	movl	-16536(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$16396, %rax
	movl	(%rax), %eax
	movl	%eax, -16512(%rbp)
	movl	$0, -16508(%rbp)
	movl	$16, -16548(%rbp)
	movl	-16512(%rbp), %eax
	cmpl	-16524(%rbp), %eax
	jne	.L42
	leaq	-16548(%rbp), %rdx
	leaq	-16416(%rbp), %rcx
	movl	-16524(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	accept@PLT
	movl	%eax, -16508(%rbp)
	cmpl	$-1, -16508(%rbp)
	je	.L57
	movl	$0, -16532(%rbp)
	jmp	.L45
.L48:
	movl	-16532(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L46
	movl	-16532(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	$1, 8(%rax)
	movl	-16532(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %eax
	movl	-16508(%rbp), %edx
	movl	%edx, %esi
	movl	%eax, %edi
	call	sendFd
	jmp	.L44
.L46:
	addl	$1, -16532(%rbp)
.L45:
	movl	-16552(%rbp), %eax
	cmpl	%eax, -16532(%rbp)
	jl	.L48
	jmp	.L44
.L42:
	leaq	-16544(%rbp), %rcx
	movl	-16512(%rbp), %eax
	movl	$4, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movl	$0, -16528(%rbp)
	jmp	.L50
.L53:
	movl	-16528(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %eax
	cmpl	%eax, -16512(%rbp)
	jne	.L51
	movl	-16528(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16472(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 8(%rax)
	movq	-16472(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L44
.L51:
	addl	$1, -16528(%rbp)
.L50:
	movl	-16552(%rbp), %eax
	cmpl	%eax, -16528(%rbp)
	jl	.L53
	jmp	.L44
.L57:
	nop
.L44:
	addl	$1, -16536(%rbp)
.L41:
	movl	-16536(%rbp), %eax
	cmpl	-16516(%rbp), %eax
	jl	.L54
	jmp	.L55
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
