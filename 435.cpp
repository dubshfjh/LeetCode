/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
/*
class Solution {
public:
    static bool compare(Interval left, Interval right){
        if(left.start < right.start){
            return true;
        }
        else if(left.start > right.start){
            return false;
        }
        else{
            return left.end < right.end;
        }
    }

    int eraseOverlapIntervals(vector<Interval>& intervals) {
        int size = intervals.size();
        if(size <= 1){
            return 0;
        }
        vector<Interval>::iterator it_i;
        sort(intervals.begin(),intervals.end(),compare);
        it_i = intervals.begin();
        while(it_i != intervals.end()){
            vector<Interval>::iterator it_j = it_i+1;
            while((*it_j).start == (*it_i).start && it_j != intervals.end()){
                intervals.erase(it_j);
            }
            if(it_j == intervals.end()){
                break;
            }
            while((*it_j).start < (*it_i).end && it_j != intervals.end()){
                intervals.erase(it_j);
            }
            it_i = it_j;
        }
        int res = size - intervals.size();
        return res;
    }
};
*/
算法思想：首先按照end升序对intervals进行排序，然后用迭代器it_i从头开始遍历intervals，分析it_j={it_i+1,...}，如果it_j与it_i区间有重叠，即(*it_j).start < (*it_i).end，则从vector中移除it_j(并且需移除元素num+1)，直至it_j == intervals.end()
或者(*it_j).start >= (*it_i).end后，将it_i 右移到 it_j的位置
缺陷：vector的remove太过耗时，导致算法运行时间极长
改进后的算法：对于与it_i 重叠的 it_j，不需要remove掉，因为与it_j比较区间是否重叠的it_i位置不变，所以直接it_j++即可。PS:运行时间极大减少了
class Solution {
public:
    static bool compare(Interval left, Interval right){
        if(left.end <= right.end){
            return true;
        }
        else{
            return false;
        }
    }
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        int size = intervals.size();
        if(size <= 1){
            return 0;
        }
        int res = 0;
        sort(intervals.begin(),intervals.end(),compare);
        vector<Interval>::iterator it_i;
        it_i=intervals.begin();
        while(it_i!=intervals.end()){
            vector<Interval>::iterator it_j = it_i+1;
            while((*it_j).start < (*it_i).end && it_j!=intervals.end()){
                res++;
                it_j++;
                //intervals.erase(it_j);
            }
            it_i = it_j;
        }
        return res;
    }
};