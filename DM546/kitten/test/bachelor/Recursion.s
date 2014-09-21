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
rec:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-36, %esp
    pushl  %ecx
    pushl  %edx
    pushl  12(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    movl   12(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $2, -24(%ebp)
    movl   -20(%ebp), %ecx
    cmp    -24(%ebp), %ecx
    jl     false0
    movl   $1, -28(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -28(%ebp)
end_comparison0:
    cmp    $1, -28(%ebp)
    jne    end_if0
    movl   12(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $1, -36(%ebp)
    movl   -36(%ebp), %ecx
    subl   %ecx, -32(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -40(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   $1, -48(%ebp)
    movl   -48(%ebp), %ecx
    subl   %ecx, -44(%ebp)
    pushl  -44(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   rec
    popl   %edx
    addl   $4, %esp
    addl   %eax, -40(%ebp)
    movl   -40(%ebp), %eax
    jmp    end_rec
end_if0:
    movl   $0, -52(%ebp)
    movl   -52(%ebp), %eax
    jmp    end_rec
end_rec:
    addl   $36, %esp
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
    addl   $-4, %esp
    pushl  %ecx
    pushl  %edx
    movl   $10, -20(%ebp)
    pushl  -20(%ebp)
    pushl  %ebp
    call   rec
    popl   %ebp
    addl   $4, %esp
    pushl  %eax
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $4, %esp
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
