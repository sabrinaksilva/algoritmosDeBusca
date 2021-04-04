#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COD 11

//Contadores de movimentações e comparações
long int movIns = 0, movQuick = 0, movHeap = 0, movSel = 0, compIns = 0, compQuick = 0, compHeap = 0, compSel = 0;

//função para verificar se abriu o arquivo
void verificarAbertura(FILE *f){
	if(f == NULL){
		printf("Erro na abertura do arquivo.");
		exit(0);
	}
}

typedef struct{
    char cod[COD];
    int mes;
} Operacao;

//Inserção Direta
void DInsertion(Operacao op[], int N){
    int i,j, xM;
    char x[COD];
    for ( i = 2; i < (N+1); i++){
        strcpy(x, op[i].cod);
        xM = op[i].mes;
        movIns++;

        strcpy(op[0].cod, x);
        op[0].mes = xM;
        movIns++;

        j = i;
        compIns++;
        while (strcmp(x, op[j-1].cod) < 0){
        compIns++;
           strcpy(op[j].cod, op[j-1].cod);
           op[j].mes = op[j-1].mes;
           movIns++;

            j =  j - 1 ;
    }
    strcpy(op[j].cod, x);
    op[j].mes = xM;
    movIns++;

    }
}

//Seleção
void selectionSort(Operacao op[], int N){
    int i, j, indiceMenor, mes;
    char cod[COD];
    for (i = 1; i <= N-1; i++){
        indiceMenor = i;
        for (j = i+1; j <= N; j++){
            compSel++;
            if (strcmp(op[j].cod, op[indiceMenor].cod) < 0){
                indiceMenor = j;
            }
        }
        strcpy(cod, op[i].cod);
        mes = op[i].mes;
        movSel++;

        strcpy(op[i].cod, op[indiceMenor].cod);
        op[i].mes = op[indiceMenor].mes;
        movSel++;

        strcpy(op[indiceMenor].cod, cod);
        op[indiceMenor].mes = mes;
        movSel++;
    }
}

//criados do Heap
void heapify(Operacao op[], int esq, int dir){
    int i, j, mes;
    char cod[COD];
    i = esq;
    j = 2*esq;
    strcpy(cod, op[esq].cod);
    mes = op[esq].mes;
    movHeap++;
    compHeap++;
    if((j < dir) && (strcmp(op[j].cod, op[j+1].cod) < 0)){
        j++;
    }
    compHeap++;
    while((j <= dir) && (strcmp(cod, op[j].cod) < 0)){
    compHeap++;
        strcpy(op[i].cod, op[j].cod);
        op[i].mes = op[j].mes;
        movHeap++;

        i = j;
        j = 2*j;
        compHeap++;
        if((j < dir) && (strcmp(op[j].cod, op[j+1].cod) < 0)){
            j++;
        }
    }
    strcpy(op[i].cod, cod);
    op[i].mes = mes;
    movHeap++;
}

//HeapSort
void heapSort(Operacao op[], int N){
    int esq = N/2, dir = N, mes;
    char cod[COD];
    while(esq > 0){
        heapify(op, esq, N);
        esq = esq - 1;
    }
    while(dir > 1){
        strcpy(cod, op[1].cod);
        mes = op[1].mes;
        movHeap++;

        strcpy(op[1].cod, op[dir].cod);
        op[1].mes = op[dir].mes;
        movHeap++;

        strcpy(op[dir].cod, cod);
        op[dir].mes = mes;
        movHeap++;

        heapify(op, 1, (dir-1));

        dir = dir - 1;
    }
}

//QuickSort - função que faz a ordenação propriamente dita
void qSort(Operacao op[], int L, int R){
    int i, j, mes;
    char x[COD],w[COD];
    i = L;
    j = R;
    strncpy(x, op[(L+R)/2].cod, 11);
    mes = op[(L+R)/2].mes;
    movQuick++;

    do{
        compQuick++;
        while (strcmp(op[i].cod, x) < 0){
            compQuick++;
            i = i + 1;
        }
        compQuick++;
        while(strcmp(x, op[j].cod) < 0){
            compQuick++;
            j = j - 1;
        }
        if (i <= j){
            strncpy(w, op[i].cod,11);
            mes = op[i].mes;
            movQuick++;

            strncpy(op[i].cod, op[j].cod,11);
            op[i].mes = op[j].mes;
            movQuick++;

            strncpy(op[j].cod, w,11);
            op[j].mes = mes;
            movQuick++;

            i++;
            j--;
        }

    }while(i <= j);
    if(L < j){
        qSort(op, L, j);
    }
    if(i < R){
        qSort(op, i, R);
    }
}

