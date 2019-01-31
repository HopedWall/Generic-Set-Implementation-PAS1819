#include "set.h"
#include <iostream>
#include <string>
#include "voce.h"

struct equal_int {
	bool operator()(int a, int b) const {
		return a == b;
	}
};

struct equal_string {
	bool operator()(std::string a, std::string b) const {
		return a == b;
	}
};

struct equal_voce {
	bool operator()(voce a, voce b) const {
		return a==b;
	}
};

struct even_p {
	bool operator()(int a) const {
		return ((a % 2)==0);
	}
};

struct greater_p {
	bool operator()(std::string a) const {
		return (a.compare("b")>=0);
	}
};

struct longer_than_10 {
	bool operator()(voce a) const {
		return (a.ntel).length() > 10;
	}
};

void test_costruttori() {

	set<int,equal_int> s1;

	set<int,equal_int> s2(s1);

	set<int,equal_int> s3 = s1;

}

void test_add() {

	set<int,equal_int> s1;

	s1.add(1);

	s1.add(2);

	//s1.add(1); lancia eccezione

	//s1.add("Ciao"); invalid conversion

	s1.add((int) 0.5f);
}

void test_add_string() {

	set<std::string,equal_string> s1;

	s1.add("Ciao");

	s1.add("Prova");

	//s1.add("Ciao"); lancia eccezione

	std::cout << s1 << std::endl;
}

void test_remove() {
	set<int,equal_int> s1;

	s1.add(1);
	s1.add(2);
	s1.add(3);

	//s1.remove(5); lancia eccezione

	s1.remove(3);

	s1.remove(2);

	s1.remove(1);

	//s1.remove(1); lancia eccezione

}

void test_remove_string() {
	set<std::string,equal_string> s1;

	s1.add("Abc");
	s1.add("aBc");
	s1.add("a");

	//s1.remove(5); lancia eccezione

	s1.remove("aBc");

	s1.remove("a");

	s1.remove("Abc");

	//s1.remove(1); lancia eccezione

}

void test_operator_quadre() {
	set<int,equal_int> s1;

	s1.add(1);
	s1.add(2);
	s1.add(3);

	std::cout << s1[0] << " " << s1[1] << " " << s1[2] << std::endl;

	int a = 0;

	//a = s1[5]; lancia eccezione

	//a = s1[-1]; lancia eccezione

	//s1[2] = 3;
}

void test_iteratori() {
	set<int,equal_int> s1;

	s1.add(1);

	s1.add(2);

	s1.add(3);

	typename set<int,equal_int>::const_iterator i, ie;

	i = s1.begin();
	ie = s1.end();

	//std::cout << *i << std::endl;

	i++;

	//std::cout << *i << std::endl;

	i--;

	//std::cout << *i << std::endl;

	i = i+2;

	//std::cout << *i << std::endl;

	i = i-1;

	//std::cout << *i << std::endl;

	i = s1.begin();
	ie = s1.end();

	//std::cout << *ie << *i << std::endl;

	//std::cout<<"i-i=" << i-i << std::endl;

	std::cout <<"i-ie=" << i-ie << std::endl;

	std::cout <<"ie-i= " << ie-i << std::endl;

	std::cout << "i <= ie =" << (i <= ie) << std::endl;
	//std::cout << "i < ie" << (i < ie) << std::endl;
	std::cout << "i >= ie =" << (i >= ie) << std::endl;
	//std::cout << "i > ie" << i > ie << std::endl;

	std::cout << "i[2]=" << i[2] << std::endl;


}

void test_print() {

	set<int,equal_int> s1;

	std::cout << s1 << std::endl;

	s1.add(1);

	std::cout << s1 << std::endl;

	s1.add(2);

	std::cout << s1 << std::endl;

	s1.add(3);

	std::cout << s1 << std::endl;

	s1.remove(3);

	std::cout << s1 << std::endl;

	s1.remove(2);

	std::cout << s1 << std::endl;

	s1.remove(1);

	std::cout << s1 << std::endl;
}

void test_filter_out() {
	set<int,equal_int> s1, s2;
	s1.add(1);
	s1.add(2);
	s1.add(3);

	even_p e;
	s2 = filter_out(s1,e);

	std::cout << "s2 vale: " << s2 << std::endl;
}

void test_filter_out_string() {
	set<std::string,equal_string> s1, s2;
	s1.add("a");
	s1.add("b");
	s1.add("c");

	greater_p e;
	s2 = filter_out(s1,e);

	std::cout << "s2 vale: " << s2 << std::endl;
}

void test_operator_plus() {
	set<int,equal_int> s1, s2, s3, s4, s5;
	s1.add(1);
	s1.add(2);
	s1.add(3);

	s2.add(4);
	s2.add(3);
	s2.add(5);

	s3 = s1 + s2;

	std::cout << "s1 + s2 vale: " << s3 << std::endl;

	s2 = s2 + s2;

	std::cout << "s2 + s2 vale: " << s2 << std::endl;

	std::cout << "s4 + s2 vale: " << s4+s2 << std::endl;

	std::cout << "s4 + s4 vale: " << s4+s4 << std::endl;

}

