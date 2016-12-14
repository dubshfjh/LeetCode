/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
testcase []
[1,3,2,1,5,3,3,4,4,5,5,6,7,7,8,8,9,3,9,2,4,5,5,6,6,7,8,8,9,8,9,9]
算法思想：如果根节点root为空则返回0；否则使用后序遍历进行递归，并记录每个节点parent代表的数字。对于每个节点node，首先使用使用后序遍历进行递归，10*parent+node->val计算node代表的数字。如果node左子/右子不为空，则使用非空子节点代表数字的sum更新node代表的数字，并返回该值；如果node为叶节点，则直接返回node代表的数字；
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(root==NULL){
            return 0;
        }
        return cal_node(root,0);
    }

    double cal_node(TreeNode* node,double parent){//根据节点node上一层父节点代表的数字parent，计算节点node代表的数字，使用后序遍历：如果node左子or右子不为空，则使用非空子节点的sum更新node代表数字；如果node为叶子节点，则将节点本身代表数字直接返回
        double node_val = parent*10+node->val;
        if(node->left==NULL && node->right==NULL){
            return node_val;
        }
        double left,right;
        left = right = 0; 
        if(node->left){
            left = cal_node(node->left,node_val);
        }
        if(node->right){
            right = cal_node(node->right,node_val);
        }
        return left+right;
    }
};
