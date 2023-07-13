/* Omar Sameh Mohamed Belal_150120079
   Osama Alsmadi_150119548
   Mais Sabbagh_150120078 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyArray(char arr1[],char arr2[]);


struct operation_type{

	char  optname[100];
	float commission;
	int optnum;
	
	struct operation_type *nextopt;
	};
	


void enqueue1(struct operation_type**startPtr,char optname[],float commission ,int optnum)
{
    struct operation_type *newPtr = (struct operation_type*)malloc(sizeof(struct operation_type));
    copyArray( newPtr->optname ,optname);
    newPtr->commission=commission;
    newPtr->optnum = optnum;
    newPtr->nextopt = NULL;

     if(*startPtr!=NULL){
	struct operation_type *currentPtr =*startPtr;
     while(currentPtr->nextopt!=NULL){
		
        currentPtr=currentPtr->nextopt;    
	}
       
	 
    currentPtr->nextopt=newPtr;
    
 
    }
    else{
		
		*startPtr=newPtr;
	
		}
}

/*..............................................................................*/

struct branch{

	char  bname[100];
	int bno;
	
	struct customer *custs;
	struct branch *nextb;
	};


void enqueue2(struct branch* *startPtr ,char  bname[],int bno)
{
    struct branch *newPtr = malloc(sizeof(struct branch));
    copyArray( newPtr->bname ,bname);
    newPtr->bno = bno;
    newPtr->custs = NULL;
    newPtr->nextb = NULL;

    if(*startPtr!=NULL){
	struct branch *currentPtr =*startPtr;
     while(currentPtr->nextb!=NULL){
		
        currentPtr=currentPtr->nextb;    
	}
       
	 
    currentPtr->nextb=newPtr;
    
 
    }
    else{
		
		*startPtr=newPtr;
	
		}
}


/*..............................................................................*/
	
struct customer{

	char  fname[100];
	char  lname[100];
	int cno;
	float paid_commission;
	
	struct transaction *tran;
	struct customer *nextc;
	};



void enqueue3(struct customer* *startPtr ,char  fname[],char  lname[],	float paid_commission)
{
    struct customer *newPtr =(struct customer*) malloc(sizeof(struct customer));
    copyArray( newPtr->fname ,fname);
   
    copyArray( newPtr->lname ,lname);
    
    newPtr->paid_commission = paid_commission;
    newPtr->tran = NULL;
    newPtr->nextc = NULL;
   
     int i=1;
  
     if(*startPtr!=NULL){
	struct customer *currentPtr =*startPtr;
     while(currentPtr->nextc!=NULL){
		i++;
        currentPtr=currentPtr->nextc;    
	}

	i++;
       newPtr->cno=i;
    currentPtr->nextc=newPtr;
    
 
    }
    else{
		newPtr->cno=i;
		*startPtr=newPtr;
	
		}
}

/*..............................................................................*/
	
struct transaction{

    int optype;
    int tno;
	float amount;
	
	struct transaction *nexttr;
	};
	


void enqueue4(struct transaction* *startPtr ,int optype,float amount)
{
    struct transaction *newPtr = (struct transaction*)malloc(sizeof(struct transaction));
   
    newPtr->optype=optype;
   
    newPtr->amount=amount;
    newPtr->nexttr = NULL;
   
     int i=1;
  
     if(*startPtr!=NULL){
	struct transaction *currentPtr =*startPtr;
     while(currentPtr->nexttr!=NULL){
		i++;
        currentPtr=currentPtr->nexttr;    
	}
        i++;
	 newPtr->tno=i;
    currentPtr->nexttr=newPtr;
    
 
    }
    else{
		 newPtr->tno=i;
		*startPtr=newPtr;
	
		}
}

/*..............................................................................*/
	
struct bank{

	struct branch *nextb;
	struct operation_type *optypes;
	};

struct bank *bankPtr = NULL;


