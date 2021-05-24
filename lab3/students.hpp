#ifndef _STUDENTS_HPP_
#define _STUDENTS_HPP_ 1
#include <string>


class Person {
	private:
		std::string firstName;
		std::string middleName;
		std::string lastName;
	public:
        Person() {}

        Person(std::string name1,std::string name2, std::string name3) : firstName(name1), middleName(name2), lastName(name3) {}
		std::string GetFirstName(){
            return firstName;
        }
        std::string GetMiddleName(){
            return middleName;
        }
        std::string GetLastName(){
            return lastName;
        }
        void SetFirstName(std::string str){
            firstName = str;
        }
        void SetMiddleName(std::string str){
            middleName = str;
        }
        void SetLastName(std::string str){
            lastName = str;
        }

        std::string WhoIs(){
            return "Person";
        }
};

class Student : public Person {
    private:
        std::string Group;
    public:
        Student(){
            Group;
        }
        Student(std::string name1, std::string name2, std::string name3, std::string group){
            SetFirstName(name1);
            SetMiddleName(name2);
            SetLastName(name3);
            Group = group;
        }
        std::string GetGroup(){
            return Group;
        }

        void SetGroup(std::string grp){
            Group = grp;
        }

        std::string WhoIs(){
            return "Student";
        }
};

class Teacher : public Person{
    private:
        std::string subject;
    public:
        Teacher(std::string name1, std::string name2, std::string name3, std::string group){
            SetFirstName(name1);
            SetMiddleName(name2);
            SetLastName(name3);
            subject = group;
        }
        std::string GetSubject(){
            return subject;
        }

        void SetSubject(std::string grp){
            subject = grp;
        }

        std::string WhoIs(){
            return "Teacher";
        }
};

#endif