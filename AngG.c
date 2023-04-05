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
    char sQuestion[MAX_QUESTION_LENGTH];
    char sAnswer[MAX_ANSWER_LENGTH];
    char sTopic[MAX_TOPIC_LENGTH];
    char sUniqueTopics[MAX_TOPIC_LENGTH];
    char sChoicesOne[MAX_CHOICE_LENGTH];
    char sChoicesTwo[MAX_CHOICE_LENGTH];
    char sChoicesThree[MAX_CHOICE_LENGTH];
    int nQuestionNum;
}; 

int inputPassword();
void getInput(struct record *record, int nRecords);
//void displayRecord(struct record *record, int nRecords);
int displayUniqueTopics(struct record *record, int nRecords);
int addRecord(struct record *record, int nRecords);
void editRecord(struct record *record, int nRecords);
void deleteRecord(struct record *record, int nRecords);
//void importRecord();
//void exportRecord();

int main() 
{
	int nMMChoice;
	int nMDMChoice;
	int nGMChoice;
	int nPassCheck;
	
	struct record aRecords[MAX_RECORDS];
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
	                            nRecord = addRecord(aRecords, nRecord);
	                            printf("\nNumber of Records: %d\n", nRecord);
	                            //displayRecord(aRecords, nRecord);
	                            break;
	                        case 2:
	                            editRecord(aRecords, nRecord);
	                            break;
	                        case 3:
	                            //nRecord = deleteRecord(aRecords, nRecord);
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
	aString sPassword;
	strcpy(sPassword, "password");
	strcat(sPassword, "");
	
	char aInputPass[MAX_SIZE];
	char ch; //take a string input
	int i = 0; //counter for input
	int bIsPass = 0; //boolean for checking if correct password
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
		
		if (strcmp(sPassword, aInputPass) == 0)
		{
			printf("\n\n||| Welcome, Admin.\n");
			bIsPass = 1;
		}	
		else 
		{
			printf("\n\n||| Wrong password. Please try again.\n");
			bIsPass = 0;
			
			printf("||| Would you like to try again [1] or go back to Main Menu [2]? ");
			scanf("%d", &nMMreturn);
			
			if (nMMreturn == 1)
			{
				i = 0; //for input taking reset
			}
				
			if (nMMreturn == 2)
			{
				bIsPass = 6; //so in main, manage data menu's value is 6 which brings it back to the main menu
			}
		}
	} while (bIsPass == 0);	
	return bIsPass;
}

