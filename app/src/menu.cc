#include "menu.h"
#include <stdlib.h>
<<<<<<< HEAD
=======
#include <ctime>
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40

Menu::Menu() {
	parser.lex("CREATE TABLE posts (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("INSERT INTO posts VALUES FROM (\"Test1\", \"Kade\", \"Does the app work? Does view work?\", \"testing, app, view\", \"yes\", \"(3/8/15)\");");
	parser.program();
	parser.lex("INSERT INTO posts VALUES FROM (\"The app\", \"Admin\", \"Testing edit content and tags\", \"testing, content\", \"no\", \"(3/8/15)\");");
	parser.program();
	parser.lex("INSERT INTO posts VALUES FROM (\"Test2\", \"Kade\", \"renaming test\", \"testing, app, rename\", \"yes\", \"(3/8/15)\");");
	parser.program();
	parser.lex("WRITE posts;");
	parser.program();
	parser.lex("CREATE TABLE editpost (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("CREATE TABLE holdpost (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();

	
	parser.lex("CREATE TABLE testone (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("CREATE TABLE testtwo (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("CREATE TABLE testthree (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("CREATE TABLE testfour (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("CREATE TABLE testfive (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	
	parser.lex("CREATE TABLE authorresult (title VARCHAR(50), date VARCHAR(20)) PRIMARY KEY (title, date);");
	parser.program();
	parser.lex("CREATE TABLE titleresult (author VARCHAR(50), date VARCHAR(20)) PRIMARY KEY (author, date);");
	parser.program();
	parser.lex("CREATE TABLE tagsresult (title VARCHAR(50), author VARCHAR(50)) PRIMARY KEY (title, author);");
	parser.program();
	parser.lex("CREATE TABLE dateresult (title VARCHAR(50), author VARCHAR(50)) PRIMARY KEY (title, author);");
	parser.program();
	}
void Menu::exit() {
	
	parser.lex("WRITE posts;");
	parser.program();
	parser.lex("EXIT;");
	parser.program();
	std::cout << "Goodbye.";
	std::exit(EXIT_SUCCESS);
	
	//exit main menu
}

void Menu::print_menu() {
	int selection_input = 0;
	//Menu Dialogue 
	std::cout << "\n[Main Menu]\n\n";
	std::cout << "1. Make a new post.\n";
	std::cout << "2. Search for a post.\n";
	std::cout << "3. Exit.\n\n";
	std::cout << "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	//Choice selection
	switch(selection_input) {
		case 1: make_post(); 
				break;
		case 2: search_menu(); 
				break;
		case 3: exit();
				break;
		default: 
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-3.\n"; 
			 print_menu();
	}
}

//search menu
void Menu::search_menu() {
	std::string str_input = "" ;
	std::string post;
	int selection_input = 0;
	//Search Menu Dialogue
<<<<<<< HEAD
	std::cout << "[Search Menu]\n\n";
=======
	std::cout << "\n[Search Menu]\n\n";
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
	std::cout << "Search by:\n";
	std::cout << "1. Author\n"; 
	std::cout << "2. Title\n"; 
	std::cout << "3. Tag(s)\n";
	std::cout << "4. Date\n";
	std::cout << "5. Return to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			case 1: 
					std::cout << "* Enter Author: ";
					std::getline(std::cin >> ws,str_input);
					post = search_by_author(str_input);
					post_manage_system(post);
					break;
			case 2: std::cout << "* Enter Title: "; 
					std::getline(std::cin >> ws,str_input);
					post = search_by_title(str_input);
					post_manage_system(post);
					break;
			case 3: std::cout << "* Enter Tag(s): "; 
					std::getline(std::cin >> ws,str_input);
					std::cout << "\n" << str_input << "\n";
					post = search_by_tags(str_input);
					post_manage_system(post);
					break;
			case 4: std::cout << "* Enter Date: "; 
					std::getline(std::cin >> ws,str_input);
					post = search_by_dates(str_input);
					post_manage_system(post);
					break;
			case 5: print_menu();
					break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-5.\n"; 
					search_menu();
	}
}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::edit_menu(std::string str_input) {
	int selection_input = 0;
<<<<<<< HEAD
	//Edit Menu Dialogue
	//TODO std::cout << "["<< relation.title() <<"'s Edit Menu]\n\n"; 
=======
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	//Edit Menu Dialogue	
	std::cout << "["<< title <<"'s Edit Menu]\n\n"; 
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
	std::cout << "[Edit Menu]\n\n";
	std::cout << "1. Author\n"; 
	std::cout << "2. Title\n"; 
	std::cout << "3. Tag(s)\n";
	std::cout << "4. Content\n";
	std::cout << "5. Comments\n";
	std::cout << "6. Return to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			
			case 1: edit_author(str_input); print_menu(); break;
			case 2: edit_title(str_input); print_menu(); break;
			case 3: edit_tags(str_input); print_menu(); break;
			case 4: edit_content(str_input); print_menu(); break;
			case 5: edit_comments(str_input); print_menu(); break;
			case 6: print_menu(); break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-6.\n"; 
					edit_menu(str_input);
	}
}


//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::post_manage_system(std::string str_input) {
	int selection_input;
<<<<<<< HEAD
	// Post's Management System Dialogue
	std::string tablename = str_input;
	tablename += ".db";
	std::vector<std::string> row = get_entries(tablename);
	// Title of post.
	std::cout << "["+ row[0] +"]\n\n";
=======
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	// Post's Management System Dialogue
	std::cout << "["+ title +"]\n\n";
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
	std::cout << "1. View\n"; 
	std::cout << "2. Edit\n"; 
	std::cout << "3. Delete\n";
	std::cout << "4. Comment\n";
	std::cout << "5. Return to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			case 1: view_post(str_input);
					post_manage_system(str_input);
			case 2: edit_menu(str_input); break;
			case 3: remove_row(str_input);
					print_menu();
					break;
			case 4: comments_menu(str_input);
					break;
			case 5: print_menu();
					break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-5.\n"; 
					post_manage_system(str_input);
					
	}
}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::comments_menu(std::string str_input) {

	int selection_input;
<<<<<<< HEAD
	//Comment System Dialogue
	//TODO std::cout << "[Commenting on "<< relation.title() <<"]\n\n";
	std::cout << "[]\n\n";
=======
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	//Comment System Dialogue
	std::cout << "[Commenting on "<< title <<"]\n\n";
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
	std::cout << "1. Comment on post\n";
	std::cout << "2. Comment on comment\n\n";
	std::cout << "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
<<<<<<< HEAD
		case 1: comment_on_post(str_input); //relation
				break;
		case 2: comment_on_comment(str_input); //relation
=======
		case 1: comment_on_post(str_input);
				break;
		case 2: comment_on_comment(str_input);
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
				break;
		default: 
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-2."; 
			 comments_menu(str_input);
	}

}

<<<<<<< HEAD
//probably this will be passed the equivalent of a relation on group 16s DMS
=======
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
void Menu::comment_on_post(std::string str_input) {
	std::string name;
	std::string comment;
	std::cout << "* Enter name: ";
	std::getline(std::cin >> ws,name);
	cout << "\n";
	std::cout << "* Enter comment: ";
	std::getline(std::cin >> ws,comment);
	//TODO do command on relation
	std::cout << "\nComment added.";
	post_manage_system(str_input);
}

<<<<<<< HEAD
//probably this will be passed the equivalent of a relation on group 16s DMS
=======
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
void Menu::comment_on_comment(std::string str_input) {
	int ID;
	std::string name;
	std::string comment;
	std::cout << "* Enter ID: ";
	std::cin >> ID;
	std::cout << "\n";
	std::cout << "* Enter name: ";
	std::getline(std::cin >> ws,name);
	cout << "\n";
	std::cout << "* Enter comment: ";
	std::getline(std::cin >> ws,comment);
	// USE ID to select the correct comment to comment on.
	//TODO do command on relation
	std::cout << "\nComment added.";
	post_manage_system(str_input);
}

void Menu::view_post(std::string str_input) {
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string author = row[1].erase(row[1].size()-1);
	author = author.erase(0,1);
	std::string content = row[2].erase(row[2].size()-1);
	content = content.erase(0,1);
	std::string tags = row[3].erase(row[3].size()-1);
	tags = tags.erase(0,1);
	std::string comment = row[4].erase(row[4].size()-1);
	comment = comment.erase(0,1);
	std::string date = row[5].erase(row[5].size()-1);
	date = date.erase(0,1);
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << "By: " << author << std::endl;
	std::cout << "Date: " << date << std::endl;
	std::cout << "Content: " << content << std::endl;
	std::cout << "Tags: " << tags << std::endl;
	//Probably should make a vector with tablename and store comments.
	std::cout << "Comment: " << comment << std::endl;
	std::cout << "--------------------------------------------------------------------------------";
}

<<<<<<< HEAD
std::string Menu::make_post() {
	std::string post;
	std::cout << "New post: " << std::endl;
	std::getline(std::cin >> ws, post);
	return post;
=======
void Menu::make_post() {
	std::string author;
	std::string content;
	std::string tags;
	std::string title;
	std::string commenting;
	int selection_input;
	time_t currentTime;
	struct tm *localTime;
	time( &currentTime );
	localTime = localtime( &currentTime );
	int day    = localTime->tm_mday;
	int month  = localTime->tm_mon + 1;
	int year   = localTime->tm_year + 1900;
	std::string date = "("+std::to_string(month)+"/"+std::to_string(day)+"/"+std::to_string(year)+")";
	
	std::cout << "\n[New post]\n" << std::endl;
	std::cout << "* Title: ";
	std::getline(std::cin >> ws,title);
	std::cout << "\n";
	std::cout << "* Author: ";
	std::getline(std::cin >> ws,author);
	std::cout << "\n";
	std::cout << "* Content: ";
	std::getline(std::cin >> ws,content);
	std::cout << "\n";
	std::cout << "* Tags: ";
	std::getline(std::cin >> ws,tags);
	std::cout << "\n";
	std::cout << "[Allow Commenting?]\n\n";
	std::cout << "1. Yes\n";
	std::cout << "2. No\n\n";
	std::cout << "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
		case 1: commenting = "yes";
				break;
		case 2: commenting = "no"; 
				break;
		default: 
			 std::cout <<"Defaulting to no.\n"; 
			 commenting = "no";
	}
	
	parser.lex("INSERT INTO posts VALUES FROM (\""+title+"\", \""+ author +"\", \""+ content +"\", \""+ tags +"\", \""+ commenting +"\", \""+date+"\");");
	parser.program(); 
	parser.lex("WRITE posts;");
	parser.program(); 
	print_menu();
>>>>>>> 2a6cc466fcd67230fc8da01d2ca33864c4643b40
}

std::string Menu::search_by_author(std::string str_input) {
	std::string query = "answer <- select (author == \"" + str_input +"\") posts;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE answer;");
	parser.program();
	parser.lex("INSERT INTO authorresult VALUES FROM RELATION project (title, date) answer;");
	parser.program();
	parser.lex("WRITE authorresult;");
	parser.program();
	std::cout << "[" << str_input << "'s Posts]\n";
	std::vector<std::string> result = search_options("authorresult.db");
	query = "result <- select (title == " + result[0] + " && date == "+ result[1] +") answer;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE result;");
	parser.program();
	parser.lex("INSERT INTO holdpost VALUES FROM RELATION project (title, author, content, tags, commenting, date) result;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	delete_searching_tables();
	
	return "holdpost";
}

std::string Menu::search_by_title(std::string str_input) {
	std::string query = "answer <- select (title == \"" + str_input +"\") posts;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE answer;");
	parser.program();
	parser.lex("INSERT INTO titleresult VALUES FROM RELATION project (author, date) answer;");
	parser.program();
	parser.lex("WRITE titleresult;");
	parser.program();
	std::cout << "[Posts by Title: " << str_input << "]\n";	
	std::vector<std::string> result = search_options("titleresult.db");
	query = "result <- select (author == " + result[0] + " && date == "+ result[1] +") answer;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE result;");
	parser.program();
	parser.lex("INSERT INTO holdpost VALUES FROM RELATION project (title, author, content, tags, commenting, date) result;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	delete_searching_tables();
	
	return "holdpost";
}


std::string Menu::search_by_tags(std::string str_input) {
	std::string query = "answer <- select ( tags == \"" + str_input +"\") posts;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE answer;");
	parser.program();
	parser.lex("INSERT INTO tagsresult VALUES FROM RELATION project (title, author) answer;");
	parser.program();
	parser.lex("WRITE tagsresult;");
	parser.program();
	std::cout << "[Posts with Tags: " << str_input << "]\n";
	std::vector<std::string> result = search_options("tagsresult.db");
	query = "result <- select (title == " + result[0] + " && author == "+ result[1] +") answer;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE result;");
	parser.program();
	parser.lex("INSERT INTO holdpost VALUES FROM RELATION project (title, author, content, tags, commenting, date) result;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	delete_searching_tables();
	
	
	return "holdpost";
}


