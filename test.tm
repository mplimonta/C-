
FUNC, inteiro, gcd -
ARG, inteiro, u, global
ARG, inteiro, v, global

FUNC, void, main -
ALLOC, x, main -
ALLOC, y, main -
CALL, $t0, input, 0
STORE, x, $t0 -
CALL, $t1, input, 0
STORE, y, $t1 -
LOAD, $t2, x -
PARAM, $t2, -, -
LOAD, $t3, y -
PARAM, $t3, -, -
CALL, $t4, gcd, 2
PARAM, $t4, -, -
CALL, $t5, output, 1

FUNC, void, blha -
ALLOC, x, blha -
MOVE, $t6, 5
STORE, x, $t6 -
