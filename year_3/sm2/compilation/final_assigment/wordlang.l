%{
#include "y.tab.h"
%}

%%

"char"       { return CHAR; }
"int"        { return INT; }
"word"       { return WORD; }
"sentence"   { return SENTENCE; }
"if"         { return IF; }
"else"       { return ELSE; }
"while"      { return WHILE; }
"loop"       { return LOOP; }
"input"      { return INPUT; }
"output"     { return OUTPUT; }

"+"          { return PLUS; }
"-"          { return MINUS; }
"="          { return ASSIGN; }
"#"          { return HASH; }
":"          { return COLON; }
"<"          { return LESS_THAN; }
">"          { return GREATER_THAN; }
"<="         { return LESS_EQUAL; }
">="         { return GREATER_EQUAL; }
"=="         { return EQUAL; }
"!"          { return NOT; }

[0-9]+       { yylval.int = atoi(yytext); return INTEGER; }
[a-zA-Z_][a-zA-Z0-9_]{0,31} { strcpy(yylval.str, yytext); return IDENTIFIER; }

\"[^\"]*\" { strcpy(yylval.str,yytext);return WORD_LITERAL; }
\'[^\']\'   { strcpy(yylval.str,yytext);return CHAR_LITERAL; }
\^[^^]*\^ {strcpy(yylval.str,yytext) ;return SENTENCE_LITERAL; }

[ \t\n]+     { /* ignore whitespace */ }
.            { printf("Unknown character: %s\n", yytext); }

%%

int yywrap (void) {return 1;}

