class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
  		int i,flag,temp,size;
  		size=digits.size();
  		vector<int> res(size+1,0);//设置size+1位的res,第0位预留出来.示例：[9,9,9]--->[1,0,0,0]
  		if(size==0){
  			res[0]=1;
  			return res;
  		}
  		flag=0;
  		for(i=size-1;i>=0;i--){
  			temp=digits[i]+1+flag;
  			if(i<size-1){//只有尾数需要=digits[i]+flag+1
  			    temp--;
  			}
  			if(temp>=10){
  				res[i+1]=temp%10;
  				flag=1;//flag记录当前位超过10,实际上可以直接使用flag/=10归并>=10 and <10两种情况
  			}
  			else{
  			    flag=0;
  				res[i+1]=temp;
  			}
  		}
  		if(flag==1){//如果digits[0]+flag>=10，则预留出的最高位设置为1
  			res[0]=1;
  		}
  		else{//否则直接将res左移一位，覆盖掉取值为0的最高位，并且pop掉出现了2次的最后一位
  			for(i=0;i<res.size()-1;i++){
  				res[i]=res[i+1];
  			}
  			res.pop_back();
  		}
  		return res;
    }
};