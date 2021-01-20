#include <stdio.h>
#include <stdlib.h>

int main(int args, char *argv[]) {
    if(args == 26) {
        
        int this[25];
        for(int i = 0; i < 25; i++) {
            sscanf(argv[i+1], "%d", &this[i]);
        }

        if(this[0] != 114) {printf("%d invalid\n", this[0]); return 1;}
		if(this[1] != 49) {printf("%d invalid\n", this[1]); return 1;}
		if(this[2] != 103) {printf("%d invalid\n", this[2]); return 1;}
		if(this[3] != 104) {printf("%d invalid\n", this[3]); return 1;}
		if(this[4] != 116) {printf("%d invalid\n", this[4]); return 1;}
		if(this[5] != 95) {printf("%d invalid\n", this[5]); return 1;}
		if(this[6] != 104) {printf("%d invalid\n", this[6]); return 1;}
		if(this[7] != 51) {printf("%d invalid\n", this[7]); return 1;}
		if(this[8] != 114) {printf("%d invalid\n", this[8]); return 1;}
		if(this[9] != 51) {printf("%d invalid\n", this[9]); return 1;}
		if(this[10] != 95) {printf("%d invalid\n", this[10]); return 1;}
		if(this[11] != 116) {printf("%d invalid\n", this[11]); return 1;}
		if(this[12] != 104) {printf("%d invalid\n", this[12]); return 1;}
		if(this[13] != 101) {printf("%d invalid\n", this[13]); return 1;}
		if(this[14] != 95) {printf("%d invalid\n", this[14]); return 1;}
		if(this[15] != 119) {printf("%d invalid\n", this[15]); return 1;}
		if(this[16] != 104) {printf("%d invalid\n", this[16]); return 1;}
		if(this[17] != 48) {printf("%d invalid\n", this[17]); return 1;}
		if(this[18] != 108) {printf("%d invalid\n", this[18]); return 1;}
		if(this[19] != 101) {printf("%d invalid\n", this[19]); return 1;}
		if(this[20] != 95) {printf("%d invalid\n", this[20]); return 1;}
		if(this[21] != 116) {printf("%d invalid\n", this[21]); return 1;}
		if(this[22] != 49) {printf("%d invalid\n", this[22]); return 1;}
		if(this[23] != 109) {printf("%d invalid\n", this[23]); return 1;}
		if(this[24] != 51) {printf("%d invalid\n", this[24]); return 1;}

        printf("valid\n");
    }
        else {
        printf("invalid %d\n", args);
    }

    return 0;
}
