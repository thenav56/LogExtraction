/*
   g++ -std=c++11 main.cpp examplewindow.cpp -o main `pkg-config --libs --cflags gtkmm-3.0`
   */

#include "../include/examplewindow.h"
#include <gtkmm/stock.h>
#include <iostream>


ExampleWindow::ExampleWindow(regex_key_value &regx)
		: m_Box(Gtk::ORIENTATION_VERTICAL),m_VBox(Gtk::ORIENTATION_VERTICAL),m_HBox(Gtk::ORIENTATION_VERTICAL),
		m_frame("Data from file :"),o_frame("Output from file :"),m_Alignment(Gtk::ALIGN_END, Gtk::ALIGN_CENTER, 1.0, 0.0)
{
		set_title("Key Value Extraction");
		set_default_size(800, 600);
		set_position(Gtk::WIN_POS_CENTER);
		add(m_Box);
		// put a MenuBar at the top of the box and other stuff below it.
		//Create actions for menus and toolbars:
		m_refActionGroup = Gtk::ActionGroup::create();
		//File|New sub menu:
		// m_refActionGroup->add(Gtk::Action::create("FileNewStandard",
		// 						Gtk::Stock::NEW, "_New", "Create a new file"),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new_generic));
		m_refActionGroup->add(Gtk::Action::create("FileNewStandard",
								Gtk::Stock::EXECUTE, "_New", "Output"),
						sigc::mem_fun(*this, &ExampleWindow::on_button_output_click));


		//file menu subgroups
		// m_refActionGroup->add(Gtk::Action::create("FileNewFoo",
		// 						Gtk::Stock::NEW, "New Foo", "Create a new foo"),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new_generic));
		// m_refActionGroup->add(Gtk::Action::create("FileNewGoo",
		// 						Gtk::Stock::NEW, "_New Goo", "Create a new goo"),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new_generic));
		//File menu:
		m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
		//Sub-menu.
		//m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));

		m_refActionGroup->add(Gtk::Action::create("FileOpen",
								Gtk::Stock::OPEN, "_Open", "Open File"),
						sigc::mem_fun(*this, &ExampleWindow::on_menu_folder_open));

		m_refActionGroup->add(Gtk::Action::create("FileSave",
								Gtk::Stock::SAVE, "_Save", "Save File"),
						sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
		// m_refActionGroup->add(Gtk::Action::create("FilePageSetup", Gtk::Stock::PRINT,"Page Setup"),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));
		// m_refActionGroup->add(Gtk::Action::create("FilePrintPreview", Gtk::Stock::PRINT, "Print Preview"),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));

		// m_refActionGroup->add(Gtk::Action::create("FilePrint",
		// 						Gtk::Stock::PRINT,"_Print","Print"),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_others));


		m_refActionGroup->add(Gtk::Action::create("FileQuit",
								Gtk::Stock::QUIT, "_Quit","Quit"),
						sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));
		//m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
		//sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));
		//Edit menu:
		// m_refActionGroup->add(Gtk::Action::create("EditMenu", "Edit"));
		// m_refActionGroup->add(Gtk::Action::create("EditCut", Gtk::Stock::CUT),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
		// m_refActionGroup->add(Gtk::Action::create("EditCopy", Gtk::Stock::COPY),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
		// m_refActionGroup->add(Gtk::Action::create("EditPaste", Gtk::Stock::PASTE),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
		// m_refActionGroup->add(Gtk::Action::create("EditUndo", Gtk::Stock::UNDO),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
		// m_refActionGroup->add(Gtk::Action::create("EditRedo", Gtk::Stock::REDO),
		// 				sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
		//
		m_refActionGroup->add( Gtk::Action::create("HelpMenu", "More") );
		m_refActionGroup->add( Gtk::Action::create("About", Gtk::Stock::ABOUT),
						sigc::mem_fun(*this, &ExampleWindow::on_menu_about) );
						m_refActionGroup->add( Gtk::Action::create("Help", Gtk::Stock::ABOUT,"_Help","Help"),
										sigc::mem_fun(*this, &ExampleWindow::on_menu_help) );
		m_refUIManager = Gtk::UIManager::create();
		m_refUIManager->insert_action_group(m_refActionGroup);
		add_accel_group(m_refUIManager->get_accel_group());


		//Layout the actions in a menubar and toolbar:
		Glib::ustring ui_info =
				"<ui>"
				" <menubar name='MenuBar'>"
				" <menu action='FileMenu'>"
				//" <menu action='FileNew'>"
				//" <menuitem action='FileNewStandard'/>"
				//" <menuitem action='FileNewFoo'/>"
				//" <menuitem action='FileNewGoo'/>"
				//" </menu>"
				" <menuitem action='FileOpen'/>"
				" <menuitem action='FileSave'/>"
				//" <menuitem action='FilePageSetup'/>"
				//" <menuitem action='FilePrintPreview'/>"
				//" <menuitem action='FilePrint'/>"
				" <menuitem action='FileQuit'/>"
				" </menu>"
				//" <menu action='EditMenu'>"
				//" <menuitem action='EditCut'/>"
				//" <menuitem action='EditCopy'/>"
				//" <menuitem action='EditPaste'/>"
				//" <menuitem action='EditUndo'/>"
				//" <menuitem action='EditRedo'/>"
				//" </menu>"
				" <menu action='HelpMenu'>"
				" <menuitem action='About'/>"
				" <menuitem action='Help'/>"
				" </menu>"
				" </menubar>"
				" <toolbar name='ToolBar'>"
				" <toolitem action='FileNewStandard'/>"
				" <separator/>"
				" <toolitem action='FileOpen'/>"
				" <separator/>"
				" <toolitem action='FileSave'/>"
				" <separator/>"
			//	" <toolitem action='FilePrint'/>"
				" <separator/>"
				" <toolitem action='FileQuit'/>"
				" </toolbar>"
				"</ui>";
		try
		{
				m_refUIManager->add_ui_from_string(ui_info);
		}
		catch(const Glib::Error& ex)
		{
				std::cerr << "building menus failed: " << ex.what();
		}
		//Get the menubar and toolbar widgets, and add them to a container widget:
		Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
		if(pMenubar)
				m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);
		Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
		if(pToolbar)
				m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
		show_all_children();
		//add the grid for the treeview and button
		//Add the Notebook, with the button underneath:
		m_Notebook.set_border_width(10);
		m_Box.pack_start(m_Notebook);
		m_Box.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
		//m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
		//m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_quit_click) );
		//Add the Notebook pages:
		m_Notebook.append_page(m_grid, "Regex");
		m_Notebook.append_page(m_grid2, "Log File");
		m_Notebook.append_page(m_grid3, "Output");
		m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this, &ExampleWindow::on_notebook_switch_page) );


		add(m_grid);

		m_grid.set_border_width(20);
		m_grid.set_row_spacing(5);
		m_Box.add(m_grid);


		Gtk::TreeView *treeview = Gtk::manage(new Gtk::TreeView);
		treeview->set_hexpand(true);
		treeview->set_vexpand(true);
		//treeview->get_selection()->set_mode(Gtk::SELECTION_MULTIPLE) ;
		treeview->set_search_column(columns.col_cnt) ;
		treeview_ScrolledWindow.add(*treeview)  ;
		//Only show the scrollbars when they are necessary:
		treeview_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		m_grid.attach(treeview_ScrolledWindow, 0, 0, 3, 1);

		refTreeModel = Gtk::ListStore::create(columns);

		treeview->set_model(refTreeModel);
		treeview->append_column("S.N", columns.col_cnt);
		treeview->append_column("Datatype", columns.col_text);
		treeview->append_column("Regex Data", columns.col_text2);

		label = Gtk::manage(new Gtk::Label);
		label2 = Gtk::manage(new Gtk::Label);
		label->set_markup("<b><span color='black'>Enter Datatype: </span></b>");
		label2->set_markup("<b><span color='black'>Enter Regex Data: </span></b>");
		m_grid.attach(*label, 0, 1, 1, 1);
		m_grid.attach(*label2, 0, 2, 1, 1);

		text = Gtk::manage(new Gtk::Entry);
		m_grid.attach(*text, 1, 1, 2, 1);
		text2 = Gtk::manage(new Gtk::Entry);
		m_grid.attach(*text2, 1, 2, 2, 3);

		Gtk::Button *b_add = Gtk::manage(new Gtk::Button("Click to add"));
		b_add->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_add_data_click));
		m_grid.attach(*b_add, 2, 8, 1, 1);

		Gtk::Button *b_remove = Gtk::manage(new Gtk::Button("Click to remove"));
		b_remove->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_delete_data_click));
		//m_grid.attach(*b_remove, 2, 10, 1, 1);

		// Gtk::Button *b_output = Gtk::manage(new Gtk::Button("Press here for output"));
		// b_output->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_output_click));
		// m_grid.attach(*b_output, 2, 10, 1, 1);


		m_grid.show_all();




		add(m_grid2);

		m_grid2.set_border_width(20);
		m_grid2.set_row_spacing(5);
		m_Box.add(m_grid2);


		label3 = Gtk::manage(new Gtk::Label);
		label3->set_markup("<b><span color='black'>Open a text file: </span></b>");
		m_grid2.attach(*label3, 0, 1, 1, 1);
		text3 = Gtk::manage(new Gtk::Entry);
		m_grid2.attach(*text3, 10, 1, 1, 1);
		Gtk::Button *b_addfile = Gtk::manage(new Gtk::Button("Browse"));
		b_addfile->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_menu_folder_open));
		m_grid2.attach(*b_addfile, 15, 1, 1, 1);

		//m_Entry.set_max_length(50);
		//label2->set_markup("<b><span color='black'>Text file data: </span></b>");
		//m_grid2.attach(*label4, 1, 2, 1, 1);

		add(m_HBox);
		add(m_Alignment);
		m_HBox.pack_start(m_VBox);
		//m_frame.add(m_Label_Normal);
		m_grid2.attach(m_frame, 0,5,200,100);
		//label4 = Gtk::manage(new Gtk::Label);
		//label4->set_markup("<b><span color='black'>The data from text file will appear here. </span></b>");
		//m_Entry.set_text("The data from text file");
		//m_Entry.set_text(m_Entry.get_text() + " will appear here.");
		//m_Entry.select_region(0, m_Entry.get_text_length());
		//m_grid2.attach(m_Entry, 10, 10, 100, 10);
		//m_frame.add(*label4);
		editor = Gtk::manage(new Gtk::TextView) ;
		editor_buffer = Gtk::TextBuffer::create() ;
		editor->set_buffer(editor_buffer) ;
		editor->set_cursor_visible(true) ;
		editor_ScrolledWindow.add(*editor)  ;
		//Only show the scrollbars when they are necessary:
		editor_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		m_frame.add(editor_ScrolledWindow) ;
		m_frame.set_hexpand(true);
		m_frame.set_vexpand(true);
		// Gtk::Button *m_Button = Gtk::manage(new Gtk::Button("Output"));
		// m_Button->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_output_click));
		//m_frame.set_label_align(Gtk::ALIGN_END, Gtk::ALIGN_START);
		//m_grid2.attach(*m_Button,40,1,20,1);
		//m_Alignment.add(*m_Button);
		m_frame.add(m_Alignment);
		m_frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
		m_Alignment.show_all();
		m_HBox.show_all();



		m_grid2.show_all();

		//-----------------------------------------------------------------------------------
		add(m_grid3);

		m_grid3.set_border_width(20);
		m_grid3.set_row_spacing(5);
		m_Box.add(m_grid3);

		add(m_HBox);
		add(o_Alignment);
		m_HBox.pack_start(m_VBox);
		m_grid3.attach(o_frame, 0,5,200,100);

		_output = Gtk::manage(new Gtk::TextView) ;
		_output_buffer = Gtk::TextBuffer::create() ;
		_output->set_buffer(_output_buffer) ;
		_output->set_cursor_visible(true) ;
		_output_ScrolledWindow.add(*_output)  ;
		//Only show the scrollbars when they are necessary:
		_output_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		o_frame.add(_output_ScrolledWindow) ;
		o_frame.set_hexpand(true);
		o_frame.set_vexpand(true);
		Gtk::Button *analyse_Button = Gtk::manage(new Gtk::Button("Analyse"));
		analyse_Button->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_analyse_click));
		//o_frame.set_label_align(Gtk::ALIGN_START,Gtk::ALIGN_END);
		//attach (Widget& child, int left, int top, int width, int height)
		m_grid3.attach(*analyse_Button,100,110,100,1);
		o_Alignment.add(*analyse_Button);
		o_frame.add(o_Alignment);
		o_frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
		o_Alignment.show_all();
		m_HBox.show_all();



		m_grid3.show_all();

		//---------------------------------------------------------------------------------------------
		reg = &regx  ;
		//reg->readFromFile("regex.tl") ;
		show_all_children();
      rowcount = 0 ;
      for(; rowcount < reg->get_regex_count();rowcount++){
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[columns.col_cnt] = rowcount;
        row[columns.col_text] = reg->gettype(rowcount);
        row[columns.col_text2] = reg->getRegex(rowcount);
    }


}


