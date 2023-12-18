void main(void) {
    /* S.O. */
    int processes[5];
    int states[5];
    int i;
    int program;
    changeOffset(288);     
    setProcessLine(157);    /*inicio do P1*/
    changeOffset(576);      
    setProcessLine(376);    /*inicio do P2*/
    changeOffset(864);
    setProcessLine(400);    /*inicio do P3*/
    changeOffset(1152);
    setProcessLine(500);    /*inicio do P4*/
    changeOffset(1440);
    setProcessLine(550);    /*inicio do P5*/
    changeOffset(0);
    i = 0;               
    while(1 == 1){
        sw(1);                          /*save OS regs on Memory*/
        sw(2);
        sw(3);
        sw(4);
        sw(5);
        sw(6);
        sw(7);
        sw(8);
        sw(9);
        sw(10);
        sw(11);
        sw(12);
        sw(13);
        sw(14);
        sw(15);
        sw(16);
        sw(17);
        sw(18);
        sw(19);
        sw(20);
        sw(21);
        sw(22);
        sw(23);
        sw(24);
        sw(25);
        sw(26);
        sw(27);
        sw(28);
        sw(29);
        sw(30);
        sw(31);
        NextLineTBE();              /* Salva a posicao da rom na 0 na ram FEITO*/
        changeOffset(288 * (i+1));  /*Change Offset to program's sgmnt*/
        lw(1);
        lw(2);
        lw(3);
        lw(4);
        lw(5);
        lw(6);
        lw(7);
        lw(8);          /*lw $t8 $t0 8 */
        lw(9);
        lw(10);
        lw(11);
        lw(12);
        lw(13);
        lw(14);
        lw(15);
        lw(16);
        lw(17);
        lw(18);
        lw(19);
        lw(20);
        lw(21);
        lw(22);
        lw(23);
        lw(24);
        lw(25);
        lw(26);
        lw(27);
        lw(28);
        lw(29);
        lw(30);
        lw(31);
        changeROM();  /*executa processo */
        output(28031970);
        sw(1);        /*DEVO RETORNAR AQUI*/
        sw(2);
        sw(3);
        sw(4);
        sw(5);
        sw(6);
        sw(7);
        sw(8);
        sw(9);
        sw(10);
        sw(11);
        sw(12);
        sw(13);
        sw(14);
        sw(15);
        sw(16);
        sw(17);
        sw(18);
        sw(19);
        sw(20);
        sw(21);
        sw(22);
        sw(23);
        sw(24);
        sw(25);
        sw(26);
        sw(27);
        sw(28);
        sw(29);
        sw(30);
        sw(31);
        changeOffset(0);
        lw(1);
        lw(2);
        lw(3);
        lw(4);
        lw(5);
        lw(6);
        lw(7);
        lw(8);
        lw(9);
        lw(10);
        lw(11);
        lw(12);
        lw(13);
        lw(14);
        lw(15);
        lw(16);
        lw(17);
        lw(18);
        lw(19);
        lw(20);
        lw(21);
        lw(22);
        lw(23);
        lw(24);
        lw(25);
        lw(26);
        lw(27);
        lw(28);
        lw(29);
        lw(30);
        lw(31);
        if(i == 2){
            i = 0;
        }else{
            i = i + 1;
        }
    }
}
/*
void main(void) {
    int processes[5];
    int i;
    int maior;
    maior = 0;
    i = 0;
    processes[0] = 35;
    processes[1] = 105;
    processes[2] = 1984;
    processes[3] = 2;
    processes[4] = 1;
    while(i < 5){
        if(processes[i] > maior){
            maior = processes[i];
        }
        i = i + 1;
    }
    output(maior);
}
*/


/*

int bababoi(int i){
    return i;
}

int baba(int i){
    return i;
}

void main(void) {
    int i;
    i = 5;
    output(baba(bababoi(i)));         
}
*/

// void main(void) {
//     /* S.O. */
//     int processes[1];
//     int states[1];
//     int i;
//     int program;
//     changeOffset(288);     
//     setProcessLine(163);    /*inicio do P1*/
//     changeOffset(0);
//     i = 0;               
//     while(1 == 1){
//         sw(1);                          /*save OS regs on Memory*/
//         sw(2);
//         sw(3);
//         sw(4);
//         sw(5);
//         sw(6);
//         sw(7);
//         sw(8);
//         sw(9);
//         sw(10);
//         sw(11);
//         sw(12);
//         sw(13);
//         sw(14);
//         sw(15);
//         sw(16);
//         sw(17);
//         sw(18);
//         sw(19);
//         sw(20);
//         sw(21);
//         sw(22);
//         sw(23);
//         sw(24);
//         sw(25);
//         sw(26);
//         sw(27);
//         sw(28);
//         sw(29);
//         sw(30);
//         sw(31);
//         changeOffset(288 * (i+1));  /*Change Offset to program's sgmnt*/
//         lw(1);
//         lw(2);
//         lw(3);
//         lw(4);
//         lw(5);
//         lw(6);
//         lw(7);
//         lw(8);          /*lw $t8 $t0 8 */
//         lw(9);
//         lw(10);
//         lw(11);
//         lw(12);
//         lw(13);
//         lw(14);
//         lw(15);
//         lw(16);
//         lw(17);
//         lw(18);
//         lw(19);
//         lw(20);
//         lw(21);
//         lw(22);
//         lw(23);
//         lw(24);
//         lw(25);
//         lw(26);
//         lw(27);
//         lw(28);
//         lw(29);
//         lw(30);
//         lw(31);
//         changeROM();  /*executa processo */
//         NextLineTBE();  /*DEVO RETORNAR AQUI*/
//         sw(1);        
//         sw(2);
//         sw(3);
//         sw(4);
//         sw(5);
//         sw(6);
//         sw(7);
//         sw(8);
//         sw(9);
//         sw(10);
//         sw(11);
//         sw(12);
//         sw(13);
//         sw(14);
//         sw(15);
//         sw(16);
//         sw(17);
//         sw(18);
//         sw(19);
//         sw(20);
//         sw(21);
//         sw(22);
//         sw(23);
//         sw(24);
//         sw(25);
//         sw(26);
//         sw(27);
//         sw(28);
//         sw(29);
//         sw(30);
//         sw(31);
//         changeOffset(0);
//         lw(1);
//         lw(2);
//         lw(3);
//         lw(4);
//         lw(5);
//         lw(6);
//         lw(7);
//         lw(8);
//         lw(9);
//         lw(10);
//         lw(11);
//         lw(12);
//         lw(13);
//         lw(14);
//         lw(15);
//         lw(16);
//         lw(17);
//         lw(18);
//         lw(19);
//         lw(20);
//         lw(21);
//         lw(22);
//         lw(23);
//         lw(24);
//         lw(25);
//         lw(26);
//         lw(27);
//         lw(28);
//         lw(29);
//         lw(30);
//         lw(31);
//         if(i != 0){
//             i = 0;
//         }
//     }
// }