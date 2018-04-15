#include <stdio.h>

int main() {

	int memory[100];
     memory[0] = 1;
	memory[99] = 800;
     int pc = 0;
	int accumulator = 0;
	int instruction = 0;

	while(1) {
		instruction = memory[pc];
		++pc;
		int opcode = instruction / 100;

		int address = instruction % 100;


		switch (opcode) {
				int card = 0;
			case 0:
				scanf("%d", &card);
				memory[address] = card;

				break;
			case 1:
			     accumulator = address;
			     break;
			case 2:
			     accumulator = accumulator + address;
			     break;
			case 3:
			     if (accumulator < 0){
			          pc = pc + address;
			     }
			     break;
	          case 4:

	               accumulator = (10 * (address / 10) ) / (10 * (address % 10));
	               break;
			case 5:
				printf("%d\n", memory[address]);
				break;
			case 6:
			     memory[address] = accumulator;
			     break;
			case 7:
			     accumulator = accumulator - address;
			     break;
			case 8:
			     memory[99]= pc;
				pc = address;
				break;
			case 9:
				return 0;
				break;
			default:
				printf("opcode '%d' not yet implemented! Panicking!\n", opcode);
				return 1;
		}
	}

return 0;
}
