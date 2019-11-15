# Como instalar OpenMP no linux

Abra o terminal e escreva 

```console
user@estepc:~$ sudo apt-get install libomp-dev
```

# Como executar

```c
//hello.c
#include <stdio.h>

int main (void) {
    #pragma omp parallel 
    {
        printf("Hello, world!\n");
    }
    return 0;
}
```

```console
user@estepc:~$ gcc -o helloc -fopenmp hello.c
user@estepc:~$ ./helloc 
Hello, world!
Hello, world!
Hello, world!
Hello, world!
Hello, world!
Hello, world!
```

