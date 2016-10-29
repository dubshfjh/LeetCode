/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
基本知识点：二叉搜索树的中序遍历就是升序序列。

因此不满足升序的两个点就是两个问题节点。设置空结点INT_MIN来保证第一次满足。

pre初始化为INT_MIN,cur初始化为root

pre     cur
INT_MIN, 4,   2,   3,   1,    5
大数被前置(问题:pre)  小数被后置(问题:cur)
            >         >    

涉及到4,2,3,1

稍作分析即可知道，第一次出现反常(pre > cur)意味着pre结点有问题，而第二次出现反常(pre > cur)

意味着后一个结点cur有问题。因此交换这两个问题节点即可。

有个小问题需要注意：如果一共只有两个节点(2,1)，那么就只会出现一次pre > cur的情况。

为了处理这种情况，我们在第一次pre>cur时，就把cur结点也临时设置为second问题节点，之后如果遇到第2次pre>cur，则更新second。

class Solution {
public:
    TreeNode *pre;//前一个节点
    TreeNode *first;//第一个问题节点
    TreeNode *second;//第二个问题节点
    void recoverTree(TreeNode* root) {
        pre = new TreeNode(INT_MIN);
        first = NULL;
        second = NULL;
        Inorder(root);
        if(first && second){
            swap(first->val,second->val);
        }
    }

    void Inorder(TreeNode* cur){
        if(cur==NULL){
            return;
        }
        Inorder(cur->left);
        if(cur->val < pre->val){
            if(first==NULL){//第一个问题节点：被前置的大数pre
                first=pre;
            }
            else{//第二个问题节点：被后置的小数cur
                second=cur;
            }
            second=cur;//对于first==NULL的情况，也需要置second=cur，这是针对只有1次pre>cur的情况出现
        }
        pre=cur;
        Inorder(cur->right);
    }
};
第一次失败：
下面的解法完全没看懂题目要求：题意并非某个节点的左、右子节点被错误地交换，而是指树中的任意两个节点被错误地交换了
// class Solution {
// public:
//     void recoverTree(TreeNode* root) {
//         bool swapflag=false;
//         queue<TreeNode*> my_que;
//         if(root==NULL){
//             return;
//         }
//         my_que.push(root);
//         while(!my_que.empty() && !swapflag){
//             TreeNode *node = my_que.front();
//             my_que.pop();
//             if(node->left){
//                 if(node->left->val < node->val){
//                     my_que.push(node->left);
//                 }
//                 else{
//                     swapflag=false;
//                 }
//             }

//             if(node->right){
//                 if(node->right->val > node->val){
//                     my_que.push(node->right);
//                 }
//                 else{
//                     swapflag=true;
//                 }
//             }

//             if(swapflag){
//                 TreeNode *left_child = node->left;
//                 TreeNode *right_child = node->right;
//                 node->right = left_child;
//                 node->left = right_child;
//             }
//         }
//     }
// };
第二次失败：
[1,null,2,3...]这类满二叉树中，如果根节点从1开始编号，则对于节点i而言，左子序号为2*i，，右子序号为2*i+1
二叉搜索树实例：[5,3,7,2,4,6,8,1,null,null,null,null,null,null,9]
思想（已证明错误）：按序分析每个节点，如果节点不满足(left<node<right)，则记录不合法的子节点

这种做法根本不能确定被swap节点的真正位置，e.g. 当交换了树中的节点(1,7)时，代码发现"5"的右子节点为"1"，于是记录"1"；发现“1”的左子节点为“6”，
于是记录“6”，最终交换1和6，完全错误
/*
class Solution {
public:
    void recoverTree(TreeNode* root) {
        int swap[2];
        vector<TreeNode*> tree_node;
        queue<TreeNode*> my_que;

        if(root==NULL){
            return;
        }
        my_que.push(root);
        tree_node.push_back(root);
        int node_index=0,node_num=0;
        while(!my_que.empty()){//必须在数组中保存完整的二叉树，否则需要swap的节点index将超过vector.size()
            node_index++;
            TreeNode *node=my_que.front();
            my_que.pop();
            // cout<<node->val<<endl;
            if(node->left){
                my_que.push(node->left);
                if(node->left->val > node->val && node_num<=1){
                    swap[node_num++] = 2*node_index;
                }
            }
            tree_node.push_back(node->left);

            if(node->right){
                my_que.push(node->right);
                if(node->right->val < node->val && node_num<=1){
                    swap[node_num++] = 2*node_index+1;
                }
            }
            tree_node.push_back(node->right);
        }
        
        int temp=tree_node[swap[0]-1]->val;
        tree_node[swap[0]-1]->val=tree_node[swap[1]-1]->val;
        tree_node[swap[1]-1]->val=temp;
        
        // TreeNode *parent_1 = tree_node[swap[0]/2 - 1];
        // cout<<parent_1->val<<",,,"<<tree_node[swap[0]-1]->val<<endl;
        // TreeNode *parent_2 = tree_node[swap[1]/2 - 1];
        // cout<<parent_2->val<<",,,"<<tree_node[swap[1]-1]->val<<endl;

        // if(swap[0]%2==0){//parent_1的错误节点为其左子节点
        //     parent_1->left = tree_node[swap[1]-1];
        // }
        // else{
        //     parent_1->right = tree_node[swap[1]-1];
        // }

        // if(swap[1]%2==0){//parent_2的错误节点为其左子节点
        //     parent_2->left = tree_node[swap[0]-1];
        // }
        // else{
        //     parent_2->right = tree_node[swap[0]-1];
        // }
    }
};
*/
第三次失败：
dfs，将不满足(low,high)的节点记录为问题节点。具体缺陷见代码注释
class Solution {
public:
    vector<TreeNode*> swap;
    TreeNode *parent;
    void recoverTree(TreeNode* root) {
        double low,high;
        low=INT_MIN;
        high=INT_MAX;
        dfs(root,low-1,high+1);
        if(swap.size()==1){//如果被交换的节点是父子节点，则发现的越界节点就只有正确二叉树中的父节点(即reversed树中的子节点)
            find_parent(root,swap[0]);//但是当父子节点距离差>1时，e.g 初始树为[5,3,7,2,4,6,8,1,null,null,null,null,null,null,9]
            int temp=parent->val;//交换"3"和"5"后，对于“5”：(负无穷,3)，对于"4"，继承父节点的取值区间：(负无穷,3)，于是误认为"4"为需要swap的节点
            parent->val=swap[0]->val;
            swap[0]->val=temp;
        }
        else if(swap.size()==2){
            int temp = swap[0]->val;
            swap[0]->val = swap[1]->val;
            swap[1]->val = temp;
        }
    }

    void dfs(TreeNode* node,double low,double high){
        if(node==NULL){
            return;
        }
        if(node->val <= low || node->val >= high){
            swap.push_back(node);
            dfs(node->left,low,high);
            dfs(node->right,low.high);
        }
        else{
            dfs(node->left,low,node->val);
            dfs(node->right,node->val,high);
        }
    }

    void find_parent(TreeNode *node,TreeNode *target){
        if(node==NULL){
            return;
        }
        if(node->left && node->left==target){
            parent=node;
        }
        if(node->right && node->right==target){
            parent=node;
        }
        find_parent(node->left,target);
        find_parent(node->right,target);
    }
};
