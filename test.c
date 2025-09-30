#include "add/add.h"
#include "hello/hello.h"
#include "time/time.h"

int main() {

    struct timeval tv;  // The struct to fill with epoch time
    
    get_time(&tv);

    unsigned char buffer[16];  //8 * 2 = 16 bytes
    for (int i=0;i<16;i++) {
        for (int j=7;j>=0;j--) {
            if ((buffer[i] >> j) &1) {
                print0();
            } else {
                print1();
            }
        }
    }
    printNL();

    return 0;  // Success
}