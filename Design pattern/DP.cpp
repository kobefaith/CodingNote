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
#include<iostream>
#include<list>
#include<string>
using namespace std;

class Observer
{
public:
    Observer(){}
    virtual ~Observer(){}
    virtual void Update(){}
};

class Blog
{
public:
    Blog(){}
    virtual ~Blog(){}
    void Attach(Observer *observer){ m_observers.push_back(observer); }
    void Remove(Observer *observer){ m_observers.remove(observer); }
    void Notify(){
        list<Observer*>::iterator iter = m_observers.begin();
        for (; iter != m_observers.end(); iter++){
            (*iter)->Update();
        }
    }
    virtual void SetStatus(string s){ m_status = s; }
    virtual string GetStatus(){ return m_status; }
private:
    list<Observer*> m_observers;
protected:
    string m_status;

};

class BlogCSDN :public Blog
{
private:
    string m_name;
public:
    BlogCSDN(string name) :m_name(name){}
    ~BlogCSDN(){}
    void SetStatus(string s){ m_status = "CSDN:" + m_name + s; }
    string GetStatus(){ return m_status; }
};
class ObserverBlog :public Observer
{
private:
    string m_name;
    Blog *m_blog;
public:
    ObserverBlog(string name, Blog *blog) :m_name(name), m_blog(blog){}
    ~ObserverBlog(){}
    void Update(){
        string status = m_blog->GetStatus();
        cout << m_name << "----------" << status << endl;
    }
};
funtion Circle(){
    createjs.Shape.call(this);
    this.setCircleType = function(type){
        this._circleType = type;
        switch(type){
            case 1:
                this.setColor("#cccccc");
                break;
            case 2:
                this.setColor("#ff6600");
                break;
            case 3:
                this.setColor("#0000ff");
                break;                
        }
    }
    this.setColor = function(colorString){
        this.graphics.beginFill(colorString);
        this.graphics.drawCircle(0,0,25);
        this.graphics.endFill();
    }
    this.getCircleType = function(){
        return this._circleType;
    }
    this.setCircleType(1);
}
Circle.prototype = new createjs.Shape();
























