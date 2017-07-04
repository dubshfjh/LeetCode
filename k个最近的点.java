/**
 * Definition for a point.
 * class Point {
 *     int x;
 *     int y;
 *     Point() { x = 0; y = 0; }
 *     Point(int a, int b) { x = a; y = b; }
 * }
 */
points：[[-435,-347],[-435,-347],[609,613],[-348,-267],[-174,-107],[87,133],[-87,-27],[-609,-507],[435,453],[-870,-747],[-783,-667],[0,53],[-174,-107],[783,773],[-261,-187],
[-609,-507],[-261,-187],[-87,-27],[87,133],[783,773],[-783,-667],[-609,-507],[-435,-347],[783,773],[-870,-747],[87,133],[87,133],[870,853],[696,693],[0,53],[174,213],
[-783,-667],[-609,-507],[261,293],[435,453],[261,293],[435,453]], 

origin:[-11,199], 13
本题为Simulator类型的题目，即模拟题目中定义的规则

算法思想：自定义类Node包含{Point + distance}，采用一个"升序排列的"TreeMap<Node>，使用自定义的Comparator<Key的泛型类 Node>，override int compare()
组合排序规则：1) 当距离不相等时：return NodeLeft.dis - NodeRight.dis  2) 距离相等时：如果 NodeLeft.x != NodeRight.x，则 return 左侧x - 右侧x  3)x相等时：return 左侧y - 右侧y
将所有的Node存放到TreeMap中，记录每个Node出现的次数。将所有的Point都按照规则存放到TreeMap后(顺序遍历依次取出 "升序序列")，使用迭代器取出k次Point作为结果(每个Node 都可以取出 Map.get(Node) 次)

遇到的坑：1. 由于坐标和距离都为double，但是要求的返回值为 int compare()，所以要定义一个 doubleToCompareInt 函数，将浮点数转化为所需要的 1,0,-1。
2. double类型比较必须注意：0.0 = +0.0 != -0.0；2个浮点数a和b的比较必须使用 abs(a-b) < 0.00000；但是浮点数与整数的比较 0.0 == 0；1.0 == 1
3. 第一版的代码没考虑points数组中存在相同点的问题，以致当存在 n 个相同点时，res里面只记录了其中1个
4. 在取出k次Point时，不能使用 while(k-- > 0 && cnt-- > 0)，而应该使用 while(k > 0 && cnt > 0) {k--; cnt--}
class Point {
    int x;
    int y;
    Point() { x = 0; y = 0; }
    Point(int a, int b) { x = a; y = b; }
}

public class Solution {
    /**
     * @param points a list of points
     * @param origin a point
     * @param k an integer
     * @return the k closest points
     */
    class Node {
        Point p;
        double distance;
        private Node(Point p, double distance) {
            this.p = p;
            this.distance = distance;
        }
// 因为使用了自定义的Comparator<Key的泛型>，所以需要再override equals & hashCode来重定义自然顺序了
//        public boolean equals(Node another) {
//            return p.equals(another.p);
//            //return p == (Node)another.p;
//        }
//
//        public int hashCode() {
//            return p.hashCode();
//        }
    }
    public Point[] kClosest(Point[] points, Point origin, int k) {
        // Write your code here
        //构建TreeMap的距离升序排列
        if (points == null || points.length <= k) {
            return points;
        }
        Map<Node, Integer> countNum = new HashMap<>();
        TreeMap<Node, Integer> neighbors = new TreeMap<>(new Comparator<Node>() {
            public int compare(Node curLeft, Node curRight) {
                if (curLeft.distance != curRight.distance) {
                    return calCompInt(curLeft.distance - curRight.distance);
                } else {
                    Point left = curLeft.p;
                    Point right = curRight.p;
                    if (left.x != right.x) {
                        return calCompInt(left.x - right.x);
                    } else {
                        return calCompInt(left.y - right.y);
                    }
                }
            }
        }
        );
        for (Point curPoint : points) {
            double distance = calDistance(curPoint, origin);
            Node curNode = new Node(curPoint, distance);
            if (neighbors.containsKey(curNode)) {
                neighbors.put(curNode, neighbors.get(curNode) + 1);
            } else {
                neighbors.put(curNode, 1);
            }

        }
        int index = 0;
        Point[] res = new Point[k];
        for (Node tmpNode : neighbors.keySet()) {
            if (k == 0) {
                break;
            }
            int tmpNodecnt = neighbors.get(tmpNode);
//            while (k-- > 0 && tmpNodecnt-- > 0) { 如果按照这种写法，以 k=2,cnt=1为例，第一次执行完后k=1,cnt=0，然后再次进入while()判断部分，虽然不进入循环，但是 k和cnt都 再次--
            while (k > 0 && tmpNodecnt > 0) {
                k--;
                tmpNodecnt--;
                res[index++] = tmpNode.p;
                // System.out.println(k + " " + tmpNodecnt + " " +index);
            }
        }
        return res;
    }

    private double calDistance(Point nodex, Point nodey) {
        double temp = Math.pow((nodex.x - nodey.x), 2) + Math.pow((nodex.y - nodey.y), 2);
        return Math.sqrt(temp);
    }


    private int calCompInt(double x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }
    }

    public static void main(String[] args) {
        Point[] points = new Point[3];
        Point p1 = new Point(1, 1);
        Point p2 = new Point(1, 1);
        Point p3 = new Point(1,0);
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        Point origin  = new Point(2, 2);
        Solution obj = new Solution();
        Point[] res = obj.kClosest(points, origin, 2);
        System.out.println();
    }
}