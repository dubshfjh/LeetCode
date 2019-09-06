import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

class Solution {
    public int findMinArrowShots(int[][] points) {
        if (null == points || 0 == points.length || 0 == points[0].length) {
            return 0;
        }
        List<Node> nodes = new ArrayList<>();
        //扫描线问题的核心：将1条线段拆成start，end 2个点，当遇到end点时针对“之前的start点”执行操作
        for (int i = 0; i < points.length; i++) {
            Node start = new Node(i, points[i][0], true);
            Node end = new Node(i, points[i][1], false);
            nodes.add(start);
            nodes.add(end);
        }
        // 按照X轴坐标升序排列
        Collections.sort(nodes, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                if (o1.axisIndex == o2.axisIndex) {
                    // 当横坐标相等时，保证start_i在end_j之后
                    // 如果不这么做的话，则遍历到“横坐标为3的end点”时，后面还会有“横坐标为3的start点”，
                    // 但这个start点所属的线段应该提前进入notShotedLineIdList
                    return o1.start ? -1 : 1;
                }
                return o1.axisIndex - o2.axisIndex;
            }
        });
        int shotNum = 0;
        List<Integer> notShotedLineIdList = new ArrayList<>();
        Set<Integer> shotedLineIdSet = new HashSet<>();
        for (Node oneNode : nodes) {
            if (oneNode.start) {
                // 当遇到start点时，记录该点所属线段为“未射中”
                notShotedLineIdList.add(oneNode.lineId);
            } else {
                // 当遇到end点时，检测该点所属线段，之前是否“已被射中”
                if (shotedLineIdSet.contains(oneNode.lineId)) {
                    // 如果已被射中，则不增加射击次数
                    continue;
                }
                // 如果还没被射中，则射击1次，由于notShotedLineIdList中的每条线段（已遇到了start点），都没到达它对应的end点
                // 因此notShotedLineIdList中的每条线段，在本次射击中爆炸了，记录这些线段全部都“已被射中”
                shotNum++;
                shotedLineIdSet.addAll(notShotedLineIdList);
                // 由于横坐标相等的点，start必然在end之前，所以在分析横坐标为X的end点时，所有横坐标的X的start点都进入了notShotedLineIdList
                // 不需要再额外分析 node[i+1,i+2...n-1]中所有横坐标为X的start点啦
                notShotedLineIdList.clear();
            }
        }
        //所有线段遍历完毕时，notShotedLineIdList必然为空，不需要再增加shotNum了
        return shotNum;
    }

    class Node {
        int lineId;
        int axisIndex;
        boolean start;

        public Node(int lineId, int axisIndex, boolean start) {
            this.lineId = lineId;
            this.axisIndex = axisIndex;
            this.start = start;
        }
    }
}