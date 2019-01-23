#ifndef SET_H
#define SET_H

#include <ostream>	 // ostream
#include <algorithm> // swap
#include <iterator>  // std::forward_iterator_tag
#include <cstddef>   // std::ptrdiff_t
#include <iostream>

template <typename T, typename Eql>	//Eql necessario in quanto non tutte le classi potrebbero avere operator ==
class set {
private:
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
	//Metodo fondamentale 1: costruttore di default
	set() : _head(0), _count(0) {}

	//Metodo fondamentale 2: copy constructor
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

	//Metodo fondamentale 3: operator=
	set &operator=(const set &other) {
		//Controllo autoassegnamento
		if(&other != this) {
			set tmp(other);
			std::swap(tmp._head, _head);
			std::swap(tmp._count, _count);
		}
		return *this;
	}

	//Metodo fondamentale 4: distruttore
	~set() {
		clear();
	}

	bool contains(T val) const {
		nodo *tmp = _head;
		bool is_in = false;

		while(tmp != 0 && is_in == false) {
			if (_equal(tmp->value, val))
				is_in = true;
			tmp = tmp->next;
		}

		return is_in;
	}

	void add(const T &value) {
		nodo *n = new nodo(value), *tmp = _head;

		if(_head == 0) {	//Primo elemento
			_head = n;
			_count = 1;
		} else {
			//Controllo che l'elemento non sia già stato inserito
			if(contains(value))
				throw std::invalid_argument("Value is already in set");

			while(tmp->next != 0)
				tmp = tmp->next;

			tmp->next = n;
			n->prev = tmp;
			_count++;

		}

		return;
	}

	void remove(const T &value) {
		nodo *tmp = _head, *p = _head;
		bool removed = false;
		if(_head == 0) {	//Lista vuota, riguarda eccezione
			throw std::invalid_argument("List is empty");
		} else {

			//Controllo che l'elemento sia presente nella lista
			if(!contains(value))
				throw std::invalid_argument("Value is not in set");

			//Controllo che l'elemento da rimuovere non sia il primo
			if(_equal(_head->value, value)) {
				if(_head->next != 0) {		//head non e' l'unico elemento
					_head = _head->next;
					_head->prev = 0;
					_count--;
					removed = true;
				} else {					//head e' l'unico elemento
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
					_count--;
					removed = true;
				}
				p = p->next;
			}

		}
		return;
	}

	//Controlla SOLA LETTURA
	T operator[](int index) const {
		nodo *tmp = _head;
		unsigned int c = 0;

		if(index < 0)
			throw std::invalid_argument("Index should be >= 0");

		while(tmp != 0 && c != index){
			tmp = tmp->next;
			c++;
		}

		if(c != index)
			throw std::out_of_range("Not enough elements");

		return tmp->value;

	}

	template <typename IT>
	set(IT b, IT e) : _head(0), _count(0) {
		try {
			for(;b!=e;++b)
				insert(static_cast<IT>(*b));
		} catch (...) {
			clear();
			throw;
		}
	}

	unsigned int count() const {return _count;}

	void clear() {
		nodo *tmp = _head;

		while(tmp!=0) {
			nodo *next = tmp->next;
			delete tmp;
			tmp = next;
		}

		_count = 0;
	}

	//Forse inutile
	int get_position(T value) const {
		nodo *tmp = _head;
		int index = 0;

		if (!contains(value))
			throw std::invalid_argument("Value is not in set");

		while(tmp!=0 && value!=*tmp) {
			tmp = tmp->next;
			index++;
		}

		return index;
	}



	/* INIZIO ITERATOR */
	class const_iterator {

		//Creo un puntatore a nodo per poter navigare i dati
		// const in quanto non si possono modificare i dati

		const nodo *n = _head;

	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef const T*                 pointer;
		typedef const T&                 reference;


		const_iterator() : n(0) {}

		const_iterator(const const_iterator &other) : n(other.n) {}

		const_iterator& operator=(const const_iterator &other) {
			n = other.n;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return n->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(n->value);
		}

		// Operatore di accesso random
		reference operator[](int index) {
			int cont = 0;
			while(cont != index) {
				n = n->next;
				cont++;
			}
			return n->value;
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(n);
			n = n->next;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator &operator++() {
			n = n->next;
			return *this;
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp(n);
			n = n->prev;
			return tmp;
		}

		// Operatore di iterazione pre-decremento
		const_iterator &operator--() {
			n = n->prev;
			return *this;
		}

		// Spostamento in avanti della posizione
		const_iterator operator+(int offset) {
			const nodo *temp = n;
			int cont = 0;
			while(cont != offset) {
				temp = temp->next;
				cont++;
			}
			const_iterator tmp(temp);
			return tmp;
		}

		// Spostamento all'indietro della posizione
		const_iterator operator-(int offset) {
			const nodo *temp = n;
			int cont = 0;
			while(cont != offset) {
				temp = temp->prev;
				cont++;
			}
			const_iterator tmp(temp);
			return tmp;
		}

		// Spostamentio in avanti della posizione
		const_iterator& operator+=(int offset) {
			int cont = 0;
			while(cont != offset) {
				n = n->next;
				cont++;
			}
			return *this;
		}

		// Spostamentio all'indietro della posizione
		const_iterator& operator-=(int offset) {
			int cont = 0;
			while(cont != offset) {
				n = n->prev;
				cont++;
			}
			return *this;
		}

		// Numero di elementi tra due iteratori
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

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return (n==other.n);
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return (n!=other.n);
		}

		// Confronto
		bool operator>(const const_iterator &other) const {
			int diff = *this-other;
			if(diff>0)
				return true;
			else
				return false;
		}


		bool operator>=(const const_iterator &other) const {
			int diff = *this-other;
			if(diff>=0)
				return true;
			else
				return false;
		}

		// Confronto
		bool operator<(const const_iterator &other) const {
			int diff = *this-other;
			if(diff<0)
				return true;
			else
				return false;
		}

		// Confronto
		bool operator<=(const const_iterator &other) const {
			int diff = *this-other;
			if(diff<=0)
				return true;
			else
				return false;
		}

	private:
		//Dati membro

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class set; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const nodo *nn) : n(nn) {}

	}; // classe const_iterator

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_head);
	}

	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(0);
	}


}; //set

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

template <typename T, typename E, typename P>
set<T,E> filter_out(set<T,E> &s, P pred) {
	set<T,E> result;
	typename set<T,E>::const_iterator i, ie;

	for(i=s.begin(), ie=s.end(); i!=ie; i++)
		if(!pred(*i))
			result.add(*i);

	return result;
}

//IDEA: visto che ogni elemento viene inserito esattamente una volta nell'insieme di arrivo
//mi basta controllare per ogni elemento che non sia gia' presente nel risultato
template <typename T, typename E>
set<T,E> operator+(set<T,E> &s1, set<T,E> &s2) {
	set<T,E> result;
	typename set<T,E>::const_iterator i1, ie1, i2, ie2;

	for(i1=s1.begin(), ie1=s1.end(); i1!=ie1; i1++)
		if(!result.contains(*i1))
			result.add(*i1);

	for(i2=s2.begin(), ie2=s2.end(); i2!=ie2; i2++)
		if(!result.contains(*i2))
			result.add(*i2);

	return result;
}

#endif