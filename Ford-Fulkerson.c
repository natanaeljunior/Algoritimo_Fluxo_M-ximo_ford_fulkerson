#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ESTRUTURAS PARA ARQUIVO DE DISTANCIA ENTRES OS PONTOS 

// ESTRUTURAS PARA ARQUIVO DE FLUXO ENTRE OS PONTOS

typedef struct matriz{
	 int nVertice;
	 char **cabecalho;	
	 int **matriz;
}TMatriz;

typedef struct carro{
	 char placa[50];
	 char motorista[50];
	 int  capacidade;
	 bool utilizado;
}TCarro;

typedef struct vetor
{
	int qtdCar;
	TCarro **vetCar;
} TVetor;


struct Fila
{
    int front;
    int rear;
    int *arr;
    int capacity;
};
/////////////////////////// ESTRUTURA LISTA CAMINHO


typedef struct caminho  {
	char *origem; 
	char *destino; 
	int saldo;
	int cap_Max;
	int passou;

}TCaminho;



struct Node  {
	 TCaminho *data;
	struct Node* next;
	struct Node* prev;
};


struct List  {
	struct Node *caminho;
	int nr;
	int totalFluxo;
	int totalKM;
	struct List* next;
	struct List* prev;
};


//struct Node* head; // global variable - pointer to head node.
struct List* list; 
///////////////////
// DECLARACAO DE FUNCOES
TMatriz * criaMat(int size);
void lerArquivo(char*nomeArquivo, void *m);
int contarVertices(char*nomeArquivo);
void imprimeMatrizFluxo(TMatriz *matriz);
void quebraStr(char string[1000], int linha, TMatriz * mFluxo);
void quebraStrCar(result,linha, vetCar);
void Print();
struct Node* InsertAtTail(TCaminho * newCaminho, struct Node * head);
void dispose(struct Node *head);
struct Node* reverse(struct Node *head);
// FUNCOES

void lerArquivo(char *nomeArquivo, void *mFluxo){
	
  FILE *arqTxt;
  char Linha[1000];
  char *result;
  int i;
  int linha = 0;

  // Abre um arquivo TEXTO para LEITURA
  arqTxt = fopen(nomeArquivo, "rt");
 	
	if (arqTxt == NULL)
	{
	    printf("Problemas na LEITURA do arquivo\n");
	    return;
	}else{
		printf("\n LEITURA DO ARQUIVO OK! \n");
	}

  while (!feof(arqTxt))
  {
  	
     result =  fgets(Linha, 1000, arqTxt);
      if (result ) {
      	  	if(linha>0){
      	  		
      	  			quebraStr(result,linha, mFluxo);
				}
	  }
	   linha++;
  	
  }
  
  fclose(arqTxt);
  printf(" \n DADOS INSERIDOS COM SUCESSO! \n");
   
}



void lerArquivoCarros(char *nomeArquivo, TVetor *vetCar){
	
  FILE *arqTxt;
  char Linha[1000];
  char *result;
  int i;
  int linha = 0;

  // Abre um arquivo TEXTO para LEITURA
  arqTxt = fopen(nomeArquivo, "rt");
 	
	if (arqTxt == NULL)
	{
	    printf("Problemas na LEITURA do arquivo\n");
	    return;
	}else{
		printf("\n LEITURA DO ARQUIVO OK! \n");
	}

  while (!feof(arqTxt))
  {
  	
     result =  fgets(Linha, 1000, arqTxt);
      if (result) {
      	  
      	  		quebraStrVetor(vetCar,result,linha);
	  }
	   linha++;
  	
  }
  
  fclose(arqTxt);
  printf(" \n DADOS INSERIDOS COM SUCESSO!\n");
   
}


void imprimeMatriz(TMatriz *matriz)
{

	
	int i,j;
	for ( i=0; i<matriz->nVertice; i++ ){
		printf("\n\nLinha: [%d]  ",i);
	  for ( j=0; j<matriz->nVertice; j++ )
	  {
	     printf("%d", matriz->matriz[i][j]);
	     printf("[%s,%s]  ", matriz->cabecalho[i],matriz->cabecalho[j]);
	  }
  }
}


