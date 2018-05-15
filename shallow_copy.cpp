/*
浅拷贝实例
*/
#include<iostream>
using namespace std;
class String{
    private:
        int *str;
    public:
	String(){
            str = new int;	
	}
        int getStr(){
	    cout<<str<<endl;
            return *str;
        }
        void setStr(int s){        
            *str = s;
        }
        ~String(){
            delete str;
        }
};
int main(){
    String str;
    int a = 5;
    str.setStr(a);
    cout<<str.getStr()<<endl;
    String b;
    b = str;
    cout<<b.getStr()<<endl;
    b.setStr(10);
    cout<<str.getStr()<<endl;
    cout<<b.getStr()<<endl;
    return 0;
}
