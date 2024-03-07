/* void show_result() */

#include "proc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <gtk/gtk.h>

extern char str_food_elem_max[];
extern char str_food_add_menu[];
extern char str_food_id[];
extern char str_date_now[];
extern char str_massa_body[];
extern sqlite3 *db;
extern int  dargc;
extern int  dfood_index;
extern char dfood_id[25][383];
extern char dfood_name[250][383];
extern char dargv[250][383];
extern char dacolname[25][383];
extern char d_norma_argv[50][383];
extern int rc;

  GtkWidget *window;
  GtkWidget *window_food;
  GtkWidget *window_view_menu;
  GtkWidget *mktable();
  GtkWidget *mktable_food();
  GtkWidget *mktable_view_menu();
  GtkWidget *mkbutton(char* elem,
                    char* norma);
  GtkWidget *mkbutton_m(char* elem,
                    char* norma);
  GtkWidget *mkbutton_xpm_result(char* elem,
                    char* norma,
                    char* summa);

/********************************************/
void get_result(){
    printf ( "Start get_result\n" );
    select_date ( );
    printf ( "Получены данные для даты : %s\n",
            str_date_now );

}
/********************************************/
void free_this3(){
  gtk_widget_destroy(window);
}

/********************************************/
void show_result( int rezmax ){

  GtkWidget *table;

    printf ( "Start show_result\n" );
  if ( rezmax ) get_result();

  /* Make a window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (free_this3),
                    NULL);
  gtk_window_set_title (GTK_WINDOW(window), str_date_now );
//  gtk_widget_set_size_request (GTK_WIDGET(window),
//                              WIDTH_MAIN, HIGHT_MAIN);
  table = mktable();
  gtk_container_add (GTK_CONTAINER (window), table);
 
  gtk_widget_show (window);

}

/********************************************/
GtkWidget *mktable(){
  GtkWidget *table;
  GtkWidget *button;

    printf ( "Start mktable\n" );
  int i, row = 10, col = 8, j=1, k=1 /*col*/;
  table = gtk_table_new(row,col,FALSE);
  gtk_widget_show(table);
  i =0;
  printf ( "i=%d j=%d k=%d dacolname=%s argv=%s norma=%s\n",
             i,j,k,dacolname[i],dargv[i],d_norma_argv[i]);
  for ( i = 1; dargc > i; i++ ){ 
      printf ( "i=%d j=%d k=%d dacolname=%s argv=%s norma=%s\n",
              i,j,k,dacolname[i],dargv[i],d_norma_argv[i]);
      button = mkbutton_xpm_result ( dacolname[i],
                          dargv[i],
                          d_norma_argv[i]);
      gtk_table_attach_defaults(GTK_TABLE(table),button,
              k-1, k, j-1, j );
      j = ( k==col )? j+1: j ;
      k = ( k==col )? 1: k+1 ;
  }

  return table;   
}
/********************************************/
static void callback_food ( GtkWidget *widget,
                              gpointer data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
    strcpy ( str_food_add_menu , ( char *) data );
    dfood_index=0;
    food_add_menu();
}

GtkWidget *mkbutton(char* elem,
                    char* summa){
    printf ( "Start mkbutton\n" );
  GtkWidget *button;
  char label[64];
  sprintf ( label, "[%s]\n%s", elem, summa );
  button = gtk_button_new_with_label(label);
  gtk_widget_show(button);
  g_signal_connect (G_OBJECT (button), "clicked",
		  G_CALLBACK (callback_food),
      (gpointer) elem);
  return button;
}

/********************************************/
static GtkWidget *xpm_label_box1( gchar *xpm_filename,
                                 gchar  *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    printf ( "Start xpm_label_box1\n" );
    /* Create box for image and label */
    box = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* Now on to the image stuff */
    image = gtk_image_new_from_file (xpm_filename);

    /* Create a label for the button */
    label = gtk_label_new (label_text);

    /* Pack the image and label into the box */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}

/********************************************/
static void callback_result ( GtkWidget *widget,
                              gpointer data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
    strcpy ( str_food_elem_max , ( char *) data );
    dfood_index=0;
    select_max_food();
    show_food ( 0 );
}

GtkWidget *mkbutton_xpm_result ( char* elem,
                                 char* summa,
                                 char* norma )
{
  GtkWidget *button;
  GtkWidget *box;

    printf ( "Start mkbutton_xpm_result\n" );
  char lab[64], xpm[16];
  double sum = atof ( summa );
  double nor = atof ( norma );
  double m = atof ( str_massa_body );
  nor =  nor/80*m; 
  int a = ( int ) sum/( nor/10 );
  a = ( a<0 )? 10 : ( a >10 )? 10: a;
  sprintf ( xpm, "xpm/p%d.xpm", a );
  printf( "a=%d xpm= %s\n",a, xpm );
  sprintf ( lab, "%s\n%s\n[%d]",
          elem, summa, ( int ) nor );
  box = xpm_label_box1 (xpm, lab);
  gtk_widget_show (box);
  button = gtk_button_new ();
  gtk_container_add (GTK_CONTAINER (button), box);
  gtk_widget_show(button);
  g_signal_connect (G_OBJECT (button), "clicked",
		  G_CALLBACK (callback_result),
      (gpointer) elem);
  return button;
}

/********************************************/
/*                show food                 */
/********************************************/
void get_food(){
    printf ( "Start get_food\n" );
    dargc=0;
    dfood_index=0;
    select_food ( );
    printf ( "Получены данные для  %d продуктов\n",
            dargc/2 );

}
/********************************************/
void free_this4(){
  gtk_widget_destroy(window_food);
}

/********************************************/
void show_food( int sel ) {
  GtkWidget *scrolled_window;
  GtkWidget *table;

    printf ( "Start show_food\n" );
  if ( sel ) get_food();

  /* Make a window */
  window_food = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window_food, 1200, 600);
  g_signal_connect (G_OBJECT (window_food), "destroy",
                    G_CALLBACK (free_this4),
                    NULL);
  gtk_window_set_title (GTK_WINDOW(window_food), str_date_now );
  
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_container_add (GTK_CONTAINER (window_food),
                                  scrolled_window);
  gtk_widget_show (scrolled_window);

  table = mktable_food();
  gtk_scrolled_window_add_with_viewport (
                   GTK_SCROLLED_WINDOW (scrolled_window), table);
 
  gtk_widget_show (window_food);

}

