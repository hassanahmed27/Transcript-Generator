#include<iostream>
#include<iomanip>
#include<cstring> 
using namespace std;

int main(){
    const int maxcourses = 7;
    const int max_Cn_Length = 100;
    int numofcourses;
    double credit_hours[maxcourses], obtained_marks[maxcourses], t_points = 0, t_credit_hours = 0;
    char course_name[maxcourses][max_Cn_Length];

    cout<<"\n================ TRANSCRIPT GENERATOR ================"<<endl;

    // Taking the input of number of courses 
    do {
        cout<<"\nEnter the Number of Courses (MAX 7): ";
        if(!(cin >> numofcourses) || numofcourses > maxcourses || numofcourses <= 0 || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Invalid input. Please enter a number between 1 and "<<maxcourses<<": ";
        } else{
            break;
        }
    } while(true);

    // Taking Input of the course name and checking its length
    for(int i = 0; i < numofcourses; i++){
        cin.ignore();
        cout<<"\nEnter the name of course "<<i+1<<": ";
        fgets(course_name[i], max_Cn_Length, stdin);
        
        // removing the newline character
        course_name[i][strlen(course_name[i])-1]='\0'; 
        if(cin.fail()){
            cout<<"Error: Failed to read course name."<<endl;
            return 1;
        }

        // Taking Input of the obtained marks
        do{
            cout<<"\nEnter the obtained marks of "<<course_name[i]<<": ";
            if(!(cin>>obtained_marks[i]) || obtained_marks[i]<0 || obtained_marks[i]>100 || cin.peek()!='\n'){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Error: Please enter obtained marks between 0 and 100."<<endl;
            }else{
                break;
            }
        } while(true);

        // Taking Input of credit hours 
        do {
            cout<<"Enter the total credit hours of "<<course_name[i]<<": ";
            if(!(cin>>credit_hours[i]) || credit_hours[i]<=0 || credit_hours[i]>3 || cin.peek()!='\n'){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Please enter credit hours between 1 and 3: "<<endl;
            } else{
                break;
            }
        } while(true);

        // Calculating the total credit hours and total points
        t_credit_hours+=credit_hours[i];
        t_points+=(obtained_marks[i] / 100.0)*credit_hours[i]*4.0;
    }

    // Calculating GPA
    float GPA = t_points / t_credit_hours;
    string grade;

    // Calculating grade based on GPA
    if (GPA >= 3.86) {
        grade = "A";
    } else if (GPA >= 3.70) {
        grade = "A-";
    } else if (GPA >= 3.30) {
        grade = "B+";
    } else if (GPA >= 3.00) {
        grade = "B";
    } else if (GPA >= 2.70) {
        grade = "B-";
    } else if (GPA >= 2.30) {
        grade = "C+";
    } else if (GPA >= 2.00) {
        grade = "C";
    } else if (GPA >= 1.70) {
        grade = "C-";
    } else if (GPA >= 1.30) {
        grade = "D+";
    } else if (GPA >= 1.00) {
        grade = "D";
    } else {
        grade = "F";
    }

    // Generating Transcript
    cout<<"\nTranscript:\n";
    cout<<"--------------------------------------------------------------\n";
    cout<<left<<setw(30)<<"Course"<<setw(20)<<"Credit Hours"<<"Marks\n";
    cout<<"--------------------------------------------------------------\n";
    for(int i=0; i<numofcourses; i++){
        cout<<left<<setw(30)<<course_name[i]
            <<setw(20)<<credit_hours[i]
            << obtained_marks[i]<<endl;
    }
    cout<<"--------------------------------------------------------------\n";
    cout<<"GPA for the semester: "<<fixed<<setprecision(2)<<GPA<<endl;
    cout<<"Grade: "<<grade<<endl;

    // Opening the file
    FILE *my_file = fopen("Your Transcript.txt", "w");

    // Checking the has been opened or not
    if(!my_file){
        cout<<"Error opening the file."<<endl;
        return 1;
    }

    // writing heading for the table
    fputs("Transcript\n", my_file);
    fputs("--------------------------------------------------------------\n", my_file);
    fputs("Course                        Credit Hours        Marks\n", my_file);
    fputs("--------------------------------------------------------------\n", my_file);

    // Write data for each course
    for(int i=0; i<numofcourses; i++){
        // converting the course data
        char courseData[150]; 
        sprintf(courseData, "%-30s%-20.2f%.2f\n", course_name[i], credit_hours[i], obtained_marks[i]);
        // Write course data to the file
        fputs(courseData, my_file);
    }

    // writing GPA and grade
    fputs("--------------------------------------------------------------\n", my_file);
    char gpaData[50]; // Adjust size according to your maximum expected length
    sprintf(gpaData, "GPA for the semester: %.2f\n", GPA);
    fputs(gpaData, my_file);
    fputs("Grade: ", my_file);
    fputs(grade.c_str(), my_file);
    fputs("\n", my_file); // Add newline character after the grade

    // Close the file
    fclose(my_file);

    return 0;
}

