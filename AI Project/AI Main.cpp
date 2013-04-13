#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
#include "Constants.h"
#include "DataTrack.h"
#include <time.h>

using namespace std;

string chromosome = "199#353A";
string file = "chromosome.txt";
short int gameArray[ARRAY_ROW][ARRAY_COL];

class aiArrayOffensive
{
      short int moveSet[ARRAY_ROW][ARRAY_COL];//negative values indicate lack of initiation to actual positions
	  short int movesMade[125];		   //moves that have been made so far
      double totalScore;                  //for the current iteration
      int wins;
      int losses;
      int draws;
      unsigned int identNum;     //do not exceed ~200,000 iterations, or this # will be too high and u go kaput.
      
      public:
              aiArrayOffensive();
              void setArray(short int arr[ARRAY_ROW][ARRAY_COL]);
              void setElement(int row, int col, int val);
              void setScore();
              void setWins(int w);
              void setLoss(int l);
              void setDraws(int d);
			  void setMovesMade(int loc, int x, int y, int z);
              void printArray();
              int dumpToFile();       //writes contents of the class to a predetermined file, useful in death
              void kill();             //does all the necessary things before killing a class member (like logs)
              double getScore();
              int getWins();
              int getLoss();
              int getDraws();
              unsigned int getIdent();
			  short int getElement(int row, int col);
			  int TestMove(short int move);
			  int getX(short int move);
			  int getY(short int move);
			  int getZ(short int move);
			  short int getMove(int turn);
              //public for convenience... dont want to write all those get and set functions... bleh
              DataTrack stats;           // lifetime wins, losses, draws, birth(iteration #),
                           //death(iteration #), id#, spawned from id#, gave birth to id#.
                           //0 values indicate data not relevant or set (if generated randomly, spawned from
                           //will be 0, or if did not give birth to anyone.)
};

class aiArrayDefensive
{
      short int moveSet[ARRAY_ROW][ARRAY_COL][2];//negative values indicate lack of initiation to actual positions
	  short int movesMade[125];		   //moves that have been made so far
      double totalScore;                  //for the current iteration
      int wins;
      int losses;
      int draws;
      unsigned int identNum;     //do not exceed ~200,000 iterations, or this # will be too high and u go kaput.
      
      public:
              aiArrayDefensive();
              void setArray(short int arr[ARRAY_ROW][ARRAY_COL], int mode);
              void setElement(int row, int col, int val);
              void setScore();
              void setWins(int w);
              void setLoss(int l);
              void setDraws(int d);
			  void setMovesMade(int loc, int x, int y, int z);
              void printArray();
              int dumpToFile();       //writes contents of the class to a predetermined file, useful in death
              void kill();             //does all the necessary things before killing a class member (like logs)
              double getScore();
              int getWins();
              int getLoss();
              int getDraws();
			  short int getElement(int row, int col, int dim);
			  int TestMove(short int move);
              unsigned int getIdent();
			  int getX(short int move);
			  int getY(short int move);
			  int getZ(short int move);
			  short int getMove(int turn);
              //public for convenience... dont want to write all those get and set functions... bleh
              DataTrack stats;           // lifetime wins, losses, draws, birth(iteration #),
                           //death(iteration #), id#, spawned from id#, gave birth to id#.
                           //0 values indicate data not relevant or set (if generated randomly, spawned from
                           //will be 0, or if did not give birth to anyone.)
};

short int GenerateLocation();
void PopulateFirstDim(short int arr[ARRAY_ROW][ARRAY_COL]);
void Validate(short int arr[ARRAY_ROW][ARRAY_COL]);
int TestColumn(short int arr[ARRAY_ROW]);
void PrintArray(short int arr[ARRAY_ROW][ARRAY_COL]);
void PrintArray(short int arr[ARRAY_ROW][ARRAY_COL], int dim);
void ShuffleElements(short int arr[ARRAY_ROW][ARRAY_COL]);
//Playing functions
void display(char board[DIMENSION][DIMENSION][DIMENSION]);
void init(char board[DIMENSION][DIMENSION][DIMENSION]);
char checkX(int z, int y, char board[DIMENSION][DIMENSION][DIMENSION]);
char checkY(int z, int x, char board[DIMENSION][DIMENSION][DIMENSION]);
char checkZ(int y, int x, char board[DIMENSION][DIMENSION][DIMENSION]);
char checkLevel(int z, char board[DIMENSION][DIMENSION][DIMENSION]);
char checkDiagonals(char board[DIMENSION][DIMENSION][DIMENSION]);
char checkWinner(char board[DIMENSION][DIMENSION][DIMENSION]);
int PlayGame(aiArrayOffensive attacker, aiArrayDefensive defender);
void CrossOver(aiArrayOffensive attack1, aiArrayOffensive* attack2, int mode);
void CrossOver(aiArrayDefensive defend1, aiArrayDefensive* defend2, int mode);
void BubbleSort(aiArrayOffensive att[POP_SIZE]);
void BubbleSort(aiArrayDefensive def[POP_SIZE]);
void PrintScores(aiArrayOffensive attack[POP_SIZE], aiArrayDefensive defend[POP_SIZE]);
void Mutation(aiArrayOffensive* attack);
void Mutation(aiArrayDefensive* defend);
void validateArray(aiArrayOffensive att[POP_SIZE]);
short int FindMissingElement(aiArrayOffensive att, int col);
int writeChromosomeToFile(aiArrayOffensive att, aiArrayDefensive def, int count);
void readChromosomeFromFile(short int arr1[ARRAY_ROW][ARRAY_COL], string filename, string chromosome);

