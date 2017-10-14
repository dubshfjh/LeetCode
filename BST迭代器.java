BST 的顺序迭代：中序遍历，左子->根->右子。因此，每一个需要visit的节点，其左子树整体不存在 or 已被访问； 
反向思考：在访问1个节点时，要先访问其左子树，"左子树"存在/已访问 等价于 "最左侧子节点"存在/已访问

1. 设置一个Stack保存"最左侧路径"上的所有节点，因此任意时间的"top元素"必然是 左子树不存在 or 已访问的元素
2. visit(栈顶元素)，由于要遵循"左根右"的顺序，因此当栈顶存在右子树时，将(栈顶元素->右子) 入栈
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
 * Example of iterate a tree:
 * BSTIterator iterator = new BSTIterator(root);
 * while (iterator.hasNext()) {
 *    TreeNode node = iterator.next();
 *    do something for node
 * } 
 */

public class BSTIterator {
    private Stack<TreeNode> leftPathNodes;
    /*
    * @param root: The root of binary tree.
    */
    public BSTIterator(TreeNode root) {
        // do intialization if necessary
        leftPathNodes = new Stack<TreeNode>();
        if (root != null) {
            // leftPathNodes.add(root);
            pushLeftPath(root);
        }
    }

    /*
     * @return: True if there has next node, or false
     */
    public boolean hasNext() {
        // write your code here
        return leftPathNodes.size() > 0;
    }

    /*
     * @return: return next node
     */
    public TreeNode next() {
        // write your code here
        TreeNode noLSubNode = leftPathNodes.pop();
        if (noLSubNode.right != null) {
            pushLeftPath(noLSubNode.right);
        }
        return noLSubNode;
    }

    private void pushLeftPath(TreeNode node) {
        while (node != null) {
            leftPathNodes.add(node);
            node =  node.left;
        }
    }
}