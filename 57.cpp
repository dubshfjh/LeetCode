#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

//算法思想：找到newInterval应该在intervals中存放的位置，然后插入，最后如同56题一样分析整个intervals即可
//缺陷：思维僵化，Insert的时间代价过高
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int i=0;
        vector<Interval> res;
        while(i<intervals.size()){//i是第一个start>newInterval.start  或者  start==newInterval.start 而且 end>=newInterval.end的元素下标，也是新元素应该插入的位置
        	if(intervals[i].start < newInterval.start){
        		i++;
        	}
        	else{
        		if(intervals[i].start == newInterval.start){
        			if(intervals[i].end < newInterval.end){
        				i++;
        			}
        			else{
        				break;
        			}
        		}
        		else{
        			break;
        		}
        	}
        }
        intervals.insert(intervals.begin()+i,newInterval);//Attention!!!! insert(iterator location,CONST TYPE& val)

        res.push_back(intervals[0]);
        for(i=1;i<intervals.size();i++){
        	if(intervals[i].end <= res[res.size()-1].end){
        		continue;
        	}
        	else if(intervals[i].start <= res[res.size()-1].end){
        		res[res.size()-1].end=intervals[i].end;
        	}
        	else{
        		res.push_back(intervals[i]);
        	}
        }

        return res;
    }
};


由于insert和erase代价太大，需要移动后面所有元素。

所有空间换时间，返回新的数组ret，而不采用inplace做法。

主要以下三种情况：

1、newInterval与当前interval没有交集，则按照先后次序加入newInterval和当前interval，然后装入所有后续interval。返回ret。

2、newInterval与当前interval有交集，合并成为新的newInterval，然后处理后续interval。

3、处理完最后一个interval若仍未返回ret，说明newInterval为最后一个interval，装入ret。返回ret。
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> ret;
        if(intervals.empty())
        {
            ret.push_back(newInterval);
            return ret;
        }
            
        int i = 0;
        while(i < intervals.size())
        {
            //no overlapping
            if(newInterval.end < intervals[i].start)
            {
                ret.push_back(newInterval);
                while(i < intervals.size())
                {
                    ret.push_back(intervals[i]);
                    i ++;
                }
                return ret;
            }
            else if(newInterval.start > intervals[i].end)
                ret.push_back(intervals[i]);


            //overlapping
            else
            {
                newInterval.start = min(newInterval.start, intervals[i].start);
                newInterval.end = max(newInterval.end, intervals[i].end);
            }
            i++;
        }
        ret.push_back(newInterval);      
        return ret;
    }
};