int main()
{
	cout<<"HI"<<endl;
	
	double iterToDo=iterationsToRun;
	double iterNum;
	double compPercent;
	int printCount=0;
	time_t sample_1;
	time_t sample_2;
	time_t start;
	
	start = time (NULL);

    aiArrayOffensive attack[POP_SIZE];
	aiArrayDefensive defend[POP_SIZE];
    short int tempArray[ARRAY_ROW][ARRAY_COL];
 
    cout<<">>>-Welcome to your Genetic Algorithm!!-<<<\n\n\n"<<endl;
    cout<<">>>-Enter a seed value for the generator-<<<"<<endl;
    
    //cin>>seedNum;
    
    cout<<">>>-Thanks for <"<<seedNum<<"> ... populating arrays ...-<<<"<<endl;
    
    srand(seedNum);

	//Populating Defensive Arrays First Main dimension

	PopulateFirstDim(tempArray);

	for(int q=0; q<POP_SIZE; q++)
	{
		defend[q].setArray(tempArray, 0);
	}

	//Populating Offensive and Defensive Arrays

	//cout<<"populated first dim"<<endl;

	//PrintArray(tempArray);
	
	//system("PAUSE");
    
    for(int j=0; j<POP_SIZE; j++)
	{
		ShuffleElements(tempArray);

        attack[j].setArray(tempArray);

		for(int i=0; i<ARRAY_ROW; i++)
        {
                for(int k=0; k<ARRAY_COL; k++)
                {
						//cout<<"setting row "<<i<<", column "<<k<<endl;
                        tempArray[i][k]=GenerateLocation();
                }
        }

		//cout<<"populating at "<<j<<endl;

		PopulateFirstDim(tempArray);
		
		//PrintArray(tempArray);
		//system("PAUSE");
		
		ShuffleElements(tempArray);
		
		//PrintArray(tempArray);
		//system("PAUSE");

		defend[j].setArray(tempArray, 1);
		
		//defend[j].printArray();
		//system("PAUSE");

		PopulateFirstDim(tempArray);
		defend[j].setArray(tempArray, 0);
    }
    
    //defend[0].printArray();
    
    //system("PAUSE");


	readChromosomeFromFile(gameArray, file ,chromosome);
	attack[0].setArray(gameArray);
	system("PAUSE");


	cout<<"ITERATIONS STARTING....\n\n";

	for(int k=0; k<iterationsToRun; k++)
	{
		int result;
		int counter=0;
		time_t temp1;
		time_t temp2;
		time_t timeToComplete;
		struct tm * timeinfo;
		time_t compDate;
		
		sample_1 = time (NULL);

		for(int d=0; d<POP_SIZE; d++)
		{
			for(int j=0; j<POP_SIZE; j++)
			{
				result=PlayGame(attack[d], defend[j]);
				//cout<<"#"<<counter<<", Att "<<d<<" vs Def "<<j;

				if(result==0)
				{
					//cout<<"||Att wins!"<<endl;

					attack[d].setWins(attack[d].getWins()+1);
					attack[d].setScore();

					defend[j].setLoss(defend[j].getLoss()+1);
					defend[j].setScore();
				}
				if(result==1)
				{
					//cout<<"||Def wins!"<<endl;

					attack[d].setLoss(attack[d].getLoss()+1);
					attack[d].setScore();

					defend[j].setWins(defend[j].getWins()+1);
					defend[j].setScore();
				}
				if(result==2)
				{
					//cout<<"||TIE!!!"<<endl;

					attack[d].setDraws(attack[d].getDraws()+1);
					attack[d].setScore();

					defend[d].setDraws(defend[d].getDraws()+1);
					defend[j].setScore();
				}

				counter++;
			}
		}

		//PrintScores(attack, defend);
		
		//cout<<endl<<endl;
		
		//system ("PAUSE");

		BubbleSort(attack);
		BubbleSort(defend);

		PrintScores(attack, defend);
		
		cout<<endl<<endl;
		
		//system("PAUSE");

		//PERFORM GENETIC ALTERATION

			attack[0].setDraws(0);
			attack[0].setLoss(0);
			attack[0].setWins(0);
			attack[0].setScore();

		for(int e=1; e<POP_SIZE; e++)
		{
            //cout<<"\n\n*****BEFORE ALTERATION*****\n\n";
            //attack[e].printArray();    
                
			CrossOver(attack[0], &attack[e], 0);
			Mutation(&attack[e]);
			
			//cout<<"\n\n*****AFTER ALTERATION*****\n\n";
			
			//attack[e].printArray();                    //so they are the same even after alterations...

			attack[e].setDraws(0);
			attack[e].setLoss(0);
			attack[e].setWins(0);
			attack[e].setScore();
		}

		defend[0].setDraws(0);
		defend[0].setLoss(0);
		defend[0].setWins(0);
		defend[0].setScore();

		for(int e=1; e<POP_SIZE; e++)
		{
			CrossOver(defend[0], &defend[e], 0);
			Mutation(&defend[e]);

			defend[e].setDraws(0);
			defend[e].setLoss(0);
			defend[e].setWins(0);
			defend[e].setScore();
		}
		
		iterNum=k;
		compPercent=(iterNum/iterToDo)*100;
		
		cout<<"\n** **\n** **\n** ** FINISHED ITERATION #"<<k<<" ** ** :"<<compPercent<<"% complete .. \n** **";
		
		if(!(k<11))
		{
            cout<<" Latest ETA is "<<asctime(timeinfo)<<"\n** ** 10: "<<temp1<<" sec's, Elapsed: "<<temp2<<" sec's\n";
  }
  
		cout<<"\n\n\n";
		
		
		if(k==(iterationsToRun-1))
		{
            /*cout<<"\n\n\n\n*****ITERATIONS COMPLETED, PRINTING TOP ATTACKER*****\n\n\n\n";
            attack[0].printArray();
            cout<<"\n\n";
            
            cout<<"\n\n\n\n*****ITERATIONS COMPLETED, PRINTING TOP DEFENDER*****\n\n\n\n";
            defend[0].printArray();
            cout<<"\n\n";*/

			cout<<"Writing to File"<<endl;

			writeChromosomeToFile(attack[0], defend[0], printCount);

			cout<<"Writing complete"<<endl;

			//system("PAUSE");
        }
        
        if(k%500==0 && k!=0)
        {
         cout<<"Writing to File"<<endl;

			      writeChromosomeToFile(attack[0], defend[0], printCount);

			      cout<<"Writing complete"<<endl;
			      
			      printCount++;
         
         }
        
        if(k%10==0 && k!=0)
		{

			cout<<"Validating Attacker\n\n";
			validateArray(attack);
			cout<<"Complete!\n\n";
			
			sample_2 = time (NULL);
			
			temp1=difftime(sample_2, sample_1);
			temp2=(difftime(sample_2, start));
			
			timeToComplete=(((100/compPercent)-1)*temp2);
			
			printf("Time for 10 Iterations is %ld seconds.\n\n", temp1);
			printf("Time elapsed since program start is %ld seconds.\n\n", temp2);
			cout<<"Estimated time remaining is : "<<timeToComplete<<" seconds.\n\n";
			
            compDate=timeToComplete+time(NULL);
            timeinfo = localtime ( &compDate );
			
			printf ( "Estimated completion time is: %s", asctime (timeinfo) );
			
  /*struct tm * timeinfo;

  timeinfo = localtime ( &timeToComplete );
			
			cout<<"Estimated time of completion is "<<asctime(timeinfo)<<"\n\n";*/

            /*cout<<"\n\n\n\n*****PRINTING INTERMITTENT RESULTS, ATTACKER*****\n\n\n\n";
            
            for(int x=0; x<2; x++)
            {
                cout<<"##$Attacker #"<<x<<", Iteration "<<k<<endl;
                attack[x].printArray();
                cout<<"\n\n";
            }
            
            cout<<"\n\n\n\n*****PRINTING INTERMITTENT RESULTS, DEFENDER*****\n\n\n\n";
            
            for(int x=0; x<2; x++)
            {
                cout<<"##$Defender #"<<x<<", Iteration "<<k<<endl;
                defend[x].printArray();
                cout<<"\n\n";
            }*/
        }
	}

    //system("PAUSE");
    
    //attack[0].printArray();
    
    //system("PAUSE");
    return 0;
}

