// code courtesy of https://github.com/TheInvincible95
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct threeAdressCode
{
	char destA[33];
	char source1A[33];
	char source2A[33];
	char op;

} threeAdressCode;
#define arrayLen(x) sizeof((x)) / sizeof((x)[0]);
void printThreeAddressCode(threeAdressCode code)
{
	if (code.op == '\0')
		if (code.source2A[0] == '\0')
			printf("%s\t=\t%s\n", code.destA, code.source1A);
		else
			assert(0 && "Assignment operation has two operands");
	else
		printf("%s\t=\t%s\t%c\t%s\n",
			   code.destA, code.source1A, code.op, code.source2A);
}
void printThreeAddressCodes(threeAdressCode array[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d] ", i);
		printThreeAddressCode(array[i]);
	}
}
void analyseForOptimisation(threeAdressCode array[], int n)
{
	for (int i = 1; i < n; i++)
	{

		for (int j = i - 1; j >= 0; j--)
		{
			if (strcmp(array[i].destA, array[j].source1A) == 0 || strcmp(array[i].destA, array[j].source2A) == 0)
				break;
			if (
				strcmp(array[i].source1A, array[j].source1A) == 0 && strcmp(array[i].source2A, array[j].source2A) == 0 && array[i].op == array[j].op // operator is the same
			)
			{
				printf("Instruction %d and %d compute the same value\n", j, i);
				printf("%d] ", j);
				printThreeAddressCode(array[j]);
				printf("%d] ", i);
				printThreeAddressCode(array[i]);
			}
			if (array[i].op == '\0' && array[i].source2A[0] == '\0' && strcmp(array[j].destA, array[i].source1A) == 0 /*Directly placing value from one address to another*/
			)
			{
				printf("Instruction %d and %d have redundant assignment\n", j, i);
				printf("%d] ", j);
				printThreeAddressCode(array[j]);
				printf("%d] ", i);
				printThreeAddressCode(array[i]);
			}
		}
	}
}
int main()
{
	threeAdressCode instrcutions[] =
		{
			{
				.destA = "temp1",
				.source1A = "a",
				.source2A = "b",
				.op = '+',
			},
			{
				.destA = "temp2",
				.source1A = "temp1",
				.source2A = "2",
				.op = '*',
			},
			{
				.destA = "temp3",
				.source1A = "c",
				.source2A = "d",
				.op = '+',
			},
			{
				.destA = "temp4",
				.source1A = "temp2",
				.source2A = "temp3",
				.op = '+',
			},
			{
				.destA = "f",
				.source1A = "temp4",
				.source2A = "\0",
				.op = '\0',
			},
			{
				.destA = "temp5",
				.source1A = "c",
				.source2A = "d",
				.op = '+',
			},
			{
				.destA = "temp6",
				.source1A = "a",
				.source2A = "b",
				.op = '+',
			},
			{
				.destA = "temp7",
				.source1A = "temp5",
				.source2A = "temp6",
				.op = '*',
			},
			{
				.destA = "g",
				.source1A = "temp7",
				.source2A = "\0",
				.op = '\0',
			},
		};
	int len = arrayLen(instrcutions);
	printThreeAddressCodes(instrcutions, len);
	printf("---------------------------------------------\n");
	analyseForOptimisation(instrcutions, len);
}
