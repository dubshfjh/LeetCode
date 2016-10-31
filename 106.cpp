/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
中序遍历：左子树最左节点(下标为in_index)...左子树最右节点,node(下标为index),右子树最左节点,...,node->right,...,右子树最右节点(下标为in_index+size-1)
后序遍历：左子树最左节点...左子树最右节点,node->left,右子树最左节点,...右子树最右节点,node->right,node(下标为post_index)

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(postorder.size()==0){
            return NULL;
        }
        int size=inorder.size();
        return constructNode(inorder,postorder,0,size-1,size);
    }

    TreeNode* constructNode(vector<int>& inorder, vector<int>& postorder,int in_index,int post_index,int size){
        //post_index：本次要分析的根节点；in_index：存储当前树在inorder中的左边界
        if(size<=0){
            return NULL;
        }
        TreeNode *node = new TreeNode(postorder[post_index]);
        int index=0;//定位postorder[post_index]这个根节点在inorder中的位置
        for(int i=0;i<size;i++){
            if(postorder[post_index] == inorder[in_index+i]){
                index=in_index+i;
                break;
            }
        }

        int leftsize = index-in_index;//记录左子树节点数目
        int rightsize = size-1-leftsize;

        node->left=constructNode(inorder,postorder,in_index,post_index-rightsize-1,leftsize);
        node->right=constructNode(inorder,postorder,index+1,post_index-1,rightsize);
        return node;
    }
};