aiArrayOffensive::aiArrayOffensive()
{
   for(int i=0; i<ARRAY_ROW; i++)
   {
           for(int s=0; s<ARRAY_COL; s++)
           {
				   //cout<<endl;
			       //cout<<"array index ["<<i<<"]["<<s<<"]"<<endl;
				   //cout<<"setting row "<<i<<", column "<<s<<endl<<endl;
                   moveSet[i][s]=-1;          //Row-Major order, rows filled row by row (across), 
                                              //going across columns s,
                                              //i.e. 'i' denotes the row #, s the column #.
           }
   }

   for(int i=0; i<ARRAY_ROW; i++)
   {
	   movesMade[i]=0;
   }
   
   totalScore=0;
   wins=0;
   losses=0;
   draws=0;
   identNum=idCount;
   stats.birth=onIteration;
   stats.death=0;
   stats.lifeDraws=0;
   stats.lifeLosses=0;
   stats.lifeWins=0;
   stats.numReproduced=0;
   stats.parent1=0;
   stats.parent2=0;
   stats.survivalCount=0;
   stats.numReproduced=0;
   idCount++;
}

void aiArrayOffensive::setArray(short int arr[ARRAY_ROW][ARRAY_COL])
{
    for(int i=0; i<ARRAY_ROW; i++)
	{
		   for(int s=0; s<ARRAY_COL; s++)
           {
                   moveSet[i][s]=arr[i][s];          
                                              //Row-Major order, rows filled row by row (across), 
                                              //going across columns s,
                                              //i.e. 'i' denotes the row #, s the column #.
           }
   }
}

void aiArrayOffensive::setElement(int row, int col, int val)
{
     moveSet[row][col]=(short int)val;
}

void aiArrayOffensive::setScore()
{
     totalScore=(wins*winMult)+(losses*lossMult)+(draws*tieMult);
}

void aiArrayOffensive::setWins(int w)
{
     wins=w;
}

void aiArrayOffensive::setLoss(int l)
{
     losses=l;
}

void aiArrayOffensive::setDraws(int d)
{
     draws=d;
}

void aiArrayOffensive::setMovesMade(int loc, int x, int y, int z)
{
	  short int cord1=x;
      short int cord2=y;
      short int cord3=z;
      
      short int result;
      char first_buffer[20];
      char second_buffer[20];
      char third_buffer[20];
      char concatenated_buffers[60];
      
      itoa(cord1,first_buffer,10);
      itoa(cord2,second_buffer,10);
      itoa(cord3,third_buffer,10);
      
      strcpy(concatenated_buffers,first_buffer);
      strcat(concatenated_buffers,second_buffer);
      strcat(concatenated_buffers,third_buffer);
      result = atoi(concatenated_buffers);

	  movesMade[loc]=result;
}

void aiArrayOffensive::printArray()
{
     for(int k=0; k<ARRAY_ROW; k++)
     {
             for(int j=0;j<ARRAY_COL; j++)
             {
                     if(j==0 && k==0)
                     {
                             for(int h=0; h<ARRAY_COL; h++)
                             {
                                     cout<<"C#"<<h%10<<" ";
                             }        
                             
                             cout<<endl;
                     }
                     
                     cout<<moveSet[k][j]<<" ";
             }
             
             cout<<endl;
     }
}

void aiArrayOffensive::kill()
{
     printf("Cant kill me! ..\n");
}

double aiArrayOffensive::getScore()
{
     return totalScore;
}

int aiArrayOffensive::getWins()
{
     return wins;
}

int aiArrayOffensive::getLoss()
{
     return losses;
}

int aiArrayOffensive::getDraws()
{
     return draws;
}

unsigned int aiArrayOffensive::getIdent()
{
     return identNum;
}

short int aiArrayOffensive::getElement(int row, int col)
{
	return moveSet[row][col];
}

int aiArrayOffensive::TestMove(short int move)
{
	//0 means move is free

	for(int i=0; i<ARRAY_ROW; i++)
    {
	   if(move==movesMade[i])
	   {
		   return 1;  //move is not free
	   }
    }

	return 0;
}

int aiArrayOffensive::getX(short int move)
{
	return move/100;
}

int aiArrayOffensive::getY(short int move)
{
	return (move%100)/10;
}

int aiArrayOffensive::getZ(short int move)
{
	return move%10;
}

short int aiArrayOffensive::getMove(int turn)
{
	short int move=GenerateLocation();
	int result=0;
	
	/*cout<<"Printing Moves Made"<<endl;

	for(int i=0; i<ARRAY_ROW; i++)
	{
		cout<<movesMade[i]<<endl;

		if(movesMade[i]==0)
		{
			break;
		}
	}*/

	for(int i=0; i<ARRAY_ROW+1; i++)
	{
		if(i>=125)
		{
			cout<<"NO MOVESS!!!! (offensive) going into complete overdrive..."<<endl;
            //system("PAUSE");
            
            short int tempArray[ARRAY_ROW][ARRAY_COL];
            
            PopulateFirstDim(tempArray);

			for(int s=0; s<ARRAY_ROW; s++)
			{
				result=TestMove(tempArray[s][0]);

				if(result==0)
				{
					setMovesMade(turn-1, getX(move), getY(move), getZ(move));

					moveSet[2][(turn-1)/2]=move;

					return move;
				}

				if(i==125)
				{
					cout<<"WTF!!!??"<<endl;
					break;
				}
			}
		}
		else
		{
			//cout<<"On turn "<<turn<<", accessing element "<<((turn-1)/2)<<endl;
			//system("PAUSE");


			move=getElement(i, ((turn-1)/2));
			//system("PAUSE");
			result=TestMove(move);

			if(result==0)
			{
                //cout<<"Found a compatible move, making "<<move<<endl;
				setMovesMade(turn-1, getX(move), getY(move), getZ(move));

				return move;
			}
			else
			{
                //cout<<"Move illegal, going down the array."<<endl;
            }
		}
	}

	setMovesMade(turn-1, getX(move), getY(move), getZ(move));
	return move;
}

//CLASS DECLARATIONS FOLLOW FOR DEFENSIVE AI

