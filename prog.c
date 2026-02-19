#include<stdio.h>
#include<string.h>
           char*B="";
           char*Q=
"#include<stdio.h>~n#include<string.h>~n           char*B=~q~1~q;~n           char*Q=~n~q~2~q;~n         unsigned h(~n        char*s,int n){~n       unsigned v    =~n      0x811C9DC5u;~n     while(n--)v    =~n      (*(unsigned~n       char*)s++^v)*~n        0x1000193u;~n         v^=v>>16;~n          v*=0x45d9f3bu;~n         v^=v>>16;~n        return v; }~n       unsigned p(~n      char**s){~n     unsigned v=0;~n      while(**s&&~n       **s!=58&&~n        **s!=124)~n         v=v*16+(~n          **s>57?**s~n         -87:**s-48),~n        (*s)++;~n       return v; }~n      unsigned w(~n     unsigned a,~n      unsigned b){~n       unsigned c=~n        a^b*~n         0x9E3779B9u;~n          c^=c>>16;~n         c*=0x45d9f3bu;~n        c^=c>>16;~n       return c; }~n      int e(char*q,~n     char*b,char*o){~n      int n=0,l; for(~n       ; *q; q++)if(~n        *q==126){ q++;~n         if(*q==49){~n          l=strlen(b);~n         if(o)memcpy(~n        o+n,b,l); else~n       fwrite(b,1,l,~n      stdout); n+=l; }~n     else if(*q==50){~n      l=strlen(Q);~n       if(o)memcpy(~n        o+n,Q,l); else~n         fwrite(Q,1,l,~n          stdout); n+=l;~n         } else{ char c=~n        *q==110?10:*q==~n       113?34:*q==98?92~n      :*q==126?126:*q==~n     116?9:*q; if(o)o[n~n      ]=c; else putchar~n       (c); n++; } }~n        else{ if(o)o[n]~n         =*q; else~n          putchar(*q);~n         n++; } if(o)~n        o[n]=0;~n       return n; }~n      int main(void){~n     char s[8192],~n      pb[4096],~n       nb[4096],hx[16],~n        nx[16],*r; int~n         k=0,l; unsigned~n          sh,nc,ch,mh,mn;~n         pb[0]=0; r=B;~n        while(*r){ sh=~n       p(&r); if(*r==~n      58)r++; nc=p(&r);~n     if(*r==124)r++; l=~n      e(Q,pb,s); ch=h(s,l~n       ); if(ch!=sh)return~n        1; if(w(ch,nc)&~n         0xFFFFF)return 1;~n          sprintf(hx,~n         ~q%08x~q,sh);~n        strcat(pb,hx);~n       strcat(pb,~q:~q);~n      sprintf(nx,~q%x~q,~n     nc); strcat(pb,nx);~n      strcat(pb,~q|~q); k++;~n       } l=e(Q,B,s); mh=~n        h(s,l); for(mn=0;~n         ; mn++)if(!(w(mh~n          ,mn)&0xFFFFF))~n         break; sprintf(~n        hx,~q%08x~q,mh);~n       sprintf(nx,~q%x~q,~n      mn); strcpy(nb,B);~n     strcat(nb,hx);~n      strcat(nb,~q:~q);~n       strcat(nb,nx);~n        strcat(nb,~q|~q);~n         e(Q,nb,0);~n          return 0*k; }~n";
         unsigned h(
        char*s,int n){
       unsigned v    =
      0x811C9DC5u;
     while(n--)v    =
      (*(unsigned
       char*)s++^v)*
        0x1000193u;
         v^=v>>16;
          v*=0x45d9f3bu;
         v^=v>>16;
        return v; }
       unsigned p(
      char**s){
     unsigned v=0;
      while(**s&&
       **s!=58&&
        **s!=124)
         v=v*16+(
          **s>57?**s
         -87:**s-48),
        (*s)++;
       return v; }
      unsigned w(
     unsigned a,
      unsigned b){
       unsigned c=
        a^b*
         0x9E3779B9u;
          c^=c>>16;
         c*=0x45d9f3bu;
        c^=c>>16;
       return c; }
      int e(char*q,
     char*b,char*o){
      int n=0,l; for(
       ; *q; q++)if(
        *q==126){ q++;
         if(*q==49){
          l=strlen(b);
         if(o)memcpy(
        o+n,b,l); else
       fwrite(b,1,l,
      stdout); n+=l; }
     else if(*q==50){
      l=strlen(Q);
       if(o)memcpy(
        o+n,Q,l); else
         fwrite(Q,1,l,
          stdout); n+=l;
         } else{ char c=
        *q==110?10:*q==
       113?34:*q==98?92
      :*q==126?126:*q==
     116?9:*q; if(o)o[n
      ]=c; else putchar
       (c); n++; } }
        else{ if(o)o[n]
         =*q; else
          putchar(*q);
         n++; } if(o)
        o[n]=0;
       return n; }
      int main(void){
     char s[8192],
      pb[4096],
       nb[4096],hx[16],
        nx[16],*r; int
         k=0,l; unsigned
          sh,nc,ch,mh,mn;
         pb[0]=0; r=B;
        while(*r){ sh=
       p(&r); if(*r==
      58)r++; nc=p(&r);
     if(*r==124)r++; l=
      e(Q,pb,s); ch=h(s,l
       ); if(ch!=sh)return
        1; if(w(ch,nc)&
         0xFFFFF)return 1;
          sprintf(hx,
         "%08x",sh);
        strcat(pb,hx);
       strcat(pb,":");
      sprintf(nx,"%x",
     nc); strcat(pb,nx);
      strcat(pb,"|"); k++;
       } l=e(Q,B,s); mh=
        h(s,l); for(mn=0;
         ; mn++)if(!(w(mh
          ,mn)&0xFFFFF))
         break; sprintf(
        hx,"%08x",mh);
       sprintf(nx,"%x",
      mn); strcpy(nb,B);
     strcat(nb,hx);
      strcat(nb,":");
       strcat(nb,nx);
        strcat(nb,"|");
         e(Q,nb,0);
          return 0*k; }
