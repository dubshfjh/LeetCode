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

错误思想：如果node的左子尚未访问，则需要让左子入栈。但是这样会导致左子未访问时，右子也无法入栈
/*
中序遍历：左，中，右("更详细的类似解法见 145 后序遍历")
迭代法：对于每个节点node，1. 如果node左子为空 || node左子为前一个访问完毕的节点pre，则先访问node，再将node从栈中pop掉，然后将pre更新为node
2. 否则先将node的"右子"入栈，再将node的"左子"入栈(PS：这样才可以保证在访问栈顶时的顺序为"先左子，再右子")
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == NULL){
            return res;
        }
        stack<TreeNode*> my_stk;
        my_stk.push(root);
        TreeNode *pre = NULL;
        TreeNode *cur = root;
        while(!my_stk.empty()){
            cur = my_stk.top();
            cout<<cur->val<<endl;
            if(cur->left==NULL || (pre && pre==cur->left)){
                my_stk.pop();
                res.push_back(cur->val);
                pre = cur;
            }
            else{//如果node的左子尚未访问，则需要让左子入栈。但是这样会导致左子未访问时，右子也无法入栈
                if(cur->right){
                    cout<<cur->right->val<<endl;
                    my_stk.push(cur->right);
                }
                if(cur->left){
                    my_stk.push(cur->left);
                }
            }
            
        }
        return res;
    }
};
*/
Attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    栈中初始化root，与cur初始化为root，是不需要同时出现的！！！！！！！！！！
    1. 栈初始化为root时，cur不需要赋初值，终止条件"栈不为空",每次迭代都需要将cur=stack.top()即可
    2. cur初始化为root时，终止条件"cur!=NULL || 栈不为空".如果栈顶初始化为了root，则cur一路向左走到尽头后，再一路pop栈顶会导致root被再次访问！！！！！！！



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


对比先序的第1种迭代模板
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





对比先序的第2种迭代模板"与上面的结构有所不同！"

初始化栈为root，如果栈不为空
1. 对于节点cur（即当前的栈顶），要先访问它自己，再访问它的左子树，然后访问它的右子树，所以第一步是visit(cur)，并将cur从栈中pop掉
2. 为了保证在分析多个栈顶时，先访问左子树，再访问右子树，必须使用栈在本层的cur被pop之前先push"右子节点"入栈，再push("左子节点入栈")
3. cur转移到下一个栈顶(左子/右子/某个祖先节点的右子)


class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == NULL){
            return res;
        }
        stack<TreeNode*> my_stk;
        my_stk.push(root);
        TreeNode *cur;
        while(!my_stk.empty()){
            cur = my_stk.top();
            res.push_back(cur->val);
            cout<<cur->val<<endl;
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

