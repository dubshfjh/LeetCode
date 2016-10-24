//1  			2  		2   3
//2，2，3	  2，3		3
//....
//与77题的区别只是在于“77中的nums固定为[1,2,3,...n]而已，将其中的start元素本身对应到本题的startindex”
class Solution {
public:
	vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        res.push_back(path);
        dfs(nums,path,0);
        return res;
    }

    void dfs(vector<int>& nums,vector<int> path,int startindex){
    	int size=nums.size();
    	if(path.size()>0){
    		res.push_back(path);
    		if(path.size()==size){
    			return;
    		}
    	}
    	for(int i=startindex;i<size;i++){
    		// while(i<size-1 && nums[i]==nums[i+1]){
    		// 	i++;//本题并不考虑“跳过相同值的兄弟节点”这块，只要求在深搜第2个及之后的节点时，不把之前的兄弟节点重复作为自己的子节点
    		// }
    		path.push_back(nums[i]);
    		dfs(nums,path,i+1);
    		path.pop_back();
    	}
    }
};

//位操作的思想
从数学角度来看，假设原集合有n个元素，那么原集合的子集合的个数是2的n次方，记为2 ^ n。

对应着从0~2 ^ n - 1这2 ^ n个数。这2 ^ n个数如果用二进制表示，可以发现一共有n位。每位要么取0，要么取1。
如果第i位取0，则说明元集合的第i个元素不出现在当前新生成的子集合中，反之，如果第i位取1，则说明元集合的第i个元素出现在当前新生成的子集合中。

这个思路可以通过比特位操作来实现。
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
    	int i,x,size;
    	vector<vector<int>> res;
    	size=nums.size();
    	sort(nums.begin(),nums.end());
    	for(x=0;x<(1<<size);x++){
    		vector<int> temp;
    		//检测当前的X取值在第0位，第1位，第2位,...,第size-1位的取值是0 or 1
    		for(i=0;i<size;i++){
    			if(x&(1<<i)){//1<<i：10000...(该二进制数共有i位)，如果x的第i位为0，则x&(1<<i)=0，即x当前的x对应的vector不包含nums[i]
    				temp.push_back(nums[i]);
    			}
    		}
    		res.push_back(temp);
    	}
    	return res;
    }
};
