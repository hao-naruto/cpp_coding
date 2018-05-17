#include<iostream>
#include<time.h>
using namespace std;
class A{
    private:
        int a;
    public:
        A(){
            a = 0;
            cout<<"constructor aa"<<endl;
        }
        A(const A& a){
            cout<<"copy A"<<endl;
        }
        A operator=(const A& a1){
            a = a1.a;
            cout<<"operator="<<endl;
            return *this;
        }
        ~A(){
            cout<<"~ A"<<endl;
        }
};
// 临时对象 赋给 a 函数结束析构
void foo(A a){
    cout<<"foo"<<endl;
}
// 编译器做了优化   NRV 具名返回值优化
// 加不加 & 结果也不同
A bar(){
    cout<<"bar11"<<endl;
    A aa;
    cout<<"bar22"<<endl;
    return aa;
}
int main(){
    A a;
    foo(a);
    cout<<"---------"<<endl;

    A b = bar();
    cout<<"bar----------out"<<endl;
/*
    // 计时
    double duration;
	clock_t start, finish;
	start=clock();
	for(int i = 0;i < 1000;i++){
        A b;
        b = bar();
        cout<<"bar--out"<<endl;
	}
    finish=clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout<<duration<<endl;
*/
    return 0;
}
/*

编译器进行了优化：
运行结果：
constructor aa
copy A
foo
~A  //调用foo传参时 产生的临时对象
-----------
bar11     // 编译器的NRV优化
constructor aa
bar22
bar--out
~A  //main函数中的对象b
~A  //main函数中的对象a

*/


#include<iostream>
#include<time.h>
using namespace std;
class A{
    private:
        int a;
    public:
        A(){
            a = 0;
            cout<<"constructor aa"<<endl;
        }
        A(const A& a1){
            a = a1.a;
            cout<<"copy A"<<endl;
        }
        A operator=(const A& a1){
            a = a1.a;
            cout<<"operator="<<endl;
            return *this;
        }
        ~A(){
            cout<<"~ A"<<endl;
        }
        void setA(int aaa){
            a = aaa;
        }
};
// 临时对象 赋给 a 函数结束析构
void foo(A a){
    cout<<"foo"<<endl;
}
A bar(){
    cout<<"bar11"<<endl;
    A aa;
    aa.setA(1);
    cout<<"bar22"<<endl;
    return aa;
}
int main(){
    A a;
    foo(a);
    cout<<"---------"<<endl;

    A b;
    cout<<&b<<endl;
    // 此时为赋值构造 并不是拷贝构造  所以没有NRV优化
    b = bar();  //bar();
    cout<<&b<<endl;
    cout<<"bar----------out"<<endl;
/*
    // 计时
    double duration;
	clock_t start, finish;
	start=clock();
	for(int i = 0;i < 1000;i++){
        A b;
        b = bar();
        cout<<"bar--out"<<endl;
	}
    finish=clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout<<duration<<endl;
*/
    return 0;
}
/*

编译器未进行优化：
当函数需要返回一个对象的时候，
如果自己创建一个临时对象用户返回，
那么这个临时对象会消 耗一个构造函数（Constructor）的调用、
一个复制构造函数的调用（Copy Constructor）以及一个析构函数（Destructor）的调用的代价。

此时调用bar()函数没有优化
运行结果为：
constructor aa
copy A
foo
~A   //调用foo传参时 产生的临时对象
-----------
constructor aa
0x68fedc  //main函数中对象b的地址
bar11
constructor aa
bar22
operator=
copy A
~A  bar函数中的对象aa
~A  bar函数返回时产生的临时对象
x68fedc    //main函数中对象b的地址
bar----------------out
~A  main函数中的对象b
~A  main函数中的对象a
*/
