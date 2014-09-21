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
    addl   $-356, %esp
    movl   $1, -100(%ebp)
    movl   -100(%ebp), %ecx
    movl   %ecx, -104(%ebp)
    movl   -104(%ebp), %ecx
    movl   %ecx, -20(%ebp)
    movl   $2, -108(%ebp)
    movl   -108(%ebp), %ecx
    movl   %ecx, -112(%ebp)
    movl   -112(%ebp), %ecx
    movl   %ecx, -24(%ebp)
    movl   $3, -116(%ebp)
    movl   -116(%ebp), %ecx
    movl   %ecx, -120(%ebp)
    movl   -120(%ebp), %ecx
    movl   %ecx, -28(%ebp)
    movl   $4, -124(%ebp)
    movl   -124(%ebp), %ecx
    movl   %ecx, -128(%ebp)
    movl   -128(%ebp), %ecx
    movl   %ecx, -32(%ebp)
    movl   $5, -132(%ebp)
    movl   -132(%ebp), %ecx
    movl   %ecx, -136(%ebp)
    movl   -136(%ebp), %ecx
    movl   %ecx, -36(%ebp)
    movl   $6, -140(%ebp)
    movl   -140(%ebp), %ecx
    movl   %ecx, -144(%ebp)
    movl   -144(%ebp), %ecx
    movl   %ecx, -40(%ebp)
    movl   $7, -148(%ebp)
    movl   -148(%ebp), %ecx
    movl   %ecx, -152(%ebp)
    movl   -152(%ebp), %ecx
    movl   %ecx, -44(%ebp)
    movl   $8, -156(%ebp)
    movl   -156(%ebp), %ecx
    movl   %ecx, -160(%ebp)
    movl   -160(%ebp), %ecx
    movl   %ecx, -48(%ebp)
    movl   $9, -164(%ebp)
    movl   -164(%ebp), %ecx
    movl   %ecx, -168(%ebp)
    movl   -168(%ebp), %ecx
    movl   %ecx, -52(%ebp)
    movl   $10, -172(%ebp)
    movl   -172(%ebp), %ecx
    movl   %ecx, -176(%ebp)
    movl   -176(%ebp), %ecx
    movl   %ecx, -56(%ebp)
    movl   $11, -180(%ebp)
    movl   -180(%ebp), %ecx
    movl   %ecx, -184(%ebp)
    movl   -184(%ebp), %ecx
    movl   %ecx, -64(%ebp)
    movl   $12, -188(%ebp)
    movl   -188(%ebp), %ecx
    movl   %ecx, -192(%ebp)
    movl   -192(%ebp), %ecx
    movl   %ecx, -68(%ebp)
    movl   $13, -196(%ebp)
    movl   -196(%ebp), %ecx
    movl   %ecx, -200(%ebp)
    movl   -200(%ebp), %ecx
    movl   %ecx, -72(%ebp)
    movl   $14, -204(%ebp)
    movl   -204(%ebp), %ecx
    movl   %ecx, -208(%ebp)
    movl   -208(%ebp), %ecx
    movl   %ecx, -76(%ebp)
    movl   $15, -212(%ebp)
    movl   -212(%ebp), %ecx
    movl   %ecx, -216(%ebp)
    movl   -216(%ebp), %ecx
    movl   %ecx, -80(%ebp)
    movl   $16, -220(%ebp)
    movl   -220(%ebp), %ecx
    movl   %ecx, -224(%ebp)
    movl   -224(%ebp), %ecx
    movl   %ecx, -84(%ebp)
    movl   $17, -228(%ebp)
    movl   -228(%ebp), %ecx
    movl   %ecx, -232(%ebp)
    movl   -232(%ebp), %ecx
    movl   %ecx, -88(%ebp)
    movl   $18, -236(%ebp)
    movl   -236(%ebp), %ecx
    movl   %ecx, -240(%ebp)
    movl   -240(%ebp), %ecx
    movl   %ecx, -92(%ebp)
    movl   $19, -244(%ebp)
    movl   -244(%ebp), %ecx
    movl   %ecx, -248(%ebp)
    movl   -248(%ebp), %ecx
    movl   %ecx, -96(%ebp)
    movl   $20, -252(%ebp)
    movl   -252(%ebp), %ecx
    movl   %ecx, -256(%ebp)
    movl   -256(%ebp), %ecx
    movl   %ecx, 0(%ebp)
    pushl  %ecx
    pushl  %edx
    movl   -20(%ebp), %ecx
    movl   %ecx, -260(%ebp)
    movl   -24(%ebp), %ecx
    movl   %ecx, -264(%ebp)
    movl   -28(%ebp), %ecx
    movl   %ecx, -268(%ebp)
    movl   -32(%ebp), %ecx
    movl   %ecx, -272(%ebp)
    movl   -36(%ebp), %ecx
    movl   %ecx, -276(%ebp)
    movl   -40(%ebp), %ecx
    movl   %ecx, -280(%ebp)
    movl   -44(%ebp), %ecx
    movl   %ecx, -284(%ebp)
    movl   -48(%ebp), %ecx
    movl   %ecx, -288(%ebp)
    movl   -52(%ebp), %ecx
    movl   %ecx, -292(%ebp)
    movl   -56(%ebp), %eax
    imul   -292(%ebp), %eax
    movl   %eax, -296(%ebp)
    movl   -296(%ebp), %ecx
    addl   %ecx, -288(%ebp)
    movl   -288(%ebp), %eax
    imul   -284(%ebp), %eax
    movl   %eax, -300(%ebp)
    movl   -300(%ebp), %ecx
    addl   %ecx, -280(%ebp)
    movl   -280(%ebp), %eax
    imul   -276(%ebp), %eax
    movl   %eax, -304(%ebp)
    movl   -304(%ebp), %ecx
    addl   %ecx, -272(%ebp)
    movl   -272(%ebp), %eax
    imul   -268(%ebp), %eax
    movl   %eax, -308(%ebp)
    movl   -308(%ebp), %ecx
    addl   %ecx, -264(%ebp)
    movl   -264(%ebp), %eax
    imul   -260(%ebp), %eax
    movl   %eax, -312(%ebp)
    movl   -312(%ebp), %ecx
    movl   %ecx, -316(%ebp)
    movl   -64(%ebp), %ecx
    movl   %ecx, -320(%ebp)
    movl   -68(%ebp), %eax
    imul   -320(%ebp), %eax
    movl   %eax, -324(%ebp)
    movl   -324(%ebp), %ecx
    movl   %ecx, -328(%ebp)
    movl   -72(%ebp), %ecx
    addl   %ecx, -328(%ebp)
    movl   -328(%ebp), %ecx
    movl   %ecx, -332(%ebp)
    movl   -76(%ebp), %eax
    imul   -332(%ebp), %eax
    movl   %eax, -336(%ebp)
    movl   -336(%ebp), %ecx
    movl   %ecx, -340(%ebp)
    movl   -80(%ebp), %ecx
    addl   %ecx, -340(%ebp)
    movl   -340(%ebp), %ecx
    movl   %ecx, -344(%ebp)
    movl   -84(%ebp), %eax
    imul   -344(%ebp), %eax
    movl   %eax, -348(%ebp)
    movl   -348(%ebp), %ecx
    movl   %ecx, -352(%ebp)
    movl   -88(%ebp), %ecx
    addl   %ecx, -352(%ebp)
    movl   -352(%ebp), %ecx
    movl   %ecx, -356(%ebp)
    movl   -92(%ebp), %eax
    imul   -356(%ebp), %eax
    movl   %eax, -360(%ebp)
    movl   -360(%ebp), %ecx
    movl   %ecx, -364(%ebp)
    movl   -96(%ebp), %ecx
    addl   %ecx, -364(%ebp)
    movl   -364(%ebp), %ecx
    movl   %ecx, -368(%ebp)
    movl   0(%ebp), %eax
    imul   -368(%ebp), %eax
    movl   %eax, -372(%ebp)
    movl   -372(%ebp), %ecx
    addl   %ecx, -316(%ebp)
    pushl  -316(%ebp)
    pushl  $_intPrint
    call   printf
    addl   $8, %esp
    popl   %edx
    popl   %ecx
    addl   $356, %esp
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
