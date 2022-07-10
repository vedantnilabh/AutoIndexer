/**
 * Summer 2022 PA 02 Vedant Nilabh
 */

#include <iostream>
#include <fstream>


#include "AutoIndexer.h"
#include "AutoIndexer.cpp"

int main(int argc, char** argv) {
    // instatiating Autondexer object and calling methods with driver code
    AutoIndexer MyIndexer(argv);
    MyIndexer.PopulateTerms();
    MyIndexer.ReadInBook();
    MyIndexer.Indexterms();
    MyIndexer.WriteToOutput();



    return 0;
}
