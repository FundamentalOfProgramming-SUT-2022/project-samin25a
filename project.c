#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <windows.h>

int main(){

char ch;

char *str = (char*)calloc(50,sizeof(char));
//char str[50];

while(1){
//scanf("%s",str);
for(int i=0;;i++){
    scanf("%c",&str[i]);
    if(str[i]==' ' || str[i]=='\n'){
        str[i]='\0';
        break;
    }
}


if(strcmp(str,"createfile")==0){

    DIR* dir;DIR* dir2;FILE* myfile;FILE* myfile2;
    char *str = (char*)calloc(50,sizeof(char));
    for(int i=0;;i++){
        scanf("%c",&str[i]);
        if(str[i]==' '){
            str[i]='\0';
            break;
        }
    }
    if(strcmp(str,"-file")==0){
        char *address = calloc(100,sizeof(char));
        int flag=0;
        address[0]='.';
        scanf("%c",&ch);
        if(ch=='/'){
            address[1]=ch;
            }
        else{
            flag=1;
            scanf("%c",&address[1]);
        }
        for(int i=2;;i++){
            scanf("%c",&address[i]);
            if((address[i]==' ' && flag==0)||address[i]=='\n'){
                address[i]='\0';
                break;
            }
            if(address[i]=='"'){
                address[i]='\0';
                scanf("%c",&ch);
                flag=!flag;
                break;
            }
            if(address[i]=='/'){
                dir = opendir(address);
                if(dir==0){
                    mkdir(address);
                    dir2 = opendir(address);

                }
            }
        }

        if(flag){
            rmdir(address);
            printf("invalid command.\n");
            }
        else{
            myfile = fopen(address,"r");
            if(myfile!=0){
                printf("The file already exists.\n");
                fclose(myfile);
                }
            else{
                myfile2 = fopen(address,"w");
                printf("File is created.\n");
                fclose(myfile2);
            }
        }
    }
    else{
        printf("invalid command.\n");
    }
}


//insertstr -file /root/s.txt -str "salam\\nkhoobi" -pos 1:0
else if(strcmp(str,"insertstr")==0){
    str = (char*)calloc(50,sizeof(char));
    for(int i=0;;i++){
        scanf("%c",&str[i]);
        if(str[i]==' '){
            str[i]='\0';
            break;
        }
    }
    if(strcmp(str,"-file")==0){
    char *address = (char*)calloc(100,sizeof(char));
    int flag=0;
    address[0]='.';
    scanf("%c",&ch);
    if(ch=='/'){
        address[1]=ch;
        }
    else{
        flag=1;
        scanf("%c",&address[1]);
    }
    for(int i=2;;i++){
        scanf("%c",&address[i]);
        if((address[i]==' ' && flag==0) ||address[i]=='\n'){
            address[i]='\0';
            break;
        }
        if(address[i]=='"'){
            address[i]='\0';
            scanf("%c",&ch);//enter
            flag=!flag;
            break;
        }
        if(address[i]=='/'){
            DIR* dir = opendir(address);
            if(dir==0){
                mkdir(address);
                DIR* dir2 = opendir(address);
            }
        }
    }

        if(flag){
            printf("invalid command.\n");
            }
        else{
            str=(char*)calloc(50,sizeof(char));
            for(int i=0;;i++){
                scanf("%c",&str[i]);
                if(str[i]==' '){
                    str[i]='\0';
                    break;
                }
            }
            FILE* myfile = fopen(address,"r+");
            if(strcmp(str,"-str")==0){
                if(myfile!=0){
                    char* to_insert = (char*)calloc(100,sizeof(char));
                    scanf("%c",&ch);
                    flag=0;
                    if(ch!='"')
                        to_insert[0]=ch;

                    else{
                        flag=1;
                        scanf("%c",&to_insert[0]);
                    }
                    for(int i=1;;i++){
                        scanf("%c",&to_insert[i]);
                        if(to_insert[i]==' '&&flag==0){
                            to_insert[i]='\0';
                            break;
                        }
                        if(to_insert[i]=='"'&&to_insert[i-1]!='\\'){
                            to_insert[i]='\0';
                            break;
                        }
                        if(to_insert[i]=='"'&&to_insert[i-1]=='\\'){
                            to_insert[i-1]='"';
                            scanf("%c",&to_insert[i]);
                        }
                        if(to_insert[i]=='\\'&&to_insert[i-1]=='\\'){
                            to_insert[i-1]='\\';
                            scanf("%c",&to_insert[i]);
                        }
                        if(to_insert[i]=='n'&&to_insert[i-1]=='\\'){
                            if(to_insert[i-2]!='\\'){
                                //printf("1");
                                to_insert[i-1]='\n';
                                scanf("%c",&to_insert[i]);
                            }
                            else{
                                //printf("2");
                                to_insert[i-2]='\\';
                                to_insert[i-1]='n';
                                scanf("%c",&to_insert[i]);
                            }
                        }
                    }
                    //getchar();
                    //printf("to_insert=%s\n",to_insert);
                    str=(char*)calloc(50,sizeof(char));
                    for(int i=0;;i++){
                        scanf("%c",&str[i]);
                        if(str[i]==' '){
                            str[i]='\0';
                            break;
                        }
                    }
                    if(strcmp(str,"-pos")==0){
                        int lnumber,chnumber;
                        scanf("%d%c%d",&lnumber,&ch,&chnumber);
                        scanf("%c",&ch);//enter
                        int mylnumber=1;
                        char *matn=(char *)calloc(100,sizeof(char));
                        int i,count=0;
                        for(i=0;;i++){
                            if(mylnumber==lnumber && count==chnumber){
                                for(int j=0;j<strlen(to_insert);j++){
                                    matn[i+j]=to_insert[j];
                                }
                                i+=strlen(to_insert)-1;
                                mylnumber++;
                            }
                            else{
                            matn[i]=fgetc(myfile);
                            if(mylnumber==lnumber)
                                count++;
                            if(matn[i]=='\n')
                                mylnumber++;
                            if(matn[i]==EOF){
                                matn[i]='\0';
                                break;
                            }
                            }
                        }
                        fclose(myfile);
                        FILE* myfile2=fopen(address,"w");
                        //printf("%s\n",matn);
                        fwrite(matn,sizeof(char),strlen(matn),myfile2);
                        fclose(myfile2);
                    }
                    else{
                        printf("%s\n",str);
                        printf("invalid command.\n");
                    }
                }
                else{
                    printf("File does not exists.\n");
                }
            }
            else{
                printf("invalid command.\n");
            }
            fclose(myfile);
        }
    }
    else{
        printf("invalid command.\n");
    }
}

//removestr –file /root/a.txt –pos 2:1 -size 3 -f
else if(strcmp(str,"removestr")==0){
    int add=1,file=1;
    str = (char*)calloc(50,sizeof(char));//-file
    for(int i=0;;i++){
        scanf("%c",&str[i]);
        if(str[i]==' '){
            str[i]='\0';
            break;
        }
    }
    char *address = (char*)calloc(100,sizeof(char));
    int flag=0;
    address[0]='.';
    scanf("%c",&ch);
    if(ch=='/'){
        address[1]=ch;
        }
    else{
        flag=1;
        scanf("%c",&address[1]);
    }
    for(int i=2;;i++){
        scanf("%c",&address[i]);
        if((address[i]==' ' && flag==0) ||address[i]=='\n'){
            address[i]='\0';
            break;
        }
        if(address[i]=='"'){
            address[i]='\0';
            scanf("%c",&ch);//enter
            break;
        }
        if(address[i]=='/'){
            DIR* dir = opendir(address);
            if(dir==0){
                add=0;
            }
        }
    }//printf("1");
                char *pos=(char *)calloc(5,sizeof(char));
                scanf("%s",pos);

                int lnumber,chnumber,size;
                char s[6],c[3];//-size
                scanf("%d%c%d %s %d %s",&lnumber,&ch,&chnumber,s,&size,c);
                getchar();
            FILE* myfile = fopen(address,"r+");
            if(myfile!=0){
                int mylnumber=1,count=0;
                char *matn = (char *)calloc(100,sizeof(char));
                for(int i=0;;i++){
                    matn[i]=fgetc(myfile);
                    if(strcmp(c,"-f")==0&&mylnumber==lnumber&&count==chnumber){
                        //printf("1");
                        matn[i]=fgetc(myfile);
                        for(int k=0;k<size-1;k++){
                            ch=fgetc(myfile);
                        }
                        for(int k=i+1;;k++){
                            matn[k]=fgetc(myfile);
                            if(matn[k]==EOF){
                                matn[k]='\0';
                                break;
                            }
                        }
                        break;
                    }
                    if(strcmp(c,"-b")==0&&mylnumber==lnumber&&count==chnumber-1){
                        for(int k=i-size+1;;k++){
                            matn[k]=fgetc(myfile);
                            if(matn[k]==EOF){
                                matn[k]='\0';
                                break;
                            }
                        }
                        break;
                    }
                    if(matn[i]==EOF){
                        matn[i]='\0';
                        break;
                    }
                    if(mylnumber==lnumber){
                        count++;
                    }
                    if(matn[i]=='\n'){
                        mylnumber++;
                    }
                }
                //printf("1");
                fclose(myfile);
                FILE* myfile2=fopen(address,"w");
                fwrite(matn,sizeof(char),strlen(matn),myfile2);
                fclose(myfile2);
            }
            else{
                file=0;
            }

    if(add==0){
        printf("Wrong address.\n");
    }
    if(file==0){
        printf("The file does not exist.\n");
    }
}


else if(strcmp(str,"cat")==0){
    str=(char*)calloc(50,sizeof(char));
    for(int i=0;;i++){
        scanf("%c",&str[i]);
        if(str[i]==' '){
            str[i]='\0';
            break;
        }
    }
    if(strcmp(str,"-file")==0){
        char *address = (char*)calloc(100,sizeof(char));
        int flag=0;
        address[0]='.';
        for(int i=1;;i++){
            scanf("%c",&address[i]);
            if(i!=1 && address[i]=='/'){
                DIR* dir=opendir(address);
                if(dir==0){
                    printf("Folder %s doesn't exist.",address);
                    flag=1;
                }
            }
            else if(address[i]=='\n'){
                address[i]='\0';
                FILE* myfile = fopen(address,"r");
                if(myfile==0){
                    printf("The file doesn't exist.\n");
                    fclose(myfile);
                    break;
                }
                else{
                    char *matn=(char *)calloc(100,sizeof(char));
                    for(int i=0;;i++){
                        matn[i]=getc(myfile);
                        if(matn[i]==EOF){
                            matn[i]='\0';
                            break;
                        }
                    }
                    printf("%s\n",matn);
                    fclose(myfile);
                }
            }
        }
    }
    else{
        printf("invalid command.");
    }
}


else if(strcmp(str,"copystr")==0){
    int add=1,file=1;
    str = (char*)calloc(50,sizeof(char));//-file
    for(int i=0;;i++){
        scanf("%c",&str[i]);
        if(str[i]==' '){
            str[i]='\0';
            break;
        }
    }
    char *address = (char*)calloc(100,sizeof(char));
    int flag=0;
    address[0]='.';
    scanf("%c",&ch);
    if(ch=='/'){
        address[1]=ch;
        }
    else{
        flag=1;
        scanf("%c",&address[1]);
    }
    for(int i=2;;i++){
        scanf("%c",&address[i]);
        if((address[i]==' ' && flag==0) ||address[i]=='\n'){
            address[i]='\0';
            break;
        }
        if(address[i]=='"'){
            address[i]='\0';
            scanf("%c",&ch);//enter
            break;
        }
        if(address[i]=='/'){
            DIR* dir = opendir(address);
            if(dir==0){
                add=0;
            }
        }
    }
    char *pos=(char *)calloc(5,sizeof(char));
    scanf("%s",pos);
    int lnumber,chnumber,size;
    char s[6],c[3];//-size
    scanf("%d%c%d %s %d %s",&lnumber,&ch,&chnumber,s,&size,c);
    getchar();//enter
    FILE* myfile = fopen(address,"r");
    if(myfile!=0){
        char *matn=(char *)calloc(100,sizeof(char));
        for(int i=0;;i++){
            matn[i]=fgetc(myfile);
            if(matn[i]==EOF){
                matn[i]='\0';
                break;
            }
        }
        fclose(myfile);
        FILE* myfile2 = fopen(address,"r");
        char *to_be_copied = (char *)calloc(100,sizeof(char));
        int count=0;
        for(int i=0;i<lnumber-1;i++){
            ch='a';
            while(1){
            ch=fgetc(myfile2);
            //printf("%c\n",ch);
            count++;
            if(ch=='\n')
                break;
            }
        }
        for(int i=0;i<chnumber;i++){
            ch=fgetc(myfile2);
            count++;
        }
        if(strcmp(c,"-f")==0){
            for(int i=0;i<size;i++){
                to_be_copied[i]=fgetc(myfile2);
            }
        }
        if(strcmp(c,"-b")==0){
            count++;
            for(int i=count-size,j=0;i<count;i++,j++){
                to_be_copied[j]=matn[i];
            }
        }
        int len = strlen(to_be_copied)+1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE,len);
        memcpy(GlobalLock(hMem),to_be_copied,len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();

        fclose(myfile2);
    }
    else{
        printf("File does not exist.\n");
    }
    if(add==0){
        printf("Wrong address.\n");
    }
}


else if(strcmp(str,"cutstr")==0){
    int add=1;
    str = (char*)calloc(50,sizeof(char));//-file
    for(int i=0;;i++){
        scanf("%c",&str[i]);
        if(str[i]==' '){
            str[i]='\0';
            break;
        }
    }
    char *address = (char*)calloc(100,sizeof(char));
    int flag=0;
    address[0]='.';
    scanf("%c",&ch);
    if(ch=='/'){
        address[1]=ch;
        }
    else{
        flag=1;
        scanf("%c",&address[1]);
    }
    for(int i=2;;i++){
        scanf("%c",&address[i]);
        if((address[i]==' ' && flag==0) ||address[i]=='\n'){
            address[i]='\0';
            break;
        }
        if(address[i]=='"'){
            address[i]='\0';
            scanf("%c",&ch);//enter
            break;
        }
        if(address[i]=='/'){
            DIR* dir = opendir(address);
            if(dir==0){
                add=0;
            }
        }
    }//cutstr -file /root/a.txt -pos 2:4 -size 5 -f
    char *pos=(char *)calloc(5,sizeof(char));
    scanf("%s",pos);
    int lnumber,chnumber,size;
    char s[6],c[3];//-size
    scanf("%d%c%d %s %d %s",&lnumber,&ch,&chnumber,s,&size,c);
    getchar();//enter
    FILE* myfile = fopen(address,"r");
    if(myfile!=0){
        char *matn=(char *)calloc(100,sizeof(char));
        char *matn2=(char *)calloc(100,sizeof(char));
        for(int i=0;;i++){
            matn[i]=fgetc(myfile);
            matn2[i]=matn[i];
            if(matn[i]==EOF){
                matn[i]='\0';
                matn2[i]='\0';
                break;
            }
        }
        fclose(myfile);
        FILE* myfile2 = fopen(address,"r");
        char *to_be_cut = (char *)calloc(100,sizeof(char));
        int count=0;
        for(int i=0;i<lnumber-1;i++){
            ch='a';
            while(1){
            ch=fgetc(myfile2);
            //printf("%c\n",ch);
            count++;
            if(ch=='\n')
                break;
            }
        }
        for(int i=0;i<chnumber;i++){
            ch=fgetc(myfile2);
            count++;
        }
        if(strcmp(c,"-f")==0){
            for(int i=0;i<size;i++){
                to_be_cut[i]=fgetc(myfile2);
            }
            for(int i=count;;i++){
                matn2[i]=matn[i+size];
                if(matn2[i]==EOF){
                    matn2[i]='\0';
                    break;
                }
            }
        }
        if(strcmp(c,"-b")==0){
            count++;
            for(int i=count-size,j=0;i<count;i++,j++){
                to_be_cut[j]=matn[i];
            }
            for(int i=count-size;;i++){
                matn2[i]=matn[i+size];
                if(matn2[i]==EOF){
                    matn2[i]='\0';
                    break;
                }
            }
        }
        fclose(myfile2);
        FILE* myfile3 = fopen(address,"w");
        fwrite(matn2,sizeof(char),strlen(matn2),myfile3);
        fclose(myfile3);

        int len = strlen(to_be_cut)+1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE,len);
        memcpy(GlobalLock(hMem),to_be_cut,len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();

    }
    else{
        printf("File does not exist.\n");
    }
    if(add==0){
        printf("Wrong address.\n");
    }
}


/*else if(strcmp(str,"pastestr")==0){

}*/

else if(strcmp(str,"find")==0){
    char *str = (char *)calloc(5,sizeof(char));
    scanf("%s",str);
    getchar();
    char* to_be_found = (char*)calloc(100,sizeof(char));
    scanf("%c",&ch);
    int flag=0;
    int count=0,at=0,byword=0,all=0;
    if(ch!='"')
        to_be_found[0]=ch;

    else{
        flag=1;
        scanf("%c",&to_be_found[0]);
    }
    for(int i=1;;i++){
        scanf("%c",&to_be_found[i]);
        if(to_be_found[i]==' '&&flag==0){
            to_be_found[i]='\0';
            break;
        }
        if(to_be_found[i]=='"'&&to_be_found[i-1]!='\\'){
            to_be_found[i]='\0';
            break;
        }
        if(to_be_found[i]=='"'&&to_be_found[i-1]=='\\'){
            to_be_found[i-1]='"';
            scanf("%c",&to_be_found[i]);
        }
        if(to_be_found[i]=='\\'&&to_be_found[i-1]=='\\'){
            to_be_found[i-1]='\\';
            scanf("%c",&to_be_found[i]);
        }
        if(to_be_found[i]=='n'&&to_be_found[i-1]=='\\'){
            if(to_be_found[i-2]!='\\'){
                //printf("1");
                to_be_found[i-1]='\n';
                scanf("%c",&to_be_found[i]);
            }
            else{
                //printf("2");
                to_be_found[i-2]='\\';
                to_be_found[i-1]='n';
                scanf("%c",&to_be_found[i]);
            }
        }
    }

    int add=1,file=1;
    str=(char *)calloc(5,sizeof(char));
    scanf("%s",str);//-file
    char *address = (char*)calloc(100,sizeof(char));
    flag=0;
    address[0]='.';
    scanf("%c",&ch);
    if(ch=='/'){
        address[1]=ch;
        }
    else{
        flag=1;
        scanf("%c",&address[1]);
    }
    for(int i=2;;i++){
        scanf("%c",&address[i]);
        if(address[i]=='\n'){
            address[i]='\0';
            break;
        }
        if(address[i]==' '){
            address[i]='\0';
            for(int i=0;i<4;i++){
                char *options=(char *)calloc(20,sizeof(char));
                scanf("%s",options);
                if(strcmp(options,"-count")==0){
                    count=1;
                    scanf("%c",&ch);
                    if(ch!=' '){
                        break;
                    }
                }
                else if(strcmp(options,"-at")==0){
                    count=1;
                    scanf("%c",&ch);
                    if(ch!=' '){
                        break;
                    }
                }
                if(strcmp(options,"-all")==0){
                    count=1;
                    scanf("%c",&ch);
                    if(ch!=' '){
                        break;
                    }
                }
                if(strcmp(options,"-byword")==0){
                    count=1;
                    scanf("%c",&ch);
                    if(ch!=' '){
                        break;
                    }
                }
            }

        }
        if(address[i]=='"'){
            address[i]='\0';
            scanf("%c",&ch);//enter
            break;
        }
        if(address[i]=='/'){
            DIR* dir = opendir(address);
            if(dir==0){
                add=0;
            }
        }
    }
    //printf("%s\n",to_be_found);
    FILE* myfile=fopen(address,"r");
    if(myfile==0)
        file=0;
    else{
        int ans[10]={-1};
        char *matn = (char *) calloc(100,sizeof(char));
        for(int i=0;;i++){
            matn[i]=fgetc(myfile);
            if(matn[i]==EOF){
                matn[i]='\0';
                break;
            }
        }
        int a;
        int tedad=0;
        for(int i=0;i<strlen(matn)-strlen(to_be_found);i++){
            a=1;
            for(int j=i;j<i+strlen(to_be_found);j++){
                if(matn[j]!=to_be_found[j-i]){
                    a=0;
                    //printf("%c %c\n",matn[j],to_be_found[j-i]);
                    break;
                }
            }
            if(a){
                ans[tedad]=i;
                tedad++;
            }
        }

        if(!count&&!at&&!all&&!byword){//find -str al -file /root/a.txt
            if(ans[0]==-1)
                printf("Not found.\n");
            else
                printf("%d\n",ans);
        //printf("%s",to_be_found);
    }
    if(count&&!at&&!all&&!byword){
        printf("%d\n",tedad);
    }
    if(!count&&!at&&all&&!byword){
        for(int i=0;i<tedad-1;i++){
            printf("%d, ",ans[i]);
        }
        printf("%d\n",ans[tedad-1]);
    }
    }
    if(add==0){
        printf("Wrong address.\n");
        //printf("%s\n",address);
        }
    if(file==0){
        printf("File does not exist.\n");
        }
}

else if(strcmp(str,"exit")==0){
    break;
}

else{
    printf("invalid command.\n");
    //printf("%s\n",str);
}


}
return 0;
}
