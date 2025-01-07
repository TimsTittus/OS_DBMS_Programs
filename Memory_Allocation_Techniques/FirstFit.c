#include<stdio.h>
#include<stdlib.h>

int main() {
	int m,n;
	
	//number of memory blocks and sizes
	printf("Enter the number of memory blocks : ");
	scanf("%d",&m);
	int *blockSizes = (int *)malloc(m * sizeof(int));
	printf("Enter the sizes of memory blocks :\n");
	for(int i=0;i<m;i++) {
		scanf("%d",&blockSizes[i]);
	}
	
	//number of processes and sizes
	printf("Enter the number of process : ");
	scanf("%d",&n);
	int *processSizes = (int *)calloc(n, sizeof(int));
	printf("Enter the sizes of processes :\n");
	for(int i=0;i<n;i++) {
		scanf("%d",&processSizes[i]);
	}
	
	for(int i=0;i<n;i++) {
		int allocated = 0;
		for(int j=0;i<m;j++) {
		if (blockSizes[j] >= processSizes[i]) { //checking if the block can fit the process
				printf("Process %d of size %d allocated to block %d\n", i+1, processSizes[i], j+1);
				blockSizes[j] -= processSizes[i]; //reduce block size
				allocated = 1;
				break;
			}
		}
		if(!allocated) {
			printf("Process %d of size %d not allocated\n", i+1, processSizes[i]);
		}
	}
	
	free(blockSizes);
	free(processSizes);
	
	return 0;
}
