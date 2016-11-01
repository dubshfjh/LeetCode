/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
前一段代码对最开始的算法在时间和空间上的改良，它对于每个节点node，只返回node所在子树的末尾节点，删除了冗余的所在子树根节点(因为这就是node->left or node->right)
算法思想：对于每个节点node，如果它为leaf节点，则直接返回自身；否则记录好其左子、右子节点，并置node->left和node->right为空。如果之前node的左子树非空，则用left_rear记录[node+左子树]的末尾节点(left_rear初值为node)，并更新node整体的末尾节点res_rear，将node->right赋值为其之前的左子节点；
如果之前node的右子树非空，则更新node整体的末尾节点为 node之前右子树的末尾节点，给left_rear->right赋值为node之前的右子节点
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==NULL){
            return;
        }
        constructNode(root);
    }

    TreeNode* constructNode(TreeNode* node){//对每个节点node，返回node所在子树的最后一个节点
        TreeNode *left_rear,*res_rear,*templeft,*tempright;//left_rear为node+其左子树的末尾节点；res_rear为node+左子树+右子树的末尾节点

        templeft = node->left;//提前记录node的子节点，之后要将node的子节点断开
        tempright = node->right;

        left_rear = res_rear = node;

        if(node->left || node->right){
            node->left = NULL;//将node本身的左、右子树都断开
            node->right = NULL;
            if(templeft){
                left_rear = constructNode(templeft);
                res_rear = left_rear;
                node->right = templeft;
            }

            if(tempright){
                res_rear = constructNode(tempright);
                left_rear->right = tempright;
            }
        }
        return res_rear;
    }
};


冗余的初始算法思想
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==NULL){
            return;
        }
        constructNode(root);
    }

    vector<TreeNode*> constructNode(TreeNode* node){//对每个节点node，返回[node所在子树的root, node所在子树的最后一个节点]。其实所在子树的root一直是root本身，只需返回树的末尾节点即可
        vector<TreeNode*> root_rear,node_tree;//node_tree记录返回的2个节点
        TreeNode *rear,*tempright,*templeft;
        templeft = node->left;
        tempright = node->right;
        // if(node->left==NULL && node->right==NULL){
        //     node_tree.push_back(node);
        //     node_tree.push_back(node);
        // }
        // else{
        node_tree.push_back(node);//如果node为叶子节点，则以node为根节点子树的root和尾节点都为node本身
        node_tree.push_back(node);
        if(node->left || node->right){
            node->left = NULL;//将node本身的左、右子树都断开
            node->right = NULL;
            if(templeft){//如果存在左子树，则将左子节点作为node进入下层递归
                root_rear = constructNode(templeft);
                rear = root_rear[1];//记录左子树的最后一个节点rear，rear->right将为(node右子树的根节点，实际上就是右子节点(NULL/非空)！！！)
                
                node->right = root_rear[0];//node右子节点为左子树的根节点(实际上就是左子节点！！！)
                node_tree[1] = root_rear[1];//将node子树的末尾节点更新一次
            }

            if(tempright){
                root_rear = constructNode(tempright);
                if(templeft==NULL){//此时说明node无左子树,node的右子节点保持不变即可
                    node->right = root_rear[0];
                }
                else{//左子树的最后一个节点rear->right将为右子节点本身
                    rear->right = root_rear[0];
                }
                node_tree[1] = root_rear[1];
            }

        }
        return node_tree;
    } 
};
