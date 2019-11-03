import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Leetcode1110 {
    class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) { val = x; }
    }

    class Solution {
        /**
         * 1.递归分析每一层，如果当前节点被删除，则它的左子&右子将作为newRoot；如果当前节点为newRoot && 自身没被删除，则它应进入result
         *   如果当前节点不为newRoot，则它属于祖先节点中最靠近的newRoot所在的子树，不需要额外考虑
         * 2.不管当前节点本身的属性，当它的左右子树递归遍历完毕后，如果左/右子树本身被删除，则断开node与子树的连接，避免最终的“真实root”仍然挂着整颗二叉树
         * @param root
         * @param to_delete
         * @return
         */
        public List<TreeNode> delNodes(TreeNode root, int[] to_delete) {
            List<TreeNode> result = new ArrayList<>();
            if (null == root || null == to_delete || 0 == to_delete.length) {
                result.add(root);
                return result;
            }
            Set<Integer> toDeleteSet = new HashSet<>();
            for (int toDeleteVal : to_delete) {
                toDeleteSet.add(toDeleteVal);
            }
            traverseTree(root, toDeleteSet, true, result);
            return result;
        }

        private void traverseTree(TreeNode node, Set<Integer> toDelete, boolean isNewRoot, List<TreeNode> result) {
            if (null == node) {
                return;
            }
            if (isNewRoot && !toDelete.contains(node.val)) {
                result.add(node);
            }

            boolean childIsNewRoot = toDelete.contains(node.val);
            traverseTree(node.left, toDelete, childIsNewRoot, result);
            traverseTree(node.right, toDelete, childIsNewRoot, result);

            // 当子节点需要删除时，在递归遍历完子树后，断开node与子节点的链接关系
            if (node.left != null && toDelete.contains(node.left.val)) {
                node.left = null;
            }
            if (node.right != null && toDelete.contains(node.right.val)) {
                node.right = null;
            }
        }
    }
}
