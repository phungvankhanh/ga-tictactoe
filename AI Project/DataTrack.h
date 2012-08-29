struct DataTrack
{
       unsigned int lifeWins;
       unsigned int lifeLosses;
       unsigned int lifeDraws;
       unsigned int birth;    //iteration #
       unsigned int death;
       unsigned int parent1;  //parent id#'s
       unsigned int parent2;
       unsigned int numReproduced;//How many times this chromosome got "lucky"
       unsigned int survivalCount;//how many iterations this move set survived 
};
