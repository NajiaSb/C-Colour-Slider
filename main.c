#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *window;
int red = 0, green = 0, blue = 0;

void changeColour(GtkWidget *window)
{
    FILE *fptr = fopen("mystyle.css", "w");
    fprintf(fptr, "#backWin{background-color: rgb(%d,%d,%d);}", red, green, blue);
    fclose(fptr);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_widget_set_name(GTK_WIDGET(window), "backWin");
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("mystyle.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void getRedValue(GtkWidget *widget, gpointer data)
{
    red = gtk_range_get_value(GTK_RANGE(widget)); // get red value
    changeColour(window);
}
void getGreenValue(GtkWidget *widget, gpointer data)
{
    green = gtk_range_get_value(GTK_RANGE(widget)); // get green value
    changeColour(window);
}
void getBlueValue(GtkWidget *widget, gpointer data)
{
    blue = gtk_range_get_value(GTK_RANGE(widget)); // get blue value
    changeColour(window);
}
void openSlider(GtkWidget *widget, gpointer data)
{
    GtkWidget *redSlider, *blueSlider, *greenSlider, *redLabel, *blueLabel, *greenLabel;
    GtkWidget *childWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); // create widget
    gtk_window_set_resizable(GTK_WINDOW(childWindow), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(childWindow), 320, 170);
    gtk_window_set_title(GTK_WINDOW(childWindow), "Slider Window");
    // create sliders
    redSlider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 255.0, 1.0);
    greenSlider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 255.0, 1.0);
    blueSlider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 255.0, 1.0);
    redLabel = gtk_label_new("Red");
    blueLabel = gtk_label_new("Blue");
    greenLabel = gtk_label_new("Green");
    // set slider size
    g_object_set(redSlider, "width-request", 270, NULL);
    g_object_set(greenSlider, "width-request", 270, NULL);
    g_object_set(blueSlider, "width-request", 270, NULL);
    // create layout to place sliders
    GtkWidget *childLayout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(childWindow), childLayout); // add layout to window
    // add sliders to layout
    gtk_layout_put(GTK_LAYOUT(childLayout), redLabel, 5, 45);
    gtk_layout_put(GTK_LAYOUT(childLayout), greenLabel, 5, 95);
    gtk_layout_put(GTK_LAYOUT(childLayout), blueLabel, 5, 145);
    gtk_layout_put(GTK_LAYOUT(childLayout), redSlider, 40, 25);
    gtk_layout_put(GTK_LAYOUT(childLayout), greenSlider, 40, 75);
    gtk_layout_put(GTK_LAYOUT(childLayout), blueSlider, 40, 125);
    // signal handlers
    g_signal_connect(redSlider, "value-changed", G_CALLBACK(getRedValue), NULL);
    g_signal_connect(greenSlider, "value-changed", G_CALLBACK(getGreenValue), NULL);
    g_signal_connect(blueSlider, "value-changed", G_CALLBACK(getBlueValue), NULL);

    gtk_widget_show_all(childWindow);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv); // initialize GTK

    GtkWidget *sliderButton;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);                    // create widget
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // center widget
    gtk_window_set_title(GTK_WINDOW(window), "Colour Slider");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // callback to quit

    sliderButton = gtk_button_new_with_label("Open Slider");

    // create layout to place sliders
    GtkWidget *layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), layout); // add layout to window
    // add button to layout
    gtk_layout_put(GTK_LAYOUT(layout), sliderButton, 100, 20);

    // signal handler for sliders
    g_signal_connect(sliderButton, "clicked", G_CALLBACK(openSlider), NULL); // callback to quit

    changeColour(window); // display current colour

    gtk_widget_show_all(window); // show window
    gtk_main();
    return 0;
}