/********************************************/
GtkWidget *mkbutton_xpm_result_food ( char* id,
                                   char* name ){
  GtkWidget *button;
  GtkWidget *box;
    printf ( "Start mkbutton_xpm_result_food\n" );
  char lab[64], xpm[16];
//  char a[24];
  char* a = "help";
  sprintf ( xpm, "xpm/%s.xpm", a );
  printf( "a=%s xpm= %s\n",a, xpm );
  sprintf ( lab, "[%s]\n%s",
          id, name );
  box = xpm_label_box1 (xpm, lab);
  gtk_widget_show (box);
  button = gtk_button_new ();
  gtk_container_add (GTK_CONTAINER (button), box);
  gtk_widget_show(button);
  return button;
}

/********************************************/
GtkWidget *mktable_food(){
  GtkWidget *table;
  GtkWidget *button;

  printf ( "Start mktable food\n" );

  int i, row = 100, col = 3, j=1, k=1 /*col*/;
  table = gtk_table_new(row,col,FALSE);
  gtk_widget_show(table);
  i =dfood_index;
  printf ( "i=%d j=%d k=%d \n",
             i,j,k );
  for ( i = 0; dfood_index > i; i=i+1 ){ 
      printf ( "i=%d j=%d k=%d id=%s argv=%s\n ",
              i,j,k,dfood_id[i],dfood_name[i]);
      button = mkbutton ( dfood_id[i],
                          dfood_name[i] );
      gtk_table_attach_defaults(GTK_TABLE(table),button,
              k-1, k, j-1, j );
      j = ( k==col )? j+1: j ;
      k = ( k==col )? 1: k+1 ;
  }

  return table;   
}
/********************************************/
/********************************************/
/*                show view menu            */
/********************************************/
void get_view_menu()
{
    printf ( "Start get_view_menu\n" );
    dargc=0;
    dfood_index=0;
    select_view_menu ( );
    printf ( "Получены данные для  %d продуктов\n",
            dargc/2 );

}
/********************************************/
void free_this5()
{
  gtk_widget_destroy(window_view_menu);
}

/********************************************/
void show_view_menu(  )
{
  GtkWidget *scrolled_window;
  GtkWidget *table;

  printf ( "Start show_view_menu\n" );
  get_view_menu();

  /* Make a window */
  window_view_menu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window_view_menu, 800, 400);
  g_signal_connect (G_OBJECT (window_view_menu), "destroy",
                    G_CALLBACK (free_this5),
                    NULL);
  gtk_window_set_title (GTK_WINDOW(window_view_menu), str_date_now );
  
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_container_add (GTK_CONTAINER (window_view_menu),
                                  scrolled_window);
  gtk_widget_show (scrolled_window);

  table = mktable_view_menu();
  gtk_scrolled_window_add_with_viewport (
                   GTK_SCROLLED_WINDOW (scrolled_window), table);
 
  gtk_widget_show (window_view_menu);

}

/********************************************/

GtkWidget *mkbutton_m(char* elem,
                    char* summa){
    printf ( "Start mkbutton\n" );
  GtkWidget *button;
  char label[64];
  sprintf ( label, "[%s]\n%s", elem, summa );
  button = gtk_button_new_with_label(label);
  gtk_widget_show(button);
  return button;
}
/********************************************/

GtkWidget *mktable_view_menu()
{
  GtkWidget *table;
  GtkWidget *button;

  printf ( "Start mktable food\n" );

  int i, row = 100, col = 3, j=1, k=1 /*col*/;
  table = gtk_table_new(row,col,FALSE);
  gtk_widget_show(table);
  i =dfood_index;
  printf ( "i=%d j=%d k=%d \n",
             i,j,k );
  for ( i = 0; dfood_index > i; i=i+1 ){ 
      printf ( "i=%d j=%d k=%d id=%s argv=%s\n ",
              i,j,k,dfood_id[i],dfood_name[i]);
      button = mkbutton_m ( dfood_id[i],
                          dfood_name[i] );
      gtk_table_attach_defaults(GTK_TABLE(table),button,
              k-1, k, j-1, j );
      j = ( k==col )? j+1: j ;
      k = ( k==col )? 1: k+1 ;
  }

  return table;   
}
/********************************************/
