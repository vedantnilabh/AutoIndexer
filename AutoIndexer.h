//
// Created by Vedant Nilabh on 6/13/22.
//

#ifndef INC_22SU_PA02_AUTOINDEXER_H
#define INC_22SU_PA02_AUTOINDEXER_H
#include "DSString.h"
#include "DSVector.h"
#include <fstream>
#include <iostream>
using namespace std;

class AutoIndexer {
public:
    AutoIndexer(char**argv);
    void PopulateTerms();
    void ReadInBook();
    void Indexterms();
    void WriteToOutput();

private:
    DSVector<DSString> termVec;
    DSVector<DSString> contentVec;
    DSVector<DSVector<DSString>> termsEachPage;
    DSVector<int> pageVec;
    char* termsFilePath;
    char* bookFilePath;
    char* outputFilePath;
};


#endif //INC_22SU_PA02_AUTOINDEXER_H
