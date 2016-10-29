/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
一棵树对称：其左子树为右子树的镜像mirror
两棵树t1,t2 成对方镜像的要求
1. t1的根节点 == t2的根节点
2. t1的左子树与t2的右子树成镜像 && t1的右子树与t2的左子树成镜像

求解以root为根的树对称：(root==root)&&(以root->left为根节点的左子树 与 以root->right为根节点的右子树)互成镜像

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root==NULL){
            return true;
        }
        return isMirror(root->left,root->right);
    }

    bool isMirror(TreeNode* left,TreeNode* right){//检查以left为根节点的树 与 以right为根节点的数是否互成镜像
        if(left==NULL && right==NULL){
            return true;
        }
        else if(left==NULL || right==NULL){
            return false;
        }
        else{
            return (left->val==right->val) && isMirror(left->left,right->right) && isMirror(left->right,right->left);
        }
    }
};


还可以借用Queue实现迭代式地判断对称。每次将两颗需要比较对称的树T1，T2的根节点依次加入队列，
于是队列中两相邻节点需要equal && (T1左子树，T2右子树)对称 && (T1右子树，T2左子树)对称
初始化队列为root->left,root->right即可
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root==NULL){
            return true;
        }
        queue<TreeNode*> q;
        q.add(root->left);
        q.add(root->right);

        while(!q.empty()){
            TreeNode *t1 = q.front();
            q.pop();
            TreeNode *t2 = q.front();
            q.pop();

            if(t1==NULL && t2==NULL){//当前的两颗子树都为NULL，满足对称
                continue;
            }
            else if(t1 && t2){
                if(t1->val != t2->val){
                    return false;
                }
                else{
                    q.push(t1->left);
                    q.push(t2->right);
                    //接下来要校验对称性的两颗子树分别为(t1左子树，t2右子树)；(t1右子树，t2左子树)，依序push根节点
                    q.push(t1->right);
                    q.push(t2->left);
                }
            }
            else{
                return false;
            }
        }

        return true;
    }
};




逻辑应该基本正确，但是代码低效到超时
对每一层都校验了对称之后，再用广搜向下走一层，效率过低，超时
（其实超时只是因为脑残到对于NULL节点仍然push进入vector，导致时复O(2^n)，当然会超时）

对于空节点忽略即可，因为如果它会导致不对称，则之前在进入广搜前的校验过程中，就return false。
所以遍历到空节点时，其对称位置也为空节点，这两个空节点都不需要加入队列进行下一步BFS！！！
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        int layer=0;
        vector<TreeNode*> my_que;
        if(root==NULL){
            return true;
        }    
        my_que.push_back(root);
        while(!my_que.empty()){          
            int low=1;
            int high=1<<layer;
            bool allnull = true;
            while(low<=high){
                TreeNode *head = my_que[low-1];
                TreeNode *rear = my_que[high-1];
                //cout<<"a:"<<head->val<<",,,"<<rear->val<<endl;
                if(head&&rear){
                    allnull=false;
                    if(head->val != rear->val){
                        return false;
                    }
                }
                else if(head || rear){
                    return false;
                }
                
                low++;
                high--;
            }
            if(allnull){
                break;
            }
            for(int i=0;i<(1<<layer);i++){
                TreeNode *node = my_que[0];
                //cout<<layer<<": "<<node->left->val<<",,,"<<node->right->val<<endl;
                my_que.erase(my_que.begin());
                if(node){
                    my_que.push_back(node->left);                    
                    my_que.push_back(node->right);
                }
                else{
                    my_que.push_back(NULL);
                    my_que.push_back(NULL);
                }
            }
            layer++;
        }
        return true;
    }
};