#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* 智障啊你，two indices意味着只要考虑2个元素相加就行了
class Solution{
public:
	vector<int> twoSum(vector<int>& nums,int target){
		vector<int> result,tempnums;
		for(int j=0;j<nums.size();j++){
			tempnums.push_back(nums[j]);
		}
		sort(tempnums.begin(),tempnums.end());
		int flag=0;
		int index=findnear(tempnums,target);
		//cout<<"index is:"<<index<<endl;
		for(int i=index;i>=0;i--){
			cout<<"The round is :"<<i<<endl;
			initial(result,tempnums[i]);
			flag=findres(tempnums,target-tempnums[i],flag,result);
			cout<<"Final flag is: "<<flag;
			if(flag==1){
				for(int k=0;k<result.size();k++){
				    cout<<result[i]<<",,,";
				}
				cout<<endl;
				break;
			}
			if(flag==-1){
				result.clear();
			}
		}
		if(i<0){
			cout<<"No result!"<<endl;
		}
		return result;
	}

	void initial(vector<int>& result,int first){
		result.clear();
		result.push_back(first);
	}

	int findres(vector<int>& nums,int tempnums,int flag,vector<int>& result){
		if(flag>=0){
			//cout<<"tempnums: "<<tempnums<<"...flag: "<<flag<<endl;
			if(tempnums==0){
				flag=1;
				return flag;
			}
			int index=findnear(nums,tempnums);
			if(index==-1){
				flag=-1;
				return flag;
			}
			else{
				result.push_back(nums[index]);
				tempnums-=nums[index];
				flag=findres(nums,tempnums,flag,result);
				cout<<"tempnums: "<<tempnums<<"...flag: "<<flag<<endl;
				return flag;
			}
		}
		
	}

	int findnear(vector<int>& nums,int temptarget){
		int res=-1;
		for(int i=0;i<nums.size();i++){
			if(nums[i]>temptarget){
				res=i-1;
				return res;
			}
		}
		return res;
	}
};
智障啊你，two indices意味着只要考虑2个元素相加就行了*/
class Solution{
public:
	vector<int> twoSum(vector<int>& nums,int target){
		int i,j,k,complement,flag;
		vector<int> result;
		for(i=0;i<nums.size();i++){
			flag=0;
			complement=target-nums[i];
			cout<<"comple: "<<complement<<endl;
			result.clear();
			for(j=0;j<nums.size();j++){
				if(j!=i&&nums[j]==complement){
					flag=1;
					cout<<"j: "<<j<<endl;
					break;
				}
			}
			if(flag==1){
				result.push_back(i);
				result.push_back(j);
				break;
			}
		}
		return result;
	}
};

//注意！！！Input[3,2,4],target:6时，必须判断complement=6-3时，不能再次选用3本身作为complement
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution{
public:
	vector<int> twoSum(vector<int>& nums,int target){
		int i,j,complement;
		vector<int> result;
		map<int,int>::iterator iter;
		map<int,int> index;
		for(i=0;i<nums.size();i++){
			index.insert(pair<int,int>(nums[i],i));
		}
		for(i=0;i<nums.size();i++){
			complement=target-nums[i];
			iter=index.find(complement);
			if(iter!=index.end()&&i!=iter->second){
				result.push_back(i);
				result.push_back(iter->second);
				break;
			}
		}
		for(i=0;i<result.size();i++){
			cout<<"index: "<<result[i]<<"  val:"<<nums[result[i]]<<endl;
		}
		return result;
	}
};

int main(){
	vector<int> nums;
	int target;
	Solution sol=Solution(); 
	nums.push_back(2);
	nums.push_back(7);
	nums.push_back(11);
	nums.push_back(15);
	target=9; 
	sol.twoSum(nums,target);
	return 0;
}
