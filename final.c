#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
FILE* op;
FILE* ip;
op=fopen(argv[1],"rw");
ip=fopen(argv[2],"w+");
int val;
int nex;


int in_comment=0;
int in_quote=0;
int line_number;
char quote_type;
int comm_line;



while ((val = getc(op)) != EOF){
        if (val=='\n')
                        line_number=line_number+1;
        if (in_comment){
                        if (val=='*'){
                                nex=getc(op);
                                if (nex=='/'){
                                        in_comment=0;
                                        continue;
                                }
                        }
                        if(val=='\n'){
                                putchar(10);
								fprintf(ip,"%c",10);
                        }

        }
		else if(!in_comment){
                if(!in_quote && (val=='\''  | val=='"')){
                        in_quote=1;
                        quote_type=val;

                }
                else if (in_quote && val == quote_type){
                        in_quote=0;
                         quote_type=0;
                }
                if (val=='/' && !in_quote){
                                nex=getc(op);
                                if (nex=='*'){
                                        in_comment=1;
                                        putchar(' ');
										fprintf(ip,"%c",' ');
										comm_line=line_number;
                        //              continue;
                                }else{
                                        putchar('/');
                                        putchar(nex);
										
										fprintf(ip,"%c",'/');
										fprintf(ip,"%c",nex);

                                }

                        }else {
                                putchar(val);
								fprintf(ip,"%c",val);
                        }
         }

        }
		if(in_comment){
			fprintf(ip,"%s%d","\nERROR: Incomplete comment at line ", comm_line);
		}


fclose(op);
fclose(ip);
        return 0;
}
