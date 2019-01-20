#include "set.h"
#include <iostream>

struct equal_int {
	bool operator()(int a, int b) const {
		return a == b;
	}
};

struct even_p {
	bool operator()(int a) const {
		return ((a % 2)==0);
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

	//std::cout <<"i-ie" << i-ie << std::endl;

	std::cout <<"ie-i= " << ie-i << std::endl;

	//std::cout << "i <= ie" << (i <= ie) << std::endl;
	//std::cout << "i < ie" << (i < ie) << std::endl;
	//std::cout << "i >= ie" << (i >= ie) << std::endl;
	//std::cout << "i > ie" << i > ie << std::endl;


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

int main() {
	/*
	test_costruttori();
	test_add();
	test_remove();
	test_operator_quadre();
	*/
	test_iteratori();
	/*
	test_print();
	test_filter_out();
	test_operator_plus();
	*/


	return 0;
}