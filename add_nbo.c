#include<stddef.h> //use size_t
#include<stdint.h> // for uint32_t
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[3]){
	
	FILE *input1, *input2;
	//char *buf1[3]={0,}, *buf2[3]={0,};
	uint32_t a1[1],a2[1];
	uint32_t add1, add2, result1, result2;
	int i;
	
	if(argc < 3 ){
		printf("Usage : %s <file1> <file2>\n",argv[0]);
		return 0;
	}

	input1 = fopen(argv[1],"rb");
	input2 = fopen(argv[2],"rb");
	
	fread(a1,sizeof(uint32_t),1,input1);
	add1 = (*a1 & 0xFF000000) >> 8;
	add2 = (*a1 & 0x00FF0000) << 8;
	result1 = (add2|add1) >> 16;
	
	fread(a2,sizeof(uint32_t),1,input2);
	add1 = (*a2 & 0xFF000000) >> 8;
	add2 = (*a2 & 0x00FF0000) << 8;
	result2 = (add2|add1) >>16;

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",result1,result1,result2,result2,result1+result2,result1+result2);
	
	fclose(input2);
	fclose(input1);
	return 0;
}
