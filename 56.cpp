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

算法错误，思路过于繁琐，尚未解决[[1,4],[0,0]]这种 num_index[0]={0,0} 的用例分析

思想：对于每个interval的start和end进行综合排序，并使用map<int,vector<int>>保存每个start和end对应的Interval下标
然后参考括号消除的思想，将当前数字num[i]的所以下标存入temp，然后分析[i+1]...[i+n]中每个数字对应的下标。如果遇到了已经出现的index，则从vector中移除它；否则push_back()进去
示例：数字对应的Interval下标数组：(0)(1)(2)(2)(0)(1)  begin=nums[0]; vector:{0}-->{0,1}-->{0,1,2}-->{0,1}-->{1}-->{empty}; end=nums[size-1]，即右移到此刻的i 于是大范围是{begin,end}
但是：(0,0) (1)(1)这种情况下，就完全错误了，之前的{0,0}找不到对端用于消除他们的index，所以i右移到越界，暂无正确思路
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
    	int i,j,begin,end,size,tempindex;
        vector<Interval> res;
        vector<int> temp,nums;
        vector<int>::iterator it;
        map<int,vector<int>> num_index;
        if(intervals.size()==0){
        	return res;
        }
        for(i=0;i<intervals.size();i++){
        	if(num_index.count(intervals[i].start)==0){
            	nums.push_back(intervals[i].start);
        		temp.clear();
        		temp.push_back(i);
        		num_index.insert(pair<int,vector<int>>(intervals[i].start,temp));
        	}
        	else{
        		num_index[intervals[i].start].push_back(i);
        	}
        
    	    if(num_index.count(intervals[i].end)==0){
     		    nums.push_back(intervals[i].end);
        		temp.clear();
        		temp.push_back(i);
        		num_index.insert(pair<int,vector<int>>(intervals[i].end,temp));
        	}
        	else{
        	    //if(intervals[i].end != intervals.start){//对于[1,1]这种情况，只保存num_index[1]={0}，而不是num_index[1]={0,0}
        	    num_index[intervals[i].end].push_back(i);
        	    //}
        	}
        	
        	//cout<<"start:"<<num_index[intervals[i].start][0]<<endl;
        	//cout<<"end:"<<num_index[intervals[i].end][0]<<endl;

        }
        sort(nums.begin(),nums.end());

        for(i=0;i<nums.size();i++){
        	temp.clear();
        	temp.assign(num_index[nums[i]].begin(),num_index[nums[i]].end());
        	begin=nums[i];
        	while(!temp.empty() && i<nums.size()){
        		i++;
        		for(j=0;j<num_index[nums[i]].size();j++){
        			tempindex=num_index[nums[i]][j];
        			it=find(temp.begin(),temp.end(),tempindex);
        			if(it != temp.end()){
        				temp.erase(it);
        			}
        			else{
        				temp.push_back(tempindex);
        			}
        		}
        		end=nums[i];
        	}
        	if(!temp.empty()){
        	    
        	}
        	Interval obj = Interval(begin,end);
        	res.push_back(obj);
        }
        return res;
    }
};


先对start排序。

然后对每两个interval（记为a,b），判断是否需要合并。

如果不需要合并（没有交集），则把a装入ret，将b继续往后。
如果需要合并（有交集），则把结果c继续往后。

这题本身是不难的，但是有两个细节：

1、compare函数中，如果是升序，必须是<而不是<=

解释：参考http://www.cplusplus.com/reference/list/list/sort/，比较必须产生strick weak ordering。

对于strick weak ordering 可以参考http://stackoverflow.com/questions/979759/operator-and-strict-weak-ordering/981299#981299的详细说明。

总之，如果a,b不等，那么compare(a,b)和compare(b,a)其中之一为true，另一为false。如果a,b相等，则都应该为false。

2、compare函数必须声明为静态成员函数或者全局函数，不能作为普通成员函数

解释：非静态成员函数是依赖于具体对象的，而std::sort这类函数是全局的，因此无法在sort中调用非静态成员函数。
可以把compare改成静态或者全局函数，使之不依赖于具体对象。


/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
	static bool compare(Interval v1,Interval v2){//升序排列的自定义compare
		if(v1.start < v2.start){
			return true;
		}
		else if(v1.start > v2.start){
			return false;
		}
		else{
			return v1.end < v2.end;
		}
	}
    vector<Interval> merge(vector<Interval>& intervals) {
    	int i;
        vector<Interval> res;
        if(intervals.empty()){
        	return res;
        }

        sort(intervals.begin(),intervals.end(),compare);
        res.push_back(intervals[0]);

        for(i=1;i<intervals.size();i++){//一个个地依次组合interval[i](即当前的对象：cur)

        	//经过排序后cur.start>=last.start，
        	if(intervals[i].end <= res[res.size()-1].end){//此时若cur.end <= last.end
        		continue;//此时cur和last组合之后，仍然为last，下一轮直接使用last比较即可
        	}
        	//由于是else if,则此时cur.end > last.end && cur.start<=last.end
        	else if(intervals[i].start <= res[res.size()-1].end){
        		res[res.size()-1].end = intervals[i].end;
        	}
        	//由于是else，则cur.start > last.end
        	else{//此时cur(即intervals[i])与上一个res[res.size()-1]不再有交集，需作为新元素添加进入res
        		res.push_back(intervals[i]);
        	}
        }

        return res;
    }
};