void compareMatriz(TMatriz *matriz1,TMatriz *matriz2)
{

	
	int i,j;
	for ( i=0; i<matriz2->nVertice; i++ ){
		printf("\n\nLinha: [%d]  ",i);
	  for ( j=0; j<matriz2->nVertice; j++ )
	  {
	  	
	  	if(matriz1->matriz[i][j] != matriz2->matriz[i][j]){
	  		    printf("%d", matriz2->matriz[i][j]);
	     		printf("[%d,%d]  ", buscaPosCabe(matriz2->cabecalho[i],matriz2),buscaPosCabe(matriz2->cabecalho[j],matriz2));
		  }
	  }
  }
}



void insereMatriz(TMatriz *m, int lin, int col, char* val){
	
	if(lin >m->nVertice || lin < 0 || col >m->nVertice || col < 0 ){
		printf("\n --------- POSICAO NAO EXISTE! ---------");
		printf("\n --------- DESEJA REDIMENSIONAR A MATRIZ? ---------");		
	}else{


		int *newVal = (int *)malloc(sizeof(int));
	    newVal = atoi(val);
	
		
		m->matriz[lin][col] = newVal;
	}
	
}

void quebraStr(char string[1000], int linha, TMatriz *mFluxo){
     const char s[2] = ";";
     char* strQuebrada;
 	 int coluna=0;
 		
      strQuebrada = strtok(string, s);
		
	
      while( strQuebrada != NULL ) 
	  {
	  			
	  			if(coluna == 0 && linha >0)
				  {
	  			    char *newString = (char *)malloc(50*sizeof(char));
	  			    strcpy(newString, strQuebrada);
	  			    
	  			    mFluxo->cabecalho[linha-1] = newString;
	  			  
			  	  } else {
	  			
			  		if (linha>0 && coluna>0)
				 	 {
			  			insereMatriz(mFluxo, linha-1, coluna-1, strQuebrada);
				  	 }
				}
	  	
			coluna++;
        	strQuebrada = strtok(NULL, s);
     }
}

void quebraStrVetor(TVetor *vet, char string[100],int linha)
{
	char v[3][80];
	TCarro car;
	const char s[2] = ";";
	char *strQuebrada;
	int i = 0;

	strQuebrada = strtok(string, s);

	while (strQuebrada != NULL)
	{

		if (i == 2)
		{
			car.capacidade = atoi(strQuebrada);
		}
		else if (i == 0)
		{
			sprintf(car.placa, "%s", strQuebrada);
	
		}
		else if (i == 1)
		{
			sprintf(car.motorista, "%s", strQuebrada);
	    
		}
		i++;
		strQuebrada = strtok(NULL, s);
	}
	addVetor(vet, car, linha);
 
}

void addVetor(TVetor *vetor, TCarro car, int linha)
{

		TCarro *newCar = (TCarro *)malloc(sizeof(TCarro));
		*newCar = car;
		newCar->utilizado =  false;
		vetor->vetCar[linha] = newCar;

}

int contarVertices(char * nomeArquivo){
	
  FILE *arqTxt;
  int lin = 0, vertice = 0;
  char Linha[1000];

  // Abre um arquivo TEXTO para LEITURA
  arqTxt = fopen(nomeArquivo, "rt");
 	
	if (arqTxt == NULL)
	{
	    printf("Problemas na LEITURA do arquivo\n");
	    return;
	}else{
		printf("\n LEITURA DO ARQUIVO OK! \n");
	}

  while (!feof(arqTxt))
  {
  
  		if (fgets(Linha, 1000, arqTxt)){
  			if(lin>0){vertice++;}
	   }
	  	
  	  lin++;
  }
  
  fclose(arqTxt);
  printf(" \n QTD VERTICES CONTADAS COM SUCESSO!\n");
  printf(" ==== VERTICES %d", vertice);
   
  return vertice;
  	
}

int contarCarros(char * nomeArquivo){
	
  FILE *arqTxt;
  int lin = 0, vertice = 0;
  char Linha[1000];

  // Abre um arquivo TEXTO para LEITURA
  arqTxt = fopen(nomeArquivo, "rt");
 	
	if (arqTxt == NULL)
	{
	    printf("Problemas na LEITURA do arquivo\n");
	    return;
	}else{
		printf("\n LEITURA DO ARQUIVO OK! \n");
	}

  while (!feof(arqTxt))
  {
  
  		if (fgets(Linha, 1000, arqTxt)){
  			vertice++;
	   }
	  	
  	  lin++;
  }
  
  fclose(arqTxt);
  printf(" \n QTD VERTICES CONTADAS COM SUCESSO!\n");
  printf(" ==== VERTICES %d", vertice);
   
  return vertice;
  	
}

