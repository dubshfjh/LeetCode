思路错误了，
1. 不应该使用 {斜率，截距} 来区分直线，可以使用 {一个点，斜率} 来区分不同的直线
2. 如果斜率为double类型，所以不能使用 a==b 来判断双精度浮点数是否相等，
    但是Double这个包装器类型 override 了equals()方法，所以HashMap可以按照与==不同的方式比较两个Double变量
3. +0.0 != -0.0；+0.0 == 0.0；因此对于 -0.0 的情况，应该通过 0.0 + (-0.0) 将它转化为 0.0
// public class Solution {
//     /**
//      * @param points an array of point
//      * @return an integer
//      */
//     class Line extends Object{
//         double k;
//         double b;
//         private Line(double k, double b) {
//             this.k = k;
//             this.b = b;
//         }

//         @Override
//         public boolean equals(Object obj) {
//             Line line = (Line) obj;
//             return line.k == this.k && line.b == this.b;
//         }

//         @Override
//         public int hashCode() {
//             return (int) (k + b);
//         }
//     }

//     public int maxPoints(Point[] points) {
//         // Write your code here
// //        father = new int[points.length];
// //        size = new int[points.length];
// //        for (int i = 0; i < points.length; i++) {
// //            father[i] = i;
// //            size[i] = 1;
// //        }
//         Map<Line, Integer> visit = new HashMap<>(); //统计每条line的出现次数
//         Map<Integer, Integer> noKLine = new HashMap<>();
//         for (int i = 0; i < points.length - 1; i++) {
//             for (int j = i + 1;j < points.length; j++) {
//                 if (points[i].x !=  points[j].x) {
//                     double k = (points[i].y - points[j].y) / (points[i].x - points[j].x);
//                     double b = k * points[i].x - points[i].y;
//                     Line curLine = new Line(k, b);
//                     if (visit.containsKey(curLine)) {
//                         visit.put(curLine, visit.get(curLine) + 1);
//                     } else {
//                         visit.put(curLine, 1);
//                     }
//                 } else {
//                     if (noKLine.containsKey(points[i].x)) {
//                         noKLine.put(points[i].x, noKLine.get(points[i].x) + 1);
//                     } else {
//                         noKLine.put(points[i].x, 1);
//                     }
//                 }
//             }
//         }
//         int res = 0;
//         for (Integer num : visit.values()) {
//             res = Math.max(res, calPointNum(num));
//         }

//         for (Integer num : noKLine.values()) {
//             res = Math.max(res, calPointNum(num));
//         }
//         return res;
//     }

//     private int calPointNum(int linenum) {
//         int left, right, middle;
//         left = 0;
//         right = linenum;
//         while (left + 1 < right) {
//             middle = (left + right) >> 1;
//             int temp = (middle * middle - middle) >> 1;
//             if (temp == linenum) {
//                 return middle;
//             } else if (temp < linenum) {
//                 left = middle;
//             } else {
//                 right = middle;
//             }
//         }
//         return Integer.MIN_VALUE;
//     }
// }
/*
并查集的思路，但是不需要使用
private int[] father;
private int[] size;

private int find(int x) {
   int bigFather = x;
   if (father[x] != x) {
       bigFather = find(father[x]);
   }
   father[x] = bigFather;
   return bigFather;
}

private void union(int x, int y) {
   int bigFatherX = find(x);
   int bigFatherY = find(y);
   if (bigFatherX != bigFatherY) {
       if (size[x] < size[y]) {
           father[bigFatherX] = bigFatherY;
           size[bigFatherY] += size[bigFatherX];
       } else {
           father[bigFatherY] = bigFatherX;
           size[bigFatherX] += size[bigFatherY];
       }
   }
}
*/


/**
 * Definition for a point.
 * class Point {
 *     int x;
 *     int y;
 *     Point() { x = 0; y = 0; }
 *     Point(int a, int b) { x = a; y = b; }
 * }
 */

