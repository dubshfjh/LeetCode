/**
 * Definition of TreeNode:
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left, right;
 *     public TreeNode(int val) {
 *         this.val = val;
 *         this.left = this.right = null;
 *     }
 * }
 */
自定义递归函数的返回结果类：
	1. singlePath：左、右子树单侧路径的maxSum，可以不包含任意节点,若包含节点则必须包含当前root节点
	2. maxPath：以当前节点为root的子树中，可以不包含当前节点的，但必须拥有1个以上节点的 {左+右} 两侧路径的maxSum
每一层的递归定义：
	1. 对于空子树，单侧路径可以不包含节点=>singlePath 赋值为0；它的父节点的maxPath必须包含至少1个节点(但不需要为父节点本身)，
		为了使得父节点的maxPath至少添加1个节点，所以当前空子树的 maxPath 赋值为 负无穷大
	
	2. singlePath 必须包含当前节点root，否则这条单侧路径无法延伸到root的上一层父节点(递归的上一层)
		'max(lChildRes.singlePath, rChildRes.singlePath) + root.val'
		如果包含root的单侧最大路径和<0，则singlePath=0!因为root的父节点(递归的上一层)可以接收到下方延伸而来的空路径:'max(singlePath, 0)'
	
	3. maxPath可以不包含当前节点，即最大path处于 左子树 or 右子树中：'max(lChildRes.maxPath, rChildRes.maxPath)'

		maxPath还可能取值为 { max(0,左子path) + root + max(0,右子path) }，如果包含左子 or 右子节点的单侧路径sum < 0，则 singlePath = 0!!!
		'max(maxPath, lChildRes.singlePath + root.val + rChildRes.singlePath)'

class ResultType {
	int singlePath; //左、右子树单侧路径的maxSum(可以不包含任意节点，若包含节点则必须包含当前root节点)，这只是1个中间值
	int maxPath; //在以当前节点为root的子树中，可以不包含当前节点的，但必须拥有1个以上节点的 {左+右} 两侧路径的maxSum，MAX(每个节点的maxPath)就是最终的res
	public ResultType(int singlePath, int maxPath) {
		this.singlePath = singlePath;
		this.maxPath = maxPath;
	}
}
public class Solution {
    /**
     * @param root: The root of binary tree.
     * @return: An integer.
     */
    public int maxPathSum(TreeNode root) {
        // write your code here
        ResultType finalres = helpMaxPathSum(root);
        return finalres.maxPath;
    }

    private ResultType helpMaxPathSum(TreeNode root) {
    	if (root == null) {
    		return new ResultType(0, Integer.MIN_VALUE); //对于空子树，单侧路径可以不包含节点=>singlePath 赋值为0；它的父节点的maxPath必须包含至少1个节点(但不需要为父节点本身)，为了使得父节点的maxPath至少添加1个节点，所以当前空子树的 maxPath 赋值为 负无穷大
    	}
    	ResultType lChildRes = helpMaxPathSum(root.left);
    	ResultType rChildRes = helpMaxPathSum(root.right);
    	int singlePath = Math.max(lChildRes.singlePath, rChildRes.singlePath) + root.val; //singlePath 必须包含当前节点root，否则这条单侧路径无法延伸到root的上一层父节点(递归的上一层)
    	singlePath = Math.max(singlePath, 0); //如果包含root的单侧最大路径和<0，则singlePath=0!因为root的父节点(递归的上一层)可以接收到下方延伸而来的空路径

    	int maxPath = Math.max(lChildRes.maxPath, rChildRes.maxPath); //maxPath可以不包含当前节点，即最大path处于 左子树 or 右子树中
    	maxPath = Math.max(maxPath, lChildRes.singlePath + root.val + rChildRes.singlePath); //maxPath还可能取值为 {max(0,左子path) + root + max(0,右子path)}，如果包含右子节点的单侧路径sum < 0，则 singlePath = 0!!!
    	return new ResultType(singlePath, maxPath);
    }
}