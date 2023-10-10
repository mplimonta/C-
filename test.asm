j main
LAB main
addi $t29 $t30 0
addi $t30 $t30 1
addi $t30 $t30 5
addi $t1 $t0 3
addi $t2 $t0 2
addi $t3 $t1 1
swr $t2 $t29 $t3
addi $t4 $t0 4
addi $t5 $t0 3
addi $t6 $t5 1
lwr $t7 $t29 $t6
addi $t8 $t4 1
swr $t7 $t29 $t8
addi $t9 $t0 3
addi $t10 $t9 1
lwr $t11 $t29 $t10
sw $t11 $t29 0
halt