// FUNCOES PARA MANIPULAR MATRIZ DE ADJACENCIA
TMatriz *criaMat(int size){
		TMatriz *m =  (TMatriz *) malloc(sizeof(TMatriz));
			
		m->nVertice = size;
			int i;		
		if(m!=NULL)
		{
			    
		  /* aloca as linhas da matriz */
		  m->matriz = (int **) calloc (size, sizeof(int *));
	
		  if (m->matriz == NULL) {
		     printf("** Erro: Memoria Insuficiente **");
		     free(m);
		     return (NULL);
		     }
					
			/* aloca as colunas da matriz */
		  	for ( i = 0; i < size; i++ ) 
			  {
		      m->matriz[i] = (int*) calloc (size, sizeof(int));

		      if (m->matriz[i] == NULL) 
			  	 {
		         printf ("** Erro: Memoria Insuficiente **");
		         return (NULL);
		         }
		      }	
		}
		
		m->cabecalho = (char **)malloc(size * sizeof(char *));

		if (m->cabecalho == NULL)
		{
			free(m);
			return NULL;
		}


		for (i = 0; i < size; i++)
		{
			m->cabecalho[i] = NULL;
		}
		
	return m;
}

//====================== CRIA VETOR ================
TVetor *criaVetor(int size)
{
	TVetor *vetor = (TVetor *)malloc(sizeof(TVetor));
	if (vetor != NULL)
	{
		int i;

		vetor->qtdCar =  size;
		vetor->vetCar = (TCarro **)malloc(size * sizeof(TCarro *));

		if (vetor->vetCar == NULL)
		{
			free(vetor);
			return NULL;
		}

		for (i = 0; i < size; i++)
		{
			vetor->vetCar[i] = NULL;
		}
	}
	return vetor;
}

void imprimeVetor( TVetor * listCarros, int qtdCar){
	
int i;

	for(i = 0; i<qtdCar; i++){
	printf("\n======MAIN=======");
 		printf("\n      PLACA: %s ",listCarros->vetCar[i]->placa);
		printf("\n  MOTORISTA: %s ",listCarros->vetCar[i]->motorista);
		printf("\n CAPACIDADE: %d ",listCarros->vetCar[i]->capacidade);
	printf("\n=================");
		
	}

}

// FUNCAO PARA ALGORITIMO DE FLUXO MAXIMO

// Uma fila para a pesquisa pela primeira vez

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }

    else
    {
        return b;
    }
}


struct Fila *criar_fila(int capacity)
{
    struct Fila *q = (struct Fila *)malloc(sizeof(struct Fila));
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->arr = (int *)malloc(sizeof(int) * q->capacity);
    return q;
}

int isFull(struct Fila *q)
{
    return q->rear == q->capacity;
}

int Vazia(struct Fila *q)
{
    return ((q->front == q->rear + 1) || (q->front == -1 && q->rear == -1));
}

void enfileirar(struct Fila *q, int data)
{
    if (!isFull(q))
    {
        q->rear += 1;
        if (q->front == -1 && q->rear == 0)
        {
            q->front = 0;
        }
        q->arr[q->rear] = data;
    }

    else
    {
        return;
    }
}

int desenfileirar(struct Fila *q)
{
    if (!Vazia(q))
    {
        int item = q->arr[q->front];
        q->front += 1;
        return item;
    }

    else
    {
        return -9999; // code ERROR
    }
}

////////////////////////// Graph Operations /////////////////////////////////////

int **create_graph(int n) // n : number of vertices
{
    int **mat = (int **)malloc(sizeof(int *) * n);
    int i;
    for ( i = 0; i < n; i++)
    {
        mat[i] = (int *)calloc(sizeof(int), n);
    }

    return mat;
}

void read_graph(int **mat, int n)
{
    int i, j, c; // i: starting vertex and j: ending vertex c : capacity

    while (1)
    {
        printf("Enter the start & end vertex along with the capacity : "), scanf("%d %d %d", &i, &j, &c);
        if (i == -1 && j == -1)
        {
            return;
        }

        mat[i][j] = c;
    }
}

