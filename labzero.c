#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

void bin2ascii(char funcb2a[]); //function to take an array of chars '1' and '0' and convert them to ascii
void prnHeader(); //function to print the header for the output
void validCheck(char validArray[],int sizerr); //function to check if input is valid
void zeroAppend(char zeroArray[]);

int main(int argc, char** argv){

	int fp; //file
	char cx; //char that is taken from read() func
	char binStr[8]; //chars to take from argument from command line
	int incx=0; //increment variable for while loop at line 32&35
	char currentStr[10]; //array that holds chars from file
	int sizeArg;
	int dashStart = 1; 

	prnHeader();

	if (argc!=2){ //checking if command line is used for inputing values & then copying arguments into program
		if(strcmp(argv[1],"-") == 0){
				dashStart=2;
		}
		for(int i=dashStart; i<argc;i++){
			sizeArg = strlen(argv[i]);
			validCheck(argv[i],sizeArg);
			for(int j=0;j<sizeArg;j++){
				if((argv[i][j]=='1') || (argv[i][j] =='0')){
				binStr[j] = argv[i][j];
				binStr[sizeArg] = '\0';
				}
			}
			zeroAppend(binStr);
			bin2ascii(binStr);
		}
	}


	if(argc ==2){ //checking that argument has 2 values, filename for input
		fp=open (argv[1],O_RDONLY);
		while(read(fp,&cx, 1) > 0){
				currentStr[incx] = cx;
				incx++;
				if (cx==32 || cx== 10){
					sizeArg = strlen(currentStr);
					currentStr[incx-1] = '\0';
					zeroAppend(currentStr);
					//validCheck(currentStr,sizeArg-1);
					bin2ascii(currentStr);
					incx=0;
				}
		}
	}	
	close(fp);
	return 0;
}

void bin2ascii(char funcb2a[]){

	int parityCount=0;
	int num=0;

	if(funcb2a[0]==49){
		num=num-128;
	}


	for(int i=0;i<8;i++){
		/*if(funcb2a[i]==0){ //appending 0s to incomplete binary numbers
			funcb2a[i] = 48;
			funcb2a[i+1] = 0;
		}*/
		if(funcb2a[i]==49){
			num+= ('1'-'0') << (7-i);
			printf("1");
			parityCount++;
		}
		if(funcb2a[i]==48){
			num+=('0'-'0') << (7-i);
			printf("0");
		}
	}

	if(num<33 || num>126){ //checking if ascii value is printable value, if not,  NUL is printed
		printf("\tNUL");
	}
	if(num>32 && num<127){ 
		printf("\t%c", num);
	}

	printf("\t%d",num);

	if(parityCount%2==0){
		printf("\tEVEN\n");
	}
	if(parityCount%2==1){
		printf("\tODD\n");
	}

	return;
}

void prnHeader(){
	printf("Original    ASCII    Decimal   Parity\n");
	printf("--------- --------- --------- ---------\n");
	return;
}

void validCheck(char validArray[],int sizerr){

	for(int j=0;j<sizerr;j++){
		if((validArray[j]!= '1') && (validArray[j]!=  '0')) {
			printf("you have entered invalid data\n");
			exit(0);
		}
	}
	return;
}

void zeroAppend(char zeroArray[]){

 	for(int i=0;i<8;i++){
 		if(zeroArray[i]=='\0'){
 			zeroArray[i]='0';
 			zeroArray[i+1]='\0';
 		}
	}

	return;
}