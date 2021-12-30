#include <stdio.h>
#include <stdlib.h>
#include "function.h"


 typedef enum {Start, Word, Greater, Greater2, Newline, Stop, Lesss, Ampersand, Ampersand2, Or, Or2, Semicolon, Lbracket, Rbracket, Slahh, Dot, Dollar} vertex;
 vertex start();
 vertex word();
 vertex greater();
 vertex greater2();
 vertex stop();
 vertex newline();

 vertex lesss();//underthan
 vertex ampersand();//ampersent
 vertex ampersand2();//ampersent2
 vertex or();
 vertex or2();
 vertex semicolon();//comma
 vertex lbracket();
 vertex rbracket();
 vertex slashh();
 vertex dot();
 vertex dollar();
 char pred;


 int main() {
     vertex V=Start;
     c=getchar();
     while(1)
     switch(V){
         case Start: V=start();
         break;

         case Word: V=word();
         break;

         case Greater: V=greater();
         break;

         case Greater2: V=greater2();
         break;

         case Newline: V=newline();
         break;

         case Stop: exit(0);
         break;

          case Lesss: exit(0);
         break;

          case Ampersand: exit(0);
         break;

          case Ampersand2: exit(0);
         break;

          case Or: exit(0);
         break;

          case Or2: exit(0);
         break;

          case Semicolon: exit(0);
         break;

          case Lbracket: exit(0);
         break;

          case Rbracket: exit(0);
         break;

          case Slahh: exit(0);
         break;

           case Dot: exit(0);
         break;

           case Dollar: exit(0);
         break;
     }
}

vertex start() {
    if(c==' '||c=='\t') { c=getchar(); return Start;}
    else if (c==EOF) {
        termlist();
        printlist();
        clearlist();
        return Stop;
    }
    else if (c=='\n') {
        termlist();
        printlist();
        c=getchar();
        return Newline;
    }
    else {
        char cprev=c;
        nullbuf();
        addsym();
        c=getchar();
        return ((cprev == '>'))? Greater: ((cprev == '|'))? Or: ((cprev == '&'))? Ampersand: ((cprev == ';'))? Semicolon: ((cprev == '<'))? Lesss: ((cprev == '('))? Lbracket: ((cprev == ')'))? Rbracket: Word;
    }
}

vertex word(){
     if(symset(c)) {
         addsym();
         c=getchar();
         return Word;
     }
     else {
     addword();
     return Start;
     }
}

vertex greater() {
     if(c=='>') {
         addsym();
         c=getchar();
         return Greater2;
     }
     else {
         addword();
         return Start;
     }
}

vertex greater2() {
     addword();
     return Start;
}

vertex newline(){
     clearlist();
     return Start;
}

////////
vertex lesss(){
    if (symset(c) && (c == '<')){
        addsym();
        c = getchar();
        return Lesss;
    }
    else{
        addword();
        return Start;
    }
}

vertex ampersent(){
    if (c == '&'){
        addsym();
        c = getchar();
        return Ampersand2;
    }
    else{
        addword();
        return Start;
    }
}

vertex ampersand2(){
    addword();
    return Start;
}

vertex or(){
    if(c == '|'){
        addsym();
        c = getchar();
        return Or2;
    }
    else{
        addword();
        return Start;
    }
}

vertex or2(){
    addword();
    return Start;
}

vertex stop(){
    exit(0);
}

vertex semicolon(){
    if (symset(c) && (c == ';')){
        addsym();
        c = getchar();
    }
    else{
        addword();
        return Start;
    }
    return Semicolon;
}

vertex lbracket(){
    if (symset(c) && (c == '(')){
        addsym();
        c = getchar();
    }
    else{
        addword();
        return Start;
    }
    return Lbracket;
}

vertex rbracket(){
    if (symset(c) && (c == ')')){
        addsym();
        c = getchar();
    }
    else{
        addword();
        return Start;
    }
    return Rbracket;
}

vertex slashh(){
    if (symset(c) && (c == '/')){
        addsym();
        c = getchar();
    }
    else{
        addword();
        return Start;
    }
    return slashh;
}

vertex dot(){
    if (symset(c) && (c == '.')){
        addsym();
        c = getchar();
    }
    else{
        addword();
        return Start;
    }
    return Dot;
}

vertex dollar(){
    if (symset(c) && (c == '$')){
        addsym();
        c = getchar();
    }
    else{
        addword();
        return Start;
    }
    return Dollar;
}






