#ifndef SET_H
#define SET_H

#include <ostream>	 // ostream
#include <algorithm> // swap
#include <iterator>  // std::forward_iterator_tag
#include <cstddef>   // std::ptrdiff_t

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

	bool is_in_set(T val) const {
		nodo *tmp = _head;
		bool is_in = false;

		while(tmp != 0 && is_in == false) {
			if (_equal(tmp->value, val))
				is_in = true;
			tmp = tmp->next;
		}

		return is_in;
	}

public:
	//Metodo fondamentale 1: costruttore di default
	set() : _head(0), _count(0) {}

	//Metodo fondamentale 2: copy constructor
	set(const set &other) : _head(0), _count(0) {
		//TODO
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

	void add(const T &value) {
		nodo *n = new nodo(value), *tmp = _head;

		if(_head == 0) {	//Primo elemento
			_head = n;
			_count = 1;
		} else {
			//Controllo che l'elemento non sia già stato inserito
			if(is_in_set(value))
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
			if(!is_in_set(value))
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
			//!!!
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			//!!!
		}

		// Operatore di iterazione pre-incremento
		const_iterator &operator++() {
			//!!!
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			//!!!
		}

		// Operatore di iterazione pre-decremento
		const_iterator &operator--() {
			//!!!
		}

		// Spostamentio in avanti della posizione
		const_iterator operator+(int offset) {
			//!!!
		}

		// Spostamentio all'indietro della posizione
		const_iterator operator-(int offset) {
			//!!!
		}

		// Spostamentio in avanti della posizione
		const_iterator& operator+=(int offset) {
			//!!!
		}

		// Spostamentio all'indietro della posizione
		const_iterator& operator-=(int offset) {
			//!!!
		}

		// Numero di elementi tra due iteratori
		difference_type operator-(const const_iterator &other) {
			//!!!
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			//!!!
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			//!!!
		}

		// Confronto
		bool operator>(const const_iterator &other) const {
			//!!!
		}


		bool operator>=(const const_iterator &other) const {
			//!!!
		}

		// Confronto
		bool operator<(const const_iterator &other) const {
			//!!!
		}


		// Confronto
		bool operator<=(const const_iterator &other) const {
			//!!!
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
std::ostream &operator<<(std::ostream &os, const set<T,E> &set) {
	typename set<T,E>::const_iterator i, ie;

	for(i=set.begin(), ie=set.end(); i!=ie; i++)
		os << *i << std::endl;

	return os;
}

template <typename T, typename E, typename P>
set &filter_out(set<T,E> &s, P pred) {
	set<T,E> result;
	typename olist<T,E,C>::const_iterator i, ie;

	for(i=ol.begin(), ie=ol.end(); i!=ie; i++)
		if(!pred(*i))
			result.add(*i);

	return result;
}

template <typename T, typename E>
set &operator+(set<T,E> &s1, set<T,E> &s2) {
	set<T,E> result;

	//qualcosa

	return result;
}

#endif