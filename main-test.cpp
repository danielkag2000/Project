#include "vars/data_server.h"
#include <iostream>



#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <sstream>
#include <iostream>


using namespace std;

int main() {
    DataTransfer transfer;
    transfer.openDataServer(5400, 10);

    int in = 0;

    cin >> in;
    cout << "hello world -- " << in << endl;
    transfer.openSender(5420, "127.0.0.1");

    string stupid = "/controls/flight/rudder";
    do {
        cin >> in;
        cout << in << endl;
        transfer.setValue(stupid, ((double) in)/ 1000);
        // cout << "stupid value: " << transfer.getValue(stupid) << endl;
        cout << "kaki gadol" << endl;
    } while (in != 0);

    cout << "closing" << endl;
    transfer.closeAll();
    cout << "closed" << endl;
    return 0;
}
