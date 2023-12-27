#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class Student{
    private:
    string ID;
    pair<string,string> name;
    vector<int> score;

    public:
    //初始化
    Student(string &Id,string &name1,string &name2,int &s1,int &s2,int &s3): ID(Id),name(name1,name2)
    {
        score.push_back(s1);
        score.push_back(s2);
        score.push_back(s3);

    }
    Student(){
        score.resize(3,0);
    }
    
    friend bool same(const Student &s1,const Student &s2);

    friend bool cmp(const Student &s1,const Student &s2);

    
    //哎 卷王 竟然比分数（这里必须这么写）
    static bool Score_cmp(const Student &s1,const Student &s2){

    int sum1=s1.score[0]+s1.score[1]+s1.score[2];
    int sum2=s2.score[0]+s2.score[1]+s2.score[2];
    if(sum1>sum2)
    return true;
    else if(sum1<sum2)
    return false;
    else
    return s1.ID<s2.ID;
}


    //获得新学生
    void get_a_new_student(vector<Student> &v){
        cin>>*this;
        int i=0;
        while(i<v.size()&&cmp(*this,v[i])){
            i++;
        }
        if(i==v.size())
        v.push_back(*this);
        else
        if(!same(*this,v[i])){
            v.insert(v.begin()+i,*this);

        }
    }

    //调整学生成绩
    void modify(vector<Student> &v){
        Student new_one;
        cin>>new_one;
        *this=new_one;
        for(int i=0;i<v.size();i++){
            if(same(v[i],*this)){
                v[i]=*this;
            }
        }

    }
    //删除学生
    void delete_student(vector<Student> &v){
        string target;
        cin>>target;
        for(int i=0;i<v.size();i++){
            if(v[i].ID==target)
            v.erase(v.begin()+i);
        }
        


    }
    //寻找合适ID的学生
    void find_ID(vector<Student> &v){
        string target;
        cin>>target;
        for(int i=0;i<v.size();i++){
            if(v[i].ID==target)
            {
                cout<<v[i];
            }
        }

    }

    //按姓名查找
    void find_name(vector<Student> &v){
        pair<string,string> target;
        cin>>target.first>>target.second;
        for(int i=0;i<v.size();i++){
            if(v[i].name==target)
            {
                cout<<v[i];
            }
        }

    }


    //按学号输出
    void ID_out(vector<Student> &v){
        vector<Student>::iterator it;
        for(it=v.begin();it<v.end();++it){
            cout<<*it;
        }

        
    }

    //按成绩输出
    void Score_out(vector<Student> &v){
        sort(v.begin(),v.end(),Student::Score_cmp);
        for(const auto& stu : v){
            cout<<stu;
        }

        
    }

    friend istream &operator>>(istream &in,Student &S);

    friend ostream &operator<<(ostream &out,const Student &S);

    
    



};

//比较
bool cmp(const Student &s1,const Student &s2){
    return s1.ID>s2.ID;
}

//cin 重载
istream &operator>>(istream &in,Student &S){
    in>>S.ID>>S.score[0]>>S.score[1]>>S.score[2]>>S.name.first>>S.name.second;
    return in;
}

//cout重载
ostream &operator<<(ostream &out,const Student &S){
    out<<S.ID<<' '<<S.score[0]<<' '<<S.score[1]<<' '<<S.score[2]<<' '<<S.name.first<<' '<<S.name.second<<' '<<endl;
    return out;
}

//是同一个学生
bool same(const Student &s1,const Student &s2){
    return (s1.ID==s2.ID);
    
}

//定义一个函数指针
typedef void (Student::*function)(vector<Student>&);

int main() {
    int select=-1;
    vector<Student> data;
    
    //刚学会的呢 ^_^
    function func[]= {NULL,
    &Student::get_a_new_student,
    &Student::modify,
    &Student::delete_student,
    &Student::find_ID,
    &Student::find_name,
    &Student::ID_out,
    &Student::Score_out,
    };

    //只是充当一个函数实现的载体
    Student S;
    while(cin>>select){
        if(!select)
        return 0;
        (S.*(func[select]))(data);     
    }
}