使用 {一个点，斜率} 来区分不同的直线，固定每个点i，统计该点出发的所有直线(斜率k相等 ==> 即意味着是同一条直线)
对于每个点i，使用新的 Map<斜率，次数>记录i与 {i+1...n} 这些点相连的直线出现次数。
1：必须通过 0.0 + 斜率 ，使得当斜率为 -0.0 时，也能通过 0.0 + (-0.0) 转化为 0.0
2. points数组中可能包含很多个相同的点,因此在分析每个点i时，需要统计这个点的出现次数count，避免统计 重复点j与点i之间的直线 
    最终分析从i出发的所有直线时，每条直线的points数目 = (相同直线数) + (与i相同的点数 - 1)
    PS：如果点 i 只出现了一次，则每条直线上的points数目 = （相同斜率直线数目）+ (1 - 1)，因此新直线的点数初始化为2
3. 可能出现所有points数组都是相同点时，为适应Step 2的模板公式，需要为 sameNode制定1个斜率为 Min_Value - 1
4. 为斜率无穷大的直线 设置 k为MAX_VALUE+1
5. int/int 会导致下取整，必须将分子和分母转换为 double 后才能保留小数位：(0.0 + points[j].y - points[i].y) / (0.0 + points[j].x - points[i].x)
/**
 * Definition for a point.
 * class Point {
 *     int x;
 *     int y;
 *     Point() { x = 0; y = 0; }
 *     Point(int a, int b) { x = a; y = b; }
 * }
 */
public class Solution {
    /**
     * @param points an array of point
     * @return an integer
     */
    public int maxPoints(Point[] points) {
        // Write your code here
        if (points == null || points.length == 0) {
            return 0;
        }
        int res = 1; //当points 包含1个以上的点时，res至少为1
        Map<Double, Integer> iLineCount = new HashMap<>();
        for (int i = 0; i < points.length; i++) {
            iLineCount.clear();
            int sameNodeCount = 0;
            //也许points中所有点都为sameNode，为sameNode制定1个斜率为 Min_Value - 1
            //这是为了适应统计每条从i出发的直线上point数 = (相同直线数) + (与i相同的点数 - 1)
            iLineCount.put(0.0 + Integer.MIN_VALUE - 1, 1);
            for (int j = i + 1; j < points.length; j++) {
                double k;
                if (points[i].x == points[j].x) {
                    if (points[i].y == points[j].y) {
                        sameNodeCount++;
                        continue; //如果j与i是同一个点，那就不能同时{sameNodeCount++，新增一条斜率不存在的直线}，因为2个相同点之间是不存在的直线的。如果不加continue，在遇到[点i，点i]这种case时会认为有3个点在同一条直线上
                    }
                    //为斜率无穷大的直线 设置 
                    k = 0.0 + Integer.MAX_VALUE + 1;
                } else {
                    k = 0.0 + (0.0 + points[j].y - points[i].y) / (0.0 + points[j].x - points[i].x);
                }
                // System.out.println(i+" "+k);

                if (iLineCount.containsKey(k)) {
                    iLineCount.put(k, iLineCount.get(k) + 1);
                } else {
                    iLineCount.put(k, 2);
                }
            }

            for (int lineCount : iLineCount.values()) {
                res = Math.max(res, lineCount + sameNodeCount);
            }
        }
        return res;
    }

    // public static void main(String[] args) {
    //     Scanner sc = new Scanner(System.in);
    //     double k = 0.0 + Integer.MIN_VALUE - 1;
    //     while (sc.hasNext()) {
    //         int n = sc.nextInt();
    //         Point[] points = new Point[n];
    //         for (int i = 0; i < n; i++) {
    //             int x = sc.nextInt();
    //             int y = sc.nextInt();
    //             points[i] = new Point(x, y);
    //         }
    //         Solution obj = new Solution();
    //         System.out.println(obj.maxPoints(points));
    //     }
    // }
}