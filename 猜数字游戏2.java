Guess Number Game V1：给定了1个guess api，它能返回-1, 1, 0 三个值代表猜大了/猜小了/right。要做的事情：猜出被选择的数字即可，二分法而已...
/* The guess API is defined in the parent class GuessGame.
   @param num, your guess
   @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
      int guess(int num); */

public class Solution extends GuessGame {
    /**
     * @param n an integer
     * @return the number you guess
     */
    public int guessNumber(int n) {
        // Write your code here
        int start = 1;
        int end = n;
        while (start + 1 < end) { //求解最靠右的数字（即最后1个<=target的数字）所在位置
        	// 	当target = INT_MAX时,会导致mid变成负数而超时: int mid = (start + end) >> 1;
            int mid = start + ((end - start) >> 1);
        	int check = guess(mid); //当target is lower时，返回 -1
        	if (check == 1 || check == 0) { //当mid<=target时，start右移
        		start = mid;
        	} else {
        		end = mid;
        	}
        }

        if (guess(end) == 0) {
        	return end;
        } else {
        	return start;
        }

        // //求解最靠左的 target(即第1个 >=target的数字)
        // while (start + 1 < end) {
        // 	int mid  = start + ((end - start) >> 1);
        // 	int check = guess(mid);
        // 	if (check == -1 || check == 0) { //当mid >= target时，end左移
        // 		end = mid;
        // 	} else {
        // 		start = mid;
        // 	}
        // }
        // if (guess(end) == 0) {
        // 	return end;
        // } else {
        // 	return start;
        // }
    }
}


失去了guess API，求出"确保猜对数字时的"最小total cost（每猜错1次，设猜的值为 number，就付出number价值)
public class Solution {
    /**
     * @param n an integer
     * @return how much money you need to have to guarantee a win
     */
    public int getMoneyAmount(int n) {
        // Write your code here
        if (n == 0) {
        	return 0;
        }


    }
}