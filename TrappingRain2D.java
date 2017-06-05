public class Solution {
    /**
     * @param heights: a matrix of integers
     * @return: an integer
     */
    class Node {
        int i,j,val;
        public Node (int i, int j, int val) {
            this.i = i;
            this.j = j;
            this.val = val;
        }
    }

    public int trapRainWater(int[][] heights) {
        // write your code here
        Queue<Node> minHeap = new PriorityQueue<Node>(
            new Comparator<Node>(){
                int compare (Node o1, Node o2) {
                    return o1.val - o2.val;
                }
        });
        int row = heights.length, col = heights[0].length;
        Node[][] nodesArr = new Node[row][col];
        boolean[][] visit = new boolean[row][col];

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                nodesArr[i][j] = new Node(i, j, heights[i][j]);
            }
        }
        for (int i = 0; i < row; i++) {
            minHeap.offer(nodesArr[i][0]);
            visit[i][0] = true;
            minHeap.offer(nodesArr[i][col - 1]);
            visit[i][col - 1] = true;
        }

        for (int i = 1; i < col - 1; i++) {
            minHeap.offer(nodesArr[0][i]);
            visit[0][i] = true;
            minHeap.offer(nodesArr[row - 1][i]);
            visit[row - 1][i] = true;
        }
        int[] dirI = {-1, 1, 0, 0};
        int[] dirJ = {0, 0, -1, 1};
        int res = 0;
        while (!minHeap.isEmpty()) {//从外围向内围灌水，外围提供的水的高度为外围柱子的短板： 即min{堆中元素.val}，首先将短板元素的未访问邻居标记为已访问，
                                    //并放入堆中作为短板候选者，如果邻居 比 短板还矮，则该邻居可以积蓄 (短板高度 - 邻居高度) 的rain，循环结束条件为：当前的外围柱子都没有未访问的邻居，导致堆为空
            Node curNode = minHeap.pop();
            int curMinHeight = curNode.val;
            for (int i = 0; i < 4; i++) {
                int nextI = curNode.i + dirI[i];
                int nextJ = curNode.j + dirJ[i];
                if (nextI < 0 || nextI >= row || nextJ < 0 || nextJ >= col || visit[nextI][nextJ]) {
                    continue;
                }
                if (curMinHeight > nodesArr[nextI][nextJ].val) {
                    res += curMinHeight - nodesArr[nextI][nextJ].val;
                }
                minHeap.offer(nodesArr[nextI][nextJ]);
                visit[nextI][nextJ] = true;
            }
        }
        return res;
    }
};

/* 用栈实现DFS遍历，但并不是本题所需要的。。。纯属思路跑偏了
Stack<Node> myStk = new Stack<Node>();
        myStk.push(minHeap.poll());
        int minRainHeight = myStk.peek().val;

        while (!myStk.empty()) {
            Node curNode = myStk.pop();
            visit[curNode.i][curNode.j] = true;
            for (int i = 0; i < 4; i++) {
                int nextI = curNode.i + dirI[i];
                int nextJ = curNode.j + dirJ[i];
                if (nextI < 0 || nextI >= row || nextJ < 0 || nextJ >= col || visit[nextI][nextJ]) {
                    continue;
                }
                myStk.push(nodesArr[nextI][nextJ]);
            }
        }
 */