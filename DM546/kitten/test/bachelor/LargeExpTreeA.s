.globl main
_intPrint:
    .string "%d\n"
.data
    .align 4
_myspace:
    .space 8
_divbyzero_error:
    .ascii "Der opstod en fejl på kørselstidspunktet: Division med 0.\n"
.text
main:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    movl   %esp, _myspace
    pushl  $0
    addl   $-196, %esp
    pushl  %ecx
    pushl  %edx
    movl   $1, -20(%ebp)
    movl   -20(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $2, -28(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $3, -36(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -40(%ebp)
    movl   $4, -44(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -48(%ebp)
    movl   $5, -52(%ebp)
    movl   -52(%ebp), %ecx
    movl   %ecx, -56(%ebp)
    movl   $6, -60(%ebp)
    movl   -60(%ebp), %ecx
    movl   %ecx, -64(%ebp)
    movl   $7, -68(%ebp)
    movl   -68(%ebp), %ecx
    movl   %ecx, -72(%ebp)
    movl   $8, -76(%ebp)
    movl   -76(%ebp), %ecx
    movl   %ecx, -80(%ebp)
    movl   $9, -84(%ebp)
    movl   -84(%ebp), %ecx
    movl   %ecx, -88(%ebp)
    movl   $10, -92(%ebp)
    movl   -92(%ebp), %eax
    imul   -88(%ebp), %eax
    movl   %eax, -96(%ebp)
    movl   -96(%ebp), %ecx
    addl   %ecx, -80(%ebp)
    movl   -80(%ebp), %eax
    imul   -72(%ebp), %eax
    movl   %eax, -100(%ebp)
    movl   -100(%ebp), %ecx
    addl   %ecx, -64(%ebp)
    movl   -64(%ebp), %eax
    imul   -56(%ebp), %eax
    movl   %eax, -104(%ebp)
    movl   -104(%ebp), %ecx
    addl   %ecx, -48(%ebp)
    movl   -48(%ebp), %eax
    imul   -40(%ebp), %eax
    movl   %eax, -108(%ebp)
    movl   -108(%ebp), %ecx
    addl   %ecx, -32(%ebp)
    movl   -32(%ebp), %eax
    imul   -24(%ebp), %eax
    movl   %eax, -112(%ebp)
    movl   -112(%ebp), %ecx
    movl   %ecx, -116(%ebp)
    movl   $11, -120(%ebp)
    movl   -120(%ebp), %ecx
    movl   %ecx, -124(%ebp)
    movl   $12, -128(%ebp)
    movl   -128(%ebp), %eax
    imul   -124(%ebp), %eax
    movl   %eax, -132(%ebp)
    movl   -132(%ebp), %ecx
    movl   %ecx, -136(%ebp)
    movl   $13, -140(%ebp)
    movl   -140(%ebp), %ecx
    addl   %ecx, -136(%ebp)
    movl   -136(%ebp), %ecx
    movl   %ecx, -144(%ebp)
    movl   $14, -148(%ebp)
    movl   -148(%ebp), %eax
    imul   -144(%ebp), %eax
    movl   %eax, -152(%ebp)
    movl   -152(%ebp), %ecx
    movl   %ecx, -156(%ebp)
    movl   $15, -160(%ebp)
    movl   -160(%ebp), %ecx
    addl   %ecx, -156(%ebp)
    movl   -156(%ebp), %ecx
    movl   %ecx, -164(%ebp)
    movl   $16, -168(%ebp)
    movl   -168(%ebp), %eax
    imul   -164(%ebp), %eax
    movl   %eax, -172(%ebp)
    movl   -172(%ebp), %ecx
    movl   %ecx, -176(%ebp)
    movl   $17, -180(%ebp)
    movl   -180(%ebp), %ecx
    addl   %ecx, -176(%ebp)
    movl   -176(%ebp), %ecx
    movl   %ecx, -184(%ebp)
    movl   $18, -188(%ebp)
    movl   -188(%ebp), %eax
    imul   -184(%ebp), %eax
    movl   %eax, -192(%ebp)
    movl   -192(%ebp), %ecx
    movl   %ecx, -196(%ebp)
    movl   $19, -200(%ebp)
    movl   -200(%ebp), %ecx
    addl   %ecx, -196(%ebp)
    movl   -196(%ebp), %ecx
    movl   %ecx, -204(%ebp)
    movl   $20, -208(%ebp)
    movl   -208(%ebp), %eax
    imul   -204(%ebp), %eax
    movl   %eax, -212(%ebp)
    movl   -212(%ebp), %ecx
    addl   %ecx, -116(%ebp)
    pushl  -116(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $196, %esp
    addl   $4, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    movl   %ebp, %edx
    movl   %edx, %esp
    popl   %ebp
    movl   $0, %eax
    ret
divbyzero:
    pushl  $_divbyzero_error
    call   printf
    movl   _myspace, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    popl   %ebp
    movl   $2, %eax
    ret
    .ident "Kitten"
