算法思路：采用递归思想，使用left和right表示剩下未使用的左括号数和右括号数

步骤1：为保证对称性，在每一层中，先尝试添加一个"("进入下层递归，再尝试添加一个")"进入下层
而真实运行情况中：首先添加N个"("，然后迅速添加N个")"，构成第一个符合的串后返回到N-1个"("这层，添加一个")"后，继续步骤1

必须注意的地方：if(left>right)，则意味着上一层构建的字符串中，已使用的")"多于"("，例如(()))这种情况，此时必须return。否则算法会
尝试添加一个"("得到(()))(，此时left=right=0，但并非对称括号

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> res;
    vector<string> generateParenthesis(int n) {
        int left,right;//left表示还可以使用的"("数目,right表示还可以使用的")"数目
        string path;
        left=right=n;
        path="";
        dfs(left,right,path);//尝试在每一层加入"("后进入下一层，然后尝试在加入")"后进入下一层
        return res;
    }

    void dfs(int left,int right,string path){
        if(left>right){//如果在上一层递归中加入括号后，可用的"("数目更多,也就是说path中的")"多余左括号
            return;//则必然不可能构成回文括号！eg. 上一层递归加入括号后,left=1,right=0：(()))，此时需要return
        }
        if(left==0&&right==0){//如果从第一层递归开始，尝试添加i个"("后结束左括号递归，加入1个")"后多次递归
            res.push_back(path);//而且保证先添加更多的"(",再添加新的")"，此时左右括号用完时，结果必然对称
        }
        if(left>0){//如果尚可添加"("，则尝试加入1个"("后进入下层递归
            dfs(left-1,right,path+"(");
        }
        if(right>0){
            dfs(left,right-1,path+")");
        }
    }
};
