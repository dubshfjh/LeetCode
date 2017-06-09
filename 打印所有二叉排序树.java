/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
包含1-n的 Unique BST = {以1为root的BST集合，以2为root的BST集合...以n为root的BST集合}
以 i 为root的BST集合(设取值范围为[low, high]) = {左子树BST集合} + i +{右子树BST集合}，而左子树BST的取值范围为 [low, i-1]，右子树BST的取值范围为 [i+1, high]
public class Solution {
    public List<TreeNode> generateTrees(int n) {
        if (n == 0) {//当初始的 low > high 时(即 1 > n时)，如果进入helpGenerate方法，则List<TreeNode>中会有一个null元素，即res.size==1，res.get(0) == null，因此必须单独判断n == 0的情况
            return new ArrayList<TreeNode>();
        }
        return helpGenerate(1, n);
    }

    public List<TreeNode> helpGenerate(int low, int high) {//取值范围为 [low,high] 的BST集合，包括 {以low为root的BST集合，以low+1为root的BST集合...以high为root的BST集合}
        List<TreeNode> curLevSet = new ArrayList<TreeNode>();
        if (low > high) {//取值范围不存在（即节点数为0）的BST集合只有1棵空树，即根节点为null的BST。
            curLevSet.add(null);
            return curLevSet;
        }

        for (int i = low; i <= high; i++) {
            List<TreeNode> lChildSet = helpGenerate(low, i - 1);
            List<TreeNode> rChildSet = helpGenerate(i + 1, high);
            for (TreeNode lChildRoot:lChildSet) {
                for (TreeNode rChildRoot:rChildSet) {
                    TreeNode curRoot = new TreeNode(i);
                    curRoot.left = lChildRoot;
                    curRoot.right = rChildRoot;
                    curLevSet.add(curRoot);
                }
            }
        }
        return curLevSet;
    }
}

基于DP思想
result[i] 存储取值范围为{1...i}的BST集合. For the result for length i+1, select the root node j from 0 to i, combine the result from 
left side and right side. Note we have to 基于res[len - j - 1]重新构建每一棵右子树，因为右子树中每个节点的取值实际上是 res[len - j -1]中节点.val + (j + 1)
public class Solution {
    public List<TreeNode> generateTrees(int n) {
        List<TreeNode>[] res = new ArrayList[n + 1];
        res[0] = new ArrayList<TreeNode>();
        if (n == 0) {
            return res[0];
        }
        res[0].add(null);//取值范围为{1...0}的BST集合只有1棵null的BST
        for (int len = 1; len <= n; len++) {
            //基于res[0...len-1] 得到 左子树BST集合，以及取值向左offset了 "j+1" 的右子树BST集合
            res[len] = new ArrayList<TreeNode>();//取值为[1...len]的BST = {以1为root的BST, 以2为root的BST...以len为root的BST}
            for (int j = 0; j < len; j++) {// root 为 j+1 的BST集合
                for (TreeNode lChildRoot : res[j]) {//左子树BST 为 取值范围为 [1...j-1] 的BST集合
                    for (TreeNode offsetRChild : res[len - j - 1]) {//右子树BST为 取值范围为 [j+2...len]的BST集合，可以通过 取值范围为 
                        //[1...len-j-1]的BST集合 进行 "j+1"的offset 得到，毕竟这2个区间的对称点为 curRoot(取值为j+1)
                        TreeNode curRoot = new TreeNode(j + 1);
                        curRoot.left = lChildRoot;
                        curRoot.right = createRightTree(offsetRChild, j + 1);
                        res[len].add(curRoot);
                    }
                }
            }
        }
        return res[n];
    }

    public TreeNode createRightTree(TreeNode offsetNode, int offset) {
        if (offsetNode == null) {
            return null;
        }
        TreeNode curNode = new TreeNode(offsetNode.val + offset);
        curNode.left = createRightTree(offsetNode.left, offset);
        curNode.right = createRightTree(offsetNode.right, offset);
        return curNode;
    }
}