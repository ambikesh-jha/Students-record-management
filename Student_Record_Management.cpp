#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class student
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, sci_marks, lang2_marks, cs_marks;
    double average;
    char grade;
    
    public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
}; 

void student::calculate()
{
    average=(eng_marks+math_marks+sci_marks+lang2_marks+cs_marks)/5.0;
    if(average>=90) grade='A';
    else if(average>=75) grade='B';
    else if(average>=50)grade='C';
    else if(average>=40)grade='D';
    else grade='F';
}
void student::getdata()
{
    cout<<"Enter student's roll number: "; cin>>rollno;
    cout<<"Enter student's name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"__________________________________________"<<endl;
    cout<<"\n\nEnter Student's Marks out of 100"<<endl;

    cout<<"\n\nEnter marks in English: ";cin>>eng_marks;
    cout<<"Enter marks in Math: ";cin>>math_marks;
    cout<<"Enter marks in Science: ";cin>>sci_marks;
    cout<<"Enter marks in Second language: ";cin>>lang2_marks;    
    cout<<"Enter marks in Computer science: ";cin>>cs_marks;
    calculate();
}
void student::showdata() const
{
    cout<<"\nRoll No. of student : "<<rollno;
    cout<<"\nName of student     : "<<name;
    cout<<"\nEnglish             : "<<eng_marks;
    cout<<"\nMaths               : "<<math_marks;
    cout<<"\nScience             : "<<sci_marks;
    cout<<"\nSecond Language     : "<<lang2_marks;
    cout<<"\nComputer Science    : "<<cs_marks<<endl;
    cout<<"\nAverage Marks       | "<<average;
    cout<<"\nGrade of student is | "<<grade;
}
int student::retrollno() const
{
return rollno;
}

void create_student()
{
    student stud;
    ofstream oFile;
    oFile.open("student.dat",ios::binary|ios::app);stud.getdata();
    oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
    oFile.close();
    cout<<"===================================="<<endl;
    cout<<"\nNEW RECORD CREATED "<<endl;
    cout<<"===================================="<<endl;
    cin.ignore();
    cin.get();
}
void display_sp(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout<<"FILE IS EMPTY... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        if(stud.retrollno()==n)
        {
            stud.showdata();
            flag=true;
        }
    }
    
    iFile.close();
    if(flag==false)
    cout<<"\n\nRECORD NOT FOUND";
    cin.ignore();
    cin.get();
}
void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
{
    cout<<"FILE IS EMPTY... Press any Key to exit";
    cin.ignore();
    cin.get();
    return;
}

cout<<"\n\n\t\tDISPLAYING ALL RECORDS\n";
while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
{
    stud.showdata();
    cout<<"\n\n====================================\n";
}

inFile.close();
cin.ignore();
cin.get();
}
void delete_student(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout<<"FILE IS EMPTY... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        if(stud.retrollno()!=n)
        {
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"===================================="<<endl;
    cout<<"RECORD DELETED.."<<endl;
    cout<<"===================================="<<endl;
    cin.ignore();
    cin.get();
}
void change_student(int n)
{
    bool found=false;
    student stud;
    fstream fl;
    fl.open("student.dat",ios::binary|ios::in|ios::out);
    if(!fl)
    
    {
        cout<<"FILE IS EMPTY... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    
    while(!fl.eof() && found==false)
    {
        fl.read(reinterpret_cast<char *> (&stud), sizeof(student));
        if(stud.retrollno()==n)
        {
            stud.showdata();
            cout<<endl<<"===================================="<<endl<<endl;
            cout<<"\nEnter new student details:"<<endl<<endl;
            stud.getdata();
            int pos=(-1)*static_cast<int>(sizeof(stud));
            fl.seekp(pos,ios::cur);
            fl.write(reinterpret_cast<char *> (&stud), sizeof(student));
            cout<<"===================================="<<endl;
            cout<<"\nRECORD UPDATED "<<endl;
            cout<<"===================================="<<endl;
            found=true;
        }
    }
    
    fl.close();
    if(found==false)
    cout<<"===================================="<<endl;
    cout<<"RECORD NOT FOUND "<<endl;
    cout<<"===================================="<<endl;
    cin.ignore();
    cin.get();
}

int main()
{
    char ch;
    cout<<setprecision(2);
    
    do
    {
        char ch;
        int num;
        system("cls");
        cout<<"Welcome to Student Record Management System"<<endl;
        cout<<"\nMENU"<<endl;
        cout<<"\n1. CREATE NEW STUDENT RECORD "<<endl;
        cout<<"2. SEARCH STUDENT RECORDS"<<endl;
        cout<<"3. DISPLAY ALL STUDENT RECORDS"<<endl;
        cout<<"4. DELETE STUDENT RECORD(S)"<<endl;
        cout<<"5. UPDATE STUDENT RECORD"<<endl;
        cout<<"6. EXIT"<<endl;
        cout<<"\nEnter your choice : ";cin>>ch;
        system("cls");
        
    switch(ch)
    {
        case '1': create_student(); break;
        case '2': cout<<"\n\nENTER STUDENT'S ROLL NO. ";cin>>num;
                  display_sp(num); break;
        case '3': display_all(); break;
        case '4': cout<<"\n\nENTER STUDENT'S ROLL NO. ";cin>>num;
                  delete_student(num);break;
        case '5': cout<<"\n\nENTER STUDENT'S ROLL NO. "; cin>>num;
                  change_student(num);break;
        case '6': cout<<"===================================="<<endl;
                  cout<<"Exiting, Thank you!"<< endl;
                  cout<<"===================================="<<endl<<endl;
                  exit(0);
    }
    
    }while(ch!='6');
    return 0;
}
