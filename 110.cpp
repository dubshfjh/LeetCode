/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
算法思想：设置全局变量flag(初始值为true，因为空树也是平衡树)，然后递归计算每一个节点的左右子树depth。如果任意节点的左子/右子不平衡，
则将全局变量置为false。最终返回全局变量
class Solution {
public:
    bool flag=true;
    bool isBalanced(TreeNode* root) {
        getDepth(root);
        return flag;
    }

    int getDepth(TreeNode* node){
        if(node==NULL){
            return 0;
        }
        int leftdepth = getDepth(node->left);//计算当前节点左子树深度
        int rightdepth = getDepth(node->right);
        if(abs(leftdepth-rightdepth)>1){//当前节点左子、右子不平衡
            flag=false;
        }
        return max(leftdepth,rightdepth)+1;
    }
};