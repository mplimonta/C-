j main
LAB gc
addi $t30 $t30 1
sw $t31 $t29 1
addi $t30 $t30 1
lw $t1 $t29 2
addi $t28 $t1 0
j FIM:gc
LAB FIM:gc
lw $t31 $t29 1
jr $t31
LAB main
addi $t29 $t30 0
addi $t30 $t30 1
addi $t2 $t0 5
sw $t2 $t29 0
lw $t3 $t29 0
sw $t3 $t30 0
addi $t30 $t30 1
sw $t29 $t30 0
addi $t29 $t30 0
addi $t30 $t30 1
sw $t3 $t29 2
jal gc
addi $t30 $t29 0
lw $t29 $t29 0
subi $t30 $t30 1
lw $t3 $t30 0
add $t4 $t0 $t28
output $t4
halt
