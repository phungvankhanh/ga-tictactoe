#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;
#define ARRAY_ROW 125
#define ARRAY_COL 63

int moveCount = 0;
string filename = "chromosome.txt";
string attack = "199#353A";		//attacking chromosome (X)
string defend = "199#111D";		//defending chromosome (O)
short int gameArray[ARRAY_ROW][ARRAY_COL];

class g12
{
	short int moveSet[ARRAY_ROW][ARRAY_COL];//negative values indicate lack of initiation to actual positions
	short int movesMade[125];		   //moves that have been made so far

private:
	char board[DIMENSION][DIMENSION][DIMENSION];
	char xORo;
	string uid;
	

public:
	g12();
	void setUp(char letter);
	void chooseChromosome(char letter);
	void setArray(short int arr[ARRAY_ROW][ARRAY_COL]);
	void readChromosomeFromFile(short int arr1[ARRAY_ROW][ARRAY_COL], string filename, string chromsome);
	void selectMove(int &moveZ, int &moveY, int &moveX);
	void notifyMove(int moveZ, int moveY, int moveX);
	int TestMove(short int move);
	int getX(short int move);
	int getY(short int move);
	int getZ(short int move);
	short int getElement(int row, int col);
	short int getMove(int turn);
	void g12::setMovesMade(int loc, int x, int y, int z);

	string myUID()
	{
		return uid;
	}

};

g12::g12()
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

   chooseChromosome(xORo);
   setArray(gameArray);
   
  
}

void g12::setUp(char letter)
{
	init(board);
	xORo = letter;
	uid = "g12";
}

void g12::chooseChromosome(char letter)
{
	if(letter = 'X')
	{
		readChromosomeFromFile(gameArray, filename, attack);
	}

	else
	{
		readChromosomeFromFile(gameArray, filename, defend);
	}
}

int g12::getX(short int move)
{
	return move/100;
}

int g12::getY(short int move)
{
	return (move%100)/10;
}

int g12::getZ(short int move)
{
	return move%10;
}

short int g12::getElement(int row, int col)
{

	cout<<"In get element, move is "<<moveSet[row][col]<<endl;
	return moveSet[row][col];
}

void g12::setArray(short int arr[ARRAY_ROW][ARRAY_COL])
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

/* Populate the Array */
void g12::readChromosomeFromFile(short int arr1[ARRAY_ROW][ARRAY_COL], string filename, string chromosome)
{

	ifstream file;
	string line;

	file.open(filename);
	if(file.is_open())
	{
		//cout << "file was opened\n";
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


void g12::selectMove(int &moveZ, int &moveY, int &moveX)
{
	moveCount++;
	short int move = getMove(moveCount);
	moveZ = getZ(move)-1;
	moveY = getY(move)-1;
	moveX = getX(move)-1;

	if (board[moveZ][moveY][moveX] == ' ')
	{
		board[moveZ][moveY][moveX] = xORo;
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

void g12::notifyMove(int moveZ, int moveY, int moveX)
{

	moveCount++;

	board[moveZ][moveY][moveX] = (xORo == 'X' ? 'O' : 'X');

	setMovesMade(moveCount-1, moveX+1, moveY+1, moveZ+1);
}

//set moves made
//test move
int g12::TestMove(short int move)
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

short int g12::getMove(int turn)
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
			cout<<"On turn "<<turn<<", accessing element "<<((turn-1)/2)<<endl;
			//system("PAUSE");


			move=getElement(i, ((turn-1)/2));
			cout<<"Move selected is "<<move<<endl;
			//system("PAUSE");
			result=TestMove(move);

			if(result==0)
			{
                cout<<"Found a compatible move, making "<<move<<endl;
				setMovesMade(turn-1, getX(move), getY(move), getZ(move));

				return move;
			}
			else
			{
                cout<<"Move illegal, going down the array."<<endl;
            }
		}
	}

	setMovesMade(turn-1, getX(move), getY(move), getZ(move));
	return move;
}

void g12::setMovesMade(int loc, int x, int y, int z)
{
	cout<<"setting move made array in DEFENDER, element "<<loc<<endl;

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

	cout<<" to "<<result<<endl;

	movesMade[loc]=result;
}

