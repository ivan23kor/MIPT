/*#include <iostream>

int i;

struct A
{
	~A()
	{
		i = 10;
	}
};

int& foo()
{
	i = 3;
	A ob;
	return i;
}

int main(int argc, char const *argv[])
{
	std::cout << foo() << std::endl;
	return 0;
}*/

/*#include <iostream>

class Base
{
	virtual void method() { std::cout << "From Base" << std::endl; };
public:
	Base() { std::cout << "Base ctor" << std::endl; };
	virtual ~Base() { method(); };
	void baseMethod() { method(); };
};

class A : public Base
{
public:
	A() { std::cout << "A ctor" << std::endl; };
	void method() { std::cout << "From A" << std::endl; };
	~A() { method(); };
};

int main(int argc, char const *argv[])
{
	Base* base = new A;
	base->baseMethod();
	delete base;

	return 0;
}

#include <iostream>

void f( int& a )
{
	a++;
}

int main(int argc, char const *argv[])
{
	int k = 0;
	f( k );
	std::cout << k << std::endl;
	return 0;
}*/

/*#include <cstdlib>
#include <iostream>
 
using std::cout;
using std::endl;
 
struct A
{
  virtual ~A() {}
 
  virtual void foo() const { cout << "A::foo()" << endl; }
  virtual void bar() const { cout << "A::bar()" << endl; }
  void baz() const { cout << "A::baz()" << endl; }
};
 
struct B : public A
{
  void foo() const { cout << "B::foo()" << endl; }
  void bar() const { cout << "B::bar()" << endl; }
  void baz() const { cout << "B::baz()" << endl; }
};
 
struct C : public B
{
  virtual void foo() const { cout << "C::foo()" << endl; }
  virtual void bar() const { cout << "C::bar()" << endl; }
  void baz() const { cout << "C::baz()" << endl; }
};
 
int main()
{
  cout << "pA is B:" << endl;
  A * pA = new B;
  pA->foo();
  pA->bar();
  pA->baz();
  delete pA;
 
  cout << "\npA is C:" << endl;
  pA = new C;
  pA->foo(); pA->bar(); pA->baz();
  delete pA;
 
  return EXIT_SUCCESS;
}*/