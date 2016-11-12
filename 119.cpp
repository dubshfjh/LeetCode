//输出第rowIndex+1个pascal数组
//思想：设置前一行数组pre，初始化pre为[1]；从第2个数组开始求解当前行res：首尾元素为1，中间插入pre[j]+pre[j+1]。然后pre更新为当前res，依次求解下一行数组
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> pre,res;
        if(rowIndex<=0){
            res.push_back(1);
            return res;
        }
        pre.push_back(1);
        for(int i=2;i<=rowIndex+1;i++){
            res.clear();
            res.push_back(1);
            for(int j=0;j<pre.size()-1;j++){
                res.push_back(pre[j]+pre[j+1]);
            }
            res.push_back(1);
            pre.assign(res.begin(),res.end());
        }
        return res;
    }
};