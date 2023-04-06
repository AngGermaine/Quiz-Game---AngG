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
void displayRecord(struct record *record, int nRecords);
int addRecord(struct record *record, int nRecords);
int getUniqueTopic(struct record *record, int nRecords, int nUniqueTopicNum);
void editRecord(struct record *record, int nRecords, int nUniqueTopicNum);
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
	int bEndEdit = 0;
	int nUniqueTopicNum;
	int bEditRecordOption;
	int i;

	do 
	{
		system("cls");
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
						displayRecord(aRecords, nRecord);
						printf("MDM = %d", nMDMChoice);
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
	                            
	                            break;
	                        case 2:
	                        	do
	                        	{
	                        		nUniqueTopicNum = 0;
	                        		displayRecord(aRecords, nRecord);
	                        		printf("\nnUniqueTopicNum = %d\n", nUniqueTopicNum);
	                        		for (i = 0; i < nRecord; i++)
	                        		{
	                        			strcpy((aRecords+i)->sUniqueTopics,"");
									}
		                        	nUniqueTopicNum = getUniqueTopic(aRecords, nRecord, nUniqueTopicNum);
		                        	editRecord(aRecords, nRecord, nUniqueTopicNum);
		                        	
			                        do
									{
										printf("Would you still like to [1] edit or [2] go back to manage data menu? ");
										scanf(" %d", &bEditRecordOption);
											
										if (bEditRecordOption == 1)
										{
											nUniqueTopicNum = 0;
											for (i = 0; i < nRecord; i++)
			                        		{
			                        			strcpy((aRecords+i)->sUniqueTopics,"");
											}
											bEndEdit = 0;
										}
										
										else
										{
											bEndEdit = 1;
										}
											
									} while (bEditRecordOption < 1 || bEditRecordOption > 2);
					
	                        		
								} while (bEndEdit == 0);
	                        	
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
			
			do
			{
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
			} while (nMMreturn < 1 || nMMreturn > 2);
			
			
		}
	} while (bIsPass == 0);	
	return bIsPass;
}

