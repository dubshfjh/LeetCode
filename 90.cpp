遇到{1,1,1,1,2}时，在每一层在对第0个'1'进行分析，后方取值同样为'1'的兄弟节点将直接跳过
但是从每层第0个'1'节点向下一层时，下层直接从后一个'1'开始即可。

原因：向下一层的本质就是在当前temp中加一个新数字(所以1;1,1;1,1,1;1,1,1,1都不重复)
而同一层兄弟节点的本质就是从当前temp中替换掉一个旧数字(所以当前temp为1,1,1时，把代表当前层次的最后的1替换成另一个'1'是没有意义的)

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> temp;
        sort(nums.begin(),nums.end());
        res.push_back(temp);
        backtrace(nums,temp,0);
        return res;
    }

    void backtrace(vector<int>& nums,vector<int> temp,int startindex){
        // cout<<"start: "<<startindex<<":"<<endl;
        for(int i=startindex;i<nums.size();i++){
            // cout<<"i: "<<i<<"  "<<nums[i]<<endl;
            temp.push_back(nums[i]);
            res.push_back(temp);
            
            backtrace(nums,temp,i+1);
            while(nums[i]==nums[i+1] && i<nums.size()-1){
                i++;
            }
            startindex=i+1;//遇到{1,1,1,1,2}时，在每一层在对第0个'1'进行分析，后方为'1'的兄弟节点将直接跳过
            temp.pop_back();//但是从每层第0个'1'节点向下一层时，下层直接从后一个'1'开始即可。
            //原因：向下一层的本质就是在当前temp中加一个新数字(所以1;1,1;1,1,1;1,1,1,1都不重复)
            //而同一层兄弟节点的本质就是从当前temp中替换掉一个旧数字(所以当前temp为1,1,1时，把代表当前层次的最后的1替换成另一个'1'是没有意义的)
        }
    }
};