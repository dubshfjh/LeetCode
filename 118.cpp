//初始化第一行为[1]，初始化pre为[1]。从第二行开始的矩阵cur：首元素和尾元素都为1，中间依次插入pre[j]+pre[j+1]，直到j==pre.size()-2为止，pre更新为cur

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if(numRows<=0){
            return res;
        }
        vector<int> cur(1,1);
        res.push_back(cur);
        if(numRows==1){
            return res;
        }
        for(int i=2;i<=numRows;i++){
            vector<int> pre = res[i-2];
            vector<int> cur(1,1);
            for(int j=0;j<pre.size()-1;j++){
                cur.push_back(pre[j]+pre[j+1]);
            }
            cur.push_back(1);
            res.push_back(cur);
        }
        return res;
    }
};