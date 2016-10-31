/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
ZigZag：使用flag标记正向存储/反向存储本层的值，第0层正向存储(头插法)、第1层反向存储(尾插法)....依层切换方向

借助队列进行BFS，每到达新的一层时，队列q中只包含上一层的元素(size个)，将上一层的节点按照其应有方向存储后，对每个节点的非空child入队列
存储玩上一层节点后，切换flag值改变本层节点的存储方向(进入下一层时，换个方向存储本层的值)。
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        int flag=0;//flag=0表示zigzag正向存储元素；flag=1表示zigzag反向存储元素
        vector<vector<int>> res;
        queue<TreeNode*> q;
        if(root==NULL){
            return res;
        }
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            vector<int> temp;
            for(int i=0;i<size;i++){
                TreeNode *node = q.front();
                q.pop();
                if(flag==0){//之字正向：尾插法
                    temp.push_back(node->val);
                }
                else{//之字反向：头插法
                    temp.insert(temp.begin(),node->val);
                }
                
                if(node->left){
                    q.push(node->left);
                }
                if(node->right){
                    q.push(node->right);
                }
            }
            flag=(flag==0)?1:0;
            res.push_back(temp);
        }
        return res;
    }
};