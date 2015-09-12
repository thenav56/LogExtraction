#include "examplewindow.h"
#include <gtkmm/main.h>
#include "regex_key_value.h"

//global variable
regex_key_value reg ;
int main(int argc, char *argv[])
{
		reg.readFromFile("regex.tl") ;
		Gtk::Main kit(argc, argv);
		ExampleWindow window(reg);
		//Shows the window and returns when it is closed.
		Gtk::Main::run(window);
		return 0;
}
