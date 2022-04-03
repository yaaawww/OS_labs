struct co* co_start(const char* name, void (*func)(void *), void *arg);
void co_yield();
void co_wait(struct co *co);

enum co_status {
	CO_NEW = 1,
	CO_RUNNING,
	CO_WAITING,
	CO_DEAD,
};

struct co {
	char* name;
	void (*func) (void *);
	void *arg;

	enum co_status status;
	struct co *waiter;
	jmp_buf context;
	uint8_t stack[STACK_SIZE];
};


