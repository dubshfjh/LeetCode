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
 
 
public class Solution {
    /**
     * @param root: The root of binary tree.
     * @return: Level order a list of lists of integer
     */
    ArrayList<ArrayList<Integer>> res;
    public ArrayList<ArrayList<Integer>> levelOrder(TreeNode root) {
        // write your code here
        res = new ArrayList<>();
        helpLevelOrder(root, 0);
        return res;
    }

    private void helpLevelOrder(TreeNode root, int level) {//将第level层递归的root.val添加到整体结果的第level-1个List中即可
    	if (root == null) {
    		return;
    	}
    	if (res.size() < level + 1) { //由于采用了 先序遍历 的递归模式，所以不需要使用 while(res.size() < level + 1)，因为在上一层递归中res就已经扩容到size == level了
    		res.add(new ArrayList<Integer>());
    	}
    	List<Integer> curLevel = res.get(level);
    	curLevel.add(root.val);
    	helpLevelOrder(root.left, level + 1);
    	helpLevelOrder(root.right, level + 1);
    }
}