j main
LAB gcd
addi $t30 $t30 1
sw $t31 $t29 1
addi $t30 $t30 1
LAB L0
lw $t1 $t29 2
addi $t2 $t0 35
neq $t3 $t1 $t2
beqz $t3 L1
LAB L2
addi $t4 $t0 1
addi $t5 $t0 1
comp $t6 $t4 $t5
beqz $t6 L3
lw $t7 $t29 2
addi $t8 $t0 1
add $t9 $t7 $t8
sw $t9 $t29 2
j L2
LAB L3
j L0
LAB L1
lw $t10 $t29 2
addi $t28 $t10 0
lw $t31 $t29 1
jr $t31
LAB main
addi $t30 $t30 1
sw $t31 $t29 1
addi $t30 $t30 1
lw $t11 $t29 1
sw $t1 $t30 0
addi $t30 $t30 1
sw $t11 $t30 0
addi $t30 $t30 1
sw $t29 $t30 0
addi $t29 $t30 0
addi $t30 $t30 1
sw $t11 $t29 2
jal gcd
addi $t30 $t29 0
lw $t29 $t29 0
subi $t30 $t30 1
lw $t1 $t30 0
subi $t30 $t30 1
lw $t11 $t30 0
sw $t1 $t29 1
lw $t31 $t29 1
jr $t31