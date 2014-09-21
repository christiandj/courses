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
log:
    pushl  %ebp
    movl   %esp, %edx
    movl   %edx, %ebp
    pushl  %ebx
    pushl  %esi
    pushl  %edi
    addl   $-92, %esp
    movl   $0, -28(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   12(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -20(%ebp)
loop0:
    pushl  -20(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   even
    popl   %edx
    addl   $4, %esp
    movl   %eax, -40(%ebp)
    movl   $0, -44(%ebp)
    movl   -40(%ebp), %ecx
    cmp    -44(%ebp), %ecx
    jne    false0
    movl   $1, -48(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -48(%ebp)
end_comparison0:
    cmp    $1, -48(%ebp)
    jne    end_if0
    movl   -20(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   $1, -56(%ebp)
    movl   -56(%ebp), %ecx
    subl   %ecx, -52(%ebp)
    movl   -52(%ebp), %ecx
    movl   %ecx, -60(%ebp)
    movl   -60(%ebp), %ecx
    movl   %ecx, -20(%ebp)
end_if0:
    pushl  -20(%ebp)
    movl   8(%ebp),%edx
    pushl  %edx
    call   even
    popl   %edx
    addl   $4, %esp
    movl   %eax, -64(%ebp)
    movl   $1, -68(%ebp)
    movl   -64(%ebp), %ecx
    cmp    -68(%ebp), %ecx
    jne    false1
    movl   $1, -72(%ebp)
    jmp    end_comparison1
false1:
    movl   $0, -72(%ebp)
end_comparison1:
    cmp    $1, -72(%ebp)
    jne    end_if1
    movl   -20(%ebp), %ecx
    movl   %ecx, -76(%ebp)
    cmp    $0, 16(%ebp)
    je     divbyzero
    movl   -76(%ebp), %eax
    cltd
    movl   16(%ebp), %ecx
    idiv   %ecx
    movl   %eax, -80(%ebp)
    movl   -80(%ebp), %ecx
    movl   %ecx, -84(%ebp)
    movl   -84(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   -24(%ebp), %ecx
    movl   %ecx, -88(%ebp)
    movl   $1, -92(%ebp)
    movl   -92(%ebp), %ecx
    addl   %ecx, -88(%ebp)
    movl   -88(%ebp), %ecx
    movl   %ecx, -96(%ebp)
    movl   -96(%ebp), %ecx
    movl   %ecx, -24(%ebp)
end_if1:
    movl   -20(%ebp), %ecx
    movl   %ecx, -100(%ebp)
    movl   $1, -104(%ebp)
    movl   -100(%ebp), %ecx
    cmp    -104(%ebp), %ecx
    jg     false2
    movl   $1, -108(%ebp)
    jmp    end_comparison2
false2:
    movl   $0, -108(%ebp)
end_comparison2:
    cmp    $1, -108(%ebp)
    jne    end_if2
    jmp    end_loop0
end_if2:
    jmp    loop0
end_loop0:
    movl   -24(%ebp), %eax
    jmp    end_log
end_log:
    addl   $92, %esp
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
    jne    false3
    movl   $1, -28(%ebp)
    jmp    end_comparison3
false3:
    movl   $0, -28(%ebp)
end_comparison3:
    cmp    $1, -28(%ebp)
    jne    end_if3
    movl   $1, -32(%ebp)
    movl   -32(%ebp), %eax
    jmp    end_even
end_if3:
    movl   12(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   $1, -40(%ebp)
    movl   -36(%ebp), %ecx
    cmp    -40(%ebp), %ecx
    jne    false4
    movl   $1, -44(%ebp)
    jmp    end_comparison4
false4:
    movl   $0, -44(%ebp)
end_comparison4:
    cmp    $1, -44(%ebp)
    jne    end_if4
    movl   $0, -48(%ebp)
    movl   -48(%ebp), %eax
    jmp    end_even
end_if4:
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
    movl   $2, -20(%ebp)
    pushl  -20(%ebp)
    movl   $1024, -24(%ebp)
    pushl  -24(%ebp)
    pushl  %ebp
    call   log
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