aiArrayDefensive::aiArrayDefensive()
{
   for(int i=0; i<ARRAY_ROW; i++)
   {
           for(int s=0; s<ARRAY_COL; s++)
           {
                   moveSet[i][s][1]=(short)-1; //Row-Major order, rows filled row by row (across),
                   moveSet[i][s][2]=(short)-1; //going across columns s,
                                               //i.e. 'i' denotes the row #, s the column #.
           }
   }

   for(int i=0; i<ARRAY_ROW; i++)
   {
	   movesMade[i]=0;
   }
   
   totalScore=0;
   wins=0;
   losses=0;
   draws=0;
   identNum=idCount;
   stats.birth=onIteration;
   stats.death=0;
   stats.lifeDraws=0;
   stats.lifeLosses=0;
   stats.lifeWins=0;
   stats.numReproduced=0;
   stats.parent1=0;
   stats.parent2=0;
   stats.survivalCount=0;
   stats.numReproduced=0;
   idCount++;
}

void aiArrayDefensive::setArray(short int arr[ARRAY_ROW][ARRAY_COL], int mode)
{
   if(mode==1)
   {
	   for(int i=0; i<ARRAY_ROW; i++)
	   {
			   for(int s=0; s<ARRAY_COL; s++)
			   {
                       //cout<<"setting moveSet["<<i<<"]["<<s<<"][1]=arr["<<i<<"]["<<s<<"]"<<endl;
                       //cout<<"which is "<<moveSet[i][s][1]<<"="<<arr[i][s]<<endl;
                       
					   moveSet[i][s][1]=arr[i][s];          
												  //Row-Major order, rows filled row by row (across), 
												  //going across columns s,
												  //i.e. 'i' denotes the row #, s the column #.
				       //system("PAUSE");
			   }
	   }
   }
   
   //system("PAUSE");
   //printArray();
   //system("PAUSE");

   if(mode==0)
   {
	   for(int i=0; i<ARRAY_ROW; i++)
	   {
			   for(int s=0; s<ARRAY_COL; s++)
			   {
                       //cout<<"setting moveSet["<<i<<"]["<<s<<"][0]=arr["<<i<<"]["<<s<<"]"<<endl;
                       //cout<<"which is "<<moveSet[i][s][0]<<"="<<arr[i][s]<<endl;
                       
					   moveSet[i][s][0]=arr[i][s];          
												  //Row-Major order, rows filled row by row (across), 
												  //going across columns s,
												  //i.e. 'i' denotes the row #, s the column #.
												  
                       //system("PAUSE");
			   }
	   }
   }
}

void aiArrayDefensive::setElement(int row, int col, int val)
{
     moveSet[row][col][1]=(short)val;
}

void aiArrayDefensive::setScore()
{
     totalScore=(wins*winMult)+(losses*lossMult)+(draws*tieMult);
}

void aiArrayDefensive::setWins(int w)
{
     wins=w;
}

void aiArrayDefensive::setLoss(int l)
{
     losses=l;
}

void aiArrayDefensive::setDraws(int d)
{
     draws=d;
}

void aiArrayDefensive::setMovesMade(int loc, int x, int y, int z)
{
	//cout<<"setting move made array in DEFENDER, element "<<loc<<endl;

	short int cord1=(short int)x;
	short int cord2=(short int)y;
	short int cord3=(short int)z;
      
	short int result;
	char first_buffer[20];
	char second_buffer[20];
	char third_buffer[20];
	char concatenated_buffers[60];
      
	itoa(cord1,first_buffer,10);
	itoa(cord2,second_buffer,10);
	itoa(cord3,third_buffer,10);
      
	strcpy(concatenated_buffers,first_buffer);
	strcat(concatenated_buffers,second_buffer);
	strcat(concatenated_buffers,third_buffer);
	result = atoi(concatenated_buffers);

	//cout<<" to "<<result<<endl;

	movesMade[loc]=result;
}

void aiArrayDefensive::printArray()
{
     for(int k=0; k<ARRAY_ROW; k++)
     {
             for(int j=0;j<ARRAY_COL; j++)
             {
                     if(j==0 && k==0)
                     {
                             for(int h=0; h<ARRAY_COL; h++)
                             {
                                     cout<<"C#"<<h%10<<" ";
                             }        
                             
                             cout<<endl;
                     }
                     
                     cout<<moveSet[k][j][1]<<" ";
             }
             
             cout<<endl;
     }
}

void aiArrayDefensive::kill()
{
     printf("Cant kill me! ..\n");
}

double aiArrayDefensive::getScore()
{
     return totalScore;
}

int aiArrayDefensive::getWins()
{
     return wins;
}

int aiArrayDefensive::getLoss()
{
     return losses;
}

int aiArrayDefensive::getDraws()
{
     return draws;
}

unsigned int aiArrayDefensive::getIdent()
{
     return identNum;
}

short int aiArrayDefensive::getElement(int row, int col, int dim)
{
	return moveSet[row][col][dim];
}

int aiArrayDefensive::TestMove(short int move)
{
	//0 means move is free

	for(int i=0; i<ARRAY_ROW; i++)
    {
	   if(move==movesMade[i])
	   {
		   return 1;  //move is not free
	   }
    }

	return 0;
}

int aiArrayDefensive::getX(short int move)
{
	return move/100;
}

int aiArrayDefensive::getY(short int move)
{
	return (move%100)/10;
}

int aiArrayDefensive::getZ(short int move)
{
	return move%10;
}

