void throwCase()
{
    if (isCritical(&rpcb1) && isCritical(&rpcb2))
        cout << "reader 1 && reader 2 in CS \n";

    if (isCritical(&rpcb1) && isCritical(&rpcb3))
        cout << "reader 1 && reader 3 in CS \n";

    if (isCritical(&rpcb1) && isCritical(&rpcb2) && isCritical(&rpcb2))
        cout << "reader 1 && reader 2 && reader 3 in CS \n";

    if (isCritical(&rpcb2) && isCritical(&rpcb3))
        cout << "reader 2 && reader 3 in CS \n";

    if (isCritical(&wpcb1) && isCritical(&wpcb2))
        cout << "reader 1 && reader 2 && reader 3 in CS \n";

    if (isCritical(&wpcb1) && isCritical(&wpcb2))
        cout << "reader 1 && reader 2 && reader 3 in CS \n";

    if (isCritical(&wpcb1) && isCritical(&rpcb1))
        cout << "writer 1 && reader 2 && reader 1 in CS \n";

    if (isCritical(&wpcb1) && isCritical(&rpcb2))
        cout << "writer 1 && reader 2 && reader 2 in CS \n";

    if (isCritical(&wpcb1) && isCritical(&rpcb3))
        cout << "writer 1 && reader 3 in CS \n";

    if (isCritical(&wpcb2) && isCritical(&rpcb1))
        cout << "writer 2 && reader 1 in CS \n";

    if (isCritical(&wpcb2) && isCritical(&rpcb2))
        cout << "writer 2 && reader 2 in CS \n";

    if (isCritical(&wpcb2) && isCritical(&rpcb3))
        cout << "writer 2 && reader 3 in CS \n";

    if (isCritical(&wpcb2) && isCritical(&rpcb2))
        cout << "writer 2 && reader 2 in CS \n";

    // check if 2 or more functions are in critical section
    if (isCritical(&wpcb1) && isCritical(&wpcb2))
    {
        panic(msg);
        cout << "Error @ W1 && W2" << endl;
    }
    // check if any writer is in critical section and any reader is in critical
    // section
    if (isCritical(&wpcb1) && isCritical(&rpcb1))
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