//Função para inicializar a ordenação do QuickSort
void quickSort(Operacao op[], int N){
    qSort(op,1,N);
}

//precisei fazer varias funções pra chamar uma de cada vez, comentando todas as outras, pois se não os marcadores
//encontrados seriam do melhor caso: o vetor ja estaria ordenado, ou parcialmente ordenado, das chamadas anteriores...
 void imprimeContadores1(Operacao op[], int N, int mes, FILE *arqDestino){
    fprintf(arqDestino, "mes %i:\n", mes);
            fprintf(arqDestino, "Inserção Direta:\nnumeroCodigos;comp;mov\n");
            DInsertion(op, N/8);
            fprintf(arqDestino, "%i,%i,%i,\n", N/8, compIns, movIns);
            compIns = 0; movIns = 0;
    }
void imprimeContadores2(Operacao op[], int N, int mes, FILE *arqDestino){
            DInsertion(op, N/6);
            fprintf(arqDestino, "%i,%i,%i,\n", N/6, compIns, movIns);
            compIns = 0; movIns = 0;
}

void imprimeContadores3(Operacao op[], int N, int mes, FILE *arqDestino){
            DInsertion(op, N/4);
            fprintf(arqDestino, "%i,%i,%i,\n", N/4, compIns, movIns);
            compIns = 0; movIns = 0;
}
void imprimeContadores4(Operacao op[], int N, int mes, FILE *arqDestino){
            DInsertion(op, N/2);
            fprintf(arqDestino, "%i,%i,%i,\n", N/2, compIns, movIns);
            compIns = 0; movIns = 0;
}

void imprimeContadores5(Operacao op[], int N, int mes, FILE *arqDestino){
            DInsertion(op, N);
            fprintf(arqDestino, "%i,%i,%i\n\n", N, compIns, movIns);
}
void imprimeContadores6(Operacao op[], int N, int mes, FILE *arqDestino){
            fprintf(arqDestino, "Selection Sort:\nnumeroCodigos;comp;mov\n");
            selectionSort(op, N/8);
            fprintf(arqDestino, "%i,%i,%i,\n", N/8, compSel, movSel);
            compSel = 0; movSel = 0;
}

void imprimeContadores7(Operacao op[], int N, int mes, FILE *arqDestino){
            selectionSort(op, N/6);
            fprintf(arqDestino, "%i,%i,%i,\n", N/6, compSel, movSel);
            compSel = 0; movSel = 0;
}

void imprimeContadores8(Operacao op[], int N, int mes, FILE *arqDestino){
            selectionSort(op, N/4);
            fprintf(arqDestino, "%i,%i,%i,\n", N/4, compSel, movSel);
            compSel = 0; movSel = 0;
}

void imprimeContadores9(Operacao op[], int N, int mes, FILE *arqDestino){
            selectionSort(op, N/2);
            fprintf(arqDestino, "%i,%i,%i,\n", N/2, compSel, movSel);
            compSel = 0; movSel = 0;

}
void imprimeContadores10(Operacao op[], int N, int mes, FILE *arqDestino){
            selectionSort(op, N);
            fprintf(arqDestino, "%i,%i,%i\n\n", N, compSel, movSel);
}
void imprimeContadores11(Operacao op[], int N, int mes, FILE *arqDestino){
            fprintf(arqDestino, "HeapSort:\nnumeroCodigos;comp;mov\n");
            heapSort(op, N/8);
            fprintf(arqDestino, "%i,%i,%i,\n", N/8, compHeap, movHeap);
            compHeap = 0; movHeap = 0;
}
void imprimeContadores12(Operacao op[], int N, int mes, FILE *arqDestino){
            heapSort(op, N/6);
            fprintf(arqDestino, "%i,%i,%i,\n", N/6, compHeap, movHeap);
            compHeap = 0; movHeap = 0;
}

