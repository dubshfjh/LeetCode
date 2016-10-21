/*
不能直接计算出temp*temp后，将其与x比较
temp		temp*temp
1073697799,,,-209283023
536848899,,,-589169655
268424449,,,658024961
402636674,,,1883192836
 */
本人使用的(middle>x/middle)这种避免大数相乘overflow的做法简直冗余，必须排除middle=(0+1)/2 or (0+0)/2这两种middle=0的情况=。=
直接使用double类型的middle遍历，使用middle*middle就会得到真实解了
Attention!!!判断(double类型的a==double类型的b)只能够使用abs(a-b)<1e^-num这种方式。而且鉴于middle^2<x和middle^2>x时，middle可能就是最终解，所以
对应的low和high都只能移到middle本身，而非middle+1 or middle-1
class Solution {
public:
    int mySqrt(int x) {
        int low,high,middle;
        low=0;
        high=x;
        if(x<0){
        	return INT_MIN;
        }
        while(low<=high){
        	middle=(low+high)/2;
        	cout<<middle<<",,,"<<endl;
        	if(middle>0){
        		if(middle==x/middle){
	        		return middle;
	        	}
	        	else if(middle<x/middle){
	        		low=middle+1;
	        	}
	        	else{
	        		high=middle-1;
	        	}
        	}
        	else{
        		if(middle*middle==x){
        			return middle;
        		}
        		else if(middle*middle<x){
        			low=middle+1;
        		}
        		else{
        			high=middle-1;
        		}
        	}
        }
        return high;
    }
};

二分法优化～～～
class Solution {
public:
    int mySqrt(int x) {
    	double begin,end,middle,res;//middle设置为double，可以使得大数相乘时不至于overflow!
    	begin=0;
    	end=x;
    	res=1;
    	middle=1;//middle初值为1，可以避免
    	while(abs(res-x)>0.00001){
    		middle=(begin+end)/2;
    		res=middle*middle;
    		//cout<<middle<<",,,"<<res<<endl;
    		if(res>x){//由于当前的res为double类型，所以它可能只是和x有较小误差(甚至可能<1e-6)，最终解可能就是middle本身
    			end=middle;//因此end只能左移到middle，而非middle-1
    		}
    		else{
    			begin=middle;
    		}
    	} 
    	return (int)middle;
    }
};

牛顿迭代法是牛顿在17世纪提出的一种在实数域和复数域上近似求解方程的方法，即不断获得曲线f(x)=0的近似值的过程。
牛顿迭代法核心就是定义一个初始近似值X0,过点(X0,f(X0))做切线,其方程为y=f(X0)+f'(X0)(X-X0)，该线与X轴的交点X1=X0-f(X0)/f'(X0)
重复该过程，通过不断求解 Xn+1=Xn-f(Xn)/f'(Xn) 得到更高精度的近似解
PS：X0 > X1 > X2 >...>Xn，所以本题的初值X0不能取 n/2，否则当N==1时就不满足了
而本题实际上就是求 x^2=n的解，所以f(x)=x^2-n，f'(x)=2*x，所以Xn+1 = Xn- xn^2-n/2Xn = Xn/2 + n/2Xn

class Solution {
public:
    int mySqrt(int x) {
    	double pre=0;
    	double current=x; // 这里从x开始 从x/2开始会导致 x==1时 不能满足  x(n+1)= xn - f'(xn)/f(xn)
    	while(abs(current-pre)>0.000001){
    		pre = current;
    		current = pre/2+x/(2*pre);
    	}
    	return (int)current;
    }
};