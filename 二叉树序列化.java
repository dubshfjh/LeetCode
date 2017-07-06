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
二叉树的序列化：将二叉树的{ preOrder序列 + ";" + inOrder序列 } 组合成的字符串返回，如果要求真实序列化，只需要返回String.getBytes()即可
二叉树的反序列化：将序列化字符串split开后，转化为经典题"二叉树preOrder序列 + inOrder序列" 构建完整的二叉树，可以基于递归思想，
    preOrder：根左右，inOrder：左根右。在每一层递归中定位当前子树的根节点value，构建节点后再递归创建左右子树
    
    1.根据每层preOrder的preS构建根节点，然后在inOrder序列中找到 .equals(preOrder[preS]) 的节点下标i，得到 左右子树的size 后，
    2. 再计算 左右子树 在preOrder & inOrder 序列中的start 和 end下标，递归创建左右子树即可

遇到的坑：1. TreeNode 的节点取值为int, 但是序列化后的字符串中 节点取值已经变成了String，因此在"序列化" & "反序列化"时 要分别注意
     int->String；String->int
2. 由于序列化后的结果为String这个引用类型，在inOrder序列中寻找 preOrder[preS]时，不能 使用 inOrder[i] == preOrder[preS]来比较，而应该使用
    inOrder[i].equals(preOrder[preS]) ！！！
class Solution {
    /**
     * This method will be invoked first, you should design your own algorithm
     * to serialize a binary tree which denote by a root node to a string which
     * can be easily deserialized by your own "deserialize" method later.
     */
    private void preOrder(TreeNode root, StringBuilder res) {
        if (root == null) {
            return;
        }
        String curNodeStr = (res.length() == 0) ? "" + root.val : ("," + root.val);
        res.append(curNodeStr);
        preOrder(root.left, res);
        preOrder(root.right, res);
    }

    private void inOrder(TreeNode root, StringBuilder res) {
        if (root == null) {
            return;
        }
        inOrder(root.left, res);
        String curNodeStr = (res.length() == 0) ? "" + root.val : ("," + root.val);
        res.append(curNodeStr);
        inOrder(root.right, res);
    }

    public String serialize(TreeNode root) {
        // write your code here
        if (root == null) {
            return "";
        }
        StringBuilder preRes = new StringBuilder();
        StringBuilder inRes = new StringBuilder();
        preOrder(root, preRes);
        inOrder(root, inRes);
        // System.out.println(preRes.toString());
        // System.out.println(inRes.toString());
        return preRes.toString() + ";" + inRes.toString();
    }

    /**
     * This method will be invoked second, the argument data is what exactly
     * you serialized at method "serialize", that means the data is not given by
     * system, it's given by your own serialize method. So the format of data is
     * designed by yourself, and deserialize it here as you serialize it in
     * "serialize" method.
     */
    public TreeNode deserialize(String data) {
        // write your code here
        if (data.length() == 0) {
            return null;
        }
        String[] temp = data.split(";");
        String[] preOrderList = temp[0].split(",");
        String[] inOrderList = temp[1].split(",");
        return helpBuild(preOrderList, 0, preOrderList.length - 1, inOrderList, 0, inOrderList.length - 1);
    }

    private TreeNode helpBuild(String[] pre, int preS, int preE, String[] inOrder, int inS, int inE) {
        if (preS > preE || inS > inE) {
            return null;
        }
        int curValue = Integer.parseInt(pre[preS]);
        TreeNode root = new TreeNode(curValue);
        int i = inS;
        for (; i <= inE; i++) {
            //if (inOrder[i] == pre[preS]) {
            if (inOrder[i].equals(pre[preS])) {
                break;
            }
        }
        int leftSize = i - inS;
        int rightSize = inE - i;
        root.left = helpBuild(pre, preS + 1, preS + leftSize, inOrder, inS, inS + leftSize - 1);
        root.right = helpBuild(pre, preS + leftSize + 1, preE, inOrder, i + 1, inE);
        return root;
    }

    public static void main(String[] args) {
        Solution obj = new Solution();
        String temp = "1,2" + ";" + "1,2";
        obj.deserialize(temp);
    }
}

