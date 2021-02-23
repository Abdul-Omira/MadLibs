#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;
/**
 * @brief qMain
 * @return
 */
int main() {

    // Declare all main variables
    ifstream file;
    string fileName;
    bool repeat = true;
    int placeHoldersReplaced = 0;
    int totalplaceHoldersReplaced = 0;
    int MadLibstories = 0 ;



    cout << "Welcome to CS 106B Mad Libs!" << endl;

    while(repeat){
    // The opening text
    cout << "I will ask you to provide various words" << endl;
    cout << "and phrases to fill in a story."<<endl ;
    cout << "At the end, I will display your story to you." << endl;
    cout << "Mad Lib input file?";

    // Get the Story file name.

    getLine(cin, fileName);

    file.open(fileName);

   // Check if file exiset.

    while (file.fail()) {
        cout << "Unable to open that file.  Try again." << endl;
        cout << "Mad Lib input file?";
        getLine(cin, fileName);
        file.open(fileName); // open the file and get it ready to process.
    }

   // Declare the main story string.
    string allLines;
    string line;
    // While loop to check all the lines in the story.
    while(getline(file, line )) {

    // While loop to check all the place holders in the story.

    while(line.find('<') != -1 && line.find('>') != -1){
    // Check the condition if I have < or > but as a part of the text, (not part of the place holders).
    if (line.find('<') != -1) {
        if (line.find('>') != -1) {
            int start = line.find('<'); // storing the first cha index value.
            int end = line.find('>'); // storing the last cha index value.
            string placeHolder = line.substr(start +1,end - start-1); // storing the placeholder and convert it from index value.
            string placeholderLC = toLowerCase(placeHolder); // turning into lowercase
            string newPlaceHolder; // Declare the string that will store the user input.
/*
 * Check for vowels.
 * Create a dinamic quastion to replace the placeholder and store it in a new place holder.
 * Add the counter for the Place Holders Replaced for the same story.
 * Add the counter for the Place Holders Replaced for all the stories.
*/
            if ((placeholderLC[0] == 'a') || (placeholderLC[0] == 'e') || (placeholderLC[0] == 'i') || (placeholderLC[0] == 'o') || (placeholderLC[0] == 'u') ){
                cout << "Please type an "<< placeholderLC << ":" ;
                getLine(cin,newPlaceHolder);
                placeHoldersReplaced +=1;
                totalplaceHoldersReplaced +=1;
            } else {
                cout << "Please type a "<< placeholderLC << ":" ;
                getLine(cin,newPlaceHolder);
                placeHoldersReplaced +=1;
                totalplaceHoldersReplaced +=1;
            }

            line.replace (start ,end - start+1, newPlaceHolder); // replace the place holders with the user entry.


        }
    } else {
        break;
    }

  }
    allLines += line + '\n'; // add the procesed line to the main final story.

}
// printing the resultes.
cout<<endl;
cout << "Your Mad Lib story:" << endl;
cout << allLines << endl;
MadLibstories += 1;
cout <<"(" << placeHoldersReplaced << ")" << "  placeholder(s) replaced." << endl;
cout << "Do another Mad Lib (Y/N)?" << endl;
string answer;
// ask the user if he wants to do another story.
if (getYesOrNo(answer,"Do another Mad Lib (Y/N)?")){
    // clearing the first story variables.
    placeHoldersReplaced = 0;
    fileName.clear();
    line.clear();
    allLines.clear();
    file.close();
    repeat = true;
} else {
    repeat = false;
    //Displaying the final results.
    double placeHoldersPS ;
    placeHoldersPS = totalplaceHoldersReplaced / MadLibstories;
    cout<<"Mad Lib stories you created: " << MadLibstories << endl;
    cout << "Total placeholders replaced: " << totalplaceHoldersReplaced << '(' << fixed << setprecision(1) << placeHoldersPS << " per story )";

}

}

    return 0;
}
