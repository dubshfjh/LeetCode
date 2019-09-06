
public class Leetcode865 {
    public class TreeNode {
         int val;
         TreeNode left;
         TreeNode right;
         TreeNode(int x) { val = x; }
     }

    class Solution {
        class NodeData {
            private int depth;
            private TreeNode deepestSubTreeNode;

            public NodeData(int depth, TreeNode deepestSubTreeNode) {
                this.depth = depth;
                this.deepestSubTreeNode = deepestSubTreeNode;
            }
        }

        public TreeNode subtreeWithAllDeepest(TreeNode root) {
            if (null == root) {
                return root;
            }
            return calMaxDepth(root, 1).deepestSubTreeNode;
        }

        /**
         * 计算以curNode为根节点的子树中，最大的深度 + 包含所有最大深度子节点的 “子树Root”
         * @param curNode
         * @param depth
         * @return
         */
        private NodeData calMaxDepth(TreeNode curNode, int depth) {
            if (null == curNode) {
                return new NodeData(depth, null);
            }
            NodeData leftSubTreeData = calMaxDepth(curNode.left, depth + 1);
            NodeData rightSubTreeData = calMaxDepth(curNode.right, depth + 1);
            int curMaxDepth = 1 + Math.max(leftSubTreeData.depth, rightSubTreeData.depth);
            if (leftSubTreeData.depth == rightSubTreeData.depth) {
                // 左，右子树均包含maxDepth的子节点，则当前root才是“包含所有最大深度子节点的 子树Root”
                return new NodeData(curMaxDepth, curNode);
            } else {
                // 仅左子树包含maxDepth的子节点，则curNode.leftNode中“包含最大深度子节点的子树Root”，就是curNode的计算结果
                // 否则，curNode.right中“包含最大深度子节点的子树Root”,就是curNode的计算结果
                return leftSubTreeData.depth > rightSubTreeData.depth
                        ? new NodeData(curMaxDepth, leftSubTreeData.deepestSubTreeNode)
                        : new NodeData(curMaxDepth, rightSubTreeData.deepestSubTreeNode);
            }
        }
    }
}
