#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define DISPLAY_CIDR(cidr) \
    printf("%u.%u.%u.%u\n", *((uint8_t*)&cidr+3), *((uint8_t*)&cidr+2), *((uint8_t*)&cidr+1), *((uint8_t*)&cidr));

typedef uint32_t CIDR;
typedef enum IPClass {
    CLASS_A,
    CLASS_B,
    CLASS_C,
    CLASS_D,
    CLASS_E,
    CLASS_LOOPBACK,
    CLASS_INVALID
} IPClass;

typedef enum IPType {
    PRIVATE,
    PUBLIC,
    LOOPBACK
} IPType;

typedef struct IPinfo {
    CIDR givenIP;
    CIDR networkAddress;
    CIDR subnetmask;
    CIDR firstHost;
    CIDR lastHost;
    uint8_t prefix;
    IPClass ipClass;
    IPType ipType;
} IPinfo;


void displayCIDR(CIDR cidr) {
    printf("%u.%u.%u.%u", *((uint8_t*)&cidr+3), *((uint8_t*)&cidr+2), *((uint8_t*)&cidr+1), *((uint8_t*)&cidr));
}

void setGivenIP(IPinfo* ipInfo, char* ip) {
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
    ipInfo->givenIP = IP;
}


CIDR setSubnetmask(IPinfo* ipInfo, uint8_t prefix) {
    CIDR subnetmask = 0;
    
    for (int i = 0; i < prefix; i++) {
        subnetmask |= (1 << 31 - i);
    }

    ipInfo->subnetmask = subnetmask;
}

void setIPClass(IPinfo* ipInfo) {
    if (ipInfo->givenIP <= 2130706431) {
        ipInfo->ipClass = CLASS_A;
    }
    else if (ipInfo->givenIP <= 2147483647) {
        ipInfo->ipClass = CLASS_LOOPBACK;
    }
    else if (ipInfo->givenIP <= 3221225471) {
        ipInfo->ipClass = CLASS_B;
    }
    else if (ipInfo->givenIP <= 3758096383) {
        ipInfo->ipClass = CLASS_C;
    }
    else if (ipInfo->givenIP <= 4028043263) {
        ipInfo->ipClass = CLASS_D;
    }
    else if (ipInfo->givenIP <= 4294967295) {
        ipInfo->ipClass = CLASS_E;
    }
    else {
        ipInfo->ipClass = CLASS_INVALID;
    }
}

IPType setType(CIDR givenIP) {

}

void generateReport(IPinfo* ipInfo) {
    unsigned int maxHosts = pow(2, 32 - ipInfo->prefix) - 2;

    printf("IP Address: "); displayCIDR(ipInfo->givenIP); printf("\n");
    printf("Network Address: "); displayCIDR(ipInfo->networkAddress); printf("\n");
    printf("Host IP Range: "); displayCIDR(ipInfo->networkAddress+1); printf(" - "); displayCIDR(ipInfo->networkAddress+maxHosts); printf("\n");
    printf("Broadcast Address: "); displayCIDR(ipInfo->networkAddress+maxHosts+1); printf("\n");
    printf("Next Subnet: "); displayCIDR(ipInfo->networkAddress+maxHosts+2); printf("\n");
    printf("IP Class: %d", ipInfo->ipClass);
    printf("IP Type: %d", ipInfo->ipType);
}

int vaildateInput(char* givenIP) {
    int ipLen = strlen(givenIP);
}

int main(int agrc, char** argv) {
    if (agrc != 3) {
        printf("<TOOLNAME> <IP> <CIDR Prefix>");
    }

    char* ipArg = *(argv+1);
    char* prefixArg = *(argv+2);

    uint8_t prefix = atoi(prefixArg);
    
    if (prefix <= 0 || prefix >= 32) {
        printf("Invalid prefix");
        return 1;
    }

    IPinfo ipInfo;

    setGivenIP(&ipInfo, ipArg);    
    setSubnetmask(&ipInfo, prefix);
    setIPClass(&ipInfo);
    ipInfo.networkAddress = ipInfo.givenIP & ipInfo.subnetmask;
    
    generateReport(&ipInfo);
    
    return 0;
}