#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//ProtoTypes
//void compress(string&);

int main(int argc, char *argv[])
{
    //Reject commands greater and less than 3///////////////
    if(argc != 3)
        cout << "Usage:./program fileSource fileDestination\n";
    
    //Attempt to compress////////////////////////////////////////////////////////////////
    else
    {
        //Delaration(s)
        fstream inFile;         //Used for source
        fstream inFile2;        //Used for destination
        string fileText = "";   //Used to save string from file
        int counter0 = 0;       //Used to track 0's
        int counter1 = 0;       //Used to track 1's
        char data;              //Used to track chars in file


        //Attempts to open source as read and destination as write/append files
        inFile.open(argv[1], ios::in);
        inFile2.open(argv[2], ios::out | ios::app);
        
        //Inform that the source and/or destination file(s) dont exist and exits program
        if (inFile.fail() || inFile2.fail())
        {
            cout << "File(s) does not exists. Exiting Program.\n";
            inFile.close();
            inFile2.close();
            return 0;
        }

        //State Status and start compress
        cout <<"File compressed.\n";
        
        //Retrieve File info
        while(inFile.good())
        {
            //Retrieve charatcer
            inFile.get(data);

            //Executes if current character is not a 0 or 1
            if (data == ' ' || data == '\n')
            {
                //Executes if the 0's counter is > 15 to compress 0's
                if (counter0 > 15)
                {
                    inFile2 << "-" + to_string(counter0) + "-"; //Writes into appended file
                    counter0 = 0;                               //reset 0's counter
                    fileText.clear();                           //reset string
                    fileText += data;                           //adds current character to string
                }

                //Executes if 1's counter is > 15 to compress 1's
                else if(counter1 > 15)
                {
                    inFile2 << "+" + to_string(counter1) + "+"; //Wrintes into appened file
                    counter1 = 0;                               //reset 1's counter
                    fileText.clear();                           //reset string
                    fileText += data;                           //adds currens character to string
                }
                
                //Nothing to compress
                else
                {
                    counter0 = 0;                               //reset 0's counter
                    counter1 = 0;                               //reset 1's counter
                    inFile2 << fileText;                        //write into appended file
                    fileText.clear();                           //reset string
                    fileText += data;                           //adds current charcter to string
                }
            }

            //Executes if current character is 1
            else if (data == '1')
            {
                //adds character to string if 0's counter is zero
                if(counter0 == 0)
                    fileText += data;
                
                //If 0's counter is > 15 it will compress 0's
                else if (counter0 > 15)
                {
                    inFile2 << "-" + to_string(counter0) + "-";  //compress 0's
                    fileText.clear();                            //reset string
                    counter0 = 0;                                //reset 0's counter
                    fileText += data;                            //add current character to string
                }

                //Nothing to compress and writes the string into appended file
                else
                {
                    inFile2 << fileText;                         //writes string into appended file
                    fileText.clear();                            //clear string
                    counter0 = 0;                                //reset 0's counter
                    fileText += data;                            //add current charater to string
                }
                counter1++;
            }
            
            //Executes if current charater is 0
            else if (data == '0')
            {
                //adds 0 to string if 1's counter is zero
                if (counter1 == 0)
                    fileText+= data;

                //If 1's counter is > 15 compress and right to appended file
                else if (counter1 > 15)
                {
                    inFile2 << "+" + to_string(counter1) + "+";  //compress 1's 
                    fileText.clear();                            //reset string
                    counter1 = 0;                                //reset 1's counter
                    fileText+= data;                             //add current charater to string
                }

                //compress nothing and write string into appened file
                else
                {
                    inFile2 << fileText;                         //write string into appended file
                    fileText.clear();                            //reset string
                    counter1 = 0;                                //reset 1's counter
                    fileText += data;                            //add current charater to string
                }
                counter0++;
            }
        }

        //Close file(s)
        inFile.close();
        inFile2.close();
    }
    return 0;
}