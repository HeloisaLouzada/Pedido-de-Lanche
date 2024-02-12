#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>
#define TAM 100

//STRUCTS
typedef struct {
    char nome_lanche[TAM];
    float preco;
    char ingredientes[TAM];
} Lanche;

typedef struct {
    int codigo;
    char nome_cliente[TAM];
    int quantidade;
    Lanche lanche_pedido;
} Pedido;

//PONTEIRO PARA CHAMADA DE FUNÇÃO
typedef void(*pointGenerico)(Pedido *, int n);

void ativarFuncao(Pedido *pedido, int n, pointGenerico funcao){
	funcao(pedido, n);
	system("pause");
}

//FUNÇÕES
int menu() {
	int op;
	
	printf("\n\nSISTEMA PEDIDOS\n\n");
	printf(" 1 - Inserir\n");
	printf(" 2 - Pesquisar por número\n");
	printf(" 3 - Pesquisar por nome\n");
	printf(" 4 - Atualizar\n");
	printf(" 5 - Maior\n");
	printf(" 6 - Excluir\n");
	printf(" 7 - Listar\n");
	printf(" 8 - Ordenar a partir dos código com Quick Sort\n");
	printf(" 9 - Ordenar a partir dos nomes dos clientes com Shake Sort\n");
	printf("10 - Ordenar a partir da quantidade com Comb Sort\n");
	printf("11 - Ordenar a partir dos preços unitários com Bubble Sort\n");
	printf(" 0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf("%d", &op);
	} while(op < 0 || op > 11);
	return op;
}

void imprimir(Pedido *pedido, int a){
    float valor;
	printf("\nDADOS DO PEDIDO\n");
    printf("Número do pedido:%d | Nome:%s | Quantidade:%d\n", pedido[a].codigo, pedido[a].nome_cliente, 
	pedido[a].quantidade);
    printf("\nDADOS DO LANCHE\n");
	printf("Lanche:%s | Valor da unidade:%.2f | Ingredientes:%s", pedido[a].lanche_pedido.nome_lanche, 
	pedido[a].lanche_pedido.preco, pedido[a].lanche_pedido.ingredientes);
	
	valor = pedido[a].quantidade * pedido[a].lanche_pedido.preco;
	printf(" | Valor total: R$%.2f\n\n", valor);
	printf("___________________________________________________________________________________\n");
}

int pesquisar_codigo(Pedido *pedido, int cont, int p){
	int i;
	for (i=0; i < cont; i++){
		if(pedido[i].codigo == p){
		return i;
       }
	}
	return -1;	
}

int validacao_codigo(Pedido *pedido, int cont){
	int aux, pesq;
	//Reutiliza a função pesquisar para validar e não deixar um código ser repetido

	do{
		printf("Digite o código do pedido:");
		scanf("%d", &pesq);
		aux = pesquisar_codigo(pedido, cont, pesq); 
		if (aux != -1){
		printf("Código já existente!!");
		}
	}while(aux != -1);
	return pesq;
}

void inserirPedido (Pedido *pedido, int cont) {
	int codigo;
	
	printf("\nINSERIR DADOS DO PEDIDO\n");
	codigo = validacao_codigo(pedido, cont);
    pedido[cont].codigo = codigo;
	   
    printf("Digite o nome do cliente:");
    scanf(" %99[^\n]s", pedido[cont].nome_cliente);
    
    printf("Digite a quantidade:");
    scanf("%d", &pedido[cont].quantidade);
    
    printf("\nDADOS DO LANCHE\n");
    printf("Digite o nome do lanche:");
    scanf(" %99[^\n]s", pedido[cont].lanche_pedido.nome_lanche);
    
	printf("Digite o valor do lanche:");
    scanf("%f",&pedido[cont].lanche_pedido.preco);
    
	printf("Digite os ingredientes:");
    scanf(" %99[^\n]s", pedido[cont].lanche_pedido.ingredientes); 
	
	printf("Pedido inserido!!\n");
}

void disponibilidade (Pedido *pedido,int cont){
	int i;
    printf("Os códigos de pedido cadastrados são:");
	for(i=0; i < cont; i++){
		printf("\n%d", pedido[i].codigo);
	}
}

void consultar_num(Pedido *pedido, int cont){
	int aux, pesq;
	
	if (!cont){
		printf("Nenhum pedido foi cadastrado !!\n");
	} 

	else{
		disponibilidade(pedido, cont);
		
		do{
			printf("\nDigite qual você deseja visualizar:");
			scanf("%d", &pesq);
			aux = pesquisar_codigo(pedido, cont, pesq);
			
			if (aux == -1){
			printf("Código não existente."); 
			/*Apesar de ter a mesma estrutura, a condição retornada é diferente da função "validacao_codigo"*/
			}

		}while(aux == -1);
		
		imprimir(pedido, aux);
	}
}

