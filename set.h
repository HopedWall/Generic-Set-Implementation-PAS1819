#ifndef SET_H
#define SET_H

#include <ostream>	 // ostream
#include <algorithm> // std::swap
#include <iterator>  // std::forward_iterator_tag
#include <cstddef>   // std::ptrdiff_t

/**
		Classe che definisce un set, ovvero un insieme (dal punto di vista matematico).
		A livello di implementazione, un set è rappresentato come una lista doppia in cui
		ad ogni nodo è associato un elemento di un tipo generico T, e in cui non compaiono
		elementi ripetuti (si utilizza un funtore Eql per verificare questa proprietà).
*/

template <typename T, typename Eql>	//Eql necessario in quanto non tutte le classi potrebbero avere operator ==
class set {
private:
	/**
		Struct che rappresenta il singolo nodo della lista. Essendo una lista doppia, oltre al valore
		dell'elemento, sono presenti dei puntatori all'elemento precedente e al successivo.
		Il nodo iniziale ha prev = 0, e quello finale ha next = 0.
	*/
	struct nodo {
		T value;
		nodo *prev, *next;

		nodo() : next(0), prev(0) {}
		nodo(const T &v, nodo *p = 0, nodo *n = 0) : value(v), prev(p), next(n) {}
	};

	nodo *_head;
	unsigned int _count;
	Eql _equal;

public:
	/**
		Metodo fondamentale 1: costruttore di default
	*/
	set() : _head(0), _count(0) {}

	/**
		Metodo fondamentale 2: copy constructor
		@param &other il set di cui effettuare la copia
	*/
	set(const set &other) : _head(0), _count(0) {
		nodo *tmp = other._head;

		try {
			while(tmp!=0) {
				add(tmp->value);
				tmp = tmp->next;
			}
		} catch (...) {
			clear();
			throw;
		}
	}

	/**
		Metodo fondamentale 3: operator=
		@param &other il set da assegnare a this
	*/
	set &operator=(const set &other) {
		//Controllo autoassegnamento
		if(&other != this) {
			set tmp(other);
			std::swap(tmp._head, _head);
			std::swap(tmp._count, _count);
		}
		return *this;
	}

	/**
		Metodo fondamentale 4: distruttore
	*/
	~set() {
		clear();
	}

	/**
		Metodo che verifica se this contiene o meno un certo elemento
		@param val il valore da inserire
		@return true se il valore è contenuto in this, false altrimenti
	*/
	bool contains(const T val) const {
		nodo *tmp = _head;
		bool is_in = false;

		while(tmp != 0 && is_in == false) {
			if (_equal(tmp->value, val))
				is_in = true;
			tmp = tmp->next;
		}

		return is_in;
	}

	/**
		Metodo che aggiunge un elemento al set. Se l'elemento è già presente, lancia un'eccezione.
		@param &value il valore da inserire
	*/
	void add(const T &value) {
		nodo *n = new nodo(value), *tmp = _head;

		if(_head == 0) {	//Primo elemento
			_head = n;
			_count = 1;
		} else {
			//Controllo che l'elemento non sia già stato inserito
			if(contains(value))
				throw "Value is already in set";

			while(tmp->next != 0)
				tmp = tmp->next;

			tmp->next = n;
			n->prev = tmp;
			_count++;

		}

		return;
	}

