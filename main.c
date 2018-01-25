/**----------------------------------------------------------
	Base64 Encoder-Decoder
	
	Main file
-------------------------------------------------------------*/

#include "base64.h"

/**----------------
	Main function.
	It just handle the file management and the memory allocation part,
	creating the strings that the encode/decode functions work with.
-------------------*/
int main(int argc, const char *argv[]){
	int fds, fdd;
	unsigned char o_flag=1, encode_flag;
	char dest_f[256], lf[1];
	char *d_string;
	void *s_string;
	size_t s_size, d_size;

	if((argc<3) | (argc>4)){
		printf("Use: %s [E/D] ascii_source_file destination_file\n",argv[0]);
     	exit(EXIT_FAILURE);
    }
    
    //Encode or decode flag
    if(*argv[1]=='E') encode_flag = 1;
    else if(*argv[1]=='D') encode_flag = 0;
    else{
    	printf("Use: %s [E/D] ascii_source_file destination_file\n",argv[0]);
     	exit(EXIT_FAILURE);
    }
    
    //Source file
	if((fds=open(argv[2],O_RDONLY))<0){
		perror("Couldnt open the source file.");
		exit(EXIT_FAILURE);
	}
	
	//Destination file
	if(argc==4){
		if((fdd=open(argv[3],O_RDWR|O_CREAT|O_TRUNC, 0644))<0)
     		perror("Couldnt open the given destination file. Trying with the default one.");
     	else o_flag=0;
    }
    if((argc==3) | (o_flag)){
    	if(encode_flag) sprintf(dest_f, "cod_%s", argv[2]);
    	else sprintf(dest_f, "decod_%s", argv[2]);
    	
    	if((fdd=open(dest_f,O_RDWR|O_CREAT|O_TRUNC, 0644))<0){
     		perror("Couldnt open the default destination file.");
     		exit(EXIT_FAILURE);
     	}
    }
    
    //Source file size
	if((s_size=lseek(fds,-1,SEEK_END))<=0){
		perror("Couldnt calculate dest file size or EMPTY SOURCE FILE.");
    	exit(EXIT_FAILURE);
    } else{
    	//text editors like gedit add Line Feed at the end when you save the file. This fakes the
    	//s_size, thats the reason we stop lseek before the last character and check it
    	read(fds, lf, 1);
    	if(lf[0]!=10) s_size++;
    }
    
    //Destination file size calculation
    if(encode_flag){
		if(s_size%3) d_size = ((s_size/3)+1)*4;
		else d_size = (s_size/3)*4;
    } else{
    	if((s_size%4)!=0){
    		perror("Incorrect Base64 ascii file (number of characters doesnt fix). Couldnt decode.");
    		printf("%li    %li\n",s_size, (s_size%4));
    		exit(EXIT_FAILURE);
    	} else d_size = (s_size/4)*3;
    }
    
    //Destination string memory allocation
	if((d_string=(char*)malloc(d_size))==NULL){
		perror("Couldnt allocate destination string.");
		exit(EXIT_FAILURE);
	}
	
	//Source string memory allocation
	s_string=mmap(0, s_size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fds, 0);
	if(s_string==MAP_FAILED){
		perror("Couldnt achieve memory mapping of the source file.");
		free(d_string);
		exit(EXIT_FAILURE);
	}
	
	//Enocding-decoding operation
	if(encode_flag) encode((char*)s_string, s_size, d_string, d_size);
	else decode((char*)s_string, s_size, d_string, d_size);
	
	//Destination file updating
	if((write(fdd, d_string, d_size))<d_size)
		perror("Error al guardar la decodificacion");
	
	//Memory freeing
	if(munmap(s_string,s_size)<0) perror("Couldnt unmap the source file");
	free(d_string);
	close(fds);
	close(fdd);
	
	return 0;	
}
