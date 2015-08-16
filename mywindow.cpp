#include "mywindow.h"

mywindow::mywindow()
{
    set_default_size(900, 700);
    set_title("Key Value Extraction");
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(20);

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &mywindow::on_quit_click));
    filemenu->append(*menuitem_quit);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);

    Gtk::TreeView *treeview = Gtk::manage(new Gtk::TreeView);
    treeview->set_hexpand(true);
    treeview->set_vexpand(true);
    grid->attach(*treeview, 0, 0, 3, 1);

    refTreeModel = Gtk::ListStore::create(columns);
    treeview->set_model(refTreeModel);
    treeview->append_column("Number", columns.col_cnt);
    treeview->append_column("Data", columns.col_text);

    label = Gtk::manage(new Gtk::Label);
    label->set_markup("<b>Enter data to cluster: </b>");
    grid->attach(*label, 0, 1, 1, 1);

    text = Gtk::manage(new Gtk::Entry);
    grid->attach(*text, 1, 1, 2, 1);

    //Gtk::Button *b1 = Gtk::manage(new Gtk::Button("Big Button 1"));
    //b1->set_hexpand(true);
    //b1->set_vexpand(true);
    //b1->signal_clicked().connect(sigc::mem_fun(*this, &mywindow::on_big_button1_click));
    //grid->attach(*b1, 0, 0, 1, 2);

    Gtk::Button *b2 = Gtk::manage(new Gtk::Button("Enter the log data"));
    b2->signal_clicked().connect(sigc::mem_fun(*this, &mywindow::on_button2_click));
    grid->attach(*b2, 2, 2, 1, 1);

    Gtk::Button *b3 = Gtk::manage(new Gtk::Button("Output"));
    b3->signal_clicked().connect(sigc::mem_fun(*this, &mywindow::on_button3_click));
    grid->attach(*b3, 2, 4, 1, 1);

    Gtk::Button *b4 = Gtk::manage(new Gtk::Button("Quit"));
    b4->signal_clicked().connect(sigc::mem_fun(*this, &mywindow::on_quit_click));
    grid->attach(*b4, 2, 6, 1, 1);


    vbox->show_all();
}

mywindow::~mywindow()
{
    //dtor
}
void mywindow::on_button_click()
{

}
void mywindow::on_big_button1_click()
{
    dialog("Big Button 1 Pressed!");
}

void mywindow::on_button2_click()
{
    
    if(text->get_text_length() == 0)
        label->set_markup("<b><span color='red'>Enter valid data </span></b>");
    else
    {

        label->set_markup("<b><span color='black'>Enter data to cluster: </span></b>");

        rowcount++;
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[columns.col_cnt] = rowcount;
        row[columns.col_text] = text->get_text();
    }
}

void mywindow::on_button3_click()
{
    dialog("Clustered Output");
}

void mywindow::on_quit_click()
{
    hide();
}

void mywindow::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Key Value Extraction");
    dlg.run();
}