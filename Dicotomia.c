#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Dicas:
        Potencia: pow(base, expoente)
        Arredondar para cima: ceil(valor)
        Modulo/ValorAbsoluto: fabs(valor)
*/

// Prototipo das funcoes. Ajustar para passagem por referência
// Criar funcao para calcular a DICOTOMIA
float CalculaValorK(float a, float b, float erro);
float funcaoX(float ponto);
float calcM(float a, float b);
void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB, float modFm);
void fecharTabela();
void pausar();

int grau;
float *multi = NULL; // Indice 0 a 6
/*
PONTEIROS - DICAS

//Criar uma variavel tipo ponteiro
float *myVar = NULL;

//Alocacao do tamanho solicitado (grau indicado)
myVar = (float *)malloc(tamanho * sizeof(float));

//Dentro do for para receber os valores
scanf("%f", myVar+i);

//Acessando os valores do vetor
//*(myVar+i)

//Liberando a memoria
//free(myVar);
*/

int main()
{
    int i;

    // printf("%-9i|%8i\n", 19, 12);

    printf("Informe o grau da funcao: ");
    scanf("%i", &grau);

    multi = malloc(grau * sizeof(float));

    // Receber os multiplicadores. Dica: Armazenar os valores em um vetor.
    // aX^0 + bX^1 + cX^2 --->Indice do vetor igual ao expoente
    for (i = grau; i >= 0; i--)
    {
        printf("Informe o fator multiplicador de x^%i(%c): ", i, 65 + (grau - i));
        scanf("%f", &multi[i]);
        getchar();
    }

    // Exibindo a funcao recebida
    printf("\nA funcao recebida foi: ");
    for (i = grau; i >= 0; i--)
    {
        if (i == 0)
            printf("%.2f = 0", multi[i]);
        else
            printf("%.2fx^%i + ", multi[i], i);
    }

    pausar();

    // Receber os valores de
    // a, b, erro
    float a, b, erro;

    printf("Informe o intervalo A: ");
    scanf("%f", &a);

    printf("Informe o intervalo B: ");
    scanf("%f", &b);

    printf("Informe o erro: ");
    scanf("%f", &erro);
    getchar();

    // Verificar se no intervalo [A, B] existe zero de funcao
    int verificarIntervalo = funcaoX(a) * funcaoX(b) > 0;

    if (verificarIntervalo)
    {
        printf("\nFunção de zero não existe no intervalo [%.2f, %.2f].", a, b);
        free(multi);
        return 0;
    }
    
    // Calcular valor de K
    float valorK = CalculaValorK(a, b, erro);

    printf("\nValor de K: %.2f", valorK);

    pausar();

    // Exibindo o cabecalho
    ImprimirCabecalhoTabela();

    // while (I <= K ... e os outros critérios de parada solicitados)
    //{
    int I;
    while (I <= valorK)
    {
        float m, fA, fB, fM, modFm;
        char multFma, multFmb;

        m = calcM(a,b);

        fA = funcaoX(a);
        fB = funcaoX(b);
        fM = funcaoX(m);

        multFma = fM * fA > 0 ? '+' : '-';
        
        multFmb = fM * fB > 0 ? '+' : '-';

        modFm = fabs(fM);

        ImprimirTabela(I, a, b, m, fA, fB, fM, multFma, multFmb, modFm);

        if (modFm <= erro)
        {
            break;
        }  

        if (multFma == '+')
        {
            a = m;
        } else if (multFmb == '+')
        {
            b = m;
        }

        I++;
    }

    fecharTabela();

    pausar();

    free(multi);
}

// Realiza o calculo do K (numero de passo)
float CalculaValorK(float a, float b, float erro)
{
    float fValorK;

    // Realizar o calculo do valor do K
    fValorK = (log10(b - a) - log10(erro)) / (log10(2));

    return ceil(fValorK);
}

// Funcao que realiza o calculo em em determinado ponto
float funcaoX(float ponto)
{
    int i;
    float resultado;
    resultado = 0;

    for (i = 0; i <= grau; i++)
    {
        resultado = resultado + multi[i] * pow(ponto, i);
    }

    return resultado;
}

float calcM(float a, float b) {
    return (a + b) / 2;
}

// Imprimindo o cabecalho
void ImprimirCabecalhoTabela()
{
    /*
    //Impressao do cabecalho
    printf("I |  a\t|  b\t|  m\t|  f(a)\t|  f(b)\t|  f(m)\t| fa*fm\t| fm*fb\t|\n");
    printf("--+-----+-------+-------+-------+-------+-------+-------+-------+\n");
    */
    // Impressao do cabecalho
    printf("I |\ta\t|\tb\t|\tm\t|\tf(a)\t|\tf(b)\t|\tf(m)\t|fa*fm\t|fm*fb\t|    |fm|    \t|\n");
    printf("--+-------------+---------------+---------------+---------------+---------------+---------------+-------+-------+---------------+\n");
}

void fecharTabela() {
    printf("--+-------------+---------------+---------------+---------------+---------------+---------------+-------+-------+---------------+\n");
}

// Imprimindo a tabela com os valores
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB, float modFm)
{
    // printf("%i |%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
    printf("%i |%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%c\t|%c\t|%.5f\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB, modFm);
}

void pausar() {
    printf("\n\n");
    printf("Pressione ENTER para continuar...");
    getchar();
    printf("\n\n");
}