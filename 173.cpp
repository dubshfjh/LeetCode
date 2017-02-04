/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
[1,2,3,null,5]
由于二叉搜索树的顺序序列就是中序遍历的结果，为实现"左父右"，栈的局部操作为"父入栈，左子入栈作为新的父"，当整颗左子树访问完毕后，访问并pop掉本层的父，本层父的右子入栈作为新的"父"
自定义额外的push_left(node)函数：将node，以及node最左侧一条线上的子孙节点入栈，从而使得每次的栈顶就是中序遍历的对应元素。
    对于构造函数：push_left(root)
    对于hasNext：当栈为空时，中序遍历不再有next元素
    对于next：首先pop出栈顶元素node作为此次输出的元素，当node存在右子时执行push_left(right)
class BSTIterator {
public:
    stack<TreeNode*> s;
    //由于二叉搜索树的顺序序列就是中序遍历的结果，为实现"左父右"，栈的局部操作为"父入栈，左子入栈作为新的"父"，当整颗左子树访问完毕后，访问并pop掉本层的父，本层父的右子入栈作为新的"父"
    BSTIterator(TreeNode *root) {
        push_left(root);//将root以及其最左侧一条线上的子孙节点入栈，因此栈顶元素为(无左子||左子在上一次调用next时被访问)的元素，因此可以作为父被访问
        //每次pop掉当前的栈顶元素时，将栈顶的右子入栈，从而对每个节点保持"左，父，右"的访问顺序
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {//第i次调用next()：返回中序遍历序列的第i个元素
        TreeNode* node = s.top();//此时栈顶元素的左子要么不存在，要么之前已经访问过
        s.pop();
        //cout<<"aaa:"<<node->val<<endl;
        if(node->right){//在访问了此时的栈顶后，如果其右子存在则要将右子入栈，下次调用next时就分析入栈的右子是否具有未被访问的left child
            push_left(node->right);//将栈顶右子，以及右子的最左侧一条线上的子孙节点入栈
        }
        return node->val;
    }

private:
    void push_left(TreeNode *node){//将node，以及node最左侧一条线上的子孙节点入栈，从而使得每次的栈顶就是中序遍历的对应元素
        while(node){
            s.push(node);
            node = node->left;
        }
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */