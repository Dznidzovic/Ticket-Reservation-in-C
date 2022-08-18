#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//Structure that stores passenger details;
int destnumber;
struct Passenger{
        char name[256];
        char age[3];
        char sex[256];
        char seatnumber[3];
        struct Line *destination;
    }Passenger;
//Structure that stores single Destination line details
typedef struct Line{
        char line[256];
        struct Line *next;
    } Line;

//Function checks if string is a number
void NumberCheck(char *string){

    int i = 0;
    int j = 0;
    while(1)
    {
        for(i;i<strlen(string);i++){
            if(string[i]<'0' || string[i]>'9'){
                j = 1;
            }
        }
        if(j==0){
            
            break;
        }
        printf("Please enter a non-negative number\n");
        scanf("%s",string);
        j = 0;
        i = 0;
    }
}
//Function gives us integer from string
int strtoint(char *string){
    int num = 0;
    int j = 1;
    for(int i = strlen(string)-1;i>=0;i--){
        int singledigit = string[i]-'0';
        num = j*singledigit + num;
        j = j * 10;
    }
    return num;
}
//Function checks if input is a number and if it fulfills our minimum and maximum limit
int NumberwLimitsCheck(char *string,int min,int max){
    scanf("%s",string);
    NumberCheck(string);
    int num = strtoint(string);
    while(1){
        if(num<min || num>max){
        printf("Please enter a number between %d and %d:\n",min,max);
        scanf("%s",string);
        NumberCheck(string);
        num = strtoint(string);
    }
    else{
        break;
    }
    }
    return num;
}

void toCapital(char *string){
    for(int i = 0;i<strlen(string);i++){
        string[i] = tolower((unsigned char) string[i]);
    }
    string[0] = toupper((unsigned char) string[0]);
   
}

//Function checks if string is valid and not a number
void StringCheck(char *string){
    int i = 0;
    int c = 0;
    while(1){
        if(strlen(string)<2){
            c = 1;
        }
        else{
            while(string[i]!='\0'){
                if(string[i]>='0' && string[i]<'9'){
                    c = 1;
                }
                i++;
            }
        }
        
    if(c==1){
        printf("Please enter a non-numerical value with more than one letter:\n");
        scanf("%s",string);
    }
    else if(c==0){
            break;
        }
    
    c = 0;
    i = 0;
    
    }
   
    
}
//Function checks if string input is a number;
//Function that delets the substring from given string
void numdelete(char*wholestring,char *substring){
    int i = 0;
    int status =  0;
    int j = 0;
    int counter = 0;
    int duzina = strlen(substring);
    int wholecounter;
    int subcounter = 0;
    printf("DUZINA JE :%d\n",duzina);
    for (i;i<strlen(wholestring);i++){
        wholecounter = i;
        if(wholestring[i]=='['){
            status = 1;
        }
        if((status==1) && (wholestring[i]==substring[0]) && duzina>1){
            
            counter = 0;
            subcounter = 0;
            for (int b = 0;b<duzina;b++){
                
                if(wholestring[wholecounter]==substring[subcounter]){
                    counter++;
                };
                wholecounter++;
                subcounter++;
            }
           
            if(counter==duzina){
                
                int g = i;
                while(wholestring[g]!='\0'){
                    wholestring[g] =  wholestring[g+duzina+1];
                    g++;
                    
                }

                
            }
            
            
            
        }
        
        
    }
    char line[256];
    char storeTheString[10000];
    int brojac = 0;
    printf("CEO FAJL: %s\n",storeTheString);
    FILE* file = fopen("destination.txt","r");

    if(file){
         while(fgets(line,256,file)){
            char copystring[256];
            char copyline[256];
            strcpy(copystring,wholestring);
            strcpy(copyline,line);
            char *token1 = strtok(copyline,"-");
            char *token2 = strtok(copystring,"-");
            char *ptr = strstr(token1,token2);
            if(ptr){
                strcat(storeTheString,wholestring);
            }
            else{
                strcat(storeTheString,line);
            }
         }
    }
    fclose(file);
    
    FILE *textwrite = fopen("destination.txt","w");
   
    if(textwrite){
        for (int i = 0;i<strlen(storeTheString);i++){
            fprintf(textwrite,"%c",storeTheString[i]);
            }
    }
    fclose(file);
    strcpy(storeTheString,"");
}
//Makes sure that user input is valid and transforms it valid for display
void StringPreProcessing(char *string){
    StringCheck(string);
    toCapital(string);
}
//GetPassengersDetails takes in the array of all Passenger structs and the number of passengers as parameters
void GetPassengerDetails(struct Passenger *ptr,int num){
    //Looping the number of passengers,getting their details and storing them inside Passengers structs;
    for (int i = 0;i<num;i++){
        char name[256];
        char secondname[256];
        
        printf("First name of the %d. person:\n",i+1);
        scanf("%s",name);
        StringPreProcessing(name);
        printf("Second name of the %d. person:\n",i+1);
        scanf("%s",secondname);
        StringPreProcessing(secondname);
        strcat(name," ");
        strcat(name,secondname);
        memcpy(ptr->name,name,strlen(name)+1);
        printf("Age of the %d. person:\n",i+1);
        scanf("%s",ptr->age);
        NumberCheck(ptr->age);
        printf("Sex of the %d. person:\n",i+1);
        scanf("%s",ptr->sex);
        StringPreProcessing(ptr->sex);
        ptr++;
        
    }
    

}

struct Line* DestinationsRepeat(int *counter,int *exitState){
        //Program will ask us to define the city we're travelling from, and city we're traveling to|We will get all the lines covering that destination.
    //We need linked list structure,as we dont know the number of lines in database of certain Destination
    Line* root = malloc(sizeof(Line));
    Line* current = root;
    
    char from[256];
    char to[256];
    char line[256];

    char stringchoice[256];

    int i = 0;
    int j = 0;


    int state = 0;
    while(state == 0 ){

    printf("Traveling from:");
    scanf("%s",from);
    StringPreProcessing(from);
    printf("Traveling to:");
    scanf("%s",to);
    StringPreProcessing(to);

    //Opening txt file with all our destinations.

    FILE *textfile;
    textfile = fopen("destination.txt","r");
    if(textfile == NULL)
    {
        printf("Database not existent!");
    }
 
    while(fgets(line,256,textfile)){
        //Looping through every line and checking if the city we're traveling from, appears in the string before the city we're travelling to
        //That way we dont mix the direction

        char *ptr1 = strstr(line,from);
        char *ptr2 = strstr(line,to);
   
        if(ptr1!=NULL && ptr2!=NULL){
           
            if(ptr1<ptr2){
                if(i==0){
                    strcpy(root->line,line);
                    i++;
                    
                }
                else{
                    Line* new = malloc(sizeof(Line));
                    strcpy(new->line,line);
                    current->next = new;
                    current = new;
                    i++;
                    
                }
                
               
                
                
            }
        }
       
        }
        fclose(textfile);
    *counter = i;
    printf("Counter je : %d\n",*counter);
    if(i<1){
        printf("No lines found\n");
        printf("1.Exit\n");
        printf("2.Search for antoher line\n");
        int choice = NumberwLimitsCheck(stringchoice,1,2);
        while(1){
            if(choice==1){
                *exitState=1;
                state = 1;
                break;
            }
            else{
                state = 0;
                break;
            }
        }
       
    }
    else{
        state = 1;
    }
    }
   
    i = 0;
    return root;
    
}

//Destinations function will ask us to define the cities, show us the available lines depending on our choice, and let us choose the time we want
struct Line* Destinations(int *exitState){
        int i = 0;
        int j = 0;
       
        Line *root = DestinationsRepeat(&i,exitState);
        if(*exitState==0){
            Line * current = root;
            while(j<i){
                char *token;
                char linecopy[250];
                strncpy(linecopy,current->line,strlen(current->line));
                //Printing just the city names and the time of departure and arrival, without printing the available seats
                token = strtok(linecopy,"[");
                printf("%d.%s\n",j+1,token);
                current = current->next;
                j++;
        }
        
            //Choosing the line you want based on the time of departure and arrival
            printf("Choose your option:\n");
            scanf("%d",&destnumber);
            while(1){
                if(destnumber>j || destnumber<=0){
                    printf("Please enter one of the available options");
                    scanf("%d",&destnumber);
                }
                else{
                    break;
                }
    }

    //Returning the right line based on the number we've selected
    current = root;
    j = 0;
    while(j<i){
        if(j==destnumber-1){
            return current;
            break;
        }
        else{
            current = current->next;
            j++;
        }
        
    }
        }
        else{
            printf("Closing the app...");
        }
       
    
    
    
   
      
}