int pesquisar_nome(Pedido *pedido, int cont, char *p){
	int i;
	for (i=0; i < cont; i++){
		if(!strcmp(pedido[i].nome_cliente, p)){
		return i;
       }
	}
	return -1;	
}

void consultar_nome(Pedido *pedido, int cont){
	int i,aux;
	char pesq[TAM];
	
	if (!cont){
		printf("Nenhum pedido foi cadastrado !!\n");
	} 

	else{
		printf("Os nomes dispiníveis para consulta são:");
		for(i=0; i < cont; i++){
			printf(" %s |", pedido[i].nome_cliente);
		}
		
		do{
			printf("\nDigite qual você deseja visualizar:");
			scanf(" %99[^\n]s", pesq);
			aux = pesquisar_nome(pedido, cont, pesq);
			if (aux == -1){
			printf("Nome não existente.");
			}
		}while(aux == -1);
		
		imprimir(pedido, aux);
	}
}

void atualizar(Pedido *pedido, int cont){
	int aux, pesq;
	
	if (!cont){
		printf("Nenhum pedido foi cadastrado !!\n");
	} 

	else{
		disponibilidade(pedido, cont);
		
		do{                                                
			printf("Digite qual você deseja atualizar?");
			scanf("%d", &pesq);
			aux = pesquisar_codigo(pedido, cont, pesq);
			
			if (aux == -1){
			printf("Código não existente.");
			}
		}while(aux == -1);
		
		printf("Digite a nova quantidade:");
		scanf("%d", &pesq);
		
		pedido[aux].quantidade = pesq;
		printf("Quantidade atualizada!!\n");
	}
}

void remover (Pedido *vetor, int *qtde, int p) {
	int i;
	
	for (i = p; i < *qtde- 1; i++) {
		   vetor[i] = vetor[i+1];
	}
	(*qtde)--;
}

void excluir (Pedido *pedido, int *cont) {
	int aux, pos;
	
	if ( !*cont){
		printf("Nenhum pedido foi cadastrado!!\n");
	} 

	else{
		disponibilidade(pedido, *cont);

		printf("\nQual o código deseja excluir?");
		scanf("%d", &aux); 
		
		pos = pesquisar_codigo(pedido, *cont, aux);
		remover(pedido, cont, pos);
		printf("Pedido excluido!!\n");
	}
	system("pause");
}

void maior(Pedido *pedido, int cont){
    int i, pos;
    float valor, maior = 0;
    
	if (!cont){
		printf("Nenhum pedido foi cadastrado!!");
	} 

	else{
		for(i=0; i < cont; i++){
			valor = pedido[i].quantidade * pedido[i].lanche_pedido.preco;
			
			if(valor >= maior){
				maior=valor;
				pos=i;
			}
		}

		printf("O maior pedido é:\n");
		imprimir(pedido, pos);
	}
}

void listar(Pedido *pedido, int cont){
    int i;
    
	if (!cont){
		printf("Nenhum pedido foi cadastrado!!\n");
	} 
	
	else{
		for(i=0; i<cont; i++){
		imprimir(pedido,i);  
		}
	}
}  

//MANIPULAÇÃO DE ARQUIVO
FILE * abrirArquivo(char *nomeArq, char *modo) {
    
    FILE *arq;
    arq = fopen( nomeArq, modo );
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo!!");
        exit(-1);
    }
    return arq;
}

void carregarArquivo(FILE * arquivo, Pedido * vetProd, int *qtde) {
    fread(qtde, sizeof(int), 1, arquivo);
    fread(vetProd, sizeof(Pedido), *qtde, arquivo);
}

void listarBin(Pedido *vetProd, int qtde) {
    int i;
    
	for( i=0; i < qtde; i++) {
        printf("%3d|%-50s|%5d|%10.2f|%-50s|%-50s\n\n", vetProd[i].codigo, vetProd[i].nome_cliente, 
		vetProd[i].quantidade , vetProd[i].lanche_pedido.preco, 
		vetProd[i].lanche_pedido.nome_lanche, vetProd[i].lanche_pedido.ingredientes);
    }
	if(i!=0){
	system("pause");
	}
}

void gravarArquivo(FILE * arquivo, Pedido * vetProd, int qtde) {
    fwrite(&qtde, sizeof(int), 1, arquivo);
    fwrite(vetProd, sizeof(Pedido), qtde, arquivo);
}


//ALGORITMOS DE ORDENAÇÃO
//QUICK SORT
void trocar(Pedido *vet, int i, int f){
    Pedido aux;
    
	aux = vet[i];
    vet[i] = vet[f];
    vet[f] = aux;   
}

