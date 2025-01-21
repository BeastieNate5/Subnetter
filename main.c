#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef struct CIDR {
    uint8_t oct1;
    uint8_t oct2;
    uint8_t oct3;
    uint8_t oct4;
} CIDR;

CIDR convertStringToIP(char* ip) {
    int ipLen = strlen(ip);
    char currentOctet[4];
    CIDR IP;
    int octetIndex = 0;
    int octetNum = 0;

    for (int i = 0; i < ipLen; i++) {
        if ( *(ip+i) == '.') {
            octetIndex = 0;

            *(((char*)&IP) + (octetNum)) = (uint8_t)atoi(currentOctet);

            octetNum += 1;
            memset(currentOctet, 0, 4);
            continue;
        }

        currentOctet[octetIndex] = *(ip+i);
        octetIndex += 1;
    }

    // To get the last octet
    *(((char*)&IP) + (octetNum)) = (uint8_t)atoi(currentOctet);
    return IP;
}

CIDR createSubnetmask(int prefix) {
    CIDR subnetmask;
    for (int i = 0; i < prefix/8; i++) {
        *((char*)&subnetmask+i) = 255;
    }

    int remiander = prefix % 8;

    for (int i = 0; i < remiander; i++) {
        *((char*)&subnetmask + prefix/8) |= (1 << 7 - i);
    }

    return subnetmask;
}

CIDR getNetworkName(CIDR* givenAddr, CIDR* subnetmask) {
    CIDR networkName = {
        givenAddr->oct1 & subnetmask->oct1,
        givenAddr->oct2 & subnetmask->oct2,
        givenAddr->oct3 & subnetmask->oct3,
        givenAddr->oct4 & subnetmask->oct4
    };

    return networkName;
}

uint8_t getMagicNumber(CIDR* subnetmask) {
    int leadingOctetOffset = (subnetmask->oct1 + subnetmask->oct2 + subnetmask->oct3 + subnetmask->oct4) / 255 - 1;
    uint8_t magicNum;

    for (int i = 0; i < 8; i++) {
        if ( (*((char*)&subnetmask + leadingOctetOffset) >> i & 1) == 1) {
            magicNum = pow(2,i);
            break;
        };
    }

    return magicNum;
}

void generateReport(CIDR networkName, CIDR* subnetmask, uint8_t prefix) {
    unsigned int maxHosts = pow(2, 32 - prefix) - 2;

    printf("Max Hosts: %u\n", maxHosts);
    
    *((uint32_t*)&networkName) += 1;

    printf("Last: %u.%u.%u.%u\n", networkName.oct1, networkName.oct2, networkName.oct3, networkName.oct4);

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
    
    CIDR givenIP = convertStringToIP(ipArg);
    CIDR subnet = createSubnetmask(prefix);
    CIDR networkName = getNetworkName(&givenIP, &subnet);
    
    generateReport(networkName, &subnet, prefix);
    

    return 0;
}