void getInput(struct record *record, int nRecords)
{
	int i, j;
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
					strcpy((record+nTopicNum)->sUniqueTopics,"\0");
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
					strcpy((record+nTopicNum)->sUniqueTopics,"\0");
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
	
    if (nRecords >= (MAX_RECORDS-1)) 
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

int getUniqueTopic(struct record *record, int nRecords, int nUniqueTopicNum)
{
    int h, k;
    int bFound;
    
    for (h = 0; h < nRecords; h++)
    {
        // Add an additional check to only add sTopic to sUniqueTopics if nQuestionNum is 1
        if ((record+h)->nQuestionNum == 1)
        {
            // Check if sTopic is already in sUniqueTopics
            bFound = 0;
            for (k = 0; k < nRecords; k++)
            {
                if (strcmp((record+h)->sTopic, (record+k)->sUniqueTopics) == 0)
                {
                    bFound++; 
                }
            }
            
            // Add sTopic to sUniqueTopics if it's not found
            if (bFound == 0)
            {
                strcpy((record+nUniqueTopicNum)->sUniqueTopics, (record+h)->sTopic);
                nUniqueTopicNum++;
            }
        }
    } 
    
    return nUniqueTopicNum;
}


void editRecord(struct record *record, int nRecords, int nUniqueTopicNum)
{
    int h, i, j, k, nEditSelect, nRecordSelect = 0, nFoundQuestion = 0, nRecordIndex = 0, nTopicNum = 0, nQuestionIndex[MAX_RECORDS];
    int bFound = 0, bEnd = 0, bTopicTrue = 1, bQuestionTrue = 1, bSkipQuestion = 1, bSameInput = 0, bDuplicate = 0;
    char sEditInput[MAX_SIZE], ch, ch1;
    
    printf("\n-EDIT RECORD-\n");

    if (nRecords == 0)
    {
    	printf("||| There are no records.\n");
    	bEnd = 1;
	}
	
	while (bEnd == 0)
	{
		printf("nUniqueTopicNum = %d\n", nUniqueTopicNum);
		
		for (h = 0; h < nRecords; h++)
		{
			if (strcmp((record+h)->sUniqueTopics, "\0") != 0 && h != nUniqueTopicNum)
			{
				printf("TOPIC: '%s'\n", (record+h)->sUniqueTopics);
			}		
		}
		
		i = 0;
		
		do //gets the index i based on the amount of nUniqueTopics and assigns that to nRecordSelect so that in the function, it knows what topic you chose
		{
			if (i == nUniqueTopicNum && bTopicTrue == 1)
			{
				i = 0;
			}
			
			if (strcmp((record+i)->sUniqueTopics, "\0") != 0)
			{
			printf("||| Choose TOPIC: '%s' [y/n]? ", (record+i)->sUniqueTopics);
			scanf(" %c", &ch);
			}
				
			if (ch == 'y' || ch == 'Y')
			{
				bTopicTrue = 0;
			}
			else
			{
				i++;
				bTopicTrue = 1;
			}
		} while (i <= nUniqueTopicNum && bTopicTrue == 1);
			
		nRecordSelect = i; 
		
			
		printf("\n~|| Here are the questions under TOPIC '%s'.\n", (record+nRecordSelect)->sUniqueTopics);
		
		for (j = 0; j < nRecords; j++) //index through the records and compare sTopic to chosen UniqueTopic name, if it finds the same on any index of record add it to the nQuestionIndex array. If it isnt add 0 instead of the value of j.
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
			
		do //ask for input if that is the question they want to edit 
		{		
			if (j == nFoundQuestion && bQuestionTrue == 1)
			{
				j = 0;
			}
				
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0 && bQuestionTrue == 1) //if current index's sTopic is same with sUniqueTopics then carry on
			{
				bSkipQuestion = 0;
			}
			
			else //skip current iteration
			{
				bSkipQuestion = 1;
			}
					
			if (bSkipQuestion == 0)
			{
				printf("||| Choose '%d. %s' [y/n]? ", (record+nQuestionIndex[j])->nQuestionNum, (record+nQuestionIndex[j])->sQuestion);
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
				
			else //skip current iteration and increment j so it goes to the next question
			{
				j++;
				bQuestionTrue = 1;
			}
				
		} while (j <= nFoundQuestion && bQuestionTrue == 1);
			
		nRecordIndex = j; 
			    
	    printf("\n-EDITING RECORD #%d-\n", nRecordIndex+1);
		printf("Topic: %s\n", (record+nRecordIndex)->sTopic);
		printf("Question Number: %d\n", (record+nRecordIndex)->nQuestionNum);
		printf("Question: %s\n", (record+nRecordIndex)->sQuestion);
		printf("Choices:\n");
		printf("1. %s\n", (record+nRecordIndex)->sChoicesOne);
		printf("2. %s\n", (record+nRecordIndex)->sChoicesTwo);
		printf("3. %s\n", (record+nRecordIndex)->sChoicesThree);
		printf("Answer: %s\n", (record+nRecordIndex)->sAnswer);
	    printf("\n~|| Choose an option\n");
		printf("[1] Topic\n");
		printf("[2] Question\n");
		printf("[3] Choice 1\n");
		printf("[4] Choice 2\n");
		printf("[5] Choice 3\n");
		printf("[6] Answer\n");
		printf("[7] Exit\n");
		printf("||| Enter your choice: ");
		scanf("%d", &nEditSelect);
			    
		switch(nEditSelect)
		{
		    case 1:
		    	nTopicNum = 0;
				do 
				{
				    fflush(stdin);
				    printf("\n||| Edit topic: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0'; 
				    
				    if (strcmp(sEditInput, (record+nRecordIndex)->sTopic) != 0) 
					{
						
				        strcpy((record+nRecordIndex)->sTopic, sEditInput);
				        
				        for (k = 0; k < nRecords; k++) 
						{
							
							if (strcmp((record+nRecordIndex)->sTopic, (record+k)->sTopic) == 0) 
							{
								nTopicNum++;
							}
						}
								    		            
						(record+nRecordIndex)->nQuestionNum = nTopicNum;

				        
				        bSameInput = 0;
				    } 
					
					else 
					{
				        printf("Please enter a different topic name.\n");
				        bSameInput = 1;
				    }
				} while (strcmp(sEditInput, (record+nRecordIndex)->sTopic) == 0 && bSameInput == 1);	
				
				bEnd = 1;
			   	break;
			case 2:
			   	do 
				{
				    fflush(stdin);
				    printf("||| Edit question: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sQuestion) == 0 || 
				                 strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0;
				    bDuplicate = 0;
				
				    if (bSameInput) 
					{
				        printf("Please enter a different question.\n");
				    } 
					
					else 
					{
				        for (k = 0; k < nRecords; k++) 
						{
				            if (strcmp(sEditInput, (record+k)->sQuestion) == 0 && k != nRecordIndex) 
							{
				                printf("Matches existing record. Please try again.\n");
				                bDuplicate = 1;
				        	}
				    	}
				
				        if (!bDuplicate) 
						{
				            strcpy((record+nRecordIndex)->sQuestion, sEditInput);
				            bFound = 1;
				        }
				    }
				} while (!bFound && (bSameInput || bDuplicate));
						 
				bEnd = 1;		
			   	break;
			case 3:
			   
				
				bEnd = 1;
			   	break;
			case 4:
			   	
			   	
			  	bEnd = 1;
			   	break;
			case 5:
			   	
			   	
			   	bEnd = 1;
			   	break;
			case 6:
			   	do 
				{
				    fflush(stdin);
				    printf("||| Edit answer: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
					
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sQuestion) == 0 || 
				                 strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0;
					
				    if (bSameInput) 
					{
						bFound = 0;
				        printf("Please enter a different answer.\n");
				    } 
					else 
					{
				        strcpy((record+nRecordIndex)->sAnswer, sEditInput);
				        bFound = 1;
				    }
				} while (!bFound && bSameInput);
			  	
			  	bEnd = 1;
			   	break;
			case 7:
				bEnd = 1;
				break;
			default:
			   	printf("||| Invalid choice. Please try again.\n");
				break;
		}
	}
}

void deleteRecord(struct record *record, int nRecords)
{
	
}

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



