/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
先序的第2种迭代模板 "初始化栈为root"

先序遍历：中，左，右
对于每个当前节点node，1. 访问node 2.将右子入栈 3.将左子入栈（从而保证出栈时首先分析左子，再分析右子）

初始化栈为root，如果栈不为空
1. 对于节点cur（即当前的栈顶），要先访问它自己，再访问它的左子树，然后访问它的右子树，所以第一步是visit(cur)，并将cur从栈中pop掉
2. 为了保证在分析多个栈顶时，先访问左子树，再访问右子树，必须使用栈在本层的cur被pop之前先push"右子节点"入栈，再push("左子节点入栈")
3. cur转移到下一个栈顶(左子/右子/某个祖先节点的右子)

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> my_stk;
        if(!root){
            return res;
        }
        my_stk.push(root);
        TreeNode *cur;
        while(!my_stk.empty()){
            cur = my_stk.top();
            res.push_back(cur->val);
            my_stk.pop();
            if(cur->right){
                my_stk.push(cur->right);
            }
            if(cur->left){
                my_stk.push(cur->left);
            }
        }
        return res;
    }
};


先序的第1种迭代模板 "初始化cur为root"
    由于"根，左，右"的访问顺序，所以每个节点node在visit后入栈，并访问node->left；node只有在pop出栈的时候，才转去访问它的right
    "在cur出栈后，将node的右子树压入栈中"
初始化cur为root，如果cur!=NULL || 栈不为空
1. 首先访问cur，然后将尚未将"右子节点入栈"的节点cur入栈，接着cur转到自己的左子树
2. 当cur一路向左走到空时将栈顶元素pop掉，并转到此时栈顶元素的右子树


class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == NULL){
            return res;
        }
        stack<TreeNode*> my_stk;
        TreeNode *cur = root;
        while(cur || !my_stk.empty()){
            if(cur){
                res.push_back(cur->val);
                my_stk.push(cur);
                cur = cur->left;
            }
            else{
                cur = my_stk.top();
                my_stk.pop();
                cur = cur->right;
            }
        }
        return res;
    }
};

对比中序的迭代模板

"cur只有从stack中弹出时才进行访问, 在cur访问完毕后，将node的右子树压入栈中"
初始化cur为root，如果 cur!=NULL || 栈不为空
1. 由于需要先访问左子树，所以首先先用stack对还没有访问的节点cur进行缓存，接着cur转到自己的左子树
2. 当cur一路向左走到空时，访问栈顶元素并将它pop掉，接着转到此时栈顶元素的右子树
PS: 栈中的最后一个被访问的元素必然没有右子树

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == NULL){
            return res;
        }
        stack<TreeNode*> my_stk;
        "
        由于迭代过程为 1.每个节点node先向左走到尽头 2. 访问当前的栈顶元素 3. 分析栈顶元素的右子
        所以不需要在栈中初始化root!!!!!!因为cur的初值就是root了，这会导致root这个元素被分析2次

        // my_stk.push(root);
        "
        TreeNode *cur = root;
        //每个节点都作为左子树压入栈中；作为根被访问；再将根的右子树做相同处理
        while(cur || !my_stk.empty()){
            if(cur){
                my_stk.push(cur);
                cur = cur->left;
            }
            else{
                cur = my_stk.top();
                my_stk.pop();
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};