
const int DEBUG=0;
const int DIMENSION=5;
const int POP_SIZE=20; //population size
const int ARRAY_COL=63;
const int ARRAY_ROW=125;
int iterationsToRun=100000;
int onIteration=1;
int seedNum=8898;            //seeds the random number generator with that number, good to change when running on
                          //different machines, infact i should allow user input for this...
unsigned int idCount=1;   //to keep track of issued id's

const int winMult=1;
const double lossMult=-0.7;
const double tieMult=0.9;


