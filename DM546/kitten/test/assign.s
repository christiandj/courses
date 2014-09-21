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
    addl   $-36, %esp
    movl   $1, -32(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $2, -40(%ebp)
    movl   -40(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $3, -48(%ebp)
    movl   -48(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   -52(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    pushl  %ecx
    pushl  %edx
    pushl  -20(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    pushl  -24(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    pushl  -28(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $36, %esp
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
