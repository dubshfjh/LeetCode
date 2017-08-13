本题：在旋转数组中搜索目标值，本质上旋转数组格式为 left,...max,min,...right || max,...,min || min...max，但是纯升序序列的情况被包含在了 left,max,min,right 里面
踩到的坑：
1. 在移动边界时，最好先处理 (条件1&&条件2) 时才进行的边界移动。e.g. (target >= A[left] && target < A[mid]) 时， 移动右边界
2. "二分搜索" 最好使用 while(start + 1 < end) {start,end = mid} 的组合，同时在退出循环后判断 [start] 和 [start + 1] 是否有1个满足条件

"这种用 通过判断 || 条件就移动左右边界的做法有逻辑错误！！！！！！！！！！！！！！！！！！！！！！！！！"
"同时，将 start, end 移动到 mid +- 1 的方法也可能造成Solution 疏漏，应该将循环退出条件设置为 start+1 < end，同时将start,end 移动到 mid"
// if (A[mid] >= A[left]) { //{left...mid...max, min,...right}
        	// 	if (target > A[mid] || target <= A[right]) {
        	// 		left = mid + 1;
        	// 	} else {
        	// 		right = mid - 1;
        	// 	}
        	// } else if (A[mid] <= A[right]) { // {left...max,min,...mid...right}
        	// 	if (target < A[mid] || target >= A[left]) {
        	// 		right = mid - 1;
        	// 	} else {
        	// 		left = mid + 1;
        	// 	}
        	// } else { //此时已经抵达了唯一的一段递减序列： left,...max,min,...right 中的{min,max}；或者 max,...,min 字段
        	// 	if (A[mid] > target) { //由于此时 max...mid...min
        	// 		left = mid + 1;
        	// 	} else {
        	// 		right = mid - 1;
        	// 	}
        	// }
public class Solution {
    /** 
     *@param A : an integer rotated sorted array
     *@param target :  an integer to be searched
     *return : an integer
     */
    public int search(int[] A, int target) {
        // write your code here
        int length = A.length;
        if (length == 0) {
        	return -1;
        }
        int left = 0;
        int right = length - 1;
        
        while (left + 1 < right) {
            // System.out.println(left + "..." + right);
        	int mid = left + ((right - left) >> 1);
        	if (A[mid] == target) {
        		return mid;
        	}
        	if (A[mid] > A[left]) { //{left...mid...max,min,...right}
        		if (target >= A[left] && target < A[mid]) {
        			right = mid;
        		} else {
        			left = mid;
        		}
        	} else { //这段逻辑其实不完善，无法解决 {max...min}的问题
        	    if (target > A[mid] && target <= A[right]) {
        			left = mid;
        		} else {
        			right = mid;
        		}
        	}
        	/* 下面这段代码的逻辑才能处理 {max...min} 的旋转数组情况，然而lintcode判断认为超时了
        	else if (A[mid] < A[right]){ // {left...max,min,...mid...right}
        		if (target > A[mid] && target <= A[right]) {
        			left = mid;
        		} else {
        			right = mid;
        		}
        	} 
        	else { //{max...mid...min}
        	    if (target < A[mid]) {
        	        left = mid;
        	    } else {
        	        right = mid;
        	    }
        	}
        	*/
        	
        }
        // System.out.println("final: " + left + "..." + right);
        if (A[left] == target) {
        	return left;
        }
        if (A[right] == target) {
        	return right;
        }
        return -1;
    }
}
