/***********************************************************
*
*A simple GTK example
*simple.c: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#include <gtk/gtk.h>
#include "simple.h"
#include "string.h"
/*Global Variables */

GtkWidget *window ;
GtkWidget *fixed ;
GtkWidget *chess_icon ;
GtkWidget *table ;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *board_fixed;

enum GRID Board[8][8];
enum GRID BoardLocation[3][2]; //setting a new array to store clicking location. 0,0 is selectclick.

void InitBoard(){
int i, j;
for(i=0;i<8;i++)
        {
                for(j=0;j<8;j++)
                {
                        if(0 != i%2)
                        {
                                if(0 != j%2)//?~Si?~X??~G?~U?j?~X??~G?~U??~W?
                                {
                                        Board[i][j] = WHITE;
                                }
                                else//?~Si?~X??~G?~U?j?~X??~A??~U??~W?
                                {
                                        Board[i][j] = BLACK;
                                }
                        }
                        else
                        {
                if(0 != j%2)//?~Si?~X??~A??~U?j?~X??~G?~U??~W?
                                {
                                        Board[i][j] = BLACK;
                                }
                                else//?~Si?~X??~A??~U?j?~X??~A??~U??~W?
                                {
                                        Board[i][j] = WHITE;
                                }
                        }
                }
        }
   for(i = 0; i < 8; i++){
	Board[i][1] = BPawn;
	Board[i][6] = WPawn;
	}
   Board[0][0] = Board[7][0] = BRook;
   Board[0][7] = Board[7][7] = WRook;
   Board[1][0] = Board[6][0] = BKnight;
   Board[1][7] = Board[6][7] = WKnight;
   Board[2][0] = Board[5][0] = BBishop;
   Board[2][7] = Board[5][7] = WBishop;
   Board[3][7] = WKing;
   Board[3][0] = BKing;
   Board[4][7] = WQueen;
   Board[4][0] = BQueen;
//   Board[4][3] = WQueen;
}

int CheckColor(int i, int j)
{
  if(0 != i%2)
  {
          if(0 != j%2)//?~Si?~X??~G?~U?j?~X??~G?~U??~W?
          {
                  Board[i][j] = WHITE;
          }
          else//?~Si?~X??~G?~U?j?~X??~A??~U??~W?
          {
                  Board[i][j] = BLACK;
          }
  }
  else
  {
if(0 != j%2)//?~Si?~X??~A??~U?j?~X??~G?~U??~W?
          {
                  Board[i][j] = BLACK;
          }
          else//?~Si?~X??~A??~U?j?~X??~A??~U??~W?
          {
                  Board[i][j] = WHITE;
          }
  }
}



void ReverseGridColor(int g_x, int g_y)
{
	if(Board[g_x][g_y] == BLACK)
	{
		Board[g_x][g_y] = WHITE;
	}
	else
	{
		Board[g_x][g_y] = BLACK;
	}
}

/*void MoveTheWKing(int g_x, int g_y)
{
	ResetBoard();
	Board[g_x][g_y] = WKing;
}

void MoveTheBKing(int g_x, int g_y)
{
	ResetBoard();
	Board[g_x][g_y] = BKing;
}*/


void DrawBoard()
{
	int i, j;

    for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bsquare.jpg") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./chess_icon/Wsquare.jpg") ;
					break;
				case WKing:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.png") ;
					break;
				case BKing:
					chess_icon = gtk_image_new_from_file("./chess_icon/BKing.png");
					break;
				case BPawn:
					chess_icon = gtk_image_new_from_file("./chess_icon/BPawn.png");
					break;
				case WPawn:
					chess_icon = gtk_image_new_from_file("./chess_icon/WPawn.png");
					break;
        case WRook:
          chess_icon = gtk_image_new_from_file("./chess_icon/WRook.png");
          break;
        case WKnight:
          chess_icon = gtk_image_new_from_file("./chess_icon/WKnight.png");
          break;
        case WQueen:
          chess_icon = gtk_image_new_from_file("./chess_icon/WQueen.png");
          break;
        case WBishop:
          chess_icon = gtk_image_new_from_file("./chess_icon/WBishop.png");
          break;
        case BRook:
          chess_icon = gtk_image_new_from_file("./chess_icon/BRook.png");
          break;
        case BKnight:
          chess_icon = gtk_image_new_from_file("./chess_icon/BKnight.png");
          break;
        case BBishop:
          chess_icon = gtk_image_new_from_file("./chess_icon/BBishop.png");
          break;
        case BQueen:
          chess_icon = gtk_image_new_from_file("./chess_icon/BQueen.png");
          break;
				default:
					break;

			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}
