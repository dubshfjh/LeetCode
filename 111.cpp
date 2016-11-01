/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
算法思想：若root为空则返回0；否则，初始化高度height为INT_MAX，对每个节点定义：从root到达该节点时的路径长度(包括当前节点)。对于每个叶子节点，将height更新为min(height,当前路径长度)。
Attention：最开始的想法参考“求最大深度”的解法，每次获取当前节点的min(左子树深度，右子树深度)+1作为当前树的最小深度。
但是当某个节点node只有左子树 or 只有右子树时，它会将0认为是右子树的深度，于是算法认为node树的深度为1。但实际上node的另一侧没有leaf节点，所以node的真实深度为(存在的那侧子树深度)

class Solution {
public:
    int res_depth=INT_MAX;
    int minDepth(TreeNode* root) {
        if(root==NULL){
            return 0;
        }
        getDepth(root,1);
        return res_depth;
    }

    void getDepth(TreeNode* node,int depth){
        if(node->left==NULL && node->right==NULL){
            res_depth = min(res_depth,depth);
            return;
        }
        
        if(node->left){
            getDepth(node->left,depth+1);
        }

        if(node->right){
            getDepth(node->right,depth+1);
        }
        return;
    }
};