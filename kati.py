x = """#define t_and 1000
#define t_array 1001
#define t_begin 1002
#define t_boolean 1003
#define t_char 1004
#define t_dispose 1005
#define t_div 1006
#define t_do 1007
#define t_else 1008
#define t_end 1009
#define t_false 1010
#define t_forward 1011
#define t_function 1012
#define t_goto 1013
#define t_if 1014
#define t_integer 1015
#define t_label 1016
#define t_mod 1017
#define t_new 1018
#define t_nil 1019
#define t_not 1020
#define t_of 1021
#define t_or 1022
#define t_procedure 1023
#define t_program 1024
#define t_real 1025
#define t_result 1026
#define t_return 1027
#define t_then 1028
#define t_true 1029
#define t_var 1030
#define t_while 1031
#define t_id 1032
#define t_rconst 1033
#define t_iconst 1034
#define t_cconst 1035
#define t_sconst 1036
#define t_neq 1037
#define t_geq 1038
#define t_leq 1039
#define t_assign 1040"""

y = x.split('\n')
y = map(lambda a: a.replace("#define ", "")[:-5], y)
for i in y:
    print '"?" {return @;}'.replace("?", i[2:]).replace("@", i)

