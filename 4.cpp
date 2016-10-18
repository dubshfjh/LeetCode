 A班和B班的同学人数分别为aEnd与bEnd，有天体育老师说要找他们中间第k矮的同学，于是先将两班的同学按从小到大的顺序站成两队。
 假设k是为13。那此时A班派出第x矮的同学，B班派出第y矮的同学来比较（注意：此时x+y<=k）。
    若x为6，y为7。如果A的第6位同学比B的第7位同学还要矮，那如果两班整体排序，那A班的6位同学一定是要站在B班的第7位前面，
    最多A班第6位就站在B班第7位的前一位，最多就整体排第12，怎么都轮不到他排第k=13个。于是可以把A班前6位丢掉，在剩下的两个队列里面找。但是就不再是找第k个，而是找第k-x个了。因为x做了基数被丢掉了。
      当然，上述例子，只要（x+y)<=k的情况，x与y只要是为非负的，那都可以。
 	  只是为了效率，一般去x=y=(k/2)。而当某一队被丢到剩下人很少或者没人了，那这个取值就要根据具体情况来取值。
//解析：http://www.lxway.com/49629084.htm

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i,j,m,n,k;
        m=nums1.size();
        n=nums2.size();
        k=m+n;
        if(k%2==0){//find(...k)代表寻找nums1和nums2整体队列中第k大的元素
        	return (find(nums1,0,m,nums2,0,n,k/2)+find(nums1,0,m,nums2,0,n,k/2+1))/2;
        }
        else{// a%b 的正负仅仅取决于a的正负,-3%2=-1;-5%3=-2,因此判断一个数为奇数：必须使用a%2!=0而非a%2==1
        	return find(nums1,0,m,nums2,0,n,k/2+1);//k并非整体数组中的下标，而是意图寻找第k大的元素，所以不用考虑从0开始的情况
        }
    }
    //递归算法，不断缩小两个数组的范围，同时k的值也相对两个搜索区间上限起始点而改变
    double find(vector<int>& A,int astart,int aend,vector<int>& B,int bstart,int bend,int kth){
    //aend表示从A的start下标到达A数组末尾的长度(即A数组长度)，其中每次设置A为较短的数组，以便A数组更早删减至空,Kth表示寻找当前A,B整体队列第Kth大的元素
    	if(aend>bend){
    		return find(B,bstart,bend,A,astart,aend,kth);
    	}//统一将长度短的放置于find函数参数的前面项

    	if(aend<=0){// 长度短的为空，则答案等同于求另外一个数组的中位数
    		return B[bstart+kth-1];//并不是只有执行到这一句才会结束，如果短数组能被清空，则算法每次都会删减A[start]和B[start]中较小值所在数组的元素，最终从长数组中直接取值
    	}

    	if(kth==1){//A,B都删减到极致（而且A还不为空）,接下来只需得到A,B整体数组中的第1位元素即为中位数，两个数组的astart和bstart 较小者在前，为中位数
    		return min(A[astart],B[bstart]);
    	}

    	//pa+pb=kth，A为较短数组，所以当A中元素少于kth/2个时，自然不能选取A[astart+kth/2-1]进行比较，所以此时取pa=A[aend]
    	int pa=min(kth/2,aend);//此时从A中选取第x大的元素，从B中选取第y大的元素，x+y=kth
    	int pb=kth-pa;//为了简化直接取x=y=kth/2，若A[astart+pa-1]<B[bstart+pb-1],则删去A中从start到astart+pa-1的部分，因为
    	//A[astart+pa-1]最多也只能达到第kth-1个位置，第kth个位置可能为A[astart+pa]...或者B[0]...B[bstart+pb-1]...的任何一个元素
    	//此时kth的值应该更新为kth-pa(因为整体序列已经确定了在kth之前有着A[astart]...A[astart+pa-1]这pa个元素)
    	//
    	if(A[astart+pa-1]<B[bstart+pb-1]){//删减A中元素
    		return find(A,astart+pa,aend-pa,B,bstart,bend,kth-pa);//astart-=pa：删除A中前pa个元素；aend-=pa：A数组长度减少pa
    	}
    	else{
    		return find(A,astart,aend,B,bstart+pb,bend-pb,kth-pb);
    	}
    }

    double min(double a,double b){
    	return a<b?a:b;
    }

};