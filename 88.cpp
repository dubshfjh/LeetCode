Runtime Error常见原因：数组越界，除0，爆栈，访问空地址
Time Limit Exceeds则是因为时间复杂度太高

做这题时在Run Code时总是Runtime Error，最后检测了一下发现在插入了nums2中全部元素后，nums1.size()仍然为m，而不是m+n
大概是因为题目中说假设nums1有足够空间是在口high吧，自己给nums1进行resize即可

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i,j,index;
        i=j=0;
        nums1.resize(m+n,0);//将num1.size()扩充到m+n，并将后面的n个元素初始化为0
        while(j<n){
            // cout<<i<<",,,"<<j<<endl;
            if(i<m+j){
                if(nums1[i]<=nums2[j]){//当i已经遍历到初始nums1中的last元素(下标为m+j-1)并i++后，直接将j中剩余的元素插入nums1即可
                    i++;
                }
                else{
                    for(int k=m+j-1;k>=i;k--){//只有当j>=0时才有意义，插入nums2[0]时，[m-1]...[i]依次右移；插入nums2[1]时，[m],[m-1],...[i]依次右移
                        nums1[k+1]=nums1[k];
                    }
                    nums1[i++]=nums2[j++];
                    //i++;
                    //j++;
                }
            }
            else{
                while(j<n){
                    nums1[i++]=nums2[j++];
                }
                //因为while循环结束之后，i的值将为m+n，而非m+n-1，leetcode验证结果的时候可能尝试输出了nums1[i]
            }
        }
        // cout<<"final: "<<nums1.size()<<endl;
        // for(int k=0;k<m+n;k++){
        //     cout<<nums1[k]<<endl;
        // }
    }
};