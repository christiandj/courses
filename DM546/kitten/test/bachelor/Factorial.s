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
    addl   $-48, %esp
    movl   12(%ebp), %ecx
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
    movl   -28(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    cmp    $1, -32(%ebp)
    je     lor0
    movl   12(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   $1, -40(%ebp)
    movl   -36(%ebp), %ecx
    cmp    -40(%ebp), %ecx
    jne    false1
    movl   $1, -44(%ebp)
    jmp    end_comparison1
false1:
    movl   $0, -44(%ebp)
end_comparison1:
lor0:
    movl   -44(%ebp), %ecx
    or     %ecx, -32(%ebp)
    cmp    $1, -32(%ebp)
    jne    end_if0
    movl   $1, -48(%ebp)
    movl   -48(%ebp), %eax
    jmp    end_factorial
end_if0:
    movl   12(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -56(%ebp)
    movl   $1, -60(%ebp)
    movl   -60(%ebp), %ecx
    subl   %ecx, -56(%ebp)
    pushl  -56(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   factorial
    popl   %edx
    addl   $4, %esp
    imul   -52(%ebp), %eax
    movl   %eax, -64(%ebp)
    movl   -64(%ebp), %eax
    jmp    end_factorial
end_factorial:
    addl   $48, %esp
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
    movl   $5, -20(%ebp)
    pushl  -20(%ebp)
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
