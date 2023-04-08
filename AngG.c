#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_SIZE 200
#define MAX_RECORDS 30
#define MAX_QUESTION_LENGTH 150
#define MAX_ANSWER_LENGTH 30
#define MAX_TOPIC_LENGTH 20
#define MAX_CHOICE_LENGTH 30

typedef char string30[30];

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

struct players {
	char sName[MAX_SIZE];
	int nGameScore;
};

int inputPassword();
void getInput(struct record *record, int nRecords);
void displayRecord(struct record *record, int nRecords);
int addRecord(struct record *record, int nRecords);
int getUniqueTopic(struct record *record, int nRecords, int nUniqueTopicNum);
void updateQuestionNumber(struct record *record, int nRecords);
void editRecord(struct record *record, int nRecords, int nUniqueTopicNum);
int deleteRecord(struct record *record, int nRecords, int nUniqueTopicNum);
int stringToInt(char *str);
int importRecord(struct record *record, int nRecords);
char* exportRecord(struct record *record, int nRecords);
int saveRecord(struct record *record, int nRecords, string30 sFilename);

int main() 
{
	int i;
	int nMMChoice, nMDMChoice, nGMChoice, nPassCheck, nUniqueTopicNum, nRecord = 0;
	int bEditRecordOption, bEndEdit = 0, bSaveRecord = 1;
	struct record aRecords[MAX_RECORDS];
	struct players aPlayers[MAX_RECORDS];
	string30 sFileName;

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
						system("cls");
						displayRecord(aRecords, nRecord);
	                    printf("\n-MANAGE DATA-\n");
	                    printf("Number of Records: %d\n", nRecord);
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
	                            printf("\n");
	                            system("pause");
	                            break;
	                        case 2:
	                        	do
	                        	{
	                        		system("cls");
	                        		nUniqueTopicNum = 0;
	                        		for (i = 0; i < nRecord; i++)
	                        		{
	                        			strcpy((aRecords+i)->sUniqueTopics,"");
									}
		                        	nUniqueTopicNum = getUniqueTopic(aRecords, nRecord, nUniqueTopicNum);
		                        	editRecord(aRecords, nRecord, nUniqueTopicNum);
			                        do
									{
										printf("\n||| Would you still like to [1] Edit other records or [2] Return to Manage Data Menu? ");
										scanf(" %d", &bEditRecordOption);
										system("cls");
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
	                        	do
	                        	{
	                        		system("cls");
	                        		nUniqueTopicNum = 0;
	                        		for (i = 0; i < nRecord; i++)
	                        		{
	                        			strcpy((aRecords+i)->sUniqueTopics,"");
									}
		                        	nUniqueTopicNum = getUniqueTopic(aRecords, nRecord, nUniqueTopicNum);
		                        	nRecord = deleteRecord(aRecords, nRecord, nUniqueTopicNum);
		                        	
			                        do
									{
										printf("\n||| Would you still like to [1] Delete other records or [2] Return to Manage Data Menu? ");
										scanf(" %d", &bEditRecordOption);
										system("cls");
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
	                        case 4:
	                            nRecord = importRecord(aRecords, nRecord);
	                            updateQuestionNumber(aRecords, nRecord);
	                            printf("\n");
	                            system("pause");
	                            break;
	                        case 5:
	                            strcpy(sFileName, exportRecord(aRecords, nRecord));
	                            break;
	                        case 6:
	                        	if (strcmp(sFileName, "") == 0)
	                        	{
	                        		for (i = 0; i < nRecord; i++)
			                        	{
			                        		strcpy((aRecords+i)->sTopic, "");
											(aRecords+i)->nQuestionNum = 0;
											strcpy((aRecords+i)->sQuestion, "");
											strcpy((aRecords+i)->sChoicesOne, "");
											strcpy((aRecords+i)->sChoicesTwo, "");
											strcpy((aRecords+i)->sChoicesThree, "");
											strcpy((aRecords+i)->sAnswer, "");	
										}
										nRecord = 0;	
								}
								
								else
								{
									nRecord = saveRecord(aRecords, nRecord, sFileName);
									bSaveRecord = 1;
								}
	                        	
								printf("\n||| Deleting unsaved records. (Tip: Save with export.)");
	                            printf("\n||| Going back to Main Menu...\n\n");
	                            system("pause");
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
					system("cls");
					displayRecord(aRecords, nRecord);
                	printf("Number of Records: %d\n", nRecord);
                    printf("\nQUIZ GAME\n");
                    printf("[1] Play\n");
                    printf("[2] View Scores\n");
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
                            for (i = 0; i < nRecord; i++)
			                {
			                    strcpy((aRecords+i)->sTopic, "");
								(aRecords+i)->nQuestionNum = 0;
								strcpy((aRecords+i)->sQuestion, "");
								strcpy((aRecords+i)->sChoicesOne, "");
								strcpy((aRecords+i)->sChoicesTwo, "");
								strcpy((aRecords+i)->sChoicesThree, "");
								strcpy((aRecords+i)->sAnswer, "");	
							}
							nRecord = 0;
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
	string30 sPassword;
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
			bIsPass = 1;
		}	
		else 
		{
			printf("\n||| Wrong password.\n");
			bIsPass = 0;
			
			do
			{
				printf("\n||| Would you like to try again [1] or go back to Main Menu [2]? ");
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
	int nTopicNum = 1, nCurrent = nRecords - 1; 
	int bFound = 0, bFoundUniqueTopic = 0;
	
	if (((record+nCurrent)->sQuestion) != '\0')
	{
		fflush(stdin);
		
		printf("||| Enter question: ");
		fgets(((record+nRecords)->sQuestion), MAX_QUESTION_LENGTH, stdin);
		(record+nRecords)->sQuestion[strlen((record+nRecords)->sQuestion)-1] = '\0'; 
				
		printf("||| Enter answer: ");
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
			printf("||| Enter topic: ");
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

void updateQuestionNumber(struct record *record, int nRecords)
{
    int i, j, nTopicNum;
    
    for (i = 0; i < nRecords; i++)
    {
        (record+i)->nQuestionNum = 0;
    }
    
    for (i = 0; i < nRecords; i++) 
    {
        if ((record+i)->nQuestionNum == 0) // Only update question number if not already assigned
        {
            nTopicNum = 1;
            for (j = i+1; j < nRecords; j++) 
            {
                if (strcmp((record+i)->sTopic, (record+j)->sTopic) == 0) 
                {
                    (record+j)->nQuestionNum = nTopicNum;
                    nTopicNum++;
                }
            }
            (record+i)->nQuestionNum = nTopicNum;
        }
    }
}

void editRecord(struct record *record, int nRecords, int nUniqueTopicNum)
{
    int h, i, j, k, nEditSelect, nRecordSelect = 0, nFoundQuestion = 0, nRecordIndex = 0, nQuestionIndex[MAX_RECORDS];
    int bFound = 0, bEnd = 0, bTopicTrue = 1, bQuestionTrue = 1, bSkipQuestion = 1, bSameInput = 0, bDuplicate = 0, bEditChoice = 0;
    char sEditInput[MAX_SIZE], ch, ch1, cAnswer;
    
    printf("\n-EDIT RECORD-\n");

    if (nRecords == 0)
    {
    	printf("||| There are no records.\n");
    	bEnd = 1;
	}
	
	while (bEnd == 0)
	{
		printf("~|| Here are the unique topics.\n");
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
		
			
		printf("\n~|| Here are the questions under TOPIC: '%s'.\n", (record+nRecordSelect)->sUniqueTopics);
		
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
		system("cls");	    
	    printf("\n-EDITING RECORD-\n");
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
		printf("||| Enter an option: ");
		scanf("%d", &nEditSelect);
			    
		switch(nEditSelect)
		{
		    case 1:
				do 
				{
				    fflush(stdin);
				    printf("\n||| Edit topic: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0'; 
				    
				    if (strcmp(sEditInput, (record+nRecordIndex)->sTopic) != 0) 
					{
						
				        strcpy((record+nRecordIndex)->sTopic, sEditInput);
				        updateQuestionNumber(record, nRecords);
				        bSameInput = 0;
				    } 
					
					else 
					{
				        printf("||| Please enter a different topic name.\n");
				        bSameInput = 1;
				    }
				} while (strcmp(sEditInput, (record+nRecordIndex)->sTopic) == 0 && bSameInput == 1);	
				printf("||| Edit successful.\n");
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
				        printf("||| Please enter a different question.\n");
				    } 
					
					else 
					{
				        for (k = 0; k < nRecords; k++) 
						{
				            if (strcmp(sEditInput, (record+k)->sQuestion) == 0 && k != nRecordIndex) 
							{
				                printf("||| Matches existing record. Please try again.\n");
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
				printf("||| Edit successful.\n");		 
				bEnd = 1;		
			   	break;
			case 3:
				do 
				{
				    fflush(stdin);
				    printf("||| Edit choice one: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sChoicesOne) == 0;
				    bDuplicate = 0;
				
				    if ((strcmp(sEditInput, (record+nRecordIndex)->sChoicesTwo) == 0 || 
				            strcmp(sEditInput, (record+nRecordIndex)->sChoicesThree) == 0) &&
							strcmp(sEditInput, (record+nRecordIndex)->sAnswer) != 0 &&
							!bEditChoice) 
				    {
				        printf("||| Matches existing choice. Please try again.\n");
				        bDuplicate = 1;
				    }
				    else 
				    {
				        if (strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0) 
				        {
				            bEditChoice = 0;
				            do
				            {
				                printf("||| Warning: The choice is the current record's answer.\n");
				                printf("||| Do you still want to edit [y/n]? ");
				                scanf(" %c", &cAnswer);
				
				                if (cAnswer == 'y' || cAnswer == 'Y')
				                {
				                    bEditChoice = 1;
				                    bFound = 1;
				                }
				                else if (cAnswer == 'n' || cAnswer == 'N')
				                {
				                    bEditChoice = 0;
				                    bFound = 1;
				                }
				                else
				                {
				                    printf("||| Invalid input. Please try again.\n");
				                }
				            } while (!bFound);
				        }
				            
				        else 
				        {
				            bEditChoice = 1;
				            bFound = 1;
				        }
				    }
				    
				} while (!bFound && bDuplicate && !bEditChoice); 
				
				if (bEditChoice)
				{
				    strcpy((record+nRecordIndex)->sChoicesOne, sEditInput);
				}
				if (bEditChoice && (cAnswer == 'y' || cAnswer == 'Y'))
				{
					printf("||| Warning: You have saved the current record's answer. I suggest you edit again.\n");
				}
				
				if (bSameInput)
				{
				    	printf("||| Edit unsuccessful, nothing was changed.\n");
				    	bEnd = 1;
				}	
				else
				{
					printf("||| Edit successful.\n");
					bEnd = 1;	
				}
			   	break;
			case 4:
			   	do 
				{
				    fflush(stdin);
				    printf("||| Edit choice two: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sChoicesTwo) == 0;
				    bDuplicate = 0;
				    
				    if ((strcmp(sEditInput, (record+nRecordIndex)->sChoicesOne) == 0 || 
				         strcmp(sEditInput, (record+nRecordIndex)->sChoicesThree) == 0) &&
						 strcmp(sEditInput, (record+nRecordIndex)->sAnswer) != 0 &&
						 !bEditChoice) 
				    {
				        printf("||| Matches existing choice. Please try again.\n");
				        bDuplicate = 1;
				    }
				    else 
				    {
				        if (strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0) 
				        {
				            bEditChoice = 0;
				            do
				            {
				                printf("||| Warning: The choice is the current record's answer.\n");
				                printf("||| Do you still want to edit [y/n]? ");
				                scanf(" %c", &cAnswer);
				
				                if (cAnswer == 'y' || cAnswer == 'Y')
				                {
				                    bEditChoice = 1;
				                    bFound = 1;
				                }
				                else if (cAnswer == 'n' || cAnswer == 'N')
				                {
				                    bEditChoice = 0;
				                    bFound = 1;
				                }
				                else
				                {
				                    printf("||| Invalid input. Please try again.\n");
				                }
				            } while (!bFound);
				        }
				        else 
				        {
				            bEditChoice = 1;
				            bFound = 1;
				        }
				    }
				    
				} while (!bFound && bDuplicate && !bEditChoice); 
				
				if (bEditChoice)
				{
				    strcpy((record+nRecordIndex)->sChoicesTwo, sEditInput);
				}
			   	if (bEditChoice && (cAnswer == 'y' || cAnswer == 'Y'))
				{
					printf("||| Warning: You have saved the current record's answer. I suggest you edit again.\n");
				}
				
				if (bSameInput)
				{
				    	printf("||| Edit unsuccessful, nothing was changed.\n");
				    	bEnd = 1;
				}	
				else
				{
					printf("||| Edit successful.\n");
					bEnd = 1;	
				}
				
			   	break;
			case 5:
				do 
				{
				    fflush(stdin);
				    printf("||| Edit choice three: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sChoicesThree) == 0;
				    bDuplicate = 0;
				
				    if ((strcmp(sEditInput, (record+nRecordIndex)->sChoicesOne) == 0 || 
				         strcmp(sEditInput, (record+nRecordIndex)->sChoicesTwo) == 0) &&
					     strcmp(sEditInput, (record+nRecordIndex)->sAnswer) != 0 &&
						 !bEditChoice) 
				    {
				        printf("||| Matches existing choice. Please try again.\n");
				        bDuplicate = 1;
				    }
				    else 
				    {
				        if (strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0) 
				        {
				            bEditChoice = 0;
				            do
				            {
				                printf("||| Warning: The choice is the current record's answer.\n");
				                printf("||| Do you still want to edit [y/n]? ");
				                scanf(" %c", &cAnswer);
				
				                if (cAnswer == 'y' || cAnswer == 'Y')
				                {
				                    bEditChoice = 1;
				                    bFound = 1;
				                }
				                else if (cAnswer == 'n' || cAnswer == 'N')
				                {
				                    bEditChoice = 0;
				                    bFound = 1;
				                }
				                else
				                {
				                        printf("||| Invalid input. Please try again.\n");
				                    }
				            } while (!bFound);
				        }
				        else 
				        {
				                bEditChoice = 1;
				                bFound = 1;
				        }
				    }
				    
				} while (!bFound && bDuplicate && !bEditChoice); 
				
				if (bEditChoice)
				{
				    strcpy((record+nRecordIndex)->sChoicesThree, sEditInput);
				}
			   	if (bEditChoice && (cAnswer == 'y' || cAnswer == 'Y'))
				{
					printf("||| Warning: You have saved the current record's answer. I suggest you edit again.\n");
				}
				
				if (bSameInput)
				{
				    	printf("||| Edit unsuccessful, nothing was changed.\n");
				    	bEnd = 1;
				}	
				else
				{
					printf("||| Edit successful.\n");
					bEnd = 1;	
				}
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
				        printf("||| Please enter a different answer.\n");
				    } 
				    
					else 
					{
				        strcpy((record+nRecordIndex)->sAnswer, sEditInput);
				        bFound = 1;
				    }
				    
				} while (!bFound && bSameInput);
				printf("||| Edit successful.\n");
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

int deleteRecord(struct record *record, int nRecords, int nUniqueTopicNum)
{
	int h, i, j, k, nRecordSelect = 0, nFoundQuestion = 0, nRecordIndex = 0, nQuestionIndex[MAX_RECORDS];
    int bEnd = 0, bTopicTrue = 1, bQuestionTrue = 1, bSkipQuestion = 1, bDeleteRecord = 0;
    char ch, ch1, cDelete;
    
    printf("\n-DELETE RECORD-\n");

    if (nRecords == 0)
    {
    	printf("||| There are no records.\n");
    	bEnd = 1;
	}
	
	while (bEnd == 0)
	{
		printf("~|| Here are the unique topics.\n");
		for (h = 0; h < nRecords; h++)
		{
			if (strcmp((record+h)->sUniqueTopics, "\0") != 0)
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
		
			
		printf("\n~|| Here are the questions under TOPIC: '%s'.\n", (record+nRecordSelect)->sUniqueTopics);
		
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
				printf("||| Delete '%d. %s' [y/n]? ", (record+nQuestionIndex[j])->nQuestionNum, (record+nQuestionIndex[j])->sQuestion);
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
		k = 0;

		do
		{
			printf("||| Are you sure you want to delete '%d. %s' [y/n]? ", (record+nQuestionIndex[nRecordIndex])->nQuestionNum, (record+nQuestionIndex[nRecordIndex])->sQuestion);
			scanf(" %c", &cDelete);
			if (cDelete == 'y' || cDelete == 'Y')
			{
				for (k = nRecordIndex; k < nRecords; k++)
				{
					strcpy((record+k)->sTopic,(record+(k+1))->sTopic);
					(record+k)->nQuestionNum = (record+(k+1))->nQuestionNum;
					strcpy((record+k)->sQuestion,(record+(k+1))->sQuestion);
					strcpy((record+k)->sChoicesOne,(record+(k+1))->sChoicesOne);
					strcpy((record+k)->sChoicesTwo,(record+(k+1))->sChoicesTwo);
					strcpy((record+k)->sChoicesThree,(record+(k+1))->sChoicesThree);
					strcpy((record+k)->sAnswer,(record+(k+1))->sAnswer);
				}
				
				strcpy((record+nRecords-1)->sTopic, "");
				(record+nRecords-1)->nQuestionNum = 0;
				strcpy((record+nRecords-1)->sQuestion, "");
				strcpy((record+nRecords-1)->sChoicesOne, "");
				strcpy((record+nRecords-1)->sChoicesTwo, "");
				strcpy((record+nRecords-1)->sChoicesThree, "");
				strcpy((record+nRecords-1)->sAnswer, "");	
		
				updateQuestionNumber(record, nRecords);
				
				bDeleteRecord = 1;
				nRecords--;
				bEnd = 1;
			}
			else if (cDelete == 'n' || cDelete == 'N')
			{
				printf("||| Cancelling deletion...\n");
				bEnd = 1;
			}
			
			else
			{
				printf("||| Invalid choice. Please try again.\n");
				bEnd = 0;
			}
			
		} while (!bDeleteRecord && !bEnd) ;
	}
	
	return nRecords;
}

int stringToInt(char *str)
{
    int nResult = 0;
    int i = 0;

    /* Convert string to integer by comparing ascii values and subtracting them with 0. 
		Assigning the result to nResult. The i is acts as the counter for which element it is at in the string array.
    */
    while (str[i] != '\0') {
        nResult = nResult * 10 + str[i] - '0';
        i++;
    }

    return nResult;
}

int importRecord(struct record *record, int nRecords)
{
	string30 sFileName;
	int i, j, nCurrentIndex = nRecords;
	int bFoundDuplicate = 0;
	char sReadText[150];
	FILE *fp;
	printf("\n-IMPORT RECORD-\n");
	
	do
	{
		fflush(stdin);
		printf("||| Input filename: ");
		fgets(sFileName, 30, stdin);
		sFileName[strlen(sFileName)-1] = '\0';
		
		fp = fopen(sFileName, "r");
		if (fp == NULL)
		{
			printf("||| File not found. Please try again.\n\n");
		}
	} while (fp == NULL);
	
	i = 0;
	
	while (fgets(sReadText, sizeof(sReadText), fp) != NULL && nCurrentIndex < MAX_RECORDS) 
	{
	    int nLength = strlen(sReadText);
			
	    if (nLength > 0 && sReadText[nLength-1] == '\n') 
		{
	        sReadText[nLength-1] = '\0';
	    }
			
	    switch(i) 
		{
	        case 0:
	            strcpy((record+nCurrentIndex)->sTopic, sReadText);
	            break;
	        case 1:
	            (record+nCurrentIndex)->nQuestionNum = stringToInt(sReadText);
	            break;
	        case 2:
	            strcpy((record+nCurrentIndex)->sQuestion, sReadText);
	            break;
	        case 3:
	            strcpy((record+nCurrentIndex)->sChoicesOne, sReadText);
	            break;
	        case 4:
	            strcpy((record+nCurrentIndex)->sChoicesTwo, sReadText);
	            break;
	        case 5:
	            strcpy((record+nCurrentIndex)->sChoicesThree, sReadText);
	            break;
	        case 6:
	            strcpy((record+nCurrentIndex)->sAnswer, sReadText);
	            break;
	        case 7:
	        	bFoundDuplicate = 0;
	        	for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	        	{
	        		if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
					    strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
					{
						bFoundDuplicate = 1;
					}
				}
				if (!bFoundDuplicate)
				{
					nCurrentIndex++;	
				}
	        	break;
	    }
			
	    i++;
			
	    if (i == 8) 
		{
	        i = 0;
	    }
	}
	/*
	//Conditions these cover, if it is at the end of the file so ignores newline, if there is only one record. 
	The previous block of code at case 7 does have the same purpose, but it does not cover if there is only one record.
	*/
	if (i == 7 && nCurrentIndex < MAX_RECORDS && feof(fp)) 
	{
	    bFoundDuplicate = 0;
	    for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	    {
	        if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
				strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
			{
				bFoundDuplicate = 1;
			}
		}
		if (!bFoundDuplicate)
		{
			nCurrentIndex++;	
		}
	}
		
	if (nCurrentIndex == nRecords)
	{
		printf("||| No records imported.\n");
	}
	else
	{
		printf("||| %d records have been imported.\n", nCurrentIndex - nRecords);
		nRecords = nCurrentIndex;
	}
	
	fclose(fp);
	return nRecords;
}

char *exportRecord(struct record *record, int nRecords)
{
	char *sFileName = (char *)malloc(30 * sizeof(char)); 
	char *sSavedFileName = (char *)malloc(30 * sizeof(char));
	int i;
	FILE *fp;
	printf("\n-EXPORT RECORD-\n");
	
	if (nRecords == 0)
	{
		printf("||| There are no records.\n");
		printf("||| Returning to Manage Data Menu...\n\n");
		strcpy(sSavedFileName, "");
		system("pause");
	}
	
	else
	{
		do
		{
			fflush(stdin);
			printf("||| Input filename: ");
			fgets(sFileName, 30, stdin);
			sFileName[strlen(sFileName)-1] = '\0';
			strcpy(sSavedFileName, sFileName);
			fp = fopen(sFileName, "w");
			if (fp == NULL)
			{
				printf("||| File not found. Please try again.\n\n");
				strcpy(sSavedFileName, "");
			}
		} while (fp == NULL);	
		
		for (i = 0; i < nRecords; i++)
		{
			fprintf(fp, "%s\n", (record+i)->sTopic);
			fprintf(fp, "%d\n", (record+i)->nQuestionNum);
			fprintf(fp, "%s\n", (record+i)->sQuestion);
			fprintf(fp, "%s\n", (record+i)->sChoicesOne);
			fprintf(fp, "%s\n", (record+i)->sChoicesTwo);
			fprintf(fp, "%s\n", (record+i)->sChoicesThree);
			fprintf(fp, "%s\n\n", (record+i)->sAnswer);
		}
		fclose(fp);
		printf("||| Records have been exported to %s.\n\n", sFileName);
		system("pause");
		
	}
	free(sFileName);
	return sSavedFileName;
}

int saveRecord(struct record *record, int nRecords, char *sSavedFileName)
{
	int i, j, nCurrentIndex = nRecords;
	int bFoundDuplicate = 0;
	char sReadText[150];
	FILE *fp;
	
	fp = fopen(sSavedFileName, "r");
	
	while (fgets(sReadText, sizeof(sReadText), fp) != NULL && nCurrentIndex < MAX_RECORDS) 
	{
	    int nLength = strlen(sReadText);
			
	    if (nLength > 0 && sReadText[nLength-1] == '\n') 
		{
	        sReadText[nLength-1] = '\0';
	    }
			
	    switch(i) 
		{
	        case 0:
	            strcpy((record+nCurrentIndex)->sTopic, sReadText);
	            break;
	        case 1:
	            (record+nCurrentIndex)->nQuestionNum = stringToInt(sReadText);
	            break;
	        case 2:
	            strcpy((record+nCurrentIndex)->sQuestion, sReadText);
	            break;
	        case 3:
	            strcpy((record+nCurrentIndex)->sChoicesOne, sReadText);
	            break;
	        case 4:
	            strcpy((record+nCurrentIndex)->sChoicesTwo, sReadText);
	            break;
	        case 5:
	            strcpy((record+nCurrentIndex)->sChoicesThree, sReadText);
	            break;
	        case 6:
	            strcpy((record+nCurrentIndex)->sAnswer, sReadText);
	            break;
	        case 7:
	        	bFoundDuplicate = 0;
	        	for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	        	{
	        		if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
					    strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
					{
						bFoundDuplicate = 1;
					}
				}
				if (!bFoundDuplicate)
				{
					nCurrentIndex++;	
				}
	        	break;
	    }
			
	    i++;
			
	    if (i == 8) 
		{
	        i = 0;
	    }
	}
	/*
	//Conditions these cover, if it is at the end of the file so ignores newline, if there is only one record. 
	The previous block of code at case 7 does have the same purpose, but it does not cover if there is only one record.
	*/
	if (i == 7 && nCurrentIndex < MAX_RECORDS && feof(fp)) 
	{
	    bFoundDuplicate = 0;
	    for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	    {
	        if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
				strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
			{
				bFoundDuplicate = 1;
			}
		}
		if (!bFoundDuplicate)
		{
			nCurrentIndex++;	
		}
	}
	
	nRecords = nCurrentIndex;
	printf("\n||| Records saved successfully.\n");
	
	return nRecords;	
}

void playGame(struct record *record, int nRecords, int nUniqueTopicNum)
{
	int i, j;
	
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
