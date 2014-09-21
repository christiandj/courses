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
abs:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-32, %esp
    movl   12(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $0, -24(%ebp)
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
    movl   12(%ebp), %eax
    jmp    end_abs
end_if0:
    movl   12(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $0, -36(%ebp)
    movl   -32(%ebp), %ecx
    cmp    -36(%ebp), %ecx
    jge    false1
    movl   $1, -40(%ebp)
    jmp    end_comparison1
false1:
    movl   $0, -40(%ebp)
end_comparison1:
    cmp    $1, -40(%ebp)
    jne    end_if1
    movl   $0, -44(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -48(%ebp)
    movl   12(%ebp), %ecx
    subl   %ecx, -48(%ebp)
    movl   -48(%ebp), %eax
    jmp    end_abs
end_if1:
end_abs:
    addl   $32, %esp
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
    pushl  %ecx
    pushl  %edx
    movl   $42, -20(%ebp)
    pushl  -20(%ebp)
    pushl  %ebp
    call   abs
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
    movl   $0, -24(%ebp)
    movl   -24(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   $42, -32(%ebp)
    movl   -32(%ebp), %ecx
    subl   %ecx, -28(%ebp)
    pushl  -28(%ebp)
    pushl  %ebp
    call   abs
    popl   %ebp
    addl   $4, %esp
    pushl  %eax
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