//Seatnumber function will show us all the available seats and ask us to choose the ones we want, after that it will delete those seats from the database
void SeatNumber(struct Passenger *ptr,int num){
    int i = 0;
    
    while(i<num){
        
        char copyline[256];
        char *token;
        char *stringptr;
        strcpy(copyline,ptr->destination->line);
        token = strtok(copyline,"[]");
        while(token!=NULL){
            if(token[0]>='0' && token[0]<='9'){
            printf("Select one of the following empty seats: %s\n",token);
            int seatnum = NumberwLimitsCheck(ptr->seatnumber,1,60);
            while(1){
                if(strlen(ptr->seatnumber)<2){
                    printf("Please put add a zero infront of the number,as it is shown");
                    int seatnum = NumberwLimitsCheck(ptr->seatnumber,1,60);
                }
                else{
                    break;
                }
            }
            
            numdelete(ptr->destination->line,ptr->seatnumber);
            break;
            }
            token = strtok(NULL,"[]");
        }
        
        ptr++;
        i++;
    }
    
}

void TicketFilePrint(struct Passenger *ptr,int num){
    FILE *read = fopen("Tickets.txt","r");
    char storeTheString[10000];
    char c;
    int counter = 0;
    if(read){
        while((c=getc(read))!=EOF){
            storeTheString[counter] = c;
            counter++;
        }
    }
    fclose(read);

   
    int i = 0;
    FILE *out = fopen("Tickets.txt","w");
    while(i<num){
        fprintf(out,"Name:%s\n",ptr->name);
        fprintf(out,"Sex:%s\n",ptr->sex);
        fprintf(out,"Age:%s\n",ptr->age);
        fprintf(out,"Line:%s\n",ptr->destination->line);
        fprintf(out,"Seatnumber:%s\n",ptr->seatnumber);
        fputs("---------------------------------\n",out);
        fputs("\n",out);

        

        
        i++;
        ptr++;
    }
    for(int i = 0;i<counter;i++){
            fprintf(out,"%c",storeTheString[i]);
        }
    fclose(out);

    

}

//Function that prints Tickets
void TicketPrint(struct Passenger *ptr,int num,int *exitState){
    char choice[3];
    struct Passenger *root = malloc(sizeof(Passenger));
    root = ptr;
    printf("Printing your tickets\n");
    for(int i = 0;i<num;i++){
        char *token;
        token = strtok(ptr->destination->line,"[");
        printf("--------------------------------------------------------\n");
        printf("Line:%s\n",token);
        printf("Seat Number:%s\n",ptr->seatnumber);
        printf("Name:%s\n",ptr->name);
        printf("Age:%s\n",ptr->age);
        printf("Sex:%s\n",ptr->sex);
        printf("--------------------------------------------------------\n");
        ptr++;
    } 
    //Function writes tickets in the file
    ptr = root;
    TicketFilePrint(ptr,num);
    printf("1.Exit\n");
    printf("2.Buy more tickets\n");
    int numstate = NumberwLimitsCheck(choice,1,2);
    if(numstate==1){
        *exitState=1;
    }
    else{
        *exitState=0;
    }
    
    }