short int aiArrayDefensive::getMove(int turn)
{
	/*cout<<"Printing Moves Made"<<endl;

	for(int i=0; i<ARRAY_ROW; i++)
	{
		cout<<movesMade[i]<<endl;

		if(movesMade[i]==0)
		{
			break;
		}
	}*/

	short int move=GenerateLocation();
	short int latest=movesMade[turn-2];

	//cout<<"Now in Defensive.GetMove"<<endl;
	//cout<<"Current turn is "<<turn<<endl;
	//cout<<"Setting latest to element #"<<(turn-2)<<endl;
    //cout<<"Value at element #"<<(turn-2)<<" is "<<movesMade[(turn-2)]<<endl;

	for(int i=0; i<ARRAY_ROW; i++)
	{
		//cout<<"Looking for match, "<<moveSet[i][((turn/2)-1)][0]<<" versus "<<latest<<endl;

		if(moveSet[i][(turn/2-1)][0]==latest)
		{
			//cout<<"Matched the attackers move, which was "<<latest<<endl;

			int record=i;
			int result=TestMove(moveSet[i][(turn/2-1)][1]);

			if(!result)
			{
				//cout<<"no illegal move on "<<moveSet[i][(turn/2-1)][1]<<endl;

				move=moveSet[i][(turn/2-1)][1];

				setMovesMade(turn-1, getX(move), getY(move), getZ(move));

				return move;
			}
			else
			{
				//cout<<"illegal move on "<<moveSet[i][(turn/2-1)][1]<<endl;
				//system("PAUSE");

				//cout<<"NO MOVESS (defensive)!!!! going into partial overdrive..."<<endl;
				
				int p=i;
				
				for(; p<125; p++)
				{
                    //cout<<"i is at "<<i<<" so...."<<endl;
                    //cout<<"p is at "<<p<<" so...."<<endl;
                    
                    //cout<<"testing "<<moveSet[p][(turn/2-1)][1]<<endl;
                        
                    result=TestMove(moveSet[p][(turn/2-1)][1]);

					if(result==0)
					{
						move=moveSet[p][(turn/2-1)][1];
						
						//cout<<"Got move "<<move<<" , setting and continuing..."<<endl;

						setMovesMade(turn-1, getX(move), getY(move), getZ(move));

						return move;
					}
                }
                
                //cout<<"NO MOVESS (defensive)!!!! going into complete overdrive..."<<endl;

				short int tempArray[ARRAY_ROW][ARRAY_COL];

				PopulateFirstDim(tempArray);

				for(int s=0; s<ARRAY_ROW; s++)
				{
					result=TestMove(tempArray[s][0]);

					if(result==0)
					{
                        //cout<<"Found valid move, making "<<tempArray[i][0]<<endl;
                                 
						move=tempArray[s][0];

						setMovesMade(turn-1, getX(move), getY(move), getZ(move));

						moveSet[record][(turn/2-1)][1]=move;

						return move;
					}
					
					//cout<<"Invalid move at search: "<<tempArray[i][0]<<" has been made."<<endl;

					if(s==124)
					{
						cout<<"WTF!!!??"<<endl;
						system("PAUSE");
						break;
					}
				}
			}
		}
	}

	cout<<"No solution found, for "<<latest<<endl;

	system("PAUSE");

	return move;
}

//FUNCTION DEFINITIONS FOLLOW

void PrintScores(aiArrayOffensive attack[POP_SIZE], aiArrayDefensive defend[POP_SIZE])
{
	cout<<endl<<"Printing attacker's scores"<<endl;

	for(int f=0; f<POP_SIZE; f++)
	{
		cout<<"#"<<f<<": Score <"<<attack[f].getScore()<<"> Won <"<<attack[f].getWins()<<"> Lost <"<<attack[f].getLoss()<<"> Tied <"<<attack[f].getDraws()<<">"<<endl;
	}

	cout<<"\nPrinting defenders's scores"<<endl;

	for(int f=0; f<POP_SIZE; f++)
	{
		cout<<"#"<<f<<": Score <"<<defend[f].getScore()<<"> Won <"<<defend[f].getWins()<<"> Lost <"<<defend[f].getLoss()<<"> Tied <"<<defend[f].getDraws()<<">"<<endl;
	}
}

short int GenerateLocation()
{
      short int cord1=rand() % 5 + 1;
      short int cord2=rand() % 5 + 1;
      short int cord3=rand() % 5 + 1;
      
      short int result;
      char first_buffer[20];
      char second_buffer[20];
      char third_buffer[20];
      char concatenated_buffers[60];
      
      itoa(cord1,first_buffer,10);
      itoa(cord2,second_buffer,10);
      itoa(cord3,third_buffer,10);
      
      strcpy(concatenated_buffers,first_buffer);
      strcat(concatenated_buffers,second_buffer);
      strcat(concatenated_buffers,third_buffer);
      result = atoi(concatenated_buffers);
      
      //cout<<"num gen'd: "<<cord1;
      //cout<<cord2;
      //cout<<cord3;
      //cout<<", result is: "<<result<<endl; 
      
      return result;
}

void PopulateFirstDim(short int arr[ARRAY_ROW][ARRAY_COL])
{
	int count = 0;

	for(int s=0; s<ARRAY_COL; s++)
	{
		for(short int i=1; i <= 5; i++)
		{
			for(short int j=1; j <= 5; j++)
			{
				for(short int k=1; k <= 5; k++)
				{
					short int result;
					char first_buffer[20];
					char second_buffer[20];
					char third_buffer[20];
					char concatenated_buffers[60];
      
					itoa(i,first_buffer,10);
					itoa(j,second_buffer,10);
					itoa(k,third_buffer,10);
      
					strcpy(concatenated_buffers,first_buffer);
					strcat(concatenated_buffers,second_buffer);
					strcat(concatenated_buffers,third_buffer);
					result = atoi(concatenated_buffers);

					//printf("Printing First Dimension\n");
					//cout<<result;

					arr[count][s]=result;

					count++;
				}
			}
		}
		count=0;
	}

	//PrintArray(arr);
}

void ShuffleElements(short int arr[ARRAY_ROW][ARRAY_COL])
{
	//cout<<"Now shuffling"<<endl;

	//PrintArray(arr);

	short int temp;

	 for(int i=0; i<ARRAY_COL; i++)
	 {
		 for(int j=0; j<ARRAY_ROW; j++)
		 {
			 int i1=rand() % 125;
			 int i2=rand() % 125;

			 while(i1==i2)
			 {
				//cout<<"they're equal "<<i1<<" "<<i2<<endl;
				i1=rand() % 125;
				i2=rand() % 125;
			 }

			 //cout<<"Replacing at "<<i1<<" and at "<<i2<<endl;

			 //switch elements
			 temp=arr[i1][i];

			 arr[i1][i]=arr[i2][i];
			 arr[i2][i]=temp;
		 }
	 }

	 //cout<<"Ended shuffling"<<endl;

	 //PrintArray(arr);
}

void CrossOver(aiArrayOffensive attack1, aiArrayOffensive* attack2, int mode)
{
	short int swap1, swap2, min, max;
	
	//pick random column from arr1 and one random from arr2

	short int randomColumn = rand() % ARRAY_COL;
	short int randomRow = rand() % ARRAY_ROW;
	short int randomRow2 = rand() % ARRAY_ROW;
	
	//cout<<"Preparing to cross ... \n";

	if(randomRow < randomRow2)
	{ 
		min = randomRow;
		max = randomRow2;
	}
	else
	{ 
		min = randomRow2;
		max = randomRow;
	}
	
	//swap the two values

	if(mode==1)	//do a full swap
	{
        //cout<<"Doing full swap\n";
                
		for(short int x = min; x < max; x++)
		{
			swap1 = attack1.getElement(x, randomColumn);
			swap2 = (*attack2).getElement(x, randomColumn);
		
			attack1.setElement(x, randomColumn, swap2);
			(*attack2).setElement(x, randomColumn, swap1);
		}
	}
	else if(mode==0)	//do a partial swap, leaving the first participant unchanged
	{
        //cout<<"Doing partial swap\n";
         
		for(short int x = min; x < max; x++)
		{
			swap1 = attack1.getElement(x, randomColumn);

            //cout<<"Getting element :"<<swap1<<", from elite attacker. At column "<<randomColumn<<endl;
            //cout<<"Setting element #"<<x<<", to new element from elite "<<swap1<<endl;
            //cout<<"Where it previously was:"<<(*attack2).getElement(x, randomColumn)<<endl;

			(*attack2).setElement(x, randomColumn, swap1);
			
			//cout<<"The element x has been set to: "<<(*attack2).getElement(x, randomColumn)<<endl;
			//system("PAUSE");
		}
	}
}

