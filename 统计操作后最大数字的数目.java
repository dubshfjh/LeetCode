Given an m * n matrix M initialized with all 0s and several update operations.

Operations are represented by a 2D array, and each operation is represented by an array with two positive integers a and b, which means M[i][j] 
        should be added by one for all 0 <= i < a and 0 <= j < b.

You need to count and return the number of maximum integers in the matrix after performing all the operations.

Example 1:
Input: 
m = 3, n = 3
operations = [[2,2],[3,3]]
Output: 4
Explanation: 
Initially, M = 
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]

After performing [2,2], M = 
[[1, 1, 0],
 [1, 1, 0],
 [0, 0, 0]]

After performing [3,3], M = 
[[2, 2, 1],
 [2, 2, 1],
 [1, 1, 1]]

So the maximum integer in M is 2, and there are four of it in M. So return 4.

每次对 row = 0...m & col = 0...n的所有元素都++，统计所有的MAX元素数目，算法思想：[i,j]相当于 X轴上的(0,0)->(i,0)线段 以及 y轴上的(0,0)->(0,j)线段组成的矩形，
    我们要求的就是所有矩形的最大重合面积，由于每个矩形的边都是在 x,y 轴上，只需要获取 min{i} * min{j} 即为重合面积

PS1：这个题不是并查集【求解元素是否在集合内，计算图的连通分量...】
    因为并查集算法中每个元素Union到同一个集合后，就不会再次Union了，但本题中对于每次的操作数[i,j]，都需要对之前可能Union过的{0..i-1}{0...j-1}重新统计一次
PS2：这个题也不是二维的扫描线问题，扫描线统计的本质上是统计多条线段的MAX重叠数，但是本题要的并不是重叠数,而是横纵坐标的最小取值即可[[2,2],[3,3],[4,4]]，最多有3条线段重合

public class Solution {
    public int maxCount(int m, int n, int[][] ops) {
        int minX = n, minY = m;
        for (int[] curOP : ops) {
            minY = Math.min(minY, curOP[0]);
            minX = Math.min(minX, curOP[1]);
        }
        return minX*minY;              
    }
}