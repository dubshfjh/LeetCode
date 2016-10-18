#include <iostream>
#include <cmath>
#include <limits.h>
using namespace std;
//123^123等一系列大数的结果与expected answer不一样，很是困惑
class Solution {
public:
    double myPow(double x, int n) {
    	int n_pos,flag;//flag==0：表示n为INT_MIN，此时-n将等于0
    	double res,tempn;
    	n_pos=flag=1;
        if(x==0 || n==0){
        	return 1;
        }
        if(n<0){
        	n_pos=0;
        	if(n==INT_MIN){
        	    flag=0;
        	    n=INT_MAX;
        	}
        	else{
        	    n=-n;
        	}
        }        
        res=binary_cal(x,n);
        if(flag==0){
            res*=x;
        }
        if(n_pos==0){
        	res=1/res;
        }
        return res;
    }

    double binary_cal(double x,int n){
    	if(n==0){
    		return 1.0;
    	}
    	else if(n==1){
    		return x; 
    	}
    	else{
    	    //return binary_cal(x,n/2)*binary_cal(x,n-n/2);
    	    
    		double temp=binary_cal(x,n/2);
    		cout<<n<<",,,"<<temp<<endl;
    		if(n%2==0){
    		   // cout<<"偶数："<<n<<",,,"<<temp*temp<<endl;;
    			return temp*temp;
    		}
    		else{
    		   // cout<<"奇数："<<n<<",,,"<<temp*temp*x<<endl;;
    			return temp*temp*x;
    		}
    		
    	}
    }
};