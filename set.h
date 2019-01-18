#ifndef SET_H
#define SET_H

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

	bool is_in_set(T val) {
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
		nodo *n = new nodo(value);

		if(_head == 0) {	//Primo elemento
			_head = n;
			_count = 1;
		} else {
			//Controllo che l'elemento non sia già stato inserito
			if(is_in_set(value))
				throw std::invalid_argument("Value is already in set");

			n->next = _head;
			_head = n;
			_count++;
		}

		return;
	}

	void remove(const T &value) {
		nodo *tmp = _head, *p = _head;
		bool removed = false;
		if(_head == 0) {	//Lista vuota
			throw std::exception("List is empty")
		} else {

			//Controllo che l'elemento sia presente nella lista
			if(!is_in_set(value))
				throw std::invalid_argument("Value is not in set");

			while(tmp!=0 && removed == false) {
				if(_equal(tmp->value, value)) {
					p->next = tmp->next;
					_count--;
					removed = true;
				}
				p = p->next;
				tmp = tmp->next;
			}
		}
		return;
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
};

#endif