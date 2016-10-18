#include <iostream>
using namespace std;
class Solution {
public:
    int myAtoi(string str) {
  		int i,negative,res,temp;
  		if(str.compare("")==0){//str.compare(anotherstr)等同于strcmp(str,anotherstr)
  			cout<<"null"<<endl;//第一个非空序列为NULL的情形，此时str is empty
  			return 0;
  		}
  		i=negative=0;
		while(str[i]==' '&&i<str.size()){
			i++;
		}
		if(i==str.size()){//第一个非空序列为NULL的情形，此时str="     ..."
			return 0;
		}

		if(str[i]=='-'){
			negative=1;
			i++;
		}
		else if(str[i]=='+'){//有+号或无符号，该数都为正数
			i++;
		}
		else if(str[i]<'0'||str[i]>'9'){//第一个非空序列并非有效数字的情形
			return 0;
		}
		
		res=0;
  		while(i<str.size()){
			if(str[i]>='0'&&str[i]<='9'){
				if(res>INT_MAX/10){//判断res*10>INT_MAX
					//cout<<((negative==0)?INT_MAX:INT_MIN)<<endl;
					return (negative==0)?INT_MAX:INT_MIN;
				}
				else{
					if(res*10+str[i]-48>=res){//判断res*10+str[i]-'0'>INT_MAX的情形
						res=res*10+(str[i]-48);
						//cout<<res<<",,,"<<str[i]-'0'<<endl;
						i++;
					}
					else{
						//cout<<((negative==0)?INT_MAX:INT_MIN)<<endl;
						return (negative==0)?INT_MAX:INT_MIN;
					}
				}
			}
  			else{
				break;
  			}
  		}
  		if(negative==1){
  			res=-res;
  		}
  		cout<<res<<endl;
  		return res;
    }
};

int main(){
	int num;
	num=-1234567;
    Solution sol=Solution();
	sol.reverse(num);
	return 0;
}