void CrossOver(aiArrayDefensive defend1, aiArrayDefensive* defend2, int mode)
{
	short int swap1, swap2, min, max;
	
	//pick random column from arr1 and one random from arr2

	short int randomColumn = rand() % ARRAY_COL;
	short int randomRow = rand() % ARRAY_ROW;
	short int randomRow2 = rand() % ARRAY_ROW;

	if(randomRow < randomRow2)
	{ 
		min = randomRow;
		max = randomRow2;
	}
	else
	{ 
		min = randomRow2;
		max = randomRow;
	}
	
	//swap the two values
	if(mode==1)	//do a full swap
	{
		for(short int x = min; x < max; x++)
		{
			swap1 = defend1.getElement(x, randomColumn, 1);
			swap2 = (*defend2).getElement(x, randomColumn, 1);
		
			defend1.setElement(x, randomColumn, swap2);
			(*defend2).setElement(x, randomColumn, swap1);
		}
	}
	else if(mode==0)	//do a partial swap, leaving the first participant unchanged
	{
		for(short int x = min; x < max; x++)
		{
			swap1 = defend1.getElement(x, randomColumn, 1);

			(*defend2).setElement(x, randomColumn, swap1);
		}
	}
}

void Mutation(aiArrayOffensive* attack)
{
	short int mutationNumber = rand() % 40;
	short int randomColumn = rand() % ARRAY_COL;
	//choose the random elements to be mutated
	for(short int i = 0; i < mutationNumber; i++)
	{
		//choose a random row
		short int randomRow = rand() % ARRAY_ROW;
		//cout << "mutation on row # " << randomRow << endl;
		//choose array1 or array2

		(*attack).setElement(randomRow, randomColumn, GenerateLocation());
	}

	/*cout << "Row#\tArray1\tArray2\n";
	for(int z = 0; z < 125; z++)
	{
		cout << z << "\t" << arr1[z][randomColumn] << "\t" << arr2[z][randomColumn] << endl;
	}*/
}

void Mutation(aiArrayDefensive* defend)
{
	short int mutationNumber = rand() % 40;
	short int randomColumn = rand() % ARRAY_COL;
	//choose the random elements to be mutated
	for(short int i = 0; i < mutationNumber; i++)
	{
		//choose a random row
		short int randomRow = rand() % ARRAY_ROW;
		//cout << "mutation on row # " << randomRow << endl;
		//choose array1 or array2

		(*defend).setElement(randomRow, randomColumn, GenerateLocation());
	}

	/*cout << "Row#\tArray1\tArray2\n";
	for(int z = 0; z < 125; z++)
	{
		cout << z << "\t" << arr1[z][randomColumn] << "\t" << arr2[z][randomColumn] << endl;
	}*/
}

void BubbleSort(aiArrayOffensive att[POP_SIZE])
{
	int i,j;

    for(i=0;i<POP_SIZE;i++)
    {
        for(j=0;j<i;j++)
        {
            if(att[i].getScore()>att[j].getScore())
            {
                aiArrayOffensive temp=att[i]; //swap 
                att[i]=att[j];
                att[j]=temp;
            }
        }
    }
}

void BubbleSort(aiArrayDefensive def[POP_SIZE])
{
	int i,j;

    for(i=0;i<POP_SIZE;i++)
    {
        for(j=0;j<i;j++)
        {
            if(def[i].getScore()>def[j].getScore())
            {
                aiArrayDefensive temp=def[i]; //swap 
                def[i]=def[j];
                def[j]=temp;
            }
        }
    }
}

void PrintArray(short int arr[ARRAY_ROW][ARRAY_COL])
{
	for(int i=0; i<ARRAY_ROW; i++)
	{
		cout<<"["<<i<<"] ";

		for(int j=0; j<ARRAY_COL; j++)
		{
			cout<<arr[i][j]<<"  ";
		}

		cout<<endl;
	}
}

void PrintArray(short int arr[ARRAY_ROW][ARRAY_COL][2], int dim)
{
	for(int i=0; i<ARRAY_ROW; i++)
	{
		cout<<"["<<i<<"] ";

		for(int j=0; j<ARRAY_COL; j++)
		{
			cout<<arr[i][j][dim]<<"  ";
		}

		cout<<endl;
	}
}

void validateArray(aiArrayOffensive att[POP_SIZE]) //aiArrayOffensive att[POP_SIZE]
{
	short int arr[ARRAY_ROW][ARRAY_COL];
	int count=0;
	PopulateFirstDim(arr);

	for(int u=0; u<POP_SIZE; u++)
	{
		//cout<<"At attacker "<<u<<endl;

		for(int s=0; s<ARRAY_COL; s++)
		{
			//cout<<"At column "<<s<<" of attacker "<<u<<endl;

			for(int i=0; i < ARRAY_ROW; i++)
			{
				for(int j=i; j<ARRAY_ROW; j++)
				{
					if((att[u].getElement(i, s) == att[u].getElement(j, s)) && (i!=j) && (att[u].getElement(i, s)!=0 && att[u].getElement(j, s)!=0))
					{
						//cout<<"Same at "<<i<<" and "<<j<<" i.e. :"<<att[u].getElement(i, s)<<"=="<<att[u].getElement(j, s)<<endl;
						count++;
						short int k=0;

						if(j>i)
						{
							//cout<<"Setting "<<j<<" to 0"<<endl;
							att[u].setElement(j, s, 0);

							k=FindMissingElement(att[u], s);

							if(k>0)
							{
								att[u].setElement(j, s, k);
							}
							else
							{
								cout<<"WTF"<<endl;
								system("PAUSE");
							}
						}

						else if(i>j)
						{
							//cout<<"Setting "<<i<<" to 0"<<endl;
							att[u].setElement(i, s, 0);

							k=FindMissingElement(att[u], s);

							if(k>0)
							{
								att[u].setElement(i, s, k);
							}
							else
							{
								cout<<"WTF"<<endl;
								system("PAUSE");
							}
						}

						//cout<<"Found a 0 at "<<g<<endl;
					}
				}
			}

			/*for(int g=0; g<ARRAY_ROW; g++)
			{
				if(att[u].getElement(g, s)==0)
				{
				
				}
			}*/
		}
	}

	cout<<"Made "<<count<<" changes."<<endl;
}

