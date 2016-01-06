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
template<typename T>
class Singleton
{
public:
	static T& Instance(){
		if(m_pInstance == NULL)
		{
			Lock lock;
			if(m_pInstance == NULL)
			{
				m_pInstance = new T();
				atexit(Destory);

			}
			return *m_pInstance;
		}
		return *m_pInstance;

	}
protected:
	Singleton(void){}
	~Singleton(void){}
private:
	Singleton(const Singleton& rhs){}
	Singleton& operator = (const Singleton& rhs){}

	void Destory()
	{
		if(m_pInstance != NULL)
			delete m_pInstance;
		m_pInstance = NULL;
	}
	static T* volatile m_pInstance;

};
template<typename T>
T* singleton<T>::m_pInstance = NULL;