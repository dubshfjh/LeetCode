#include <iostream>
#include <vector>

using namespace std;

//INT_MIN/1 计算错误! 准确的说，任何把INT_MIN转化为正数的操作都会错误
class Solution {
public:
    int divide(int dividend, int divisor) {
        int positive,j;
        double i,res,temp,pos_dividend,pos_divisor;
        vector<double> temp_factor,temp_i;//temp_factor记录divisor,2*divisor,4*divisor,8*divisor....。temp_i对应存储因子1，2，4，8...
        positive=1;
        if((dividend>0&&divisor<0)||(dividend<0&&divisor>0)){
        	positive=-1;
        }
        //-dividend+dividend!=0意味着取值为INT_MIN,而用int接收的话，-INT_MIN=0!!!! 可以用double类型变量接收防止overflow
        pos_dividend=dividend;
		pos_dividend=(pos_dividend>=0)?pos_dividend:-pos_dividend;
		
		pos_divisor=divisor;
        pos_divisor=(pos_divisor>=0)?pos_divisor:-pos_divisor;

        //dividend=(dividend>=0)?dividend:(-dividend);
        //divisor=(divisor>=0)?divisor:(-divisor);
        if(pos_divisor==0&&pos_dividend!=0){//c++定义了0/0=0
        	return INT_MAX;
        }
        if(pos_dividend==0||pos_dividend<pos_divisor){
        	return 0;
        }
        i=1;
        temp=pos_divisor;
        temp_factor.push_back(temp);
        temp_i.push_back(i);
        while(temp<=pos_dividend){
        	temp+=temp;
        	temp_factor.push_back(temp);//在计算INT_MIN/1时，temp_factor可能要加入2147483648，所以temp_factor必须设置为vector<double>
        	i+=i;

        	temp_i.push_back(i);
        }
        temp_factor.pop_back();//最后一个temp=2^n*pos_divisor必然大于pos_dividend
        temp_i.pop_back();//删除最后一个2^n*pos_divisor中的因子n
        
        res=0;
        for(j=temp_factor.size()-1;j>=0;j--){
        	if(pos_dividend-temp_factor[j]>=0){
				//cout<<temp<<",,,"<<temp_factor[j]<<endl;
        		pos_dividend-=temp_factor[j];
        		res+=temp_i[j];
        	}
        }
		cout<<positive<<endl;
		
		if((res>INT_MAX&&positive==1)||(-res<INT_MIN&&positive==-1)){//由于res为最终结果的绝对值，所以res>INT_MAX或者-res<INT_MIN时，结果溢出
			res=INT_MAX;//PS:-INT_MIN=0!!!!!只能判断-res<INT_MIN，不能判断res<-INT_MIN
		}
		cout<<res-INT_MAX<<endl;
        return (positive==1)?res:-res;
    }
};

int main(){
    int dividend,divisor,res;
    dividend=-2147483648;
    divisor=1;
    Solution sol=Solution();
    res=sol.divide(dividend,divisor);
    cout<<res<<endl;
    return 0;
}


第二种优化做法：不使用vector存储中间值和中间因子，利用算数左移shift位(a<<shift==a*2^shift)

#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;
class Solution {
public:
    int divide(int dividend, int divisor){
    	long long int res;
    	res=getdivide(dividend,divisor);
    	if(res>INT_MAX||res<INT_MIN){
    		return INT_MAX;//overflow
    	}
    	return res;
    }

    long long int getdivide(long long dividend,long long divisor){
    	int positive=1;
    	int shift=0;
    	long long res=0;
    	long long temp=1;//temp记录因子1,2,4,8,16;shift记录左移位数
    	if(divisor==0&&dividend!=0){
    		return INT_MAX;
    	}
    	if(dividend==0){
    		return 0;
    	}
    	if((dividend<0)^(divisor<0)==1){//a<0和b<0为不相等真值时，^取真值为1
    		positive=0;
    	}

    	dividend=abs(dividend);
    	divisor=abs(divisor);

    	while(dividend>=divisor){
    		shift=0;
    		temp=1;
    		while(dividend>(divisor<<shift)){//找到最接近而且>=divisor的一个数,其因子为temp
    			shift++;
    			temp=temp<<1;
    		}

    		if(dividend==temp){
    			res+=temp;
    			break;
    		}
    		else{//dividend<(divisor<<shift)
    			temp>>=1;
    			shift--;
    		}
    		res+=temp;
    		dividend-=(divisor<<shift);
    	}
    	cout<<positive<<",,,"<<res<<endl;
    	return (positive==1)?res:-res;
    }
};

int main(){
    int dividend,divisor,res;
    dividend=2147483648;
    divisor=1;
    Solution sol=Solution();
    res=sol.divide(dividend,divisor);
    cout<<res<<endl;
    return 0;
}