int bfs(int **res_graph, int s, int t, int path[], int n)
{
    struct Fila *q = criar_fila(n);
    int *visited = (int *)calloc(sizeof(int), n);
    visited[s] = 1;
    enfileirar(q, s);
    path[s] = -1;

    while (!Vazia(q))
    {
        int dsrc = desenfileirar(q);
		int i;
        for (i = 0; i < n; i++)
        {
            if (res_graph[dsrc][i] > 0 && visited[i] == 0)
            {
          
                enfileirar(q, i);
                visited[i] = 1;
                path[i] = dsrc;
            }
        }
    }


    if (visited[t] == 1)
    {
    	
        return 1;
    }

    else
    {
    	
        return 0;
    }
    
}


 bool alocarVeiculo(TVetor *listCarros,int fluxo){
 	
 	int calc=0;
 	TCarro *car = NULL;
 	int i, aux=100000;
 	
 	for (i=0; i<listCarros->qtdCar;i++)
	 {
 		 calc = listCarros->vetCar[i]->capacidade-fluxo;
 		
 		if(calc < aux && calc >=0 && listCarros->vetCar[i]->utilizado == false)
		 {
 			aux =  calc;
			car = listCarros->vetCar[i];
 		
		 }
	 }
	

	
	if(car==NULL){

		printf("\n\n===================================");
		for (i=0; i<listCarros->qtdCar;i++)
	 	{
	 
 		 printf("\nCARRO %d ",i);
 		 if(listCarros->vetCar[i]->utilizado == true){
 		 	printf("UTILIZADO",listCarros->vetCar[i]->utilizado);
		  }else{
		  	printf("CAPACIDADE INSUFICIENTE : %d", listCarros->vetCar[i]->capacidade);
		  }
 		  
	 	}
	 	printf("\n\n===================================");
	 	
		return false;
	} 
	
	printf("\n================ CARRO UTILIZADO PARA FLUXO DE %d ==================",fluxo) ;
	printf("\nPlaca: %s ",car->placa);
	printf("\nMotorista: %s ",car->motorista);
	printf("\nCapacidade: %d ",car->capacidade);
	car->utilizado =  true;
	printf("\n=====================================================================\n");
	car->capacidade=  car->capacidade-fluxo;
	printf("CAPACIDADE ATUALIZADA PARA : %d", car->capacidade);
	
	return true;
 }

////////////////////////// Ford Fulkerson ALgorithm /////////////////////////////////////

int fordFulkerson(TMatriz *graph, int origem, int destino, int n, TVetor * listCarros)
{
    int u, v;
	 
	char vetPercorrido[graph->nVertice];
	
	// LISTA
 		
 	
    int **res_graph = create_graph(n);
    for (u = 0; u < n; u++)
    {
    
        for (v = 0; v < n; v++)
        {
            res_graph[u][v] = graph->matriz[u][v];
           
        }
    }

    int path[n];

    int max_flow = 0;

	int lin=0, col=0;
    while (bfs(res_graph, origem, destino, path, n))
    {
    	
    
    	
        int path_flow = 1000; 
        printf("\n\n");
        for (v = destino; v != origem; v = path[v])
        {
            u = path[v];
            path_flow = min(path_flow, res_graph[u][v]);
         
        }
		
			struct Node *newHead = (struct Node*)malloc(sizeof(struct Node));	
 			newHead = NULL;
 		
        for (v = destino; v != origem; v = path[v])
        {
            u = path[v];
            res_graph[u][v] -= path_flow;
            res_graph[v][u] += path_flow;
            
		//	printf("\n | [saldo: %d]<- [passou: %d]<- [Cap.Max: %d] <::%d-%d \n",res_graph[u][v],path_flow, (res_graph[u][v]+path_flow),v,u);
          
       		 
       		 
       	     TCaminho* c = ( TCaminho*)malloc(sizeof( TCaminho));
       	     c->cap_Max = (res_graph[u][v]+path_flow);
       	     c->passou = path_flow ;
       	     c->saldo = res_graph[u][v];
       	     c->origem = graph->cabecalho[u];
			 c->destino = graph->cabecalho[v];	
				
       		
       		newHead = InsertAtTail(c, newHead); 
       		
			Print(newHead);   
			     	
          col++;
        }
		
	
        max_flow += path_flow;
        
		
        
		printf("\n Maximo fluxo deste caminho: %d\n",path_flow);
		 if(!alocarVeiculo(listCarros,path_flow)){
		 	
		 	printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		 	printf("\n == Nao ha carros disponiveis! ==\n");
		 	printf("\niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n");
		 	system("PAUSE");
		 	return max_flow-path_flow;
		 }
		 
		 	InsertListCaminho(newHead, lin, path_flow); 
	
	lin++;	

    }
   

    return max_flow;
}


 void carNaoAlocados(TVetor *listCar){
 	int i ;
	printf("\n\n ================ VEICULOS NAO ALOCADOS ==================") ;
 	for(i=0; i<listCar->qtdCar; i++){
 		if(!listCar->vetCar[i]->utilizado){
 		
			printf("\n Placa: %s ",listCar->vetCar[i]->placa);
			printf("\n Motorista: %s ",listCar->vetCar[i]->motorista);
			printf("\n Capacidade: %d ",listCar->vetCar[i]->capacidade);
	printf("\n**********************************************************");

		}
	 }
	printf("\n=====================================================================\n");

 }

