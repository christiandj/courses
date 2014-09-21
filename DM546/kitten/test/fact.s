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
factorial:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-52, %esp
    movl   $1, -24(%ebp)
    movl   -24(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $1, -36(%ebp)
    movl   -32(%ebp), %ecx
    cmp    -36(%ebp), %ecx
    jle    false0
    movl   $1, -40(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -40(%ebp)
end_comparison0:
    cmp    $1, -40(%ebp)
    jne    end_if0
    movl   12(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -48(%ebp)
    movl   $1, -52(%ebp)
    movl   -52(%ebp), %ecx
    subl   %ecx, -48(%ebp)
    pushl  -48(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   factorial
    popl   %edx
    addl   $4, %esp
    imul   -44(%ebp), %eax
    movl   %eax, -56(%ebp)
    movl   -56(%ebp), %ecx
    movl   %ecx, -60(%ebp)
    movl   -60(%ebp), %ecx
    movl   %ecx, -20(%ebp)
end_if0:
    movl   8(%ebp),%edx
    movl   -20(%edx), %ecx
    movl   %ecx, -64(%ebp)
    movl   -20(%ebp), %ecx
    addl   %ecx, -64(%ebp)
    movl   -64(%ebp), %ecx
    movl   %ecx, -68(%ebp)
    movl   8(%ebp),%edx
    movl   -68(%ebp), %ecx
    movl   %ecx, -20(%edx)
    movl   -20(%ebp), %eax
    jmp    end_factorial
end_factorial:
    addl   $52, %esp
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
    addl   $-16, %esp
    movl   $0, -24(%ebp)
    movl   -24(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    pushl  %ecx
    pushl  %edx
    movl   $5, -32(%ebp)
    pushl  -32(%ebp)
    pushl  %ebp
    call   factorial
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
    pushl  -20(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $16, %esp
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
