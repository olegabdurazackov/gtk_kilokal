#ifndef PROC_H
#define PROC_H

#define PROGRAMM_VERSION "version 3.0.0"
#define PROGRAMM_NAME		 " Графическая оболочка kolokal "
#define PROGRAMM_DESCRIPTION	 "\n  Учёт химических элементов, "\
      "получаемых с пищей."\

#define FI 1.618
#define HIGHT_MAIN 440
#define WIDTH_MAIN 808
#define HIGHT_POPUP 320
#define WIDTH_POPUP 678

#define DB_FILE   "kkal.db"

void about();
void dbrowse();
void get_date_now();
void form_edit ( int argc,
                char** argv, 
                char** col_name );
int dopen();
void dclose();
void error ( int rc,
							char *msg,
							char *z_err_mes,
							char* ok );
void select_norma ( );
void select_date ( );
void select_food ( );
void gr_edit_data();
void set_date_now();
void show_result();
void show_food();
void show_view_menu();
void select_max_food();
void select_view_menu();
void food_add_menu ();
#endif