// funcoes de lista para salvar caminhos



struct TListCaminho* newLista(struct Node *node, int lin, int totalF) {
	 struct List* newCaminho = (struct List*)malloc(sizeof(struct List));
	newCaminho->caminho = node;
	newCaminho->totalFluxo = totalF;
	newCaminho->nr = lin;
	newCaminho->prev = NULL;
	newCaminho->next = NULL;
	return newCaminho;
}


void InsertListCaminho(struct Node *newnode, int lin, int totalFluxo) {
	 struct List* temp = list;
	    
	 struct List* newCaminho = newLista(newnode, lin, totalFluxo);
	 
	if(list == NULL) {
		list = newCaminho;
		return;
	}
	while(temp->next != NULL) temp = temp->next; 
	temp->next = newCaminho;
	newCaminho->prev = temp;
}



struct Node* newNo(TCaminho *newCaminho) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = newCaminho;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}



struct Node *InsertAtTail(TCaminho *newCaminho, struct Node *head) {
	struct Node* temp = head;
	struct Node* newNode = newNo(newCaminho);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; 
	temp->next = newNode;
	newNode->prev = temp;

return head	;
}

//Prints all the elements in linked list in forward traversal order
void PrintList() {


	struct List *aux = list;
	printf("\n\nCAMINHO LISTA:\n" );
	while(aux != NULL) {
			printf("\n\nCaminho: %d | F.Total: %d \n",aux->nr, aux->totalFluxo);
			Print(aux->caminho);
		aux =aux->next;
	}
	


	printf("\n");
}



//Prints all the elements in linked list in forward traversal order
void Print( struct Node *head) {


	struct Node *temp= head;

	while(temp != NULL) {
		
		printf(" | [saldo: %d]<- [passou: %d]<- [Cap.Max: %d] <::%s-%s \n",
		           temp->data->saldo,
				   temp->data->passou, 
				   temp->data->cap_Max,
				   temp->data->destino,
				   temp->data->origem 
				);
		temp =temp->next;
	}
	printf("\n");
}


/*
    remove all element of the list
*/
void dispose(struct Node *head)
{
    struct Node *cursor, *tmp;
 
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}


int  buscaPosCabe(char str[1], TMatriz *MD){
 	
 	
 	int i; 
 	
 	for (i = 0; i<MD->nVertice; i++)
	 {
 		if(strcmp(str, MD->cabecalho[i])==0)
 		return i;
	 }

 }

 void calcularDistancia( TMatriz *matrizDis){
 	
	struct List *aux = list;
	int dis;
	printf("\n\nCAMINHO LISTA:\n" );
	while(aux != NULL) {
		dis = 0;
			printf("\n\nCaminho: %d | F.Total: %d \n",aux->nr, aux->totalFluxo );
		
			struct Node *temp= aux->caminho;

			while(temp != NULL) {
				
				int O =  buscaPosCabe(temp->data->origem, matrizDis);
				int D =  buscaPosCabe(temp->data->destino, matrizDis);
				printf("\n Origem:%s - [%d]\n Destino %s  - [%d] \n",
				           temp->data->origem,
				           O,
						   temp->data->destino,
						   D
						);
					dis = dis+matrizDis->matriz[O][D];	
					
				//	imprimeMatriz(matrizDis);
					printf("\n\nDistancia: O:D %d  ", matrizDis->matriz[O][D]);	
				temp =temp->next;
			}
			printf("\n");
		
		printf("========== Total Distancia KM: %d =========== \n\n",dis );
		
		aux =aux->next;
	}
	

 	
 }

