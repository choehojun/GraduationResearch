#include <stdio.h>
#include <string.h>

enum attack_types   {STACK_OVERFLOW=100};
enum functions      {MEMCPY=200, STRCPY, STRNCPY};

size_t num_of_attack_types = 1;
char *attack_types[] = {"stackoverflow"};

size_t num_of_functions = 3;
char *functions[] = {"memcpy", "strcpy", "strncpy"};

typedef struct attack_form ATTACK_FORM;
struct attack_form {
  enum attack_types attack_type;
  enum functions function;
};

static ATTACK_FORM attack;
static char *stack_overflow_payload = "AAAAAAAAAAAAAAAAAAAAAAAAA";
static int is_error = 0; 

__attribute((noinline))
void print_bufs(char * buf_overflow, char * buf_other_data) {
  printf("&buf_overflow:   %p\n buf_overflow:   %s\n", buf_overflow, buf_overflow);
  printf("&buf_other_data: %p\n buf_other_data: %s\n", buf_other_data, buf_other_data);
}

void set_attack(char* choice) {
    if(strcmp(choice, attack_types[0]) == 0) {
        attack.attack_type = STACK_OVERFLOW;
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
    set_attack(argv[1]);
    set_function(argv[2]);

    if(is_error == 1) {
        is_error = 0;
        return 0;
    }

    if(attack.attack_type == STACK_OVERFLOW) {
        char buf_other_data[8] = "BBBBBBB\0";
        char buf_overflow[8];
        print_bufs(buf_overflow, buf_other_data);
        if(attack.function == MEMCPY) {
            memcpy(buf_overflow, stack_overflow_payload, strlen(stack_overflow_payload));
        }
        else if(attack.function == STRCPY) {
            strcpy(buf_overflow, stack_overflow_payload);
        }
        else if(attack.function == STRNCPY) {
            strncpy(buf_overflow, stack_overflow_payload, strlen(stack_overflow_payload));
        }
        
        print_bufs(buf_overflow, buf_other_data);

        if(strcmp(buf_other_data, "BBBBBBB") != 0) {
            printf("Stack overflow attack succeeded!\n");
        }
        else {
            printf("Stack overflow attack failed!\n");
        }
    }

  return 0;
}

// EXPLOIT with
// callMain(["AAAAAAAAAAAAAAAAAAAAAAAAA"])