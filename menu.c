#include "proc.h"
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sqlite3.h>

/*********************************/
/* 						 datas 	   				 */

char str_date_now[20];
char str_massa_body[12]= "110";
char str_massa_food[12]= "1";

sqlite3 *db;
//char z_err_mes[127];
int  dargc;
int  dfood_index;
char dfood_id[25][383];
char dfood_name[250][383];
char dargv[250][383];
char dacolname[25][383];
char d_norma_argv[50][383];
int rc;


/*********************************/
/* 						 procs 	   				 */

static GtkWidget *xpm_label_box( gchar     *xpm_filename,
                                 gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

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

/* Our usual callback function */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
    if ( 0 == strcmp("О программе",( char *) data ) ) about();
    if ( 0 == strcmp("База данных",( char *) data ) ) dbrowse();
    if ( 0 == strcmp("Изменить дату и массы",( char *) data ) )
                                              set_date_now();
    if ( 0 == strcmp("Результат",( char *) data ) )
                                              show_result( 1 );
    if ( 0 == strcmp("Добавить меню",( char *) data ) )
                                              show_food( 1 );
    if ( 0 == strcmp("Показать меню",( char *) data ) )
                                              show_view_menu( );
}

int main( int   argc,
          char *argv[] )
{
    get_date_now();
    select_norma();

    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button, *but1, *but2, *but3, *but4, *but5;
    GtkWidget *box, *box1, *box0, *box2, *box3, *box4, *box5;

    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window), PROGRAMM_NAME);

    /* It's a good idea to do this for all windows. */
    g_signal_connect (G_OBJECT (window), "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect (G_OBJECT (window), "delete-event",
	 	      G_CALLBACK (gtk_main_quit), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Create a new button */
    button = gtk_button_new ();
    but1 = gtk_button_new ();
    but2 = gtk_button_new ();
    but3 = gtk_button_new ();
    but4 = gtk_button_new ();
    but5 = gtk_button_new ();

    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), (gpointer) "База данных");
    g_signal_connect (G_OBJECT (but1), "clicked",
		      G_CALLBACK (callback), (gpointer) "Добавить меню");
    g_signal_connect (G_OBJECT (but2), "clicked",
		      G_CALLBACK (callback), (gpointer) "О программе");
    g_signal_connect (G_OBJECT (but3), "clicked",
		      G_CALLBACK (callback), (gpointer) "Показать меню");
    g_signal_connect (G_OBJECT (but4), "clicked",
		      G_CALLBACK (callback), (gpointer) "Результат");
    g_signal_connect (G_OBJECT (but5), "clicked",
		      G_CALLBACK (callback), (gpointer) "Изменить дату и массы");

    /* This calls our box creating function */
    box = xpm_label_box ("xpm/bibl.xpm", "База данных");
    box1 = xpm_label_box ("xpm/bludo.xpm", "Добавить меню");
    box2 = xpm_label_box ("xpm/help.xpm", "О программе");
    box3 = xpm_label_box ("xpm/graf.xpm", "Показать меню");
    box4 = xpm_label_box ("xpm/buch.xpm", "Результат");
    box5 = xpm_label_box ("xpm/pencil.xpm", "Изменить дату и массы");

    /* Pack and show all our widgets */
    gtk_widget_show (box);
    gtk_widget_show (box1);
    gtk_widget_show (box2);
    gtk_widget_show (box3);
    gtk_widget_show (box4);
    gtk_widget_show (box5);

    gtk_container_add (GTK_CONTAINER (button), box);
    gtk_container_add (GTK_CONTAINER (but1), box1);
    gtk_container_add (GTK_CONTAINER (but2), box2);
    gtk_container_add (GTK_CONTAINER (but3), box3);
    gtk_container_add (GTK_CONTAINER (but4), box4);
    gtk_container_add (GTK_CONTAINER (but5), box5);

    gtk_widget_show (button);
    gtk_widget_show (but1);
    gtk_widget_show (but2);
    gtk_widget_show (but3);
    gtk_widget_show (but4);
    gtk_widget_show (but5);

    box0 = gtk_vbox_new (FALSE, 0);
    gtk_widget_show (box0);
    gtk_container_add (GTK_CONTAINER (window), box0);
    gtk_box_pack_start (GTK_BOX (box0), but1, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box0), but4, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box0), but3, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box0), but5, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box0), button, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box0), but2, FALSE, FALSE, 3);

    gtk_widget_show (window);

    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return 0;
}
