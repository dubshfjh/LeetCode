使用分治法：定义每层递归返回 当前子树中 至少包含 A节点 or B节点 中1个的最近祖先节点
由于Tree中只有"最近公共祖先Node"能满足: 左、右子树中各包含 A,B 中的1个。
每层递归的定义如下：
1. 终止条件：如果 当前节点为 null，则返回 null

2. 如果 当前节点 == A or B，则返回自身即可
	分类讨论：2.1 如果A是B的祖先节点，直接返回A并没有逻辑错误，e.g. Tree：{1->2;1->3}，A：1, B：3，那么确实不需要再去遍历3节点
	2.2 如果A与B并没有祖先关系(即分属于不同子树)，那么从root开始DfS的过程自然会同时 遍历到A节点，以及B节点

3. Divide：分别 对left子节点 和 right子节点 递归分析，并分别记录 二者的结果 
4. Conquer：Merge 左右子树的结果：如果 二者都不为空，则当前节点为"最近公共祖先"；
	如果有1个不为空，则说明当前节点的子树只包含 A,B中的1个，返回不为null的子树结果；
	如果二者都为空，则说明当前节点的子树 不包含A,B，返回null即可
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
     * @param root: The root of the binary search tree.
     * @param A and B: two nodes in a Binary.
     * @return: Return the least common ancestor(LCA) of the two nodes.
     */
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode A, TreeNode B) {
        // write your code here
        if (root == null) {
        	return null;
        } else if (root == A || root == B) {
        	return root;
        } else {
        	TreeNode left = lowestCommonAncestor(root.left, A, B);
        	TreeNode right = lowestCommonAncestor(root.right, A, B);
        	if (left != null && right != null) {
        		return root;
        	} else if (left != null) {
        		return left;
        	} else if (right != null) {
        		return right;
        	} else {
        		return null;
        	}
        }
    }
}


解法2：参照剑指offer的思想，使用两个链表分别记录 root->A 和 root->B 的path，然后求解两个链表的最后1个重合节点即可
踩到的坑：
	1. 在dfs(root, path)执行完毕时，由于在每层递归对path中本层root节点的删除，最后path将为空；为了保存root->A的路径
		必须在dfs遇到 A 时，用一个新的List 记录当前递层的路径，接口修正为 (root, path, recordPath)
		ps：由于本题的递归被设计为 从path移除 root的左右子节点，所以当 dfs 整体结束时path仍然保存有根节点
		因此，在dfs搜索到 A 后，应该先 path.clear()，再dfs 搜索 B 

	2. 当dfs 搜索到 target 后，不能直接使用 recordPath = new ArrayList<>(path) 来进行备份，
		让我们称呼 recordPath 变量从root->上一层过程中的 取值为 内存地址 List@467； new ArrayList<>(path)这个对象的内存地址为 List@468
		此时 recordPath = new ArrayList<>(path)  只是做到了  recordPath = {List@467 ==> List@468}
		但我们需要的是修改{root->上一层}过程中传递的 List@468位置的对象
	解决方案：使用 recordPath.addAll(path) 往List@468 中填充数据；而不是使得本层递归的局部变量 指向另一个对象 List@467
public class Solution {
    /**
     * @param root: The root of the binary search tree.
     * @param A and B: two nodes in a Binary.
     * @return: Return the least common ancestor(LCA) of the two nodes.
     */
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode A, TreeNode B) {
        if (root == null) {
            return null;
        }
        List<TreeNode> tempPath = new LinkedList<TreeNode>();

        List<TreeNode> pathA = new ArrayList<TreeNode>();
        tempPath.add(root);
        findPath(root, A, tempPath, pathA);

        tempPath.clear(); //由于递归被设计成：只会在递归完左右子树 后 移除左右子节点; 而不会移除当前层的root，所以最后dfs完成后root会保留下来
        List<TreeNode> pathB = new ArrayList<TreeNode>();
        tempPath.add(root);
        findPath(root, B, tempPath, pathB);

        int length = Math.min(pathA.size(), pathB.size());
        TreeNode res = null;
        for (int i = 0; i < length; i++) {
            if (pathA.get(i) != pathB.get(i)) {
                break;
            } else {
                res = pathA.get(i);
            }
        }
        return res;
    }

    private boolean findPath(TreeNode root, TreeNode target, List<TreeNode> path, List<TreeNode> res) {
        if (root == null) {
            return false;
        }
        if (root == target) {
//            res = new ArrayList<TreeNode>(path); 这样的话只是让本层的res变量指向了另一个对象(e.g. res：List@468->List@469)，
// 但我们需要的是修改上一层传过来的List@468地址对应的对象，因此修正为：List@468.addAll(data)
            res.addAll(path);
            return true;
        } else {
            path.add(root.left);
            boolean lFind = findPath(root.left, target, path, res);
            path.remove(root.left);
            if (!lFind) {
                path.add(root.right);
                boolean rFind = findPath(root.right, target, path, res);
                path.remove(root.right);
                return rFind;
            }
            return lFind;
        }
    }

//     public static void main(String[] args) {
//         TreeNode node1 = new TreeNode(1);
//         TreeNode node2 = new TreeNode(2);
//         TreeNode node3 = new TreeNode(3);
//         TreeNode node4 = new TreeNode(4);
//         node1.right = node2;
//         node2.right = node3;
//         node3.right = node4;
//         Solution obj = new Solution();
//         obj.lowestCommonAncestor(node1, node2, node4);
//     }
}
