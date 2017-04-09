/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
为每个节点记录其所在层level，并记录树已遍历节点的最大level(total_level)
    给出判断树的层数>=3时是否已遍历过所有最底层叶节点的方法：
        当前节点为叶节点，而且该节点所在level < total_level，
        因为在dfs遍历完全二叉树时，只有遍历了全部左侧的最底层叶节点后，才会进入右侧的非最底层叶节点
    一旦发现最底层叶节点遍历完毕，则不再进行dfs

"运行时间炸了！！！！"
class Solution {
public:
    int total_level,leaf_index;
    bool last_deepleaf = false;
    int countNodes(TreeNode* root) {
        total_level = leaf_index = 0;
        if(!root){
            return 0;
        }
        dfs(0,root);
        return pow(2,total_level)+leaf_index-1;
    }

    void dfs(int level,TreeNode *node){//level代表node处于第level+1层，算法对于最后叶节点的判断逻辑只对层数>=3的完全二叉树有效,如果输入为层数<=2的完全二叉树，则last_deepleaf始终为false，将完整执行dfs
        if(!last_deepleaf){
            if(!node->left && !node->right){//node为叶节点
                if(level >= total_level){//node为最深层的叶子节点
                    total_level = level;
                    leaf_index++;
                }
                else{//node为倒数第二层的叶子节点，因此last 处于最底层的叶子节点已经分析过了
                    last_deepleaf = true;
                }
            }
            else{
                if(node->left){
                    dfs(level+1,node->left);
                }
                if(node->right){
                    dfs(level+1,node->right);
                }
            }
        }
    }
};


进一步利用完全二叉树概念，对于以Node为根节点的子树而言，分 子树为满二叉树/非满二叉树 2种情况讨论
1. 要么node子树的最左侧高度height_l(始终为左子树高度) == node子树的最右侧高度height_r，此时子树为满二叉树，直接返回2^height_l-1，PS：height_l始终为左子树高度，但height_r只有在满二叉树中才会 == 左子树的高度!!!!!!
2. 要么node子树的最左侧高度height_l>node子树的最右侧高度height_r，此时与满二叉树相比，子树只是在最底层少了些叶节点，按照正常dfs流程返回 (node本身)+(node左子树节点数)+(node右子树节点数)作为结果。
   对于last 最底层叶节点所处子树而言，要么该子树为完全二叉树；要么该子树的右子树为NULL 而且 该子树的左子树为完全二叉树
   e.g.  1      1
       1  1;   1

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root){
            return 0; 
        }
        int h_left,h_right;
        h_left = h_right = 0;
        TreeNode *node = root->left;
        while(node){
            h_left++;
            node=node->left;
        }
        node = root->right;
        while(node){
            h_right++;
            node = node->right;
        }
        if(h_left == h_right){
            return pow(2,h_left+1)-1;
        }
        else{
            return 1+countNodes(root->left)+countNodes(root->right);
        }
    }
};
