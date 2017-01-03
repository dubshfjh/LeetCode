/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
缺陷：需要使用Map类型的visited记录1个节点的子节点是否已经访问，空间复杂度过高
优化思路：使用1个指针pre记录上一个访问完毕的节点，如果 pre == node->left，则说明node没有右子树而且左子树已经访问完毕了；如果pre == node->right，则说明node的右子树已经访问完毕了
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> my_stk;
        unordered_map<TreeNode*,bool> visited;
        vector<int> res;
        my_stk.push(root);
        while(!my_stk.empty()){
            TreeNode *node = my_stk.top();
            if(node->left && visited.count(node->left)==0){
                my_stk.push(node->left);
                continue;
            }
            if(node->right && visited.count(node->right)==0){
                my_stk.push(node->right);
                continue;
            }
            // res.push_back(node->val);
            visited[node] = true;
            cout<<node->val<<endl;
            my_stk.pop();
        }
        return res;

    }
};

使用pre替代visited的逻辑错误！！！下面分析具体case
    对于任何拥有左子和右子的节点node，1.左子压入栈中 continue 2. 在左子访问完毕后标记 pre为左子，pop掉左子后栈顶元素为 node 3. 对于node，由于 pre && pre==cur->left，所以不push左子入栈，而是push右子入栈后 continue
    4. 在右子访问完毕后标记 pre为右子，pop掉右子后栈顶元素又为node  5. 对于node，由于pre==cur->right，于是将node->left再次入栈，无穷尽也....！！！
/*
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == NULL){
            return res;
        }
        stack<TreeNode*> my_stk;
        my_stk.push(root);
        TreeNode *cur,*pre;
        pre = NULL;
        while(!my_stk.empty()){
            cur = my_stk.top();
            if(cur->left && (!pre || (pre && pre!=cur->left))){
                my_stk.push(cur->left);
                continue;
            }

            if(cur->right && (!pre || (pre && pre!=cur->right))){
                my_stk.push(cur->right);
                continue;
            }

            res.push_back(cur->val);
            cout<<cur->val<<endl;
            my_stk.pop();
            pre = cur;
        }
        return res;
    }
};
*/

递归Code
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        int root_val;
        vector<int> left_vec,right_vec;
        if(root == NULL){
            return left_vec;
        }
        left_vec = postorderTraversal(root->left);
        right_vec = postorderTraversal(root->right);
        root_val = root->val;

        left_vec.insert(left_vec.end(),right.begin(),right.end());
        left_vec.insert(left_vec.end(),root_val);
        return left_vec;
    }
};

迭代Code
对于任一节点P，

1）先将节点P入栈；

2）若P不存在左孩子和右孩子，或者P存在左孩子或右孩子，但左右孩子已经被输出，则可以直接输出节点P，并将其出栈，将出栈节点P标记为前一个访问完毕的节点(pre)，再将节点P pop出栈；

3）若不满足2）中的条件，则依次执行P的"右"子入栈, "左"子入栈("这是为了保证出栈时首先分析左孩子，再分析右孩子")，当前节点P设置为当前的栈顶，之后重复操作2）；

4）直到栈空，遍历结束。

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *cur,*pre;
        pre = NULL;//指针指向 上一个访问的节点
        cur = root;//指针指向 当前的节点
        if(cur == NULL){
            return res;
        }
        stack<TreeNode*> my_stk;
        my_stk.push(root);
        while(!my_stk.empty()){
            cur = my_stk.top();//当前分析节点 为 栈顶
            if((cur->left==NULL && cur->right==NULL) || (pre && (pre==cur->left || pre==cur->right)) ){//如果(pre为cur->left&&cur)，说明cur的右子树为空而且左子树已经访问完毕；如果(pre为cur->right&&cur)。说明cur的左右子树已经访问完毕
            //如果当前节点没有左右孩子，或者有左孩子/右孩子，但已经被访问完毕,则直接输出该节点，将其出栈，将其标记为前一个访问完毕的节点(pre)
                my_stk.pop();
                res.push_back(cur->val);
                pre = cur;
            }
            else{
                if(cur->right){//如果不满足上面两种情况,则将其右孩子，左孩子依次入栈  
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

由于后序为"左->右->中"，所以考虑先获得"中->右->左"的数组后reverse得到结果，为了得到"中->右->左"：while(!stack.empty){ 1.visit(中) 2.左子入栈 3.右子入栈}

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> my_stk;
        TreeNode *cur;
        if(root == NULL){
            return res;
        }

        my_stk.push(root);
        while(!my_stk.empty()){
            cur = my_stk.top();
            res.push_back(cur->val);
            my_stk.pop(); //栈顶节点出栈、输出

            //注意，下面入栈顺序不能错 ，因为先左子入栈，后右子入栈
            //这样出栈时先遍历才是右（中->右->左）
            if(cur->left){
                my_stk.push(cur->left);
            }
            if(cur->right){
                my_stk.push(cur->right);
            }
        }

        reverse(res.begin(),res.end());//逆序，就成了后序遍历
        return res
    }
};