/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
算法思想：为每个节点node定义从root到它之前路径path，以及该路径的sum值。在path中加上当前node，并使用变量new_val记录加上node之后的新sum，如果node为叶节点 && new_val==sum，则
记录此时的path(已包含node)到最终结果。如果node并非叶节点，则递归分析其非空子节点。由于node的递归上层不会受到node层path变量的影响，并不需要path.pop_back()
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(root==NULL){
            return res;
        }
        vector<int> temp;
        getNodeval(root,0,sum,temp);
        return res;
    }

    void getNodeval(TreeNode* node,int val,int sum,vector<int> path){
        int new_val = val+node->val;
        path.push_back(node->val);
        if(node->left==NULL && node->right==NULL && new_val==sum){
            res.push_back(path);
        }
        else{
            if(node->left){
                getNodeval(node->left,new_val,sum,path);
            }

            if(node->right){
                getNodeval(node->right,new_val,sum,path);
            }
        }
        // path.pop_back();
        return;
    }
};