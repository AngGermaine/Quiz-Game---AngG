#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_SIZE 200
#define MAX_RECORDS 25
#define MAX_QUESTION_LENGTH 150
#define MAX_ANSWER_LENGTH 30
#define MAX_TOPIC_LENGTH 20
#define MAX_CHOICE_LENGTH 30

typedef char aString[MAX_SIZE];

struct record {
    char aQuestion[MAX_QUESTION_LENGTH];
    char aAnswer[MAX_ANSWER_LENGTH];
    char aTopic[MAX_TOPIC_LENGTH];
    char aChoicesOne[MAX_CHOICE_LENGTH];
    char aChoicesTwo[MAX_CHOICE_LENGTH];
    char aChoicesThree[MAX_CHOICE_LENGTH];
    int nQuestionNumber;
}; 

int inputPassword();
void getInput(struct record *record, int nRecords);
int addRecord(struct record *record, int nRecords);
//void editRecord();
//void deleteRecord();
//void importRecord();
//void exportRecord();

int main() 
{
	int nMMChoice;
	int nMDMChoice;
	int nGMChoice;
	int nPassCheck;
	
	struct record records[MAX_RECORDS];
	int nRecord = 0;

	do 
	{
    	printf("\n-MAIN MENU-\n");
    	printf("[1] Manage Data\n");
    	printf("[2] Play\n");
    	printf("[3] Exit\n");

        printf("||| Enter your choice: ");
        scanf("%d", &nMMChoice);

        switch (nMMChoice) 
		{
            case 1:
            	//Ask for password first
            	nPassCheck = inputPassword();
            	if (nPassCheck == 6)
            	{
            		printf("\n||| Going back to Main Menu...\n");
            		nMDMChoice = nPassCheck; //giving nMDMChoice value of 6 which returns it back to main menu
				}
            	// Manage Data menu
            	else
            	{
            		do 
					{
	                    printf("\n-MANAGE DATA-\n");
	                    printf("[1] Add record\n");
	                    printf("[2] Edit record\n");
	                    printf("[3] Delete record\n");
	                    printf("[4] Import record\n");
	                    printf("[5] Export record\n");
	                    printf("[6] Back to Main Menu\n");
	
	                    printf("||| Enter your choice: ");
	                    scanf("%d", &nMDMChoice);
	
	                    switch (nMDMChoice) 
						{
	                        case 1:
	                            nRecord = addRecord(records, nRecord);
	                            printf("\n%d", nRecord);
	                            break;
	                        case 2:
	                            //editRecord();
	                            break;
	                        case 3:
	                            //deleteRecord();
	                            break;
	                        case 4:
	                            //importRecord();
	                            break;
	                        case 5:
	                            //exportRecord();
	                            break;
	                        case 6:
	                            printf("\n||| Going back to Main Menu...\n");
	                            break;
	                        default:
	                            printf("||| Invalid choice. Please try again.\n");
	                            break;
	                    }
	                } while (nMDMChoice != 6);
				}
            	
                break;
                
            case 2:
                // Play Game menu
                do 
				{
                    printf("\nQUIZ GAME\n");
                    printf("[1] \n");
                    printf("[2] \n");
                    printf("[3] Back to Main Menu\n");

                    printf("||| Enter your choice: ");
                    scanf("%d", &nGMChoice);

                    switch (nGMChoice) 
					{
                        case 1:
                            
                            break;
                        case 2:
                            
                            break;
                        case 3:
                            printf("\n||| Going back to Main Menu...\n");
                            break;
                        default:
                            printf("||| Invalid choice. Please try again.\n");
                            break;
                    }
                } while (nGMChoice != 3);
                break;
            case 3:
                printf("\n||| Exiting program...\n");
                break;
            default:
                printf("||| Invalid choice. Please try again.\n");
                break;
        }
    } while (nMMChoice != 3);

    return 0;
}

