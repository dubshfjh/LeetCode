/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
算法思想：规定子树的左边界low和右边界high，每次选择中间的mid作为当前子树的根节点作为构建的node，其左子树区间为[low,mid-1]，右子树区间为[mid+1,high]
node->left即为左子树区间的根节点；node->right即为右子树区间的根节点。若low>high则说明当前节点为NULL
PS：初始时的子树边界为[0,size-1]

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int size=nums.size();
        return constructNode(nums,0,size-1);
    }

    TreeNode* constructNode(vector<int>& nums,int low,int high){
        if(low>high){
            return NULL;
        }
        int mid = (low+high)/2;
        TreeNode *node = new TreeNode(nums[mid]);
        node->left = constructNode(nums,low,mid-1);
        node->right = constructNode(nums,mid+1,high);
        return node;
    }
};