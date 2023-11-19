#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CASOS_DE_TESTE 5
int tamanhos[] = {1000, 10000, 25000, 50000, 75000};

enum Algoritmo {
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    MERGE_SORT,
    QUICK_SORT,
    TAM_ALGORITMOS
};

int* gerarArrayAleatorio(int tamanho) {
    int* array = (int*)malloc(tamanho * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; i++) {
        array[i] = rand();  // Preenche o array com números inteiros aleatórios
    }

    return array;
}

// Função para trocar dois elementos do array
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        // Últimos i elementos já estão ordenados, então não precisamos considerá-los
        for (int j = 0; j < n-i-1; j++) {
            // Troca se o elemento encontrado for maior que o próximo elemento
            if (arr[j] > arr[j+1]) {
                trocar(&arr[j], &arr[j+1]);
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, indiceMinimo;

    // Percorre o array
    for (i = 0; i < n-1; i++) {
        // Encontra o índice do elemento mínimo no subarray não ordenado
        indiceMinimo = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[indiceMinimo])
                indiceMinimo = j;

        // Troca o elemento mínimo encontrado com o primeiro elemento não ordenado
        trocar(&arr[indiceMinimo], &arr[i]);
    }
}

void insertionSort(int arr[], int n) {
    int i, chave, j;
    
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;

        // Move os elementos do arr[0..i-1] que são maiores que a chave para uma posição à frente
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

void intercalar(int arr[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int* subArrayEsquerdo = (int*)malloc(n1 * sizeof(int));
    int* subArrayDireito = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) {
        subArrayEsquerdo[i] = arr[inicio + i];
    }
    for (j = 0; j < n2; j++) {
        subArrayDireito[j] = arr[meio + 1 + j];
    }

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (subArrayEsquerdo[i] <= subArrayDireito[j]) {
            arr[k] = subArrayEsquerdo[i];
            i++;
        } else {
            arr[k] = subArrayDireito[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = subArrayEsquerdo[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = subArrayDireito[j];
        j++;
        k++;
    }

    free(subArrayEsquerdo);
    free(subArrayDireito);
}

void mergeSort(int arr[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);
        intercalar(arr, inicio, meio, fim);
    }
}

// Função para encontrar o pivô e colocá-lo na posição correta
int particionar(int array[], int baixo, int alto) {
    int pivô = array[alto]; // escolha o último elemento como pivô
    int i = (baixo - 1); // índice do menor elemento

    for (int j = baixo; j <= alto - 1; j++) {
        // se o elemento atual é menor ou igual ao pivô
        if (array[j] <= pivô) {
            i++;
            // troca array[i] e array[j]
            trocar(&array[i], &array[j]);
        }
    }

    // troca array[i + 1] e array[alto] (pivô)
    trocar(&array[i + 1], &array[alto]);
    return (i + 1);
}

void quickSort(int array[], int baixo, int alto) {
    if (baixo < alto) {
        // encontra o índice do pivô, array[p]
        int p = particionar(array, baixo, alto);

        // separadamente ordena os elementos antes e depois do pivô
        quickSort(array, baixo, p - 1);
        quickSort(array, p + 1, alto);
    }
}
int *copiar_array(int *array, int tamanho) {
    int *copia = (int *)malloc(tamanho * sizeof(int));
    if (copia == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; i++) {
        copia[i] = array[i];
    }

    return copia;
}

int main() {
    // Inicializa o gerador de números aleatórios com uma semente baseada no tempo
    srand((unsigned int)time(NULL));

    int **arrays = (int**)malloc(CASOS_DE_TESTE * sizeof(int*));

    for (int i = 0; i < CASOS_DE_TESTE; i++) {
        int tamanho = tamanhos[i];
        arrays[i] = gerarArrayAleatorio(tamanho);
    }

    for (int i = 0; i < TAM_ALGORITMOS; i++) {
        switch (i) {
            case BUBBLE_SORT:
                printf("Bubble Sort\n");
                for (int j = 0; j < CASOS_DE_TESTE; j++) {
                    int *arr_copia = copiar_array(arrays[j], tamanhos[j]);

                    // Registre o tempo inicial
                    clock_t inicio = clock();
                    bubbleSort(arr_copia, tamanhos[j]);

                    // Registre o tempo final
                    clock_t fim = clock();

                    // Calcule o tempo decorrido
                    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    printf("\tTamanho: %d\t\tTempo: %lf\n", tamanhos[j], tempoDecorrido);

                    free(arr_copia);
                }
                
                break;
            case SELECTION_SORT:
                printf("Selection Sort\n");
                for (int j = 0; j < CASOS_DE_TESTE; j++) {
                    int *arr_copia = copiar_array(arrays[j], tamanhos[j]);

                    // Registre o tempo inicial
                    clock_t inicio = clock();
                    selectionSort(arr_copia, tamanhos[j]);

                    // Registre o tempo final
                    clock_t fim = clock();

                    // Calcule o tempo decorrido
                    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    printf("\tTamanho: %d\t\tTempo: %lf\n", tamanhos[j], tempoDecorrido);

                    free(arr_copia);
                }
                break;
            case INSERTION_SORT:
                printf("Insertion Sort\n");
                for (int j = 0; j < CASOS_DE_TESTE; j++) {
                    int *arr_copia = copiar_array(arrays[j], tamanhos[j]);

                    // Registre o tempo inicial
                    clock_t inicio = clock();
                    insertionSort(arr_copia, tamanhos[j]);

                    // Registre o tempo final
                    clock_t fim = clock();

                    // Calcule o tempo decorrido
                    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    printf("\tTamanho: %d\t\tTempo: %lf\n", tamanhos[j], tempoDecorrido);

                    free(arr_copia);
                }
                break;
            case MERGE_SORT:
                printf("Merge Sort\n");
                for (int j = 0; j < CASOS_DE_TESTE; j++) {
                    int *arr_copia = copiar_array(arrays[j], tamanhos[j]);

                    // Registre o tempo inicial
                    clock_t inicio = clock();
                    mergeSort(arr_copia, 0, tamanhos[j] - 1);

                    // Registre o tempo final
                    clock_t fim = clock();

                    // Calcule o tempo decorrido
                    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    printf("\tTamanho: %d\t\tTempo: %lf\n", tamanhos[j], tempoDecorrido);

                    free(arr_copia);
                }
                
                break;
            case QUICK_SORT:
                printf("Quick Sort\n");
                for (int j = 0; j < CASOS_DE_TESTE; j++) {
                    int *arr_copia = copiar_array(arrays[j], tamanhos[j]);

                    // Registre o tempo inicial
                    clock_t inicio = clock();
                    quickSort(arr_copia, 0, tamanhos[j] - 1);

                    // Registre o tempo final
                    clock_t fim = clock();

                    // Calcule o tempo decorrido
                    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    printf("\tTamanho: %d\t\tTempo: %lf\n", tamanhos[j], tempoDecorrido);

                    free(arr_copia);
                }
                break;
        }
    }


    for (int i = 0; i < CASOS_DE_TESTE; i++) {
        free(arrays[i]);
    }
    free(arrays);

    return 0;
}