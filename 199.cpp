/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
取得每一层最靠右的节点,改造preorder,按照"根右左"的顺序遍历整棵树，由于对于每个节点都先访问右子，再访问左子，所以每层访问的第一个节点即为本层的最右节点
在每层递归中加入参数level标识tree所处树的层数，由于此时vector只需要保存每层树的最靠右的节点(即每层遍历到的first节点)，所以当某层递归的res.size() < level时说明当前level的头一个节点(即最靠右节点)尚未存储
因此按照“根右左”的顺序递归分析整个树，当某个节点的res.size()<level时在res中保存当前节点的值，直到当前的node为NULL时结束递归
class Solution {
public:
    vector<int> res;    
    vector<int> rightSideView(TreeNode* root) {
        // if(root == NULL){
        //     return res;
        // }
        recursion(root,1);
        return res;
    }

    void recursion(TreeNode* node,int level){
        if(node == NULL){
            return;
        }
        if(res.size() < level){
            res.push_back(node->val);
        }
        recursion(node->right,level+1);
        recursion(node->left,level+1);
    }
};

BFS实现层次遍历
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;    
        if(root == NULL){
            return res;
        }
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int nodenum,level_right;
            nodenum = q.size();
            while(nodenum-- > 0){
                TreeNode *node = q.front();
                level_right = node->val;
                q.pop();                
                if(node->left){
                    q.push(node->left);
                }
                if(node->right){
                    q.push(node->right);
                }
            }
            res.push_back(level_right);
        }
        return res;
    }
};