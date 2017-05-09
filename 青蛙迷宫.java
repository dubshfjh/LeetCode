import java.util.*;

public class Main{
    List<String> res;
    int remainHealth;
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()){
            Main obj = new Main();
            obj.res = new ArrayList<String>();
            obj.remainHealth = -1;
            int n = sc.nextInt();
            int m = sc.nextInt();
            int health = sc.nextInt();
            int[][] matrix = new int[n][m];
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    matrix[i][j] = sc.nextInt();
                }
            }
            List<String> path = new ArrayList<String>();
            obj.solveMatrix(matrix,n,m,0,0,health,path);
            if(obj.remainHealth < 0){
                System.out.println("Can not escape!");
            }
            else{
                StringBuilder resStr = new StringBuilder();
                for(String temp:obj.res){
                    resStr.append(temp).append(",");
                }
                resStr.deleteCharAt(resStr.length()-1);
                System.out.println(resStr.toString());
            }

        }
    }

    public void solveMatrix(int[][] matrix,int n,int m,int i,int j,int health,List<String> path){
        if(health<=remainHealth || i<0 || i>=n || j<0 || j>=m || matrix[i][j]==0){
            return;
        }
        path.add("["+i+","+j+"]");
        if(i==0 && j==m-1){
            if(health > remainHealth){
                res = new ArrayList<String>(path);
                remainHealth = health;
            }
            path.remove(path.size()-1);
            return;
        }
        matrix[i][j] = 0;
        //分别上(health-3)，下(health-0)，左()，右 四个方向
        solveMatrix(matrix,n,m,i-1,j,health-3,path);
        solveMatrix(matrix,n,m,i+1,j,health,path);
        solveMatrix(matrix,n,m,i,j-1,health-1,path);
        solveMatrix(matrix,n,m,i,j+1,health-1,path);
        matrix[i][j] = 1;
        path.remove(path.size()-1);
    }
}