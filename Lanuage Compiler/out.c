#include <stdio.h>
int main(void){
float var;
if(0 == scanf("%f", &var)) {
var = 0;
scanf("%*s");
}
loop:
printf("%.2f\n", (float)(var));
goto loop;
return 0;
}
