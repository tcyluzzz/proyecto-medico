	#include <stdio.h>
	#include <string.h>
	
	/*----- FUNCIONES DE CONSULTAS -----*/
	void trans2fech(unsigned long fecha1,unsigned long fecha2);
	void pordiag();
	void listmed();
	void buscpac(char *pac);
	void secmayor();
	void comp(int numg,int cant);
	
	/*----- FUNCIONES DE AGREGAR -----*/
	void agregar();
	void agregarpac();
	void agregarmed();
	void agregarsana();
	void agregarextra();
	void agregartrans();
	
	/*----- FUNCIONES DE ELIMINACION -----*/
	void eliminar();
	void eliminpac();
	void eliminmed();
	void eliminextra();
	void eliminsan();
	void elimintrans();
	
	/*----- FUNCIONES DE MODIFICACION -----*/
	void modificar();
	void modificarpac();
	void modificarmed();
	void modificarextra();
	void modificarsan();
	void modificartrans();
	
	/*----- ESTRUCTURAS -----*/
	struct Pacientes{
		char nombre[30];
		int dni;
		int fechdenac;
		char gen;
		char direccion[60];
		unsigned long telefono;
		char grupsan[15];
		char rh[10];
		char obrasoc[20];
		char diagnostico[20];
		char nomfam[30];
		int dnifam;
		unsigned long telfam;
		char paren[20];};
		
	struct Medicos{
		char nombre[30];
		int dni;
		int matri;
		char especialidad[20];};	
	
	struct Extracciones{
		int numguia;
		int fechextra;
		int fechaven;
		char gruposan[15];
		char rh[20];
		char hemocom[30];};	
	
	struct Sanatorios{
		char nombre[30];
		char direccion[60];};
	
	struct Transfusiones{
		int numguia;
		char hemocom[20];
		char paciente[40];
		int fechatrans;
		char medico[40];
		char tecnico[80];
		char sector[20];};
		
	/*----- MAIN HUB -----*/
	int main(){	
		char pac[60];
		int a=99,fechamin=0,fechamax=0,aux=0,cant=0;
		
		while(a!=0){
		printf("Para buscar las transfusiones entre dos fechas presione 1\n");
		printf("Para ver el mayor porcentaje de transfusiones por diagnostico presione 2\n");
		printf("Para ver los cinco medicos que mas transfusiones realizaron presione 3\n");
		printf("Para buscar las transfuciones por el nombre del paciente presione 4\n");
		printf("Para ver el sector con mas cantidades de transfusiones presione 5\n");
		printf("Para agregar registros presione 6\n");
		printf("Para eliminar registros presione 7\n");
		printf("Para modificar registros presione 8\n");
		printf("Para realizar un comprobante de transfusion presione 9\n\n");
		printf("Para salir presione 0\nseleccion:|--- ");
		
			scanf("%d",&a);
			fflush(stdin);
			
		if((a!=0)&&(a!=1)&&(a!=2)&&(a!=3)&&(a!=4)&&(a!=5)&&(a!=6)&&(a!=7)&&(a!=8)&&(a!=9)){
		printf("\nINGRESO UN VALOR INCORRECTO DE A, INGRESE OTRA VEZ LA SELECCION \n\n");}
		
			switch(a) {
				case 1:{
				printf("\nIngrese la fecha minima a ingresar en formato \n AAAAMMDD\n ");
				scanf("%lu",&fechamin);
				fflush(stdin);
				printf("\nIngrese la fecha maxima a buscar en formato \n AAAAMMDD\n ");
				scanf("%lu",&fechamax);
				fflush(stdin);
				printf("\n\n");
				trans2fech(fechamin,fechamax);
				break;}
				
				case 2:{
				printf("\n\n");
				pordiag();
				break;}
				
				case 3:{
				printf("\n\n");
				listmed();
				break;}
					
				case 4:{
				printf("\nIngrese el nombre del paciente: ");
				gets(pac);
				printf("\n\n");
				buscpac(&pac[0]);
				break;}
				
				case 5:{
				printf("\n\n");
				secmayor();
				break;}	
				
				case 6:{
				printf("\n\n");
				agregar();
				break;}
				
				case 7:{
				printf("\n\n");
				eliminar();
				break;}
				
				case 8:{
				printf("\n\n");
				modificar();
				break;}
				
				case 9:{
				printf("\n\nSi quiere generar un comprobante de una transfusion a seleccion ingrese 1: \n");
				printf("Si quiere generar todos los comprobantes de las transfusiones ingrese 0: \nseleccion:|--- ");
				scanf("%d",&cant);fflush(stdin);
				if(cant==1){
				printf("\nIngrese el numero de guia del comprobante necesitado: ");
				scanf("%d",&aux);fflush(stdin);
				printf("\n\n");
				comp(aux,cant);
				}else comp(aux,cant);
				break;}
			}
		}
		return 0;
	}
	
	/*----- FUNCION BUSCAR ENTRE DOS FECHAS -----*/
	void trans2fech(unsigned long fechamin,unsigned long fechamax){
		FILE *f;
		int aux;
		struct Transfusiones trans;
		printf("Num guia  Hemocomponente       Pacientes     Fecha trans \tMedico solic\t Tecnico a cargo      Sector");
		
		if((f=fopen("Transfusiones.dat","rb"))!=NULL){
			fread(&trans,sizeof(struct Transfusiones),1,f);
			while(!feof(f)){
				if(((trans.fechatrans)>=fechamin)&&((trans.fechatrans)<=fechamax)){
				printf("\n%d\t  %-20s %-15s %d\t\t  %-10s    %-20s %s ",trans.numguia,trans.hemocom,trans.paciente,trans.fechatrans,trans.medico,trans.tecnico,trans.sector);
				aux=1;}
				fread(&trans,sizeof(struct Transfusiones),1,f);
			}
			fclose(f);
		}else perror("ERROR APERTURA DEL ARCHIVO Transfusiones.dat: ");
		
		if(aux==0)
		printf("\n\n\t\tNO SE ENCONTRARON TRANSFUSIONES REALIZADAS ENTRE EL RANGO DE ENTRADA ");
		
		printf("\n\n\n");
	}
	
	/*----- FUNCION PORCENTAJE DEL TOTAL DEL DIAGNOSTICO CON MAS TRANS -----*/
	void pordiag(){
		struct Transfusiones transfusion;
		struct Pacientes paciente;
		int enf[6],i=0,mayor=0,aux=0;
		for(i=0;i<6;i++)
		enf[i]=0;
		
		FILE *f,*arch;
		if((f=fopen("Transfusiones.dat","rb"))!=NULL){
			if((arch=fopen("Pacientes.dat","rb"))!=NULL){
				fread(&transfusion,sizeof(struct Transfusiones),1,f);
				while(!feof(f)){
					fread(&paciente,sizeof(struct Pacientes),1,arch);
					while(!feof(arch)){
						if(!strcmp(paciente.nombre,transfusion.paciente)){
							if(!(strcmp(paciente.diagnostico,"malaria"))){
							enf[0]++;
							aux++;
							}
							else if(!(strcmp(paciente.diagnostico,"sifilis"))){
							aux++;
							enf[1]++;
							}
							else if(!(strcmp(paciente.diagnostico,"hepatitis b"))){
							enf[2]++;
							aux++;
							}
							else if(!(strcmp(paciente.diagnostico,"hepatitis c"))){
							aux++;
							enf[3]++;
							}
							else if(!(strcmp(paciente.diagnostico,"anemia"))){
							enf[4]++;
							aux++;
							}
							else if(!(strcmp(paciente.diagnostico,"bronquitis"))){
							aux++;
							enf[5]++;
							}
						}
						fread(&paciente,sizeof(struct Pacientes),1,arch);
					}
					rewind(arch);
					fread(&transfusion,sizeof(struct Transfusiones),1,f);
				}
			}else perror("ERROR APERTURA DEL ARCHIVO Pacientes.dat: ");
			fclose(arch);
			fclose(f);
		}else perror("ERROR APERTURA DEL ARCHIVO Transfusiones.dat: ");
		
		enf[0]=(enf[0]*100)/aux;
		enf[1]=(enf[1]*100)/aux;
		enf[2]=(enf[2]*100)/aux;
		enf[3]=(enf[3]*100)/aux;
		enf[4]=(enf[4]*100)/aux;
		enf[5]=(enf[5]*100)/aux;
		
		for(i=0;i<5;i++){
			if(enf[i]>mayor){
			mayor=enf[i];
			aux=i;}
		}
		
		switch(aux) {
			case 0:{
			printf("El diagnostico con mayor porcentaje de transfusiones es: malaria con un %d%% del total\n\n",enf[aux]);
			break;}
			
			case 1:{
			printf("El diagnostico con mayor porcentaje de transfusiones es: sifilis con un %d%% del total\n\n",enf[aux]);
			break;}
			
			case 2:{
			printf("El diagnostico con mayor porcentaje de transfusiones es: hepatitis b con un %d%% del total\n\n",enf[aux]);
			break;}
			
			case 3:{
			printf("El diagnostico con mayor porcentaje de transfusiones es: hepatitis c con un %d%% del total\n\n",enf[aux]);
			break;}
			
			case 4:{
			printf("El diagnostico con mayor porcentaje de transfusiones es: anemia con un %d%% del total\n\n",enf[aux]);
			break;}
			
			case 5:{
			printf("El diagnostico con mayor porcentaje de transfusiones es: bronquitis con un %d%% del total\n\n",enf[aux]);
			break;}	
		}
		
	printf("\n");
	}
	
	/*----- FUNCION 5 MEDICOS CON MAS CANTIDAD DE TRANS -----*/
	void listmed(){
		FILE *f,*arch;
		int n[5],i=0,j=0,aux=0;
		char nmed[5][50];
		struct Transfusiones transfusion;
		struct Medicos medico;
		if((f=fopen("Transfusiones.dat","rb"))!=NULL){
		if((arch=fopen("Medicos.dat","r+b"))!=NULL){
			fread(&medico,sizeof(struct Medicos),1,arch);
			while(!(feof(arch))){
				i++;
				fread(&medico,sizeof(struct Medicos),1,arch);
				}
			rewind(arch);
			int cantrans[i];
			for(j=0;j<i;j++)
			cantrans[j]=0;
			char nom[i][50];
			i=0;
			for (j=0;j<i;j++)
			i=0;
			rewind(arch);
			fread(&transfusion,sizeof(struct Transfusiones),1,f);
			while (!(feof(f))){
				fread(&medico,sizeof(struct Medicos),1,arch);
				while(!(feof(arch))){
				strcpy(nom[i],medico.nombre);
				if(!strcmp(nom[i],transfusion.medico)){
						cantrans[i]++;
					}
				fread(&medico,sizeof(struct Medicos),1,arch);
				i++;
				}
				aux=i;
				i=0;
				rewind(arch);
			fread(&transfusion,sizeof(struct Transfusiones),1,f);
			}
			fclose(f);
			fclose(arch);
			for(j=0;j<5;j++){
				n[j]=0;
				strcpy(nmed[j],"_");
			}
			
					for(i=0;i<aux;i++){
						if(n[0]<cantrans[i]){
						strcpy(nmed[0],nom[i]);
						n[0]=cantrans[i];}
					}
						
					for(j=0;j<15;j++){
						if(n[1]<cantrans[j]&&strcmp(nmed[0],nom[j])){
						n[1]=cantrans[j];
						strcpy(nmed[1],nom[j]);}
					}
						
					for(j=0;j<15;j++){
						if(n[2]<cantrans[j]&&strcmp(nmed[0],nom[j])&&strcmp(nmed[1],nom[j])){
						n[2]=cantrans[j];
						strcpy(nmed[2],nom[j]);}
					}
						
					for(j=0;j<15;j++){
						if(n[3]<cantrans[j]&&strcmp(nmed[2],nom[j])&&strcmp(nmed[0],nom[j])&&strcmp(nmed[1],nom[j])){
						n[3]=cantrans[j];
						strcpy(nmed[3],nom[j]);}
					}
						
					for(j=0;j<15;j++){
						if(n[4]<cantrans[j]&&strcmp(nmed[3],nom[j])&&strcmp(nmed[2],nom[j])&&strcmp(nmed[0],nom[j])&&strcmp(nmed[1],nom[j])){
						n[4]=cantrans[j];
						strcpy(nmed[4],nom[j]);}
					}
						
						/*FIN ELSE*/
	
			printf("Los 5 medicos con mas transfusiones son:\n");
			for(i=0;i<5;i++)
			printf("\n%s con %d transfusiones\n",nmed[i],n[i]);
		}else perror("ERROR APERTURA ARCHIVO Medicos.dat: ");
		}else perror("ERROR APERTURA ARCHIVO Transfusiones.dat: ");
		
		printf("\n\n");
	}
	
	/*----- FUNCION BUSCAR TRANS POR PACIENTE -----*/
	void buscpac(char *pac){
		FILE *f;
		struct Transfusiones transfusion;
		if((f=fopen("Transfusiones.dat","rb"))!=NULL){
		fread(&transfusion,sizeof(struct Transfusiones),1,f);
			while(!feof(f)){
				if(!(strcmp(pac,transfusion.paciente))){
				printf("Las transfusiones realizadas a: %s son las siguientes: \n",pac);
				printf("Numero de guia:  %d\nHemocomponente:  %s\nPaciente:  %s\nFecha de transfusion:  %d\nMedico:  %s\nTecnico:  %s\nSector:  %s\n",transfusion.numguia,transfusion.hemocom,transfusion.paciente,transfusion.fechatrans,transfusion.medico,transfusion.tecnico,transfusion.sector);
				}
				fread(&transfusion,sizeof(struct Transfusiones),1,f);
			}
			fclose(f);	
		} else perror("ERROR APERTURA DEL ARCHIVO Transfusiones.dat: ");
		
		printf("\n\n");
	}
	
	/*----- FUNCION SECTORES MAYORES CANTIDAD DE TRANSFUSIONES -----*/
	void secmayor(){
		FILE *f;
		struct Transfusiones transfusion;
		int sectores[7],i=0,j=0,aux[7],h;
		char sec[7][20]={"internacion","pediatria","neonatal","guardia","quirofano","oncologia","UTI"};
		for(i=0;i<7;i++){
			aux[i]=0;
			sectores[i]=0;
		}
		
		if((f=fopen("Transfusiones.dat","rb"))!=NULL){
			fread(&transfusion,sizeof(struct Transfusiones),1,f);
			while(!feof(f)){
				if(!strcmp(transfusion.sector,"internacion")){
				sectores[0]++;}
				else if(!strcmp(transfusion.sector,"pediatria")){
				sectores[1]++;
				}
				else if(!strcmp(transfusion.sector,"neonatal")){
				sectores[2]++;
				}
				else if(!strcmp(transfusion.sector,"guardia")){
				sectores[3]++;
				}
				else if(!strcmp(transfusion.sector,"quirofano")){
				sectores[4]++;	
				}
				else if(!strcmp(transfusion.sector,"oncologia")){
				sectores[5]++;
				}
				else if(!strcmp(transfusion.sector,"UTI")){
				sectores[6]++;	
				}
				fread(&transfusion,sizeof(struct Transfusiones),1,f);
			}
			for(i=0;i<7;i++){
				if(j<sectores[i]){
					j=sectores[i];
					aux[i]=1;
				}
			}
			for(i=0;i<7;i++){
				if(aux[i]==1){
					printf("El sector o los sectores con mas transfusiones son: %s con un total de: %d transfusiones.\n",sec[i],j);
				}
			}
			fclose(f);
		}else perror("ERROR APERTURA DEL ARCHIVO Transfusiones.dat: ");
		
		printf("\n\n");
	}
	
	/*----- GENERAR COMPROBANTES DE TRANSFUSION -----*/
	void comp(int numg,int cant){
		FILE *f,*arch;
		struct Transfusiones tra;
		char nomarch[100];
		int i=0;
		if(cant==0){
			if((f=fopen("Transfusiones.dat","rb"))!=NULL){
				
				fread(&tra,sizeof(struct Transfusiones),1,f);
				while(!feof(f)){
				strcpy(nomarch,"Comprobante ");
				strcat(nomarch,tra.paciente);
				strcat(nomarch,".txt");
					if((arch=fopen(nomarch,"w"))!=NULL){
						fprintf(arch,"%s %d \n","Numero de guía:",tra.numguia);
						fprintf(arch,"%s %s \n","Paciente:",tra.paciente);
						fprintf(arch,"%s %d \n","Fecha de transfusión:",tra.fechatrans);
						fprintf(arch,"%s %s \n","Médico solicitante:",tra.medico);
						fprintf(arch,"%s %s \n","Técnico a cargo:",tra.tecnico);
						fprintf(arch,"%s %s \n","Hemocomponente:",tra.hemocom);
						fprintf(arch,"%s %s \n","Sector:",tra.sector);
						fclose(arch);
						fread(&tra,sizeof(struct Transfusiones),1,f); printf("\n----- SE REALIZO CON EXITO EL COMPROBANTE DE LA TRANSFUSION: %d -----\n",tra.numguia);
					}else {printf("ERROR CREACION ARCHIVO %s: ",nomarch);perror("");}		
				}
				i=1;
				fclose(f);	
			}else perror("ERROR APERTURA ARCHIVO Transfusiones.dat: ");
				
		}else if((f=fopen("Transfusiones.dat","rb"))!=NULL){
			fread(&tra,sizeof(struct Transfusiones),1,f);
			while(!feof(f)){
				if(tra.numguia==numg){
					i=1;
					strcpy(nomarch,"Comprobante ");
					strcat(nomarch,tra.paciente);
					strcat(nomarch,".txt");
					
					if((arch=fopen(nomarch,"w"))!=NULL){
						
						fprintf(arch,"%s %d \n","Numero de guía:",tra.numguia);
						fprintf(arch,"%s %s \n","Paciente:",tra.paciente);
						fprintf(arch,"%s %d \n","Fecha de transfusión:",tra.fechatrans);
						fprintf(arch,"%s %s \n","Médico solicitante:",tra.medico);
						fprintf(arch,"%s %s \n","Técnico a cargo:",tra.tecnico);
						fprintf(arch,"%s %s \n","Hemocomponente:",tra.hemocom);
						fprintf(arch,"%s %s \n","Sector:",tra.sector);
						fclose(arch);
						printf("\n----- SE REALIZO CON EXITO EL COMPROBANTE DE LA TRANSFUSION: %d -----\n",tra.numguia);
						
					}else {printf("ERROR CREACION ARCHIVO %s: ",nomarch);perror("");}
				}
			fread(&tra,sizeof(struct Transfusiones),1,f);
			}
		}
	if(i!=1){printf("/-\\ EL NUMERO DE GUIA INGRESADO NO EXISTE /-\\\n");} printf("\n\n"); 
	}
	
	
	/*----- FUNCION PRINCIPAL AGREGAR -----*/	
	void agregar(){
		int h=99;
		while(h!=0){
		printf("Si quiere agregar registros al archivo de Pacientes presione 1\n");
		printf("Si quiere agregar registros al archivo de Medicos presione 2\n");
		printf("Si quiere agregar registros al archivo de Sanatorios presione 3\n");
		printf("Si quiere agregar registros registros al archivo de Extracciones presione 4\n");
		printf("Si quiere agregar registros al archivo de Transfusiones presione 5\n\n");
		printf("Para regresar presione 0\n");
		printf("Seleccion:|--- ");
		
		scanf("%d",&h);
		fflush(stdin);
		
			switch(h) {
				case 1:{
				printf("\n\n");
				agregarpac();
				break;}
				
				case 2:{
				printf("\n\n");
				agregarmed();
				break;}
				
				case 3:{
				printf("\n\n");
				agregarsana();
				break;}
				
				case 4:{
				printf("\n\n");
				agregarextra();
				break;}
				
				case 5:{
				printf("\n\n");
				agregartrans();
				break;}
			}
		
			if((h!=0)&&(h!=1)&&(h!=2)&&(h!=3)&&(h!=4)&&(h!=5)){
			printf("\nINGRESO UN VALOR INCORRECTO, INGRESE OTRA VEZ LA SELECCION \n\n");}	
		}
		printf("\n\n");
	}

	/*----- AGREGAR PACIENTES -----*/
	void agregarpac(){
		struct Pacientes pac;
		FILE *f;
		
		printf("Ingrese el nombre del paciente: "); gets(pac.nombre);
		printf("\nIngrese el DNI del paciente: "); scanf("%d",&pac.dni); fflush(stdin);
		printf("\nIngrese la fecha de nacimiento del paciente en formato \n AAAAMMDD:\n "); scanf("%d",&pac.fechdenac); fflush(stdin);
		printf("\nIngrese el genero del paciente F si es femenino o M si es masculino: "); scanf("%c",&pac.gen); fflush(stdin);
		printf("\nIngrese la direccion del paciente: "); gets(pac.direccion);
		printf("\nIngrese el telefono del paciente: "); scanf("%lu",&pac.telefono); fflush(stdin);
		printf("\nIngrese el grupo sanguineo del paciente: "); gets(pac.grupsan);
		printf("\nIngrese el factor rh del paciente: "); gets(pac.rh);
		printf("\nIngrese la obra social del paciente: "); gets(pac.obrasoc);
		printf("\nIngrese el diagnostico del paciente: "); gets(pac.diagnostico);
		printf("\nIngrese el nombre del familiar: "); gets(pac.nomfam);
		printf("\nIngrese el dni del familiar "); scanf("%d",&pac.dnifam); fflush(stdin);
		printf("\nIngrese el telefono del familiar "); scanf("%lu",&pac.telfam); fflush(stdin);
		printf("\nIngrese el parentesco que tiene con el paciente: "); gets(pac.paren);
	
		if((f=fopen("Pacientes.dat","ab"))!=NULL){
			fseek(f,sizeof(struct Pacientes),SEEK_END);
			fwrite(&pac,sizeof(struct Pacientes),1,f);
			printf("\n\n--- SE AGREGO EL REGISTRO CON EXITO ---\n");
			fclose(f);} else perror("ERROR APERTURA ARCHIVO Pacientes.dat: ");
		
		printf("\n\n");
	}

	/*----- AGREGAR MEDICOS -----*/
	void agregarmed(){
		struct Medicos med;
		FILE *f;
		printf("INGRESE EL NOMBRE DEL MEDICO: ");gets(med.nombre);
		printf("\nINGRESE EL DNI: "); scanf("%i",&med.dni); fflush(stdin);
		printf("\nINGRESE LA MATRICULA: "); scanf("%i",&med.matri); fflush(stdin);
		printf("\nINGRESE LA ESPECIALIDAD: ");gets(med.especialidad);
		
		if((f=fopen("Medicos.dat","ab"))!=NULL){
			fseek(f,sizeof(struct Medicos),SEEK_END);
			fwrite(&med,sizeof(struct Medicos),1,f);
			printf("\n\n--- SE AGREGO EL REGISTRO CON EXITO ---\n");
			fclose(f);}	else perror("ERROR APERTURA ARCHIVO Medicos.dat: ");
			
		printf("\n\n");
	}
	
	/*----- AGREGAR SANATORIOS -----*/
	void agregarsana(){
		struct Sanatorios sana;
		FILE *f;
		printf("INGRESE EL NOMBRE DEL SANATORIO: ");fflush(stdin);	gets(sana.nombre);
		printf("\nINGRESE LA DIRECCION DEL SANATORIO: ");fflush(stdin);	gets(sana.direccion);
		
		if((f=fopen("Sanatorios.dat","ab"))!=NULL){
			fseek(f,sizeof(struct Sanatorios),SEEK_END);
			fwrite(&sana,sizeof(struct Sanatorios),1,f);
			printf("\n\n--- SE AGREGO EL REGISTRO CON EXITO ---\n");
			fclose(f);}	else perror("ERROR APERTURA ARCHIVO Sanatorios.dat: ");
			
		printf("\n\n");
	}
	
	/*----- AGREGAR EXTRACCIONES -----*/
	void agregarextra(){
		struct Extracciones extra;
		FILE *f;
		printf("INGRESE EL NUMERO DE GUIA: "); scanf("%i",&extra.numguia); fflush(stdin);
		printf("\nINGRESE LA FECHA DE EXTRACCION AAAAMMDD: "); scanf("%i",&extra.fechextra); fflush(stdin);
		printf("\nINGRESE LA FECHA DE VENCIMIENTO AAAAMMDD: ");	scanf("%i",&extra.fechaven); fflush(stdin);
		printf("\nINGRESE EL GRUPO SANGUINEO: "); gets(extra.gruposan);
		printf("\nINGRESE EL RH: "); gets(extra.rh);
		printf("\nINGRESE EL HEMOCOMPONENTE: "); gets(extra.hemocom);
		
			if((f=fopen("Extracciones.dat","ab"))!=NULL){
				fseek(f,sizeof(struct Extracciones),SEEK_END);
				fwrite(&extra,sizeof(struct Extracciones),1,f);
				printf("\n\n--- SE AGREGO EL REGISTRO CON EXITO ---\n");
				fclose(f);}	else perror("ERROR APERTURA ARCHIVO Extracciones.dat: ");
				
		printf("\n\n");
	}
	
	/*----- AGREGAR TRANSFUSiONES -----*/
	void agregartrans(){
		struct Transfusiones tran;
		
		FILE *f;
		printf("INGRESE LA UNIDAD DE SANGRE: "); scanf("%d",&tran.numguia); fflush(stdin);
		printf("\nINGRESE EL HEMOCOMPONENTE:  "); gets(tran.hemocom);
		printf("\nINGRESE EL NOMBRE DEL PACIENTE:  "); gets(tran.paciente);
		printf("\nINGRESE LA FECHA DE TRANSFUSION: "); scanf("%d",&tran.fechatrans); fflush(stdin);
		printf("\nINGRESE EL MEDICO SOLICITANTE: "); gets(tran.medico);
		printf("\nINGRESE EL NOMBRE Y DNI DEL TECNICO: "); gets(tran.tecnico);
		printf("\nINGRESE EL SECTOR: "); gets(tran.sector);
		if((f=fopen("Transfusiones.dat","ab"))!=NULL){
			fseek(f,sizeof(struct Transfusiones),SEEK_END);
			fwrite(&tran,sizeof(struct Transfusiones),1,f);
			printf("\n\n--- SE AGREGO EL REGISTRO CON EXITO ---\n");
			fclose(f);}	else perror("ERROR APERTURA ARCHIVO Transfusiones.dat: ");
			
		printf("\n\n");
	}
	
	/*----- FUNCION PRINCIPAL ELIMINAR -----*/
	void eliminar(){
		int h=99;
		while(h!=0){
		printf("Si quiere eliminar registros al archivo de Pacientes presione 1\n");
		printf("Si quiere eliminar registros al archivo de Medicos presione 2\n");
		printf("Si quiere eliminar registros al archivo de Sanatorios presione 3\n");
		printf("Si quiere eliminar registros registros al archivo de Extracciones presione 4\n");
		printf("Si quiere eliminar registros al archivo de Transfusiones presione 5\n\n");
		printf("Para regresar presione 0\n");
		printf("Seleccion:|--- ");
		scanf("%d",&h);
		fflush(stdin);
		switch(h) {
			case 1:{
				printf("\n\n");
				eliminpac();
				break;}
			case 2:{
				printf("\n\n");
				eliminmed();
				break;}
			case 3:{
				printf("\n\n");
				eliminsan();
				break;}
			case 4:{
				printf("\n\n");
				eliminextra();
				break;}
			case 5:{
				printf("\n\n");
				elimintrans();
				break;}
		}
			if((h!=0)&&(h!=1)&&(h!=2)&&(h!=3)&&(h!=4)&&(h!=5)){
			printf("\nINGRESO UN VALOR INCORRECTO, INGRESE OTRA VEZ LA SELECCION \n\n");
			}
		}
		printf("\n\n");
	}
	
	/*----- ELIMINAR PACIENTES -----*/
	void eliminpac(){
		FILE *arch,*f;
	    int cod;
	    int i=0,j=0,ex=0;
	    struct Pacientes pac;
	    
	    if((arch=fopen("Pacientes.dat","r+b"))!=NULL){
	    	printf("INGRESE EL DNI DEL REGISTRO A ELIMINAR: "); scanf("%d", &cod);
	    	
		    fread(&pac,sizeof(struct Pacientes),1,arch);
		    while(!(feof(arch))){
		    	if(cod!=pac.dni){
				i++;}
				if(cod==pac.dni){
				ex=1;}
		    fread(&pac,sizeof(struct Pacientes),1,arch);}
		
			struct Pacientes pac2[i];
			rewind(arch);
			i=0;
			
			fread(&pac,sizeof(struct Pacientes),1,arch);
		    while(!(feof(arch))){
		    	if(cod!=pac.dni){
		    	pac2[i]=pac;
		    	i++;}
	    	fread(&pac,sizeof(struct Pacientes),1,arch);}
		
		fclose(arch);
		
			if((f=fopen("Pacientes.dat","wb"))!=NULL){
			for(j=0;j<i;j++){
				fwrite(&pac2[j],sizeof(struct Pacientes),1,f);}
			fclose(f);}
			
			if(ex==1)printf("\n--- BORRADO EXITOSO ---\n");
			if(ex==0) printf("\n\n--- EL DNI INGRESADO NO EXISTE ---\n");
			
		}else perror("ERROR APERTURA DEL ARCHIVO Pacientes.dat: ");	
		printf("\n\n");
	}
	
	/*----- ELIMINAR MEDICOS -----*/
	void eliminmed(){
		FILE *arch,*f;
	    int cod;
	    int i=0,j=0,ex=0;
	    struct Medicos med;
	    
	    if((arch=fopen("Medicos.dat","r+b"))!=NULL){
	    	printf("INGRESE LA MATRICULA DEL REGISTRO A ELIMINAR: "); scanf("%d", &cod);
	    	
		    fread(&med,sizeof(struct Medicos),1,arch);
		    while(!(feof(arch))){
		    	if(cod!=med.matri){
				i++;}
				if(cod==med.matri){
				ex=1;}
		    fread(&med,sizeof(struct Medicos),1,arch);}
		
			struct Medicos med2[i];
			rewind(arch);
			i=0;
			
			fread(&med,sizeof(struct Medicos),1,arch);
		    while(!(feof(arch))){
		    	if(cod!=med.matri){
		    	med2[i]=med;
		    	i++;}
	    	fread(&med,sizeof(struct Medicos),1,arch);}
		
		fclose(arch);
		
			if((f=fopen("Medicos.dat","wb"))!=NULL){
			for(j=0;j<i;j++){
				fwrite(&med2[j],sizeof(struct Medicos),1,f);}
			fclose(f);}
			
			if(ex==1) printf("\nBORRADO EXITOSO");
			if(ex==0) printf("\n\n--- LA MATRICULA INGRESADA NO EXISTE ---\n");
			
		}else perror("ERROR APERTURA DEL ARCHIVO Medicos.dat: ");
		printf("\n\n");
	}

	/*----- ELIMINAR EXTRACCION -----*/
	void eliminextra(){
	    FILE *arch,*f;
	    int cod;
	    int i=0,j=0,ex=0;
	    struct Extracciones ext;
	
	    if((arch=fopen("Extracciones.dat","r+b"))!=NULL){
	        printf("INGRESE EL NUMERO DE GUIA DEL REGISTRO A ELIMINAR: "); scanf("%d", &cod);
	        	
	        fread(&ext,sizeof(struct Extracciones),1,arch);
	        while(!(feof(arch))){
	            if(cod!=ext.numguia){
	            i++;}
	            if(cod==ext.numguia){
	            ex=1;}
	        fread(&ext,sizeof(struct Extracciones),1,arch);}
	
	        struct Extracciones ext2[i];
	        rewind(arch);
	        i=0;
	
	        fread(&ext,sizeof(struct Extracciones),1,arch);
	        while(!(feof(arch))){
	            if(cod!=ext.numguia){
	            ext2[i]=ext;
	            i++;}
	        fread(&ext,sizeof(struct Extracciones),1,arch);}
	
	    fclose(arch);
	
	        if((f=fopen("Extracciones.dat","wb"))!=NULL){
	        for(j=0;j<i;j++){
	            fwrite(&ext2[j],sizeof(struct Extracciones),1,f);}
	        fclose(f);}
	            
	        if(ex==1)printf("\n\n--- BORRADO EXITOSO ---\n");
	        if(ex==0) printf("\n\n--- EL NUMERO DE GUIA INGRESADO NO EXISTE ---\n");
	
	    }else perror("ERROR APERTURA ARCHIVO Extracciones.dat: ");
	    printf("\n\n");
	}
    
    /*----- ELIMINAR SANATORIOS -----*/
    void eliminsan(){
        FILE *arch,*f;
        int i=0,j=0,ex=0;
        char cod[20];
        struct Sanatorios str;

        if((arch=fopen("Sanatorios.dat","r+b"))!=NULL){
        	printf("INGRESE EL NOMBRE DEL SANATORIO QUE DESEA ELIMINAR: "); gets(cod);
        	
            fread(&str,sizeof(struct Sanatorios),1,arch);
            while(!(feof(arch))){
                 if (strcmp(str.nombre,cod)){
                i++;}
                 if (!strcmp(str.nombre,cod)){
                ex=1;}
            fread(&str,sizeof(struct Sanatorios),1,arch);}
            struct Sanatorios str2[i];
            rewind(arch);
            i=0;

            fread(&str,sizeof(struct Sanatorios),1,arch);
            while(!(feof(arch))){
                     if (strstr(str.nombre,cod) == NULL){
                str2[i]=str;
                i++;}
            fread(&str,sizeof(struct Sanatorios),1,arch);}

        fclose(arch);

            if((f=fopen("Sanatorios.dat","wb"))!=NULL){
            for(j=0;j<i;j++){
                fwrite(&str2[j],sizeof(struct Sanatorios),1,f);}
            fclose(f);}
            
            if(ex==1)printf("\n\n--- BORRADO EXITOSO ---\n");
            if(ex==0) printf("\n\n--- EL NOMBRE DEL SANATORIO NO EXISTE---\n");

        }else perror("ERROR APERTURA ARCHIVO Sanatorios.dat: ");
        printf("\n\n");
    }
    
    /*----- ELIMINAR TRANSFUSION -----*/
    void elimintrans(){
        FILE *arch,*f;
        int cod;
        int i=0,j=0,ex=0;
        struct Transfusiones tr;

        if((arch=fopen("Transfusiones.dat","r+b"))!=NULL){
        	printf("INGRESE EL NUMERO DE GUIA DEL REGISTRO A ELIMINAR: "); scanf("%d", &cod);
        	
            fread(&tr,sizeof(struct Transfusiones),1,arch);
            while(!(feof(arch))){
                if(cod!=tr.numguia){
                i++;}
                if(cod==tr.numguia){
                ex=1;}
            fread(&tr,sizeof(struct Transfusiones),1,arch);}

            struct Transfusiones tr2[i];
            rewind(arch);
            i=0;

            fread(&tr,sizeof(struct Transfusiones),1,arch);
            while(!(feof(arch))){
                if(cod!=tr.numguia){
                tr2[i]=tr;
                i++;}
            fread(&tr,sizeof(struct Transfusiones),1,arch);}

        fclose(arch);

            if((f=fopen("Transfusiones.dat","wb"))!=NULL){
            for(j=0;j<i;j++){
                fwrite(&tr2[j],sizeof(struct Transfusiones),1,f);}
            fclose(f);}
            
            if(ex==1) printf("\n\n--- BORRADO EXITOSO ---\n");
            if(ex==0) printf("\n\n---LA MATRICULA INGRESADA NO EXISTE---\n");

        }else perror("ERROR APERTURA ARCHIVO Transfusiones.dat: ");
        printf("\n\n");
    }

	/*----- FUNCION PRINCIPAL MODIFICAR -----*/
	void modificar(){
		int h=99;
		while(h!=0){
		printf("Si quiere modificar registros al archivo de Pacientes presione 1\n");
		printf("Si quiere modificar registros al archivo de Medicos presione 2\n");
		printf("Si quiere modificar registros al archivo de Sanatorios presione 3\n");
		printf("Si quiere modificar registros registros al archivo de Extracciones presione 4\n");
		printf("Si quiere modificar registros al archivo de Transfusiones presione 5\n\n");
		printf("Para regresar presione 0\n");
		printf("Seleccion:|--- ");
		scanf("%d",&h);
		fflush(stdin);
		switch(h) {
			case 1:{
				printf("\n\n");
				modificarpac();
				break;}
			case 2:{
				printf("\n\n");
				modificarmed();
				break;}
			case 3:{
				printf("\n\n");
				modificarsan();
				break;}
			case 4:{
				printf("\n\n");
				modificarextra();
				break;}
			case 5:{
				printf("\n\n");
				modificartrans();
				break;}
		}
			if((h!=0)&&(h!=1)&&(h!=2)&&(h!=3)&&(h!=4)&&(h!=5)){
			printf("\nINGRESO UN VALOR INCORRECTO, INGRESE OTRA VEZ LA SELECCION \n\n");
			}
		}
		printf("\n\n");
	}
		


	/*----- FUNCION MODIFICAR PACIENTE -----*/
	void modificarpac(){
	    FILE *arch;
	    int cod,i,existe=0,aux=0;
	    struct Pacientes pc;
	    
	    if ((arch=fopen("Pacientes.dat","r+b"))!=NULL){
	    	
	    	printf("INGRESE EL DNI DEL PACIENTE A MODIFICAR: ");
	    	scanf("%i", &cod);
	    	fflush(stdin);
	    	
	    	fread(&pc, sizeof(struct Pacientes), 1, arch);
	    	while(!feof(arch)){
	    		if(cod==pc.dni)
	    		aux=1;
	    	fread(&pc, sizeof(struct Pacientes), 1, arch);}
			
			rewind(arch);
			fread(&pc, sizeof(struct Pacientes), 1, arch);
	   		while(!feof(arch)&&aux==1){
	      		if (cod==pc.dni){
	   			printf("REGISTRO %d",i);
	   			i++;
		   		printf("-------- INGRESE LOS NUEVOS DATOS ----------\n");
	   			printf("INGRESE EL NOMBRE DEL PACIENTE: "); gets(pc.nombre);
				printf("INGRESE EL DNI: "); scanf("%d",&pc.dni); fflush(stdin);
				printf("INGRESE LA FECHA DE NACIEMIENTO AAAAMMDD: "); scanf("%d",&pc.fechdenac); fflush(stdin);
				printf("INGRESE EL GENERO: "); scanf("%c",&pc.gen); fflush(stdin); fflush(stdin);
				printf("INGRESE LA DIRECCION: "); gets(pc.direccion);	
				printf("INGRESE EL RH: "); gets(pc.rh);
				printf("INGRESE EL NUMERO DE TELEFONO: "); scanf("%lu",&pc.telefono);fflush(stdin);
				printf("INGRESE EL GRUPO SANGUINEO "); gets(pc.grupsan);
				printf("INGRESE LA OBRA SOCIAL: "); gets(pc.obrasoc); 
				printf("INGRESE EL DIAGNOSTICO: "); gets(pc.diagnostico);
				printf("INGRESE EL NOMBRE DEL FAMILIAR A CARGO: "); gets(pc.nomfam);
				printf("INGRESE EL DNI DEL FAMILIAR A CARGO: "); scanf("%i",&pc.dnifam); fflush(stdin);
				printf("INGRESE EL NUMERO DE TELEFONO DEL FAMILIAR A CARGO: "); scanf("%lu",&pc.telfam); fflush(stdin);
				printf("INGRESE EL PARENTEZCO QUE TIENE CON EL PACIENTE: "); gets(pc.paren);
			    int pos=ftell(arch)-sizeof(struct Pacientes);
    			fseek(arch,pos,SEEK_SET);
    			fwrite(&pc,sizeof(struct Pacientes), 1, arch);
	    		existe=1;
	    		aux=0;
	           	}
			fread(&pc, sizeof(struct Pacientes),1, arch);}
			
			if (existe==1) printf("\n\n--- MODIFICACION EXITOSA ---\n");
			if (existe==0) printf("\n\n--- NO EXISTE ESE DNI EN EL REGISTRO ---\n");
			
			fclose(arch);
			
			
		}else perror("ERROR APERTURA ARCHIVO Pacientes.dat: ");
	        
	    
	    printf("\n\n");
	}	


	
	/*----- FUNCION MODIFICAR MEDICOS -----*/
	void modificarmed(){
		FILE *arch;
	    int cod,i,existe=0,aux=0, pos;
	    struct Medicos med;
	    
	    if ((arch=fopen("Medicos.dat","r+b"))!=NULL){
	    	
	    	printf("INGRESE LA MATRICULA DEL MEDICO A MODIFICAR: ");
	    	scanf("%i", &cod);
	    	fflush(stdin);
	    	
	    	fread(&med, sizeof(struct Medicos), 1, arch);
	    	while(!feof(arch)){
	    		if(cod==med.matri)
	    		aux=1;
	    	fread(&med, sizeof(struct Medicos), 1, arch);}
			
			rewind(arch);
			fread(&med, sizeof(struct Medicos), 1, arch);
	   		while(!(feof(arch))&&aux==1){
	      		if (cod==med.matri){
	   			printf("REGISTRO %d",i);
	   			i++;
		   		printf("-------- INGRESE LOS NUEVOS DATOS ----------\n");
	   			printf("INGRESE EL NOMBRE: "); gets(med.nombre);
	   			printf("INGRESE LA MATRICULA: "); scanf("%d",&med.matri);fflush(stdin);
	   			printf("INGRESE EL DNI: "); scanf("%d",&med.dni);fflush(stdin);
	   			printf("INGRESE LA ESPECIALIDAD: "); gets(med.especialidad);
	   			pos=ftell(arch)-sizeof(struct Medicos);
    			fseek(arch,pos,SEEK_SET);
    			fwrite(&med,sizeof(struct Medicos), 1, arch);
	    		existe=1;
	    		aux=0;
	           	}
			fread(&med, sizeof(struct Medicos),1, arch);}
			
			if (existe==1) printf("\n\n--- MODIFICACION EXITOSA ---\n");
			if (existe==0) printf("\n\n--- NO EXISTE ESA MATRICULA EN EL REGISTRO ---\n");
			
			fclose(arch);
			
		}else perror("ERROR APERTURA ARCHIVO Medicos.dat: ");
	        
	    printf("\n\n");		
	}
	
	/*----- FUNCION MODIFICAR SANATORIOS -----*/	
	void modificarsan(){
		char cod[30];
		FILE *arch;
		int i,existe=0;
	    
	    if ((arch=fopen("Sanatorios.dat","r+b"))!=NULL){
	         
	    
	    printf("INGRESE EL NOMBRE DEL SANATORIO QUE DESEA MODIFICAR "); fflush(stdin); gets(cod);
	   	struct Sanatorios str;
	    fread(&str, sizeof(struct Sanatorios), 1, arch);
	    
	    while(!feof(arch))
	    {
	         if (strstr(str.nombre,cod) != NULL){
	    		printf("\nINGRESE EL NOMBRE DEL SANATORIO: ");fflush(stdin);    gets(str.nombre);
	   			printf("\nINGRESE LA DIRECCION DEL SANATORIO: ");fflush(stdin);    gets(str.direccion);
	   			
	           	int pos=ftell(arch)-sizeof(struct Sanatorios);
	           	fseek(arch,pos,SEEK_SET);
	           	fwrite(&str, sizeof(struct Sanatorios), 1, arch);
	           	existe=1;
	           break;}
	        fread(&str, sizeof(struct Sanatorios),1, arch);
	        
	    }
	    if (existe==0) printf("\n\nNO EXISTE ESTE NOMBRE EN EL REGISTRO\n");
	    if (existe==1) printf("\n\n--- MODIFICACION EXITOSA ---\n");
	    
	    fclose(arch);
		}else perror("ERROR APERTURA ARCHIVO Sanatorios.dat: ");
		
	    printf("\n\n");
	}

	/*----- FUNCION MODIFICAR EXTRACCIONES -----*/
	void modificarextra(){
		FILE *arch;
		int cod=0,i=0,existe=0;
		struct Extracciones ext;
		
    	if ((arch=fopen("Extracciones.dat","r+b"))!=NULL){
    		
    	printf("INGRESAR EL NUMERO DE GUIA A MODIFICAR: ");
    	scanf("%i", &cod);
    	fflush(stdin);
    	
    	fread(&ext, sizeof(struct Extracciones), 1, arch);
		while(!feof(arch)){
        	if (cod==ext.numguia){
        	
		    printf("\nINGRESE EL NUMERO DE GUIA: "); scanf("%i",&ext.numguia); fflush(stdin);
		    printf("\nINGRESE LA FECHA DE EXTRACCION AAAAMMDD: "); scanf("%i",&ext.fechextra); fflush(stdin);
		    printf("\nINGRESE LA FECHA DE VENCIMIENTO AAAAMMDD: "); scanf("%i",&ext.fechaven); fflush(stdin);
		    printf("\nINGRESE EL GRUPO SANGUINEO: "); gets(ext.gruposan);
		    printf("\nINGRESE EL RH: "); gets(ext.rh);
		    printf("\nINGRESE EL HEMOCOMPONENTE: "); gets(ext.hemocom);
		    
           int pos=ftell(arch)-sizeof(struct Extracciones);
           fseek(arch,pos,SEEK_SET);
           fwrite(&ext, sizeof(struct Extracciones), 1, arch);
           existe=1;
		   break;}
           
        fread(&ext, sizeof(struct Extracciones),1, arch);}
        
    	if (existe==0) printf("\n\nNO EXISTE ESTE NUMERO DE GUIA EN EL ARCHIVO\n");
    	if (existe==1) printf("\n\n--- MODIFICACION EXITOSA ---\n");
    	
    	fclose(arch);
    	
		}else perror("ERROR APERTURA ARCHIVO Extracciones.dat: ");
		printf("\n\n");
	}
	
	/*----- FUNCION MODIFICAR TRANSFUSIONES -----*/
	void modificartrans(){
		
		FILE *arch;
		int cod=0,i=0,existe=0;
		struct Transfusiones ext;
		
    	if ((arch=fopen("Transfusiones.dat","r+b"))!=NULL){
    		
    	printf("INGRESAR EL NUMERO DE GUIA A MODIFICAR: ");
    	scanf("%i", &cod);
    	fflush(stdin);
    	
    	fread(&ext, sizeof(struct Transfusiones), 1, arch);
		while(!feof(arch)){
        	if (cod==ext.numguia){
        	
		    printf("\nINGRESE EL NUMERO DE GUIA: "); scanf("%i",&ext.numguia); fflush(stdin);
		    printf("\nINGRESE EL HEMOCOMPONENTE: "); gets(ext.hemocom);
		    printf("\nINGRESE EL NOMBRE DEL PACIENTE: "); gets(ext.paciente);
		    printf("\nINGRESE LA FECHA DE TRANSFUSION EN FORMATO AAAAMMDD: "); scanf("%i",&ext.fechatrans); fflush(stdin);
		    printf("\nINGRESE EL NOMBRE DEL MEDICO SOLICITANTE: "); gets(ext.medico);
		    printf("\nINGRESE EL NOMBRRE Y EL DNI DEL TECNICO: "); gets(ext.tecnico);
		    printf("\nINGRESE EL SECTOR: "); gets(ext.sector);
		    
           int pos=ftell(arch)-sizeof(struct Transfusiones);
           fseek(arch,pos,SEEK_SET);
           fwrite(&ext, sizeof(struct Transfusiones), 1, arch);
           existe=1;
		   break;}
           
        fread(&ext, sizeof(struct Transfusiones),1, arch);}
        
    	if (existe==0) printf("\n\nNO EXISTE ESTE NUMERO DE GUIA EN EL ARCHIVO\n");
    	if (existe==1) printf("\n\n--- MODIFICACION EXITOSA ---\n");
    	
    	fclose(arch);
    	
		}else perror("ERROR APERTURA ARCHIVO Transfusiones.dat: ");
		printf("\n\n");
		
	}
