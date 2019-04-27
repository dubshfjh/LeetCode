import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Leetcode766 {
    public boolean isToeplitzMatrix(int[][] matrix) {
        if (null == matrix || 0 == matrix.length) {
            return true;
        }
        // 正对角线：rowId + colId 相等，反对角线：rowId - colId 相等，
        // 不要想着遍历上半矩形：i = 0...row-1，j=0...正对角线colId
        // 直接m*n遍历每个元素，用map将(i - j)作为key即可
        Map<Integer, Integer> diagnoseValues = new HashMap<>();
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                int rowColDiff = i - j;
                if (diagnoseValues.containsKey(rowColDiff)) {
                    if (diagnoseValues.get(rowColDiff) != matrix[i][j]) {
                        return false;
                    }
                } else {
                    diagnoseValues.put(rowColDiff, matrix[i][j]);
                }
            }
        }
        return true;
    }
}