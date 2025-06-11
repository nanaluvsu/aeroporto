#include "grafo.c"
#include <stdio.h>
#include <locale.h>


void
clear (void)
{
    while ( getchar() != '\n' );
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Grafo *grafo = criar_grafo();
    printf("Estrutura e Recuperacao de Dados II\nTrabalho de Grafos.\n\n");
    adicionar_node(grafo, "GRU", "Sao Paulo");      // adicionando aeroportos eba(esse é de SP)
    adicionar_node(grafo, "GIG", "Rio de Janeiro"); // RJ
    adicionar_node(grafo, "BSB", "Brasilia");       // Brasilia
    adicionar_node(grafo, "SSA", "Salvador");       // Salvador
    adicionar_node(grafo, "CNF", "Belo Horizonte"); // Belo Horizonte
    Relacionamento relSPRJ = {1,"GRU","GIG"};
    adicionar_rel(grafo, relSPRJ);
    Relacionamento relRJBH = {2,"GIG","CNF"};
    adicionar_rel(grafo, relRJBH);
    Relacionamento relSPBR = {3,"GRU","BSB"};
    adicionar_rel(grafo, relSPBR);
    Relacionamento relBRSV = {4,"BSB","SSA"};
    adicionar_rel(grafo, relBRSV);
    Relacionamento relSPBH = {5,"GRU","CNF"};
    adicionar_rel(grafo, relSPBH);
    Relacionamento relSVBH = {6,"SSA","CNF"};
    adicionar_rel(grafo, relSVBH);

    int op;
    do
    {
        printf("\n---------------------------------\n");
        printf("\nEscolha uma opcao:\n");
        printf("[1] Registrar novo aeroporto;\n");
        printf("[2] Registrar novo voo entre aeroportos;\n");
        printf("[3] Remover voo;\n");
        printf("[4] Listar voos que partem de um aeroporto;\n");
        printf("[5] Listar possiveis trajetos que passam por um aeroporto;\n");
        printf("[0] Sair.\n");
        printf("Opcao: ");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("Registro de aeroporto\n\n");
            char sigla[4];
            char estado[50];
            printf("Digite a sigla do aeroporto: ");
            scanf("%s", sigla);
            printf("\nDigite o estado do aeroporto(pode ser abreviacao. Exemplo: Sao Paulo -> SP): ");
            scanf("%s", estado);

            if (adicionar_node(grafo, sigla, estado))
            {
                printf("eba :3 ta tendo %s \n", sigla);
                listaAeroportos(grafo);
            }
            else
            {
                printf("Deu erro :c\n");
            }
            break;
        case 2:
            printf("Registro de voo\n\n");
            U32 id, origem, destino;
            printf("Digite o codigo do voo: ");
            scanf("%u", &id);
            printf("Digite a sigla do aeroporto de origem: ");
            scanf("%s", &origem);
            printf("Digite a sigla do aeroporto de destino: ");
            scanf("%s", &destino);
            Relacionamento rel = {id, origem, destino};
            if (adicionar_rel(grafo, rel))
            {
                printf("ta tendo :3\n");
            }
            else
            {
                printf("noggers\n");
            }
            break;
        case 3:
        printf("Remoção de voo\n\n");
            char sigRemo[4];
            printf("Digite a sigla do voo a ser removido: ");
            scanf("%s", &sigRemo);
            Relacionamento remover = cade(grafo, sigRemo);
            if (remover.id != 0)
            {
                if (remover_rel(grafo, remover))
                {
                    printf("comi :3\n");
                }
                else
                {
                    printf("explodiu\n");
                }
            }
            else
            {
                printf("nao ta tendo\n");
            }

            // printf("Remocao de voo não implementada\n\n"); // ta implementada eu so fui burra nao consegui fazer funcionar(provavelmente o do augusto vai dar certo espero)
            break;
        case 4:
            printf("Listar voos que partem de um aeroporto\n\n");
            char origem1[4];
            printf("Digite a sigla do aeroporto de origem: ");
            scanf("%s", &origem1);
            if (!busca_og(grafo, origem1)) 
            {
                printf("Nenhum voo encontrado com origem no aeroporto especificado.\n");
            }
            break;
        case 5: 
            printf("Busca de trajeto\n\n");
            char origem2[4];
            char destino1[4];
            printf("Digite a sigla do aeroporto de origem: ");
            scanf("%s", &origem2);
            printf("Digite a sigla do aeroporto de destino: ");
            scanf("%s", &destino1);
            char* path = malloc(grafo->qtd_nodes * sizeof(char*)); // Talvez seja memoria demais(?)
            U32 lenVis = 0; // Tamanho do caminho
            U32* mapVis = malloc(grafo->qtd_nodes * sizeof(U32)); 

            if (!busca_trajeto(grafo, origem2, destino1, path, &lenVis, mapVis))
            {
                printf("Nenhum trajeto encontrado entre os aeroportos especificados.\n");
            }
            break;
        case 0:
            printf("tchau :(\n");
            removerGrafo(grafo);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 0);

    removerGrafo(grafo);
    return 0;
}
