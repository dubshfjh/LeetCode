class Solution {
public:
    //是nums待调整的堆数组，element是待调整的数组元素的位置，size是数组的长度
    //本函数功能是：在堆中插入新元素[element]时，维护nums"尾部"的大根堆
    void MaxHeapify(vector<int>& nums,int size,int element){//
        int lchild,rchild;
        lchild = element*2+1;//当下标从1开始时，左子下标为2*i+1；当下标从1开始时，左子下标为2*i
        rchild = lchild+1;
        // cout<<element<<"..."<<lchild<<"..."<<rchild<<"..."<<endl;
        while(rchild < size){
            if(nums[element]>=nums[lchild] && nums[element]>=nums[rchild]){
                return;
            }
            if(nums[lchild] > nums[rchild]){
                swap(nums[element], nums[lchild]);
                element = lchild;
            }
            else{
                swap(nums[element], nums[rchild]);
                element = rchild;
            }
            lchild = 2*element+1;
            rchild = lchild+1;
        }
        if(lchild < size && nums[lchild]>nums[element] ){//如果完全二叉树的倒数第二层只有左子树，且左子树大于父节点 */
            swap(nums[lchild],nums[element]);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        int size = nums.size();
        if(size == 0 || size<k){
            return INT_MIN;
        }
        for(int i=size-1;i>=0;i--){
            // cout<<"first size: "<<size<<endl;
            MaxHeapify(nums,size,i);
        }
        
        while(k-->0){//执行k次步骤2
            // cout<<"second size: "<<size-1<<endl;
            swap(nums[0], nums[size-1]);
            MaxHeapify(nums,--size,0);
        }
        return nums[size];
    }
};


参考资料：两端代码分别为小顶堆排序 和 大顶堆排序。以大顶堆为例
步骤1：首先定义Heap调整函数：在堆中插入新元素[element]时，维护存储于数组nums"尾部"的大顶堆。while(右子<size){swap([element],较大子节点)；element更新位置到子节点上} 
    循环结束后，if(左子存在 && 左子>[element])，还需swap(左子，[element])
步骤2：由于始终维护的是nums尾部的大顶堆，于是i从size-1遍历到0，从最后一个元素开始将所有元素插入heap中，从而建立大顶heap
步骤2：由于Heap的顶端都为当前max元素，所以将当前max元素[0] 与 当前尾元素[size-1] 交换位置(原堆顶max元素就已经到达正确位置)，size--后将新的[0]插入到大顶Heap中的正确位置
/*
 * 堆排序
 * 整理节点time:O(lgn)
 */
template<typenameT>
void MinHeapify( T*arry, int size, int element )
{
    int lchild = element * 2 + 1, rchild = lchild + 1; /* 左右子树 */
    while ( rchild < size )                                                         /* 子树均在范围内 */
    {
        if ( arry[element] <= arry[lchild] && arry[element] <= arry[rchild] )   /* 如果比左右子树都小，完成整理 */
        {
            return;
        }
        if ( arry[lchild] <= arry[rchild] )                                     /* 如果左边最小 */
        {
            swap( arry[element], arry[lchild] );                            /* 把左面的提到上面 */
            element = lchild;                                               /* 循环时整理子树 */
        }else  { /* 否则右面最小 */
            swap( arry[element], arry[rchild] );                            /*同理 */
            element = rchild;
        }
        lchild  = element * 2 + 1;
        rchild  = lchild + 1;                                                   /* 重新计算子树位置 */
    }
    if ( lchild < size && arry[lchild] < arry[element] )                            /* 只有左子树且子树小于自己 */
    {
        swap( arry[lchild], arry[element] );
    }
    return;
}


/* 堆排序time:O(nlgn) */
template<typenameT>
void HeapSort( T*arry, int size )
{
    int i;
    for ( i = size - 1; i >= 0; i-- )               /* 从子树开始整理树 */
    {
        MinHeapify( arry, size, i );
    }
    while ( size > 0 )                              /* 拆除树 */
    {
        swap( arry[size - 1], arry[0] );        /* 将根（最小）与数组最末交换 */
        size--;                                 /* 树大小减小 */
        MinHeapify( arry, size, 0 );            /* 整理树 */
    }
    return;
}



#include <stdio.h>
//array是待调整的堆数组，i是待调整的数组元素的位置，nlength是数组的长度
//本函数功能是：根据数组array构建大根堆
void HeapAdjust(int array[],int i,int nLength)
{
    int nChild;
    int nTemp;
    for(;2*i+1<nLength;i=nChild)
    {
        //子结点的位置=2*（父结点位置）+1
        nChild=2*i+1;
        //得到子结点中较大的结点
        if(nChild<nLength-1&&array[nChild+1]>array[nChild])
            ++nChild;
        //如果较大的子结点大于父结点那么把较大的子结点往上移动，替换它的父结点
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp; 
        }
        else break; //否则退出循环
    }
}
//堆排序算法
void HeapSort(int array[],int length)
{
    int i;
    //调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
    //length/2-1是最后一个非叶节点，此处"/"为整除
    for(i=length/2-1;i>=0;--i)
        HeapAdjust(array,i,length);
    //从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for(i=length-1;i>0;--i)
    {
        //把第一个元素和当前的最后一个元素交换，
        //保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
        array[i]=array[0]^array[i];
        array[0]=array[0]^array[i];
        array[i]=array[0]^array[i];
        //不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        HeapAdjust(array,0,i);
    }
}
int main()
{
    int i;
    int num[]={9,8,7,6,5,4,3,2,1,0};
    HeapSort(num,sizeof(num)/sizeof(int));
    for(i=0;i<sizeof(num)/sizeof(int);i++)
    {
        printf("%d ",num[i]);
    }
    printf("\nok\n");
    return 0;
}