short int FindMissingElement(aiArrayOffensive att, int col)
{
	short int arr[ARRAY_ROW][ARRAY_COL];

	PopulateFirstDim(arr);

	for(int h=0; h<ARRAY_ROW; h++)
	{
		bool found = false;

		int k=0;

		while(k < ARRAY_ROW && !found)
		{
			if(arr[h][0]==att.getElement(k, col))
			{
				found=true;
			}

			k++;
		}

		if(!found)
		{
			return arr[h][0];
		}
	}

	return 0;
}

int writeChromosomeToFile(aiArrayOffensive att, aiArrayDefensive def, int count)
{
	ofstream file;

	file.open ("chromosome.txt",ios::app);

	cout<<"In write function, writing."<<endl;
	
	//Get the Attacking Chromosome
	file << count <<"#"<< att.getElement(0,0) << "A" << endl;  //name of the chromosome format(ChromosomeCount#FirstElementInTheArray Attack or Defend)
	for(int i = 0; i < ARRAY_ROW; i++)
	{
  
		for(int j = 0; j < ARRAY_COL; j++)
		{
			file << att.getElement(i,j) << " ";
		}
		
		file<<"\n";
	}

	file << "\n\n";

	//Get the Defending Chromosome
	file << count << "#" << def.getElement(0, 0, 0) << "D" << endl;
	for(short int x = 0; x < ARRAY_ROW; x++)
	{
  
		for(short int y = 0; y < ARRAY_COL; y++)
		{
			file << def.getElement(x, y, 1)<<" ";
		}
		 file<<"\n";
	}

	file << "\n\n";
	count++;
	file.close();

	return count;
}

void readChromosomeFromFile(short int arr1[ARRAY_ROW][ARRAY_COL], string filename, string chromosome)
{

	ifstream file;
	string line;

	file.open(filename);
	if(file.is_open())
	{
		cout << "file was opened\n";
		while(!file.eof())
		{
			getline(file,line);
			if(line.compare(chromosome) == 0)
			{
				cout << "Found Chromosome " << chromosome << endl;
				for(short int i = 0; i < ARRAY_ROW; i++){
					for(short int j = 0; j < ARRAY_COL; j++){
						file >> arr1[i][j];
					}
				}
			}

			
		}
	}

	else { cout << "File was not opened\n"; }

}
//PLAYING FUNCTIONS

void display(char board[DIMENSION][DIMENSION][DIMENSION])
{
	int x, y, z;
	for (z = 0; z < DIMENSION; z++)
	{
		for (y = 0; y < DIMENSION; y++)
		{
			for (x = 0; x < DIMENSION-1; x++)
			{
				printf(" %c |", board[z][y][x] == ' ' ? '_' : board[z][y][x]);
			}
			printf(" %c \n", board[z][y][x] == ' ' ? '_' : board[z][y][x]);
		}
		printf("\n------------------------------------------\n");
	}
	printf("\n******************\n");
	printf("\n******************\n");
	printf("\n******************\n");

}

void init(char board[DIMENSION][DIMENSION][DIMENSION])
{
	int x, y, z;
	for (z = 0; z < DIMENSION; z++)
		for (y = 0; y < DIMENSION; y++)
			for (x = 0; x < DIMENSION; x++)
				board[z][y][x] = ' ';
}

char checkX(int z, int y, char board[DIMENSION][DIMENSION][DIMENSION])
{
	char winner = board[z][y][0];
	if (winner == ' ')
		return ' ';
	for (int x = 1; x < DIMENSION; x++)
	{
		if (board[z][y][x] != board[z][y][x-1])
			return ' ';
	}
	if (DEBUG) cout << "Winner horizontal z = " << z << ", y = " << y << endl;
	return winner;

}

char checkY(int z, int x, char board[DIMENSION][DIMENSION][DIMENSION])
{
	char winner = board[z][0][x];
	if (winner == ' ')
		return ' ';
	for (int y = 1; y < DIMENSION; y++)
	{
		if (board[z][y][x] != board[z][y-1][x])
			return ' ';
	}
	if (DEBUG) cout << "Winner vertical z = " << z << ", x = " << x << endl;
	return winner;

}

char checkZ(int y, int x, char board[DIMENSION][DIMENSION][DIMENSION])
{
	char winner = board[0][y][x];
	if (winner == ' ')
		return ' ';
	for (int z = 1; z < DIMENSION; z++)
	{
		if (board[z][y][x] != board[z-1][y][x])
			return ' ';
	}
	if (DEBUG) cout << "Winner layer y = " << y << ", x = " << x << endl;
	return winner;

}

char checkLevel(int z, char board[DIMENSION][DIMENSION][DIMENSION])
{
	for (int y = 0; y < DIMENSION; y++)
	{
		char winner = checkX(z, y, board);
		if (winner != ' ')
			return winner;

	}

	for (int x = 0; x < DIMENSION; x++)
	{
		char winner = checkY(z, x, board);
		if (winner != ' ')
			return winner;
	}

	return ' ';

}

