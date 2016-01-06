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
