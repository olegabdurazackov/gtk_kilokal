#include "proc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>

extern char str_date_now[];
extern char str_massa_body[];
extern char str_massa_food[];

  GtkWidget *window1;
  GtkWidget *frame, *frame1, *frame2, *frame3;
  GtkWidget *main_vbox, *hbox, *hbox1,*hbox2,*hbox3;
  GtkWidget *entry_date, *entry_massa, *entry_massa_food;

/********************************************/
int a2a ( const gchar* in ){
    g_message (" --= start a2a =--%s!\n", in);
    int out = 0;
    int i = strlen ( in ) -1 ;;
        for ( i; i >=0; i-- ){
            if ( ( '0' > in[i] || ':' < in[i] ) && '.' != in[i] ){
                out = 1;
                continue;
            }
        }

    return out;

}
/********************************************/
void get_date_now(){
    printf ( "Start get_date_now\n" );
    time_t t = time ( NULL );
    struct tm* ptm = localtime ( &t );
    strftime ( str_date_now, 
            19, "%Y-%m-%d", ptm );
    printf ( "Установлена дата : %s\n",
            str_date_now );

}
/********************************************/
static void enter_callback_date( GtkWidget *widget,
                            GtkWidget *entry_date )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry_date));
  strcpy( str_date_now, entry_text );
  printf ("Entry contents: %s\n", str_date_now);
}
                     
/********************************************/
static void enter_callback_massa( GtkWidget *widget,
                            GtkWidget *entry_massa )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry_massa));
	if ( a2a ( entry_text ) ){
  		printf ( "введите число\n" );
	}else{
		  strcpy( str_massa_body, entry_text );
 			printf ("Entry contents: %s\n", str_massa_body);
	}
}
                     
/********************************************/
static void enter_callback_massa_food( GtkWidget *widget,
                            GtkWidget *entry_massa_food )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (
									GTK_ENTRY (entry_massa_food));
	if ( a2a ( entry_text ) ){
  		printf ( "введите число\n" );
	}else{
      strcpy( str_massa_food, entry_text );
      printf ("Entry contents: %s\n", str_massa_food);
  }
}
                     
/********************************************/
void free_this2(){
  
  gtk_widget_destroy(window1);
}

void set_date_now(){
  /* Make a window */
  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (window1), "destroy",
                    G_CALLBACK (free_this2),
                    NULL);
  gtk_window_set_title ( GTK_WINDOW(window1),
												"Ввод даты и масс" );
//  gtk_widget_set_size_request (GTK_WIDGET(window1),
//                              WIDTH_MAIN, HIGHT_MAIN);
 
    entry_date = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_date), 12);
    g_signal_connect (entry_date, "changed",
		      G_CALLBACK (enter_callback_date),
		      (gpointer) entry_date);
    gtk_entry_set_text (GTK_ENTRY (entry_date), str_date_now);

    entry_massa = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_massa), 12);
    g_signal_connect (entry_massa, "changed",
		      G_CALLBACK (enter_callback_massa),
		      (gpointer) entry_massa);
    gtk_entry_set_text (GTK_ENTRY (entry_massa), str_massa_body);

    entry_massa_food = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_massa_food), 12);
    g_signal_connect (entry_massa_food, "changed",
		   					   G_CALLBACK (enter_callback_massa_food),
		    					 (gpointer) entry_massa_food);
    gtk_entry_set_text (GTK_ENTRY (entry_massa_food),
											str_massa_food);

    gtk_widget_show (entry_date);
    gtk_widget_show (entry_massa);
    gtk_widget_show (entry_massa_food);

  frame= gtk_frame_new ( "Ввод данных");
  frame1= gtk_frame_new ( "Дата:");
  frame2= gtk_frame_new ( "Вес тела ( кГ ):");
  frame3= gtk_frame_new ( "Масса продукта ( 100 Г ):");

  gtk_container_add (GTK_CONTAINER (frame1), entry_date);
  gtk_container_add (GTK_CONTAINER (frame2), entry_massa);
  gtk_container_add (GTK_CONTAINER (frame3), entry_massa_food);

    gtk_widget_show (frame);
    gtk_widget_show (frame1);
    gtk_widget_show (frame2);
    gtk_widget_show (frame3);

  /* Make a vbox to put the three menus in */
  main_vbox = gtk_vbox_new (FALSE, 1);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 5);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 5);
  gtk_container_set_border_width (GTK_CONTAINER (frame1), 3);
  gtk_container_set_border_width (GTK_CONTAINER (frame2), 3);
  gtk_container_set_border_width (GTK_CONTAINER (frame3), 3);
  gtk_container_add (GTK_CONTAINER (window1), main_vbox);
  gtk_container_add (GTK_CONTAINER (main_vbox), frame);
 
  hbox = gtk_hbox_new (FALSE, 5);
  hbox1= gtk_hbox_new (FALSE, 5);
  hbox2= gtk_hbox_new (FALSE, 5);
  hbox3= gtk_hbox_new (FALSE, 5);
  gtk_container_add (GTK_CONTAINER (frame), hbox);
  gtk_container_add (GTK_CONTAINER (hbox1), frame1);
  gtk_container_add (GTK_CONTAINER (hbox2), frame2);
  gtk_container_add (GTK_CONTAINER (hbox3), frame3);
  gtk_box_pack_start (GTK_BOX (hbox), hbox1, FALSE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), hbox2, FALSE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), hbox3, FALSE, TRUE, 0);

  gtk_widget_show_all (window1);

}

/********************************************/
