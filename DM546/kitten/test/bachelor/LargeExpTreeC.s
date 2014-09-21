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
    addl   $-436, %esp
    movl   $3, -100(%ebp)
    pushl  -100(%ebp)
    movl   $1, -104(%ebp)
    pushl  -104(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -108(%ebp)
    movl   -108(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $3, -112(%ebp)
    pushl  -112(%ebp)
    movl   $2, -116(%ebp)
    pushl  -116(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -120(%ebp)
    movl   -120(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $3, -124(%ebp)
    pushl  -124(%ebp)
    movl   $3, -128(%ebp)
    pushl  -128(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -132(%ebp)
    movl   -132(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   $3, -136(%ebp)
    pushl  -136(%ebp)
    movl   $4, -140(%ebp)
    pushl  -140(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -144(%ebp)
    movl   -144(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $3, -148(%ebp)
    pushl  -148(%ebp)
    movl   $5, -152(%ebp)
    pushl  -152(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -156(%ebp)
    movl   -156(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   $3, -160(%ebp)
    pushl  -160(%ebp)
    movl   $6, -164(%ebp)
    pushl  -164(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -168(%ebp)
    movl   -168(%ebp), %ecx
    movl   %ecx, -40(%ebp)
    movl   $3, -172(%ebp)
    pushl  -172(%ebp)
    movl   $7, -176(%ebp)
    pushl  -176(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -180(%ebp)
    movl   -180(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   $3, -184(%ebp)
    pushl  -184(%ebp)
    movl   $8, -188(%ebp)
    pushl  -188(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -192(%ebp)
    movl   -192(%ebp), %ecx
    movl   %ecx, -48(%ebp)
    movl   $3, -196(%ebp)
    pushl  -196(%ebp)
    movl   $9, -200(%ebp)
    pushl  -200(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -204(%ebp)
    movl   -204(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   $3, -208(%ebp)
    pushl  -208(%ebp)
    movl   $10, -212(%ebp)
    pushl  -212(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -216(%ebp)
    movl   -216(%ebp), %ecx
    movl   %ecx, -56(%ebp)
    movl   $3, -220(%ebp)
    pushl  -220(%ebp)
    movl   $11, -224(%ebp)
    pushl  -224(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -228(%ebp)
    movl   -228(%ebp), %ecx
    movl   %ecx, -64(%ebp)
    movl   $3, -232(%ebp)
    pushl  -232(%ebp)
    movl   $12, -236(%ebp)
    pushl  -236(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -240(%ebp)
    movl   -240(%ebp), %ecx
    movl   %ecx, -68(%ebp)
    movl   $3, -244(%ebp)
    pushl  -244(%ebp)
    movl   $13, -248(%ebp)
    pushl  -248(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -252(%ebp)
    movl   -252(%ebp), %ecx
    movl   %ecx, -72(%ebp)
    movl   $3, -256(%ebp)
    pushl  -256(%ebp)
    movl   $14, -260(%ebp)
    pushl  -260(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -264(%ebp)
    movl   -264(%ebp), %ecx
    movl   %ecx, -76(%ebp)
    movl   $3, -268(%ebp)
    pushl  -268(%ebp)
    movl   $15, -272(%ebp)
    pushl  -272(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -276(%ebp)
    movl   -276(%ebp), %ecx
    movl   %ecx, -80(%ebp)
    movl   $3, -280(%ebp)
    pushl  -280(%ebp)
    movl   $16, -284(%ebp)
    pushl  -284(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -288(%ebp)
    movl   -288(%ebp), %ecx
    movl   %ecx, -84(%ebp)
    movl   $3, -292(%ebp)
    pushl  -292(%ebp)
    movl   $17, -296(%ebp)
    pushl  -296(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -300(%ebp)
    movl   -300(%ebp), %ecx
    movl   %ecx, -88(%ebp)
    movl   $3, -304(%ebp)
    pushl  -304(%ebp)
    movl   $18, -308(%ebp)
    pushl  -308(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -312(%ebp)
    movl   -312(%ebp), %ecx
    movl   %ecx, -92(%ebp)
    movl   $3, -316(%ebp)
    pushl  -316(%ebp)
    movl   $19, -320(%ebp)
    pushl  -320(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -324(%ebp)
    movl   -324(%ebp), %ecx
    movl   %ecx, -96(%ebp)
    movl   $3, -328(%ebp)
    pushl  -328(%ebp)
    movl   $20, -332(%ebp)
    pushl  -332(%ebp)
    pushl  %ebp
    call   echo
    popl   %ebp
    addl   $8, %esp
    movl   %eax, -336(%ebp)
    movl   -336(%ebp), %ecx
    movl   %ecx, 0(%ebp)
    pushl  %ecx
    pushl  %edx
    movl   -20(%ebp), %ecx
    movl   %ecx, -340(%ebp)
    movl   -24(%ebp), %ecx
    movl   %ecx, -344(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -348(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -352(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -356(%ebp)
    movl   -40(%ebp), %ecx
    movl   %ecx, -360(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -364(%ebp)
    movl   -48(%ebp), %ecx
    movl   %ecx, -368(%ebp)
    movl   -52(%ebp), %ecx
    movl   %ecx, -372(%ebp)
    movl   -56(%ebp), %eax
    imul   -372(%ebp), %eax
    movl   %eax, -376(%ebp)
    movl   -376(%ebp), %ecx
    addl   %ecx, -368(%ebp)
    movl   -368(%ebp), %eax
    imul   -364(%ebp), %eax
    movl   %eax, -380(%ebp)
    movl   -380(%ebp), %ecx
    addl   %ecx, -360(%ebp)
    movl   -360(%ebp), %eax
    imul   -356(%ebp), %eax
    movl   %eax, -384(%ebp)
    movl   -384(%ebp), %ecx
    addl   %ecx, -352(%ebp)
    movl   -352(%ebp), %eax
    imul   -348(%ebp), %eax
    movl   %eax, -388(%ebp)
    movl   -388(%ebp), %ecx
    addl   %ecx, -344(%ebp)
    movl   -344(%ebp), %eax
    imul   -340(%ebp), %eax
    movl   %eax, -392(%ebp)
    movl   -392(%ebp), %ecx
    movl   %ecx, -396(%ebp)
    movl   -64(%ebp), %ecx
    movl   %ecx, -400(%ebp)
    movl   -68(%ebp), %eax
    imul   -400(%ebp), %eax
    movl   %eax, -404(%ebp)
    movl   -404(%ebp), %ecx
    movl   %ecx, -408(%ebp)
    movl   -72(%ebp), %ecx
    addl   %ecx, -408(%ebp)
    movl   -408(%ebp), %ecx
    movl   %ecx, -412(%ebp)
    movl   -76(%ebp), %eax
    imul   -412(%ebp), %eax
    movl   %eax, -416(%ebp)
    movl   -416(%ebp), %ecx
    movl   %ecx, -420(%ebp)
    movl   -80(%ebp), %ecx
    addl   %ecx, -420(%ebp)
    movl   -420(%ebp), %ecx
    movl   %ecx, -424(%ebp)
    movl   -84(%ebp), %eax
    imul   -424(%ebp), %eax
    movl   %eax, -428(%ebp)
    movl   -428(%ebp), %ecx
    movl   %ecx, -432(%ebp)
    movl   -88(%ebp), %ecx
    addl   %ecx, -432(%ebp)
    movl   -432(%ebp), %ecx
    movl   %ecx, -436(%ebp)
    movl   -92(%ebp), %eax
    imul   -436(%ebp), %eax
    movl   %eax, -440(%ebp)
    movl   -440(%ebp), %ecx
    movl   %ecx, -444(%ebp)
    movl   -96(%ebp), %ecx
    addl   %ecx, -444(%ebp)
    movl   -444(%ebp), %ecx
    movl   %ecx, -448(%ebp)
    movl   0(%ebp), %eax
    imul   -448(%ebp), %eax
    movl   %eax, -452(%ebp)
    movl   -452(%ebp), %ecx
    addl   %ecx, -396(%ebp)
    pushl  -396(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $436, %esp
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
