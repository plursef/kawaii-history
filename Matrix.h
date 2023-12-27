#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;
class Matrix
{
    private:            
        vector<vector<double>> v;
        int row=0;//行
        int col=0;//列
    
    /********   初始化部分   *********/
    
    
    public:
        //初始化为m行n列
        Matrix(int m,int n){row=m;
        col=n;
        v.resize(m, vector<double>(n, 0));
             
        }
        //文字控制Unit代表单位化
        Matrix(int n,const string &s){
                row = col = n;
                v.resize(n, vector<double> (n,0));
            if(s=="Unit"){    
                for(int i=0;i<n;i++)
                {
                    v[i][i] = 1;
                }
            }

        }

        //列表初始化构造函数
        Matrix(const initializer_list<initializer_list<double>> &initlist){
            row = initlist.size();
            col = initlist.begin()->size();
            v.resize(row,vector<double>(col,0));
            
            int i = 0;
            for (const auto &rowList : initlist) {
            int j = 0;
            for (const double &value : rowList) {
                v[i][j] = value;
                j++;
            }
            i++;
        }
        }

        //列表矩阵块初始化
        Matrix(const initializer_list<initializer_list<Matrix>> &initlist){
            int L_row = initlist.size();
            int L_col = initlist.begin()->size();
            int fullrow = 0, fullcol = 0;
            for(const auto& rowlist : initlist){
                fullrow += rowlist.begin()->row;
            }
            for(const auto& single : *initlist.begin()){
                fullcol += single.col;
            }
            
            v.resize(fullrow,vector<double>(fullcol,0));
            int now_row = 0, now_col = 0;
            for(int i=0; i<L_row; i++){
                now_col = 0;
                for(int j=0; j<L_col; j++){
                    int s=now_row, t=now_col;
                    for(const auto& rowlist : ((initlist.begin()+i)->begin()+j)->v){
                        t = now_col;
                        for(const double& colelem : rowlist){
                            v[s][t] = colelem;
                            t++;
                        }s++;
                    }

                
                now_col += ((initlist.begin()+i)->begin()+j)->col;
                }
                now_row += (initlist.begin()+i)->begin()->row;
            }
        }


        double Matrix_row(){
            return row;
        }
        
        double Matrix_col(){
            return col;
        }

    /********   初始化部分结束   *********/
    
    