std::string Menu::search_by_dates(std::string str_input) {
	std::string query = "answer <- select ( date == \"" + str_input +"\") posts;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE answer;");
	parser.program();
	parser.lex("INSERT INTO dateresult VALUES FROM RELATION project (title, author) answer;");
	parser.program();
	parser.lex("WRITE dateresult;");
	parser.program();
	std::cout << "[Posts on: " << str_input << "]\n";
	std::vector<std::string> result = search_options("dateresult.db");
	query = "result <- select (title == " + result[0] + " && author == "+ result[1] +") answer;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE result;");
	parser.program();
	parser.lex("INSERT INTO holdpost VALUES FROM RELATION project (title, author, content, tags, commenting, date) result;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	delete_searching_tables();
	
	
	return "holdpost";
}

void Menu::edit_author(std::string str_input) {	
	
	parser.lex("INSERT INTO editpost VALUES FROM RELATION project (title, author, content, tags, commenting, date) "+str_input+";");
	parser.program();
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	std::string author = row[1].erase(row[1].size()-1);
	author = author.erase(0,1);
	std::string new_author;
	
	std::cout << "[Editing "<< title <<"'s Author]\n\n";
	std::cout << "Current Author: "<< author <<"\n\n";
	std::cout << "* Enter new Author: ";
	std::getline(std::cin >> ws, new_author);
	std::cout << "\n";
	std::string query = "UPDATE editpost SET author == \"" + new_author + "\" WHERE (author == \""+author+"\");";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE editpost;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	parser.lex("WRITE posts;");
	parser.program();
	remove_row("holdpost");
	
}

