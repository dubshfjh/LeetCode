E.g. 以count[n]表示 n个节点的二叉查找树的数目，包含{ 以1为root的BST数目(左子树为0个节点,右子树为n-1个节点)，以2为root的BST数目(左子树为1个节点,右子树为n-2个节点)}..... 以n为root的BST数目(左子树为n-1个节点，右子树为0个节点) }
count[0]: 包含0个节点的BST只有1棵null树，count[0] = 1
count[1]：包含1个节点的BST只有以1为root的BST数目(左子树为0个节点，右子树为0个节点)，count[1] = 1
则 count[n] = count[0] * count[n-1] {以1为root,此类BST左子树节点数为0；BST右子树节点为 n-1} + 
count[1] * count[n-2] {以2为root, 此类BST左子树节点数为1；BST右子树节点数为 n-2} + ... + count[n-1] * count[0] {以n-1为root,此类BST左子树节点数为n-1；BST右子树节点为0}

public class Solution {
    /**
     * @paramn n: An integer
     * @return: An integer
     */
    public int numTrees(int n) {
        // write your code here
        if (n == 0) {
            return 1;
        }
        int[] count = new int[n + 1];
        count[0] = 1;
        count[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= i - 1; j++) {//j 代表 以i为root的查找树的 左子树节点数目(0...i-1)； i-j-1代表右子树节点数目
                count[i] += count[j] * count[i - j -1];
            }
        }
        return count[n];
    }
}