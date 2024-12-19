#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;
struct student{
    string name;
    int ncc, y;
    vector<string> cc;//list of completed courses
    unordered_map<string, string> ec;//slot, code of the course

};

struct course{
    string code, name, slot;
    int cred, cap, npreq;
    vector<string> preq;
    vector<string>waitlist;


};
int main(){
    int q;
    std::cin>>q;
    unordered_map<string, student> studentMap;//student id, student class
    unordered_map<string, course> courseMap;//course code, course class
    unordered_map<string, vector<string>> enrollmentMap; //course code, vector containing the ids off all the students enrolled in the course
    while(q--){
        string command;
        cin>>command;
        if(command=="add_student"){
            string x;
            vector<string> line;
            //getting the student details
            if (cin.peek() == '\n') {
              cin.ignore(1, '\n');
            }
            getline(cin, x);  
            stringstream ss(x);  
            while (ss >> x) {
                line.push_back(x); 
            } 

            string id=line[0];
            student newStudent;
            newStudent.name=line[1];
            newStudent.ncc=stoi(line[2]);
            newStudent.y=stoi(line[3]);
            newStudent.ec;
            vector<string> line1;
            if (cin.peek() == '\n') {
              cin.ignore(1, '\n');
            }
            //taking the input of the completed courses
            getline(cin, x);  
            stringstream s1(x);  
            while (s1 >> x) {  
                line1.push_back(x);  
            }
            newStudent.cc=line1;
            studentMap[id]=newStudent;
            
            
            
        }
        else if(command=="add_course"){
            
            string code, name, slot;
            int cred, cap, npreq;
            vector <string> preq;
            if (cin.peek() == '\n') {
              cin.ignore(1, '\n');
            }
            string x;
            vector<string> line;
            getline(cin, x);  
            stringstream ss(x);  
            while (ss >> x) {  
                line.push_back(x); 
            }
            string code1=line[0];
            
            course newCourse;
            newCourse.name=line[1];
            newCourse.cred=stoi(line[2]);
            newCourse.cap=stoi(line[3]);
            newCourse.slot=line[4];
            newCourse.npreq=stoi(line[5]);
            newCourse.waitlist;
            
            
            vector <string> line1;
            
            getline(cin, x); 
            stringstream s1(x);  
            while (s1 >> x) {  
                line1.push_back(x);   
            }
            //checking if the addition of this course will induce a cyclic dependency 
            vector<string> preqq;
            for(string str: line1){
                
                if(courseMap.find(str) != courseMap.end()) {
                    
                    preqq.insert(preqq.end(), courseMap[str].preq.begin(), courseMap[str].preq.end());
                   
                } 
                
                preqq.push_back(str);
                
                
            }
            
            newCourse.preq=preqq;
            //if code1 (the code of the course) cant be found in the altered preq vector, it means that it is ok to add it
            if(find(newCourse.preq.begin(), newCourse.preq.end(), code1)== newCourse.preq.end()){
            courseMap[code1]=newCourse;
            
            enrollmentMap[code1];
            }
            
            
            
        }
        
        else if(command=="enroll"){
            vector <string> line;
            string x;
            if (cin.peek() == '\n') {
              cin.ignore(1, '\n');
            }
            getline(cin, x);  
            stringstream ss(x);  
            while (ss >> x) {  
                line.push_back(x);   
            }
            string code2, id;
            code2=line[1];
            
            id=line[0];
            if (courseMap.find(code2) != courseMap.end()) {//checking that the course has been registered
                if(studentMap.find(id)!=studentMap.end()){//checking if the student id is valid
                    if(courseMap[code2].cap!=0){
                        vector<string>vec;
                        bool flag=true;
                        vec=studentMap[id].cc;
                        //checking if all the pre-req exsist in the courses completed by the student
                        for(string i: courseMap[code2].preq){
                            
                            if (find(vec.begin(), vec.end(), i)==vec.end()){
                                flag=false;
                                break;

                            }
                        }
                        if(flag){
                            if(studentMap[id].ec.find(courseMap[code2].slot)==studentMap[id].ec.end()){//checking if the student is free in the slot the course is in
                                enrollmentMap[code2].push_back(id); //adding the student to the course's list of students
                                courseMap[code2].cap=courseMap[code2].cap-1; //decreasing the capacity of the course by one
                                studentMap[id].ec[courseMap[code2].slot]=code2; //adding the time slot of the course enrolled to the students list of course and slot

                            }
                        }
                    }
                    else{
                        
                        vector<string>vec;
                        bool flag=true;
                        vec=studentMap[id].cc;
                        //checking if all the pre-req exsist in the courses completed by the student
                        for(string i: courseMap[code2].preq){
                            
                            if (find(vec.begin(), vec.end(), i)==vec.end()){
                                flag=false;
                                break;

                            }
                        }
                        if(flag){
                            //if the required courses have been completed, the student is pushed into the waitlist
                            //checking if the student is available in the course's slot will be done at the time of enrollment
                            courseMap[code2].waitlist.push_back(id);

                        }

                    }

                    

                }
                
            }
        }
        else if(command=="print"){
            vector <string> line;
            string x;
            if (cin.peek() == '\n') {
              cin.ignore(1, '\n');
            }
            getline(cin, x);  
            stringstream ss(x);  
            while (ss >> x) {  
                line.push_back(x);   
            }
            string code3=line[0];
            //checking if the course is registered in the system
            if(courseMap.find(code3)==courseMap.end()) cout<<"Invalid Course "<<code3<<endl;
            else{
                if(enrollmentMap[code3].size()==0){
                    cout<<"No enrollments have been made in this course"<<endl;
                }
                else{
                    cout<<"Enrolled students in "<<code3<<endl;
                    for(string i: enrollmentMap[code3]){
                       cout<<i<<' ';//printing ou the ids of the students enrolled in the course
                    }
                cout<<endl;
                }
                

            }
            
            
        }
        else if(command=="drop"){
            vector <string> line;
            string x;
            string id, code4;
            if (cin.peek() == '\n') {
              cin.ignore(1, '\n');
            }
            getline(cin, x);  
            stringstream ss(x);  
            while (ss >> x) {  
                line.push_back(x);   
            }
            id=line[0];
            code4=line[1];
            enrollmentMap[code4].erase(remove(enrollmentMap[code4].begin(), enrollmentMap[code4].end(), id), enrollmentMap[code4].end());//removing the dropper's id from the enrollmentMap
            string slott=courseMap[code4].slot;
            studentMap[id].ec.erase(slott);//freeing the course's slot from the student's map
            if(courseMap[code4].waitlist.size()==0){//if no one is there in the waitlist, then the capacity is decreased by one
                courseMap[code4].cap=1;
            }
            else{
                string idd;
                while(courseMap[code4].waitlist.size()!=0){//checking if any of the students in waitlist qualify regitration
                idd=courseMap[code4].waitlist[0];
                courseMap[code4].waitlist.erase(courseMap[code4].waitlist.begin());
                if(studentMap[idd].ec.find(courseMap[code4].slot)==studentMap[idd].ec.end()){//checking if the student has the slot free at the time of enrollment
                    enrollmentMap[code4].push_back(idd); //adding the student to the course's list of students
                    courseMap[code4].cap=courseMap[code4].cap-1; //decreasing the capacity of the course by one
                    studentMap[idd].ec[courseMap[code4].slot]=code4;//adding the time slot of the course enrolled to the students list of course and slot
                    break;
                }
                }
                


            }


        }
            
    
    }
    



}