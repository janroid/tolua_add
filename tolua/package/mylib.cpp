#include "mylib.h"
#include <iostream>

Test::Test(int a, int b)
{
	this->a = a;
	this->b = b;
}

Test::~Test()
{

}

void Test::sayHello()
{
	std::cout << "hello world" << std::endl;
}

int Test::add()
{
	return this->a + this->b;
}

int Test::getA()
{
	return this->a;
}