void test_operator_plus_string() {
	set<std::string,equal_string> s1, s2, s3, s4, s5;
	s1.add("Ciao");
	s1.add("Prova1");
	s1.add("Prova2");

	s2.add("Prova1");
	s2.add("Ciao2");
	s2.add("Prova23");

	s3 = s1 + s2;

	std::cout << "s1 + s2 vale: " << s3 << std::endl;

	std::cout << "s2 + s1 vale: " << s2+s1 << std::endl;

	s2 = s2 + s2;

	std::cout << "s2 + s2 vale: " << s2 << std::endl;

	std::cout << "s4 + s2 vale: " << s4+s2 << std::endl;

	std::cout << "s4 + s4 vale: " << s4+s4 << std::endl;

}

void test_add_voce() {
	set<voce,equal_voce> rubrica_voci;
	voce a;
	voce b("Nome","Cognome","123456789");
	voce c("Nome1","Cognome1","42424242");
	rubrica_voci.add(a);
	rubrica_voci.add(b);
	rubrica_voci.add(c);

	std::cout << rubrica_voci << std::endl;
}

void test_remove_voce() {
	set<voce,equal_voce> rubrica_voci;

	voce a;
	voce b("Nome","Cognome","123456789");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e(b);
	rubrica_voci.add(a);
	rubrica_voci.add(b);
	rubrica_voci.add(c);
	rubrica_voci.add(d);
	//rubrica_voci.add(e);

	std::cout << rubrica_voci << std::endl;

	rubrica_voci.remove(a); //eliminazione in testa
	std::cout << rubrica_voci << std::endl;

	rubrica_voci.remove(d); //eliminazione in coda
	std::cout << rubrica_voci << std::endl;

	//rubrica_voci.remove(a); //eliminazione in testa
	//std::cout << rubrica_voci << std::endl;

	set<voce,equal_voce>::const_iterator i,ie;

	i = rubrica_voci.begin();
	ie = rubrica_voci.end();

	//std::cout << i[10] << std::endl;

	std::cout << i-ie << std::endl;
	for(;i!=ie;i++)
		std::cout << *i;
	std::cout << std::endl;

}

void test_filter_and_plus_voce() {
	set<voce,equal_voce> r1, r2, r3, r4;

	voce b("Nome","Cognome","12345678910112345");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e(b);

	r1.add(b);
	r1.add(c);
	r2.add(d);
	r2.add(e);

	std::cout << "r1" << r1 << std::endl;
	longer_than_10 ltt;
	r3 = filter_out(r1,ltt);
	std::cout << "r3" << r3 << std::endl;

	r4 = r2 + r3;
	std::cout << r2 << " " << r3 << std::endl;
	std::cout << r4 << std::endl;
}

void test_costruttore_iteratori_voce() {
	set<voce,equal_voce> r1;

	voce b("Nome","Cognome","12345678910112345");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e("Nome3","Cognome3","2039485");

	r1.add(b);
	r1.add(c);
	r1.add(d);
	r1.add(e);

	std::cout << "r1=" << r1 << std::endl;

	set<voce,equal_voce>::const_iterator i1=r1.begin(),ie1=r1.end();
	std::cout << "Prima i1++" << *i1 << std::endl;
	i1++;
	std::cout << "Dopo i1++" << *i1 << std::endl;

	//std::cout << "Prima ie1--" << *ie1 << std::endl;
	//ie1--;
	//std::cout << "Dopo ie1--" << *ie1 << std::endl;

	set<voce,equal_voce> r2(i1,ie1);
	std::cout << r2 << std::endl;

}

void test_iteratori_vari() {
	set<voce,equal_voce> r1;

	voce b("Nome","Cognome","12345678910112345");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e("Nome3","Cognome3","2039485");

	r1.add(b);
	r1.add(c);
	r1.add(d);
	r1.add(e);

	set<voce,equal_voce>::const_iterator i=r1.begin(),ie=r1.end(), i2;

	//operator+
	std::cout << "i: " << *i << " i+1: " << *(i+1) << "i: " << *i << std::endl;

	i2 = i;
	//operator++
	std::cout << "i: " << *i << "i++: " << *(i++) << std::endl;
	std::cout << "i2: " << *i2 << "++i: " << *(++i2) << std::endl;

}

void test_operator_quadre_voce() {
	set<voce,equal_voce> r1;

	voce b("Nome","Cognome","12345678910112345");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e("Nome3","Cognome3","2039485");

	r1.add(b);
	r1.add(c);
	r1.add(d);
	r1.add(e);

	std::cout << "r1 vale: " << std::endl;
	std::cout << r1 << std::endl;
	std::cout << r1[0] << std::endl;
	std::cout << r1[1] << std::endl;
	std::cout << r1[2] << std::endl;
	std::cout << r1[3] << std::endl;
	//std::cout << r1[4] << std::endl;
}

int main() {

	test_costruttori();
	test_add();
	test_remove();
	test_operator_quadre();
	test_iteratori();
	test_print();
	test_filter_out();

	try {
		test_operator_plus();
	} catch (...) {
	}


	test_add_string();
	test_remove_string();
	test_filter_out_string();

	try{
		test_operator_plus_string();
	} catch (...) {
	}

	test_add_voce();
	test_remove_voce();
	test_operator_quadre_voce();
	test_filter_and_plus_voce();
	test_costruttore_iteratori_voce();
	test_iteratori_vari();
	test_operator_quadre_voce();

	return 0;
}