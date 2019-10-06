import java.util.HashSet;
import java.util.Set;

public class Leetcode874 {
    class Solution {
        private int[][] direction = {{0,1},{1,0},{0,-1},{-1,0}};
        /**
         * 北（0,1），南(0,-1)，西(-1,0)，东(1,0)
         * 从北方向开始，一路右拐则会经历"北->东->南->西"4个方向，如果向左拐，则会经历相反的方向
         * @param commands
         * @param obstacles
         * @return
         */
        public int robotSim(int[] commands, int[][] obstacles) {
            if (null == commands || 0 == commands.length) {
                return 0;
            }
            int dirChangeNum = 0, result = 0;
            int startX = 0, startY = 0;
            Set<String> obstacleSet = new HashSet<>();
            for (int[] obstacle : obstacles) {
                obstacleSet.add(obstacle[0] + "," + obstacle[1]);
            }
            for (int command : commands) {
                if (-1 == command) {
                    dirChangeNum = (dirChangeNum + 1 + 4) % 4;
                } else if (-2 == command) {
                    // 如果直接-1 % 4，则取值就是-1
                    dirChangeNum = (dirChangeNum - 1 + 4) % 4;
                } else {
                    // System.out.println(dirChangeNum);
                    for (int i = 0; i < command && !obstacleSet.contains((startX + direction[dirChangeNum][0]) + "," + (startY + direction[dirChangeNum][1])); i++) {
                        startX += direction[dirChangeNum][0];
                        startY += direction[dirChangeNum][1];
                    }
                    result = Math.max(result, startX * startX + startY * startY);
                }
            }
            return result;
        }
    }
}
