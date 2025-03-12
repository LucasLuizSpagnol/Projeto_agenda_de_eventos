// UFFS Agenda

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _data {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};

typedef struct _data Data;

struct _evento {
    int codigo;
    Data dataEvento;
    float duracao;
    char descricao[100];
    struct _evento *proximo;
};

typedef struct _evento Evento;

Evento* criarEvento(int codigo, Data data, float duracao, const char* descricao) {
    Evento* novoEvento = (Evento*) malloc(sizeof(Evento));
    if (novoEvento == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    novoEvento->codigo = codigo;
    novoEvento->dataEvento = data;
    novoEvento->duracao = duracao;
    strcpy(novoEvento->descricao, descricao);
    novoEvento->proximo = NULL;

    return novoEvento;
}

void inserirFim(Evento** lista, Evento* novoEvento) {
    Evento* aux = *lista;

    if (*lista == NULL) {
        *lista = novoEvento;
    }
	else {
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novoEvento;
    }
}

void consultarEventos(Evento* lista) {
    int opcao;
    printf("Escolha a opcao de consulta:\n");
    printf("1. Consultar por data\n");
    printf("2. Consultar por data e hora\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int dia, mes, ano;
        printf("\nDigite o dia: ");
        scanf("%d", &dia);
        printf("Digite o mes: ");
        scanf("%d", &mes);
        printf("Digite o ano: ");
        scanf("%d", &ano);

        Evento* aux = lista;
        int encontrouEvento = 0;

        while (aux != NULL) {
            if (aux->dataEvento.dia == dia &&
                aux->dataEvento.mes == mes &&
                aux->dataEvento.ano == ano) {
                // Evento encontrado para a data
                printf("Codigo: %d\n", aux->codigo);
                printf("Data: %02d/%02d/%04d as %02d:%02d\n", 
                       aux->dataEvento.dia,
                       aux->dataEvento.mes,
                       aux->dataEvento.ano,
                       aux->dataEvento.hora,
                       aux->dataEvento.minuto);
                printf("Duracao: %.2f horas\n", aux->duracao);
                printf("Descricao: %s\n", aux->descricao);
                encontrouEvento = 1;
            }
            aux = aux->proximo;
        }
        if (!encontrouEvento) {
            printf("Nenhum compromisso encontrado para esta data.\n");
        }

    } else if (opcao == 2) {
        int dia, mes, ano, hora, minuto;
        printf("\nDigite o dia: ");
        scanf("%d", &dia);
        printf("Digite o mes: ");
        scanf("%d", &mes);
        printf("Digite o ano: ");
        scanf("%d", &ano);
		printf("Digite a hora: ");
        scanf("%d", &hora);
        printf("Digite o minuto: ");
        scanf("%d", &minuto);
        printf("-------------------\n");
        
        
        Evento* aux = lista;
        int encontrouEvento = 0;

        while (aux != NULL) {
            if (aux->dataEvento.dia == dia &&
                aux->dataEvento.mes == mes &&
                aux->dataEvento.ano == ano &&
                aux->dataEvento.hora == hora &&
                aux->dataEvento.minuto == minuto) {
                	
                printf("Codigo: %d\n", aux->codigo);
                printf("Data: %02d/%02d/%04d as %02d:%02d\n", 
                       aux->dataEvento.dia,
                       aux->dataEvento.mes,
                       aux->dataEvento.ano,
                       aux->dataEvento.hora,
                       aux->dataEvento.minuto);
                printf("Duracao: %.2f horas\n", aux->duracao);
                printf("Descricao: %s\n", aux->descricao);
                printf("--------------------\n");
                encontrouEvento = 1;
                break;
            }
            aux = aux->proximo;
        }

        if (!encontrouEvento) {
            printf("Nenhum compromisso encontrado para esta data e hora.\n");
        }

    }
	else {
        printf("Opcao invalida. Por favor, escolha 1 ou 2.\n");
    }
}

void lerDadosEvento(Evento* evento) {
    printf("Digite o codigo do evento: ");
    scanf("%d", &evento->codigo);

    printf("Dia: ");
    scanf("%d", &evento->dataEvento.dia);
    printf("Mes: ");
    scanf("%d", &evento->dataEvento.mes);
    printf("Ano: ");
    scanf("%d", &evento->dataEvento.ano);
    printf("Hora: ");
    scanf("%d", &evento->dataEvento.hora);
    printf("Minuto: ");
    scanf("%d", &evento->dataEvento.minuto);

    printf("Digite a duracao do evento: ");
    scanf("%f", &evento->duracao);

    printf("Digite a descricao do evento: ");
    getchar();  // Limpar o buffer do newline
    fgets(evento->descricao, sizeof(evento->descricao), stdin);
    evento->descricao[strcspn(evento->descricao, "\n")] = '\0'; // Remove a nova linha
}

void imprimirEventos(Evento* lista) {
    Evento* aux = lista;

    if (aux == NULL) {
        printf("Nenhum evento encontrado.\n");
        return;
    }

    printf("Lista de Eventos:\n");
    printf("--------------------\n");

    while (aux != NULL) {
        printf("C0digo: %d\n", aux->codigo);
        printf("Data: %02d/%02d/%04d as %02d:%02d\n", 
               aux->dataEvento.dia,
               aux->dataEvento.mes,
               aux->dataEvento.ano,
               aux->dataEvento.hora,
               aux->dataEvento.minuto);
        printf("Duracao: %.2f horas\n", aux->duracao);
        printf("Descricao: %s\n", aux->descricao);
        printf("--------------------\n");
        
        aux = aux->proximo;  // Move para o próximo evento
    }
}
void alterarEventoPorDataHora(Evento* lista, int dia, int mes, int ano, int hora, int minuto) {
    Evento* aux = lista;
    int eventoEncontrado = 0;

    while (aux != NULL) {
        // Verifica se a data e hora do evento correspondem
        if (aux->dataEvento.dia == dia &&
            aux->dataEvento.mes == mes &&
            aux->dataEvento.ano == ano &&
            aux->dataEvento.hora == hora &&
            aux->dataEvento.minuto == minuto) {
            
            eventoEncontrado = 1;
            // Solicita novas informações ao usuário
            printf("Evento encontrado. Digite os novos dados:\n");

            printf("Nova duracao do evento: ");
            scanf("%f", &aux->duracao);

            printf("Nova descricao do evento: ");
            getchar();
            fgets(aux->descricao, sizeof(aux->descricao), stdin);
            aux->descricao[strcspn(aux->descricao, "\n")] = '\0'; // Remove a nova linha

            printf("Evento alterado com sucesso.\n");
        }
        aux = aux->proximo;
    }

    if (!eventoEncontrado) {
        printf("Evento com a data e hora especificadas nao encontrado.\n");
    }
}

void excluirEventoPorDataHora(Evento** lista, int dia, int mes, int ano, int hora, int minuto) {
    Evento* aux = *lista;
    Evento* anterior = NULL;
    int eventoEncontrado = 0;

    while (aux != NULL) {
        // Verifica se a data e hora do evento correspondem
        if (aux->dataEvento.dia == dia &&
            aux->dataEvento.mes == mes &&
            aux->dataEvento.ano == ano &&
            aux->dataEvento.hora == hora &&
            aux->dataEvento.minuto == minuto) {
            
            eventoEncontrado = 1;

            // Se o evento a ser excluído é o primeiro da lista
            if (anterior == NULL) {
                *lista = aux->proximo;  // Atualiza a cabeça da lista
            }
			else {
                anterior->proximo = aux->proximo;  // Remove o evento da lista
            }

            free(aux);
            printf("Evento excluido com sucesso.\n");
            return;
        }
        anterior = aux;
        aux = aux->proximo;
    }

    if (!eventoEncontrado) {
        printf("Evento com a data e hora especificadas nao encontrado.\n");
    }
}
    
int main() {
    Evento* lista = NULL;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Incluir evento\n");
        printf("2. Consultar\n");
        printf("3. Alterar evento\n");
        printf("4. Excluir\n");
        printf("5. Listar todos\n");
        printf("6. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("----------------------\n");
		
	
        printf("----------------------\n");

        switch (opcao) {
            case 1: {
    			Data novaData;
    			

    			Evento* novoEvento = criarEvento(0, novaData, 0, "");
    			lerDadosEvento(novoEvento);
    			inserirFim(&lista, novoEvento);
    			break;
            }
            case 2: {
            	consultarEventos(lista);
				break;
			}
            case 3: {
    			int dia, mes, ano, hora, minuto;
    			printf("Dia: ");
    			scanf("%d", &dia);
    			printf("Mes: ");
    			scanf("%d", &mes);
    			printf("Ano: ");
    			scanf("%d", &ano);
    			printf("Hora: ");
    			scanf("%d", &hora);
    			printf("Minuto: ");
    			scanf("%d", &minuto);
    			alterarEventoPorDataHora(lista, dia, mes, ano, hora, minuto);
    			break;
			}
			case 4: {
    			int dia, mes, ano, hora, minuto;
    			printf("Dia: ");
    			scanf("%d", &dia);
    			printf("Mes: ");
    			scanf("%d", &mes);
    			printf("Ano: ");
    			scanf("%d", &ano);
    			printf("Hora: ");
    			scanf("%d", &hora);
    			printf("Minuto: ");
    			scanf("%d", &minuto);
    			excluirEventoPorDataHora(&lista, dia, mes, ano, hora, minuto);
    			break;
			}
			case 5: {
				if (lista == NULL) {
    		    	printf("A lista de eventos esta vazia.\n");
    			} 
				else {
        			imprimirEventos(lista);
    			}
   	 			break;
            }
			case 6: {
				break;
			}
            default:
                printf("Opçao invalida.\n");
        }
    } while (opcao != 6);

    return 0;
}
     
            
