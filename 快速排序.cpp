#include <iostream>

int quicksort(vector<int> a,int left,int right){
	if(left>right){
		return;
	}
	int low,high,key;
	key=a[left];
	low=left;
	high=right;
	while(low<high){
		while(a[high]>key&&low<high){
			high--;
		}
		a[low]=a[high];//因为key记录了a[low]，所以将小于key的值放在low的位置(初始为left，之后为上次空出来的地方)
		while(a[low]<key&&low<high){
			low++;
		}
		a[high]=a[low];//把大于key的值放在上次空出来的地方
	}//本循环结束后，对当前的枢轴a[left]而言，比它小的or相等的都到了左侧，比它大的or相等的都到了右侧
	a[low]=key;//把key填到上一步的位置，因为不管low和high的大小，终归会执行a[high]=a[low]这一步，从而a[low]空了出来

	quicksort(a,left,low-1);
	quicksort(a,low+1,right);
}