int inputPassword()
{
	aString aPassword;
	strcpy(aPassword, "password");
	strcat(aPassword, "");
	
	char aInputPass[MAX_SIZE];
	char ch; //take a string input
	int i = 0; //counter for input
	int isPass = 0; //boolean for checking if correct password
	int nMMreturn; //taking int input for options
	
	
	printf("\n-LOGIN-");
	do
	{
		printf("\n||| Hello, please input the password: ");
		
		do //ask for string input
		{
			ch = getch();
			if (ch != 13)
			{
				printf("*");
				aInputPass[i] = ch;
				i++;
				aInputPass[i] = '\0';
			}
		} while (i < MAX_SIZE && ch != 13);
		
		if (strcmp(aPassword, aInputPass) == 0)
		{
			printf("\n\n||| Welcome, Admin.\n");
			isPass = 1;
		}	
		else 
		{
			printf("\n\n||| Wrong password. Please try again.\n");
			isPass = 0;
			
			printf("||| Would you like to try again [1] or go back to Main Menu [2]? ");
			scanf("%d", &nMMreturn);
			
			if (nMMreturn == 1)
			{
				i = 0; //for input taking reset
			}
				
			if (nMMreturn == 2)
			{
				isPass = 6; //so in main, manage data menu's value is 6 which brings it back to the main menu
			}
		}
	} while (isPass == 0);	
	return isPass;
}

