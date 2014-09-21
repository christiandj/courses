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
echo:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-20, %esp
    movl   16(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $0, -24(%ebp)
    movl   -20(%ebp), %ecx
    cmp    -24(%ebp), %ecx
    jne    false0
    movl   $1, -28(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -28(%ebp)
end_comparison0:
    cmp    $1, -28(%ebp)
    jne    end_if0
    movl   12(%ebp), %eax
    jmp    end_echo
end_if0:
    movl   16(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $1, -36(%ebp)
    movl   -36(%ebp), %ecx
    subl   %ecx, -32(%ebp)
    pushl  -32(%ebp)
    pushl  12(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   echo
    popl   %edx
    addl   $8, %esp
    movl   %eax, %eax
    jmp    end_echo
end_echo:
    addl   $20, %esp
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
    addl   $-28, %esp
    movl   $3, -24(%ebp)
    pushl  -24(%ebp)
    movl   $0, -28(%ebp)
    pushl  -28(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -32(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    pushl  %ecx
    pushl  %edx
    movl   $3, -36(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -40(%ebp)
    cmp    $0, -20(%ebp)
    je     divbyzero
    movl   -40(%ebp), %eax
    cltd
    movl   -20(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -44(%ebp)
    pushl  -44(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $28, %esp
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
