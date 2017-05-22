start : expr ;
expr : expr MULT expr | ZERO | ONE ;
MULT : '*' ;
ZERO : '0' ;
ONE : '1' ;