	/**
		Metodo che rimuove un elemento dal set. Se l'elemento non è presente, lancia un'eccezione.
		@param &value il valore da rimuovere
	*/
	void remove(const T &value) {	//Controlla delete
		nodo *tmp = _head, *p = _head;
		bool removed = false;
		if(_head == 0) {	//Lista vuota, riguarda eccezione
			throw "List is empty";
		} else {

			//Controllo che l'elemento sia presente nella lista
			if(!contains(value))
				throw "Value is not in set";

			//Controllo che l'elemento da rimuovere non sia il primo
			if(_equal(_head->value, value)) {
				if(_head->next != 0) {		//head non e' l'unico elemento
					_head = _head->next;
					_head->prev = 0;
					delete tmp;
					_count--;
					removed = true;
				} else {					//head e' l'unico elemento
					delete _head;
					_head = 0;
					_count = 0;
					removed = true;
				}

			}

			while(tmp!=0 && removed == false) {
				tmp = tmp->next;
				if(_equal(tmp->value, value)) {
					p->next = tmp->next;
					if (tmp->next != 0)		//tmp non è l'ultimo elemento della lista
						(tmp->next)->prev = p;
					delete tmp;
					_count--;
					removed = true;
				}
				p = p->next;
			}

		}
		return;
	}

	/**
		Metodo che restituisce l'elemento in posizione index. Se l'indice non è valido Lancia un'eccezione.
		@param index l'indice dell'elemento da restituire
		@return l'elemento in posizione index
	*/
	//Controlla SOLA LETTURA
	T operator[](const int index) const {
		nodo *tmp = _head;
		unsigned int c = 0;

		if(index < 0)
			throw "Index should be >= 0";

		while(tmp != 0 && c != index){
			tmp = tmp->next;
			c++;
		}

		if(c != index)
			throw "Not enough elements";

		return tmp->value;

	}

	/**
		Metodo che crea un set a partire da due iteratori, che rappresentano l'inizio e la fine di un altro set.
		@param b l'iteratore di inizio
		@param e l'iteratore di fine
	*/
	template <typename IT>
	set(IT b, IT e) : _head(0), _count(0) {
		try {
			for(;b!=e;++b)
				add(static_cast<T>(*b));
		} catch (...) {
			clear();
			throw;
		}
	}

	/**
		Metodo che ritorna il numero di elementi del set.
		@return il numero di elementi del set.
	*/
	unsigned int count() const {return _count;}

	/**
		Metodo che svuota il set.
	*/
	void clear() {
		nodo *tmp = _head;

		while(tmp!=0) {
			nodo *next = tmp->next;
			delete tmp;
			tmp = next;
		}

		_count = 0;
	}

	/**
		Metodo che ritorna la posizione di un elemento del set.
		@param value il valore di cui si vuole sapere la posizione
		@return la posizione dell'elemento
	*/
	//Forse inutile
	int get_position(T value) const {
		nodo *tmp = _head;
		int index = 0;

		if (!contains(value))
			throw "Value is not in set";

		while(tmp!=0 && value!=*tmp) {
			tmp = tmp->next;
			index++;
		}

		return index;
	}



	/**
		Const iterator di tipo random-access.
	*/
	class const_iterator {

		//Creo un puntatore a nodo per poter navigare i dati
		// const in quanto non si possono modificare i dati

		const nodo *n;

	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef const T*                 pointer;
		typedef const T&                 reference;

		/**
			Costruttore di default.
		*/
		const_iterator() : n(0) {
		}

		/**
			Costruttore di copia.
			@param other const_iterator di cui effettuare la copia
		*/
		const_iterator(const const_iterator &other) : n(other.n) {}

		/**
			Operator = per assegnare un const_iterator ad un altro.
			@param other il const iterator che si vuole assegnare this
		*/
		const_iterator& operator=(const const_iterator &other) {
			n = other.n;
			return *this;
		}

		/**
			Distruttore.
		*/
		~const_iterator() {}

		/**
			Ritorna il dato riferito all'iteratore. (Dereferenziamento)
		*/
		reference operator*() const {
			return n->value;
		}

		/**
			Ritorna il puntatore al dato riferito dall'iteratore
		*/
		pointer operator->() const {
			return &(n->value);
		}

		/**
			Operatore di accesso random. Permette l'accesso all'elemento in posizione index.
			Se l'indice non è valido Lancia un'eccezione.
			@param index l'indice dell'elemento a cui si vuole accedere
		*/
		// Operatore di accesso random
		reference operator[](const int index) {
			int cont = 0;
			const nodo *temp = n;

			if(index < 0)
				throw "Index should be >= 0";

			while(temp!=0 && cont != index) {
				temp = temp->next;
				cont++;
			}

			if (cont != index)
				throw "Not enough elements";

			return temp->value;
		}

