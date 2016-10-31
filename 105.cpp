/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
Attetion：如果给constructNode传入参数(vector<int> preorder...),当数组过大时会内存超限；必须给参数设置为引用"&"，即(vector<int> &preorder)

1、确定树的根节点。树根是当前树中所有元素在前序遍历中最先出现的元素。 

2、求解树的子树。找出根节点在中序遍历中的位置，根左边的所有元素就是左子树，根右边的所有元素就是右子树。若根节点左边或右边为空，则该方向子树为空；若根节点边和右边都为空，则根节点已经为叶子节点。 

3、递归求解树。将左子树和右子树分别看成一棵二叉树，重复1、2、3步，直到所有的节点完成定位

前序遍历：node(下标为pre_index),node->left,...,左子树最右节点,node->right,...,右子树最右节点

中序遍历：左子树最左节点(下标为in_index)...左子树最右节点,node(下标为index),右子树最左节点,...,node->right,...,右子树最右节点(下标为in_index+size-1)

(前序，中序遍历：从pre_order中的节点node开始，利用当前子树在in_order的左边界(定义边界是为了加速定位)，以及node->val获得node在中序的位置，从而计算出左、右子树的长度。
然后得到node左、右子树根节点在preorder中的位置，以及两个根节点在inorder中的左边界)


后序遍历：左子树最左节点...左子树最右节点,node->left,右子树最左节点,...右子树最右节点,node->right,node

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size()==0){
            return NULL;
        }
        int size=preorder.size();
        return constructNode(preorder,inorder,0,0,size);
        // TreeNode *root = constructNode(preorder,inorder,0,0,preorder.size());
        // return root;
    }

    TreeNode* constructNode(vector<int> &preorder,vector<int> &inorder,int pre_index,int in_index,int size){//size为当前分析节点[pre_index]的子树节点总数目
        //pre_index为本次需要分析的根节点，in_index存储当前树在in_order中的左边界(用于加速定位元素)
        if(size<=0){
            return NULL;
        }
        TreeNode *node = new TreeNode(preorder[pre_index]);
        int index=0;// 寻找根节点在中序遍历数组的下标
        for(int i=0;i<size;++i){
            if(preorder[pre_index] == inorder[in_index+i]){//利用中序数组算出左子树的节点数目
                index = in_index+i;
                break;
            }
        }

        int leftsize = index - in_index;//[pre_index]为根的左子树节点num
        int rightsize = size - leftsize - 1;//[pre_index]为根的右子树节点num

        //node的左子树根节点为 preorder[pre_index+1]，左子树在中序序列中的左边界为in_index
        node->left = constructNode(preorder,inorder,pre_index+1,in_index,leftsize);

        //node的右子树根节点为 preorder[pre_index+leftsize+1]，右子树在中序序列中的左边界为index+1
        node->right = constructNode(preorder,inorder,pre_index+leftsize+1,index+1,rightsize);
        return node;
    }
};

算法错误！！！！！
思路参见照片105.jpg，但是思路还是有谬误，构建节点node时，定位其左右子树的根节点的方法有偏差（上方代码的定位更加合理，也不需要区分node->left和node->right为空的情况），只需要通过递归不断缩减左右子树的范围即可

遇到[1,2,4,8,5,3,6,7]，[8,4,2,5,1,6,3,7]这组用例就出错了，少了"5"节点，多出了"8"节点
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// class Solution {
// public:
//     TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//         int i,j;
//         if(preorder.size()==0 || inorder.size()==0 || preorder.size()!=inorder.size()){
//             return NULL;
//         }
//         TreeNode *root = new TreeNode(preorder[0]);
//         i=0;
//         j=find_index(inorder,preorder[i]);
//         root = constructNode(root,preorder,inorder,i,j);
//         return root;
//     }  

//     TreeNode* constructNode(TreeNode *node,vector<int>& preorder, vector<int>& inorder,int i,int j) {
//         int index;
//         int size=preorder.size();
//         //找到node的左子节点
//         if(j==0 || size-1-j==size-1-i){
//             node->left=NULL;
//         }
//         else{
//             TreeNode *leftchild = new TreeNode(preorder[i+1]);
//             node->left = leftchild;
//         }

//         //找到node的右子节点
//         if(j==size-1 || inorder[j+1]==preorder[i-1]){
//             node->right=NULL;
//         }
//         else{
//             if(j>1){
//                 int leftchild_right=inorder[j-1];//记录左子树最右节点的值
//                 index = find_index(preorder,leftchild_right);
//             }
//             else{
//                 index = i;
//             }
//             TreeNode *rightchild = new TreeNode(preorder[index+1]);
//             node->right = rightchild;
//         }

//         if(node->left){
//             constructNode(node->left,preorder,inorder,i+1,find_index(inorder,node->left->val));
//         }

//         if(node->right){
//             constructNode(node->right,preorder,inorder,index+1,find_index(inorder,node->right->val));
//         }
//         //cout<<node->val<<" left:"<<node->left<<"  right:"<<node->right<<"  i: "<<i<<"  j: "<<j<<endl;
//         return node;
//     }

//     int find_index(vector<int> order,int val){
//         return find(order.begin(),order.end(),val)-order.begin();
//     }
// };
int main(){
    int a[]={1,2,3};
    int b[]={2,1,3};
    vector<int> pre(a,a+3);
    vector<int> in(b,b+3);
    Solution s = Solution();
    s.buildTree(pre,in); 
    return 0;
}