void GUIMove(int s_x, int s_y, int g_x, int g_y)
{

  BoardLocation[2][1] = Board[g_x][g_y];
  CheckColor(g_x, g_y);
  Board[s_x][s_y] = BoardLocation[2][1];
  DrawBoard();
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
  BoardLocation[0][0] = *g_x;
  BoardLocation[0][1] = *g_y;
}


void SelectCoordToGrid(int c_x, int c_y, int *s_x, int *s_y)
{
	*s_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*s_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
  BoardLocation[1][0] = *s_x;
  BoardLocation[1][1] = *s_y;
}
/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below.
 */
static void
print_hello (GtkWidget *widget,
     gpointer   data)
{
  g_print ("Hello World\n");
}

static gboolean
on_delete_event (GtkWidget *widget,
         GdkEvent  *event,
         gpointer   data)
{
  /* If you return FALSE in the "delete_event" signal handler,
   * GTK will emit the "destroy" signal. Returning TRUE means
   * you don't want the window to be destroyed.
   *
   * This is useful for popping up 'are you sure you want to quit?'
   * type dialogs.
   */

  g_print ("delete event occurred\n");
  gtk_main_quit();
  return TRUE;
}
gint select_click(GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data)
{
      int coord_x, coord_y, grid_x, grid_y;
      GdkModifierType state ;
      printf("Which piece do you want to move?\n");

      gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ;

      SelectCoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

      printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);

}

gint area_click (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data)
{
  int x1, y1 ;
  char words[MAX_MSGLEN] ;
  int coord_x_n, coord_y_n;
  int grid_s_x, grid_s_y;
  struct BOARD *chess_board ;
  struct SQUARE *chess_piece ;
  struct SQUARE *piece_dest ;
  int Pre_x, Pre_y, Cu_x, Cu_y;

  GdkModifierType state ;
  gdk_window_get_pointer(widget->window, &coord_x_n, &coord_y_n, &state) ;

  CoordToGrid(coord_x_n, coord_y_n, &grid_s_x, &grid_s_y);

  printf("The new selct is coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x_n, coord_y_n, grid_s_x, grid_s_y);

  Pre_x = BoardLocation[0][0];
  Pre_y = BoardLocation[0][1];
  Cu_x = BoardLocation[1][0];
  Cu_y = BoardLocation[1][1];
  GUIMove(Pre_x, Pre_y, Cu_x, Cu_y);

  //MoveTheBKing(grid_x, grid_y);


    gtk_container_remove(GTK_CONTAINER(window), fixed) ;
    table = gtk_table_new (0, 0, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();

    /*set fixed*/

    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(board_fixed), fixed) ;

    gtk_widget_show_all(window) ;

  return FALSE ;
}

gint Buttons (GtkWidget *fixed)
{

   gtk_fixed_put(GTK_FIXED(board_fixed),button1,400,50);
   //gtk_container_add (GTK_CONTAINER (window), button1);

   gtk_fixed_put(GTK_FIXED(board_fixed),button2,400,100);
   //gtk_container_add (GTK_CONTAINER (window), button2);

   gtk_fixed_put(GTK_FIXED(board_fixed),button3,400,150);
   //gtk_container_add (GTK_CONTAINER (window), button3);
}

int
main (int   argc,
      char *argv[])
{
  char str[MAX_MSGLEN];

  gtk_init(&argc, &argv) ;
  //ResetBoard();

  /*create a new window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ;
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ;
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ;
  gtk_window_set_title(GTK_WINDOW(window), "Deep Core Dumped") ;
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;

  /*Add bottoms on window*/
  button1 = gtk_button_new_with_label("Undo");
  button2 = gtk_button_new_with_label("Hint");
  button3 = gtk_button_new_with_label("Quit");

  /*register event handlers*/
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ;
  //gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ;
  gtk_widget_set_events(window,GDK_BUTTON_PRESS_MASK |GDK_BUTTON_RELEASE_MASK) ;
  g_signal_connect(window, "button_press_event", G_CALLBACK(select_click), NULL) ;
  g_signal_connect(window, "button_release_event", G_CALLBACK(area_click), NULL) ;
  g_signal_connect(G_OBJECT(button3), "delete_event_bottom", G_CALLBACK(on_delete_event), NULL) ;

  /*create a table and draw the board*/

  InitBoard();
  table = gtk_table_new (8, 8, TRUE) ;
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;

  DrawBoard();
  board_fixed = gtk_fixed_new() ;
  gtk_fixed_put(GTK_FIXED(board_fixed), table, 0, 0) ;
  gtk_container_add(GTK_CONTAINER(window), board_fixed) ;
  Buttons(board_fixed);

  fixed = gtk_fixed_new() ;
  gtk_fixed_put(GTK_FIXED(board_fixed), fixed, 0, 0) ;
  //gtk_container_add(GTK_CONTAINER(window), fixed) ;



  /*show the window*/
  gtk_widget_show_all(window) ;
  gtk_main() ;

  return 0 ;
}
