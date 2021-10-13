/* DCA0209 - ALGORITMOS E ESTRUTURAS DE DADOS II 
Desenvolvido por Hadênia Rodrigues
Tabela Hash*/

#include <iostream>
#include <vector>
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
	//qtdade de elementos já inseridos na tabela hash
	int tamanho;

	/*DONE*
		* Função para inserir a tupla <c,v> na tabela.
		* É preciso calcular o código hash a partir da chave c.
		* Em seguida, usamos qtde_buckets para descobrir o índice
		* dessa tupla. Prestar atenção na alocação de tupla quando
		* há colisões. A função hash às vezes retorna valores
		* negativos: use abs() para evitar índices negativos.
	**/
	void inserir(Chave c, Valor v, Tupla<Chave, Valor>** tabela) {
	
		size_t hashchave = hash<Chave>{}(c);
		int index = hashchave % qtde_buckets;

		Tupla<Chave, Valor>* tupla = new Tupla<Chave, Valor>(c, v);
		tupla->setProx(NULL);

		if (tabela[index] == NULL) {
			tabela[index] = tupla;
		} else {
			Tupla<Chave, Valor>* front = tabela[index];

			while (front->getProx() != NULL) {
				if (front->getChave() == c) {
						return;
				}
				front = front->getProx();
			}
			front->setProx(tupla);
		}
	}

	/*DONE*
		* Função para aumentar o tamanho do array quando o
		* fator de carga for >= 1. O tamanho do array
		* (qtde_buckets) deve ser multiplicado por 8 para
		* que essa operação seja feita com pouca frequência.
		* Por fim, precisamos reposicionar as tuplas, considerando
		* que a posição nesse novo array com maior tamanho
		* será diferente.
		**/
	void aumentaArray() {
		if (load_factor() < 1) return;

		int ant_buckets = qtde_buckets;
		qtde_buckets = qtde_buckets * 8;
		Tupla<Chave, Valor>** new_table = new Tupla<Chave, Valor>*[qtde_buckets]();

		for (int i = 0; i < ant_buckets; i++) {
			if (tabela[i] != NULL) {
				Tupla<Chave, Valor>* front = tabela[i];
				while (front != NULL) {
					inserir(front->getChave(), front->getValor(), new_table);
					front = front->getProx();
				}
			}
		}

		delete[] tabela;
		tabela = new_table;
	}

   public:
	/*DONE*
		* Inicializar o array de tuplas com capacidade = qtde_buckets.
		* Lembrar de setar todas as posições do array inicializado
		* para NULL.
		**/
	TabelaHash() {
		qtde_buckets = 8;
		tamanho = 0;

	 tabela = (TabelaHash tabela*)malloc(sizeof(TabelaHash tabela));
	

		tabela = new Tupla<Chave, Valor>*[qtde_buckets]();
		for (int i = 0; i < qtde_buckets; i++)
			tabela[i] = NULL;
	}

	/*DONE*
		* Essa é a função pública que nos permite inserir
		* uma tupla <c,v> na tabela. Nessa função nós
		* verificamos se é preciso aumentar o array de acordo
		* com o load factor. Essa função pode reusar sua versão
		* sobrecarregada para inserir a tupla na tabela.
		* Essa função também incrementa a quantidade de elementos
		* na tabela (variável tamanho).
		**/
	void inserir(Chave c, Valor v) {
		tamanho++;
		if (load_factor() >= 1)
			aumentaArray();

		inserir(c, v, tabela);
	}

	/*DONE*
		* Essa função retorna o fator de carga da Tabela Hash.
		**/
	double load_factor() {
        return (double)tamanho / (double)qtde_buckets;
	}

	/*DONE*
		* Há apenas um valor associado a uma chave.
		* Essa função retorna esse valor, caso a chave exista.
		* Se a chave não existir a função retorna NULL.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
	Valor getValor(Chave chave) {
		size_t hashchave = hash<Chave>{}(chave);
		int index = hashchave % qtde_buckets;

		if (tabela[index] != NULL) {
			Tupla<Chave, Valor>* front = tabela[index];
			while (front->getChave() != chave) {
				if (front->getProx() == NULL) 
					return 0;
				front = front->getProx();
			}
			return front->getValor();
		}

		return 0;
	}

	/*DONE*
		* Essa função retorna true caso a chave exista,
		* false caso contrário.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
	bool contemChave(Chave chave) {
	
		size_t hashchave = hash<Chave>{}(chave);
		int index = hashchave % qtde_buckets;

		if (tabela[index] != NULL) {
			Tupla<Chave, Valor>* front = tabela[index];
			while (front->getChave() != chave) {
				if (front->getProx() == NULL) {
					return false;
				}
				front = front->getProx();
			}
			return true;
		}

		return false;
	}

	/*DONE*
		* Essa função retorna um vetor com todas as chaves
		* já inseridas na tabela.
		**/
	vector<Chave> getChaves() {
		vector<Chave> chaves;

		for (int i = 0; i < qtde_buckets; i++) {
			if (tabela[i] != NULL) {
				Tupla<Chave, Valor>* front = tabela[i];
				while (front != NULL) {
					chaves.push_back(front->getChave());
					front = front->getProx();
				}
			}
		}

		return chaves;
	}

	/*DONE*
		* Essa função desaloca os nós previamente alocados, e muda
		* o tamanho do array de tuplas para 8.
		**/
	void clear() {
		for (int i = 0; i < qtde_buckets; i++){
			Tupla<Chave, Valor>* front = tabela[i];
			while (front != NULL){
				Tupla<Chave, Valor>* tp = front;
			//	delete front; 
			//	front = tp->getProx();
				front = tp->getProx();
				delete tp;
			}
			tabela[i] = NULL;
		}

		delete[] tabela;

		qtde_buckets = 8;
		tamanho = 0;

		tabela = new Tupla<Chave, Valor>*[qtde_buckets]();
		for (int i = 0; i < qtde_buckets; i++)
			tabela[i] = NULL;
	}

	/*DONE*
		* Há apenas um nó associado com uma mesma chave.
		* Essa função remove esse nó da tabela, caso a chave exista.
		* Se a chave não existir a função não faz nada.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		* Dica: olhar algoritmo de remoção em lista ligada, pois
		* após a remoção de um nó a lista precisa permanecer íntegra,
		* ou seja, navegável.
		**/
	void remover(Chave chave) {

		size_t hashchave = hash<Chave>{}(chave);
		int index = hashchave % qtde_buckets;


		if (tabela[index] != NULL) {
			Tupla<Chave, Valor>* front = tabela[index];
			Tupla<Chave, Valor>* ant = NULL;

			while (front->getChave() != chave) {
				ant = front;
				front = front->getProx();
				if (front == NULL) {
					return;
				}
			}

			if (ant == NULL) {
				tabela[index] = front->getProx();
			} else {
				ant->setProx(front->getProx());
			}
			tamanho--;
			delete front;
		}
	}

	/**
		* Essa função retorna a quantidade de pares
		* que já foram inseridos na Tabela Hash.
		**/
	int size() {
		return tamanho;
	}

	/**
		* Essa função retorna o tamanho atual do
		* array usado para armazenar a Tabela Hash.
		**/
	int bucket_count() {
		return qtde_buckets;
	}

};