//Function prints all the tickets in database
void TicketsFromFilePrint(int *exitState){
            char c;
            FILE *file;
            file = fopen("tickets.txt","r");
            if(file){
                while((c=getc(file))!=EOF)
                    printf("%c",c);
            }
            fclose(file);
           
}
//Function asks you to add a line to the database
void AddAnotherLineFnc(){
            char from[256];
            char to[256];
            char torember[256];
            char departureTimeHours[3];
            char departureTimeMinutes[3];
            char landingTimeHours[3];
            char landingTimeMinutes[3];
            char state[3];
            char c;
            char storeTheString[10000];
            int numstate;
            int counter = 0;
            int numcheck;
        
            FILE *file;
            file = fopen("destination.txt","r");
            if(file){
                while((c=getc(file))!=EOF){
                    storeTheString[counter] = c;
                    counter++;
                }
                    
            }
            fclose(file);
            printf("Departure city:\n");
            scanf("%s",from);
            StringCheck(from);
            toCapital(from);
            printf("STRING JE:%s\n",from);
            
            printf("Landing city:\n");
            scanf("%s",to);
            StringCheck(to);
            toCapital(to);

            printf("Departure time(hours):\n");
            
            numcheck = NumberwLimitsCheck(departureTimeHours,0,24);

            printf("Departure time(minutes):\n");
            numcheck = NumberwLimitsCheck(departureTimeMinutes,0,60);

            printf("Landing time(hours):\n");
            numcheck = NumberwLimitsCheck(landingTimeHours,0,24);

            printf("landing time(minutes):\n");
            numcheck = NumberwLimitsCheck(landingTimeMinutes,0,60);

            strcat(departureTimeHours,":");
            strcat(departureTimeHours,departureTimeMinutes);
            strcat(departureTimeHours,"-");
            strcat(departureTimeHours,landingTimeHours);
            strcat(departureTimeHours,":");
            strcat(departureTimeHours,landingTimeMinutes);
            
           

           
            FILE *filewrite;
            filewrite = fopen("destination.txt","w");
            if(filewrite){

            
            fprintf(filewrite,"%s|%s|%s|",from,to,departureTimeHours);
            fprintf(filewrite,"[");
            for(int i = 1;i<61;i++){
                if(i==60){
                    fprintf(filewrite,"%d",i);

                }
                else if(i<10){
                    fprintf(filewrite,"0%d ",i);
                }
                else{
                    fprintf(filewrite,"%d ",i);
                }
                
            }
            fprintf(filewrite,"]\n");
            for(int i = 0;i<counter;i++){
                fprintf(filewrite,"%c",storeTheString[i]);
            }

            }
            printf("Line succesfully added\n");
}
void TicketDelete(){
    char firstname[256];
    char secondname[256];
    char line[256];
    int counter = 0;
    char *ptr;
    char storeTheString[10000];
    printf("First name of the person on the ticket:\n");
    scanf("%s",firstname);
    StringPreProcessing(firstname);
    printf("Second name of the person on the ticket:\n");
    scanf("%s",secondname);
    StringPreProcessing(secondname);

    strcat(firstname," ");
    strcat(firstname,secondname);


    FILE *file = fopen("Tickets.txt","r");

    int temp=0;
    int flag = 0;
    if(file){
        while(fgets(line,256,file)){
            counter++;
            ptr = strstr(line,firstname);
            if(ptr){
                temp = counter;
                flag = 1;
            }
            
            
            if(counter<temp+6 && flag ==1){
                continue;
            }
            else{
                strcat(storeTheString,line);
            }
        }
    }
    fclose(file);


    FILE *textwrite = fopen("Tickets.txt","w");
    if(textwrite){
        for (int i = 0;i<strlen(storeTheString);i++){
            fprintf(textwrite,"%c",storeTheString[i]);
            }
    }
    if(temp==0){
        printf("Ticket not found");
    }
    else{
        printf("Ticket deleted");
    
    }
    
}
 

void main(){
    
    printf("Welcome to MyAir ticket selling center!\n");
    printf("---------------------------------------\n");
    printf("1.Control Panel\n");
    printf("2.Reserve a ticket\n");
    char modestring[3];
    int mode = NumberwLimitsCheck(modestring,1,2);
    int exitState = 0;
    int *exitStateptr = &exitState;

    int exitStateCP = 0;
    int *exitStateCPptr = &exitStateCP;

    if(mode==1){
        
       
        printf("1.Print all the reserved tickets\n");
        printf("2.Delete a reservation\n");
        printf("3.Add another line into database\n");
        char numstr[2];
        int num = NumberwLimitsCheck(numstr,1,3);

        if(num==1){
           TicketsFromFilePrint(exitStateCPptr);
        
        }
        else if(num==3){
            AddAnotherLineFnc();
        }
        else{
            TicketDelete();
        }   
    }
    else{
    //Defining number of passengers buying the ticket
    int num;
    
    //creating while loop so we can exit the mid process or redo it without starting the program again;
    while(1){
        if(*exitStateptr==1){
        break;
    }
        
    printf("Enter the number of passengers:");
    char charnum[2];
    num = NumberwLimitsCheck(charnum,1,60);

    //Creating an array of Passenger structs
    struct Passenger passengers[num]; 
    //Calling a function that obtains passengers details
    GetPassengerDetails(passengers,num);
    //Defining a pointer to Line struct;
    Line* currentLine;
    //Destinations function returns the pointer to the destination that customer selected iside Destinations function
    currentLine = Destinations(exitStateptr);

    if(*exitStateptr==1){
        break;
    }
    //Assigning the current line to the destination struct of the every single  Passenger struct
    for(int i = 0;i<num;i++){
        passengers[i].destination = currentLine;
    }
    //Function lets us choose the seatnumber;
    SeatNumber(passengers,num);
    //Function prints tickets;
    TicketPrint(passengers,num,exitStateptr);
    
    }
    }
       
}