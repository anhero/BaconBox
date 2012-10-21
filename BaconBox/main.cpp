#include <iostream>

#include "TestComponent.h"

using namespace BaconBox;

int main(int argc, const char * argv[]) {
	TestComponent * tc = new TestComponent();
	
	Component *c = tc;
	
	std::cout << tc->getId() << std::endl;
	std::cout << c->getId() << std::endl;
	
	delete tc;
	tc = NULL;
	
	c = new Component();
	
	std::cout << c->getId() << std::endl;
	
	delete c;
	c = NULL;
	
    return 0;
}

