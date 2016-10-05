//Scott Corcoran
//10/3/16
//This program is passed a 2d vector
//the inner vector is ints and will only be 3 in length
//the program represents paths from towns on the left to towns on the right across a river
//taking the path of the highest cost

//Restrictions for answer
//no two paths start or end at the came town
//they cant cross one another 




////////////////////////////////////////////////////////////////////////////////////////
#ifndef BUILD_H_INCLUDED
#define BUILD_H_INCLUDED

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using Bridge = vector<int>; //this is to save me programming time?

////////////////////////////////////////////////////////////////////////////////////////
//This section is to find if the path is legal
//So it abides by the restrictions given above
int checkIfLegal(vector<Bridge> tempOption, vector<int> newOption)
{
	for (int i = 0; i < tempOption.size(); i++)
	{
		//making sure they are not in the same town
		if (tempOption[i][0] == newOption[0] || tempOption[i][1] == newOption[1])
		{
			return 0;
		}	
		
		//making sure that do not cross one another
		if ((tempOption[i][0] > newOption[0] && tempOption[i][1] < newOption[1]) || (tempOption[i][0] < newOption[0] && tempOption[i][1] > newOption[1]))
		{
			return 0;
		}

	}

	return 1;
}

////////////////////////////////////////////////////////////////////////////////////////
//This is checking if the new option 
//that has been generated is better than the prior saved one
bool checktotal(vector<Bridge> tempOption, vector<Bridge> bestOption)
{

	int originalTotal = 0;
	int	newTotal = 0;
	for (int i = 0; i < bestOption.size(); i++)
	{
		originalTotal += bestOption[i][2];
		newTotal += tempOption[i][2];
	}
	if (originalTotal > newTotal)
	{
		return 0;
	}
	return 1;
}

////////////////////////////////////////////////////////////////////////////////////////
//This is to zero out the prior contents of my temp vector
//We reuse the area between passes so we 
//want it to not be able to throw out bridge options
//because garbage is left in them
vector<Bridge> zeroOutTemp(vector<Bridge> tempOption)
{
	for (int i = 0; i < tempOption.size(); i++)
	{
		//I chose -1 because it is never passed unlike 0 which is
		//a 0 would cause it to say we already have a site starting from there
		tempOption[i][0] = -1; 
		tempOption[i][1] = -1;
		tempOption[i][2] = 0;
	}

	return tempOption;
}
////////////////////////////////////////////////////////////////////////////////////////
//This is out main
//take in data from the client
//we will be copying it in pieces into the NewOption
//seeing if it could be added to our current list,
//if it can we add it to are temp
//Once we make it through we compare our temp to our best result
//repeat process several times till we are sure
int build(int w, int e, const vector<Bridge> & bridges) {

	int numberOfOptions = bridges.size(); 
	vector<Bridge> bestOption(numberOfOptions, vector<int>(3, 0));

	//Each option is three parts
	//left side right side and value 
	vector<int> newOption(3); 

	vector<Bridge> tempOption(numberOfOptions,vector<int>(3 ,-1)); //fill with -1's

	for (int i = 0; i < numberOfOptions; i++)
	{
		//put 0's in so if a value is not entered there is not value there not 
		//a value there to throw off the total
		tempOption[i][2] = 0; 
	}

	//check for empty bridge (tricky Chappell)
	if (bridges.size() == 0)
		return 0;


//outer loop
	for (int i = 0; i < numberOfOptions; i++)
	{
		//inner loop
		for (int j = 0; j < numberOfOptions; j++)
		{
			if ((j+i) < numberOfOptions)
			{
				newOption[0] = bridges[j + i][0];
				newOption[1] = bridges[j + i][1];
				newOption[2] = bridges[j + i][2];
			}
			else
			{
				newOption[0] = bridges[(j + i) - numberOfOptions][0];
				newOption[1] = bridges[(j + i) - numberOfOptions][1];
				newOption[2] = bridges[(j + i) - numberOfOptions][2];
			}
			if (checkIfLegal(tempOption,newOption) == 1)
			{
				tempOption[j][0] = newOption[0];
				tempOption[j][1] = newOption[1];
				tempOption[j][2] = newOption[2];

			}
		}
		if (checktotal(tempOption, bestOption))
		{
			int Total = 0;
			for (int i = 0; i < tempOption.size(); i++)
			{
				Total += bestOption[i][2];
			}
			bestOption = tempOption;
		}//end inner loop 
		tempOption = zeroOutTemp(tempOption); //zero our tempotion for another pass
	}//end outer loop

	//This calc and stores the final value to be sent off to the client
	int storageOFTotal = 0;
	for (int i = 0; i < bestOption.size(); i++)
	{
		storageOFTotal += bestOption[i][2];
	}

	return storageOFTotal;
}


#endif
