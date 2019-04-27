import java.util.ArrayList;
import java.util.List;

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
//class Leetcode872 {
//    public boolean leafSimilar(TreeNode root1, TreeNode root2) {
//        if (null == root1 || null == root2) {
//            return null == root1 && null == root2;
//        }
//        List<TreeNode> leafs = new ArrayList<>();
//        traverseRecordLeaf(root1, leafs);
//        return traverseCompareLeaf(root2, leafs);
//    }
//
//    private void traverseRecordLeaf(TreeNode root, List<TreeNode> path) {
//        if (null == root) {
//            return;
//        }
//        traverseRecordLeaf(root.left, path);
//        if (null == root.left && null == root.right) {
//            path.add(root);
//        }
//        traverseRecordLeaf(root.right, path);
//    }
//
//    private boolean traverseCompareLeaf(TreeNode root, List<TreeNode> leafs) {
//        if (null == root) {
//            return true;
//        }
//        if (!traverseCompareLeaf(root.left, leafs)) {
//            return false;
//        }
//        if (null == root.left && null == root.right) {
//            TreeNode leafToCompare = leafs.remove(0);
//            if (null == leafToCompare || root.val != leafToCompare.val) {
//                return false;
//            }
//        }
//        return traverseCompareLeaf(root.right, leafs);
//    }
//
//    public class TreeNode {
//        int val;
//        TreeNode left;
//        TreeNode right;
//        TreeNode(int x) { val = x; }
//    }
//}