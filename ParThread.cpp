#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<pthread.h>

using namespace std;

//Prototype(s)
int splitFile(vector<string> &, string &);
void compress(string &);

struct thread_data {
	int thread_id;
	string index;
	string outputFileName;
};

// function run by pthreas
void *tFun(void *thread_arg)
{
	// define our received data to be a struct
	struct thread_data *received_data;

	// assign the the value from the argument passed in
	received_data = (struct thread_data *) thread_arg;

	// set the output name and the index string accordingly
	string outputFileName = received_data -> outputFileName;
	string index = received_data -> index;

	// get a reference to the ofstream for the output file
	std::ofstream outputFile;

	// open the output file for appending
	outputFile.open(outputFileName, std::ios_base::app);

	// compress the index
    compress(index);
    
	// print the line followed by a newline to the output file
	outputFile << index;

	outputFile.close();

	// to get rid of warning of non return
	void* status;
	return status;
}

int main(int argc, char* argv[])
{
	//get representations for the commandline args
   	string fileName;
    string outputFileName;

	// get an fstream
	fstream op;

	// open the output file to create it
	op.open(outputFileName, ios::out);

	//close it
	op.close();

	//get the number of args and catch error condition for filenames
    if (argc == 3) {
        fileName = argv[1];
        outputFileName = argv[2];
    }
    else {
        cout << "You must specify an input file name then output file name as commandline args\n";
		return -1;
    }

    //vector to save file split(s)
    vector<string> dummies;

	//print that we are splitting the file
    cout << "Splitting File...\n";
	
	//Call function to split a file into dummies, if error, return -1
	if (splitFile(dummies, fileName) == -1) {
		return -1;
	}

	// print the number of splits
	cout << "Splitting complete...\n"
         << "Number of split(s): " << dummies.size() << endl;

    //Create an array of pthreads and an array of thread data
    pthread_t threads[dummies.size()];
	struct thread_data td[dummies.size()];

	// int used for pthread result
	int res;

	// loop through the array and start a thread and set thread data to pass to tFun
    for(int i = 0; i < dummies.size(); i++)
    {
		// set the id, the index string, and the outputFileName
		td[i].thread_id = i;
		td[i].index = dummies[i];
		td[i].outputFileName = outputFileName;

		// create the thread to compress and output the line
		res = pthread_create(&threads[i], NULL, tFun, (void *)&td[i]);

		// catch error condition
		if (res) {
			cerr << "Issue creating thread\n";
			return -1;
		}
    }

	// define a void pointer for status
	void *status;

	// call join on the threads to wait for execution
    for(int i = 0; i < dummies.size(); i++)
    {
        pthread_join(threads[i], &status);
    }

	// call pthread exit to make sure all threads are cleanly terminated
	pthread_exit(NULL);

	// return 0 for all is well
    return 0;
}

// split file subprogram to split our input file into bits
int splitFile(vector<string> &dummies, string &inputFileName)
{
	// get a fstream to read the file
	fstream myFile;

	// set our variables for reading
	string fileT = "";
	char x;
	string data;

	// open the read file
	myFile.open(inputFileName, ios::in);

	// catch error condition
	if (myFile.fail())
	{
		cerr << "Input File does not exist\n";
		return -1;
    }

	// split the file into sections for compression
	while (myFile.good())
	{
		myFile.get(x);
		if (x == '0' || x == '1')
		{
			fileT += x;
		}

		else if (x == ' ' || x== '\n')
		{
			fileT += x;
			dummies.push_back(fileT);
			fileT.clear();
		}

		else if (myFile.eof())
		{
			//fileT.pop_back();
			fileT+= x;
			dummies.push_back(fileT);
			fileT.clear();
		}
	}

	// close the file
	myFile.close();

	// return 0 for all is well
	return 0;
}

// compression subprogram
void compress(string &index)
{
	string fileText = "";   //Used to save string from file
	string decoy = "";      //
    int counter0 = 0;       //Used to track 0's
    int counter1 = 0;       //Used to track 1's
	for (int i = 0; i != index.size(); i++)
	{
		//Executes if current character is 1
    	if (index[i] == '1')
    	{
			//adds character to string if 0's counter is zero
    	    if(counter0 == 0)
			    fileText += index[i];
	
    	    //If 0's counter is > 15 it will compress 0's
    	    else if (counter0 > 15)
    	    {
    	        decoy += "-" + to_string(counter0) + "-";    //compress 0's
    	        fileText.clear();                            //reset string
    	        counter0 = 0;                                //reset 0's counter
    	    	fileText += index[i];                            //add current character to string
    	    }

    	    //Nothing to compress and writes the string into appended file
    	    else
    	    {
    		    decoy += fileText;                         //writes string into appended file
    	        fileText.clear();                            //clear string
    	        counter0 = 0;                                //reset 0's counter
    	        fileText += index[i];                            //add current charater to string
			}

    		counter1++;

			if(i == index.size() - 1)
			{
				if (counter1 >15)
				{
					decoy += "+" + to_string(counter1) + "+";
					fileText.clear();
					counter1 = 0;
				}

				else
				{
					decoy += fileText;
					fileText.clear();
					counter0 = 0;
					fileText += index[i];
				}
			}
		}

		 //Executes if current charater is 0
        else if (index[i] == '0')
        {
            //adds 0 to string if 1's counter is zero
            if (counter1 == 0)
                fileText+= index[i];
            //If 1's counter is > 15 compress and right to appended file
            else if (counter1 > 15)
            {
                decoy += "+" + to_string(counter1) + "+";  //compress 1's 
                fileText.clear();                            //reset string
                counter1 = 0;                                //reset 1's counter
                fileText += index[i];                             //add current charater to string
            }
            //compress nothing and write string into appened file
            else
            {
                decoy +=  fileText;                         //write string into appended file
                fileText.clear();                            //reset string
                counter1 = 0;                                //reset 1's counter
                fileText += index[i];                            //add current charater to string
            }
            counter0++;

			if(i == index.size() - 1)
			{
				if (counter0 >15)
				{
					decoy += "-" + to_string(counter0) + "-";
					fileText.clear();
					counter0 = 0;
				}

				else
				{
					decoy += fileText;
					fileText.clear();
					counter1 = 0;
					fileText += index[i];
				}
			}
        }
		 //Executes if current character is not a 0 or 1
        else if (index[i] == ' ' || index[i] == '\n')
		{
             //Executes if the 0's counter is > 15 to compress 0's
             if (counter0 > 15)
             {
                 decoy += "-" + to_string(counter0) + "-"; //Writes into appended file
                 counter0 = 0;                               //reset 0's counter
                 fileText.clear();                           //reset string
                 fileText += index[i];                           //adds current character to string
             }
             //Executes if 1's counter is > 15 to compress 1's
             else if(counter1 > 15)
             {
                 decoy += "+" + to_string(counter1) + "+"; //Wrintes into appened file
                 counter1 = 0;                               //reset 1's counter
                 fileText.clear();                           //reset string
                 fileText += index[i];                           //adds currens character to string
             }
             
             //Nothing to compress
             else
             {
                 counter0 = 0;                               //reset 0's counter
                 counter1 = 0;                               //reset 1's counter
				 fileText += index[i];
                 decoy += fileText;                        //write into appended file
                 fileText.clear();                           //reset string
                 //fileText += index[i];                           //adds current charcter to string
             }
		}  
    }

	index = decoy;
}
