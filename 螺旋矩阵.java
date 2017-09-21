螺旋矩阵遵循：左->右; 上->下; 右->左; 下->上 4 steps，使用 up, down, left, right 分别记录还需遍历的矩形边界
while (左边界 <= 右边界 && 上边界 <= 下边界)
1. 左->右：执行条件：(left <= right)；执行过程：记录 matrix[up][left...max]；执行后：上边界下移, up++
2. 上->下：执行条件：(up <= down)；记录 matrix[right][up...down]；执行后：右边界左移, right--

3. 右->左：执行条件：(执行了"step 2" && left <= right)，如果没执行 step 2 则意味着"step 1"应该为这一轮的最后一步，
		   毕竟 up > down，如果再次执行 "右->左" 则意味着 重复遍历 step 1 的"冗余路径", 具体条件为 (up <= down && left <= right)
		   执行过程：记录 matrix[down][right...left]；执行后：下边界上移, down--

4. 下->上：执行条件：(执行了"step 3" && up <= down)，避免 重复遍历 step 2 的"冗余路径", 具体条件为 (left <= right && up <= down)
			执行过程：记录 matrix[left][down...up]；执行后：左边界右移, left++
			
public class Solution {
    /*
     * @param matrix: a matrix of m x n elements
     * @return: an integer list
     */
    public List<Integer> spiralOrder(int[][] matrix) {
        // write your code here
        List<Integer> record = new LinkedList<>();
       
        if (matrix.length == 0 || matrix[0].length == 0) {
        	return record;
        }
        int rowNum = matrix.length - 1;
        int colNum = matrix[0].length - 1;
        int up = 0;
        int down = rowNum;
        int left = 0;
        int right = colNum;
        while (up <= down && left <= right) { //左->右; 上->下; 右->左; 下->上
            // System.out.println(left + " " + right + " " + up + " " + down);
        	if (left <= right) {
        		for (int i = left; i <= right; i++) {
        			record.add(matrix[up][i]);
	        	}
        	    up++;
        	}
        	
            // System.out.println(left + " " + right + " " + up + " " + down);
        	if (up <= down) {
        		for (int i = up; i <= down; i++) {
        			record.add(matrix[i][right]);
        		}
	    		right--;
        	}

            // System.out.println(left + " " + right + " " + up + " " + down);
        	if (up <= down && left <= right) { //避免左->右后，但不用再执行上->下时，执行1轮冗余的右->左, e.g.[[1, 2, 3]
        		for (int i = right; i >= left; i--) {
        			record.add(matrix[down][i]);
        		}
	    		down--;

        	}

            // System.out.println(left + " " + right + " " + up + " " + down);
        	if (left <= right && up <= down) {
        		for (int i = down; i >= up; i--) { //避免上->下后，但不用再执行右->左时，执行1轮冗余的下->上。e.g. [[1],[2]]
        			record.add(matrix[i][left]);
        		}
	    		left++;
        	}
        }
        return record;
    }
}