void getInput(struct record *record, int nRecords)
{
	int i, j, k;
	int nCurrent = nRecords - 1; 
	int bFound = 0;
	int bFoundUniqueTopic = 0;
	int nTopicNum = 1;
	
	if (((record+nCurrent)->sQuestion) != '\0')
	{
		fflush(stdin);
		
		printf("||| Enter question: ");
		fgets(((record+nRecords)->sQuestion), MAX_QUESTION_LENGTH, stdin);
		(record+nRecords)->sQuestion[strlen((record+nRecords)->sQuestion)-1] = '\0'; 
				
		printf("\n||| Enter answer: ");
		fgets(((record+nRecords)->sAnswer), MAX_ANSWER_LENGTH, stdin);
		(record+nRecords)->sAnswer[strlen((record+nRecords)->sAnswer)-1] = '\0'; 
						
		for (i = 0; i < nRecords && bFound == 0; i++)
		{
			if (strcmp((record+nRecords)->sQuestion,(record+i)->sQuestion) == 0 &&
			    strcmp((record+nRecords)->sAnswer,(record+i)->sAnswer) == 0)
			{
				bFound = 1;
			} 
		}
		
		if (bFound != 1)
		{
			printf("\n||| Enter topic: ");
			fgets(((record+nRecords)->sTopic), MAX_TOPIC_LENGTH, stdin);
			(record+nRecords)->sTopic[strlen((record+nRecords)->sTopic)-1] = '\0';  
				
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if (strcmp((record+nRecords)->sTopic, (record+j)->sUniqueTopics) == 0)
				{
					bFoundUniqueTopic = 1;
				}
			}
			
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if((bFoundUniqueTopic == 0) && ((record+j)->sUniqueTopics == '\0'))
				{
					strcpy((record+nTopicNum)->sUniqueTopics, (record+nRecords)->sTopic);
					bFoundUniqueTopic = 1;
				} 
			}
			
			for (j = 0; j < nRecords; j++)
			{
				if (strcmp((record+nRecords)->sTopic, (record+j)->sTopic) == 0)
				{
					nTopicNum++;
				}
			}
							
			(record+nRecords)->nQuestionNum = nTopicNum;

			do
			{	
				printf("\n||| Enter choice 1: ");
				fgets(((record+nRecords)->sChoicesOne), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->sChoicesOne[strlen((record+nRecords)->sChoicesOne)-1] = '\0';  
						
				printf("||| Enter choice 2: ");
				fgets(((record+nRecords)->sChoicesTwo), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->sChoicesTwo[strlen((record+nRecords)->sChoicesTwo)-1] = '\0';  
						
				printf("||| Enter choice 3: ");
				fgets(((record+nRecords)->sChoicesThree), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->sChoicesThree[strlen((record+nRecords)->sChoicesThree)-1] = '\0';  	

			}while((strcmp((record+nRecords)->sAnswer,(record+nRecords)->sChoicesOne) != 0 &&
			 	    strcmp((record+nRecords)->sAnswer,(record+nRecords)->sChoicesTwo) != 0 &&
			        strcmp((record+nRecords)->sAnswer,(record+nRecords)->sChoicesThree) != 0) ||
				   (strcmp((record+nRecords)->sChoicesOne,(record+nRecords)->sChoicesTwo) == 0 ||
				    strcmp((record+nRecords)->sChoicesTwo,(record+nRecords)->sChoicesThree) == 0 ||
				    strcmp((record+nRecords)->sChoicesOne,(record+nRecords)->sChoicesThree) == 0));
		}	
		
	}
	
	else
	{
		for (i = 0; i < nRecords; i++)
		{
			fflush(stdin);
			
			printf("||| Enter question: ");
			fgets(((record+i)->sQuestion), MAX_QUESTION_LENGTH, stdin);
			(record+i)->sQuestion[strlen((record+i)->sQuestion)-1] = '\0'; 
				
			printf("\n||| Enter answer: ");
			fgets(((record+i)->sAnswer), MAX_ANSWER_LENGTH, stdin);
			(record+i)->sAnswer[strlen((record+i)->sAnswer)-1] = '\0';  
			
			printf("\n||| Enter topic: ");
			fgets(((record+i)->sTopic), MAX_TOPIC_LENGTH, stdin);
			(record+i)->sTopic[strlen((record+i)->sTopic)-1] = '\0'; 
			
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if (strcmp((record+i)->sTopic, (record+j)->sUniqueTopics) == 0)
				{
					bFoundUniqueTopic = 1;
				}
			}
			
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if((bFoundUniqueTopic == 0) && ((record+j)->sUniqueTopics == '\0'))
				{
					strcpy((record+nTopicNum)->sUniqueTopics, (record+i)->sTopic);
					bFoundUniqueTopic = 1;
				} 
			}
			
			for (j = 0; j < nRecords; j++)
			{
				if (strcmp((record+i)->sTopic, (record+j)->sTopic) == 0)
				{
					nTopicNum++;
				}
			}
							
			(record+i)->nQuestionNum = nTopicNum;				
			
			do
			{
				printf("\n||| Enter choice 1: ");
				fgets(((record+i)->sChoicesOne), MAX_CHOICE_LENGTH, stdin);
				(record+i)->sChoicesOne[strlen((record+i)->sChoicesOne)-1] = '\0'; 
							
				printf("||| Enter choice 2: ");
				fgets(((record+i)->sChoicesTwo), MAX_CHOICE_LENGTH, stdin);
				(record+i)->sChoicesTwo[strlen((record+i)->sChoicesTwo)-1] = '\0';  
							
				printf("||| Enter choice 3: ");
				fgets(((record+i)->sChoicesThree), MAX_CHOICE_LENGTH, stdin);
				(record+i)->sChoicesThree[strlen((record+i)->sChoicesThree)-1] = '\0';  
					
			}while((strcmp((record+i)->sAnswer,(record+i)->sChoicesOne) != 0 &&
				    strcmp((record+i)->sAnswer,(record+i)->sChoicesTwo) != 0 &&
					strcmp((record+i)->sAnswer,(record+i)->sChoicesThree) != 0) ||
				   (strcmp((record+i)->sChoicesOne,(record+i)->sChoicesTwo) == 0 ||
					strcmp((record+i)->sChoicesTwo,(record+i)->sChoicesThree) == 0 ||
					strcmp((record+i)->sChoicesOne,(record+i)->sChoicesThree) == 0));
					
		}		
	}
	
} 

int addRecord(struct record *record, int nRecords)
{
	int i;
	int bFound = 0;
	
    if (nRecords >= MAX_RECORDS) 
	{
        printf("\n||| The records database is full. Please delete some records to continue.\n");
        return nRecords;
    }

	printf("\n-ADD RECORD-\n");
    getInput(record, nRecords);

    for (i = 0; i < nRecords && bFound == 0; i++)
	{
		if (strcmp((record+nRecords)->sQuestion,(record+i)->sQuestion) == 0 &&
		    strcmp((record+nRecords)->sAnswer,(record+i)->sAnswer) == 0)
		{
			bFound = 1;
			printf("\n||| Record already exists.\n");
			return nRecords;
		} 
	}

    printf("\n||| Record successfully added.\n");
	
    return nRecords + 1;
}

