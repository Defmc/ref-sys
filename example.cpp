#include <iostream>
#include "ref_header_only.hpp"

int main(int argc, char* argv[]){
	TinyRef<int> a(new int(0));
	TinyRef<int> b = a;

	*a.operator->() += 10;

	std::cout << "a and b's value: " << *b.operator->() << std::endl;
	*b.operator->() -= 5;
	std::cout << "a and b's value now: " << *a.operator->() << std::endl;

	return 0;
}