		/**
			Operatore di iterazione post-incremento.
		*/
		const_iterator operator++(int) {
			const_iterator tmp(n);
			n = n->next;
			return tmp;
		}

		/**
			Operatore di iterazione pre-incremento.
		*/
		const_iterator &operator++() {
			n = n->next;
			return *this;
		}

		/**
			Operatore di iterazione post-decremento.
		*/
		const_iterator operator--(int) {
			const_iterator tmp(n);
			n = n->prev;
			return tmp;
		}

		/**
			Operatore di iterazione pre-decremento.
		*/
		const_iterator &operator--() {
			n = n->prev;
			return *this;
		}

		/**
			Spostamento in avanti di offset posizioni. Lancia un'eccezione se lo spostamento non è possibile.
			@param offset il numero di posizioni di cui spostarsi
		*/
		const_iterator operator+(int offset) const {
			const nodo *temp = n;
			int cont = 0;
			while(cont != offset) {
				temp = temp->next;
				cont++;
			}
			const_iterator tmp(temp);
			return tmp;
		}

		/**
			Spostamento all'indietro di offset posizioni. Lancia un'eccezione se lo spostamento non è possibile.
			@param offset il numero di posizioni di cui spostarsi
		*/
		const_iterator operator-(int offset) const {
			const nodo *temp = n;
			int cont = 0;

			while(cont != offset) {
				temp = temp->prev;
				cont++;
			}
			const_iterator tmp(temp);
			return tmp;
		}

		/**
			Spostamento in avanti di offset posizioni. Lancia un'eccezione se lo spostamento non è possibile.
			@param offset il numero di posizioni di cui spostarsi
		*/
		const_iterator& operator+=(int offset) {
			int cont = 0;
			while(cont != offset) {
				n = n->next;
				cont++;
			}
			return *this;
		}

		/**
			Spostamento all'indietro di offset posizioni. Lancia un'eccezione se lo spostamento non è possibile.
			@param offset il numero di posizioni di cui spostarsi
		*/
		const_iterator& operator-=(int offset) {
			int cont = 0;
			while(cont != offset) {
				n = n->prev;
				cont++;
			}
			return *this;
		}

		/**
			Numero di elementi tra due iteratori. Può essere positivo (se this è più avanti di other),
			o negativo (se this è più indietro di other).
			@param other il const_iterator con cui confrontare this
			@return >0 se this è posizionato dopo other, <0 se this è posizionato prima di other, 0 se sono alla stessa posizione.
		*/
		difference_type operator-(const const_iterator &other) const {
			if(n == 0 && other.n == 0)
				return 0;
			else if (n==0)						//RIVEDERE
				return -(other-(*this));
			else {
				const nodo *tmp = n;
				int cont = 0;
				bool trovato = false;

				if(tmp == other.n)
					trovato=true;

				//Provo ad andare avanti
				while(tmp!=0 && trovato == false) {
					tmp = tmp->next;
					cont--;
					if(tmp==other.n)
						trovato = true;
				}

				if(trovato==false) {
					cont = 0;
					tmp = n;
				}

				//Provo ad andare indietro
				while(tmp!=0 && trovato == false) {
					tmp = tmp->prev;
					cont++;
					if(tmp==other.n)
						trovato = true;
				}

				return cont;
			}
		}

		/**
			Ritorna se due iteratori sono uguali (puntano allo stesso elemento) o meno.
			@param il const iterator da confrontare
			@return true se i due iteratori sono uguali, false se sono diversi
		*/
		bool operator==(const const_iterator &other) const {
			return (n==other.n);
		}

