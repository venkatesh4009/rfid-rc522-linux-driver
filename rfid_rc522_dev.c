#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h> 
#include <arpa/inet.h> 
#include <sys/time.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <math.h> 

enum IO_CMD { 
    READ_CARD = 3, 
    CHANGE_PASSWD = 1, 
    CHANGE_BLOCK = 2, 
    CHANGE_KEY = 5, 
    WRITE_CARD = 4, 
    GET_ID = 6, 
}; 

int main(int argc, char** argv) 
{ 
    int rc522_fd; 
    int i, read_num; 
    char r[256];
    char a[20]; 
    char bufpw1[20] = "PHYTEC_RFID";
    char last_tag[256] = ""; // Variable to store last read RFID tag
    int card1_count = 0, card2_count = 0, card3_count = 0; // Counters for each card
    
    // Actual IDs of RFID1, RFID2, and RFID3
    char actual_id_rfid1[] = "\x50\x48\x59\x54\x45\x43\x5F\x52\x46\x49\x44\x5F\x52\x43\x35\x32"; // Provided RFID1 ID
    char actual_id_rfid2[] = "\x50\x48\x59\x54\x45\x43\x5F\x52\x46\x49\x44\x00\x00\x00\x00\x00"; // Provided RFID2 ID
    char actual_id_rfid3[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; // Provided RFID3 ID
    
    printf("test: rc522 %s %s\n", __DATE__, __TIME__); 
    printf("test: before open rc522_fd\n"); 
    rc522_fd = open("/dev/rfid_rc522_dev", O_RDWR); 
    printf("test: rc522_fd=%d\n", rc522_fd); 
    if(rc522_fd == -1) 
    { 
        printf("test: Error Opening rc522\n"); 
        return(-1); 
    } 
    printf("test: wait 01\n"); 
    sleep(1);                 //wait 
    printf("test: wait 02\n"); 

    while(1) {
        read_num = read(rc522_fd, r, sizeof(r)); // Read RFID card value
        if(read_num > 0) { 
            if (strcmp(r, last_tag) == 0) {
                // If the same tag is detected twice, print the appropriate message
                if (strcmp(r, actual_id_rfid1) == 0 && card1_count == 1) {
                    printf("*** PHYTEC RFID_RC522_01 *** \n");
                    card1_count = 0; // Reset the counter
                } else if (strcmp(r, actual_id_rfid2) == 0 && card2_count == 1) {
                    printf("*** PHYTEC RFID_RC522_02 *** \n");
                    card2_count = 0; // Reset the counter
                } else if (strcmp(r, actual_id_rfid3) == 0 && card3_count == 1) {
                    printf("*** PHYTEC RFID_RC522_03 *** \n");
                    card3_count = 0; // Reset the counter
                }
            } else {
                printf("Read RFID_RC522 card ID: ");
                for(int i = 0; i < read_num; i++) {
                    printf("[0x%.2X] ", r[i]);
                }
                printf("\n");
                strcpy(last_tag, r); // Update last read RFID tag
                
                // Increment counter for the detected card
                if (strcmp(r, actual_id_rfid1) == 0) {
                    if (card1_count == 0) {
                        card1_count++;
                    } else {
                        card1_count = 2; // Set the count to 2 for the first read of RFID1
                    }
                } else if (strcmp(r, actual_id_rfid2) == 0) {
                    card2_count++;
                } else if (strcmp(r, actual_id_rfid3) == 0) {
                    card3_count++;
                }
            }
        } else {
            printf("No data read.\n");
        }
        sleep(1);
    }

    return 0; 
} 

