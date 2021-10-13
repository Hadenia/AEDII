#include <vector>
#include<iostream>
using namespace std;

template <typename K, typename V>
class Tupla {
private:
	K chave;
	V valor;
	Tupla* prox;
public:
	Tupla(K c, V v) {
		chave = c;
		valor = v;
		prox = NULL;
	}

	K getChave() {
		return chave;
	}

	V getValor() {
		return valor;
	}

	Tupla* getProx() {
		return prox;
	}

	void setProx(Tupla* prox) {
		Tupla::prox = prox;
	}
};

template <typename Chave, typename Valor>
class TabelaHash {

private:
	Tupla<Chave, Valor>** tabela;

	//tamanho atual do array
	int qtde_buckets;
	//qtdade de elementos j� inseridos na tabela hash
	int tamanho;

	/**
	* Fun��o para inserir a tupla <c,v> na tabela.
	* � preciso calcular o c�digo hash a partir da chave c.
	* Em seguida, usamos qtde_buckets para descobrir o �ndice
	* dessa tupla. Prestar aten��o na aloca��o de tupla quando
	* h� colis�es. A fun��o hash �s vezes retorna valores
	* negativos: use abs() para evitar �ndices negativos.
	**/
	void inserir(Chave c, Valor v, Tupla<Chave, Valor>** tabela) {
		//IMPLEMENTAR
		Tupla<Chave, Valor>* nova_tupla = new Tupla<Chave, Valor>(c, v);

		int indexBucket = obterIndexBucket(c, this->qtde_buckets);

		Tupla<Chave, Valor>* tupla_inicial_bucket = this->tabela[indexBucket];

		// Adiciona nova tupla no �nicio da lista encadeada
		nova_tupla->setProx(tupla_inicial_bucket);
		this->tabela[indexBucket] = nova_tupla;
	}

	/**
	* Fun��o para aumentar o tamanho do array quando o
	* fator de carga for >= 1. O tamanho do array
	* (qtde_buckets) deve ser multiplicado por 8 para
	* que essa opera��o seja feita com pouca frequ�ncia.
	* Por fim, precisamos reposicionar as tuplas, considerando
	* que a posi��o nesse novo array com maior tamanho
	* ser� diferente.
	**/
	void aumentaArray() {
		//IMPLEMENTAR
		int i;
		int nova_qtde_buckets = this->qtde_buckets * 8;

		Tupla<Chave, Valor>** nova_tabela = new Tupla<Chave, Valor> *[nova_qtde_buckets];
		for (i = 0; i < nova_qtde_buckets; i++)
			nova_tabela[i] = NULL;

		// Faz a transfer�ncia dos primeiros elementos de cada bucket
		// da tabela antiga para a nova
		for (i = 0; i < this->qtde_buckets; i++)
		{
			if (this->tabela[i] == NULL)
				continue;

			Tupla<Chave, Valor>* primeiro_elem_bucket = this->tabela[i];
			int index_nova_tabela = obterIndexBucket(primeiro_elem_bucket->getChave(), nova_qtde_buckets);
			nova_tabela[index_nova_tabela] = primeiro_elem_bucket;
		}

		delete this->tabela;
		this->tabela = nova_tabela;
		this->qtde_buckets = nova_qtde_buckets;
	}

	int obterIndexBucket(Chave c, int total_buckets)
	{
		size_t chave = hash<Chave>{}(c); // usar abs()?
		return chave % total_buckets;
	}

public:

	/**
	* Inicializar o array de tuplas com capacidade = qtde_buckets.
	* Lembrar de setar todas as posi��es do array inicializado
	* para NULL.
	**/
	TabelaHash() {
		//IMPLEMENTAR
		qtde_buckets = 8;
		tamanho = 0;

		tabela = new Tupla<Chave, Valor>*[qtde_buckets]();
		for (int i = 0; i < qtde_buckets; i++)
			tabela[i] = NULL;
	}

	void reset_tabela()
	{
		this->tamanho = 0;
		this->qtde_buckets = 8;

		delete this->tabela;
		this->tabela = new Tupla<Chave, Valor> *[this->qtde_buckets];
		for (int i = 0; i < this->qtde_buckets; i++)
			this->tabela[i] = NULL;
	}

	/**
	* Essa � a fun��o p�blica que nos permite inserir
	* uma tupla <c,v> na tabela. Nessa fun��o n�s
	* verificamos se � preciso aumentar o array de acordo
	* com o load factor. Essa fun��o pode reusar sua vers�o
	* sobrecarregada para inserir a tupla na tabela.
	* Essa fun��o tamb�m incrementa a quantidade de elementos
	* na tabela (vari�vel tamanho).
	**/
	void inserir(Chave c, Valor v) {
		//IMPLEMENTAR
		this->tamanho++;

		if (load_factor() >= 1.0)
			aumentaArray();

		inserir(c, v, this->tabela);
	}