		/**
			Ritorna se due iteratori sono diversi (puntano ad elementi diversi) o meno.
			@param other il const_iterator da confrontare
			@return true se i due iteratori sono diversi, false se sono uguali
		*/
		bool operator!=(const const_iterator &other) const {
			return (n!=other.n);
		}

		/**
			Ritorna se this è posizionato dopo other o meno.
			@param other il const_iterator da confrontare
			@return true se this è posizionato dopo other, false se this è posizionato prima o alla stessa posizione.
		*/
		bool operator>(const const_iterator &other) const {
			int diff = *this-other;
			if(diff>0)
				return true;
			else
				return false;
		}

		/**
			Ritorna se this è posizionato dopo o alla stessa posizione di other, o meno.
			@param il const_iterator da confrontare
			@return true se this è dopo o alla stessa posizione di other, false se è posizionato prima.
		*/
		bool operator>=(const const_iterator &other) const {
			int diff = *this-other;
			if(diff>=0)
				return true;
			else
				return false;
		}

		/**
			Ritorna se this è posizionato prima di other o meno.
			@param other il const_iterator da confrontare
			@return true se this è posizionato prima di other, false se è alla stessa posizione o prima.
		*/
		bool operator<(const const_iterator &other) const {
			int diff = *this-other;
			if(diff<0)
				return true;
			else
				return false;
		}

		/**
			Ritorna se this è posizionato prima o alla stessa posizione di other, o meno.
			@param other il const_iterator da confrontare
			@return true se this è prima o alla stessa posizione di other, false se è posizionato dopo.
		*/
		bool operator<=(const const_iterator &other) const {
			int diff = *this-other;
			if(diff<=0)
				return true;
			else
				return false;
		}

	private:
		friend class set;

		/**
			Costruttore di copia.
			@param il nodo di cui ottenere una copia
		*/
		const_iterator(const nodo *nn) : n(nn) {}

	}; // classe const_iterator

	/**
		Ritorna un iteratore posizionato all'inizio del set.
	*/
	const_iterator begin() const {
		return const_iterator(_head);
	}

	/**
		Ritorna un iteratore posizionato alla fine del set.
	*/
	const_iterator end() const {
		return const_iterator(0);
	}


}; //set

/**
	Stampa tutti gli elementi del set.
*/
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, const set<T,E> &s) {
	typename set<T,E>::const_iterator i, ie;

	os << "{";
	for(i=s.begin(), ie=s.end(); i!=ie; i++) {
		os << *i;
		if(i+1 != ie)
			os << ", ";
	}
	os << "}";

	return os;
}

/**
	Ritorna un set di tutti gli elementi di un set che non soddisfano un predicato.
	@param s il set di partenza
	@param p il predicato con cui confrontare gli elementi del set
	@return il set di tutti gli elementi che non soddisfano il predicato
*/
template <typename T, typename E, typename P>
set<T,E> filter_out(set<T,E> &s, P pred) {
	set<T,E> result;
	typename set<T,E>::const_iterator i, ie;

	for(i=s.begin(), ie=s.end(); i!=ie; i++)
		if(!pred(*i))
			result.add(*i);

	return result;
}

/**
	Effettua l'unione di due insiemi. Se un elemento appare in entrambi gli insiemi, lancia un'eccezione.
	@param s1 il primo set
	@param s2 il secondo set
	@return il set dato dall'unione di s1 e s2
*/
template <typename T, typename E>
set<T,E> operator+(set<T,E> &s1, set<T,E> &s2) {
	set<T,E> result;
	typename set<T,E>::const_iterator i1, ie1, i2, ie2;

	for(i1=s1.begin(), ie1=s1.end(); i1!=ie1; i1++)
		if(s2.contains(*i1))
			throw "Element is present in both sets";
		else
			result.add(*i1);

	for(i2=s2.begin(), ie2=s2.end(); i2!=ie2; i2++)
		if(s1.contains(*i2))
			throw "Element is present in both sets";
		else
			result.add(*i2);

	return result;
}

#endif