//destructor
ExampleWindow::~ExampleWindow()
{
}


void ExampleWindow::on_menu_file_quit()
{
		hide(); //Closes the main window to stop the Gtk::Main::run().
}

//when file -> open in clicked in menubar

/*void ExampleWindow::on_menu_file_open()
  {
  Gtk::FileChooserDialog dialog("Please choose a folder",
  Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
  dialog.set_transient_for(*this);
//Add response buttons the the dialog:
dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
dialog.add_button("Select", Gtk::RESPONSE_OK);
int result = dialog.run();
//Handle the response:
switch(result)
{
case(Gtk::RESPONSE_OK):
{
std::cout << "Select clicked." << std::endl;
std::cout << "Folder selected: " << dialog.get_filename()
<< std::endl;
break;
}
case(Gtk::RESPONSE_CANCEL):
{
std::cout << "Cancel clicked." << std::endl;
break;
}
default:
{
std::cout << "Unexpected button clicked." << std::endl;
break;
}
}
}
*/
//open browsing view when open is clicked in menubar
void ExampleWindow::on_menu_folder_open()
{
		Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
		dialog.set_transient_for(*this);
		//Add response buttons the the dialog:
		dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
		//Add filters, so that only certain file types can be selected:
		Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
		filter_text->set_name("Text files");
		filter_text->add_mime_type("text/plain");
		dialog.add_filter(filter_text);
		Glib::RefPtr<Gtk::FileFilter> filter_cpp = Gtk::FileFilter::create();
		filter_cpp->set_name("C/C++ files");
		filter_cpp->add_mime_type("text/x-c");
		filter_cpp->add_mime_type("text/x-c++");
		filter_cpp->add_mime_type("text/x-c-header");
		dialog.add_filter(filter_cpp);
		Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
		filter_any->set_name("Any files");
		filter_any->add_pattern("*");
		dialog.add_filter(filter_any);
		//Show the dialog and wait for a user response:
		int result = dialog.run();
		//Handle the response:
		switch(result)
		{
				case(Gtk::RESPONSE_OK):
						{
								std::cout << "Open clicked." << std::endl;
								//Notice that this is a std::string, not a Glib::ustring.
								std::string filename = dialog.get_filename();
								std::cout << "File selected: " << filename << std::endl;
								std::ifstream file_load(filename.c_str());
								if(file_load.is_open()){
										std::string _temp ;
										Glib::ustring file_text = "" ;
										while(std::getline(file_load,_temp)){
												file_text += _temp+'\n' ;
										}
										editor_buffer->set_text(file_text) ;
										m_Notebook.set_current_page(1);
								}
								break;
						}
				case(Gtk::RESPONSE_CANCEL):
						{
								std::cout << "Cancel clicked." << std::endl;
								break;
						}
				default:
						{
								std::cout << "Unexpected button clicked." << std::endl;
								break;
						}
		}
}

