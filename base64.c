/**------------------------------------
	base64.c
	
	encode/decode functions file
---------------------------------------*/

#include "base64.h"

const char *crp = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char S_CRP = 64;


/**----------------
	Encode function
	Input:
		char *s_string -> source string with the non encode message
		size_t s_size -> source string number of bytes (of characters too)
		char *d_string -> destination string. Will be filled with the encode message
		size_t d_size -> destination string number of bytes (of characters too)
			[The caller should give a d_string with the correct size]
	
	Description:
		Encodes the message according to the Base64 algorithm.
		Uses an integer to storage the three 8-bytes and a char to extract from it
		four 6-bytes.Then, the program uses each char to get the correct character from *crp
		according to the algorithm.
--------------------*/
void encode(char *s_string, size_t s_size, char *d_string, size_t d_size){
	int i, j, pag=d_size/4;
	int code = 0;
	char n_lpag = s_size%3;
	if(!n_lpag) n_lpag=3;
	unsigned char n_equal = (3-n_lpag);
	char aux;
	
	for(i=0;i<pag;i++){
		
		if(i<(pag-1)){
			for(j=0;j<3;j++){
		
				code<<=8;
				code |=((int)s_string[3*i+j]);
			}
			for(j=3;j>=0;j--){
			
				aux = (char)code;
				aux &= 0x3F; //Mascara para dejar solo 6 bits
				d_string[4*i+j] = crp[(short)aux];
				code>>=6;
			}
		} else{
			for(j=0;j<3;j++){
		
				code<<=8;
				if(j<n_lpag) code |=((int)s_string[3*i+j]);
			}
			for(j=3;j>=0;j--){
			
				if(n_equal){
					d_string[4*i+j] = '=';
					n_equal--;
				} else{
					aux = (char)code;
					aux &= 0x3F; //Mascara para dejar solo 6 bits
					d_string[4*i+j] = crp[(short)aux];
				}
				code>>=6;
			}			
		}
	}
}

/**----------------
	Encode function
	Input:
		char *s_string -> source string with the encode message
		size_t s_size -> source string number of bytes (of characters too)
		char *d_string -> destination string. Will be filled with the decode message
		size_t d_size -> destination string number of bytes (of characters too)
			[The caller should give a s_string with the correct size]
	
	Description:
		Decodes the message according to the Base64 algorithm.
		First, the program finds the source character position in the crp string. Then
		uses it as an 6-byte number and uses an integer to store them four by four and
		a char to extract from it three 8-bytes. This 8-bytes are the correct 8-byte
		characters, that are stored in the d_string.
--------------------*/
void decode(char *s_string, size_t s_size, char *d_string, size_t d_size){
	int i, j, k, pag=s_size/4;
	int code = 0;
	int n_equal = 0;
	
	for(i=0;i<pag;i++){
		for(j=0;j<4;j++){
		
			code<<=6;
			
			for(k=0;k<S_CRP;k++){
				if((s_string[4*i+j])==crp[k]){
					s_string[4*i+j]=k;
					break;
				}else if((s_string[4*i+j])=='='){
					n_equal++;
					s_string[4*i+j]=0;
					break;
				}
			}
			code |=((int)s_string[4*i+j]);
		}
		for(j=2;j>=0;j--){
			if(n_equal!=0){
				n_equal--;
				d_string[3*i+j]=' ';
			}
			else d_string[3*i+j]=(char)code;
			code>>=8;
		}
	}
}
