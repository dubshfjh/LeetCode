class Solution {
public:
	vector<vector<int>> res;
    vector<vector<int>> combine(int n, int k) {//Attention：{1,2,3}和{1,3,2}算同一种组合！！！
        vector<int> path;
    	map<int,int> brother;
        dfs(path,1,n,k);
        return res;
    }

    void dfs(vector<int> path,int start,int n,int k){//每一层从第2个节点开始，其子节点不能再与之前的兄弟节点相同
    	int i,flag=0;//即访问到{1,2,3,4}这一层时，"1"的子节点不能再为"1"本身 ,"2"的子节点不能再为1以及"2"本身，"3"的子节点不能再为"1,2"以及"3"本身，"4"的子节点不能再为"1,2,3"以及"4"本身
    	if(path.size()==k){
    		res.push_back(path);
    		return;
    	}
    	
    	for(int i=start;i<=n;i++){//start为上一层节点之后的第一个节点
    		path.push_back(i);
			dfs(path,i+1,n,k);
			path.pop_back();
    	}
    }
};