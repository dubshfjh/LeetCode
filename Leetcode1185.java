public class Leetcode1185 {
    class Solution {
        private static final int FIRST_YEAR = 1971;
        private final int[] DAYNUM_OF_MONTH = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        private final String[] DAY_OF_WEEK = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        private final int FIRST_DAY_OF_WEEK_ID = 5;
        /**
         * 前置知识：闰年的2月为29天，全年为366天，1971年1月1日为Friday
         * @param day
         * @param month
         * @param year
         * @return
         */
        public String dayOfTheWeek(int day, int month, int year) {
            int dayNumFromFirstDay = 0;
            for (int i = FIRST_YEAR; i < year; i++) {
                if (isLeapYear(i)) {
                    dayNumFromFirstDay += 366;
                } else {
                    dayNumFromFirstDay += 365;
                }
            }
            DAYNUM_OF_MONTH[1] = isLeapYear(year) ? 29 : 28;
            for (int j = 0; j < month - 1; j++) {
                dayNumFromFirstDay += DAYNUM_OF_MONTH[j];
            }
            dayNumFromFirstDay += (day - 1);
            return DAY_OF_WEEK[(dayNumFromFirstDay + FIRST_DAY_OF_WEEK_ID) % 7];
        }

        /**
         * 1. 普通年能被4整除且不能被100整除的为闰年。（如2004年就是闰年，1900年不是闰年）
         * 2. 世纪年能被400整除的是闰年。（如2000年是闰年，1900年不是闰年）
         * 3. 数值很大的年份，这年如果能整除3200，并且能整除172800则是闰年。如172800年是闰年，86400年不是闰年（因为虽然能整除3200，但不能整除172800）
         * @param year
         * @return
         */
        private boolean isLeapYear(int year) {
            if (0 == year % 4 && 0 != year % 100) {
                return true;
            }
            if (0 == year % 100 && 0 == year % 400) {
                return true;
            }
            if (0 == year % 3200 && 0 == year % 172800) {
                return true;
            }
            return false;
        }
    }

    Solution solution = new Solution();

    public static void main(String[] args) {
        Leetcode1185 leetcode1185 = new Leetcode1185();
        System.out.println(leetcode1185.solution.dayOfTheWeek(15, 8, 1993));
    }
}
