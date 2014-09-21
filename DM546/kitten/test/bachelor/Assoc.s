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
    addl   $-128, %esp
    pushl  %ecx
    pushl  %edx
    movl   $10, -20(%ebp)
    movl   -20(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $2, -28(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $2, -36(%ebp)
    movl   -36(%ebp), %eax
    imul   -32(%ebp), %eax
    movl   %eax, -40(%ebp)
    movl   -40(%ebp), %ecx
    subl   %ecx, -24(%ebp)
    pushl  -24(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    movl   $24, -44(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -48(%ebp)
    movl   $4, -52(%ebp)
    cmp    $0, -52(%ebp)
    je     divbyzero
    movl   -48(%ebp), %eax
    cltd
    movl   -52(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -56(%ebp)
    movl   -56(%ebp), %ecx
    movl   %ecx, -60(%ebp)
    movl   $2, -64(%ebp)
    movl   -64(%ebp), %eax
    imul   -60(%ebp), %eax
    movl   %eax, -68(%ebp)
    pushl  -68(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    movl   $100, -72(%ebp)
    movl   -72(%ebp), %ecx
    movl   %ecx, -76(%ebp)
    movl   $2, -80(%ebp)
    cmp    $0, -80(%ebp)
    je     divbyzero
    movl   -76(%ebp), %eax
    cltd
    movl   -80(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -84(%ebp)
    movl   -84(%ebp), %ecx
    movl   %ecx, -88(%ebp)
    movl   $5, -92(%ebp)
    cmp    $0, -92(%ebp)
    je     divbyzero
    movl   -88(%ebp), %eax
    cltd
    movl   -92(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -96(%ebp)
    movl   -96(%ebp), %ecx
    movl   %ecx, -100(%ebp)
    movl   $10, -104(%ebp)
    cmp    $0, -104(%ebp)
    je     divbyzero
    movl   -100(%ebp), %eax
    cltd
    movl   -104(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -108(%ebp)
    pushl  -108(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    movl   $4, -112(%ebp)
    movl   -112(%ebp), %ecx
    movl   %ecx, -116(%ebp)
    movl   $5, -120(%ebp)
    movl   -120(%ebp), %eax
    imul   -116(%ebp), %eax
    movl   %eax, -124(%ebp)
    movl   -124(%ebp), %ecx
    movl   %ecx, -128(%ebp)
    movl   $3, -132(%ebp)
    movl   -132(%ebp), %ecx
    movl   %ecx, -136(%ebp)
    movl   $6, -140(%ebp)
    movl   -140(%ebp), %eax
    imul   -136(%ebp), %eax
    movl   %eax, -144(%ebp)
    movl   -144(%ebp), %ecx
    subl   %ecx, -128(%ebp)
    pushl  -128(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $128, %esp
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
