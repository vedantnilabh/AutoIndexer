//
// Created by Vedant Nilabh on 6/13/22.
//

#include "AutoIndexer.h"

void AutoIndexer::PopulateTerms() {
    // opening terms file
    ifstream fileTerms(termsFilePath);
    if(!fileTerms.is_open()){
        cout << "terms file is not open" << endl;
        exit(1);
    }
    char buffer[501];
    while(fileTerms.getline(buffer, 500)){
        DSString term(buffer);
        term.toLower(); // lowercase
        // pushing term to termVec
        termVec.pushBack(term);
    }
    // Sorting termVec to make outputting easier
    termVec.Sort();
    fileTerms.close();
}

void AutoIndexer::ReadInBook() {
    // Book File
    ifstream fileBook(bookFilePath);
    if(!fileBook.is_open()){
        cout << "book file is not open" << endl;
        exit(1);
    }
    // We are ensuring that pageVec and ContentVec are parallel, meaning thet are the same size, as they correspond
    char buffer[500];
    int currentLine = 0;
    while(fileBook.getline(buffer, 500)){
        if(buffer[0] == '<'){
            currentLine = 0; // this checks that we are reading in page Numbers or Content
            // indicates a new page
            DSString pageNum(buffer);
            if(pageNum != DSString("<-1>")) { // checking if we have reached end of file
                pageNum.RemovePunct(); // removes brackets
                int page = atoi(pageNum.c_str());
                // pushing pageNum to pageVec
                pageVec.pushBack(page);
                currentLine++;
                continue;
            }

        }

        else if(currentLine == 1) { // reading in first line of Content
            DSString content(buffer);
            content.toLower();
            contentVec.pushBack(content);
            currentLine++;
            continue;
        }

        else if(currentLine != 1){ // edge case because we need to read across lines
            DSString content(buffer);
            content.AddChar(' ', 0); // adding space at beginning of read in line
            content.toLower();
            // using += to concatenate with other page content
            DSString oldContent(contentVec[contentVec.getSize() - 1]);
            oldContent += content;
            contentVec[contentVec.getSize() - 1] = oldContent;
            currentLine++;
            continue;
        }



    }
    fileBook.close();
}

void AutoIndexer::Indexterms() {
    for (int i = 0; i < contentVec.getSize(); i++) {
        // creating vector of terms for each Page
        DSVector<DSString> termPageVec;
        for (int j = 0; j < termVec.getSize(); j++) {
            // is a keyword in some page's content
            if (contentVec[i].find(termVec[j]) != -1) {
                // push if it is
                termPageVec.pushBack(termVec[j]);
            }
        }
        // pushing the vector for an entire page to another Vector of Vectors
        termsEachPage.pushBack(termPageVec);
    }
}
void AutoIndexer::WriteToOutput() {
    // opening output file to write to
    ofstream fileWrite(outputFilePath);
    if(!fileWrite.is_open()){
        cout << "write file is not open" << endl;
        exit(1);
    }
    // this vector contains unique starting characters so we know when to add the [char]
    DSVector<char> startOfFoundWords;
    // null term - ascii of 0, will be different from all other starting chars in file
    startOfFoundWords.pushBack('\0');
    for(int i = 0; i < termVec.getSize(); i++){
        int countPage = 0; // number of pages a term appears on
        int countChar = 0; // check if we need to wrap text
        for(int j = 0; j < pageVec.getSize(); j++) {
            for(int k = 0; k < termsEachPage[j].getSize(); k++) {
                if(countPage == 0 && termVec[i] == termsEachPage[j][k]) { // first page it appears on, found in termsEachPage
                    if(startOfFoundWords[startOfFoundWords.getSize() - 1] != termVec[i][0]) { // checking last char of Vector
                        fileWrite << endl;
                        char firstChar = std::toupper(termVec[i][0]);
                        fileWrite << "[" << firstChar << "]" << endl;
                        startOfFoundWords.pushBack(termVec[i][0]);
                    }
                    else {
                        fileWrite << endl;
                    }
                    // term to output with page number
                    fileWrite << termsEachPage[j][k] << ":" << " " << pageVec[j];
                    countPage++;
                    int len = termsEachPage[j][k].getLength() + 1 + 1 + 1;
                    countChar += len;
                    if(countChar >= 60){
                        // do we need to wrap text
                        fileWrite << endl;
                        fileWrite << "    ";
                    }
                }
                else if(termVec[i] == termsEachPage[j][k]){
                    // means that word is already in output file, just adding page number
                    fileWrite << "," << " " << pageVec[j];
                    int len = pageVec[j] + 2;
                    countPage++;
                    countChar += len;
                    if(countChar >= 60){
                        // wrap text
                        fileWrite << endl;
                        fileWrite << "    ";
                    }
                }
            }
        }
    }
    fileWrite.close();
}

AutoIndexer::AutoIndexer(char* argv[]) {
    // constructor that takes in argv and assigns file path data members
    this->bookFilePath = argv[1];
    this->termsFilePath = argv[2];
    this->outputFilePath = argv[3];

}


