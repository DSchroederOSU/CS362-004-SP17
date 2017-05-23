//#define ASSERT(expr) ((expr)?printf("TEST SUCCESSFULLY COMPLETED\n"):printf("TEST FAILED\n"))
#define ASSERT(expr) ((expr)?success++:fail++)