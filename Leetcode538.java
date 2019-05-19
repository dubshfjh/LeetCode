import java.util.ArrayList;
import java.util.List;

public class Leetcode538 {

     class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) { val = x; }
     }
    class Solution {
        int currentIndex = 0;
        public TreeNode convertBST(TreeNode root) {
            if (null == root) {
                return root;
            }
            List<Integer> inOrderValList = new ArrayList<Integer>();
            createInorderValList(root, inOrderValList);
            int[] presumInOrderValArr = new int[1 + inOrderValList.size()];
            presumInOrderValArr[0] = 0;
            for (int i = 1; i <= inOrderValList.size(); i++) {
                presumInOrderValArr[i] = presumInOrderValArr[i - 1] + inOrderValList.get(i - 1);
            }
            inOrderReplaceTreeNode(root, presumInOrderValArr);
            return root;
        }

        private void createInorderValList(TreeNode root, List<Integer> inOrderValList) {
            if (null == root) {
                return;
            }
            createInorderValList(root.left, inOrderValList);
            inOrderValList.add(root.val);
            createInorderValList(root.right, inOrderValList);
        }

        private void inOrderReplaceTreeNode(TreeNode root, int[] presumInOrderValArr) {
            if (null == root) {
                return;
            }
            inOrderReplaceTreeNode(root.left, presumInOrderValArr);
            // 计算sum(currentIndex, ..., size-1)
            int curNodeValue = presumInOrderValArr[presumInOrderValArr.length - 1] - presumInOrderValArr[currentIndex];
            root.val = curNodeValue;
            currentIndex++;
            inOrderReplaceTreeNode(root.right, presumInOrderValArr);
        }
    }
}
