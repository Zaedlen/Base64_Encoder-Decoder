#include "base64.h"

void desencriptar(char *c, size_t tcod, char *decode, size_t tdecod);

int main(int argc, const char *argv[]){
	int fdo,fdd;
	char *decode, *ndest;
	void *pos;
	size_t tcod, tdecod;

	if(argc!=2){
		printf("Uso: %s archivo_a_desencriptar\n",argv[0]);
     	exit(1);
    }
     
	if((fdo=open(argv[1],O_RDWR))<0)
     	perror("Error al abrir el archivo");
     	
    //Fichero destino
    ndest=(char*)malloc((strlen("decod_")+strlen(argv[1])));
    sprintf(ndest, "decod_%s", argv[1]);
    if((fdd=open(ndest,O_RDWR|O_CREAT, 0644))<0)
     	perror("Error al abrir el archivo");
     	
	if((tcod=lseek(fdo,0,SEEK_END))<=0)
    	perror("Error al calcular tam del archivo o archivo vacio");
    
    tdecod = (tcod/4)*3;
    if((decode=(char*)malloc(tdecod))==NULL)
    	perror("Error en la memoria dinamica");
    
    pos=mmap(0, tcod, PROT_READ|PROT_WRITE, MAP_PRIVATE, fdo, 0);
	if(pos==MAP_FAILED)
		perror("Error al proyectar la memoria");
	
	desencriptar((char*)pos, tcod, decode, tdecod);	
	
	//Actualizar el fichero
	if((write(fdd, decode, tdecod))<tdecod)
		perror("Error al guardar la decodificacion");
	
	//Liberar memoria
	if(munmap(pos,tcod)<0) perror("Error al liberar mem");
	
	free(decode);
	free(ndest);
	close(fdo);
	close(fdd);
	
	return 0;
}

void desencriptar(char *c, size_t tcod, char *decode, size_t tdecod){
	int i, j, k, pag=tcod/4;
	int code = 0;
	int equal = 0;
	
	for(i=0;i<pag;i++){
		for(j=0;j<4;j++){
		
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
				decode[3*i+j]=' ';
			}
			else decode[3*i+j]=(char)code;
			code>>=8;
		}
	}
}
