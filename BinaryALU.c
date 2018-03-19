#include <stdio.h>
#include <stdlib.h>
#define BYTE_LENGTH 8

#define BYTES1_LIMIT_MIN -128
#define BYTES2_LIMIT_MIN -32768
#define BYTES4_LIMIT_MIN -2147483648

#define BYTES1_LIMIT_MAX 127
#define BYTES2_LIMIT_MAX 32767
#define BYTES4_LIMIT_MAX 2147483647

#define MENU "\t0 INV A\n\t1 A NAND B\n\t2 SHL A\n\t3 SAR A\n\t4 ROR A\n\t5 SET A, B\n\t6 -A\n\t7 A + (-B)\n"
void printBinary(long int bytes, int lengthInBytes,char select);
char checkNegative(long int bytes, int lengthInBits);
char bitValue(long int bytes,int bitSelect);
char evenCheck(long int bytes);

long int invA(long int bytes);
long int AnandB(long int A, long int B);
long int SHLA(long int A);
long int SAR(long int A, int lengthInBytes);
long int ROR(long int A, int lengthInBytes);
long int SETAB(long int A,long int B);
long int intNegate(long int bytes);
long int AADDnegB(long int A, long int B);

int main(void)
{
	long int userInputA, userInputB;
	char selectFunction, selectExit, selectPrint;
	char error = 0;
	char exitMenu = 0;
	int lengthInBytes;
	printf("Sizeof long int %ld\n",sizeof(long int));
	while(!exitMenu)
	{
		error = 0;
		system("clear");
		printf("Insert A decimal value: ");
		scanf("%ld",&userInputA);
		printf("Insert B decimal value: ");
		scanf("%ld",&userInputB);
		if(((userInputA >= BYTES1_LIMIT_MIN) && (userInputA <= BYTES1_LIMIT_MAX)) && ((userInputB >= BYTES1_LIMIT_MIN) && (userInputB <= BYTES1_LIMIT_MAX)))
		{
			lengthInBytes = 1;
		}
		else if(((userInputA >= BYTES2_LIMIT_MIN) && (userInputA <= BYTES2_LIMIT_MAX)) && ((userInputB >= BYTES2_LIMIT_MIN) && (userInputB <= BYTES2_LIMIT_MAX)))
		{
			lengthInBytes = 2;
		}
		else if(((userInputA >= BYTES4_LIMIT_MIN) && (userInputA <= BYTES4_LIMIT_MAX)) && ((userInputB >= BYTES4_LIMIT_MIN) && (userInputB <= BYTES4_LIMIT_MAX)))
		{
			lengthInBytes = 4;
		}
		else
		{
			error = 1;
		}
		if(!error)
		{
			printf("Select operation:\n");
			printf("%s",MENU);
			scanf(" %c",&selectFunction);
			selectFunction -='0';
			printf("Select printing mode h/b (HEX)/(BIN)\n");
			scanf(" %c",&selectPrint);
			printf("selectFunction %d\n",selectFunction);
			if(selectFunction == 0)
			{
				printBinary(invA(userInputA),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 1)
			{
				printBinary(AnandB(userInputA,userInputB),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 2)
			{
				printBinary(SHLA(userInputA),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 3)
			{
				printBinary(SAR(userInputA,lengthInBytes),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 4)
			{
				printBinary(ROR(userInputA,lengthInBytes),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 5)
			{
				printBinary(SETAB(userInputA,userInputB),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 6)
			{
				printBinary(intNegate(userInputA),lengthInBytes,selectPrint);
			}
			else if(selectFunction == 7)
			{
				printBinary(AADDnegB(userInputA, userInputB),lengthInBytes,selectPrint);
			}
			printf("Continue? [y/n]");
			scanf(" %c",&selectExit);

			if((selectExit != 'y') && (selectExit != 'Y'))
			{
				exitMenu = 1;
			}
		}
	}

	return 0;
}

void printBinary(long int bytes, int lengthInBytes,char select)
{
	int index;
	if(lengthInBytes <= sizeof(long int))
	{
		lengthInBytes *= 8;	/*convert to bits*/
		if((select == 'b') || (select == 'B'))
		{
			printf("BIN:");
			for(index = lengthInBytes - 1;index >= 0;index--)
			{
				if(((index + 1) % 4) == 0)
				{
					printf(" "); /*Separate into nibbles*/
				}
					printf("%d",bitValue(bytes,index));

			}
			printf("\n");
		}
		else	if ((select == 'h') || (select == 'H')) {
			printf("HEX: %02lX\n",bytes);
		}
	}
	else
	{
		printf("Wrong bytelength to printBinary!\n");
	}
}

char checkNegative(long int bytes, int lengthInBits)
{
	if(bytes & (1 << (lengthInBits-1)))
	{
		return 1;
	}
	return 0;
}

char bitValue(long int bytes,int bitSelect)
{
	if(bytes & (1 << bitSelect))
	{
		return 1;
	}
	return 0;
}

char evenCheck(long int bytes)
{
	return bytes && 1;
}

long int intNegate(long int bytes)
{
	return ~bytes + 1;
}

long int invA(long int A)
{
	return ~A;
}

long int AnandB(long int A, long int B)
{
	return ~(A & B);
}

long int SHLA(long int A)
{
	return A << 1;
}

long int SAR(long int A, int lengthInBytes)
{
	lengthInBytes *= 8;
	if(bitValue(A,lengthInBytes - 1))
	{
		A = A >> 1;
		A |= (1 << (lengthInBytes-1));
	}
	else
	{
		A = A >> 1;
	}
	return A;
}

long int ROR(long int A, int lengthInBytes)
{
	lengthInBytes*=8;
	if(bitValue(A,0))
	{
		A = A >> 1;
		A |= (1 << (lengthInBytes-1));
	}
	else
	{
		A = A >> 1;
	}
	return A;
}

long int SETAB(long int A,long int B)
{
	return A | (1 << B);
}

long int AADDnegB(long int A, long int B)
{
	return A + intNegate(B);
}
