#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_ASSIGNMENT 4

typedef struct {
    char FirstName[10];
    char LastName[10];
    int PointOfAssignement[4];
    char EmailAddress[20];
	float Grade;
} Student;

void ReadFile(Student *Student, int *counter, char *ReadFileName) {
    FILE *fp;
    fp = fopen( ReadFileName, "r");
	
    int i = 0;   //counter for student number
    if (fp == NULL) {
        printf("Can't find the file");
    }
    char *buf = (char *) malloc(256);
    char d = ',';
    int j,k;

    // with fgets read each line in the text
    while (fgets(buf, 255, fp) != NULL) { 
        for(j=k=0; buf[j]!='\0'; j++) //remove comma ',' of string
            if(buf[j]!=d)
                buf[k++]=buf[j];
        buf[k]= '\0';
        
		//use  sscanf to read each element of line
        sscanf(buf,"%s %s %d %d %d %d %s",Student[i].FirstName,Student[i].LastName,&Student[i].PointOfAssignement[0]
                ,&Student[i].PointOfAssignement[1],&Student[i].PointOfAssignement[2],&Student[i].PointOfAssignement[3]
                ,Student[i].EmailAddress);
        //Iterate throught the struct
        *counter = i;
        i++;
    }
    fclose(fp);
    free(buf);
}

// match point to grade
float grade(float Points){
    float Grade = 0;
    if (Points >= 0.0 && Points <= 50) Grade = 5.0;
    else if (Points >= 50 && Points <= 55.5) Grade = 4.0;
    else if (Points >= 55.5 && Points <= 60.5) Grade = 3.7;
    else if (Points >= 60.5 && Points <= 65.5) Grade = 3.3;
    else if (Points >= 65.5 && Points <= 70.5) Grade = 3.0;
    else if (Points >= 70.5 && Points <= 75.5) Grade = 2.7;
    else if (Points >= 75.5 && Points <= 81) Grade = 2.3;
    else if (Points >= 81 && Points <= 86) Grade = 2.0;
    else if (Points >= 86 && Points <= 91) Grade = 1.7;
    else if (Points >= 91 && Points <= 96) Grade = 1.3;
    else if (Points >= 96 && Points <= 100) Grade = 1.0;
    return Grade;
}

void WriteFile(Student *Student, int* counter, char* WriteFileName) {
    FILE *fw;
    fw = fopen(WriteFileName, "w");
    if (fw == NULL) {
        printf("Can't find the file");
    }

    for (int k = 0; k <= *counter; ++k) {
    	float Points = 0;
    	for (int j = 0; j < NUMBER_OF_ASSIGNMENT; j++) {
        	Points += Student[k].PointOfAssignement[j]; //sum up all the points
    		}
		//convert point to grade
    	Student[k].Grade = grade(Points);

    	fprintf(fw, "%s %s <%s>: %1.1f\n", Student[k].FirstName, Student[k].LastName, Student[k].EmailAddress, Student[k].Grade);
    }
    fclose(fw);
}

void HighScore(Student *Student, int* counter){
    float max_grade = 5;
    int  ID = 0;

    for (int k = 0; k <= *counter; ++k) {
    	if (Student[k].Grade < max_grade){
       		 max_grade = Student[k].Grade;
        	 ID = k;
    	}
    }
    printf("%s %s <%s>: %1.1f\n", Student[ID].FirstName, Student[ID].LastName, Student[ID].EmailAddress, max_grade);
}

void main(void) {
    //char ptr to the read and write file destination
    char *ReadFileName = "Student_list.txt"; // ++ Just use the name of file, when the code file and text file in the same directory
    char *WriteFileName = "Destination_list.txt";
    //Initialize a counter for the number of Student instaces are present in the Read File
    int counter = 0;
    Student Student[100];
    ReadFile(Student,  &counter, ReadFileName);
    WriteFile(Student, &counter, WriteFileName);
    HighScore(Student, &counter);
}


	
	
