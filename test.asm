j main
LAB main
addi $t29 $t30 0
addi $t30 $t30 2
addi $t30 $t30 2
addi $t30 $t30 1
addi $t30 $t30 1
addi $t1 $t0 0
changemem $t1
add $t2 $t0 $t28
addi $t3 $t0 0
sw $t3 $t29 4
addi $t4 $t0 100
addi $t5 $t0 0
addi $t6 $t5 0
sw $t4 $t6 0
addi $t7 $t0 200
addi $t8 $t0 1
addi $t9 $t8 0
sw $t7 $t9 0
LAB L0
addi $t10 $t0 1
addi $t11 $t0 1
comp $t12 $t10 $t11
beq $t12 $t0 L1
save
add $t13 $t0 $t28
lw $t14 $t29 4
addi $t15 $t0 1
add $t16 $t14 $t15
changemem $t16
add $t17 $t0 $t28
lw $t18 $t29 4
addi $t19 $t18 0
lw $t20 $t19 0
lw $t21 $t29 4
addi $t22 $t0 1
add $t23 $t21 $t22
exec $t20
changemem $t23
add $t24 $t0 $t28
save
add $t25 $t0 $t28
addi $t26 $t0 0
changemem $t26
add $t27 $t0 $t28
load
add $t28 $t0 $t28
lw $t1 $t29 4
addi $t2 $t0 2
comp $t3 $t1 $t2
beq $t3 $t0 L2
addi $t1 $t0 0
sw $t1 $t29 4
j L3
LAB L2
lw $t1 $t29 4
addi $t2 $t0 1
add $t3 $t1 $t2
sw $t3 $t29 4
LAB L3
j L0
LAB L1
halt
