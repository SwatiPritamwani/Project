/*****************************************************************************
 * "Contact Management System" 
 *
 * This code performs various operations mainly used in phonebook.
 *
 * Copyright (C) 2015 Swati Pritamwani
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<ctype.h>
#include<stdlib.h> 
#include<termios.h>
#include<unistd.h>
#define sclear() printf("\033[H\033[J")
struct person {
    char title[30];
    char name[35];
    char address[50];
    char father_name[35];
    char mother_name[30];
    char mble_no[30];
    char sex[8];
    char email[100];
    char citision_no[20];
    char groupname[30];
    char savew[30];
};

void menu();
void start();
void back();
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();
void duplicate_find();
void duplicate_check();

char temp[30];
int cd=1;
int getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
int getche() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

int main() {
    start();
    return 0;
}
void back() {
    start();
}
void start() {
    menu();
}
void menu() {
	sclear();
	printf("\tWELCOME TO CONTACT MANAGEMENT SYSTEM");
	printf("\n\nMENU\n");
	printf("\n1.Add New Contacts\n2.List Contacts\n3.Delete Contacts\n4.Modify Contacts\n5.Search Contacts");
	printf("\n6.Duplicate Contacts count\n7.Exit"); 
	printf("\n\nChoose one option form above = ");
	switch(getch()) {
    		case '1':addrecord();
    			break;
		case '2': listrecord();
    			break;
   	        case '3': deleterecord();
    			break;
    		case '4': modifyrecord();
    			break;
    		case '5': searchrecord();
    			break;
    		case '6': duplicate_find();
    			break;
		case '7': exit(0);
   			 break;
    		default:
                	sclear();
                	printf("\nEnter 1 to 6 only");
                	printf("\n Enter any key");
                	getch();
			menu();
	}
}
void duplicate_find() {
	struct person p;
	FILE *f;
	char mble[30];
	int fl,cc;
	fl=1;
	cc=0;
	f=fopen("mf.txt","rb");
	if(f==NULL) {
		printf("\n error in opening\a\a\a\a");
	}
	printf("\nEnter Phone Number = ");
	fflush(stdin);
	gets(mble);
	while(fread(&p,sizeof(p),1,f)==1) {
		if(strcmp(p.mble_no,mble)==0) {
			printf("\n\tInformation For %s",mble);
			printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
			cc=cc+1;
			fl=2;
		}
	}
	if(fl==1) {
		printf("DATA not found");
	}
	else {
		printf("Duplicate data find %d times",cc-1);
	}
	fclose(f);
	printf("\n Enter any key");
	getch();
	sclear();
	menu();
}
void addrecord() {
	FILE *psf;
	FILE *psfr;
	FILE *ssf;
	FILE *ssfr;
	FILE *mf;
        struct person p;
        sclear();
	psf=fopen("psf.txt","ab+");
	psfr=fopen("psfr.txt","ab+");
	ssf=fopen("ssf.txt","ab+");
	ssfr=fopen("ssfr.txt","ab+");
	mf=fopen("mf.txt","ab+");	
        printf("\n Enter Title: ");
        gets(p.title);
        printf("\n Enter name: ");
        gets(p.name);
        printf("\nEnter the address: ");
        gets(p.address);
        printf("\nEnter father name: ");
        gets(p.father_name);
        printf("\nEnter mother name: ");
        gets(p.mother_name);
        printf("\nEnter phone no.:");
        gets(p.mble_no);
        printf("Enter sex:");
        gets(p.sex);
        printf("\nEnter e-mail:");
        gets(p.email);
        printf("\nEnter citizen no:");
        gets(p.citision_no);
	printf("\nEnter group name(family/friend):");
        gets(p.groupname);
	printf("\nEnter Storage name(sim/phone):");
        gets(p.savew);
	strcpy(temp,p.mble_no);
	duplicate_check();
	if(cd==1) {
		if(strcmp(p.savew,"sim")==0) {
			if(strcmp(p.groupname,"family")==0) {
				fwrite(&p,sizeof(p),1,ssf);
				fflush(stdin);
				printf("\n record saved");
				fclose(ssf);
			}
			else if(strcmp(p.groupname,"friend")==0) {
				fwrite(&p,sizeof(p),1,ssfr);
				fflush(stdin);
				printf("\n record saved");
				fclose(ssfr);
			}
			else {
				printf("\nInvalid group name!! please try again");
				getch();
				addrecord();
			}
		}
		else if(strcmp(p.savew,"phone")==0) {
			if(strcmp(p.groupname,"family")==0) {
				 fwrite(&p,sizeof(p),1,psf);
				 fflush(stdin);
				 printf("\n record saved");
				 fclose(psf);
			}
			else if(strcmp(p.groupname,"friend")==0) {
				fwrite(&p,sizeof(p),1,psfr);
				fflush(stdin);
				printf("\n record saved");
				fclose(psfr);
			}
			else {
				printf("\nInvalid group name!! please try again");
				getch();
				addrecord();
			}
		}
		else {
			printf("\nInvalid Storage Type!! please try again");
			getch();
			addrecord();
		}
		fwrite(&p,sizeof(p),1,mf);
		fclose(mf);
	}
	else {
       		 printf("Error!!Duplicate contact present ");
	}  
        printf("\n\nEnter any key");
	getch();
	sclear();
        menu();
}
void duplicate_check() {
	struct person p;
	FILE *f;
	int cc;
	cc=1;
	f=fopen("mf.txt","rb");
	if(f==NULL) {
		printf("\n error in opening\a\a\a\a");
	}
	while(fread(&p,sizeof(p),1,f)==1) {
		if(strcmp(p.mble_no,temp)==0) {
			printf("\ncc: %d",cc);
			cc=cc+1;
			if(cc==2) {
				cd=2;
				break;
			}
		}
	}
	fclose(f);
}
void listrecord() {
	struct person p;
        FILE *f;
	printf("\nLIST CONTACTS MENU\n");
	printf("\n1.By Group\n2.By Storage\n3.All From Both\n4.Exit");
	printf("\n\nChoose one option form above = ");
	switch(getch()) {
    		case '1':
			sclear();
			printf("\nGROUP WISE CONTACTS MENU\n");
			printf("\n1.By Friend\n2.By Family\n3.All From Both\n4.Exit");
			printf("\n\nChoose one option form above = ");
			switch(getch()) {
				case '1':
					f=fopen("ssfr.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					f=fopen("psfr.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
				       		printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					printf("\n Enter any key");
				        getch();
					sclear();
					menu();
					break;
				case '2': 
					f=fopen("ssf.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					f=fopen("psf.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					printf("\n Enter any key");
					getch();
					sclear();
					menu();
					break;
				case '3': 
					f=fopen("ssfr.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					f=fopen("psfr.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						 printf("\n\n\n YOUR RECORD IS\n\n ");
						 printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						 getch();
						 sclear();
					}
					fclose(f);
					f=fopen("ssf.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					f=fopen("psf.txt","rb");
					if(f==NULL) {
						printf("\n file opening error in listing :");
						exit(1);
					}
					while(fread(&p,sizeof(p),1,f)==1) {
						printf("\n\n\n YOUR RECORD IS\n\n ");
						printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
						getch();
						sclear();
					}
					fclose(f);
					printf("\n Enter any key");
					getch();
					sclear();
					menu();
					break;
				case '4': menu();
					break;
				default:
					sclear();
					printf("\nEnter 1 to 3 only");
					printf("\n Enter any key");
					getch();
					listrecord();
			}
    			break;
			case '2': 
				sclear();
				printf("\nSTORAGE WISE LIST CONTACTS MENU\n");
				printf("\n1.By Sim\n2.By Phone\n3.All From Both\n4.Exit");
				printf("\n\nChoose one option form above = ");
				switch(getch()) {
					case '1':
						f=fopen("ssf.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						f=fopen("ssfr.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						printf("\n Enter any key");
						getch();
						sclear();
						menu();
						break;
					case '2': 
						f=fopen("psf.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						f=fopen("psfr.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						printf("\n Enter any key");
						getch();
						sclear();
						menu();
						break;
					case '3': 
						f=fopen("ssf.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						f=fopen("ssfr.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						f=fopen("psf.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						f=fopen("psfr.txt","rb");
						if(f==NULL) {
							printf("\n file opening error in listing :");
							exit(1);
						}
						while(fread(&p,sizeof(p),1,f)==1) {
							printf("\n\n\n YOUR RECORD IS\n\n ");
							printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
							getch();
							sclear();
						}
						fclose(f);
						printf("\n Enter any key");
						getch();
						sclear();
						menu();
						break;
					case '4': menu();
						break;
					default:
						sclear();
						printf("\nEnter 1 to 3 only");
						printf("\n Enter any key");
						getch();
						listrecord();
				}
    				break;
    			case '3': 
				f=fopen("mf.txt","rb");
				if(f==NULL) {
					printf("\n file opening error in listing :");
					exit(1);
				}
				while(fread(&p,sizeof(p),1,f)==1) {
					printf("\n\n\n YOUR RECORD IS\n\n ");
					printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
					getch();
					sclear();
				}
				fclose(f);
				printf("\n Enter any key");
				getch();
				sclear();
				menu();
    				break;
			case '4': menu();
    				break;
   			 default:
                		sclear();
                		printf("\nEnter 1 to 6 only");
                		printf("\n Enter any key");
                		getch();
				listrecord();
	}
}
void searchrecord(){
	struct person p;
	FILE *f;
	char name[100];
	char mble[30];
	int fl;
	fl=1;
	printf("\t\t\tWELCOME TO CONTACT MANAGEMENT SYSTEM");
	printf("\n\nSEARCH MENU\n");
	printf("\n1.Search By Name\n2.Search By Phone Number\n3.Exit");
	printf("\n\nChoose one option form above = ");
	switch(getch()) {
    		case '1':
			f=fopen("mf.txt","rb");
			if(f==NULL) {
				printf("\n error in opening\a\a\a\a");
				exit(1);
			}
			printf("\nEnter Name = ");
			gets(name);
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(p.name,name)==0) {
					printf("\n\tInformation For %s",name);
					printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
					fl=2;
				}
			}
			if(fl==1) {
				printf("DATA not found");
			}
			fclose(f);
			printf("\n Enter any key");
			getch();
			sclear();
			menu();
			break;
   		case '2': 
			f=fopen("mf.txt","rb");
			if(f==NULL) {
				printf("\n error in opening\a\a\a\a");
				exit(1);
			}
			printf("\nEnter Phone Number = ");
			gets(mble);
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(p.mble_no,mble)==0) {
					printf("\n\tInformation For %s",mble);
					printf("\nTitle=%s\nName=%s\nAdress=%s\nFather name=%s\nMother name=%s\nMobile no=%s\nSex=%s\nE-mail=%s\nCitizen no=%s",p.title,p.name,p.address,p.father_name,p.mother_name,p.mble_no,p.sex,p.email,p.citision_no);
					fl=2;
				}
			}
			if(fl==1) {
				printf("DATA not found");
			}
			fclose(f);
			printf("\n Enter any key");
			getch();
			sclear();
			menu();
    			break;
   
    		case '3': exit(0);
    			break;
    		default:
                	sclear();
                	printf("\nEnter 1 to 5 only");
                	printf("\n Enter any key");
                	getch();
			menu();
	}
}
void deleterecord() {
	struct person p;
    	FILE *f,*ft;
	int flag,df;
	char ph[30];
	char name[100];
	df=0;
	printf("\t\t\tWELCOME TO CONTACT MANAGEMENT SYSTEM");
	printf("\n\nDELETE CONTACTS MENU\n");
	printf("\n1.Delete By Name\n2.Delete By Phone Number\n3.Exit");
	printf("\n\nChoose one option form above = ");
	switch(getch()) {
    		case '1':
			printf("Enter NAME: ");
			gets(name);
			fflush(stdin);
			f=fopen("mf.txt","rb");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
			}
			else {
				ft=fopen("temp.txt","wb+");
				if(ft==NULL)
					printf("file opening error");
				else {
					while(fread(&p,sizeof(p),1,f)==1) {
						if(strcmp(p.name,name)!=0)
							fwrite(&p,sizeof(p),1,ft);
						if(strcmp(p.name,name)==0)
							flag=1;
					}
					fclose(f);
					fclose(ft);
					if(flag!=1) {
						remove("temp.txt");
					}
					else {
						remove("mf.txt");
						rename("temp.txt","mf.txt");
						df=1;
					}
				}
			}
			f=fopen("ssfr.txt","rb");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
			}
			else {
				ft=fopen("temp.txt","wb+");
				if(ft==NULL)
					printf("file opening error");
				else {
					while(fread(&p,sizeof(p),1,f)==1) {
						if(strcmp(p.name,name)!=0)
							fwrite(&p,sizeof(p),1,ft);
						if(strcmp(p.name,name)==0)
							flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("ssfr.txt");
							rename("temp.txt","ssfr.txt");
							df=1;
						}
					}
				}
				f=fopen("ssf.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.name,name)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.name,name)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("ssf.txt");
							rename("temp.txt","ssf.txt");
							df=1;
						}
					}
				}
				f=fopen("psfr.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.name,name)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.name,name)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("psfr.txt");
							rename("temp.txt","psfr.txt");
							df=1;
						}
					}
				}
				f=fopen("psf.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.name,name)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.name,name)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("psf.txt");
							rename("temp.txt","psf.txt");
							df=1;
						}
					}
				}
				if(df==1) {
					printf("RECORD DELETED SUCCESSFULLY.");
				}
				else {
					printf("NO CONACT'S RECORD TO DELETE.");
				}
				printf("\n Enter any key");
				getch();
				sclear();
				menu();
				break;
   		case '2': 
			printf("Enter Phone no: ");
			gets(ph);
			fflush(stdin);
			f=fopen("mf.txt","rb");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
			}
			else {
				ft=fopen("temp.txt","wb+");
				if(ft==NULL)
					printf("file opening error");
				else {
					while(fread(&p,sizeof(p),1,f)==1) {
						if(strcmp(p.mble_no,ph)!=0)
							fwrite(&p,sizeof(p),1,ft);
						if(strcmp(p.mble_no,ph)==0)
							flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("mf.txt");
							rename("temp.txt","mf.txt");
							df=1;
						}
					}
				}
				f=fopen("ssfr.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.mble_no,ph)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.mble_no,ph)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("ssfr.txt");
							rename("temp.txt","ssfr.txt");
							df=1;
						}
					}
				}
				f=fopen("ssf.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.mble_no,ph)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.mble_no,ph)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("ssf.txt");
							rename("temp.txt","ssf.txt");
							df=1;
						}
					}
				}
				f=fopen("psfr.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.mble_no,ph)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.mble_no,ph)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("psfr.txt");
							rename("temp.txt","psfr.txt");
							df=1;
						}
					}
				}
				f=fopen("psf.txt","rb");
				if(f==NULL) {
					printf("CONTACT'S DATA NOT ADDED YET.");
				}
				else {
					ft=fopen("temp.txt","wb+");
					if(ft==NULL)
						printf("file opening error");
					else {
						while(fread(&p,sizeof(p),1,f)==1) {
							if(strcmp(p.mble_no,ph)!=0)
								fwrite(&p,sizeof(p),1,ft);
							if(strcmp(p.mble_no,ph)==0)
								flag=1;
						}
						fclose(f);
						fclose(ft);
						if(flag!=1) {
							remove("temp.txt");
						}
						else {
							remove("psf.txt");
							rename("temp.txt","psf.txt");
							df=1;
						}
					}
				}
				if(df==1) {
					printf("RECORD DELETED SUCCESSFULLY.");
				}
				else {
					printf("NO CONACT'S RECORD TO DELETE.");
				}
				printf("\n Enter any key");
				getch();
				sclear();
				menu();
				break;
    
		case '3': exit(0);
    	      		break;
    		default:
    			sclear();
                	printf("\nEnter 1 to 5 only");
                	printf("\n Enter any key");
               		getch();
			menu();
	}
}
void modifyrecord() {
    	FILE *f;
    	int flag=0,df;
    	struct person p,s;
	char  name[50];
	char phno[30];
	df=0;
	printf("\n MODIFY CONTACTS RECORD MENU\n");
	printf("\n1.By Name\n2.By Phone no\n3.Exit");
	printf("\n\nChoose one option form above = ");
	switch(getch()) {
    		case '1':
			printf("\nENTER CONTACT'S NAME TO MODIFY: ");
			gets(name);
			f=fopen("psf.txt","rb+");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
				exit(1);
			}
			else {
				sclear();
				while(fread(&p,sizeof(p),1,f)==1) {
					if(strcmp(name,p.name)==0) {
						printf("\n Enter Title: ");
						gets(s.title);
						printf("\n Enter name:");
						gets(s.name);
						printf("\nEnter the address:");
						gets(s.address);
						printf("\nEnter father name:");
						gets(s.father_name);
						printf("\nEnter mother name:");
						gets(s.mother_name);
						printf("\nEnter phone no:");
						gets(s.mble_no);
						printf("\nEnter sex:");
						gets(s.sex);
						printf("\nEnter e-mail:");
						gets(s.email);
						printf("\nEnter citizen no\n");
						gets(s.citision_no);
						fseek(f,-sizeof(p),SEEK_CUR);
						fwrite(&s,sizeof(p),1,f);
						flag=1;
						break;
					}
					fflush(stdin);
				}
				if(flag==1) {
					df=1;
				}
				fclose(f);
			}
			f=fopen("psfr.txt","rb+");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
				exit(1);
			}
			else {
				sclear();
				while(fread(&p,sizeof(p),1,f)==1) {
					if(strcmp(name,p.name)==0) {
						printf("\n Enter Title: ");
						gets(s.title);
						printf("\n Enter name:");
						gets(s.name);
						printf("\nEnter the address:");
						gets(s.address);
						printf("\nEnter father name:");
						gets(s.father_name);
					 	printf("\nEnter mother name:");
						gets(s.mother_name);
					        printf("\nEnter phone no:");
						gets(s.mble_no);
						printf("\nEnter sex:");
						gets(s.sex);
						printf("\nEnter e-mail:");
						gets(s.email);
						printf("\nEnter citizen no\n");
						gets(s.citision_no);
						fseek(f,-sizeof(p),SEEK_CUR);
						fwrite(&s,sizeof(p),1,f);
						flag=1;
						break;
					}
					fflush(stdin);
				}
				if(flag==1) {
					df=1;
				}
				fclose(f);
			}
			f=fopen("ssf.txt","rb+");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
				exit(1);
			}
			else {
				sclear();	
				while(fread(&p,sizeof(p),1,f)==1) {
					if(strcmp(name,p.name)==0) {
						printf("\n Enter Title: ");
						gets(s.title);
						printf("\n Enter name:");
						gets(s.name);
						printf("\nEnter the address:");
						gets(s.address);
						printf("\nEnter father name:");
						gets(s.father_name);
						printf("\nEnter mother name:");
						gets(s.mother_name);
						printf("\nEnter phone no:");
						gets(s.mble_no);
						printf("\nEnter sex:");
						gets(s.sex);
						printf("\nEnter e-mail:");
						gets(s.email);
						printf("\nEnter citizen no\n");
						gets(s.citision_no);
						fseek(f,-sizeof(p),SEEK_CUR);
						fwrite(&s,sizeof(p),1,f);
						flag=1;
						break;
					}
					fflush(stdin);
				}
				if(flag==1) {
					df=1;
				}
				fclose(f);
			}
			f=fopen("ssfr.txt","rb+");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
				exit(1);
			}
			else {
				sclear();
				while(fread(&p,sizeof(p),1,f)==1) {
					if(strcmp(name,p.name)==0) {
						printf("\n Enter Title: ");
						gets(s.title);
						printf("\n Enter name:");
						gets(s.name);
						printf("\nEnter the address:");
						gets(s.address);
						printf("\nEnter father name:");
						gets(s.father_name);
						printf("\nEnter mother name:");
						gets(s.mother_name);
						printf("\nEnter phone no:");
						gets(s.mble_no);
						printf("\nEnter sex:");
						gets(s.sex);
						printf("\nEnter e-mail:");
						gets(s.email);
						printf("\nEnter citizen no\n");
						gets(s.citision_no);
						fseek(f,-sizeof(p),SEEK_CUR);
						fwrite(&s,sizeof(p),1,f);
						flag=1;
						break;
					}
					fflush(stdin);
				}
				if(flag==1) {
					df=1;
				}
				fclose(f);
			}
			f=fopen("mf.txt","rb+");
			if(f==NULL) {
				printf("CONTACT'S DATA NOT ADDED YET.");
				exit(1);
			}
			else {
				sclear();
				while(fread(&p,sizeof(p),1,f)==1) {
					if(strcmp(name,p.name)==0) {
						fseek(f,-sizeof(p),SEEK_CUR);
						fwrite(&s,sizeof(p),1,f);
						flag=1;
						break;
					}
					fflush(stdin);
				}
				if(flag==1) {
					df=1;
				}
				fclose(f);
			}
			if(df==1) {
				printf("\n your data is modified");
			}
			else {
				printf(" \n data not found");
			}
			printf("\n Enter any key");
			getch();
			sclear();
			menu();
			break;
	case '2': 
		printf("\nENTER PHONE NO TO MODIFY: ");
		gets(phno);
		f=fopen("psf.txt","rb+");
		if(f==NULL) {
			printf("CONTACT'S DATA NOT ADDED YET.");
			exit(1);
		}
		else {
			sclear();
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(phno,p.mble_no)==0) {
					printf("\n Enter Title: ");
					gets(s.title);
					printf("\n Enter name:");
					gets(s.name);
					printf("\nEnter the address:");
					gets(s.address);
					printf("\nEnter father name:");
					gets(s.father_name);
					printf("\nEnter mother name:");
					gets(s.mother_name);
					printf("\nEnter phone no:");
					gets(s.mble_no);
					printf("\nEnter sex:");
					gets(s.sex);
					printf("\nEnter e-mail:");
					gets(s.email);
					printf("\nEnter citizen no\n");
					gets(s.citision_no);
					fseek(f,-sizeof(p),SEEK_CUR);
					fwrite(&s,sizeof(p),1,f);
					flag=1;
					break;
				}
				fflush(stdin);
			}
			if(flag==1) {
				df=1;
			}
			fclose(f);
		}
		f=fopen("psfr.txt","rb+");
		if(f==NULL) {
			printf("CONTACT'S DATA NOT ADDED YET.");
			exit(1);
		}
		else {
			sclear();
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(phno,p.mble_no)==0) {
					printf("\n Enter Title: ");
					gets(s.title);
					printf("\n Enter name:");
					gets(s.name);
					printf("\nEnter the address:");
					gets(s.address);
					printf("\nEnter father name:");
					gets(s.father_name);
					printf("\nEnter mother name:");
					gets(s.mother_name);
					printf("\nEnter phone no:");
					gets(s.mble_no);
					printf("\nEnter sex:");
					gets(s.sex);
					printf("\nEnter e-mail:");
					gets(s.email);
					printf("\nEnter citizen no\n");
					gets(s.citision_no);
					fseek(f,-sizeof(p),SEEK_CUR);
					fwrite(&s,sizeof(p),1,f);
					flag=1;
					break;
				}
				fflush(stdin);
			}
			if(flag==1) {
				df=1;
			}
			fclose(f);
		}
		f=fopen("ssf.txt","rb+");
		if(f==NULL) {
			printf("CONTACT'S DATA NOT ADDED YET.");
			exit(1);
		}
		else {
			sclear();
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(phno,p.mble_no)==0) {
					printf("\n Enter Title: ");
					gets(s.title);
					printf("\n Enter name:");
					gets(s.name);
					printf("\nEnter the address:");
					gets(s.address);
					printf("\nEnter father name:");
					gets(s.father_name);
					printf("\nEnter mother name:");
					gets(s.mother_name);
					printf("\nEnter phone no:");
					gets(s.mble_no);
					printf("\nEnter sex:");
					gets(s.sex);
					printf("\nEnter e-mail:");
					gets(s.email);
					printf("\nEnter citizen no\n");
					gets(s.citision_no);
					fseek(f,-sizeof(p),SEEK_CUR);
					fwrite(&s,sizeof(p),1,f);
					flag=1;
					break;
				}
				fflush(stdin);
			}
			if(flag==1) {
				df=1;
			}
			fclose(f);
		}
		f=fopen("ssfr.txt","rb+");
		if(f==NULL) {
			printf("CONTACT'S DATA NOT ADDED YET.");
			exit(1);
		}
		else {
			sclear();
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(phno,p.mble_no)==0) {
					printf("\n Enter Title: ");
					gets(s.title);
					printf("\n Enter name:");
					gets(s.name);
					printf("\nEnter the address:");
					gets(s.address);
					printf("\nEnter father name:");
					gets(s.father_name);
					printf("\nEnter mother name:");
					gets(s.mother_name);
					printf("\nEnter phone no:");
					gets(s.mble_no);
					printf("\nEnter sex:");
					gets(s.sex);
					printf("\nEnter e-mail:");
					gets(s.email);
					printf("\nEnter citizen no\n");
					gets(s.citision_no);
					fseek(f,-sizeof(p),SEEK_CUR);
					fwrite(&s,sizeof(p),1,f);
					flag=1;
					break;
				}
				fflush(stdin);
			}
			if(flag==1) {
				df=1;
			}
			fclose(f);
		}
		f=fopen("mf.txt","rb+");
		if(f==NULL) {
			printf("CONTACT'S DATA NOT ADDED YET.");
			exit(1);
		}
		else {
			sclear();
			while(fread(&p,sizeof(p),1,f)==1) {
				if(strcmp(phno,p.mble_no)==0) {
					fseek(f,-sizeof(p),SEEK_CUR);
					fwrite(&s,sizeof(p),1,f);
					flag=1;
					break;
				}
				fflush(stdin);
			}
			if(flag==1) {
				df=1;
			}
			fclose(f);
		}
		if(df==1) {
			printf("\n your data is modified");
		}
		else {
			printf(" \n data not found");
		}
		printf("\n Enter any key");
		getch();
		sclear();
		menu();
		break;
	case '3': exit(0);
		break;
		default:
		sclear();
		printf("\nEnter 1 to 3 only");
		printf("\n Enter any key");
		getch();
		modifyrecord();
	}
}
