// wap to assign values to each member of the following structure. Pass the populated str to a func 
// using call-by-value and another func 
// using call-by-address and print the value of each member of the structure 

#include <stdio.h>

struct dob_age
{
    int date;
    int month;
    int year;
    int age;
};

struct student_info
{
    int roll_no;
    char name[50];
    float cgpa;
    struct dob_age dob_age;
};

void displayByValue(struct student_info s)
{
    printf("Using Call-by-Value:\n");
    printf("Roll No: %d\n", s.roll_no);
    printf("Name: %s\n", s.name);
    printf("CGPA: %.2f\n", s.cgpa);
    printf("DOB: %d/%d/%d\n", s.dob_age.date, s.dob_age.month, s.dob_age.year);
    printf("Age: %d\n\n", s.dob_age.age);
}

void displayByAddress(struct student_info *s)
{
    printf("Using Call-by-Address:\n");
    printf("Roll No: %d\n", s->roll_no);
    printf("Name: %s\n", s->name);
    printf("CGPA: %.2f\n", s->cgpa);
    printf("DOB: %d/%d/%d\n", s->dob_age.date, s->dob_age.month, s->dob_age.year);
    printf("Age: %d\n", s->dob_age.age);
}

int main()
{
    struct student_info s1 = {1, "Rahul", 8.5, {12, 12, 1999, 21}};
    displayByValue(s1);
    displayByAddress(&s1);
    return 0;
}
