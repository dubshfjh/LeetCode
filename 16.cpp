#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

卧槽，审题啊！！！写了一半才发现题目不是要求输出"sum=target，而且相隔最近的3个数"
而是“找出3数之和，与target的大小最为接近的数！！！下面的代码文不对题，作废！”
/*
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int i,j,start,end,size,temp,minlen;
        vector<int> index;
        size=nums.size();
        for(i=0;i<size;i++){
        	index.push_back(i);//对nums中最新下标为i的项初始化，其原下标为i
        }
        for(i=0;i<size;i++){
        	for(j=i+1;j<size;j++){
        		if(nums[i]>nums[j]){
        			temp=nums[i];
        			nums[i]=nums[j];
        			nums[j]=temp;

        			temp=index[j];
        			index[j]=index[i];//i,j项互换后，最新下标为j的项,其原下标为index[i]
        			index[i]=temp;
        		}
        	}
        }

        minlen=-1;
        for(i=0;i<size;i++){
        	start=i+1;
        	end=size-1;
        	while(start<end){
        		temp=nums[start]+nums[end]+nums[i];
        		if(temp==target){
        			if(minlen==-1){

        			}
        		}
        	}
        }
    }
};
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target){
    	int i,size,start,end,sum,res,tempdis,mindis;
        sort(nums.begin(),nums.end());
        //unsigned int mindis;

        size=nums.size();//size<3时需要报错，但理论上长度应该必然>3吧？
		
        mindis=target-(nums[0]+nums[1]+nums[2]);//mindis是很可能超过INT_MAX的，所以可以任取nums中3点得到用于比较的初值
        if(mindis<0){
			mindis=-mindis;
		}
		for(i=0;i<size;i++){
        	start=i+1;
        	end=size-1;
        	while(start<end){
        		sum=nums[i]+nums[start]+nums[end];
				//cout<<nums[i]<<",,"<<nums[start]<<",,"<<nums[end]<<endl;
        		if(sum==target){
					res=target;
        			return res;
        		}
        		else{
        			if(sum<target){
						if(target-sum<=mindis){//因为最接近的结果可能就是我设置的初值，所以必须用"<="!!!
							mindis=target-sum;
							cout<<sum<<",,,"<<mindis<<endl;
							res=sum;
						}
        				start++;
        			}
        			else if(sum>target){
						if(sum-target<=mindis){//因为最接近的结果可能就是我设置的初值，所以必须用"<="!!!
							mindis=sum-target;
							//cout<<sum<<",,,"<<mindis<<endl;
							res=sum;
						}
						end--;
        			}
        		}
        	}
        }
        //cout<<res<<endl;
        return res;
    }
};

int main(){
	int a[]={-10,0,-2,3,-8,1,-10,8,-8,6,-7,0,-7,2,2,-5,-8,1,-4,6};
    vector<int> num(a,a+20);
    int target=18;
    Solution sol=Solution();
    sol.threeSumClosest(num,target);
    return 0;
}

