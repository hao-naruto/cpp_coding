#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef struct sdshdr{
    //  记录buf数组中已使用的字节数
    int len;
    // 记录buf数组中为使用的字节数
    int free;
    // 用于保存字符串
    char buf[];
}SDS;
SDS* sdsnewlen(const char* init, size_t len){
    struct sdshdr* sh;
    sh = (struct sdshdr*)malloc(2*sizeof(int)+(len+1)*sizeof(char));
    // 内存分配失败，返回
    if (sh == NULL) return NULL;
    // 设置初始化长度
    sh->len = len;
    // 新 sds 不预留任何空间
    sh->free = 0;
    // 如果有指定初始化内容，将它们复制到 sdshdr 的 buf 中
    // T = O(N)
    if (len && init)
        memcpy(sh->buf, init, len);
    // 以 \0 结尾
    sh->buf[len] = '\0';
    // 返回 buf 部分，而不是整个 sdshdr
    return sh;
}
SDS* sdsnew(const char* init){
    size_t init_len = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, init_len);
}
void sdsfree(SDS* s){
    free(s);
}
class Dynamic_String{
    private:
        SDS* s;
        int* count;
    public:
        Dynamic_String(const char* str = ""){
            s = sdsnew(str);
            count = new int;
            *count = 1;
        }
        // 拷贝构造函数
        Dynamic_String(const Dynamic_String& ds){
            s = ds.s;
            count = ds.count;
            (*count)++;
            cout<<"copy count:"<<*count<<endl;
        }
        // 赋值构造函数
        Dynamic_String& operator=(const Dynamic_String& ds){
            cout<<"operator="<<endl;
            // 是否指向同一内存地址
            if(s != ds.s){
                // 原对象是否要释放
                if(--(*count) == 0){
                    sdsfree(s);
                    free(count);
                }
                s = ds.s;
                count = ds.count;
                (*count)++;
            }
            return *this;
        }
        ~Dynamic_String(){
            (*count)--;
            if(*count == 0){
                sdsfree(s);
                free(count);
                cout<<"delete ~"<<endl;
            }
        }
        //重载[]运算符
        char& operator[](int pos){
            CopyOnwrite(); //写时拷贝
            return s->buf[pos];
        }
        void CopyOnwrite(){
            if(*count > 1){ //需要拷贝
                cout<<"CopyOnWrite"<<endl;
                struct sdshdr* sh =(struct sdshdr*)malloc(2*sizeof(int)+sizeof(char)*strlen(s->buf));
                memcpy(sh->buf, s->buf, strlen(s->buf)+1);
                sh->free = s->free;
                sh->len =s->len;
                (*count)--;
                // 新的 空间 新的 引用计数器
                this->s = sh;
                count = new int(1);
            }
        }
};
int main(int argc, char *argv[]){
    Dynamic_String ds("abcdefg");
    Dynamic_String dst = ds;
    cout<<ds[1]<<endl;
    ds[1] = 'l';
    cout<<ds[1]<<endl;
    cout<<dst[1]<<endl;
   // cout<<sizeof(ds)<<endl;
    return 0;
}
/*

*/