void getInput(struct record *record, int nRecords)
{
	int i, j;
	int current = nRecords - 1; 
	int found = 0;
	
	if (((record+current)->aQuestion) != '\0')
	{
		fflush(stdin);
		
		printf("\nEnter question: ");
		fgets(((record+nRecords)->aQuestion), MAX_QUESTION_LENGTH, stdin);
		(record+nRecords)->aQuestion[strlen((record+nRecords)->aQuestion)-1] = '\0'; 
				
		printf("\nEnter answer: ");
		fgets(((record+nRecords)->aAnswer), MAX_ANSWER_LENGTH, stdin);
		(record+nRecords)->aAnswer[strlen((record+nRecords)->aAnswer)-1] = '\0'; 
						
		for (j = 0; j < nRecords && found == 0; j++)
		{
			if (strcmp((record+nRecords)->aQuestion,(record+j)->aQuestion) == 0 &&
			    strcmp((record+nRecords)->aAnswer,(record+j)->aAnswer) == 0)
			{
				found = 1;
			} 
		}
		
		if (found != 1)
		{
			do
			{
				printf("\nEnter topic: ");
				fgets(((record+nRecords)->aTopic), MAX_TOPIC_LENGTH, stdin);
				(record+nRecords)->aTopic[strlen((record+nRecords)->aTopic)-1] = '\0';  
					
				printf("Enter choice 1: ");
				fgets(((record+nRecords)->aChoicesOne), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->aChoicesOne[strlen((record+nRecords)->aChoicesOne)-1] = '\0';  
						
				printf("Enter choice 2: ");
				fgets(((record+nRecords)->aChoicesTwo), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->aChoicesTwo[strlen((record+nRecords)->aChoicesTwo)-1] = '\0';  
						
				printf("Enter choice 3: ");
				fgets(((record+nRecords)->aChoicesThree), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->aChoicesThree[strlen((record+nRecords)->aChoicesThree)-1] = '\0';  	

			}while((strcmp((record+nRecords)->aAnswer,(record+nRecords)->aChoicesOne) != 0 &&
			 	    strcmp((record+nRecords)->aAnswer,(record+nRecords)->aChoicesTwo) != 0 &&
			        strcmp((record+nRecords)->aAnswer,(record+nRecords)->aChoicesThree) != 0) ||
				   (strcmp((record+nRecords)->aChoicesOne,(record+nRecords)->aChoicesTwo) == 0 ||
				    strcmp((record+nRecords)->aChoicesTwo,(record+nRecords)->aChoicesThree) == 0 ||
				    strcmp((record+nRecords)->aChoicesOne,(record+nRecords)->aChoicesThree) == 0));
		}	
		
	}
	
	else
	{
		for (i = 0; i < nRecords; i++)
		{
			fflush(stdin);
			
			printf("\nEnter question: ");
			fgets(((record+i)->aQuestion), MAX_QUESTION_LENGTH, stdin);
			(record+i)->aQuestion[strlen((record+i)->aQuestion)-1] = '\0'; 
				
			printf("\nEnter answer: ");
			fgets(((record+i)->aAnswer), MAX_ANSWER_LENGTH, stdin);
			(record+i)->aAnswer[strlen((record+i)->aAnswer)-1] = '\0';  
							
			for (j = 0; j < nRecords && found == 0; j++)
			{
				if (strcmp((record+i)->aQuestion,(record+j)->aQuestion) == 0 &&
				    strcmp((record+i)->aAnswer,(record+j)->aAnswer) == 0)
				{
					found = 1;
				}
			} 
			
			if (found != 1)
			{
				do
				{
					printf("\nEnter topic: ");
					fgets(((record+i)->aTopic), MAX_TOPIC_LENGTH, stdin);
					(record+i)->aTopic[strlen((record+i)->aTopic)-1] = '\0'; 
						
					printf("Enter choice 1: ");
					fgets(((record+i)->aChoicesOne), MAX_CHOICE_LENGTH, stdin);
					(record+i)->aChoicesOne[strlen((record+i)->aChoicesOne)-1] = '\0'; 
							
					printf("Enter choice 2: ");
					fgets(((record+i)->aChoicesTwo), MAX_CHOICE_LENGTH, stdin);
					(record+i)->aChoicesTwo[strlen((record+i)->aChoicesTwo)-1] = '\0';  
							
					printf("Enter choice 3: ");
					fgets(((record+i)->aChoicesThree), MAX_CHOICE_LENGTH, stdin);
					(record+i)->aChoicesThree[strlen((record+i)->aChoicesThree)-1] = '\0';  	
				}while((strcmp((record+i)->aAnswer,(record+i)->aChoicesOne) != 0 &&
					    strcmp((record+i)->aAnswer,(record+i)->aChoicesTwo) != 0 &&
					    strcmp((record+i)->aAnswer,(record+i)->aChoicesThree) != 0) ||
					   (strcmp((record+i)->aChoicesOne,(record+i)->aChoicesTwo) == 0 ||
					    strcmp((record+i)->aChoicesTwo,(record+i)->aChoicesThree) == 0 ||
					    strcmp((record+i)->aChoicesOne,(record+i)->aChoicesThree) == 0));
			}	
				 
		}		
	}
	
} 


int addRecord(struct record *record, int nRecords)
{
	int i, j;
	int found = 0;
    if (nRecords >= MAX_RECORDS) {
        printf("||| The records database is full. Please delete some records to continue.\n");
        return nRecords;
    }

    getInput(record, nRecords);

    for (i = 0; i < nRecords; i++) 
	{
        for (j = 0; j < nRecords && found == 0; j++)
			{
				if (strcmp((record+i)->aQuestion,(record+j)->aQuestion) == 0 &&
				    strcmp((record+i)->aAnswer,(record+j)->aAnswer) == 0)
				{
					found = 1;
					printf("\n||| Record already exists.\n");
					return nRecords;
				}
			}
    }

    printf("\n||| Record successfully added.\n");

    return nRecords + 1;
}


/*
void displayRecord(struct record record[], int nRecord) 
{	
	int i;
	for (i = 0; i < nRecord; i++)
	{
    printf("Topic: %s\n", (record+i)->aTopic);
    printf("Question Number: %d\n", (record+i)->nQuestionNumber);
    printf("Question: %s\n", (record+i)->aQuestion);
   
    printf("Choices:\n");
    printf("1. %s\n", (record+i)->aChoices[0]);
    printf("2. %s\n", (record+i)->aChoices[1]);
    printf("3. %s\n", (record+i)->aChoices[2]);
    
    printf("Answer: %s\n", (record+j)->aAnswer);
    
	}
}
*/


