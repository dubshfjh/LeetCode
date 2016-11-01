/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
算法思想：先序遍历，设定全局bool变量equalSum，对每个节点node定义：到达该节点之前路径的sum（即当前sum不包含node），
用newval记录node进入路径后的新sum，如果node为leaf节点而且newval==sum，则更新equalSum为true。对于非叶子节点，继续递归分析其非空子树，newval将作为下一层节点的val。
PS：树为空时，它的路径和为NULL，而不是0
class Solution {
public:
    bool equalSum = false;
    bool hasPathSum(TreeNode* root, int sum) {
        if(root==NULL){
            return false;
        }
        getNodeValue(root,0,sum);
        return equalSum;
    }

    void getNodeValue(TreeNode* node,int val,int sum){
        int newval = val+node->val;
        if(node->left==NULL && node->right==NULL && newval==sum){
            // cout<<node->val<<",,,"<<newval<<endl;
            equalSum = true;
            return;
        }
        else{
            if(node->left){
                getNodeValue(node->left,newval,sum);
            }
            if(node->right){
                getNodeValue(node->right,newval,sum);
            }
        }
    }
};