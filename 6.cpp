#include <iostream>
#include <string>
using namespace std;

//运用String数组，可以Accept
class Solution {
public:
    string convert(string s, int numRows) {
        int i,j,len;
        string result;
        string str[1000];
        for(i=0;i<numRows;i++){
            str[i]="";
        }
        i=0;
        len=s.length();
        while(i<len){
            for(j=0;j<numRows&&i<len;j++){//先从上到下写0 to n-1行 
                str[j]+=s[i];
                //cout<<str[j]<<endl;;
                i++;
            }
            for(j=numRows-2;j>=1&&i<len;j--){//再从下到上写n-2 to 1行
                str[j]+=s[i];
                //cout<<str[j]<<endl;
                i++;
            }
        }
        result="";
        for(j=0;j<numRows;j++){
            result+=str[j];
            //cout<<str[j]<<endl;
        }
        //cout<<result<<endl;
        return result;
    }
};

//放弃string数组，直接计算导出字符串中index_j 和 "之字形"字符串数组中index_i的数学关系
class Solution {
public:
   string convert(string s, int numRows) {
        int i,j,id,len,odd;//id为“之字形”字符串中的index
        string res="";
        len=s.length();
        if(numRows<2){
            return s;
        }
        id=0;//第一行和最后一行单独算，id初值不一样，但都是id+=2*(num-1);中间的num-2行，则是id+=2*(num-1-i)
        while(id<len){//先加完第一行的全部字符进入字符串
            res+=s[id];
            id+=2*(numRows-1);
        }
        for(i=1;i<=numRows-2;i++){
            id=i;
            if(id>=len){
                break;
            }
            res+=s[id];//加上第1列
            odd=0;//第1列之后，开始为偶数列，然后为奇数列，依次循环
            while(id<=len){
                if(odd==0){
                    id+=2*(numRows-i-1);
                    if(id<len){
                        res+=s[id];
                    }
                    odd=1;
                }
                if(odd==1){
                    id+=2*i;
                    if(id<len){
                        res+=s[id];
                    }
                    odd=0;
                }   
            }
            
        }
        id=numRows-1;
        while(id<len){
            res+=s[id];
            id+=2*(numRows-1);
        }
        cout<<res<<endl;
        return res;
    }
};


