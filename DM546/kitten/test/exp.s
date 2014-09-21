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
exp:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-128, %esp
    movl   16(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $0, -24(%ebp)
    movl   -20(%ebp), %ecx
    cmp    -24(%ebp), %ecx
    jge    false0
    movl   $1, -28(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -28(%ebp)
end_comparison0:
    cmp    $1, -28(%ebp)
    jne    end_if0
    movl   $0, -32(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   16(%ebp), %ecx
    subl   %ecx, -36(%ebp)
    pushl  -36(%ebp)
    movl   $1, -40(%ebp)
    movl   -40(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    cmp    $0, 12(%ebp)
    je     divbyzero
    movl   -44(%ebp), %eax
    cltd
    movl   12(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -48(%ebp)
    pushl  -48(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   exp
    popl   %edx
    addl   $8, %esp
    movl   %eax, %eax
    jmp    end_exp
end_if0:
    movl   16(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   $0, -56(%ebp)
    movl   -52(%ebp), %ecx
    cmp    -56(%ebp), %ecx
    jne    false1
    movl   $1, -60(%ebp)
    jmp    end_comparison1
false1:
    movl   $0, -60(%ebp)
end_comparison1:
    cmp    $1, -60(%ebp)
    jne    end_if1
    movl   $1, -64(%ebp)
    movl   -64(%ebp), %eax
    jmp    end_exp
end_if1:
    movl   16(%ebp), %ecx
    movl   %ecx, -68(%ebp)
    movl   $1, -72(%ebp)
    movl   -68(%ebp), %ecx
    cmp    -72(%ebp), %ecx
    jne    false2
    movl   $1, -76(%ebp)
    jmp    end_comparison2
false2:
    movl   $0, -76(%ebp)
end_comparison2:
    cmp    $1, -76(%ebp)
    jne    end_if2
    movl   12(%ebp), %eax
    jmp    end_exp
end_if2:
    pushl  16(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   even
    popl   %edx
    addl   $4, %esp
    movl   %eax, -80(%ebp)
    movl   $1, -84(%ebp)
    movl   -80(%ebp), %ecx
    cmp    -84(%ebp), %ecx
    jne    false3
    movl   $1, -88(%ebp)
    jmp    end_comparison3
false3:
    movl   $0, -88(%ebp)
end_comparison3:
    cmp    $1, -88(%ebp)
    jne    end_if3
    movl   16(%ebp), %ecx
    movl   %ecx, -92(%ebp)
    movl   $2, -96(%ebp)
    cmp    $0, -96(%ebp)
    je     divbyzero
    movl   -92(%ebp), %eax
    cltd
    movl   -96(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -100(%ebp)
    pushl  -100(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -104(%ebp)
    movl   12(%ebp), %eax
    imul   -104(%ebp), %eax
    movl   %eax, -108(%ebp)
    pushl  -108(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   exp
    popl   %edx
    addl   $8, %esp
    movl   %eax, %eax
    jmp    end_exp
end_if3:
    movl   12(%ebp), %ecx
    movl   %ecx, -112(%ebp)
    movl   16(%ebp), %ecx
    movl   %ecx, -116(%ebp)
    movl   $1, -120(%ebp)
    movl   -120(%ebp), %ecx
    subl   %ecx, -116(%ebp)
    movl   -116(%ebp), %ecx
    movl   %ecx, -124(%ebp)
    movl   $2, -128(%ebp)
    cmp    $0, -128(%ebp)
    je     divbyzero
    movl   -124(%ebp), %eax
    cltd
    movl   -128(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -132(%ebp)
    pushl  -132(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -136(%ebp)
    movl   12(%ebp), %eax
    imul   -136(%ebp), %eax
    movl   %eax, -140(%ebp)
    pushl  -140(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   exp
    popl   %edx
    addl   $8, %esp
    imul   -112(%ebp), %eax
    movl   %eax, -144(%ebp)
    movl   -144(%ebp), %eax
    jmp    end_exp
end_exp:
    addl   $128, %esp
    addl   $4, %esp
    popl   %edi
    popl   %esi
    popl   %ebx
    movl   %ebp, %edx
    movl   %edx, %esp
    popl   %ebp
    ret
even:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-40, %esp
    movl   12(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $0, -24(%ebp)
    movl   -20(%ebp), %ecx
    cmp    -24(%ebp), %ecx
    jne    false4
    movl   $1, -28(%ebp)
    jmp    end_comparison4
false4:
    movl   $0, -28(%ebp)
end_comparison4:
    cmp    $1, -28(%ebp)
    jne    end_if4
    movl   $1, -32(%ebp)
    movl   -32(%ebp), %eax
    jmp    end_even
end_if4:
    movl   12(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   $1, -40(%ebp)
    movl   -36(%ebp), %ecx
    cmp    -40(%ebp), %ecx
    jne    false5
    movl   $1, -44(%ebp)
    jmp    end_comparison5
false5:
    movl   $0, -44(%ebp)
end_comparison5:
    cmp    $1, -44(%ebp)
    jne    end_if5
    movl   $0, -48(%ebp)
    movl   -48(%ebp), %eax
    jmp    end_even
end_if5:
    movl   12(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   $2, -56(%ebp)
    movl   -56(%ebp), %ecx
    subl   %ecx, -52(%ebp)
    pushl  -52(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   even
    popl   %edx
    addl   $4, %esp
    movl   %eax, %eax
    jmp    end_even
end_even:
    addl   $40, %esp
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
    movl   $10, -20(%ebp)
    pushl  -20(%ebp)
    movl   $2, -24(%ebp)
    pushl  -24(%ebp)
    pushl  %ebp
    call   exp
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
