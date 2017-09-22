#include <iostream>
#include <fstream>

#ifndef _READ_BK_H
#define _READ_BK_H

template <class T>
class read_bk
{
    public:    
        // Variables
        int nNodes = 0;
        int nEdges = 0;
        // Vector of weights per node
        T *f;
        // Array of weights, size = nNodes * nNodes
        T **w;

        // Methods
        void init_graph(int numberNodes, int numberEdges);
        void free_memory();
        bool readFile(char* fileName);

        read_bk(char* filename);
        
        ~read_bk();
        
};
#endif
