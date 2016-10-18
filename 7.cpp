#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

冗余过度，太垃圾！判断正数int+正数int是否溢出的方法:结果为负数(符号位变为1)，则溢出
/*

class Solution{
	int reverse(int x) {
  		int i,temp,flag,res;
		double factor;
  		vector<int> num;
  		flag=0;
  		factor=1.0;//factor必须为double类型，否则当真实因子为100000000时，factor=10*真实因子，直接溢出
  		if(x<0){
  			flag=1;
  			x=0-x;
  		}
  		while(x>0){
  			temp=x%10;
  			num.push_back(temp);
			cout<<temp<<",,,"<<x<<endl;
			if(factor>INT_MAX){//判断a*b>INT_MAX的方法:a>INT_MAX/b(当a>0,b>0)，此时factor大小为真实因子*10，实际上为(真实因子>max/10)
				return 0;//本段代码用于判断x本身溢出的情况(因为只有x本身溢出时，factor才可能溢出)，实际上没有必要
			}
			else{
				factor*=10;
  				x/=10;
			}
			//cout<<factor<<endl;		
  		}
  		res=0;
  		factor=factor/10;
  		for(i=0;i<num.size();i++){
			//cout<<num[i]<<"..."<<factor<<endl;
			if(num[i]*factor>INT_MAX-res){//判断a+b>INT_MAX的方法：a>INTMAX-b
				cout<<"0"<<endl;
				return 0;
			}
			else{
				res+=(num[i]*factor);
  				factor/=10;
			}
  		}
  		if(flag==1){
  			res=0-res;
  		}
  		cout<<res<<endl;
  		return res;
    }
};
*/
class Solution{
public:
	int reverse(int x){
		int add,negative,res;
		negative=res=0;
		if(x<0){
			x=-x;
			negative=1;
		}
		while(x>0){
			add=x-(x/10)*10;
			cout<<res<<",,,"<<add<<endl;
			res=res*10+add;
			x/=10;
		}

		if(res<0){
			return 0;
		}
		else{
			if(negative==1){
				res=-res;
				cout<<res<<endl;
				return res;
			}
		}
	}
};

int main(){
	int num;
	num=-1234567;
    Solution sol=Solution();
	sol.reverse(num);
	return 0;
}