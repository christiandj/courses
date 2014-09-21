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
    addl   $-92, %esp
    movl   $0, -32(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $0, -40(%ebp)
    movl   -40(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   $0, -48(%ebp)
    movl   -48(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   -52(%ebp), %ecx
    movl   %ecx, -20(%ebp)
loop0:
    movl   -24(%ebp), %ecx
    movl   %ecx, -56(%ebp)
    movl   $1, -60(%ebp)
    movl   -60(%ebp), %ecx
    addl   %ecx, -56(%ebp)
    movl   -56(%ebp), %ecx
    movl   %ecx, -64(%ebp)
    movl   -64(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $1, -68(%ebp)
    movl   -68(%ebp), %ecx
    movl   %ecx, -72(%ebp)
    movl   -28(%ebp), %ecx
    subl   %ecx, -72(%ebp)
    movl   -72(%ebp), %ecx
    movl   %ecx, -76(%ebp)
    movl   -76(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -80(%ebp)
    movl   $1, -84(%ebp)
    movl   -80(%ebp), %ecx
    cmp    -84(%ebp), %ecx
    jne    false0
    movl   $1, -88(%ebp)
    jmp    end_comparison0
false0:
    movl   $0, -88(%ebp)
end_comparison0:
    cmp    $1, -88(%ebp)
    jne    end_if0
    jmp    loop0
end_if0:
    movl   -20(%ebp), %ecx
    movl   %ecx, -92(%ebp)
    movl   -24(%ebp), %ecx
    addl   %ecx, -92(%ebp)
    movl   -92(%ebp), %ecx
    movl   %ecx, -96(%ebp)
    movl   -96(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   -20(%ebp), %ecx
    movl   %ecx, -100(%ebp)
    movl   $40, -104(%ebp)
    movl   -100(%ebp), %ecx
    cmp    -104(%ebp), %ecx
    jl     false1
    movl   $1, -108(%ebp)
    jmp    end_comparison1
false1:
    movl   $0, -108(%ebp)
end_comparison1:
    cmp    $1, -108(%ebp)
    jne    end_if1
    jmp    end_loop0
end_if1:
    jmp    loop0
end_loop0:
    pushl  %ecx
    pushl  %edx
    pushl  -20(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $92, %esp
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
