#include "co.h"
#include <stdlib.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h> 

#define STACK_SIZE 8192

enum co_status {
	CO_NEW = 1,
	CO_RUNNING,
	CO_WAITING,
	CO_DEAD,
};

struct co {
	const char* name;
	void (*func)(void*);
	void* arg;
	
	enum co_status status;
	struct co * waiter;
	jmp_buf context;
	uint8_t stack[STACK_SIZE];
};

static struct co *current;

static struct co *pool[2];
static int index = 0;
static int round = 0;
static jmp_buf main_context;

static inline void stack_switch_call(void *sp, void *entry, uintptr_t arg) {
	__asm__ volatile (
#if __x86_64__
	    "movq %0, %%rsp; movq %2, %%rdi; jmp *%1"
		: 
		: "b"((uintptr_t)sp), "d"(entry), "a"(arg) 
		: "memory"
#else
		"movl %0, %%esp; movl %2, 4(%0); jmp *%1"
		:
		: "b"((uintptr_t)sp - 8), "d"(entry), "a"(arg) 
		: "memory"
#endif
 	);
}

struct co *co_start(const char *name, void (*func)(void *), void *arg) {
	struct co *new_co = (struct co*)malloc(sizeof(struct co));
	new_co->name = name;
	new_co->func = func;
	new_co->arg = arg;
	new_co->status = CO_NEW;
	
	pool[index] = new_co;
	index++;
	
	return new_co;
}

void co_wait(struct co *co) {
	 if (co->status != CO_DEAD) {
		 setjmp(main_context);
		 current = pool[round];
		 co_yield();
	 } else {
		 
	 }
}

void co_yield() {
	int val = setjmp(current->context);
	if (val == 0) {
		current = pool[(round++) % 2];
		if (current->status == CO_NEW) {
			stack_switch_call(&current->stack[8191], current->func, (uintptr_t)current->arg);
		} else {
			longjmp(current->context, 1);
		}
	} else {
		return;
	}
}

void entry(void *arg) {
  while (1) {
    printf("%s", (const char *)arg);
    co_yield();
  }
}

int main() {
	struct co *co1 = co_start("co1", entry, "a");
	struct co *co2 = co_start("co2", entry, "b");
	co_wait(co1);
	co_wait(co2);
}
