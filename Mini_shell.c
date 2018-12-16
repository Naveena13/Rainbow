



 
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<math.h>
#include<time.h>

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int sort(char **args);
int palindrome(char **args);


char *builtin_str[] = {
  "cd",
  "help",
   "sort",
"palindrome",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &sort,
&palindrome,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
int sort(char **args)

{
   int count=0;
   char a[10];
   int c[10];
   strcpy(a,args[1]);
   for(int i=1,j=0;i<strlen(a);i+=2,j++)
   {
      //printf("%d",(int)a[i]);
      c[j]=(int)a[i]-48;
      count++;
   //   printf("%d",c[i]);
   }
   for(int i=0;i<count;i++)
   {
      printf("%d\n",c[i]);
   }
   printf("\n");
   int temp_;
   for(int i=0;i<count-1;i++)
   {
      for(int j=i+1;j<count;j++)
        {
            if(c[i]>c[j])
             {
                temp_=c[i];
                c[i]=c[j];
                c[j]=temp_;
             }
        }
  }
 printf("\nthe sorted array is\n ");
 for(int i=0;i<count;i++)
 {
   printf("\n%d",c[i]);
 }
  
  
    
  int palindrome(char **args)
{
int count=0;
   char str[10];
   int c[10];
   strcpy(str,args[1]);
 int l = 0;
    int h = strlen(str) - 1;

    // Keep comparing characters while they are same
    while (h > l)
    {
        if (str[l++] != str[h--])
        {
            printf("%s is Not Palindrome", str);
             count=1;
            break;
           // return;
        }
    }
if(count==0)
    printf("%s is palindrome", str);


}
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "NS: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("NS shell\n");
  printf("\n");
  printf("Use the following to work in the shell:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}


int lsh_exit(char **args)
{
  return 0;
}


int lsh_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {

    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
   
    perror("lsh");
  } else {
    
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

#define LSH_RL_BUFSIZE 1024

char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

   
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("@");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}


int main(int argc, char **argv)
{
  printf("Welcome");
//  lsh_loop();
time_t T= time(NULL);
    struct  tm tm = *localtime(&T);

    printf("\n %02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    printf("\n %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
   if(tm.tm_hour>6 && tm.tm_hour<11)
    printf("Good morning");
  else if(tm.tm_hour>=11 & tm.tm_hour<16)
   printf("Good noon");
   else if(tm.tm_hour>=16 && tm.tm_hour<20)
printf("Good evening");
else
  printf("Good night");

  
lsh_loop();
  return EXIT_SUCCESS;
}

 



