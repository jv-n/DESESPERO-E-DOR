#include <stdio.h>

int main ()
{   
    int bufunfa; 
    int a,b,c,d; 
    float ef_a, ef_b, ef_c, ef_d;

    ef_a = 75; ef_b = 50; ef_c = 25; ef_d = 50;

    scanf("%d", &bufunfa);
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    if(a!=0)
    {
        ef_a/=a;
    }
    if(b!=0)
    {
        ef_b/=b;
    }
    if(c!=0)
    {
        ef_c/=c;
    }
    if(d!=0)
    {
        ef_d/=d;
    }

    float media = (ef_a+ef_b+ef_c+ef_d)/4;

    /*Para A*/
    if(ef_a<media && a<=bufunfa)
    {
        printf("EH BOMBA TORRESMO\n");
    }
    if((ef_a>=media && a<=bufunfa) || (ef_a>=media && a == 0))
    {
        printf("eh dento\n");
    }
    else if(a>bufunfa)
    {
        printf("foi de comes\n");
    }

    if(ef_b<media && b<=bufunfa)
    {
        printf("EH BOMBA TORRESMO\n");
    }
    if((ef_b>=media && b<=bufunfa) || (ef_b>=media && b == 0))
    {
        printf("eh dento\n");
    }
    else if(b>=bufunfa)
    {
        printf("foi de comes\n");
    }

    if(ef_c<media && c<=bufunfa)
    {
        printf("EH BOMBA TORRESMO\n");
    }
    if((ef_c>=media && c<=bufunfa) || (ef_c>=media && c == 0))
    {
        printf("eh dento\n");
    }
    else if(c>bufunfa)
    {
        printf("foi de comes\n");
    }

    if(ef_d<media && d<=bufunfa)
    {
        printf("EH BOMBA TORRESMO\n");
    }
    if((ef_d>=media && d<=bufunfa) || (ef_d>=media && d == 0))
    {
        printf("eh dento\n");
    }
    else if(d>bufunfa)
    {
        printf("foi de comes\n");
    }
    return 0;
}