/*..............................................................................*/
int checkName(struct branch *ptr,char fname[],char lname[]);
/*..............................................................................*/
void readOperationTypes(){
	
	char fileName[100];
	printf("please enter the name of the input file: ");
	scanf("%s",fileName);
	FILE *file=fopen(fileName,"r");
	
	struct bank *temp =bankPtr;
	char  optname[100];
	float commission=0.01;
	int optnum=1;
	 
	while(fscanf(file,"%s %f",optname,&commission)!=EOF){
		
		enqueue1(&(temp->optypes),optname,commission,optnum);
		optnum++;
		
		
		}
		

	    fclose(file);
	
	}
	
/*..............................................................................*/

	
void readBranches(){
	
	char fileName[100];
	printf("please enter the name of the input file: ");
	scanf("%s",fileName);
	FILE *file=fopen(fileName,"r");
	
	char  bname[100];
	int bno=1;
    struct bank *temp =bankPtr;
	while(fscanf(file,"%s",bname)!=EOF){
		
	
		enqueue2(&(temp->nextb),bname,bno);
		bno++;
		
		}
	    fclose(file);
	}
	
/*..............................................................................*/
	
void readCustomers(){
	
	struct bank *temp =bankPtr;
	struct branch* tempb=temp->nextb;
	
	
	
	char fileName[100];
	printf("please enter the name of the input file: ");
	scanf("%s",fileName);
	FILE *file=fopen(fileName,"r");
	
	char  fname[100];
	char  lname[100];
	
	float paid_commission=0;
    int bno=0;
	 
	int i=0;
	while(fscanf(file,"%d %s %s",&bno,fname,lname)!=EOF){
		
		
	    for(i=0;i<bno-1;i++){
			
	    tempb=tempb->nextb;
	}
	if(!checkName(tempb,fname,lname))
	  continue;
	
		enqueue3(&(tempb->custs),fname,lname,paid_commission);
		
		tempb=temp->nextb;
		}
		

	    fclose(file);
	    
	   
	
	}
	
/*..............................................................................*/

void readTransactions(){
	struct bank *temp =bankPtr;
	struct branch*tempb=temp->nextb;
	struct customer *tempc;
	
	
	char fileName[100];
	printf("please enter the name of the input file: ");
	scanf("%s",fileName);
	FILE *file=fopen(fileName,"r");
	
	int bno;
	int cno;
	int optype;
	float amount;
	
	int i=0;
	while(fscanf(file,"%d %d %d %f",&bno,&cno,&optype,&amount)!=EOF){
		
		
	    for(i=0;i<bno-1;i++){
			
	    tempb=tempb->nextb;
	}

	tempc=tempb->custs;

	 for(i=0;i<cno-1;i++){
			
	    tempc=tempc->nextc;
	}
	  
		enqueue4(&(tempc->tran), optype, amount);
		
		tempb=temp->nextb;
		tempc=NULL;
		
		}
		

	    fclose(file);
	   
	}
	
/*..............................................................................*/

void printPaidCommission(){
	
	struct bank *temp =bankPtr;
	struct branch*tempb=temp->nextb;
	struct customer * tempc;
	struct transaction * tempt;
	struct operation_type * tempo;
	int i=0;
	float total_comm=0;
	 while(tempb!=NULL){
		 
			printf("Branch : %s\n",tempb->bname);
			tempc=tempb->custs;
			while(tempc!=NULL){
				printf("--> cust id %d %s %s\n",tempc->cno,tempc->fname,tempc->lname);
				tempt=tempc->tran;
				if(tempt==NULL){
					printf("  --(customer has no transaction)\n");
					
					}
					else{
				while(tempt!=NULL){
					tempo=temp->optypes;
					for(i=0;i<tempt->optype-1;i++){
						tempo=tempo->nextopt;
						}
					printf("  --tno %d optype %d commission rate %.2f ",tempt->tno,tempt->optype,tempo->commission );
					tempc->paid_commission=tempo->commission*tempt->amount/100;
					total_comm+=tempc->paid_commission;
					printf("amount %.2f paid commission %.2f",tempt->amount,tempc->paid_commission);
					
					printf(" total commission %.2f\n",total_comm);
					
					tempt=tempt->nexttr;
					}
				}
				tempc=tempc->nextc;
				printf("  ** paid commission %.2f\n\n",total_comm);
				 total_comm=0;
				}
			tempb=tempb->nextb;
			
			}
	
	
	
	}
/*..............................................................................*/

