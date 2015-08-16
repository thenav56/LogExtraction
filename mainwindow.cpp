#include <gtkmm.h>
#include "mywindow.h"

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

    mywindow window;

    return app->run(window);
}