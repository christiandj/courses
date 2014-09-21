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
max:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-8, %esp
    movl   12(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   -20(%ebp), %ecx
    cmp    16(%ebp), %ecx
    jle    false0
    movl   $1, -24(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -24(%ebp)
end_comparison0:
    cmp    $1, -24(%ebp)
    jne    end_if0
    movl   12(%ebp), %eax
    jmp    end_max
end_if0:
    movl   16(%ebp), %eax
    jmp    end_max
end_max:
    addl   $8, %esp
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
    addl   $-8, %esp
    pushl  %ecx
    pushl  %edx
    movl   $20, -20(%ebp)
    pushl  -20(%ebp)
    movl   $10, -24(%ebp)
    pushl  -24(%ebp)
    pushl  %ebp
    call   max
    popl   %ebp
    addl   $8, %esp
    pushl  %eax
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $8, %esp
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