void printoperationtypes(){
	
	struct bank *temp =bankPtr;
	struct operation_type * tempo=temp->optypes;
	
	
	   while(tempo!=NULL){
		
			printf("--%d %s %.2f\n",tempo->optnum,tempo->optname,tempo->commission);
			tempo=tempo->nextopt;
				}
			
			
			}

	
	
	
	/*..............................................................................*/
	
void printbranches(){
	
	struct bank *temp =bankPtr;
	struct branch* tempb=temp->nextb;
	
	
	   while(tempb!=NULL){
		
			printf("Branch : %d %s\n",tempb->bno,tempb->bname);
			tempb=tempb->nextb;
				}
			
			
			}

	
	
	
	/*..............................................................................*/
void printcustomers(){
	
	struct bank *temp =bankPtr;
	struct branch* tempb=temp->nextb;
	
	
	   while(tempb!=NULL){
		 struct customer *tempc=tempb->custs;
			printf("Branch : %d %s\n",tempb->bno,tempb->bname);
			while(tempc!=NULL){
				printf("  --%d %s %s\n",tempc->cno,tempc->fname,tempc->lname);
				
				tempc=tempc->nextc;
				}
			tempb=tempb->nextb;
			
			}

	
	}
	
	/*..............................................................................*/
	
	
void printtransactions(){
	
	struct bank *temp =bankPtr;
	struct branch* tempb=temp->nextb;
	struct customer * tempc;
	struct transaction * tempt;
	
	 while(tempb!=NULL){
		 
			printf("Branch : %d %s\n",tempb->bno,tempb->bname);
			tempc=tempb->custs;
			while(tempc!=NULL){
				printf("  --%d %s %s\n",tempc->cno,tempc->fname,tempc->lname);
				tempt=tempc->tran;
				while(tempt!=NULL){
					
					printf("          ++tno %d operation type (optype) %d amount %.2f\n",tempt->optype,tempt->optype,tempt->amount);
					tempt=tempt->nexttr;
					}
				tempc=tempc->nextc;
				}
			tempb=tempb->nextb;
			
			}

	
	}

/*..............................................................................*/

void copyArray(char arr1[],char arr2[]){
	int i=0;
	for(i=0;i<100;i++){
		arr1[i]=arr2[i];
		}
	
	}	
	
/*..............................................................................*/

int checkName(struct branch *ptr,char fname[],char lname[]){
	
	struct branch *tempb=ptr;
	 struct customer *tempc=tempb->custs;
	 while(tempc!=NULL){
	 
	  
	  if(strcmp(fname,tempc->fname)==0&&strcmp(lname,tempc->lname)==0)
	  return 0;
	  tempc=tempc->nextc;
  }
	return 1;
	
	
	}	
	
/*..............................................................................*/
	
	
int main() {
	
	bankPtr=malloc(sizeof(struct bank));
	bankPtr->nextb=NULL;
	bankPtr->optypes=NULL;
	
	int option=1;
	printf("\n");
	printf("1) Read operation types from the file\n");
	printf("2) Read branches from the file\n");
	printf("3) Read customers from the file\n");
	printf("4) Read customers transactions from the file\n");
	printf("5) calculate paid commission amount of each customers in each branches\n\n");
	
	printf("option: ");
	scanf("%d",&option);
    printf("\n");
 
 while(option>0&&option<6){
	
	
	switch(option){
		
		case 1:
		readOperationTypes();
		printoperationtypes();
		break;
		
		case 2:
		readBranches();
		printbranches();
		
		break;
		
		case 3:
		 readCustomers();
	     printcustomers();
		break;
		
		case 4:
		readTransactions();
		printtransactions();
		break;
		
		case 5:
		printPaidCommission();
		break;
		
		
		}

	printf("\n");
	printf("****************************************");
	printf("\n");
	printf("1) Read operation types from the file\n");
	printf("2) Read branches from the file\n");
	printf("3) Read customers from the file\n");
	printf("4) Read customers transactions from the file\n");
	printf("5) calculate paid commission amount of each customers in each branches\n\n");
	
	printf("option: ");
	scanf("%d",&option);
    printf("\n");
	 
	 }


   return 0;
}