void imprimeContadores13(Operacao op[], int N, int mes, FILE *arqDestino){
            heapSort(op, N/4);
            fprintf(arqDestino, "%i,%i,%i,\n", N/4, compHeap, movHeap);
            compHeap = 0; movHeap = 0;
}

void imprimeContadores14(Operacao op[], int N, int mes, FILE *arqDestino){
            heapSort(op, N/2);
            fprintf(arqDestino, "%i,%i,%i,\n", N/2, compHeap, movHeap);
            compHeap = 0; movHeap = 0;
}

void imprimeContadores15(Operacao op[], int N, int mes, FILE *arqDestino){
            heapSort(op, N);
            fprintf(arqDestino, "%i,%i,%i\n\n", N, compHeap, movHeap);
            compHeap = 0; movHeap = 0;
}
void imprimeContadores16(Operacao op[], int N, int mes, FILE *arqDestino){
            fprintf(arqDestino, "QuickSort:\nnumeroCodigos;comp;mov\n");
            quickSort(op, N/8);
            fprintf(arqDestino, "%i,%i,%i,\n", N/8, compQuick, movQuick);
            compQuick = 0; movQuick = 0;
}

void imprimeContadores17(Operacao op[], int N, int mes, FILE *arqDestino){
            quickSort(op, N/6);
            fprintf(arqDestino, "%i,%i,%i,\n", N/6, compQuick, movQuick);
            compQuick = 0; movQuick = 0;
}

void imprimeContadores18(Operacao op[], int N, int mes, FILE *arqDestino){
            quickSort(op, N/4);
            fprintf(arqDestino, "%i,%i,%i,\n", N/4, compQuick, movQuick);
            compQuick = 0; movQuick = 0;
}
void imprimeContadores19(Operacao op[], int N, int mes, FILE *arqDestino){
            quickSort(op, N/2);
            fprintf(arqDestino, "%i,%i,%i,\n", N/2, compQuick, movQuick);
            compQuick = 0; movQuick = 0;
}
void imprimeContadores20(Operacao op[], int N, int mes, FILE *arqDestino){
            quickSort(op, N);
            fprintf(arqDestino, "%i,%i,%i\n\n\n\n", N, compQuick, movQuick);
 }