void Menu::edit_title(std::string str_input) {	
	std::string new_title;
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	std::cout << "[Editing "<< title <<"'s Title]\n\n";
	std::cout << "Current Title: " << title << "\n\n";
	std::cout << "* Enter new Title: ";
	std::getline(std::cin >> ws, new_title);
	std::cout << "\n";
	std::string query = "UPDATE editpost SET title == \"" + new_title + "\" WHERE (title == \""+title+"\");";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE editpost;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	parser.lex("WRITE posts;");
	parser.program();
	remove_row("holdpost");
}

void Menu::edit_tags(std::string str_input) {	
	std::string new_tags;
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	std::string tags = row[3].erase(row[3].size()-1);
	tags = tags.erase(0,1);
	std::cout << "[Editing "<< tags <<"'s Tag(s)]\n\n";
	std::cout << "Current Tags: " << tags << "\n\n";
	std::cout << "* Enter new tags: ";
	std::getline(std::cin >> ws, new_tags);
	std::cout << "\n";
	std::string query = "UPDATE editpost SET tags == \"" + new_tags + "\" WHERE (tags == \""+tags+"\");";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE editpost;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	parser.lex("WRITE posts;");
	parser.program();
	remove_row("holdpost");

}

void Menu::edit_content(std::string str_input) {	
	std::string new_content;
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	std::string content = row[2].erase(row[2].size()-1);
	content = content.erase(0,1);
	std::cout << "[Editing "<< title <<"'s Content]\n\n";
	std::cout << "Current Content: "<< content <<"\n\n";
	std::cout << "* Enter new Content: ";
	std::getline(std::cin >> ws, new_content);
	std::cout << "\n";
	std::string query = "UPDATE editpost SET content == \"" + new_content + "\" WHERE (tags == \""+content+"\");";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE editpost;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	parser.lex("WRITE posts;");
	parser.program();
	remove_row("holdpost");
}

