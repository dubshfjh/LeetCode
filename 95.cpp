/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
下面的回溯思想完全错误，应该为每层递归增加一个上限和下限
class Solution {
public:
    vector<TreeNode*> res;
    vector<TreeNode*> generateTrees(int n) {
        vector<int> visited(n+1,0);
        for(int i=1;i<=n;i++){
            TreeNode *root = new TreeNode(i);
            visited[i]=1;
            cout<<"i: "<<i<<",,,";
            get_left(root,root,n,visited);
            get_right(root,root,n,visited);
            cout<<endl;
            visited[i]=0;
            res.push_back(root);
        }
        return res;
    }

    void get_left(TreeNode *root,TreeNode *node,int n,vector<int> visited){
        if(node->val==1){
            return;
        }
        for(int i=1;i<node->val;i++){
            if(visited[i]==0){
                cout<<i<<",,,";
                visited[i]=1;
                TreeNode *temp = new TreeNode(i);
                node->left=temp;
                get_left(root,temp,n,visited);
                get_right(root,temp,n,visited);
                visited[i]=0;    
            }
        }
    }

    void get_right(TreeNode *root,TreeNode *node,int n,vector<int> visited){
        if(node->val==n){
            return;
        }
        for(int i=node->val+1;i<=n;i++){
            if(visited[i]==0){
                cout<<i<<",,,";
                visited[i]=1;
    
                TreeNode *temp = new TreeNode(i);
                node->right=temp;
                get_left(root,temp,n,visited);
                get_right(root,temp,n,visited);
                visited[i]=0;
            }
        }
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
递归思想，规定当前节点的取值区间，左区间为[low,i-1]，右区间为[i+1,high]，依次选择当前节点的根节点，然后对左右子序列再分别建树。

由于左右子序列建树的结果也可能不止一种，需要考虑所有搭配情况。

vector<TreeNode *> left代表所有valid左子树。
vector<TreeNode *> right代表所有valid右子树。

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n==0){
            vector<TreeNode*> nulltree;
            return nulltree;
        }
        return getoneLayer(1,n);//初始取值区间为1-n
    }

    vector<TreeNode*> getoneLayer(int low,int high){//获得取值区间为[low,high]之间的节点，并为每个节点构建其左、右子树
        vector<TreeNode*> cur_node;
        if(low>high){//取值区间无元素(low>high)说明上一层节点不应该有这侧的子树(eg. n=3时，1->2中"2"的左子区间为[2-1,2]，此时"2"左子节点为NULL )
           cur_node.push_back(NULL);
        }
        else if(low==high){//low==high，说明上一层的节点在本侧的子树只有low这个节点(n=3时，1->2中"2"的右子区间为[2+1,3])
            TreeNode *temp = new TreeNode(low);
            cur_node.push_back(temp);
        }
        else{
            for(int i=low;i<=high;i++){//分析当前区间的每个节点i
                vector<TreeNode*> left_child = getoneLayer(low,i-1);//节点i的左子树取值区间为[low,i-1]，获得其左子节点的列表
                vector<TreeNode*> right_child = getoneLayer(i+1,high);//节点i的右子树取值区间为[i+1,high]

                for(int j=0;j<left_child.size();j++){//当节点i的左/右子树不存在时，下一层返回的节点列表中仍然存在元素[0]=NULL
                    for(int k=0;k<right_child.size();k++){
                        TreeNode *temp = new TreeNode(i);
                        temp->left=left_child[j];
                        temp->right=right_child[k];
                        cur_node.push_back(temp);
                    }
                }
                       
            }
        }
        return cur_node;
    }
};