void verificaArestaNulo(){
	
	struct List *aux = list;
	printf("\n\nCAMINHO LISTA: " );
	while(aux != NULL) {
			printf("\n\nCaminho: %d | ",aux->nr );
		
			struct Node *temp= aux->caminho;
				
			int qtdA_Nula=0;
			while(temp != NULL) {
				
				
				if(temp->data->saldo == 0){
					
					printf(" Origem: %s - Destino: %s ", temp->data->origem, temp->data->destino);
					qtdA_Nula++;
				}
				
				temp =temp->next;
			}
		
			printf("\n\n ========== Aresta Nula : %d =========\n", qtdA_Nula);
			if(qtdA_Nula == 1){
				Print(aux->caminho);
			}else{
				printf("Quantidade de arestas nulas > 1 : %d", qtdA_Nula);
			}
			
		aux =aux->next;
	}
	


	printf("\n");
	
}


 void cargaPendente( TMatriz *MF)
{
	struct List *aux = list;

	while(aux != NULL) {
		
			struct Node *temp= aux->caminho;

			while(temp != NULL) {
				
				int O =  buscaPosCabe(temp->data->origem, MF);
				int D =  buscaPosCabe(temp->data->destino, MF);
				MF->matriz[O][D] = MF->matriz[O][D] - aux->caminho->data->passou;	
					
				temp =temp->next;
			}
	
		aux =aux->next;
	}
	
 	
}
int main(int argc, char *argv[]) {
	
	int qtdCar = contarCarros("carros.txt");
	int qtdVerFluxo = contarVertices("fluxo.txt");
	int qtdVerDis = contarVertices("distancia.txt");
	

////////////////////////////////////////////////////////
		
	TMatriz *mFluxo = criaMat(qtdVerFluxo);
	lerArquivo("fluxo.txt", mFluxo);

//	imprimeMatriz(mFluxo);
		
	TMatriz *mDistancia = criaMat(qtdVerDis);
	lerArquivo("distancia.txt", mDistancia);

//	imprimeMatriz(mDistancia);
	
	
	TVetor *listCarros = criaVetor(qtdCar);
	lerArquivoCarros("carros.txt", listCarros);
	
 //  imprimeVetor(listCarros, qtdCar);
	
	
	 int *visited = (int *)calloc(sizeof(int), qtdCar);
	 
	system("PAUSE");
	system("cls");
	int op = -1;
	
	while(op!=0){
		system("cls");
		printf("\n=================== MENU ===================\n");
		printf("\n 1 - Veiculos alocados para cada fluxo e o caminho.");
		printf("\n 2 - Distância a percorrer em cada Fluxo. ");
		printf("\n 3 - Lista de veiculos nao alocados.");	
		printf("\n 4 - Veiculos Insuficientes.");	
		printf("\n 5 - Carga  pendente em cada centro. ");
		printf("\n 6 - Caminho com apenas uma aresta nula (Informe qual a aresta e o caminho)");
		printf("\n\n=================== FIM =====================\n");
		printf("\n\n Escolha uma opcao: ");
		scanf("%d", &op);
		
			switch (op)
		{
			
		case 1:
			system("cls");
		   
		    printf("\n\nFLUXO MAXIMO: %d\n\n", fordFulkerson(mFluxo, 0, 5,qtdVerFluxo,listCarros));
			 
			system("PAUSE");
		
			break;
		case 2:
			system("cls");
				calcularDistancia(mDistancia);
					printf("\n\n");
			system("PAUSE");
	
			break;
			
			case 3:
			system("cls");
			carNaoAlocados(listCarros);
		
	        system("PAUSE");

			break;
			
			case 4:
			system("cls");
		 	
		    printf("\n\nFLUXO MAXIMO : %d \n\n", fordFulkerson(mFluxo, 0, 9,qtdVerFluxo,listCarros));
		
	        system("PAUSE");

			break;
			
			case 5:
			system("cls");
			
					
			TMatriz *mOriginal = criaMat(qtdVerFluxo);
			lerArquivo("fluxo.txt", mFluxo);
			
			cargaPendente(mFluxo);
			compareMatriz(mOriginal, mFluxo);
	        system("PAUSE");

			break;
			
			case 6:
			system("cls");
			verificaArestaNulo();
	        system("PAUSE");

			break;
		}
	}
	
	return 0;
}
