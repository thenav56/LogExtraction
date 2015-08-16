#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <gtkmm.h>

class mywindow : public Gtk::Window
{
    public:
        mywindow();
        virtual ~mywindow();
        Gtk::TreeView *treeview;
        Gtk::Label *label;
        Gtk::Entry *text;
        
    protected:
        void on_big_button1_click();
        void on_button2_click();
        void on_button3_click();
        void on_button4_click();
        void on_quit_click();
        void on_button_click();
        void dialog(Glib::ustring msg);
        class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumns()
                { add(col_cnt); add(col_text); }

                Gtk::TreeModelColumn<int> col_cnt;
                Gtk::TreeModelColumn<Glib::ustring> col_text;
        };

        ModelColumns columns;
        Glib::RefPtr<Gtk::ListStore> refTreeModel;
        int rowcount = 0;
    private:
};
#endif // MYWINDOW_H