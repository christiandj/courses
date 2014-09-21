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
three:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-8, %esp
    movl   12(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   16(%ebp), %ecx
    addl   %ecx, -20(%ebp)
    movl   -20(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   20(%ebp), %ecx
    addl   %ecx, -24(%ebp)
    movl   -24(%ebp), %eax
    jmp    end_three
end_three:
    addl   $8, %esp
    addl   $4, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    movl   %ebp, %edx
    movl   %edx, %esp
    popl   %ebp
    ret
two:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-4, %esp
    movl   12(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   16(%ebp), %ecx
    addl   %ecx, -20(%ebp)
    movl   -20(%ebp), %eax
    jmp    end_two
end_two:
    addl   $4, %esp
    addl   $4, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    movl   %ebp, %edx
    movl   %edx, %esp
    popl   %ebp
    ret
one:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    movl   12(%ebp), %eax
    jmp    end_one
end_one:
    addl   $4, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    movl   %ebp, %edx
    movl   %edx, %esp
    popl   %ebp
    ret
none:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-4, %esp
    movl   $0, -20(%ebp)
    movl   -20(%ebp), %eax
    jmp    end_none
end_none:
    addl   $4, %esp
    addl   $4, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    movl   %ebp, %edx
    movl   %edx, %esp
    popl   %ebp
    ret
main:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    movl   %esp, _myspace
    pushl  $0
    addl   $-24, %esp
    pushl  %ecx
    pushl  %edx
    pushl  %ebp
    call   none
    popl   %ebp
    pushl  %eax
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    movl   $1, -20(%ebp)
    pushl  -20(%ebp)
    pushl  %ebp
    call   one
    popl   %ebp
    addl   $4, %esp
    pushl  %eax
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    movl   $2, -24(%ebp)
    pushl  -24(%ebp)
    movl   $1, -28(%ebp)
    pushl  -28(%ebp)
    pushl  %ebp
    call   two
    popl   %ebp
    addl   $8, %esp
    pushl  %eax
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    pushl  %ecx
    pushl  %edx
    movl   $3, -32(%ebp)
    pushl  -32(%ebp)
    movl   $2, -36(%ebp)
    pushl  -36(%ebp)
    movl   $1, -40(%ebp)
    pushl  -40(%ebp)
    pushl  %ebp
    call   three
    popl   %ebp
    addl   $12, %esp
    pushl  %eax
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $24, %esp
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
