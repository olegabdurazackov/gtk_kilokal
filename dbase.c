#include "proc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*********************************/
/* 						 datas 	   				 */

extern char str_date_now[];
extern char str_massa_food[];
char str_food_elem_max[64];
char str_food_add_menu[255];
char str_food_id[8];
extern sqlite3 *db;
//extern char z_err_mes[127];
extern int  dargc;
extern int  dfood_index;
extern char dfood_id[25][383];
extern char dfood_name[250][383];
extern char dargv[250][383];
extern char dacolname[25][383];
extern char d_norma_argv[50][383];
extern int rc;


/****************************************/
void dbrowse(){
		char cmd[64];
		sprintf ( cmd, "sqlitebrowser %s" , DB_FILE );
		system ( cmd );

}
/****************************************/
void error ( int rc,
            char *msg,
            char *z_err_mes,
            char* ok) {
    if ( rc ) {
        fprintf ( stderr,msg, z_err_mes );
        sqlite3_free ( z_err_mes );
    }else{
        fprintf ( stdout, ok );
    }
}
/****************************************/

int dopen(){
    rc = sqlite3_open ( DB_FILE, &db );
    if ( rc ) {
        fprintf(stderr,"не могу открыть %s\n",
                sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stdout,"открыл rc= %d \n",rc);
        return 0;
    }
}
/****************************************/

void dclose(){
    sqlite3_close(db);
    printf("закрыл \n");

}
/****************************************/

static int callback_db ( void *not_used,
                      int argc,
                     char **argv,
                     char **az_col_name ) {
    printf ( "Start callback_db argc=%d,dfood_index=%d\n",
            argc, dfood_index );
    int i;
    for ( i=0; i<argc; i++ ) {
        printf("%s= %s\t",az_col_name[i],argv[i]?argv[i]:"NULL");
        strcpy(dargv[i],argv[i]);
        strcpy(dacolname[i],az_col_name[i]);
        printf("%s= %s\t",dacolname[i],dargv[i]?dargv[i]:"NULL");
        dfood_index++;
    }
    dargc = argc ;
    printf("\n");
    return 0;
}

/****************************************/
static int callback_food ( void *not_used,
                      int argc,
                     char **argv,
                     char **az_col_name ) {
    printf ( "Start callback_food argc=%d,dfood_index=%d\n",
            argc, dfood_index );
    int i;
    for ( i=1; i<argc; i=i+2 ) {
        printf("%s= %s\t",az_col_name[i],argv[i]?argv[i]:"NULL");
        strcpy(dfood_id[dfood_index],argv[i-1]);
        strcpy(dfood_name[dfood_index],argv[i]);
        dfood_index++;
    }
    printf("\n");
    return 0;
}

/****************************************/
static int callback_norma ( void *not_used,
                            int argc,
                            char **argv,
                            char **az_col_name ) {
    int i;
    for ( i=0; i<argc; i++ ) {
        printf("%s= %s\t",az_col_name[i],argv[i]?argv[i]:"NULL");
        strcpy ( d_norma_argv[i], argv[i] );
    }
    dargc = argc ;
    printf ( " argc=%d\n", argc );
    return 0;
}

/****************************************/
void select_norma ( ){
    dopen();
    char *z_err_mes=0;
    char* sql="select * from dp where data like 'norma';";
    int rc=sqlite3_exec(db,sql,callback_norma,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
    dclose();
}

/****************************************/
void select_date ( ){
    dopen();
    char *z_err_mes=0;
    char sql[127];
    sprintf (sql,
            "select * from dp where data like '%s';",
            str_date_now );
    int rc=sqlite3_exec(db,sql,callback_db,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
    dclose();
}

/****************************************/
void select_food ( ){
    printf ( "Start select_food\n" );
    dopen();
    char *z_err_mes=0;
    char* sql="select foodid,name from food order by name;";
    int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
    dclose();
}
/****************************************/
void select_max_food ( ){
    printf ( "Start select_max_food\n" );
    dopen();
    char *z_err_mes=0;
    char sql[255];
    sprintf ( sql,
       "select foodid,name from food_ordnung order by %s desc limit 30;",
       str_food_elem_max );
    int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
    dclose();
    printf ( "End select_max_food\n" );
}

void food_add_menu ( ){
    printf ( "Start food_add_menu\n" );
    dopen();
    char *z_err_mes=0;
    char sql[255];
    sprintf ( sql,
       "insert into pot(foodid,massa100g,data) values('%s','%s','%s') ;",
       str_food_add_menu, str_massa_food, str_date_now );
    int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
    dclose();
    printf ( "End food_add_menu\n" );
}

/****************************************/
void select_view_menu ( ){
    dopen();
    char *z_err_mes=0;
    char sql[127];
    sprintf (sql,
            "select massa100g,name from pot"
            " left join food on pot.foodid=food.foodid "
            "where data like '%s';",
            str_date_now );
    int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
    dclose();
}

