#include <stdio.h>
#include <stdarg.h>

void foo(char *fmt, ...)
{
        va_list ap;
        va_list ap2;
        int d, i;
        char c, *s;

        i = 0;
        va_start(ap, fmt);
        va_copy(ap2, ap);
        while (fmt[i] != '\0')
                switch(fmt[i++]) {
                case 's':                       /* string */
                        s = va_arg(ap, char *);
                        printf("string %s\n", s);
                        break;
                case 'd':                       /* int */
                        d = va_arg(ap, int);
                        printf("int %d\n", d);
                        break;
                case 'c':                       /* char */
                        /* Note: char is promoted to int. */
                        c = va_arg(ap, int);
                        printf("char %c\n", c);
                        break;
                }
        va_end(ap);
        //...
        /* use ap2 to iterate over the arguments again */
        /* we don't have to use va_start() here */
        i = 0;
        while (fmt[i] != '\0')
                switch(fmt[i++]) {
                case 's':                       /* string */
                        s = va_arg(ap2, char *);
                        printf("string %s\n", s);
                        break;
                case 'd':                       /* int */
                        d = va_arg(ap2, int);
                        printf("int %d\n", d);
                        break;
                case 'c':                       /* char */
                        /* Note: char is promoted to int. */
                        c = va_arg(ap2, int);
                        printf("char %c\n", c);
                        break;
                }
        va_end(ap2);
}
void foo2(char *fmt, ...)
{
    va_list ap;
    int d;
    char c, *s;

    va_start(ap, fmt);
    while (*fmt)
    {
        
        s = va_arg(ap, char *);
        printf("string %s\n", s);
        fmt++;
        // printf("fmt %c\n",*fmt);
        // switch (*fmt++)
        // {
        // case 's': /* string */
        //     s = va_arg(ap, char *);
        //     printf("string %s\n", s);
        //     break;
        // case 'd': /* int */
        //     d = va_arg(ap, int);
        //     printf("int %d\n", d);
        //     break;
        // case 'c': /* char */
        //     /* need a cast here since va_arg only
        //        takes fully promoted types */
        //     c = (char)va_arg(ap, int);
        //     printf("char %c\n", c);
        //     break;
        // }
    }

    va_end(ap);
}

int main()
{
    foo2("sddcc", "always", "asdf", "asdfasdf", "-a", "p", (char *)0);
    // foo2("sddcc", "always", 4, 3, 99, 'p',NULL);
    return 0;
}