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
    addl   $-60, %esp
    movl   $1, -20(%ebp)
    movl   -20(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $2, -28(%ebp)
    movl   -24(%ebp), %ecx
    cmp    -28(%ebp), %ecx
    jge    false0
    movl   $1, -32(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -32(%ebp)
end_comparison0:
    cmp    $1, -32(%ebp)
    jne    end_if0
    pushl  %ecx
    pushl  %edx
    movl   $1, -36(%ebp)
    pushl  -36(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
end_if0:
    movl   $1, -40(%ebp)
    movl   -40(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   $2, -48(%ebp)
    movl   -44(%ebp), %ecx
    cmp    -48(%ebp), %ecx
    jne    false1
    movl   $1, -52(%ebp)
    jmp    end_comparison1
false1:
    movl   $0, -52(%ebp)
end_comparison1:
    cmp    $1, -52(%ebp)
    jne    end_if1
    pushl  %ecx
    pushl  %edx
    movl   $2, -56(%ebp)
    pushl  -56(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
end_if1:
    movl   $1, -60(%ebp)
    movl   -60(%ebp), %ecx
    movl   %ecx, -64(%ebp)
    movl   $2, -68(%ebp)
    movl   -64(%ebp), %ecx
    cmp    -68(%ebp), %ecx
    jle    false2
    movl   $1, -72(%ebp)
    jmp    end_comparison2
false2:
    movl   $0, -72(%ebp)
end_comparison2:
    cmp    $1, -72(%ebp)
    jne    end_if2
    pushl  %ecx
    pushl  %edx
    movl   $3, -76(%ebp)
    pushl  -76(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
end_if2:
    addl   $60, %esp
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
