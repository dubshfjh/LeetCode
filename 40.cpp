#include <iostream>
#include <vector>
#include <algorithm>

//http://www.cnblogs.com/ganganloveu/p/4167175.html

1、在同一层递归树中，如果某元素已经处理并进入下一层递归，那么与该元素相同的值就应该跳过。否则将出现重复。

例如：1,1,2,3

如果第一个1已经处理并进入下一层递归1,2,3

那么第二个1就应该跳过，因为后续所有情况都已经被覆盖掉。

2、必须选择相同元素第一个进入下一层递归，而不是任意一个

例如：1,1,2,3

如果第一个1已经处理并进入下一层递归1,2,3，那么两个1是可以同时成为可行解的

而如果选择的是第二个1并进入下一层递归2,3，那么不会出现两个1的解了。

class Solution {
public:
	vector<vector<int>> res;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> temp;
        sort(candidates.begin(),candidates.end());
        dfs(0,target,temp,candidates);
        //reverse(res.begin(),res.end());
        return res;
    }

    void dfs(int index,int target,vector<int> temp,vector<int> candidates){
		if(target==0){
			res.push_back(temp);
		}
    	else{//本质上就是分析在选择了index所在元素之后，对在它之后元素(比它更大)遍历全部的选择决策
			for(int i=index;i<candidates.size()&&candidates[i]<=target;i++){
				if(i!=index && candidates[i]==candidates[i-1]){//在选择了index，并对之后的全部元素做出决策之后
					continue;//在{index+1...size-1}这段元素中，与[index]相等的元素就不需要再“选择它们，并分析它们之后的元素”了
				}//因为这部分的结果已经包含在“选择了index后，对index之后的元素进行选择”这部分了
				//cout<<index<<",,,"<<i<<endl;
				temp.push_back(candidates[i]);
				dfs(i+1,target-candidates[i],temp,candidates);
				temp.pop_back();
			}
    	}
    }
};



在遍历子集的过程中：

（1）单个元素大于target，则后续元素无需扫描了，直接返回结果。
（2）单个子集元素和大于target，则不用加入当前的子集容器了。
（3）单个子集元素和等于target，加入结果数组。

class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        vector<vector<int> > result;
        vector<vector<int> > subsets;
        vector<int> empty;
        subsets.push_back(empty);
        
        sort(num.begin(), num.end());
        for(int i = 0; i < num.size();)
        {//for each number
            int count = 0;
            int cur = num[i];
            if(cur > target)    //end
                return result;
            while(i < num.size() && num[i] == cur)//举例说明:[1,1,1,1,2]，分析first 1时，直接让i跳到最后一个"1"处，并记录"1"的个数
            {//repeat count
                i ++;
                count ++;
            }
            int size = subsets.size();    //orinigal size instead of calling size() function
            for(int j = 0; j < size; j ++)
            {
                vector<int> sub = subsets[j];
                int tempCount = count;
                while(tempCount --)//举例说明:[1,1,1,1,2],从使用1个"1"开始分析，直到使用count个1为止，构建subset:[1],[1,1],[1,1,1],[1,1,1,1]
                {
                    sub.push_back(cur);//cur为当前的num[i]
                    int sum = accumulate(sub.begin(), sub.end(), 0);
                    if(sum == target)
                    {
                        result.push_back(sub);
                        subsets.push_back(sub);
                    }
                    else if(sum < target)
                        subsets.push_back(sub);
                }
            }
        }
        return result;
    }
};