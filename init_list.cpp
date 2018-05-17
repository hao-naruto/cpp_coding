/*
必须使用初始化列表进行初始化的四种情况：
1、初始化一个引用成员变量
2、初始化一个const成员变量
3、当调用基类的构造函数，且构造函数有一组参数
4、当调用成员对象的构造函数，且构造函数有一组参数

初始化列表初始化与在构造函数体内初始化有区别

*/
// 初始化一个引用成员变量、const成员变量
#include<iostream>
using namespace std;
class InitList{
    private:
        int i;
        const int ci;
        int &ri;
    public:
        // const或 引用 类型 必须使用 初始化列表 初始化
        InitList(int a):i(a),ci(a),ri(a){ }
};
int main(){
    return 0;
}

//当调用基类的构造函数，且构造函数有一组参数
#include<iostream>
using namespace std;
class Base{
    private:
        int base;
    public:
        Base(int b){
            base = b;
        }
};
class InitList:public Base{
    private:
        int i;
    public:
        // 父类有 有参构造函数 必须使用 初始化列表
        InitList(int b):Base(b){
        }
};
int main(){
    return 0;
}

//当调用成员对象的构造函数，且构造函数有一组参数
#include<iostream>
using namespace std;
class Base{
    private:
        int base;
    public:
        Base(int b){
            base = b;
        }
};
class InitList{
    private:
        int i;
        Base base;
    public:
        // 含有的成员对象 有参构造函数 必须使用 初始化列表
        InitList(int ii,Base b):i(ii),base(b){
          //  base = b;  // error!!!
        }
};
int main(){
    return 0;
}

//初始化列表初始化与在构造函数体内初始化有区别
#include<iostream>
using namespace std;
class Base{
    private:
        int base;
    public:
        Base(){
            base = 0;
            cout<<"Base constructor"<<endl;
        }
        Base(int i){
            base = i;
            cout<<"Base constructor"<<endl;
        }
        Base& operator=(int i){
            base = i;
            cout<<"operator="<<endl;
            return *this;
        }
        ~Base(){
            cout<<"~Base"<<endl;
        }
};
class InitList{
    private:
        int i;
        Base base;
    public:
        // 先初始化 base 再调用 赋值构造函数
        InitList(){
            i = 0;
            base = 0;
        }
        // 直接 调用赋值构造函数
       // InitList():i(0),base(0){ }
        ~InitList(){
            cout<<"~InitList"<<endl;
        }
};
int main(){
    InitList il;
    return 0;
}