char checkDiagonals(char board[DIMENSION][DIMENSION][DIMENSION])
{
	for (int z = 0; z < DIMENSION; z++)
	{
		if ((board[z][0][0] != ' ') && (board[z][0][0]==board[z][1][1]) && (board[z][1][1]==board[z][2][2]) && (board[z][2][2]==board[z][3][3]) && (board[z][3][3]==board[z][4][4]))
		{
			if (DEBUG) cout << "[1]Winner diagonal starting at " << z << ", 0, 0" << endl;
			return board[z][0][0];
		}
		if ((board[z][4][0] != ' ') && (board[z][4][0]==board[z][3][1]) && (board[z][3][1]==board[z][2][2]) && (board[z][2][2]==board[z][1][3]) && (board[z][1][3]==board[z][0][4]))
		{
			if (DEBUG) cout << "[2]Winner diagonal starting at " << z << ", 4, 0" << endl;
			return board[z][4][0];
		}
	}

	for (int x = 0; x < DIMENSION; x++)
	{
		if ((board[0][0][x] != ' ') && (board[0][0][x]==board[1][1][x]) && (board[0][0][x]==board[2][2][x]) && (board[0][0][x]==board[3][3][x]) && (board[0][0][x]==board[4][4][x]))
		{
			if (DEBUG) cout << "[3]Winner diagonal starting at 0, 0, " << x << endl;
			return board[0][0][x];
		}
		if ((board[4][0][x] != ' ') && (board[4][0][x]==board[3][1][x]) && (board[4][0][x]==board[2][2][x]) && (board[4][0][x]==board[1][3][x]) && (board[4][0][x]==board[0][4][x]))
		{
			if (DEBUG) cout << "[4]Winner diagonal starting at 4, 0, " << x << endl;
			return board[4][0][x];
		}
	}

	for (int y = 0; y < DIMENSION; y++)
	{
		if ((board[0][y][0] != ' ') && (board[0][y][0]==board[1][y][1]) && (board[0][y][0]==board[2][y][2]) && (board[0][y][0]==board[3][y][3]) && (board[0][y][0]==board[4][y][4]))
		{
			if (DEBUG) cout << "[5]Winner diagonal starting at 0, " << y << ", 0" << endl;
			return board[0][y][0];
		}
		if ((board[4][y][0] != ' ') && (board[4][y][0]==board[3][y][1]) && (board[4][y][0]==board[2][y][2]) && (board[4][y][0]==board[1][y][3]) && (board[4][y][0]==board[0][y][4]))
		{
			if (DEBUG) cout << "[6]Winner diagonal starting at 4, " << y << ", 0" << endl;
			return board[4][y][0];
		}
	}

	if ((board[0][0][0] != ' ') && (board[0][0][0]==board[1][1][1]) && (board[0][0][0]==board[2][2][2]) && (board[0][0][0]==board[3][3][3]) && (board[0][0][0]==board[4][4][4]))
	{
		if (DEBUG) cout << "[6]Winner diagonal starting at 0, 0, 0" << endl;
		return board[0][0][0];
	}
	if ((board[4][0][0] != ' ') && (board[4][0][0]==board[3][1][1]) && (board[4][0][0]==board[2][2][2]) && (board[4][0][0]==board[1][3][3]) && (board[4][0][0]==board[0][4][4]))
	{
		if (DEBUG) cout << "[7]Winner diagonal starting at 4, 0, 0" << endl;
		return board[4][0][0];
	}
	if ((board[0][4][0] != ' ') && (board[0][4][0]==board[1][3][1]) && (board[0][4][0]==board[2][2][2]) && (board[0][4][0]==board[3][1][3]) && (board[0][4][0]==board[4][0][4]))
	{
		if (DEBUG) cout << "[8]Winner diagonal starting at 0, 4, 0" << endl;
		return board[0][4][0];
	}
	if ((board[4][4][0] != ' ') && (board[4][4][0]==board[3][3][1]) && (board[4][4][0]==board[2][2][2]) && (board[4][4][0]==board[1][1][3]) && (board[4][4][0]==board[0][0][4]))
	{
		if (DEBUG) cout << "[9]Winner diagonal starting at 4, 4, 0" << endl;
		return board[4][4][0];
	}

	return ' ';
}

char checkWinner(char board[DIMENSION][DIMENSION][DIMENSION])
{
	// Check X & Y axis for each level
	for (int z = 0; z < DIMENSION; z++)
	{
		char winner = checkLevel(z, board);
		if (winner != ' ')
			return winner;
	}

	// Now check the Z runs
	for (int y = 0; y < DIMENSION; y++)
		for (int x = 0; x < DIMENSION; x++)
		{
			char winner = checkZ(y, x, board);
			if (winner != ' ')
				return winner;
		}

	return checkDiagonals(board);

}

int PlayGame(aiArrayOffensive attacker, aiArrayDefensive defender)
{
	int result=-1;	//0 means attacker won, 1 means defender won, 2 mean a tie
	int counter = 0;
	static int NUMCELLS = DIMENSION * DIMENSION * DIMENSION;
	char board[DIMENSION][DIMENSION][DIMENSION];
	int moveX, moveY, moveZ;
	char winner = ' ';
	init(board);		//X goes first (attacker)		//O goes second (defender)
	srand ( time(NULL) );

	while ((winner == ' ') && (counter <= NUMCELLS))
	{
        //cout << "Counter = " << counter << endl;
        
        if (counter >= 125)
	    {
		    //cout << "Tie!" << endl;
		    //display(board);
		    //cout<<endl<<endl;
		    //system("PAUSE");
		    return 2;
	    }
        
		counter++;
		if (counter % 2 == 1)
		{
			//pX.selectMove(moveZ, moveY, moveX);

			short int move=attacker.getMove(counter);

			moveZ=attacker.getZ(move)-1;
			moveY=attacker.getY(move)-1;
			moveX=attacker.getX(move)-1;



			//cout << "Player X moves [" << moveZ << "][" << moveY << "][" << moveX << "]" << endl;
			if (board[moveZ][moveY][moveX] == ' ')
			{
				board[moveZ][moveY][moveX] = 'X';

				defender.setMovesMade(counter-1, moveX+1, moveY+1, moveZ+1);

				//pO.notifyMove(moveZ, moveY, moveX);
			}
			else
			{
                cout << "Player X moves [" << moveZ << "][" << moveY << "][" << moveX << "]" << endl;
				cout << "Player X makes an illegal move and loses!" << endl;
				winner = 'O';
				//system("PAUSE");
				break;
			}
		}
		else
		{
			//pO.selectMove(moveZ, moveY, moveX);

			short int move=defender.getMove(counter);

			moveZ=defender.getZ(move)-1;
			moveY=defender.getY(move)-1;
			moveX=defender.getX(move)-1;

			//cout << "Player O moves [" << moveZ << "][" << moveY << "][" << moveX << "]" << endl;
			if (board[moveZ][moveY][moveX] == ' ')
			{
				board[moveZ][moveY][moveX] = 'O';

				attacker.setMovesMade(counter-1, moveX+1, moveY+1, moveZ+1);

				//pX.notifyMove(moveZ, moveY, moveX);
			}
			else
			{
                cout << "Player O moves [" << moveZ << "][" << moveY << "][" << moveX << "]" << endl;
				cout << "Player O makes an illegal move and loses!" << endl;
				winner = 'X';
				system("PAUSE");
				break;
			}
		}

		//display(board);
		winner = checkWinner(board);
		//{char scs[5]; gets(scs);}
	}

	//display(board);
	if (counter >= 125)
	{
		//cout << "Tie!" << endl;
		//system("PAUSE");
		return 2;
	}
	else
	{
		if (winner == 'X')
		{
			result=0;
			//cout << "Winner is X (ATTACKER)" << endl;
		}
		else
		{
			result=1;
			//cout << "Winner is O (DEFENDER)" << endl;
		}
	}
	//cout << "Counter = " << counter << endl;

	//system("PAUSE");

	return result;
}
