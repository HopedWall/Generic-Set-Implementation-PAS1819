#include "set.h"
#include <iostream>

struct equal_int {
	bool operator()(int a, int b) const {
		return a == b;
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

int main() {
	test_costruttori();
	test_add();
	test_remove();
	test_operator_quadre();


	return 0;
}