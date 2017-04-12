Wrong Answer，思路完全错误了
// class Solution {
// public:
//     int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
//        bool inter_hori,inter_verti;//分别判断两个矩形横向交叉和垂直交叉
//        if((A>=E&&A<=G)||(E>=A&&E<=C)){
//             inter_hori = true;
//        }
//        if((B>=F&&B<=H)||(F>=B&&F<=D)){
//             inter_verti = true;
//        }
//        if(!inter_hori && !inter_verti){
//             return (C-A)*(D-B) + (G-E)*(H-F);
//        }
//        else if(inter_hori && !inter_verti){
            
//        }
//        else{
//             int midrec_area,leftrec_area,rightrrec_area;//中间矩形的长：左侧矩形右上角x - 右侧矩形左下角x；中间矩形的宽：上方矩形右上角y-下方矩形左下角y    
//             if(A<E){//此时A处于左侧矩形，
//                 if(H<D){//此时A处于上侧矩形
//                     midrec_area = (C-E)*(D-F);             
//                 }
//                 else{
//                     midrec_area = (C-E)*(H-A);
//                 }
//                 leftrec_area = (E-A)*(D-B);
//                 rightrrec_area = (G-C)*(H-F);
//             }
//             else{//此时E处于左侧矩形
//                 if(H<D){//此时A处于上侧矩形
//                     midrec_area = (G-A)*(D-F);
//                 }
//                 else{
//                     midrec_area = (G-A)*(H-A);
//                 }
//                 leftrec_area = (A-E)*(H-F);
//                 rightrrec_area = (C-G)*(D-B);
//             }
//             return leftrec_area+midrec_area+rightrrec_area;
//        }
//     }
// };


返回左侧矩形面积 + 右侧矩形面积 - 相交矩形面积

相交矩形 长 = min{矩形1和矩形2右侧边的x值，即靠左的右侧边x值} - max{矩形1和矩形2左侧边的x值，即靠右的左侧边x值}
相交矩形 宽 = min{矩形1和矩形2上侧边的y值，即靠下的上侧边y值} - max{矩形1和矩形2下侧边的y值，即考上的右侧边y值}

如果相交矩形 长<0, or 相交矩形 宽<0， 则矩形1和矩形2 不相交，相交矩形面积为0

上面的思想仍有缺陷！！！e.g. length = -1500000000 - 1500000000 < INT_MIN，于是length>0，
    因此只能先计算 right和left，如果 right>left 才计算长 = right-left;
    同时，先计算 bottom和top，如果 top>bottom 才计算宽 = top-bottom;防止减法的overflow问题！！！

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int interec_area;
        int left = max(A,E);
        int right = min(C,G);
        int bottom = max(B,F);
        int top = min(D,H);
        /* 错误！！！e.g. length = -1500000000 - 1500000000 < INT_MIN，于是length>0
        int length = min(C,G) - max(A,E);
        int width = min(D,H) - max(B,F);
        */
        if(right<=left || top<=bottom){
            interec_area = 0;
        }
        else{
            interec_area = (right-left)*(top-bottom);
        }
        return (C-A)*(D-B) + (G-E)*(H-F) - interec_area;
    }
};