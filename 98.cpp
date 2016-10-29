/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
因为每个Node取值区间为(全部左侧子孙descendant节点,全部右侧子孙descendant)，
但是如果直观地在每一层都检索其全部左子孙、右子孙，那么时间复杂度简直就是在作死。

思想：为每一层节点规定其取值开区间(而不是闭区间)！！！初值为(INT_MIN-1,INT_MAX+1) PS:这是因为INT_MIN-1 = INT_MAX,INT_MAX+1=INT_MIN
对每一层节点，校验本层节点node取值位于(low,high) && 其左子树是否位于(low,node->val) && 其右子树是否位于(node->val,high)

PS：double变量接受INT_MIN/INT_MAX后，再 -1/+1才不会出错， 闭区间导致的bug详见代码注释
class Solution {
public:
    bool isValidBST(TreeNode* root){
        // double test=INT_MIN; //这样做结果为-1，正确
        // cout<<(test-1-INT_MIN)<<"..."<<endl;
        // double test=INT_MIN-1; //这样做结果为|INT_MIN|+INT_MAX
        // cout<<(test-INT_MIN)<<"..."<<endl;
        cout<<INT_MIN-(INT_MIN+1)<<endl;
        double lowlimit = INT_MIN;
        double highlimit = INT_MAX;
        if(root==NULL){
            return true;
        }
        return check_valid(root,lowlimit-1,highlimit+1);//必须初始化为开区间(INT_MIN-1,INT_MAX+1)，而不能初始化为闭区间[INT_MIN,INT_MAX]
    }

    bool check_valid(TreeNode *node,double low,double high){//必须定义开区间(low,high)，如果使用闭区间则左子取值为[low,node-1]，[node+1,high]。因为在没有正确使用double类型变量时，INT_MIN-1=INT_MAX;INT_MAX+1=INT_MIN。
        bool valid = false;//如果当前节点为INT_MIN，那么它的左子树区间则为[INT_MIN,INT_MAX(INT_MIN-1)]，从而取值同样为INT_MIN的左子节点也在该区间内，错误地认为本树为valid。同理，当前node为INT_MAX时，其右子区间为[INT_MIN,INT_MAX]，将误认为INT_MAX也为合法的右子节点
        // cout<<"low: "<<low<<" high: "<<high<<endl;
        if(node->val-low>0 && node->val-high<0){
            valid = true;
            if(node->left){
                
                valid=valid && (check_valid(node->left,low,node->val));
            }
            if(node->right){
                valid=valid && (check_valid(node->right,node->val,high));
            }
            return valid;
        }   
        else{
            return valid;
        }
    }
};
