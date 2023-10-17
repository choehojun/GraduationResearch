#include <stdio.h>
#include <string.h>

enum attack_types   {STACK_OVERFLOW=100, INDIRECT_CALL, RODATA_OVERWRITE};
enum functions      {MEMCPY=200, STRCPY, STRNCPY};

size_t num_of_attack_types = 3;
char *attack_types[] = {"stackoverflow", "indirectcall", "rodataoverwrite"};

size_t num_of_functions = 3;
char *functions[] = {"memcpy", "strcpy", "strncpy"};

typedef struct attack_form ATTACK_FORM;
struct attack_form {
  enum attack_types attack_type;
  enum functions function;
};

static ATTACK_FORM attack;
static char *stack_overflow_payload = "AAAAAAAAAAAAAAAAAAAAAAAAA";

//use this payload when using printf for debugging (line 138, 140)
//static char *indirect_call_payload = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\02";

//use this payload when not using printf for debugging (line 138, 140)
static char *indirect_call_payload = "aaaaaaaaaaaaaaaaaaaaaaaaaaaa\02";

char *global_const = "AAAA";
static const char *rodata_const = "Rodata constant overwrite failed!";
static char *rodata_overwrite_payload = "aaaaaaaaaaaaaaRodata constant overwrite succeeded!\0";
static int is_error = 0;
static int is_first = 1;

void evil(int unused) { printf("Indirect call redirection succeeded!\n"); }
void normal(char *unused) { printf("Indirect call redirection failed!\n"); }

__attribute((noinline))
void print_bufs(char *buf_overflow, char *buf_other_data) {
  printf("&buf_overflow:   %p\n buf_overflow:   %s\n", buf_overflow, buf_overflow);
  printf("&buf_other_data: %p\n buf_other_data: %s\n", buf_other_data, buf_other_data);
}

__attribute__((noinline)) 
void indirect_vulnerable(enum functions function) {
  char buf[8];
  if(function == MEMCPY) {
    memcpy(buf, indirect_call_payload, strlen(indirect_call_payload));
  }
  else if(function == STRCPY) {
    strcpy(buf, indirect_call_payload);
  }
  else if(function == STRNCPY) {
    strncpy(buf, indirect_call_payload, strlen(indirect_call_payload));
  }
}

__attribute__((noinline)) 
void rodata_vulnerable(enum functions function) {
  if(function == MEMCPY) {
    memcpy(global_const, rodata_overwrite_payload, strlen(rodata_overwrite_payload));
  }
  else if(function == STRCPY) {
    strcpy(global_const, rodata_overwrite_payload);
  }
  else if(function == STRNCPY) {
    strncpy(global_const, rodata_overwrite_payload, strlen(rodata_overwrite_payload));
  }
}

void set_attack(char* choice) {
    if(strcmp(choice, attack_types[0]) == 0) {
        attack.attack_type = STACK_OVERFLOW;
    }
    else if(strcmp(choice, attack_types[1]) == 0) {
        attack.attack_type = INDIRECT_CALL;
    }
    else if(strcmp(choice, attack_types[2]) == 0) {
        attack.attack_type = RODATA_OVERWRITE;
    }
    else {
        printf("Error: Unknown choice of attack type \"%s\"\n", choice);
        is_error = 1;
    }
}

void set_function(char* choice) {
    if(strcmp(choice, functions[0]) == 0) {
        attack.function = MEMCPY;
    }
    else if(strcmp(choice, functions[1]) == 0) {
        attack.function = STRCPY;
    }
    else if(strcmp(choice, functions[2]) == 0) {
        attack.function = STRNCPY;
    }
    else {
        printf("Error: Unknown choice of function \"%s\"\n", choice);
        is_error = 1;
    }
}


int main(int argc, char **argv) {
    if(is_first == 1) {
        is_first = 0;
        return 0;
    }
    
    set_attack(argv[1]);
    set_function(argv[2]);


    if(is_error == 1) {
        is_error = 0;
        return 0;
    }

    if(attack.attack_type == STACK_OVERFLOW) {
        char buf_other_data[8] = "BBBBBBB\0";
        char buf_overflow[8];
        //print_bufs(buf_overflow, buf_other_data);
        if(attack.function == MEMCPY) {
            memcpy(buf_overflow, stack_overflow_payload, strlen(stack_overflow_payload));
        }
        else if(attack.function == STRCPY) {
            strcpy(buf_overflow, stack_overflow_payload);
        }
        else if(attack.function == STRNCPY) {
            strncpy(buf_overflow, stack_overflow_payload, strlen(stack_overflow_payload));
        }
        
        //print_bufs(buf_overflow, buf_other_data);

        if(strcmp(buf_other_data, "BBBBBBB") != 0) {
            printf("Stack overflow attack succeeded!\n");
        }
        else {
            printf("Stack overflow attack failed!\n");
        }
    }

    else if(attack.attack_type == INDIRECT_CALL) {
        void (*func_ptr)(char *);
        func_ptr = &normal;
        //printf("&func_ptr: %p\nfunc_ptr:  %p\n", &func_ptr, func_ptr);
        indirect_vulnerable(attack.function);
        //printf("&func_ptr: %p\nfunc_ptr:  %p\n", &func_ptr, func_ptr);

        (*func_ptr)("aaaa");
    }

    else if(attack.attack_type == RODATA_OVERWRITE) {
        rodata_vulnerable(attack.function);
        printf("%s", rodata_const);
    }

  return 0;
}

__attribute__((used)) void dead_code() { printf("%p\n", evil); }