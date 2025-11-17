#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ANOTAÇÔES:

sizeof(int) -> 4 bytes
sizeof(char) -> 1 byte
sizeof(void *) - > 8 bytes

[0] nomeAux (byte 0 a 99)
[100] idadeAux (byte 100 a 103)
[104] emailAux (byte 104 a 203)
[204] contador (byte 204 a 207)
[208] encontrados (byte 208 a 211)
[212] lista (void*)  <-- ponteiro pra primeira pessoa
[212 + sizeof(void*)] menu (int)

Total: 212 + sizeof(void*) + sizeof(int) bytes

*/

void *criarPessoa(void *nome, void *idade, void *email) {

    void **novo = (void **) malloc(sizeof(void *) * 4);

    novo[0] = malloc(strlen((char *) nome) + 1);
    strcpy((char *) novo[0], (char *) nome);

    novo[1] = malloc(sizeof(int));
    *(int *) novo[1] = *(int *) idade;

    novo[2] = malloc(strlen((char *) email) + 1);
    strcpy((char *) novo[2], (char *) email);

    novo[3] = NULL;

    return novo;
}

void adicionarPessoa(void *pBuffer) {

    char *nomeAux      = (char *) pBuffer;
    int  *idadeAux     = (int  *) ((char *) pBuffer + 100);
    char *emailAux     = (char *) ((char *) pBuffer + 104);
    int  *contador     = (int  *) ((char *) pBuffer + 204);
    int  *encontrados  = (int *) ((char *) pBuffer + 208);
    void ***lista      = (void ***) ((char *) pBuffer + 212);

    printf("\nDigite nome: ");
    fgets(nomeAux, 100, stdin);
    nomeAux[strcspn(nomeAux, "\n")] = 0;

    printf("Digite idade: ");
    scanf("%d", idadeAux);
    getchar();

    printf("Digite email: ");
    fgets(emailAux, 100, stdin);
    emailAux[strcspn(emailAux, "\n")] = 0;

    void **aux = *lista;
    *encontrados = 0;

    while (aux != NULL) {
        if (strcmp((char *) aux[0], nomeAux) == 0) {
            (*encontrados)++;
        }
        aux = aux[3];
    }

    if (*encontrados > 0) {
        printf("Já existe(m) %d pessoa(s) com esse nome. Deseja adicionar mesmo? (1=Sim / 0=Não): ", *encontrados);
        scanf("%d", contador);
        getchar();

        if (*contador == 0) {
            printf("\nCancelando adição.\n");
            return;
        }
    }

    void **novo = criarPessoa(nomeAux, idadeAux, emailAux);
    novo[3] = *lista;
    *lista = novo;

    printf("\nPessoa adicionada.\n");
}

void removerPessoa(void *pBuffer) {

    char *nomeAux   = (char *) pBuffer;
    int  *contador  = (int  *) ((char *)pBuffer + 204);
    int  *encontrados = (int *) ((char *)pBuffer + 208);
    void ***lista   = (void ***) ((char *)pBuffer + 212);

    printf("\nDigite o nome para remover: ");
    fgets(nomeAux, 100, stdin);
    nomeAux[strcspn(nomeAux, "\n")] = 0;


    void **aux = *lista;
    *encontrados = 0;

    while (aux != NULL) {
        if (strcmp((char *)aux[0], nomeAux) == 0) {
            (*encontrados)++;
            printf("[%d] %s | %d | %s\n",
                   *encontrados,
                   (char *)aux[0],
                   *(int *)aux[1],
                   (char *)aux[2]);
        }
        aux = aux[3];
    }

    if (*encontrados == 0) {
        printf("\nNenhuma pessoa encontrada com esse nome.\n");
        return;
    }

    if (*encontrados > 1) {
        printf("Qual deseja remover (1 - %d)? ", *encontrados);
        scanf("%d", contador);
        getchar();

    } else {
        *contador = 1;
    }

    *encontrados = 0;
    aux = *lista;
    void **anterior = NULL;

    while (aux != NULL) {

        if (strcmp((char *)aux[0], nomeAux) == 0) {
            (*encontrados)++;

            if (*encontrados == *contador) {

                if (anterior == NULL)
                    *lista = aux[3];
                else
                    anterior[3] = aux[3];

                free(aux[0]);
                free(aux[1]);
                free(aux[2]);
                free(aux);
                printf("\nRemovido com sucesso.\n");
                return;
            }
        }

        anterior = aux;
        aux = aux[3];
    }
}

void buscarPessoa(void *pBuffer) {

    char *nomeAux = (char *)pBuffer;
    int *encontrados = (int *)((char *)pBuffer + 208);
    void ***lista = (void ***)((char *)pBuffer + 212);

    printf("\nDigite nome para buscar: ");
    fgets(nomeAux, 100, stdin);
    nomeAux[strcspn(nomeAux, "\n")] = 0;

    void **aux = *lista;
    *encontrados = 0;

    while (aux != NULL) {

        if (strcmp((char *)aux[0], nomeAux) == 0) {

            (*encontrados)++;

            printf("--------[%d]--------\n", *encontrados);
            printf("Nome : %s\n", (char *)aux[0]);
            printf("Idade: %d\n", *(int *)aux[1]);
            printf("Email: %s\n", (char *)aux[2]);
            printf("-------------------\n");
        }

        aux = aux[3];
    }

    if (*encontrados == 0)
        printf("\nNenhuma pessoa encontrada com esse nome.\n");
}

void listar(void *pBuffer) {

    void ***lista = (void ***)((char *)pBuffer + 212);
    void **aux = *lista;

    printf("\n====== RECENTES ======\n\n");

    while (aux != NULL) {
        printf("Nome : %s\n", (char *)aux[0]);
        printf("Idade: %d\n", *(int *)aux[1]);
        printf("Email: %s\n", (char *)aux[2]);
        printf("-------------------\n");
        aux = aux[3];
    }
}

int main() {

    void *pBuffer = malloc(212 + sizeof(void *) + sizeof(int));
    void ***lista = (void ***) ((char *)pBuffer + 212);
    *lista = NULL;
    
    int *menu = (int *) ((char *)pBuffer + 212 + sizeof(void *));
    
    while (1) {

        printf("\n1 - Adicionar\n");
        printf("2 - Remover\n");
        printf("3 - Buscar\n");
        printf("4 - Listar\n");
        printf("5 - Sair\n\n");
        printf("Escolha: ");
        scanf("%d", menu);
        getchar();

        if (*menu == 1) adicionarPessoa(pBuffer);
        else if (*menu == 2) removerPessoa(pBuffer);
        else if (*menu == 3) buscarPessoa(pBuffer);
        else if (*menu == 4) listar(pBuffer);
        else if (*menu == 5) break;
        else printf("Opção inválida.\n");
    }

    free(pBuffer);
    return 0;
}
