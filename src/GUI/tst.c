#include <gtk/gtk.h>

void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{
	gtk_widget_set_app_paintable(widget, TRUE);		//允许窗口可以绘图
	gtk_widget_realize(widget);	
 
	/* 更改背景图时，图片会重叠
 * 	 * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
 * 	 	 */
	gtk_widget_queue_draw(widget);
 
	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);	// 创建图片资源对象
	// w, h是指定图片的宽度和高度
	 	GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);
	// 	 
		 	GdkPixmap *pixmap = NULL;
	// 	 	 
	// 
	 	gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
	 	 	 		 	 	 		// 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
	 	gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
	 	 	 		 	 	 			 
	 	 	 		 	 	 			 	// 释放资源
	 	g_object_unref(src_pixbuf);
	 	g_object_unref(dst_pixbuf);
		g_object_unref(pixmap);
	 	 	 		 	 	 			}
	
	
 int main(int argc,char *argv[])
 {
    

    gtk_init (&argc, &argv); 	// 初始化
 
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
	gtk_window_set_title(GTK_WINDOW(window), "Chess");
	gtk_widget_set_size_request(window, 500, 450);
 
	chang_background(window, 500, 400, "bg.jpg");
 	 // 创建窗口 
 
	GtkWidget *fixed = gtk_fixed_new(); 	//创建一个固定容器
	gtk_container_add(GTK_CONTAINER (window), fixed); // 固定放进窗口
 
	GtkWidget *button1 = gtk_button_new_with_label("Player 2");  // 创建按钮
	gtk_fixed_put(GTK_FIXED(fixed), button1, 0, 0); // 按钮添加到固定布局
	
	GtkWidget *button2 = gtk_button_new_with_label("Player 1");  // 创建按钮
	gtk_fixed_put(GTK_FIXED(fixed), button2, 0, 0); // 按钮添加到固定布局
	
	gtk_fixed_move(GTK_FIXED(fixed), button1, 90, 310); // 移动控件的位置
	gtk_fixed_move(GTK_FIXED(fixed), button2, 300, 310);
	gtk_widget_set_size_request(button1, 100, 50);
	gtk_widget_set_size_request(button2, 100, 50);



    gtk_widget_show_all(window);

    gtk_main();

    return 0;
 }

