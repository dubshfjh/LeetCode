/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
树结构显然用递归来解，解题关键：

1、对于每一层递归，只有包含此层树根节点的值才可以返回到上层。否则路径将不连续。

2、返回的值最多为根节点加上左右子树中的一个返回值，而不能加上两个返回值。否则路径将分叉。

在这两个前提下有个需要注意的问题，最上层返回的值并不一定是满足要求的最大值，

因为最大值对应的路径不一定包含root的值，可能存在于某个子树上。因此解决方案为设置全局变量maxSum，在递归过程中不断更新最大值。

class Solution {
public:
    int maxSum = INT_MIN;
    int maxPathSum(TreeNode* root) {
        getpath_sum(root);
        return maxSum;
    }

    int getpath_sum(TreeNode* node){//获得以node为根节点的树的pathsum。首先计算到node为止的pathSum(不用考虑今后回不回node的父节点)并尝试更新maxSum。然后选取max(左子，右子，0)+node->val返回node的父节点
        if(!node){
            return INT_MIN;
        }
        int val_left = getpath_sum(node->left);
        int val_right = getpath_sum(node->right);

        if(node->val>=0){//路径一定会包含node(因为node+子节点>=子节点本身的Sum)
            if(val_left>=0 && val_right>=0){
                maxSum = max(maxSum,node->val+val_left+val_right);
            }
            else if(val_left<0 && val_right>=0){
                maxSum = max(maxSum,node->val+val_right);
            }
            else if(val_left>=0 && val_right<0){
                maxSum = max(maxSum,node->val+val_left);
            }
            else{
                maxSum = max(maxSum,node->val);
            }
        }
        else{//此时可能会放弃node,因为node必然会<0
            if(val_left>=0 && val_right>=0){//如果左子+node+右子>=max(左子,右子)则选择包含node，否则单独选择左子或右子
                maxSum = max(maxSum,max(node->val+val_left+val_right, max(val_left,val_right)));
            }
            else if(val_left<0 && val_right>=0){//此时node<0 && 左子<0，本层最大的sum就是val_right
                maxSum = max(maxSum,val_right);
            }
            else if(val_left>=0 && val_right<0){
                maxSum = max(maxSum,val_left);
            }
            else{//选取左子，右子，node这三个负数sum中的最大值作为本层maxSum
                maxSum = max(maxSum,max(node->val,max(val_left,val_right)));
            }
        }

        int nodeSum = max(0,max(val_left,val_right))+node->val;//要想返回上层，则必须包含node本身
        return nodeSum;
    }
};