#ifndef GTKMM_ExampleWindow_H
#define GTKMM_ExampleWindow_H
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <fstream>
#include "regex_key_value.h"
class ExampleWindow : public Gtk::Window
{
public:
 ExampleWindow(regex_key_value reg);
 virtual ~ExampleWindow();
 Gtk::TreeView *treeview;
 Gtk::Label *label,*label2, *label3, *label4,m_Label_Normal;
 Gtk::TextView *editor ;
 Glib::RefPtr<Gtk::TextBuffer> editor_buffer ;
 Gtk::ScrolledWindow editor_ScrolledWindow , treeview_ScrolledWindow;
 Gtk::Entry m_Entry,*text,*text2,*text3, get_text;
 Gtk::Grid m_grid,m_grid2;
 Gtk::Frame m_frame;
 Gtk::Alignment m_Alignment;
protected:
 //Signal handlers:
 void on_menu_file_new_generic();
 void on_menu_file_quit();
 void on_menu_file_open();
 void on_menu_folder_open();
 void on_menu_file_page_setup();
 void on_menu_file_print_preview();
 void on_menu_file_print();
 void on_menu_others();
 void on_menu_choices_one();
 void on_menu_choices_two();
 void on_menu_file_new();
 void on_button_addfile_click();
 void on_button_enterhere_click();
 void on_button_output_click();
 void on_button_add_data_click();
 void on_quit_click();
 void on_output_from_file();
 void dialog(Glib::ustring msg);
 void on_notebook_switch_page(Gtk::Widget* page, int page_num);
 //Printing-related objects:
class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumns()
                { add(col_cnt); add(col_text); add(col_text2);}

                Gtk::TreeModelColumn<int> col_cnt;
                Gtk::TreeModelColumn<Glib::ustring> col_text;
                Gtk::TreeModelColumn<Glib::ustring> col_text2;
        };

        ModelColumns columns;
        Glib::RefPtr<Gtk::ListStore> refTreeModel;
        int rowcount = 0;

 //Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
 //Glib::RefPtr<Gtk::PrintSettings> m_refSettings;
 //Gtk::Box m_VBox;
 Gtk::Table m_Table;
 Gtk::Label m_NameLabel;
 Gtk::Entry m_NameEntry;
 Gtk::Label m_SurnameLabel;
 Gtk::Entry m_SurnameEntry;
 Gtk::Label m_CommentsLabel;
 Gtk::ScrolledWindow m_ScrolledWindow;
 Gtk::TextView m_TextView;

 Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
 unsigned m_ContextId;
 Gtk::Statusbar m_Statusbar;

 //Child widgets:
 Gtk::Menu m_Menu_Popup;
 Gtk::Notebook m_Notebook;
 Gtk::Button m_Button;
 Gtk::ButtonBox m_ButtonBox;
 Gtk::Box m_Box,m_VBox,m_HBox;
 Glib::RefPtr<Gtk::UIManager> m_refUIManager;
 Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
 Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;
};
#endif //GTKMM_ExampleWindow_H