int main(){
	FILE *mes1, *mes2, *mes3, *mes4, *mes5;
  int i, j, k;
  char linha[COD];
  Operacao o[16601], op1[101], op2[501], op3[1001], op4[5001], op5[10001]; //ao total tem-se 16600 operacoes em todos os arquivos


  mes1 = fopen("mes_1.txt", "r");
  verificarAbertura(mes1);
  mes2 = fopen("mes_2.txt", "r");
  verificarAbertura(mes2);
  mes3 = fopen("mes_3.txt", "r");
  verificarAbertura(mes3);
  mes4 = fopen("mes_4.txt", "r");
  verificarAbertura(mes4);
  mes5 = fopen("mes_5.txt", "r");
  verificarAbertura(mes5);

  /*IMPORTANTE: LEMBRE DE COMEÇAR TODOS OS J EM 1, PARA QUE A SELEÇÃO FUNCIONE. TODOS OS OUTROS MÉTODOS DEVERÃO
  CONSIDERAR QUE O VETOR COMEÇA EM 1 E TERMINA EM 16600*/


  //o i e o j são necessários pra separar uma "linha válida" de uma "vazia", que o fgets tava achando
  i = 0;
  j = 1;
  while (fgets(linha, 11, mes1)){
    if (i % 2 == 0){
      strcpy(op1[j].cod, strtok(linha, "\n")); //strtok pra tirar o \n do final da linha lida
      op1[j].mes = 1; //printf("%i ", j);
      j++;
    }
    i++;
  }
  i = 0;
  j = 1;
  while (fgets(linha, 11, mes2)){
    if (i % 2 == 0){
      //k = j + 100;
      strcpy(op2[j].cod, strtok(linha, "\n"));//printf("%i ", j);
      op2[j].mes = 2;
      j++;
    }
    i++;
  }

  i = 0;
  j = 1;
  while (fgets(linha, 11, mes3)){
    if (i % 2 == 0){
      //k = j + 100 + 500;
      strcpy(op3[j].cod, strtok(linha, "\n"));//printf("%i ", j);
      op3[j].mes = 3;
      j++;
    }
    i++;
  }

  i = 0;
  j = 1;
  while (fgets(linha, 11, mes4)){
    if (i % 2 == 0){
      k = j + 100 + 500 + 1000;
      strcpy(op4[j].cod, strtok(linha, "\n"));//printf("%i ", j);
      op4[j].mes = 4;
      j++;
    }
    i++;
  }

  i = 0;
  j = 1;
  while (fgets(linha, 11, mes5)){
    if (i % 2 == 0){
      k = j + 100 + 500 + 1000 + 5000;
      strcpy(op5[j].cod, strtok(linha, "\n"));//printf("%i ", j);
      op5[j].mes = 5;
      j++;
    }
    i++;
  }

  //DInsertion(op5, 10000);
  //selectionSort(op5, 10000);
  //heapSort(op5, 10000);
   //quickSort(op5, 10000);

    // Colocando o total de movimentações e comparações por mês em um txt:
    FILE *compMov = fopen("compMov.txt", "a");
    verificarAbertura(compMov);
    //imprimeContadores1(op1, 100, 1, compMov);
    //imprimeContadores2(op1, 100, 1, compMov);
    //imprimeContadores3(op1, 100, 1, compMov);
    //imprimeContadores4(op1, 100, 1, compMov);
    //imprimeContadores5(op1, 100, 1, compMov);
    //imprimeContadores6(op1, 100, 1, compMov);
    //imprimeContadores7(op1, 100, 1, compMov);
    //imprimeContadores8(op1, 100, 1, compMov);
    //imprimeContadores9(op1, 100, 1, compMov);
    //imprimeContadores10(op1, 100, 1, compMov);
    //imprimeContadores11(op1, 100, 1, compMov);
    //imprimeContadores12(op1, 100, 1, compMov);
    //imprimeContadores13(op1, 100, 1, compMov);
    //imprimeContadores14(op1, 100, 1, compMov);
    //imprimeContadores15(op1, 100, 1, compMov);
    //imprimeContadores16(op1, 100, 1, compMov);
    //imprimeContadores17(op1, 100, 1, compMov);
    //imprimeContadores18(op1, 100, 1, compMov);
    //imprimeContadores19(op1, 100, 1, compMov);
   //imprimeContadores20(op1, 100, 1, compMov);


   // imprimeContadores1(op2, 500, 2, compMov);
   //imprimeContadores2(op2, 500, 2, compMov);
    //imprimeContadores3(op2, 500, 2, compMov);
   // imprimeContadores4(op2, 500, 2, compMov);
   // imprimeContadores5(op2, 500, 2, compMov);
   // imprimeContadores6(op2, 500, 2, compMov);
   // imprimeContadores7(op2, 500, 2, compMov);
   // imprimeContadores8(op2, 500, 2, compMov);
   // imprimeContadores9(op2, 500, 2, compMov);
   // imprimeContadores10(op2, 500, 2, compMov);
   // imprimeContadores11(op2, 500, 2, compMov);
   // imprimeContadores12(op2, 500, 2, compMov);
    //imprimeContadores13(op2, 500, 2, compMov);
  //  imprimeContadores14(op2, 500, 2, compMov);
  //imprimeContadores15(op2, 500, 2, compMov);
  //imprimeContadores16(op2, 500, 2, compMov);
   //imprimeContadores17(op2, 500, 2, compMov);
   //imprimeContadores18(op2, 500, 2, compMov);
   //imprimeContadores19(op2, 500, 2, compMov);
    //imprimeContadores20(op2, 500, 2, compMov);



    //imprimeContadores1(op3, 1000, 3, compMov);
    //imprimeContadores2(op3, 1000, 3, compMov);
    //imprimeContadores3(op3, 1000, 3, compMov);
    //imprimeContadores4(op3, 1000, 3, compMov);
    //imprimeContadores5(op3, 1000, 3, compMov);
    //imprimeContadores6(op3, 1000, 3, compMov);
    //imprimeContadores7(op3, 1000, 3, compMov);
    //imprimeContadores8(op3, 1000, 3, compMov);
    //imprimeContadores9(op3, 1000, 3, compMov);
    //imprimeContadores10(op3, 1000, 3, compMov);
    //imprimeContadores11(op3, 1000, 3, compMov);
    //imprimeContadores12(op3, 1000, 3, compMov);
    //imprimeContadores13(op3, 1000, 3, compMov);
    //imprimeContadores14(op3, 1000, 3, compMov);
    //imprimeContadores15(op3, 1000, 3, compMov);
    //imprimeContadores16(op3, 1000, 3, compMov);
    //imprimeContadores17(op3, 1000, 3, compMov);
    //imprimeContadores18(op3, 1000, 3, compMov);
    //imprimeContadores19(op3, 1000, 3, compMov);
    //imprimeContadores20(op3, 1000, 3, compMov);




    //imprimeContadores1(op4, 5000, 4, compMov);
    //imprimeContadores2(op4, 5000, 4, compMov);
    //imprimeContadores3(op4, 5000, 4, compMov);
    //imprimeContadores4(op4, 5000, 4, compMov);
    //imprimeContadores5(op4, 5000, 4, compMov);
    //imprimeContadores6(op4, 5000, 4, compMov);
    //imprimeContadores7(op4, 5000, 4, compMov);
    //imprimeContadores8(op4, 5000, 4, compMov);
    //imprimeContadores9(op4, 5000, 4, compMov);
    //imprimeContadores10(op4, 5000, 4, compMov);
    //imprimeContadores11(op4, 5000, 4, compMov);
    //imprimeContadores12(op4, 5000, 4, compMov);
    //imprimeContadores13(op4, 5000, 4, compMov);
    //imprimeContadores14(op4, 5000, 4, compMov);
    //imprimeContadores15(op4, 5000, 4, compMov);
    //imprimeContadores16(op4, 5000, 4, compMov);
    //imprimeContadores17(op4, 5000, 4, compMov);
    //imprimeContadores18(op4, 5000, 4, compMov);
    //imprimeContadores19(op4, 5000, 4, compMov);
    //imprimeContadores20(op4, 5000, 4, compMov);



    //imprimeContadores1(op5, 10000, 5, compMov);
    //imprimeContadores2(op5, 10000, 5, compMov);
    //imprimeContadores3(op5, 10000, 5, compMov);
    //imprimeContadores4(op5, 10000, 5, compMov);
    //imprimeContadores5(op5, 10000, 5, compMov);
    //imprimeContadores6(op5, 10000, 5, compMov);
    //imprimeContadores7(op5, 10000, 5, compMov);
    //imprimeContadores8(op5, 10000, 5, compMov);
    //imprimeContadores9(op5, 10000, 5, compMov);
    //imprimeContadores10(op5, 10000, 5, compMov);
    //imprimeContadores11(op5, 10000, 5, compMov);
    //imprimeContadores12(op5, 10000, 5, compMov);
    //imprimeContadores13(op5, 10000, 5, compMov);
    //imprimeContadores14(op5, 10000, 5, compMov);
    //imprimeContadores15(op5, 10000, 5, compMov);
    //imprimeContadores16(op5, 10000, 5, compMov);
    //imprimeContadores17(op5, 10000, 5, compMov);
    //imprimeContadores18(op5, 10000, 5, compMov);
    //imprimeContadores19(op5, 10000, 5, compMov);
    //imprimeContadores20(op5, 10000, 5, compMov);

    //fprintf(compMov, "Metodo: QuickSort\nmes;comp;mov;\n");
    //fprintf(compMov, "5;%i;%i;\n", compQuick, movQuick);
    fclose(compMov);

    heapSort(op5, 10000);
    for(i = 0; i < 100; i++){
        printf("%s\n", op5[i].cod);
    }
}