void Menu::edit_comments(std::string str_input) {	
	int selection_input;
	std::string new_commenting;
	std::vector<std::string> row = get_entries(str_input+".db");
	std::string title = row[0].erase(row[0].size()-1);
	title = title.erase(0,1);
	std::string commenting = row[4].erase(row[4].size()-1);
	commenting = commenting.erase(0,1);
	
	std::cout << "[Editing "<< title <<"'s Commenting Options]\n\n";
	std::cout << "Current Commenting Setting: "<< commenting <<"\n\n";
	std::cout << "[Allow Commenting?]\n\n";
	std::cout << "1. Yes\n";
	std::cout << "2. No\n\n";
	std::cout << "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
		case 1: new_commenting = "yes";
				break;
		case 2: new_commenting = "no"; 
				break;
		default: 
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-2."; 
			 edit_comments(str_input);
	}
	std::string query = "UPDATE editpost SET commenting == \"" + new_commenting + "\" WHERE (tags == \""+commenting+"\");";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE editpost;");
	parser.program();
	parser.lex("WRITE holdpost;");
	parser.program();
	parser.lex("WRITE posts;");
	parser.program();
	remove_row("holdpost");
}

std::vector<std::string> Menu::search_options(std::string str_input) {

Table* t = parser.database->get_table(str_input);

  if (t != NULL) {
	  int i;
	  for (i = 0; i < t->get_items().size(); ++i) {
		std::vector<std::string> entry = t->get_items()[i];
		std::cout << i+1 << ". " << entry[0] << " " << entry[1] << std::endl;
		}
		std::cout << i+1 << ". Return to Main Menu\n";
		
		int ID;
		std::cout << "* Enter ID: "; 
		std::cin >> ID;
		std::cout << "\n";
		if(ID == i+1) {
			delete_searching_tables();
			print_menu();
		}
		else {
			std::vector<std::string> entry = t->get_items()[ID-1];
			return entry;
		}
	}
   else {
    cout << "The requested file " << str_input << " is not a relation.\n";
  }

}

