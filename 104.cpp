/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int left_depth,right_depth;
        if(root==NULL){
            return 0;
        }
        left_depth = maxDepth(root->left);
        right_depth = maxDepth(root->right);
        return 1+max(left_depth,right_depth);
    }
};