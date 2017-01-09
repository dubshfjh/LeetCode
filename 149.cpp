最后还是Wrong answer，暂时弃坑
死于 test case [[0,9],[138,429],[115,359],[115,359],[-30,-102],[230,709],[-150,-686],[-135,-613],[-60,-248],[-161,-481],[207,639],[23,79],[-230,-691],[-115,-341],[92,289],[60,336],[-105,-467],[135,701],[-90,-394],[-184,-551],[150,774]]

首先用蛮力法，对第i(0,1...n-1)个节点进行分析，计算其余n-1个节点与i节点的斜率，如果节点j,k与节点i的斜率相同，则j,k都在于i相连的同一条直线上
Wrong answer，[[0,0],[1,1],[0,0]]
修正1：当i,j的斜率为新数字时，应该初始化gradient_num[斜率] = 点i的数目 + 点j的数目("不能误认为i,j只出现一次，而初始化为 2 ")；当斜率已存在时，需要gradient_num[斜率] += 点j的数目，而不能认为j只出现一次而执行"++"操作
在统计不存在斜率的点i,j时，也应该初始化nogradient_num为点i的数目，然后 += 点j的数目
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
修正2：map内部存储机制实际是以红黑树为基础，红黑树在插入节点时，必须依照大小比对之后在一个合适的位置上执行插入动作。所以作为关键字，起码必须有“<”这个比较操作符。
我们知道，int，float，enum，size_t等等简单关键字，都有内置的比较函数，与map搭配无论是插入还是查找，都没什么问题。但是作为复杂数据类型，如果没有明确定义“<”比较操作符，
就不能与map直接搭配使用，除非我们自己定义第三个参数。

算法思想：判断 3 个点 i,j,k是否在同一条直线上的方法为：(i,j),(i,k)的斜率相同，但是也不能忽略"相同点"与"斜率不存在"两种情况
step one：对points这个vector进行坐标排序，统计出相同(x,y)坐标的点数目
step two：用点 i 遍历所有点的集合，与点 i 在同一条直线上的点j需要满足3个条件之一
    1. 与点 i 坐标完全相同的点，"不能武断地认为一个点只存在一次，因此在统计斜率不存在直线上的点数/某个斜率的点数时，都需要用 +=num[points[i]]替代 +=1，避免忽略相同点的情况"
    2. 与点 i 横坐标相同的点（这条直线不存在斜率），初始化变量nogradient_num = num[points[i]]，在遇到点 j 时，计算nogradient_num += num[points[j]]
    3. 与点 i 在斜率取值相同的一条直线上的点，初始化变量 map[斜率gra] = num[points[i]]+num[points[j]]，在遇到下一个与 i 的斜率也为gra的点k时，计算 map[斜率gra] += num[points[k]]
step three：
    对每个点i，更新 res = max(res,nogradient_num,点i构成的map[斜率gra])

"对 vector<Point> 进行排序的优化"：在用点i遍历所有点集合时，在分析完点i后可以跳过 之后尾随的 与(i_x,i_y)坐标一样的相同点，减少运行时间

"遇到的坑"：
    1. map内部存储机制实际是以红黑树为基础，红黑树在插入节点时，必须依照大小比对之后在一个合适的位置上执行插入动作。因此将 struct Point 作为 map 的key时，必须自定义 key 的比较机制
    2. 在定义key的排序方法时，有着重载 operator "<"/ 自定义比较函数两种做法，其中重载operator "<" 的参数必须为 2个"const Point &"，所以它不能作为 class 的成员函数，因为成员函数只允许 1 个参数 
    3. vector,map这类动态数据结构对于溢出的下标是有着默认值"0"的，e.g. map[不存在key] = 0，points[points.size()].x = points[points.size()].y = 0;
    4. 在计算斜率时有大坑！！！ double k = double(y)/double(x)才正确，如果使用 double k = (int 变量)/(int 变量)会导致 k 的小数位全被弃掉！！！

bool operator <(const Point &left,const Point &right){
    if(left.x < right.x){
        return true;
    }
    else if(left.x > right.x){
        return false;
    }
    else{
        return left.y < right.y;
    }
}
class Solution {
public:
    /*重载<作为成员函数不行，两个操作数都要求是const*/  
    //bool operator <(const Key& key);  
    static bool compare(Point left,Point right){
        if(left.x < right.x){
            return true;
        }
        else if(left.x > right.x){
            return false;
        }
        else{
            return left.y < right.y;
        }
    }

    int maxPoints(vector<Point>& points) {
        int res = 0;
        if(points.size() <= 2){
            return points.size();
        }
        sort(points.begin(),points.end(),compare);
        // for(int i=0;i<points.size();i++){
        //     cout<<points[i].x<<",,,"<<points[i].y<<endl;
        // }
        map<double,int> gradient_num;
        map<Point,int> point_num;//
        int i,j;
        i = 0;
        while(i<points.size()){
            for(j=i+1;j<points.size();j++){
                if(points[j].x != points[i].x || points[j].y != points[i].y){
                    break;
                }
            }
            point_num[points[i]] = j-i;

            // cout<<points[i].x<<",,,"<<points[i].y<<",,,"<<point_num[points[i]]<<endl;
            // cout<<i<<",,,"<<j<<",,,"<<points[j].x<<",,,"<<points[j].y<<",,,"<<point_num[points[i]]<<endl;
            i = j;
        }

        for(i=0;i<points.size();i++){
            if(i>0 && points[i].x == points[i-1].x && points[i].y == points[i-1].y){
                continue;
            }
            gradient_num.clear();
            int nogradient_num = point_num[points[i]];
            for(j=i+1;j<points.size();j++){
                if(points[j].x == points[j-1].x && points[j].y == points[j-1].y){
                    continue;
                }

                if(points[j].x == points[i].x){
                    nogradient_num += point_num[points[j]];
                }
                else{
                    double gradient = double(points[j].y - points[i].y)/double(points[j].x - points[i].x);
                    // cout<<points[i].x<<",,,"<<points[i].y<<",,,"<<gradient<<endl;
                    if(gradient_num.find(gradient) == gradient_num.end()){
                        gradient_num[gradient] = point_num[points[i]] + point_num[points[j]];
                    }
                    else{
                        gradient_num[gradient] += point_num[points[j]];
                    }
                }
            }
            
            res = max(res,nogradient_num);
            for(auto it=gradient_num.begin();it!=gradient_num.end();it++){
                res = max(res,it->second);
            }
        }
        return res;
    }
};