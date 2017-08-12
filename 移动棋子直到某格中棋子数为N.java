本题通过率为50%，因为final target可能为棋盘上的任意一个点，而不一定为初始点！！！
局限的思想(认为最终必然收敛到初始点)：
1. dis[i][j]：棋子从初始位置i->初始位置j的move，dis[i][i] = MAX_VALUE
2. moves[i][j]: 以初始位置i为final target，共需要j枚棋子时的minMove
3. 分析对一个固定 i 作为final target(即收敛位置)时，为了让某个格子中棋子数 >= {1.2...n} 所需的minMove
	moves[i][1] = 0;
	基于贪心策略，对 dis[i][0...n - 1] 进行升序排列，每次先移动距离 i 尽量近的初始棋子
	for j = 2 to n：moves[i][j] = moves[i][j - 1] + dis[i][j - 2];

4. 对于 j = 2 to n，整体的最小move数 = Min(moves[0...n][j])，即 Min{每个i作为final target，为了凑出 j 个棋子所需的最小Move}

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            int n = sc.nextInt();
            int[] x = new int[n];
            int[] y = new int[n];
            for (int i = 0; i < n; i++) {
                x[i] = sc.nextInt();
            }

            for (int i = 0; i < n; i++) {
                y[i] = sc.nextInt();
            }
            Main obj = new Main();
            obj.calMinMove(n, x, y);
        }
    }
//    class Node {
//        int from;
//        int to;
//        int dis;
//        public Node(int from, int to, int dis) {
//            this.from = from;
//            this.to = to;
//            this.dis = dis;
//        }
//    }
    private void calMinMove(int n, int[] x, int[] y) {
//        int pointNum = (maxY - minY + 1) * (maxX - minX + 1);
        int[][] dis = new int[n][n];// dis[i][j]：棋子i->棋盘上任意点j的move
        int[][] moves = new int[n][n + 1];// moves[i][j]: 以i为final target，共需要j枚棋子时的minMove
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = Math.abs(x[i] - x[j]) + Math.abs(y[i] - y[j]);
            }
//            for (int j = minX; j <= maxX; j++) {
//                for (int k = minY; k <= maxY; k++) {
//                    dis[i][j * (maxY - minY) + k] = Math.abs(x[i] - j) + Math.abs(y[i] - k);
//                }
//            }
        }
        for (int i = 0; i < n; i++) {
            dis[i][i] = Integer.MAX_VALUE;
            Arrays.sort(dis[i]);
        }
        for (int i = 0; i < n; i++) {
            moves[i][1] = 0;
            for (int j = 2; j <= n; j++) {
                moves[i][j] = moves[i][j - 1] + dis[i][j - 2];
            }
        }
        System.out.print(0);
        for (int j = 2; j <= n; j++) {
            int minMove = Integer.MAX_VALUE;
            for (int i = 0; i < n; i++) {
                minMove = Math.min(minMove, moves[i][j]);
            }
            System.out.print(" " + minMove);
        }
        System.out.println();
    }
}