int particao(Pedido *vetor, int ini, int fim) {
	int pivo, i, f;

	pivo = vetor[ini].codigo;
	i = ini + 1;
	f = fim;
	
	while (i <= f){
	   
    	   if (vetor[i].codigo < pivo){
    	       i++;
    	   }
    	       else if (vetor[f].codigo > pivo){
    	            f--;
    	          }
    	             else {
                	     trocar(vetor, i, f);
                	     i++;
                	     f--;
                	   }
	}
    trocar(vetor, ini, f);
    return f;
}

void quickSort(Pedido * vetor, int ini, int fim ) {
	
	int posPivo;
	
	if ( ini < fim ) {
	    
		posPivo = particao(vetor,ini,fim);
		quickSort(vetor, ini, posPivo - 1 );
		quickSort(vetor, posPivo + 1, fim );
	}
}

//SHAKE SORT
void shakeSort(Pedido *vet, int n) {
	int i, f,trocas;
    int ini = 0;
    int fim = n - 1;
	Pedido aux;

    do {
       
        trocas = 0;
        for (i = ini,  f = fim ; i < fim; i++, f--) {
            if ( strcmp(vet[i].nome_cliente, vet[i+1].nome_cliente) > 0) {
                aux = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = aux;
                trocas++;
            }
            if ( strcmp(vet[f].nome_cliente, vet[f-1].nome_cliente) < 0) {
                aux = vet[f];
                vet[f] = vet[f-1];
                vet[f-1] = aux;
                trocas++;
            }

        }
        ini++;
        fim--;

    } while ( trocas > 0);
	 printf("Pedidos ordenados !!\n");
}

//COMB SORT
void combSort(Pedido * vet, int n) {
    Pedido aux;
    int i, trocas;
    int h;

    h = n;
    do {
        h = h / 1.3;
        if ( ( h == 9) || ( h == 10) ) {
            h = 11;
        } else if ( h == 0) {
            h = 1;
        } 

        trocas = 0;
        for (i = 0; i < n-h; i++) {
            if ( vet[i].quantidade > vet[i+h].quantidade) {

                aux = vet[i];
                vet[i] = vet[i+h];
                vet[i+h] = aux;
                trocas++;
            }
        }
        
        if ( h == 1) {
            n--;
        }
        
    } while ( ( trocas > 0) || ( h > 1) );
	printf("Pedidos ordenados !!\n");
}

//BUBBLE SORT
void bubbleSort(Pedido * vet, int n) {
    Pedido aux;
	int i, trocas;

    do {
       
        trocas = 0;
        for (i = 0; i < n-1; i++) {
            if ( vet[i].lanche_pedido.preco > vet[i+1].lanche_pedido.preco) {
                
                aux = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = aux;
                trocas++;
            }
        }
        n--;

    } while ( trocas > 0);
	printf("Pedidos ordenados !!\n");
}

//FUNÇÃO PRINCIPAL
int main() {
    //SetConsoleOutputCP(65001);
	FILE * arquivo; 
	Pedido pedidos[TAM];
	int op, cont = 0;
	
	arquivo = abrirArquivo("Pedidos.bin", "rb");
	carregarArquivo(arquivo, pedidos, &cont);
    
	while ( ! feof(arquivo) ) {                   
        fread(pedidos, sizeof(Pedido), 1, arquivo);
	}
	
	listarBin(pedidos, cont);
	
	do {
		op = menu();
		switch ( op ) {
			case 0:
				arquivo = abrirArquivo("Pedidos.bin", "wb");
				gravarArquivo(arquivo, pedidos, cont);
				fclose(arquivo);
				break;
			case 1:
				ativarFuncao(pedidos, cont, inserirPedido); 
				arquivo = abrirArquivo("Pedidos.bin", "wb");
				gravarArquivo(arquivo, pedidos, cont);
				fclose(arquivo);
				cont++;
				break;
			case 2:
				ativarFuncao(pedidos, cont, consultar_num);
				break;
			case 3:
				ativarFuncao(pedidos, cont, consultar_nome);
				break;
			case 4:
				ativarFuncao(pedidos, cont, atualizar);
				break;
			case 5:
				ativarFuncao(pedidos, cont, maior);
				break;
			case 6:
				excluir(pedidos, &cont);
				break;
			case 7:
				carregarArquivo(arquivo, pedidos, &cont);
				ativarFuncao(pedidos, cont, listar);
				break;	
			case 8:
				quickSort(pedidos, 0, cont-1);
				printf("Pedidos ordenados !!\n");
				system("pause");
				break;
			case 9:
				ativarFuncao(pedidos, cont, shakeSort);
				break;	
			case 10:
				ativarFuncao(pedidos, cont, combSort);
				break;	
			case 11:
				ativarFuncao(pedidos, cont, bubbleSort);
				break;		
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}
	} while (op != 0);
	return 0;
}