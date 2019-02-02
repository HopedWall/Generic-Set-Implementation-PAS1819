#include "set.h"
#include <iostream>
#include <string>
#include "voce.h"
#include <cassert>

struct equal_int {
	bool operator()(int a, int b) const {
		return a == b;
	}
};

struct equal_float {
	bool operator()(float a, float b) const {
		return ((b-a) < 0.01);
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

	std::cout << "---test_costruttori---" << std::endl;

	set<int,equal_int> s1;

	set<int,equal_int> s2(s1);

	set<int,equal_int> s3 = s1;

	std::cout << "ok" << std::endl;

}

void test_add() {

	std::cout << "---test_add---" << std::endl;

	set<int,equal_int> s1;

	s1.add(1);

	s1.add(2);

	/*
	try {
		s1.add(1); //lancia eccezione
	} catch(...) {
		s1.clear();
	}
	*/

	//s1.add("Ciao"); invalid conversion (compilazione)

	s1.add((int)0.5f);

	assert(s1[0] == 1);
	assert(s1[1] == 2);
	assert(s1[2] == 0);

	std::cout << "ok" << std::endl;
}

void test_add_string() {

	std::cout << "---test_add_string---" << std::endl;

	set<std::string,equal_string> s1;

	s1.add("Ciao");

	s1.add("Prova");

	//s1.add("Ciao"); lancia eccezione

	//std::cout << s1 << std::endl;

	assert(s1[0] == "Ciao");
	assert(s1[1] == "Prova");

	std::cout << "ok" << std::endl;
}

void test_remove() {

	std::cout << "---test_remove---" << std::endl;

	set<int,equal_int> s1;

	s1.add(1);
	s1.add(2);
	s1.add(3);

	//s1.remove(5); lancia eccezione

	s1.remove(3);

	assert(s1[0] == 1);
	assert(s1[1] == 2);

	s1.remove(2);

	assert(s1[0] == 1);

	s1.remove(1);

	//s1.remove(1); lancia eccezione

	std::cout << "ok" << std::endl;
}

void test_remove_string() {

	std::cout << "---test_remove_string---" << std::endl;

	set<std::string,equal_string> s1;

	s1.add("Abc");
	s1.add("aBc");
	s1.add("a");

	//s1.remove(5); lancia eccezione

	s1.remove("aBc");

	assert(s1[0] == "Abc");
	assert(s1[1] == "a");

	s1.remove("a");

	assert(s1[0] == "Abc");

	s1.remove("Abc");

	//s1.remove(1); lancia eccezione

	std::cout << "ok" << std::endl;
}

void test_operator_quadre() {

	std::cout << "---test_operator_quadre---" << std::endl;

	set<int,equal_int> s1;

	s1.add(1);
	s1.add(2);
	s1.add(3);

	assert(s1[0] == 1);
	assert(s1[1] == 2);
	assert(s1[2] == 3);

	//std::cout << s1[0] << " " << s1[1] << " " << s1[2] << std::endl;

	//int a = 0;

	//a = s1[5]; lancia eccezione

	//a = s1[-1]; lancia eccezione

	//s1[2] = 3;

	std::cout << "ok" << std::endl;
}

void test_iteratori() {

	std::cout << "---test_iteratori---" << std::endl;

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

	std::cout << "ok" << std::endl;
}

void test_print() {

	std::cout << "---test_print---" << std::endl;

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

	std::cout << "ok" << std::endl;
}

void test_filter_out() {

	std::cout << "---test_filter_out---" << std::endl;

	set<int,equal_int> s1, s2;
	s1.add(1);
	s1.add(2);
	s1.add(3);

	even_p e;
	s2 = filter_out(s1,e);

	//std::cout << "s2 vale: " << s2 << std::endl;
	assert(s2[0] == 1);
	assert(s2[1] == 3);

	std::cout << "ok" << std::endl;
}

void test_filter_out_string() {

	std::cout << "---test_filter_out_string---" << std::endl;

	set<std::string,equal_string> s1, s2;
	s1.add("a");
	s1.add("b");
	s1.add("c");

	greater_p e;
	s2 = filter_out(s1,e);

	assert(s1[0] == "a");

	//std::cout << "s2 vale: " << s2 << std::endl;

	std::cout << "ok" << std::endl;
}

void test_operator_plus() {

	std::cout << "---test_operator_plus---" << std::endl;

	set<int,equal_int> s1, s2, s3;
	s1.add(1);
	s1.add(2);
	s1.add(3);

	s2.add(4);
	s2.add(3);
	s2.add(5);

	try {
		s3 = s1 + s2;
		//std::cout << "s1 + s2 vale: " << s3 << std::endl;
		assert(s3[0] == 1);
		assert(s3[1] == 2);
		assert(s1[2] == 3);
		assert(s1[4] == 4);
		assert(s1[5] == 5);

	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "ok" << std::endl;
}

void test_iterator_constructor_cast() {
	std::cout << "---test_iterator_constructor_cast---" << std::endl;

	set<float,equal_float> s1;
	s1.add(1.5);
	s1.add(2.7);
	s1.add(3.9);
	//std::cout << s1 << std::endl;
	set<float,equal_float>::const_iterator i=s1.begin(), ie=s1.end();
	set<int,equal_int> s2(i,ie);
	//std::cout << s2 << std::endl;
	assert(s2[0] == 1);
	assert(s2[1] == 2);
	assert(s2[2] == 3);

	std::cout << "ok" << std::endl;

}

void test_operator_plus_string() {

	std::cout << "---test_operator_plus_string---" << std::endl;

	set<std::string,equal_string> s1, s2, s3, s4, s5;
	s1.add("Ciao");
	s1.add("Prova1");
	s1.add("Prova2");

	s2.add("Prova1");
	s2.add("Ciao2");
	s2.add("Prova23");

	try {
		s3 = s1 + s2;

		std::cout << "s2 + s1 vale: " << s2+s1 << std::endl;

	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		s2 = s2 + s2;
		std::cout << "s2 + s2 vale: " << s2+s2 << std::endl;
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;
}

void test_add_voce() {

	std::cout << "---test_add_voce---" << std::endl;

	set<voce,equal_voce> rubrica_voci;
	equal_voce ev;

	voce a;
	voce b("Nome","Cognome","123456789");
	voce c("Nome1","Cognome1","42424242");
	rubrica_voci.add(a);
	rubrica_voci.add(b);
	rubrica_voci.add(c);

	std::cout << rubrica_voci << std::endl;

	assert(ev(rubrica_voci[0],a));
	assert(ev(rubrica_voci[1],b));
	assert(ev(rubrica_voci[2],c));

	std::cout << "ok" << std::endl;
}

void test_remove_voce() {

	std::cout << "---test_remove_voce---" << std::endl;

	set<voce,equal_voce> rubrica_voci;
	equal_voce ev;

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
	assert(ev(rubrica_voci[0],b));
	//std::cout << rubrica_voci << std::endl;

	rubrica_voci.remove(d); //eliminazione in coda
	assert(ev(rubrica_voci[1],c));
	//std::cout << rubrica_voci << std::endl;

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

	std::cout << "ok" << std::endl;

}

void test_filter_and_plus_voce() {

	std::cout << "---test_filter_and_plus_voce---" << std::endl;

	set<voce,equal_voce> r1, r2, r3, r4;
	equal_voce ev;

	voce b("Nome","Cognome","12345678910112345");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e(b);

	r1.add(b);
	r1.add(c);
	r2.add(d);
	r2.add(e);

	//std::cout << "r1" << r1 << std::endl;
	longer_than_10 ltt;
	r3 = filter_out(r1,ltt);
	//std::cout << "r3" << r3 << std::endl;
	assert(ev(r3[0],r1[1]));

	r4 = r2 + r3;
	//std::cout << r2 << " " << r3 << std::endl;
	//std::cout << r4 << std::endl;
	assert(ev(r4[0],r2[0]));
	assert(ev(r4[1],r2[1]));
	assert(ev(r4[2],r3[0]));

	std::cout << "ok" << std::endl;
}

void test_costruttore_iteratori_voce() {

	std::cout << "---test_costruttore_iteratori_voce---" << std::endl;

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

	std::cout << "ok" << std::endl;
}

void test_iteratori_vari() {

	std::cout << "---test_iteratori_vari---" << std::endl;

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

	std::cout << "ok" << std::endl;
}

void test_operator_quadre_voce() {

	std::cout << "---test_operator_quadre_voce---" << std::endl;

	set<voce,equal_voce> r1;
	equal_voce ev;

	voce b("Nome","Cognome","12345678910112345");
	voce c("Nome1","Cognome1","42424242");
	voce d("Nome2","Cognome2","129384701");
	voce e("Nome3","Cognome3","2039485");

	r1.add(b);
	r1.add(c);
	r1.add(d);
	r1.add(e);

	assert(ev(r1[0],b));
	assert(ev(r1[1],c));
	assert(ev(r1[2],d));
	assert(ev(r1[3],e));

	//std::cout << "r1 vale: " << std::endl;
	//std::cout << r1 << std::endl;
	//std::cout << r1[0] << std::endl;
	//std::cout << r1[1] << std::endl;
	//std::cout << r1[2] << std::endl;
	//std::cout << r1[3] << std::endl;
	//std::cout << r1[4] << std::endl;

	std::cout << "ok" << std::endl;
}

void test_eccezioni_add() {
	std::cout << "---test_eccezioni_add---" << std::endl;

	set<int,equal_int> s1;

	s1.add(1);
	s1.add(2);
	try {
		s1.add(1);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		s1.add(2);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;

}

void test_eccezioni_delete() {
	std::cout << "---test_eccezioni_delete---" << std::endl;

	set<int,equal_int> s1;

	s1.add(1);
	s1.add(2);
	try {
		s1.remove(3);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;

}

void test_eccezioni_operator() {
	std::cout << "---test_eccezioni_operator---" << std::endl;

	set<int,equal_int> s1, s2, s3;

	s1.add(1);
	s1.add(2);
	s2.add(1);
	try {
		s3 = s1 + s2;
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;

}

void test_eccezioni_add_voce() {
	std::cout << "---test_eccezioni_add_voce---" << std::endl;
	set<voce,equal_voce> rubrica_voci;

	voce b("Nome","Cognome","123456789");
	voce c("Nome1","Cognome1","42424242");
	rubrica_voci.add(b);
	rubrica_voci.add(c);

	try {
		rubrica_voci.add(b);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		rubrica_voci.add(c);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;
}

void test_eccezioni_delete_voce() {
	std::cout << "---test_eccezioni_delete_voce---" << std::endl;
	set<voce,equal_voce> rubrica_voci;

	voce b("Nome","Cognome","123456789");
	voce c("Nome1","Cognome1","42424242");
	rubrica_voci.add(b);
	rubrica_voci.add(c);

	rubrica_voci.remove(b);
	try {
		rubrica_voci.remove(b);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	rubrica_voci.remove(c);
	try {
		rubrica_voci.remove(c);
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;
}

void test_eccezioni_operator_voce() {
	std::cout << "---test_eccezioni_operator_voce---" << std::endl;
	set<voce,equal_voce> rv1, rv2, rv3;

	voce b("Nome","Cognome","123456789");
	voce c("Nome1","Cognome1","42424242");
	rv1.add(b);
	rv1.add(c);
	rv2.add(b);

	try {
		rv3 = rv1+rv2;
	} catch (set_exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "ok" << std::endl;
}

int main() {

	test_costruttori();
	test_add();
	test_remove();
	test_operator_quadre();
	test_iteratori();
	test_print();
	test_filter_out();
	test_operator_plus();
	test_iterator_constructor_cast();

	test_add_string();
	test_remove_string();
	test_filter_out_string();
	test_operator_plus_string();

	test_add_voce();
	test_remove_voce();
	test_operator_quadre_voce();
	test_filter_and_plus_voce();
	test_costruttore_iteratori_voce();
	test_iteratori_vari();
	test_operator_quadre_voce();

	test_eccezioni_add();
	test_eccezioni_delete();
	test_eccezioni_operator();

	test_eccezioni_add_voce();
	test_eccezioni_delete_voce();
	test_eccezioni_operator_voce();
	return 0;
}