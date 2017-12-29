#include "base64.h"

void encriptar(char *c, size_t tcod, char *code, size_t tdecod);

int main(int argc, const char *argv[]){
	int fdo,fdd;
	char *code, *ndest;
	void *pos;
	size_t tcod, tdecod;

	if(argc!=2){
		printf("Uso: %s archivo_a_encriptar\n",argv[0]);
     	exit(1);
    }
     
	if((fdo=open(argv[1],O_RDWR))<0)
     	perror("Error al abrir el archivo");
     	
    //Fichero destino
    ndest=(char*)malloc((strlen("cod_")+strlen(argv[1])));
    sprintf(ndest, "cod_%s", argv[1]);
    if((fdd=open(ndest,O_RDWR|O_CREAT|O_TRUNC, 0644))<0)
     	perror("Error al abrir el archivo");
     	
	if((tdecod=lseek(fdo,0,SEEK_END))<=0)
    	perror("Error al calcular tam del archivo o archivo vacio");
    
    //Cadena de caracteres que almacena el resultado
    if(tdecod%3) tcod = ((tdecod/3)+1)*4;
    else tcod = (tdecod/3)*4;
    if((code=(char*)malloc(tcod))==NULL)
    	perror("Error en la memoria dinamica");
    
    pos=mmap(0, tdecod, PROT_READ|PROT_WRITE, MAP_PRIVATE, fdo, 0);
	if(pos==MAP_FAILED)
		perror("Error al proyectar en memoria");
	
	encriptar((char*)pos, tdecod, code, tcod);	
	
	//Actualizar el fichero
	if((write(fdd, code, tcod))<tcod)
		perror("Error al guardar la decodificacion");
	
	//Liberar memoria
	if(munmap(pos,tdecod)<0) perror("Error al liberar mem");
	
	free(code);
	free(ndest);
	close(fdo);
	close(fdd);
	
	return 0;
}

void encriptar(char *c, size_t tdecod, char *encode, size_t tcod){
	int i, j, k, pag=tcod/4;
	int code = 0;
	int equal = tdecod%3;
	char aux;
	
	for(i=0;i<pag;i++){
		
		if(i!=pag-1){
			for(j=0;j<3;j++){
		
				code<<=8;
				code |=((int)c[3*i+j]);
			}
			for(j=3;j>=0;j--){
			
				aux = (char)code;
				aux &= 0x3F; //Mascara para dejar solo 6 bits
				encode[3*i+j] = crp[aux];
				code>>=6;
			}
		} else{
			for(j=0;j<3;j++){
		
				code<<=8;
				if(code |=((int)c[3*i+j]);
			}
			for(j=3;j>=0;j--){
			
				aux = (char)code;
				aux &= 0x3F; //Mascara para dejar solo 6 bits
				encode[3*i+j] = crp[aux];
				code>>=6;
			}
			
		}
			
		
			code<<=6;
			
			for(k=0;k<S_CRP;k++){
				if((c[4*i+j])==crp[k]){
					c[4*i+j]=k;
					break;
				}else if((c[4*i+j])=='='){
					equal++;
					c[4*i+j]=0;
					break;
				}
			}
			code |=((int)c[4*i+j]);
		}
		for(j=2;j>=0;j--){
			if(equal!=0){
				equal--;
				encode[3*i+j]=' ';
			}
			else encode[3*i+j]=(char)code;
			code>>=8;
		}
	}
}