    /********   一些运算重构   *********/
    public:       
        //加法重构
        Matrix operator+(const Matrix &A){
            Matrix m(v.size(),v[0].size());
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    m.v[i][j]=v[i][j]+A.v[i][j];
                }
            }
            return m;
        };

        //减法重构
        Matrix operator-(const Matrix &A){
            Matrix m(row,col);
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    m.v[i][j]=v[i][j]-A.v[i][j];
                }
            }
            return m;
        };
        
        //赋值符号同构
        void operator=(const Matrix &A){
            
            row = A.row;
            col = A.col;
            v.resize(A.row,vector<double>(A.col,0));
            
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    v[i][j]=A.v[i][j];
                }
            }
        };
        
        friend Matrix operator*(const Matrix&A,const Matrix &B);


        friend Matrix operator^(const Matrix& A,const Matrix & B);
    
        //输入一个矩阵
        friend istream &operator >> (istream& in , Matrix& M){
            cout<<"请输入"<<M.row<<"行"<<M.col<<"列""的矩阵"<<endl;
            for(int i=0;i<M.row;i++){
                
                for(int j=0;j<M.col;j++){
                     
                    cin >> M.v[i][j];
                }
            }
            return in;

        }
        //打印一个矩阵
        friend ostream &operator << (ostream& out , const Matrix& M){
            for(int i=0;i<M.row;i++){
                
                for(int j=0;j<M.col;j++){
                     
                    cout<<setw(5)<< M.v[i][j]<<' ';
                }
                cout<<'\n';
            }
            return out;

        }

    /********   运算重构结束   *********/
    
    
    
    
    
    
    public:

    /******************    矩阵性质运算     ***********************/
        //求行列式
        friend double det(Matrix M);
        
        //转置矩阵
        Matrix Turn(){int m=row,n=col;
            Matrix s(n,m);
            for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                s.v[i][j]=v[j][i];
            }
            return s;
        }

        //取出i行j列的元素（已废弃）
        double see_element(int i,int j)
        {return this->v[i][j];}
        
        //对矩阵元素设置（已废弃）
        void set_element(double d,int i,int j){
            v[i][j]=d;
        }
        
        //求逆矩阵
        Matrix reverse(){
            Matrix M(col,row);
            
            if(M.row==M.col){M=*this;int n=M.row;vector<double> identity(n,0);int i,j,k;
            //利用高斯消元法求逆矩阵
            for(i=0;i<n;i++)
            {M.v[i].insert(M.v[i].end(),identity.begin(),identity.end());
            M.v[i][i+n]=1.00;}
            //开始消元
            for(i=0;i<n;i++){k=0,j=i;
                while(M.v[j][i]==0) j++;
                //if(j==n);  //应该报错，但是我不会写；
                vector<double> temp;
                temp=M.v[i];M.v[i]=M.v[j];M.v[j]=temp;//非零元素交换到正确位置
                double divided=M.v[i][i];
                for(k=0;k<2*n;k++)
                M.v[i][k] /=divided;
                for(k=0;k<n;k++){double first=M.v[k][i];
                if(k==i) continue;
                    for(j=i;j<2*n;j++){
                        M.v[k][j] -= first*M.v[i][j];
                    }
                }

            }
            //消元结束留下矩阵
            for(i=0;i<n;i++){
                M.v[i].erase(M.v[i].begin(),M.v[i].begin()+n);
            }
            return M;
 
            }
            else{
                if(M.row<M.col){M=((*this).Turn()*(*this)).reverse()*((*this).Turn());
                }
                if(M.row>M.col){M=((*this).Turn())*((*this)*((*this).Turn())).reverse();
                }
                return M;
            }
        }


    /******************    矩阵性质运算结束     ***********************/

};


//求行列式，但是未考虑m!=n的情形
double det(Matrix M){int i=0;int m=M.v.size(),n=M.v[0].size();
            if(m==1)
            return M.v[0][0];
            while(M.v[0][i]==0) i++;
            if(i==n)
            return 0;
            double verse=1/M.v[0][i];
            for(int j=0;j<n;j++){
                if(j==i) continue;
                double coeff=M.v[0][j]*verse;
                for(int k=0;k<m;k++){
                    M.v[k][j] -= coeff*M.v[k][i];
                }
            }
            double d=M.v[0][i];
            M.v.erase(M.v.begin());
            for(int j=0;j<m-1;j++)
            M.v[j].erase(M.v[j].begin()+i);
            if((i&1)==0)
            return d*det(M);
            else
            return -d*det(M);

        }

// 矩阵乘法重构
Matrix operator*(const Matrix &A ,const Matrix &B){
    Matrix result(A.row,B.col);
    for(int i=0;i<A.row;i++){
        for(int j=0;j<B.col;j++){
            for(int k=0;k<A.col;k++)
            result.v[i][j] += A.v[i][k]*B.v[k][j];
        }
        
    }
    return result;
}

//张量乘法重构
Matrix operator^(const Matrix& A,const Matrix & B){
    Matrix res(A.row*B.row, A.col*B.col);
    for(int i=0; i<A.row; i++){
        for(int j=0; j<A.col; j++){
            for(int s=0; s<B.row; s++){
                for(int t=0;t<B.col; t++){
                    res.v[i*B.row + s][j*B.col + t] = A.v[i][j]*B.v[s][t];

                }
            }
        }
    }
    return res;

}



//矩阵快速幂
Matrix power(Matrix m,int n){Matrix res(m.Matrix_row(),"Unit");
    while(n)
    {
        if(n&1!=0)
        res = res*m;
        m = m*m;
        n >>= 1;
    }
    return res;

}




