//
// Created by Maksym Selishchev on 07/01/2024.
//

#ifndef SMARTPOINTERS_CREFCOUNTER_H
#define SMARTPOINTERS_CREFCOUNTER_H


class CRefCounter {
public:
    CRefCounter() { i_count; }
    int iAdd() { return(++i_count); }
    int iDec() { return(--i_count); };
    int iGet() { return(i_count); }
private:
    int i_count;
};


#endif //SMARTPOINTERS_CREFCOUNTER_H
