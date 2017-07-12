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
     * @param T1, T2: The roots of binary tree.
     * @return: True if T2 is a subtree of T1, or false.
     */
    public boolean isSubtree(TreeNode T1, TreeNode T2) {
        // write your code here
        if (T2 == null) {
        	return true;
        } else if (T1 == null) {
        	return false;
        }

        if(helpSubTree(T1, T2)) {
        	return true;
        } else {
        	if(isSubtree(T1.left, T2) || isSubtree(T1.right, T2)) {
        		return true;
        	}
        	return false;
        }
    }

    private boolean helpSubTree(TreeNode t1, TreeNode t2) {
    	if (t1 == null || t2 == null) {
    		return t1 == t2;
    	} else {
    		if (t1.val != t2.val) {
    			return false;
    		} else {
    			return helpSubTree(t1.left, t2.left) && helpSubTree(t1.right, t2.right);
    		}
    	}
    }
}