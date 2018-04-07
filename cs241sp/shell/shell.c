/**
 * Machine Problem: Shell
 * CS 241 - Spring 2016
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include <string.h>
#include <sys/wait.h>
int startsWith(char *pre, char *str)
{
    size_t lenpre = strlen(pre),
    lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

int parse_command(char *cmd, char parse_cmd[10][100]){
    int index = 0;
    int character = 0;
    char eof = 0;
    int count = 0;
    while(*cmd != eof){
        if(*cmd == ' ' || *cmd == '\t' || *cmd == '\n'){
            parse_cmd[index][character] = 0;
            character = 0;
            index++;
            cmd++;
            count++;
            continue;
        }
        parse_cmd[index][character] = *cmd;
        cmd++;
        character++;
        if(*cmd == 0){
            //OBOB.
            parse_cmd[index][character] = *cmd;
            count++;
        }
    }
    return count;
}

void execute_command(int count, char parse_cmd[10][100], char *cmd){
    char *parsed[count+1];
    ///char *environment[] = {0};
    int index = 0;
    for(index = 0; index<count; index++){
        parsed[index] = parse_cmd[index];
    }
    parsed[index] = 0;
    
    int immediate_return = 0;
    if(*parsed[count-1] == '&'){
        parsed[count-1] = 0;
        count--;
        immediate_return = 1;
    }
    else{
        int len = strlen(parsed[count-1]);
        if(parsed[count-1][len-1] =='&')
        {
            immediate_return = 1;
            parsed[count-1][len-1] = 0;
            
        }
        
    }
    
    
    
    int status;
    pid_t child_id =fork();
    
    
    
    if(child_id == 0){
        //child code
        execvp(parsed[0], parsed);
        //if command would have been successful, he control will never reach here.
        printf("%s: not found\n",parsed[0]);
        exit(0);
    }
    else if(child_id < 0){
        //error
        printf("Error: Could not create a child process\n");
        exit(0);
    }
    else{
        //the parent code
        //wait for the child to complete
        if(immediate_return)
            return;
        waitpid(child_id, &status, 0);
        if(status < 0)
        {
            printf("%s: not found\n",parsed[0]);
        }
    }
    return;
}
char history[1000][100];
int history_size = 0;
void read_history(char *history_file)
{
    FILE * pFile;
    pFile = fopen (history_file,"r");
    if (pFile!=NULL)
    {
        history_size = 0;
        while(fgets(history[history_size], 1000, pFile) > 0)
            history_size++;
    }
    else
    {
        printf("History file Not Found %s\n",history_file);
        exit(-1);
    }
    
    return;
    
    
    
    
}

int targc;
char **targv;


void run_shell(int argc, char *argv[])
{
    
    // TODO: This is the entry point for your shell.
    char *history_file = NULL;
    char *commands_file = NULL;
    if(argv[1] && strcmp(argv[1],"-h") == 0){
        history_file = argv[2];
        if(argv[3] && strcmp(argv[3], "-f") == 0){
            commands_file = argv[4];
        }
    }
    else if(argv[1] && strcmp(argv[1], "-f") == 0){
        commands_file = argv[2];
        if(argv[3] && strcmp(argv[3], "-h") == 0){
            history_file = argv[4];
        }
    }
    
    if(commands_file != NULL){
        
        FILE * pFile;
        pFile = fopen (commands_file,"a");
        if (pFile!=NULL)
        {
            fputs ("exit",pFile);
            fclose (pFile);
        }
        else{
            printf("Command File Not Found %s\n",commands_file);
            exit(-1);
        }
        
        freopen(commands_file,"r",stdin);
    }
    
    
    
    
    if(history_file!=NULL)
        read_history(history_file);
    
    
    
    char *cmd = (char *) malloc(sizeof(char)*1000);
    char parsed_cmd[10][100];
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != 0)
        ;
    else{
        perror("No such directory");
        exit(-1);
    }
    
    
    char latest[100];
    int run_latest = 0;
    
    while(1){
        
        if(run_latest)
        {
            strcpy(cmd,latest);
            run_latest = 0;
        }
        else
        {
            printf("(pid = %d)%s$ ", getpid(), cwd);
            fgets(cmd, 1000, stdin);
        }
        if(commands_file!=NULL)
            printf("%s",cmd);
        if((*cmd == 'e' || *cmd == 'E') && (*(cmd+1) == 'x' || *(cmd+1) == 'X')  && (*(cmd+2) == 'i' || *(cmd+2) == 'I')  && (*(cmd+3) == 't' || *(cmd+3) == 'T')){
            
            strcpy(history[history_size++],"exit");
            FILE * pFile;
            pFile = fopen ("history.txt","w");
            if (pFile!=NULL)
            {
                for(int i=0;i<history_size;++i)
                    fprintf(pFile,"%s",history[i]);
            }
            
            
            
            
            
            exit(0);
        }
        
        
        /* With strncmp
         if(strncmp(cmd, "exit", strlen("exit")) || strncmp(cmd, "Exit", strlen("Exit"))){
         printf("Shell Completed.\n");
         exit(0);
         }
         */
        
        //get the arguments in the given cmd on the command promt.
        int count = parse_command(cmd, parsed_cmd);
        
        
        if(strcmp(parsed_cmd[0],"cd") == 0)
        {
            sprintf(history[history_size++],"cd %s",parsed_cmd[1]);
            if(parsed_cmd[1] == NULL){
                parsed_cmd[1][0] = '.';
                parsed_cmd[1][1] = 0;
            }
            
            if(chdir(parsed_cmd[1])!=0)
                printf("%s: No such file or directory\n",parsed_cmd[1]);
            if (getcwd(cwd, sizeof(cwd)) != 0)
                ;
            else
                exit(-1);
        }
        else if(strcmp(parsed_cmd[0],"!history") == 0){
            int i;
            for(i=0;i<history_size;++i)
            {
                printf("%d\t%s",i,history[i]);
            }
            
            
        }
        else if(parsed_cmd[0][0] == '#')
        {
            int n = atoi(parsed_cmd[0]+1);
            if(n >= history_size)
                printf("Invalid Index\n");
            else
            {
                run_latest = 1;
                strcpy(latest,history[n]);
                printf("%s",latest);
                printf("\n");
                
            }
            
        }
        else if(parsed_cmd[0][0] == '!')
        {
            
            int i=history_size-1;
            while(i>=0)
            {
                if(startsWith(parsed_cmd[0]+1,history[i]))
                {
                    run_latest = 1;
                    strcpy(latest,history[i]);
                    printf("%s",latest);
                    break;
                    
                }
                else
                {
                    
                    i--;
                }
            }
            if( i < 0 )
                printf("No Match\n");
            
            
        }
        else{
            
            //execute the given command.
            
            printf("Command executed by pid=%d\n",getpid());
            strcpy(history[history_size++],cmd);
            execute_command(count, parsed_cmd, cmd);
        }
    }
    
}

static void handler(int signum)
{
    /** Ignore SIG_INT **/
    if(signum == SIGINT)
    {
        
        
        struct sigaction sa;
        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGINT, &sa, NULL) == -1)
        {
            printf("Can't set signal handler");
            exit(-1);
        }
        
        printf("\n");
        run_shell(targc,targv);
    }
}

int main(int argc, char *argv[]) {
    
    targc = argc;
    targv = argv;
    
    
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        printf("Can't set signal handler");
        exit(-1);
    }
    run_shell(argc,argv);
    
    
}