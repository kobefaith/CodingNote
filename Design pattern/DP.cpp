#include<iostream>
using namespace std;

class SingleCore
{
public:
    virtual void Show()=0;
};
class SingleCoreA:public SingleCore
{
    public:
    void Show(){cout<<"Single Core A"<<endl;}
  
};
class SingleCoreB:public SingleCore
{
    public:
    void Show(){cout<<"single core B"<<endl;}
};
class MultiCore
{
    public:
    virtual viod Show()=0;
};
class MultiCoreA :public MultiCore
{
    public:
    void Show(){cout<<"Multi Core A"<<endl;}    
};
class MultiCoreB:public MultiCore
{
    public:
    void Show(){cout<<"Multi Core B"<<endl;}    
};
class CoreFactory
{
    public:
    virtual SingleCore* CreateSingleCore()=0;
    virtual MultiCore* CreateMultiCore()=0;
};
class FactoryA:public CoreFactory
{
    public:
    SingleCore* CreateSingleCore(){return new SingleCoreA();}
    MultiCore* CreateMultiCore(){return new MultiCoreA();}
};
class FactoryB:public CoreFactory
{
    public:
    SingleCore* CreateSingleCore(){return new SingleCoreB();}
    MultiCore* CreateMultiCore(){return new MultiCoreB();}
};

class Phone
{
    public:
    Phone(){}
    virtual ~Phone(){}
    virtual void showDecorate(){}
};
class iPhone :public Phone
{
    private:
    string m_name;
    public:
    iPhone(string name):m_name(name){}
    ~iPhone(){}
    void ShowDecorate(){cout<<m_name<<"的装饰"<<endl;}
};

class NokiaPhone:public Phone
{
    private:
    string m_name;
    public:
    NokiaPhone(string name):m_name(name){}
    ~NokiaPhone(){}
    void ShowDecorate(){cout<<m_name<<"的装饰"<<endl;}
    
}；
class DecoratePhone:public Phone
{
    private:
    Phone *m_phone;
    public:
    DecoratePhone(Phone *phone):m_phone(phone){}
    virtual void ShowDecorate(){m_phone->ShowDecorate();}
};
class DecoratePhoneA :public DecoratePhone
{
    public:
    DecoratePhoneA(Phone *phone):DecoratePhone(phone){}
    void ShowDecorate(){DecoratePhone::ShowDecorate();AddDecorate();}
    private:
    void AddDecorate(){cout<<"增加挂件"<<endl;}
};
class DecoratePhoneB:public DecoratePhone
{
    public:
    DecoratePhone(Phone *phone):DecoratePhone(phone){}
    void ShowDecorate(){DecoratePhone::ShowDecorate();AddDecorate();}
    private:
    void AddDecorate(){cout<<"屏幕贴膜"<<endl;}
}