void Menu::delete_searching_tables() {
	
	parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("answer.db") );
	if (std::ifstream("answer.db"))
	{	
		
		std::remove( "answer.db" );

	}
	
	if (std::ifstream("result.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("result.db") );
		std::remove( "result.db" );

	}
	
	if (std::ifstream("dateresult.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("dateresult.db") );
		std::remove( "dateresult.db" );
		parser.lex("CREATE TABLE dateresult (title VARCHAR(50), author VARCHAR(50)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	if (std::ifstream("tagsresult.db"))
	{
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("tagsresult.db") );
		std::remove( "tagsresult.db" );
		parser.lex("CREATE TABLE tagsresult (title VARCHAR(50), author VARCHAR(50)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	if (std::ifstream("titleresult.db"))
	{
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("titleresult.db") );
		std::remove( "titleresult.db" );
		parser.lex("CREATE TABLE titleresult (author VARCHAR(50), date VARCHAR(20)) PRIMARY KEY (author, date);");
		parser.program();
	}
	
	if (std::ifstream("authorresult.db"))
	{
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("authorresult.db") );
		std::remove( "authorresult.db" );
		parser.lex("CREATE TABLE authorresult (title VARCHAR(50), date VARCHAR(20)) PRIMARY KEY (title, date);");
		parser.program();
	}
	
	if (std::ifstream("testone.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("testone.db") );
		std::remove( "testone.db" );
		parser.lex("CREATE TABLE testone (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	if (std::ifstream("testtwo.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("testtwo.db") );
		std::remove( "testtwo.db" );
		parser.lex("CREATE TABLE testtwo (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	if (std::ifstream("testthree.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("testthree.db") );
		std::remove( "testthree.db" );
		parser.lex("CREATE TABLE testthree (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	if (std::ifstream("testfour.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("testfour.db") );
		std::remove( "testfour.db" );
		parser.lex("CREATE TABLE testfour (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	if (std::ifstream("testfive.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("testfive.db") );
		std::remove( "testfive.db" );
		parser.lex("CREATE TABLE testfive (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
}

int Menu::get_table_index(std::string name) {
	for (int i = 0; i < parser.database->dbms.size(); i++) {
		if (parser.database->dbms.at(i).get_name().compare(name)==0) {
			return i;
		}
	}
}

void Menu::remove_row(std::string name) {

	//create a new table
	std::string query;
	parser.lex("CREATE TABLE poststwo (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
	parser.program();
	//add unedited rows
	std::vector<std::string> row = get_entries(name+".db");
	
	query = "resulttwo <- select (author == " + row[1] + ") posts;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE resulttwo;");
	parser.program();
	parser.lex("INSERT INTO testtwo VALUES FROM RELATION project (title, author, content, tags, commenting, date) resulttwo;");
	parser.program();
	parser.lex("WRITE testtwo;");
	parser.program();
	
	query = "resultone <- select (author != " + row[1] + ") posts;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE resultone;");
	parser.program();
	parser.lex("INSERT INTO testone VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultone;");
	parser.program();
	parser.lex("WRITE testone;");
	parser.program();
	
	query = "resultthree <- select (title == " + row[0] + " && date == "+ row[5] +") testtwo;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE resultthree;");
	parser.program();
	parser.lex("INSERT INTO testthree VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultthree;");
	parser.program();
	parser.lex("WRITE testthree;");
	parser.program();
	
	query = "resultfour <- select (title != " + row[0] + " && date == "+ row[5] +") testtwo;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE resultfour;");
	parser.program();
	parser.lex("INSERT INTO testfour VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultfour;");
	parser.program();
	
	query = "resultfive <- select (title == " + row[0] + " && date != "+ row[5] +") testtwo;";
	parser.lex(query);
	parser.program();
	parser.lex("WRITE resultfive;");
	parser.program();
	parser.lex("INSERT INTO testfive VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultfive;");
	parser.program();
	
	parser.lex("WRITE testone;");
	parser.program();
	parser.lex("WRITE testthree;");
	parser.program();
	parser.lex("WRITE testfour;");
	parser.program();
	parser.lex("WRITE testfive;");
	parser.program();
	
	
	parser.lex("INSERT INTO poststwo VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultone;");
	parser.program();
	parser.lex("INSERT INTO poststwo VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultfour;");
	parser.program();
	parser.lex("INSERT INTO poststwo VALUES FROM RELATION project (title, author, content, tags, commenting, date) resultfive;");
	parser.program();
	
	
	if(!post_delete)
	{
		parser.lex("INSERT INTO poststwo VALUES FROM RELATION project (title, author, content, tags, commenting, date) editpost;");
		parser.program();
	}
	
	parser.lex("WRITE poststwo;");
	parser.program();
	// creates holdpost table and stores editpost into it
	if (std::ifstream("holdpost.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("holdpost.db") );
		std::remove( "holdpost.db" );
		parser.lex("CREATE TABLE holdpost (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
		parser.lex("INSERT INTO holdpost VALUES FROM RELATION project (title, author, content, tags, commenting, date) editpost;");
		parser.program();
	}
	// creates editpost table
	if (std::ifstream("editpost.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("editpost.db") );
		std::remove( "editpost.db" );
		parser.lex("CREATE TABLE editpost (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
	}
	
	//remove posts from dbms and add the the new table to dbms
	if (std::ifstream("posts.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("posts.db") );
		std::remove( "posts.db" );
		parser.lex("CREATE TABLE posts (title VARCHAR(50), author VARCHAR(50), content VARCHAR(1000000), tags VARCHAR(100), commenting  VARCHAR(10), date VARCHAR(20)) PRIMARY KEY (title, author);");
		parser.program();
		parser.lex("INSERT INTO posts VALUES FROM RELATION project (title, author, content, tags, commenting, date) poststwo;");
		parser.program();
	}
	
	// remove holder for new table from dbms
	if (std::ifstream("poststwo.db"))
	{	
		parser.database->dbms.erase( parser.database->dbms.begin() + get_table_index("poststwo.db") );
		std::remove( "poststwo.db" );
	}
	
	delete_searching_tables();

}

//Used on tables with only one row
std::vector<std::string> Menu::get_entries(std::string name) {
	Table* t = parser.database->get_table(name);
	std::vector<std::string> entry = t->get_items()[0];
	return entry;
}



std::string Menu::get_rest_of_string(int from, std::string str_input) {
	std::string post = "";
	for(int i = from; i < str_input.size(); i++)
	{
		post += str_input.at(i);
	}
	
	return post;
}


