// int main(int argc, char const *argv[])
// {
// 	my_heapinfo();
// 	my_init();
// 	my_heapinfo();
// 	char* test = NULL;
// 	if (test == NULL){
// 		printf("null pointer\n");
// 	}
// 	else{
// 		printf("allocated\n");
// 	}
// 	test = my_alloc(8);
// 	if(test == NULL) {
// 		printf("Error\n");
// 		return 0;
// 	}
// 	*(test+0) = 'a';
// 	*(test+1) = 'b';
// 	*(test+2) = 'c';
// 	*(test+3) = 'd';
// 	printf("before free: %s\n", test);
// 	my_heapinfo();
// 	// my_free(test);
// 	// printf("after free: %s\n", test);
// 	// my_heapinfo();
// 	char* t = NULL;
// 	t = my_alloc(16);
// 	if(t == NULL) {
// 		printf("Error\n");
// 		return 0;
// 	}
// 	my_heapinfo();

// 	my_free(test);
// 	my_heapinfo();

// 	int* a = my_alloc(8);
// 	my_heapinfo();

// 	int* b = my_alloc(16);
// 	my_heapinfo();

// 	int* c = my_alloc(16);
// 	my_heapinfo();

// 	int* d = my_alloc(3984);
// 	my_heapinfo();

// 	my_free(d);
// 	my_heapinfo();
// 	my_free(t);
// 	my_heapinfo();

// 	my_free(c);
// 	my_heapinfo();
// 	my_free(b);
// 	my_heapinfo();
// 	my_free(a);
// 	my_heapinfo();

// 	// my_free(b);
// 	// my_heapinfo();
// 	my_clean();

	// int a = my_init();
	// printf("%d\n", a);

	// char *temp = (char *)my_alloc(sizeof(char)*24);
	// char *ttemp = (char *)my_alloc(sizeof(char)*160);
	// char *tttemp = (char *)my_alloc(sizeof(char)*160);
	// my_heapinfo();// All three allocated
	// printf("Ttemp is freed\n");
	// my_free(ttemp);
	// my_heapinfo();// One is freed
	// ttemp = (char *) my_alloc(sizeof(char)*160);// Reallocated
	// printf("TTemp is Reallocated\n");
	// my_heapinfo();
	// my_free(ttemp);
	// my_heapinfo();
	// my_free(temp);
	// my_heapinfo();	
	// my_free(tttemp);
	// my_heapinfo();
	// my_clean();
	// printf("%s\n", tttemp);// Should cause segfault.
	// printf("He%s\n", ttemp);
	// printf("He%s\n", tttemp);
	// char* test = NULL;
	// if (test == NULL){
	// 	printf("null pointer\n");
	// }
	// else{
	// 	printf("allocated\n");
	// }
	// test = my_alloc(16);
	// if(test == NULL) {
	// 	printf("Error\n");
	// 	return 0;
	// }
	// *(test+0) = 'a';
	// *(test+1) = 'b';
	// *(test+2) = 'c';
	// *(test+3) = 'd';
	// printf("before free: %s\n", test);
	// my_heapinfo();
	// // my_free(test);
	// // printf("after free: %s\n", test);
	// // my_heapinfo();


	// char* t = NULL;
	// if (t == NULL){
	// 	printf("null pointer\n");
	// }
	// else{
	// 	printf("allocated\n");
	// }
	// t = my_alloc(16);
	// if(t == NULL) {
	// 	printf("Error\n");
	// 	return 0;
	// }
	// *(t+0) = 'a';
	// *(t+1) = 'b';
	// *(t+2) = 'c';
	// *(t+3) = 'd';
	// printf("before free: %s\n", t);
	// my_heapinfo();

	// int* i = NULL;
	// if (i == NULL){
	// 	printf("null pointer\n");
	// }
	// else{
	// 	printf("allocated\n");
	// }
	// i = my_alloc(16);
	// *(i+0) = 4005;
	// *(i+1) = 3;
	// *(i+2) = 2;
	// printf("before free: %d\n", *i);
	// my_heapinfo();
	// // my_free(test);
	// // printf("after free: %s\n", test);
	// // my_heapinfo();

	// char* test2 = NULL;
	// if (test2 == NULL){
	// 	printf("null pointer\n");
	// }
	// else{
	// 	printf("allocated\n");
	// }
	// test2 = my_alloc(8);
	// if(test2 == NULL) {
	// 	printf("Error\n");
	// 	return 0;
	// }
	// *(test2+0) = 'e';
	// *(test2+1) = 'f';
	// *(test2+2) = 'g';
	// *(test2+3) = 'h';
	// *(test2+4) = 'i';
	// printf("before free: %s\n", test2);
	// // my_free(test);
	// // printf("after free: %s\n", test);
	// my_heapinfo();

	// int* k = NULL;
	// if (k == NULL){
	// 	printf("null pointer\n");
	// }
	// else{
	// 	printf("allocated\n");
	// }
	// k = my_alloc(16);
	// *(k+0) = 5;
	// *(k+1) = 3;
	// *(k+2) = 2;
	// printf("before free: %d\n", *k);
	// my_heapinfo();

	// int* m = NULL;
	// if (m == NULL){
	// 	printf("null pointer\n");
	// }
	// else{
	// 	printf("allocated\n");
	// }
	// m = my_alloc(16);
	// *(m+0) = 5;
	// *(m+1) = 3;
	// *(m+2) = 2;
	// printf("before free: %d\n", *m);
	// my_heapinfo();

	// my_free(i);
	// my_heapinfo();
	// my_free(k);
	// my_heapinfo();
	// my_free(test);
	// my_heapinfo();
	// my_free(test2);
	// my_heapinfo();
	// my_free(t);
	// my_heapinfo();
	// my_free(m);
	// my_heapinfo();
// 	return 0;
// }