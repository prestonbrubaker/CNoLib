#include "add/add.h"
#include "hello/hello.h"
#include "time/time.h"
#include "gelb/gelb.h"
#include "web/web.h"




int main() {
    send_message("hello\n", 9043);
    gelb();
    struct timeval tv;  // The struct to fill with epoch time
    unsigned char buffer[16];  //8 * 2 = 16 bytes
    get_time(&tv);

    unsigned char a = 0;
    for (int i=0;i<16;i++) {
        for (int j=7;j>=0;j--) {
            if ((buffer[i] >> j) &1) {
                printChar('1');
                if (i == 10) {
                a += 1<<j;
                }
            } else {
                printChar('0');
                
            }

            
        }
        printChar('\n');
        if (i == 7) {printChar('\n');}
    }
    printNL();


    printChar('h');
    printChar('\n');

    char string[] = "I really like and love \033[35mWilloh\033[0m ";
    for (int i=0;i<40;i++) {
        printChar(string[i]);
    }

    printChar(a);

    printChar('\n');
    hello();
    //printNL();
    

    return 0;

}