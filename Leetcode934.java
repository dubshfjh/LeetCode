import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class Leetcode934 {
    class Solution {
        /**
         * 1.首先利用并查集的思想，把同一块大陆的点归并为1个father
         * 2.上下左右搜索每个"this1"
         *   如果在搜索路径上遇到另1个"other1"
         *   2.1 处于同一个大陆，那么不再继续搜索，因为经历"other1"的最优解，必然在以"other1"为起点的搜索过程中
         *   2.2 处于另一个大陆，尝试用此时的搜索路径长度，去更新最优解
         *   如果在搜索路径上遇到另1个"other0"，则增加搜索路径长度，继续搜索
         * 3. 考虑剪枝优化，如果搜索路径长度 > 此时的最优解，则放弃该搜索路径
         *
         * 不过并查集的做法，稍微有点复杂
         * 1.任意找个"1"出发，通过DFS将它所在的大陆全部保存在Queue中
         * 2.分析Queue中的每个元素，采用BFS的思想，向“上 下 左 右”的邻居各搜索1步，即每轮搜索都只使“所有节点的搜索路径 + 1”
         *   2.1 如果邻居节点在 DFS or BFS中已访问过，则忽略
         *   2.2 如果邻居节点未访问 && 取值为"0"，则加入Queue尾部
         *   2.3 如果邻居节点未访问 && 取值为"1"，则说明遇到了另1个大陆的"1"，此时的搜索路径就是最优解
         * @param A
         * @return
         */
        private int[][] directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        public int shortestBridge(int[][] A) {
            if (null == A || 0 == A.length
                    || null == A[0] || 0 == A[0].length) {
                return 0;
            }
            boolean findOneIsland = false;
            Queue<int[]> pointQueue = new LinkedList<>();
            boolean[][] visit = new boolean[A.length][A[0].length];
            //DFS，任意找个"1"出发，通过DFS将它所在的大陆全部保存在Queue中
            for (int i = 0; i < A.length; i++) {
                if (findOneIsland) {
                    break;
                }
                for (int j = 0; j < A[0].length; j++) {
                    if (1 == A[i][j]) {
                        traverseOneIsland(A, i, j, visit, pointQueue);
                        findOneIsland = true;
                        break;
                    }
                }
            }
            // BFS的思想，遍历1个大陆中的每个"1"，向“上 下 左 右”的邻居各搜索1步，直到在第X轮搜索中遇到另1个大陆的"1"
            int curStep = 0;
            while (!pointQueue.isEmpty()) {
                int curQueueSize = pointQueue.size();
                // System.out.println("-----nextRound-----");
                while (curQueueSize-- > 0) {
                    int[] curPoint = pointQueue.poll();
                    // System.out.println("----" + curPoint[0] + "," + curPoint[1]);
                    for (int[] dir : directions) {
                        int nextI = curPoint[0] + dir[0];
                        int nextJ = curPoint[1] + dir[1];
                        if (nextI >= 0 && nextI < A.length
                                && nextJ >= 0 && nextJ < A[0].length
                                && !visit[nextI][nextJ]) {
                            // System.out.println(nextI + "," + nextJ);
                            if (A[nextI][nextJ] == 1) {
                                return curStep;
                            } else {
                                visit[nextI][nextJ] = true;
                                pointQueue.offer(new int[] {nextI, nextJ});
                            }
                        }
                    }
                }
                curStep++;
            }
            return -1;
        }

        /**
         * 从i,j出发DFS搜索，将属于同1个大陆的所有"1"都插入到pointQueue中
         * @param A
         * @param i
         * @param j
         * @param visit
         * @param pointQueue
         */
        private void traverseOneIsland(int[][] A, int i, int j, boolean[][] visit, Queue<int[]> pointQueue) {
            if (i < 0 || i >= A.length
                    || j < 0 || j >= A[0].length
                    || visit[i][j] || A[i][j] == 0) {
                return;
            }
            visit[i][j] = true;
            pointQueue.offer(new int[]{i, j});
            for (int[] dir : directions) {
                traverseOneIsland(A, i + dir[0], j + dir[1], visit, pointQueue);
            }
        }
    }
}