void editRecord(struct record *record, int nRecords)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int nUniqueTopics;
	int nRecordSelect = 0;
	int nFoundQuestion = 0;
	int nQuestionIndex[MAX_RECORDS];
	int n;
    int bTopicTrue = 1;
	int bQuestionTrue = 1; 
	int bSkipQuestion = 1;
    char ch, ch1;
    
    printf("\n-EDIT RECORD-\n");
    nUniqueTopics = displayUniqueTopics(record, nRecords);
    
	do
	{
		if (i == nUniqueTopics && bTopicTrue == 1)
		{
			i = 0;
		}
		printf("i = %d\n", i);

		printf("||| Choose %s?", (record+i)->sUniqueTopics);
		scanf(" %c", &ch);
		
		if (ch == 'y' || ch == 'Y')
		{
			bTopicTrue = 0;
		}
		else
		{
			i++;
			bTopicTrue = 1;
		}
	} while (i <= nUniqueTopics && bTopicTrue == 1);
	
	nRecordSelect = i; 
	
	printf("\nHere are the questions under TOPIC '%s'.\n", (record+nRecordSelect)->sUniqueTopics);
	for (j = 0; j < nRecords; j++)
	{
		if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0)
		{
			printf("%d. %s\n", (record+j)->nQuestionNum, (record+j)->sQuestion);
			nQuestionIndex[nFoundQuestion++] = j;	
		}
		else
		{
			nQuestionIndex[nFoundQuestion++] = 0;
		}
	}
	
	for (j = 0; j < nFoundQuestion; j++)
	{
		printf("%d\n", nFoundQuestion);
		printf("[%d] Question Index %d\n", j, nQuestionIndex[j]);
		printf(" %s\n", (record+j)->sTopic);
	}
	
	do
	{		
		if (j == nFoundQuestion && bQuestionTrue == 1)
		{
			j = 0;
		}
		
		if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0)
		{
			bSkipQuestion = 0;
		}
		
		else
		{
			bSkipQuestion = 1;
		}
			
		if (bSkipQuestion == 0)
		{
			printf("j = %d\n", j);
			printf(" %s\n", (record+j)->sTopic);
			printf("||| Choose '%d. %s'?", (record+nQuestionIndex[j])->nQuestionNum, (record+nQuestionIndex[j])->sQuestion);
			scanf(" %c", &ch1);
			
			if (ch1 == 'y' || ch1 == 'Y')
			{
				bQuestionTrue = 0;
				
			}
			
			else
			{
				j++;
				bQuestionTrue = 1;
			}
		}
		
		else
		{
			printf("j = %d\n", j);
			printf(" %s\n", (record+j)->sTopic);
			j++;
			bQuestionTrue = 1;
		}
		
	} while (j <= nFoundQuestion && bQuestionTrue == 1);
		
}

void deleteRecord(struct record *record, int nRecords)
{
	
}

int displayUniqueTopics(struct record *record, int nRecords)
{
	int i, j;
	int bFound;
	int nTopicNum = 0;
	
	for (i = 0; i < nRecords; i++)
	{
		bFound = 0;
		
		for (j = 0; j < nRecords && bFound == 0; j++)
		{
			if (strcmp((record+i)->sTopic, (record+j)->sUniqueTopics) == 0)
			{
				bFound = 1;
			}
		}
		
		if (bFound == 0)
		{
			strcpy((record+nTopicNum)->sUniqueTopics, (record+i)->sTopic);
			nTopicNum++;
		}
	}
	
	for (i = 0; i < nTopicNum; i++)
	{
		printf("%d. %s\n", i+1, (record+i)->sUniqueTopics);
	}
	
	return nTopicNum;
}

/*
void displayRecord(struct record *record, int nRecords) 
{	
	int i;
	for (i = 0; i < nRecords; i++)
	{
    printf("\nTopic: %s\n", (record+i)->sTopic);
    printf("Question Number: %d\n", (record+i)->nQuestionNum);
    printf("Question: %s\n", (record+i)->sQuestion);
   
    printf("Choices:\n");
    printf("1. %s\n", (record+i)->sChoicesOne);
    printf("2. %s\n", (record+i)->sChoicesTwo);
    printf("3. %s\n", (record+i)->sChoicesThree);
    
    printf("Answer: %s\n", (record+i)->sAnswer);
    
	}
}
*/


