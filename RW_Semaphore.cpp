/*
 * @file: Project_03.cpp
 * @author: ahmedesoliman
 * @breif: This project file implements a binary semaphore that is used to
 * synchronize two threads. Binary semaphore is a semaphore that has only two
 * states: 1) available and 2) not available. The semaphore is initialized to
 * available. The first thread that tries to acquire the semaphore will succeed
 * and the second thread will block until the first thread releases the
 * semaphore. The semaphore is released by the first thread when it finishes its
 * execution. The second thread will then acquire the semaphore and execute.
 * @version: 0.1
 * @date: 12-3-2022
 * @copyright: copyright (c) 2022
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

// process control block (pcb)
struct pcb
{
    int pc;          // program counter
    bool isCritical; // flag to check if the program is in critical section
    string id;       // process id assigned by function name
};

// initialize control blocks objects

struct pcb rpcb1 = {0, false, "R1"}; // reader 1 process control block
struct pcb rpcb2 = {0, false, "R2"}; // reader 2 process control block
struct pcb rpcb3 = {0, false, "R3"}; // reader 3 process control block
struct pcb wpcb1 = {0, false, "W1"}; // writer 1 process control block
struct pcb wpcb2 = {0, false, "W2"}; // writer 2 process control block

int rwSem = 1; // semaphore for reader/writer
int rSem = 2;  // semaphore for reader

int rCounter = 0; // counter for readers
int wCounter = 0; // counter for writers

char buffer[25]; // buffer to store data

// implement semaphore wait function
void wait(int &S)
{
    while (S <= 0)
        ; // spin until S > 0
    if (S > 0)
        S--;
}

// implement semaphore signal function
void signal(int &S) { S++; } // increment S

// implement panic function
void panic(string msg)
{
    cout << msg << endl;
    // exit(1);
}

// implement iscritical function
bool isCritical(struct pcb *pcb) // check if the program is in critical section
{
    if (pcb->isCritical == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// implement report process function
void reportProcess(struct pcb *pcb)
{
    if (isCritical(pcb)) // check if the program is in critical section
    {
        cout << "Process " << pcb->id << " is in case: " << pcb->pc << endl;
        cout << "Process " << pcb->id << " is in critical section " << isCritical(pcb) << endl;
    }
}

// check if the program is in critical section
void checkCritical(int &rcount, int &wCount)
{
    string msg = "!!!PANIC!!!";
    // check if more than 2 reader and 1 writer are in critical section
    if (rcount > 2 && wCount > 1)
    {
        panic(msg);
        reportProcess(&rpcb1);
        reportProcess(&rpcb2);
        reportProcess(&rpcb3);
        reportProcess(&wpcb1);
        reportProcess(&wpcb2);
    }
    // check if more than 1 writer are in critical section
    else if (wCount > 1)
    {
        panic(msg);
        reportProcess(&rpcb1);
        reportProcess(&rpcb2);
        reportProcess(&rpcb3);
        reportProcess(&wpcb1);
        reportProcess(&wpcb2);
    }
}

// writer 1
void w1(struct pcb *pcb)
{
    switch (pcb->pc)
    {
    case 0:
        wait(rwSem);
        cout << pcb->id << " is entering critical section \n";
        pcb->pc++;
        break;

    case 1: // critical section case
        wCounter++;
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        buffer[rand() % 25] = 'A' + rand() % 26;
        cout << pcb->id << " is inside critical section \n";
        wCounter--;
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 2:
        signal(rwSem);
        cout << pcb->id << " is existing critical section \n";
        pcb->pc = 0;
        break;
    }
}
// writer 2
void w2(struct pcb *pcb)
{
    switch (pcb->pc)
    {

    case 0:
        wait(rwSem);
        pcb->pc++;
        cout << pcb->id << " is entering critical section \n";
        break;

    case 1: // critical section case
        wCounter++;
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        buffer[rand() % 25] = 'A' + rand() % 26;
        cout << pcb->id << " is inside critical section \n";
        wCounter--;
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 2:
        signal(rwSem);
        cout << pcb->id << " is existing critical section \n";
        pcb->pc = 0;
        break;
    }
}

// reader 1
void r1(struct pcb *pcb)
{
    switch (pcb->pc)
    {
    case 0: // cout "reader is entry section"
        wait(rSem);
        rCounter++;
        cout << pcb->id << " is entering critical section \n";
        pcb->pc++;
        break;

    case 1:
        if (rCounter == 1)
            wait(rwSem);
        pcb->pc++;
        break;

    case 2:
        signal(rSem);
        pcb->pc++;
        break;

    case 3: // critical case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        cout << pcb->id << " is inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 4:
        wait(rSem);
        rCounter--;
        cout << pcb->id << " is leaving critical section \n";
        pcb->pc++;
        break;

    case 5:
        if (rCounter == 0)
            signal(rwSem);
        pcb->pc++;
        break;

    case 6:
        signal(rSem);
        cout << pcb->id << " is existing critical section \n";
        pcb->pc = 0;
        break;
    }
}
// reader 2
void r2(struct pcb *pcb)
{
    switch (pcb->pc)
    {
    case 0:
        wait(rSem);
        rCounter++;
        cout << pcb->id << " is entering critical section \n";
        pcb->pc++;
        break;

    case 1:
        if (rCounter == 1)
            wait(rwSem);
        pcb->pc++;
        break;

    case 2:
        signal(rSem);
        pcb->pc++;
        break;

    case 3: // critical section case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        cout << pcb->id << " is inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 4:
        wait(rSem);
        rCounter--;
        cout << pcb->id << " is leaving critical section \n";
        pcb->pc++;
        break;

    case 5:
        if (rCounter == 0)
            signal(rwSem);
        pcb->pc++;
        break;

    case 6:
        signal(rSem);
        cout << pcb->id << " is existing critical section \n";
        pcb->pc = 0;
        break;
    }
}
// reader 3
void r3(struct pcb *pcb)
{
    switch (pcb->pc)
    {
    case 0:
        wait(rSem);
        rCounter++;
        cout << pcb->id << " is entering critical section \n";
        pcb->pc++;
        break;

    case 1:
        if (rCounter == 1)
            wait(rwSem);
        pcb->pc++;
        break;

    case 2:
        signal(rSem);
        pcb->pc++;
        break;

    case 3: // critical section case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        cout << pcb->id << " is inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 4:
        wait(rSem);
        rCounter--;
        cout << pcb->id << " is leaving critical section \n";
        pcb->pc++;
        break;
    case 5:
        if (rCounter == 0)
            signal(rwSem);
        pcb->pc++;
        break;
    case 6:
        signal(rSem);
        cout << pcb->id << " is existing critical section \n";
        pcb->pc = 0;
        break;
    }
}

// main function
int main()
{
    // inialize buffer and fill with dots '.'
    for (int i = 0; i < 25; i++)
    {
        buffer[i] = '.';
    }

    // for (;true;)
    for (int x = 0; x < 100; x++)
    {
        int turn = rand() % 5; // random number between 0 and 4

        switch (turn)
        {
        case 0:
            r1(&rpcb1);
            break;
        case 1:
            r2(&rpcb2);
            break;
        case 2:
            r3(&rpcb3);
            break;
        case 3:
            w1(&wpcb1);
            break;
        case 4:
            w2(&wpcb2);
            break;
        }
    }
}