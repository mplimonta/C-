j main
addi $t30 $t30 1
sw $t31 $t29 1
addi $t30 $t30 1
addi $t30 $t30 1
lw $t1 $t29 3
addi $t2 $t0 0
comp $t3 $t1 $t2
lw $t4 $t29 2
addi $t28 $t4 0
j L1
LAB L0
lw $t5 $t29 3
lw $t6 $t29 2
lw $t7 $t29 2
lw $t8 $t29 3
div $t9 $t7 $t8
lw $t10 $t29 3
mult $t11 $t9 $t10
sub $t12 $t6 $t11
sw $t1 $t30 0
addi $t30 $t30 1
sw $t4 $t30 0
addi $t30 $t30 1
sw $t29 $t30 0
addi $t29 $t30 0
addi $t30 $t30 1
sw $t5 $t29 2
sw $t12 $t29 3
jal gcd
addi $t30 $t29 0
lw $t29 $t29 0
subi $t30 $t30 1
lw $t1 $t30 0
subi $t30 $t30 1
lw $t4 $t30 0
addi $t28 $t28 0
j L1
LAB L1
lw $t31 $t29 1
jr $t31
addi $t30 $t30 1
sw $t31 $t29 1
addi $t30 $t30 1
addi $t30 $t30 1
input $t28
sw $t1 $t29 1
input $t28
sw $t1 $t29 2
lw $t16 $t29 1
lw $t17 $t29 2
sw $t16 $t30 0
addi $t30 $t30 1
sw $t17 $t30 0
addi $t30 $t30 1
sw $t29 $t30 0
addi $t29 $t30 0
addi $t30 $t30 1
sw $t16 $t29 2
sw $t17 $t29 3
jal gcd
addi $t30 $t29 0
lw $t29 $t29 0
subi $t30 $t30 1
lw $t16 $t30 0
subi $t30 $t30 1
lw $t17 $t30 0
output $t28
lw $t31 $t29 1
jr $t31
