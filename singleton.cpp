#include<iostream>
using namespace std;

class Singleton
{
public:
	static Singleton& Instance()
	{
		static Singleton singleton;
		return singleton;

	}
private:
	Singleton(){};

};

template <typename T>
class Singleton
{
public:
	static T& Instance()
	{
		static T s_Instance;
		return s_Instance;
	}
protected:
	Singleton(void){}
	~Singleton(void){}
private:
	Singleton(const Singleton& rhs){}
	singleton& operator = (const Singleton& rhs){}
};
