#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define DISPLAY_CIDR(cidr) \
    printf("%u.%u.%u.%u\n", *((uint8_t*)&cidr+3), *((uint8_t*)&cidr+2), *((uint8_t*)&cidr+1), *((uint8_t*)&cidr));


typedef uint32_t CIDR;

typedef struct CIDRf {
    uint8_t oct1;
    uint8_t oct2;
    uint8_t oct3;
    uint8_t oct4;
} CIDRf;

void displayCIDR(CIDR cidr) {
    printf("%u.%u.%u.%u\n", *((uint8_t*)&cidr+3), *((uint8_t*)&cidr+2), *((uint8_t*)&cidr+1), *((uint8_t*)&cidr));
}

CIDR convertToCIDR(char* ip) {
        int ipLen = strlen(ip);
    char currentOctet[4];
    CIDR IP;
    int octetIndex = 0;
    int octetNum = 0;

    for (int i = 0; i < ipLen; i++) {
        if ( *(ip+i) == '.') {
            octetIndex = 0;

            *(((char*)&IP) + (3 - octetNum)) = (uint8_t)atoi(currentOctet);

            octetNum += 1;
            memset(currentOctet, 0, 4);
            continue;
        }

        currentOctet[octetIndex] = *(ip+i);
        octetIndex += 1;
    }

    // To get the last octet
    *((char*)&IP) = (uint8_t)atoi(currentOctet);
    return IP;
}


CIDR createSubnetmask(uint8_t prefix) {
    CIDR subnetmask = 0;
    
    for (int i = 0; i < prefix; i++) {
        subnetmask |= (1 << 31 - i);
    }

    return subnetmask;
}

void generateReport(CIDR* networkName, CIDR* subnetmask, uint8_t prefix, unsigned int amount) {
    unsigned int maxHosts = pow(2, 32 - prefix) - 2;

    for (int i = 0; i < amount; i++) {
        printf("NN   | "); displayCIDR((*networkName) + (maxHosts+2) * i);
        printf("1st  | "); displayCIDR(*(networkName) + 1 + (maxHosts+2) * i);
        printf("Last | "); displayCIDR(*(networkName) + maxHosts + (maxHosts+2) * i);
        printf("\n");
    }
}

int vaildateInput(char* givenIP) {
    int ipLen = strlen(givenIP);
}

int main(int agrc, char** argv) {
    if (agrc != 4) {
        printf("<TOOLNAME> <IP> <CIDR Prefix> <Network amount>");
    }

    char* ipArg = *(argv+1);
    char* prefixArg = *(argv+2);
    char* amountArg = *(argv+3);

    uint8_t prefix = atoi(prefixArg);
    int amount = atoi(amountArg);
    
    if (prefix == 0) {
        printf("Invalid prefix");
        return 1;
    }

    CIDR givenIP = convertToCIDR(ipArg);    CIDR subnetmask = createSubnetmask(prefix);
    CIDR networkName = givenIP & subnetmask;
    
    generateReport(&networkName, &subnetmask, prefix, amount);
    
    

    return 0;
}