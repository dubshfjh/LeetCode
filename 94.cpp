//中序遍历：首先访问node的整个左子树，然后访问node的整个右子树。所以当访问到node时，它的左侧子孙节点都已经访问过了
class Solution {
public:
    vector<int> res;
    vector<int> inorderTraversal(TreeNode* root) {
        inorder(root);
        return res
    }

    void inorder(TreeNode* node){
        if(node==NULL){
            return;
        }   
        inorderTraversal(node->left);
        res.push_back(node->val);
        inorderTraversal(node->right);
    }
};