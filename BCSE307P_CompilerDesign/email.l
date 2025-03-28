character [a-zA-Z0-9]
domain {character}+(\.{character}+)+
email ^.*{character}[{character}.]*@{domain}$

%%
{email} {printf("Valid!");}
.* {printf("Invalid! %d", yyleng);}
%%