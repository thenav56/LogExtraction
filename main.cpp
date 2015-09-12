#include "examplewindow.h"
#include <gtkmm/main.h>
#include "regex_key_value.h"

//global variable
int main(int argc, char *argv[])
{
		Gtk::Main kit(argc, argv);
		ExampleWindow window;
		//Shows the window and returns when it is closed.
		Gtk::Main::run(window);
		return 0;
}
