#include "ARN.h"
#include "stdlib.h"
#include "stdio.h"

#pragma warning(disable : 4996)

#define V true
#define P false

typedef struct no
{
	bool cor;				//R1
	int val;
	struct no* esq, * dir;
	struct no* pai;

}NO;

NO* cria(int val, NO* pai)
{
	NO* novo;

	novo = (NO*)malloc(sizeof(NO*));

	novo->val = val;
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = pai;

	return novo;
}

void insere(NO** raiz, int val, NO* pai, bool direito)
{
	if ((*raiz) == NULL) {
		NO* novo;
		novo = cria(val, pai);

		(*raiz) = novo;

		if (direito)	(*raiz)->pai->dir = (*raiz);
		else			(*raiz)->pai->esq = (*raiz);

		return;
	}


	if (val > (*raiz)->val)			insere(&(*raiz)->dir, val, (*raiz), true);

	else if (val < (*raiz)->val)	insere(&(*raiz)->esq, val, (*raiz), false);


	//se o valor for igual ele não será adicionado
}

NO** busca(NO** raiz, int val)
{
	if ((*raiz) == NULL)		return NULL;

	if (val < (*raiz)->val)			busca(&(*raiz)->esq, val);
	else if (val > (*raiz)->val)	busca(&(*raiz)->dir, val);
	else							return raiz;
}

void rotpinta(NO** a)
{
	(*a)->cor = V;				//a
	(*a)->pai->cor = P;			//b
	(*a)->pai->pai->cor = V;	//c

	//nessa aplicação, em uma rotação dupla os nós serão pintados duas vezes em sequência, o que embora retundante não possui custo significativo
}

void rotD(NO** a)
{												//diagrama 0

	rotpinta(a);								//diagrama 1

	(*a)->pai->pai->esq = (*a)->pai->dir;		//diagrama 2
	(*a)->pai->dir = (*a)->pai->pai;			//diagrama 3

	(*a)->pai->pai = (*a)->pai->dir->pai;		//diagrama 4
	(*a)->pai->dir->pai = (*a)->pai;			//diagrama 5
}

void rotE(NO** a)
{

	rotpinta(a);

	(*a)->pai->pai->dir = (*a)->pai->esq;
	(*a)->pai->esq = (*a)->pai->pai;

	(*a)->pai->pai = (*a)->pai->esq->pai;
	(*a)->pai->esq->pai = (*a)->pai;
}

int antecessor(NO** x, int res)
{		printf("|/ ");
	if ((*x)->dir != NULL)	res = antecessor(&(*x)->dir, NULL);
	else {
		res = (*x)->val;

		if ((*x)->esq != NULL) {		printf("Caso2\n");
			(*x)->val = (*x)->esq->val;

			(*x)->esq = NULL;
			(*x) = NULL;

			//free((*x)->esq);
		}
		else {			printf("Caso3\n");
			(*x)->pai->dir = NULL;
			(*x) = NULL;

			//free((*x));
		}
	}
	return res;
}

int remove(NO** raiz, int val)				//diagrame sabosta -----------
{
	NO** x;
	int res;

	x = busca(raiz, val);
	
	if (x == NULL)		return NULL;
						printf("Val: %i\tesq: %ld  / dir : %ld\n", (*x)->val,(*x)->esq,(*x)->dir);
	res = (*x)->val;

	if ((*x)->esq == NULL) {
		if ((*x)->dir != NULL) {			//DIAGRAMA 0
				printf("Caso0\n");
			(*x)->dir->pai = (*x)->pai;		//DIAGRAMA 1
			
			(*x)->pai->dir = (*x)->dir;		//DIAGRAMA 2
		}
		else {
			printf("Caso1\n");
			(*x)->pai->dir = NULL;
		}

		(*x) = NULL;
		//free(x);							//DIAGRAMA 3
	}
	else	(*x)->val = antecessor(x, NULL);
	//free(x);
	return res;
}

void pinta(NO** raiz) {}

void rotaciona(NO** raiz)
{

}

void balanceia(NO** no)
{
	if ((*no)->pai->pai != NULL)									//tem avô
		if ((*no)->pai->pai->esq == (*no)->pai)						//o no à esquerda do avô é o pai
			if ((*no)->pai->pai->dir->cor)		pinta(no);			//o tio é vermelho, troca a cor
			else;
		else if ((*no)->pai->pai->esq->cor)		pinta(no);			//o tio é vermelho, troca a cor
		else									rotaciona(no);		//o tio é preto ou nulo, rotaciona; R3
	else										rotaciona(no);		//não tem avô, rotaciona
}

void r4(NO** no)
{
	if ((*no)->cor) {
		if ((*no)->esq != NULL)	if ((*no)->esq->cor)	balanceia(&(*no)->esq);
		if ((*no)->dir != NULL)	if ((*no)->dir->cor)	balanceia(&(*no)->dir);
	}
}

/// <summary>
/// Verifica o balanceamento
/// </summary>
/// <param name="raiz">-> raiz da arvore</param>
void balanco(NO** raiz)
{
	(*raiz)->cor = P;				//R2
}

int equilib(NO** raiz, int bal)
{
	bal = bal + 1 - (*raiz)->cor;

	return 0;
}

void insercao(NO** raiz, int val)
{
	insere(raiz, val, NULL, NULL);
	balanco(raiz);
	equilib(raiz, 0);
}

void inordem(NO* raiz)
{
	if (raiz == NULL)	return;

	inordem(raiz->esq);
	printf("%i %i\n", raiz->val, raiz->cor);
	inordem(raiz->dir);
}

void posordem(NO* raiz)
{
	if (raiz == NULL)	return;

	posordem(raiz->esq);
	posordem(raiz->dir);
	printf("%i %i\n", raiz->val, raiz->cor);
}

//-----------------------------------------------------------------------------------------------------------

int main()
{
	//srand(1241351242);

	int w = 0, fin;
	NO* arv;

	fin = 20;

	arv = cria(rand() % 100, NULL);

	while (w < fin)
	{
		insere(&arv, rand() % 100, NULL, NULL);

		w++;
	}
	posordem(arv);

	printf("\n\n->");

	scanf("%i", &w);

	remove(&arv, w);

	posordem(arv);

	//free(arv);
	return 0;
}

/*
void ARN::arn()
{
}
*/
