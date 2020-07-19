#include<stddef.h> //use size_t
#include<stdint.h> // for uint32_t
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

uint32_t to_big(uint32_t bits32);//빅엔디안으로 변환
uint32_t to_little(uint32_t bits32);//리틀엔디안으로 변환

int main(int argc, char *argv[2]){
	
	const int check = 1;
	FILE *input1, *input2;
	uint32_t in1[1],re1[1],in2[1],re2[1];

	if((*(char*)&check)==0){
		printf("big\n");
		
		input1 = fopen(argv[1],"rb");
		input2 = fopen(argv[2],"rb");
		
		fread(in1,sizeof(uint32_t),1,input1);
		re1[0] = to_little(in1[0]);
		fread(in2,sizeof(uint32_t),1,input2);
		re2[0] = to_little(in2[0]);

		printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",re1[0],re1[0],re2[0],re2[0],re1[0]+re2[0],re1[0]+re2[0]);
	}
	else{
		printf("little\n");
		
		input1 = fopen(argv[1],"rb");
		input2 = fopen(argv[2],"rb");

		fread(in1,sizeof(uint32_t),1,input1);
		re1[0] = to_big(in1[0]);
		fread(in2,sizeof(uint32_t),1,input2);
		re2[0] = to_big(in2[0]);

		printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",re1[0],re1[0],re2[0],re2[0],re1[0]+re2[0],re1[0]+re2[0]);
	}

	fclose(input2);
	fclose(input1);
	return 0;
}

uint32_t to_big(uint32_t bits32){
	uint32_t byte[4];
	uint32_t ret;
	
	byte[0] = (uint32_t)((bits32 >> 0) & 0xff);
 	byte[1] = (uint32_t)((bits32 >> 8) & 0xff);
	byte[2] = (uint32_t)((bits32 >> 16) & 0xff);
	byte[3] = (uint32_t)((bits32 >> 24) & 0xff);

	return ((uint32_t)byte[0] << 24)|((uint32_t)byte[1] << 16)|((uint32_t)byte[2] << 8)|((uint32_t)byte[3] << 0);	
}

uint32_t to_little(uint32_t bits32){
	uint32_t byte[4];
	uint32_t ret;

	byte[0] = (uint32_t)((bits32 >> 0) & 0xff);
	byte[1] = (uint32_t)((bits32 >> 8) & 0xff);
	byte[2] = (uint32_t)((bits32 >> 16) & 0xff);
	byte[3] = (uint32_t)((bits32 >> 24) & 0xff);
	
	return ((uint32_t)byte[0] << 0) |((uint32_t)byte[1] << 8)|((uint32_t)byte[2] << 16)|((uint32_t)byte[3] <<24);
}