	/**
	* Essa fun��o retorna o fator de carga da Tabela Hash.
	**/
	double load_factor() {
		//IMPLEMENTAR
		return this->tamanho / (double)this->qtde_buckets;
	}

	/**
	* H� apenas um valor associado a uma chave.
	* Essa fun��o retorna esse valor, caso a chave exista.
	* Se a chave n�o existir a fun��o retorna NULL.
	* Lembre-se: em caso de colis�o, � preciso navegar
	* no bucket (lista ligada) para ter certeza se a chave
	* existe ou n�o.
	**/
	Valor getValor(Chave chave) {
		//IMPLEMENTAR
		int indexBucket = obterIndexBucket(chave, this->qtde_buckets); // O(1)

		Tupla<Chave, Valor>* tupla = this->tabela[indexBucket];

		while (tupla->getChave() != chave)
		{
			if (tupla->getProx() == NULL)
				//return NULL;
				return 0;
			else
				tupla = tupla->getProx();
		}

		return tupla->getValor();
	}

	/**
	* Essa fun��o retorna true caso a chave exista,
	* false caso contr�rio.
	* Lembre-se: em caso de colis�o, � preciso navegar
	* no bucket (lista ligada) para ter certeza se a chave
	* existe ou n�o.
	**/
	bool contemChave(Chave chave) {
		//IMPLEMENTAR
		int indexBucket = obterIndexBucket(chave, this->qtde_buckets);
		if (this->tabela[indexBucket] == NULL)
			return false;
		Tupla<Chave, Valor> elem_no_bucket = *(this->tabela[indexBucket]);

		while (elem_no_bucket.getChave() != chave)
		{
			if (elem_no_bucket.getProx() == NULL)
				return false;
			else
				elem_no_bucket = *(elem_no_bucket.getProx());
		}

		return true;
	}

	/**
	* Essa fun��o retorna um vetor com todas as chaves
	* j� inseridas na tabela.
	**/
	vector<Chave> getChaves() {
		//IMPLEMENTAR
		vector<Chave> chaves;

		for (int i = 0; i < this->qtde_buckets; i++)
		{
			if (this->tabela[i] == NULL)
				continue;

			Tupla<Chave, Valor>* tupla = this->tabela[i];
			do
			{
				chaves.push_back(tupla->getChave());
				tupla = tupla->getProx();
			} while (tupla != NULL);
		}

		return chaves;
	}

	/**
	* Essa fun��o desaloca os n�s previamente alocados, e muda
	* o tamanho do array de tuplas para 8.
	**/
	void clear() {
		//IMPLEMENTAR
		vector<Chave> chaves = getChaves();

		for (Chave c : chaves)
			remover(c);

		reset_tabela();
	}

	/**
	* H� apenas um n� associado com uma mesma chave.
	* Essa fun��o remove esse n� da tabela, caso a chave exista.
	* Se a chave n�o existir a fun��o n�o faz nada.
	* Lembre-se: em caso de colis�o, � preciso navegar
	* no bucket (lista ligada) para ter certeza se a chave
	* existe ou n�o.
	* Dica: olhar algoritmo de remo��o em lista ligada, pois
	* ap�s a remo��o de um n� a lista precisa permanecer �ntegra,
	* ou seja, naveg�vel.
	**/
	void remover(Chave chave) {
		//IMPLEMENTAR
		int index_bucket = obterIndexBucket(chave, this->qtde_buckets);

		Tupla<Chave, Valor>* tupla = this->tabela[index_bucket];

		if (tupla == NULL)
			return;
		// Para remover, basta fazer o pr�ximo do anterior ser igual ao pr�ximo do atual
		Tupla<Chave, Valor>* proximo;
		Tupla<Chave, Valor>* excluido;

		// Checa se a chave j� est� no primeiro
		if (tupla->getChave() == chave)
		{
			excluido = tupla;
			proximo = tupla->getProx();

			this->tabela[index_bucket] = proximo;
			delete excluido;

			this->tamanho--;
			return;
		}

		// Checa se a chave est� nos elementos seguintes
		while (tupla->getProx() != NULL)
		{
			if (tupla->getProx()->getChave() == chave)
			{
				excluido = tupla;
				proximo = tupla->getProx()->getProx();

				tupla->setProx(proximo);
				delete excluido;

				this->tamanho--;
				return;
			}

			tupla = tupla->getProx();
		}
	}

	/**
	* Essa fun��o retorna a quantidade de pares
	* que j� foram inseridos na Tabela Hash.
	**/
	int size() {
		return tamanho;
	}

	/**
	* Essa fun��o retorna o tamanho atual do
	* array usado para armazenar a Tabela Hash.
	**/
	int bucket_count() {
		return qtde_buckets;
	}
};