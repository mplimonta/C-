j main
LAB main
addi $t29 $t30 0
addi $t30 $t30 5
addi $t30 $t30 1
addi $t30 $t30 1
addi $t1 $t0 0
sw $t1 $t29 5
addi $t2 $t0 0
sw $t2 $t29 6
addi $t3 $t0 31
addi $t4 $t0 0
addi $t5 $t4 0
sw $t3 $t5 0
addi $t6 $t0 1
addi $t7 $t0 1
addi $t8 $t7 0
sw $t6 $t8 0
addi $t9 $t0 73
addi $t10 $t0 2
addi $t11 $t10 0
sw $t9 $t11 0
addi $t12 $t0 22
addi $t13 $t0 3
addi $t14 $t13 0
sw $t12 $t14 0
addi $t15 $t0 7
addi $t16 $t0 4
addi $t17 $t16 0
sw $t15 $t17 0
LAB L0
lw $t18 $t29 5
addi $t19 $t0 5
lt $t20 $t18 $t19
beq $t20 $t0 L1
lw $t21 $t29 5
addi $t22 $t21 0
lw $t23 $t22 0
lw $t24 $t29 6
gt $t25 $t23 $t24
beq $t25 $t0 L2
lw $t26 $t29 5
addi $t27 $t26 0
lw $t28 $t27 0
sw $t28 $t29 6
j L3
LAB L2
LAB L3
lw $t1 $t29 5
addi $t2 $t0 1
add $t3 $t1 $t2
sw $t3 $t29 5
j L0
LAB L1
lw $t1 $t29 6
output $t1
halt
