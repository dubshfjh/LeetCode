#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

使用left,right两个指针维护装水两侧的位置。

当left处高度较低时，说明left右侧的水平面高度必然和left一致，此时逐步右移left。水的格数应该加上 [left]-[比left还低的元素]
因为这些位置都能装水，知道再遇到同样高 or 更高的位置，然后进行下一轮判断

同理，当right处高度较低时，说明right左侧的水平面高度必然和right一致，此时逐步左移right，水的格数应该同时加上[right]-[比right还低的元素]
知道遇到同样高 or 更高的位置

当left == right相遇时，结束

class Solution{
public:
	int trap(vector<int>& height){
		int left,right,res,minheight;
		left=res=0;
		right=height.size()-1;
		while(left<right){
			minheight = min(height[left],height[right]);
			if(height[left] == minheight){
				left++;
				while(left<right && height[left]<minheight){
					res += minheight-height[left];
					left++;
				}
			}

			if(height[right] == minheight){
				right--;
				while(left<right && height[right]<minheight){
					res += minheight-height[right];
					right--;
				}
			}
		}

		return res;
	}
};




从第一个非零数开始标记为lastMarkedheight，这个lastMarkedheight作为一个可以盛水的高度基准，为了确定它是安全的，
需要遍历它之后的数，要是有更高的数字则是安全的，否则把lastMarkedheight的值降低为可搜索到的最高高度。
在确认安全之后继续遍历数组。遇到矮的则把高度差作为储水量加起来，到比lastMarkedheight高的就重新判断那个值是否安全并更新lastMarkedheight。

本段代码并不是在计算得到了lastMarkedheight时，就直接计算到达后一个>=lastMarkedheight元素为止的总水量
而是对每个元素进行判断，若[i]>=lastMarkedheight，则计算新的lastMarkedheight；若[i]<lastMarkedheight，则累加计算本列的水量
class Solution {
public:
    int trap(vector<int>& height) {
        vector<int>::iterator it;
        int sumWater=0;
        int lastMarkedHight=0;
        for(it = height.begin();it!=height.end();it++){
            if(lastMarkedHight==0 && *it == 0)//前面的0无视掉
            	continue;
            if(lastMarkedHight==0 && *it != 0){//第一个非零作为lastMarkedHight
            	lastMarkedHight = *it;
            }
            if(lastMarkedHight!=0 && *it>=lastMarkedHight){//判断是否安全
                int a = 0;
                bool findLarger = false;
                for(vector<int>::iterator tempIt=it+1;tempIt!=height.end();tempIt++){//找是否有更高的
                    if(*tempIt>*it){
                        findLarger = true;
                        break;
                    }
                }
                if(findLarger){//安全
                    lastMarkedHight = *it;
                    continue;
                }
                else{//找it后最高的一个数作为lastMarkedHight
                    while(find(it+1,height.end(),*it-a)==height.end() && *it-a>0){
                        a++;
                    }
                	lastMarkedHight = *it-a;
                }
            	continue;
            }
            if(lastMarkedHight!=0 && *it<lastMarkedHight && it!=height.end()-1){
                sumWater = sumWater+(lastMarkedHight-*it);//遇到矮的加储水量
                cout<<sumWater<<endl;
                continue;
            }
        }
        return sumWater;
    }
};
int main(){
	int res;
    int a[]={0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> num(a,a+12);
    Solution sol=Solution();
    res=sol.trap(num);
    cout<<res<<endl;
    return 0;
}



