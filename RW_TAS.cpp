/**
 * @file: Project_03.cpp
 * @author: ahmedesoliman
 * @breif:  This project file implements a test and set lock that is used to
 * synchronize two threads. Test and set lock is a lock that has only two
 * states: 1) available and 2) not available. The lock is initialized to
 * available. The first thread that tries to acquire the lock will succeed and
 * the second thread will block until the first thread releases the lock. The
 * lock is released by the first thread when it finishes its execution. The
 * second thread will then acquire the lock and execute.
 *
 * @version:
 * @date: 12-3-2022
 * @copyright: copyright (c) 2022
 */

#include <iostream>
#include <pthread.h>
#include <string.h>
#include <vector>

using namespace std;

// process control block (pcb)
struct pcb
{
    int pc = 0; // program counter
    bool isCritical = false;
};

// initialize control blocks objects
struct pcb rpcb1;
struct pcb rpcb2;
struct pcb rpcb3;
struct pcb wpcb1;
struct pcb wpcb2;

int rCounter = 0; // counter for readers
int wCounter = 0; // counter for writers

char buffer[25]; // buffer to store data

bool rwlock = false; // target flag
bool lock = false;   // target flag



// implement boolean test and set function
bool test_and_set(bool &target) {
	bool rv = target;
	target = true;
	return rv;
}

// implement test and set waiting fucntion
void TAS_wait(bool &target) {
	while (test_and_set(target));
}

// implement test and set signal function
void TAS_signal(bool &target) { target = false; }

// implement panic function
void panic(string msg)
{
    cout << msg << endl;
    // exit(1);
}

// implement iscritical function
bool isCritical(struct pcb *pcb)
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
// check if the program is in critical section
void checkCritical(int &rcount, int &wCount)
{
    string msg = "!!!PANIC!!!";

    if (rcount > 3 || wCount > 1)
        cout << "Readers in CS = " << rcount << " && Writers in CS = " << wCount << endl;

    // check if 2 or more functions are in critical section
    if (isCritical(&wpcb1) && isCritical(&wpcb2))
    {
        panic(msg);
        cout << "Error @ W1 && W2" << endl;
    }
    // check if any writer is in critical section and any reader is in critical
    // section
    else if (isCritical(&wpcb1) && isCritical(&rpcb1))
    {
        panic(msg);
        cout << "Error @ W1 && R1" << endl;
    }
    // check if any writer is in critical section and any reader is in critical
    // section&
    else if (isCritical(&wpcb1) && isCritical(&rpcb2))
    {
        panic(msg);
        cout << "Error @ W1 && R2 " << endl;
    } // check if any writer is in critical section and any reader is in critical
      // section
    else if (isCritical(&wpcb1) && isCritical(&rpcb3))
    {
        panic(msg);
        cout << "Error @ W1 && R3" << endl;
    } // check if any writer is in critical section and any reader is in critical
      // section
    else if (isCritical(&wpcb2) && isCritical(&rpcb1))
    {
        panic(msg);
        cout << "Error @ W2 && R1" << endl;
    } // check if any writer is in critical section and any reader is in critical
      // section
    else if (isCritical(&wpcb2) && isCritical(&rpcb2))
    {
        panic(msg);
        cout << "Error @ W2 && R2" << endl;
    } // check if any writer is in critical section and any reader is in critical
      // section
    else if (isCritical(&wpcb2) && isCritical(&rpcb3))
    {
        panic(msg);
        cout << "Error @ W2 && R3" << endl;
    } // check if any writer is in critical section and any reader is in critical
      // section
    else if (isCritical(&rpcb1) && isCritical(&rpcb2) && isCritical(&rpcb3))
    {
        panic(msg);
        cout << "Error @ R1 && R2 && R3" << endl;
    } // check if any writer is in critical section and any reader is in critical
      // section
}


// writer 1
void w1(struct pcb *pcb)
{
    switch (pcb->pc)
    {
    case 0:
        TAS_wait(rwlock);
        pcb->pc++;
        break;

    case 1: // critical section case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        buffer[rand() % 25] = 'A' + rand() % 26;
        cout << "Writer 1 inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 2:
        TAS_signal(rwlock);
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
        TAS_wait(rwlock);
        pcb->pc++;
        break;

    case 1: // critical section case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        buffer[rand() % 25] = 'A' + rand() % 26;
        cout << "Writer 2 inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 2:
        TAS_signal(rwlock);
        pcb->pc = 0;
        break;
    }
}

// reader 1
void r1(struct pcb *pcb)
{
    switch (pcb->pc)
    {
    case 0:
        TAS_wait(lock);
        rCounter++;
        pcb->pc++;
        break;

    case 1:
        if (rCounter == 1)
            TAS_wait(rwlock);
        pcb->pc++;
        break;

    case 2:
        TAS_signal(lock);
        pcb->pc++;
        break;

    case 3: // critical case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        cout << "Reader 1 inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 4:
        TAS_wait(lock);
        rCounter--;
        pcb->pc++;
        break;

    case 5:
        if (rCounter == 0)
            TAS_signal(rwlock);
        pcb->pc++;
        break;

    case 6:
        TAS_signal(lock);
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
        TAS_wait(lock);
        rCounter++;
        pcb->pc++;
        break;

    case 1:
        if (rCounter == 1)
            TAS_wait(rwlock);
        pcb->pc++;
        break;

    case 2:
        TAS_signal(lock);
        pcb->pc++;
        break;

    case 3: // critical section case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        cout << "Reader 2 inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 4:
        TAS_wait(lock);
        rCounter--;
        pcb->pc++;
        break;

    case 5:
        if (rCounter == 0)
            TAS_signal(rwlock);
        pcb->pc++;
        break;

    case 6:
        TAS_signal(lock);
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
        TAS_wait(lock);
        rCounter++;
        pcb->pc++;
        break;

    case 1:
        if (rCounter == 1)
            TAS_wait(rwlock);
        pcb->pc++;
        break;

    case 2:
        TAS_signal(lock);
        pcb->pc++;
        break;

    case 3: // critical section case
        pcb->isCritical = true;
        checkCritical(rCounter, wCounter);
        cout << "Reader 3 inside critical section \n";
        pcb->isCritical = false;
        pcb->pc++;
        break;

    case 4:
        TAS_wait(lock);
        rCounter--;
        pcb->pc++;
        break;
    case 5:
        if (rCounter == 0)
            TAS_signal(rwlock);
        pcb->pc++;
        break;
    case 6:
        TAS_signal(lock);
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