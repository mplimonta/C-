/*
int gcd (int u, int v)
{       
	if (v == 0) return u ;
	else return gcd(v,u-u/v*v);
}

void main(void)
{	int x; int y;
	x = input();
    y = input();
	output(gcd(x,y));
}
*/
/*
int fib(int n)
{
    int a; int b; int c; int i;
    a = 0;
    b = 1;
    i = 2; 
    if (n == 0) {
        return a;
    } while (i <= n) {
        c = a + b;
        a = b;
        b = c;
        i = i + 1;
    }
    return b;
}


void main(void)
{
    int n;
    n = input();
    output(fib(n));
}
*/
/*
int EhPrimo(int n) {
    int i;
    i = 5;
    if (n <= 1){
        return 0;
    } 
    if (n <= 3) {
        return 1;
    }
    if (n/2*2 == n){
        return 0;
    }
    if (n/3*3 == n){
        return 0;
    }
    while (i * i <= n) {
        if (n/i*i == n){
            return 0;
        } 
        if(n/(i + 2)*(i + 2) == n){
            return 0;
        }
        i = i + 6;
    }
    return 1;
}

void main(void) {
    int num;
    num = input();
    output(EhPrimo(num));
}
*/
/*
int Fatorial(int n) {
    int result;
    result = 1;
    while (n != 1){
        result = result * n;
        n = n - 1;
    }
    return result;
}

void main(void) {
    int num;
    num = input();
    output(Fatorial(num));
}
*/
/*
int Triangulo(int a, int b, int c) {
    if (a + b > c){
        if(a + c > b){
            if(b + c > a){
               return 1; 
            }
        }
    }
    return 0;
}

void main(void) {
    int a;
    int b; 
    int c;
    a = input();
    b = input();
    c = input();
    output(Triangulo(a,b,c));
}
*/
/*
int ehPalindromo(int n) {
    int reverso;
    int original;
    int digito;
    int temp;
    reverso = 0;
    original = n;
    while (n != 0) {
        temp = n;
        digito = 0;
        while (temp >= 10) {
            temp = temp - 10;
            digito = digito + 1;
        }
        reverso = reverso * 10 + digito;
        n = n / 10;
    }

    if (original == reverso) {
        return 1;
    } else {
        return 0;
    }
}

void main(void) {
    int num;
    num = input();
    output(ehPalindromo(num));
}
*/
/*
void main(void) {
    int a;
    int b;
    int c;
    int media;
    a = input();
    b = input();
    c = input();
    media = (a + b + c) / 3;
    output(media);
}
*/
/*
void main(void) {
    int comprimento;
    int largura;
    int area;
    comprimento = input();
    largura = input();
    area = comprimento * largura;
    output(area);
}
*/
/*
void main(void) {
    int a;
    int b;
    int c;
    int d;
    int e;
    int resultado;
    resultado = 0;
    a = input();
    b = input();
    c = input();
    d = input();
    e = input();
    if (resultado < a){
        resultado = a;
    }
    if (resultado < b){
        resultado = b;
    }
    if (resultado < c){
        resultado = c;
    }
    if (resultado < d){
        resultado = d;
    }
    if (resultado < e){
        resultado = e;
    }
    output(resultado);
}
*/
/*
int potencia(int base, int expoente) {
    int i;
    int resultado;
    resultado = 1;

    i = 0;
    while (i < expoente) {
        resultado = resultado * base;
        i = i + 1;
    }
    return resultado;
}

void main(void) {
    int base;
    int exp;
    int res;

    base = input();
    exp = input();

    res = potencia(base, exp);

    output(res);
}
*/