void ExampleWindow::on_menu_file_new_generic()
{
		std::cout << "A File|New menu item was selected." << std::endl;
}
void ExampleWindow::on_menu_others()
{

		std::cout << "A menu item was selected." << std::endl;
}

void ExampleWindow::on_button_delete_data_click(){
	auto path = treeview->get_selection()->get_selected();
	//auto iter = refTreeModel->get_iter(path) ;
	//refTreeModel->erase(iter) ;
	// if(iter){  //If anything is selected
	// 	Gtk::TreeModel::Row row = *iter;
	// 	//row.remove();
	// 	}


}

void ExampleWindow::on_button_add_data_click()
{

		if(text->get_text_length() == 0 or text2->get_text_length() == 0){
				dialog("ERROR:: Enter valid data",Gtk::MESSAGE_WARNING);
				label->set_markup("<b><span color='red'>Enter Datatype: </span></b>");
				label2->set_markup("<b><span color='red'>Enter Regex Data: </span></b>");
		}else
		{

				label->set_markup("<b><span color='black'>Enter Datatype: </span></b>");
				label2->set_markup("<b><span color='black'>Enter Regex Data: </span></b>");



				Gtk::TreeModel::Row row = *(refTreeModel->append());
				row[columns.col_cnt] = rowcount;
				row[columns.col_text] = text->get_text();
				row[columns.col_text2] = text2->get_text();

        rowcount++;
				std::cout<<text->get_text()<<text2->get_text()<<std::endl ;
				reg->add(text->get_text(),text2->get_text() ) ;
		}
}

