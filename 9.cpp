#include <iostream>
#include <vector>
using namespace std;

注意1：cout全部注释掉！leetcode存在output exceeds limit这种错误！
注意2：负数不是回文数！本算法冗余，重写一个！
class Solution {
public:
    bool isPalindrome(int x){
    	int i,len,temp,temp_x;
		if(x<0){
			return false;//0-INT_MIN=INT_MIN
		}
		else{//x!=INT_MIN时
			len=0;
			if(x==0){
				len=1;
			}
			else{
				temp_x=x;
				while(temp_x>0){
					temp_x/=10;
					len++;
				}
				temp_x=x;
			}
			while(len>0){
				temp=x%10;
				len--;
				//cout<<"old: "<<temp_x<<endl;
				temp_x-=temp*pow(10.0,len);
				//cout<<"new: "<<temp_x<<endl;
				//cout<<"temp,,,"<<temp<<endl;
				//cout<<"temp_x,,,"<<temp_x<<endl;
				x/=10;
			}
			if(temp_x==0){
				//cout<<"true"<<endl;
				return true;
			}
			//cout<<"false"<<endl;
			return false;
		}			
    }
};


class Solution {
public:
    bool isPalindrome(int x){
    	int i,len,temp_x,left,right;
        if(x<0){
        	return false;
        }
        temp_x=x;
        len=1;
        while(x/10>0){
        	len*=10;
        	x/=10;
        }
        x=temp_x;
        left=right=0;
        while(x>0){
        	left=x/len;
        	right=x%10;
        	if(left!=right){//比较首尾
        		return false;
        	}
        	x=(x-(left*len)-right)/10;//去除首尾数字，/10可去除尾数0，ps:此时删除-right仍然正确，因为0/10=1/10=2/10=...
        	len/=100;//数字减少两位
        }
        return true;
    }
};

int main(){
	int num;
	num=-1234567;
    Solution sol=Solution();
	sol.isPalindrome(num);
	return 0;
}