void ExampleWindow::on_button_output_click()
{
		//dialog("Clustered Output");
		std::string file_text = "THe Output Should Be Here" ;
		_output_buffer->set_text(file_text) ;
		std::string _editor_buffer = editor_buffer->get_text() ;
		std::ofstream out(".temp_log_file");
		out<<_editor_buffer ;
		out.close() ;
		//run the program here
		// char *arg[] = {"programname","untagged","tagged",".temp_log_file"} ;
		// main_run(arg) ;
		std::string filename = "regex.tl" ;
		std::ifstream file_load(filename.c_str());
		if(file_load.is_open()){
				std::string _temp ;
				Glib::ustring file_text = "" ;
				while(std::getline(file_load,_temp)){
						file_text += _temp+'\n' ;
				}
				_output_buffer->set_text(file_text) ;
		}
		m_Notebook.set_current_page(2);
}
void ExampleWindow::on_quit_click()
{
		hide();
}

void ExampleWindow::on_menu_help(){

}

void ExampleWindow::on_menu_about(){
		dialog("Log Extraction(IOE MINOR PROJECT)\n\tDeveloped By\n\tUttam Khanal\n\tPrabesh Pathak\n\tPramod Maharjan\n\tNavin Ayer",Gtk::MESSAGE_INFO) ;
}

void ExampleWindow::on_button_analyse_click(){
	Glib::ustring msg = "This is the Analysed Information Brother" ;
	Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
	dlg.set_title("Output");
	dlg.run();
}

void ExampleWindow::dialog(Glib::ustring msg, Gtk::MessageType type = Gtk::MESSAGE_INFO ){
		Gtk::MessageDialog dlg(msg, false, type, Gtk::BUTTONS_OK, true);
		dlg.set_title("Output");
		dlg.run();
}

void ExampleWindow::on_notebook_switch_page(Gtk::Widget* /* page */, int page_num)
{
		std::cout << "Switched to tab with index " << page_num << std::endl;
		//You can also use m_Notebook.get_current_page() to get this index.
}
