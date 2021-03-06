#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>

#include <string>
#include <cstring>

#include <readline/readline.h>
#include <readline/history.h>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

#include "menu.h"

int main(int argc, char* argv[]) {
  // Start Engine
  Engine dbengine;

  // read shell hist
  errlog("Reading shell history from .shellhist");
  if (read_history(".shellhist") == 0) {
    errlog("Read Success");
  } else {
    errlog("Read Failure");
  }

  // if provided script and --file
  if ((argc > 2) && (std::strcmp(argv[1], "--file") == 0)) {
    errlog("Reading SQL Programs from file");

    std::vector<std::string> programs;

    // read file from stdin
    std::string line;
    std::ifstream scriptfile(argv[2]);
    if (scriptfile.is_open()) {
      while (std::getline(scriptfile, line)) {
        // skip empty lines
        if (line.length() > 1) {
          programs.push_back(line);
        }
      }
      scriptfile.close();
    }

// print debug info
#ifdef DEBUG
    errlog("Read Programs:");
    for (std::string prog : programs) {
      errlog(prog);
    }
#endif

    // if there's at least one string
    if (programs.size() > 0) {
      // run script
      for (std::string prog : programs) {
        std::string errstr = "Main: Running: " + prog;
        errlog(errstr);
        if (prog.length() > 1) {
          if (dbengine.execSQL(prog) != 0) {
            std::string errmsg = "Shell: " + prog + " FAILED.";
            errlog(errmsg);
          }
          add_history(prog.c_str());
        }
#ifdef DEBUG
        draw_line();
#endif
      }
    }
    std::cout << "Script Execution Finished." << std::endl;
    // write history to shell mode history file
  }

  // Start Blog
  std::cout << "Group 15 Blog" << std::endl;
  draw_line();
  errlog("App: Opening Tables.");
  std::vector<std::string> app_tables{"posts", "tags", "tagmap", "comments"};
  std::vector<std::string> need_tables;
  for (std::string title : app_tables) {
    if (dbengine.openTable(title) != -1) {
      std::string errstr = "App: Opened Table: " + title;
      errlog(errstr);
    } else {
      std::string errstr = "App: Failed to open Table: " + title;
      errlog(errstr);
      // push back table on to need_tables
      // we will create those tables if they can't be found.
      need_tables.push_back(title);
    }
  }
  if (need_tables.size() > 0) {
    // log needed tables.
    errlog("Creating Tables...", true);
    std::string errstr = "App: Creating Tables: ";
    for (std::string title : need_tables) {
      errstr += title + " ";
    }
    errlog(errstr);
  }

  // create needed tables
  for (std::string title : need_tables) {
    if (title == "posts") {
      std::string sqlprog =
          "CREATE TABLE posts (id INTEGER, title VARCHAR(1024), author "
          "VARCHAR(1024), date INTEGER, content VARCHAR(32768), "
          "if_comment INTEGER) PRIMARY KEY (id);";
      // add command to readline history
      add_history(sqlprog.c_str());
      dbengine.execSQL(sqlprog);
    } else if (title == "tags") {
      std::string sqlprog =
          "CREATE TABLE tags (id INTEGER, tagname VARCHAR(1024)) PRIMARY KEY "
          "(id);";
      // add command to readline history
      add_history(sqlprog.c_str());
      dbengine.execSQL(sqlprog);
    } else if (title == "tagmap") {
      std::string sqlprog =
          "CREATE TABLE tagmap (id INTEGER, tagid INTEGER, postid INTEGER) "
          "PRIMARY KEY (id);";
      // add command to readline history
      add_history(sqlprog.c_str());
      dbengine.execSQL(sqlprog);
    } else if (title == "comments") {
      // inrefto is the id of the parent comment, -1 for top level comment
      std::string sqlprog =
          "CREATE TABLE comments (id INTEGER, postid INTEGER, author "
          "VARCHAR(1024), date INTEGER, content VARCHAR(4096), inrefto "
          "INTEGER) PRIMARY KEY (id);";
      // add command to readline history
      add_history(sqlprog.c_str());
      dbengine.execSQL(sqlprog);
    }
  }

  // Create menu
  Menu menu(dbengine);

  // Start prompt
  // input and shell_prompt buffer
  char* input, shell_prompt[4096];
  std::string shell_hist_file = ".shellhist";
  std::string app_hist_file = ".apphist";
  std::string menuinput;
  // default to app mode
  bool shellmode = false;

  // write script history to file
  errlog("Writing script history to .shellhist");
  if (write_history((shell_hist_file).c_str()) == 0) {
    errlog("Write Success");
  } else {
    errlog("Write Failure");
  }
  // clear history
  clear_history();
  // read app history
  errlog("Reading app history from .apphist");
  if (read_history((app_hist_file).c_str()) == 0) {
    errlog("Read Success");
  } else {
    errlog("Read Failure");
  }

  // Configure readline to auto-complete paths when the tab key is hit.
  rl_bind_key('\t', rl_complete);

  for (;;) {
    if (!shellmode) {
      // print menu
      menu.menu_print();
    }

// Create prompt string from user name
#ifdef DEBUG
    if (shellmode) {
      snprintf(shell_prompt, sizeof(shell_prompt), "%s@DBengine(DEBUG) $ ",
               getenv("USER"));
    } else {
      // app mode
      snprintf(shell_prompt, sizeof(shell_prompt), "%s@blog(DEBUG) > ",
               getenv("USER"));
    }
#else
    if (shellmode) {
      snprintf(shell_prompt, sizeof(shell_prompt), "%s@DBengine $ ",
               getenv("USER"));
    } else {
      // app mode
      snprintf(shell_prompt, sizeof(shell_prompt), "%s@blog > ",
               getenv("USER"));
    }
#endif

    // Display prompt and read input (NB: input must be freed after use)...
    input = readline(shell_prompt);

    // Check for EOF.
    if (!input) {
      std::cout << std::endl;

      errlog("Got EOF. Writing histories and exiting.");
      // write histories
      if (shellmode) {
        // write shell history to file
        errlog("Writing shell history to .shellhist");
        if (write_history((shell_hist_file).c_str()) == 0) {
          errlog("Write Success");
        } else {
          errlog("Write Failure");
        }
        // clear history
        clear_history();
        // read app history
        errlog("Reading app history from .apphist");
        if (read_history((app_hist_file).c_str()) == 0) {
          errlog("Read Success");
        } else {
          errlog("Read Failure");
        }
        // write app history
        errlog("Writing app history to .apphist");
        if (write_history((app_hist_file).c_str()) == 0) {
          errlog("Write Success");
        } else {
          errlog("Write Failure");
        }
      } else {
        // write app history
        errlog("Writing app history to .apphist");
        if (write_history((app_hist_file).c_str()) == 0) {
          errlog("Write Success");
        } else {
          errlog("Write Failure");
        }
        // clear history
        clear_history();
        // read shell history
        errlog("Reading shell history from .shellhist");
        if (read_history((shell_hist_file).c_str()) == 0) {
          errlog("Read Success");
        } else {
          errlog("Read Failure");
        }
        // write shell history to file
        errlog("Writing shell history to .shellhist");
        if (write_history((shell_hist_file).c_str()) == 0) {
          errlog("Write Success");
        } else {
          errlog("Write Failure");
        }
      }
      errlog("Exiting.");
      break;
    }

    // Add input to history.
    add_history(input);

    // parse input
    // check if help
    if ((std::strcmp(input, "?") == 0) || (std::strcmp(input, "h") == 0) ||
        (std::strcmp(input, "help") == 0)) {
      std::cout << std::endl;
      std::cout << "Help" << std::endl;
      draw_line();
      std::cout << "App CLI Arguments" << std::endl;
      draw_line(76);
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "< (file)";
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Run app script and quit (example in engine/share)"
                << std::endl;
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "--file (file)";
      std::cout
          << std::left << std::setw(20) << std::setfill(' ')
          << "Run sql script before starting app (example in engine/share)"
          << std::endl;
      std::cout << std::endl;

      std::cout << "Any Mode" << std::endl;
      draw_line(76);
      std::cout << std::left << std::setw(20) << std::setfill(' ') << "Up Key";
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Previous Command in History" << std::endl;
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Down Key";
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Next Command in History" << std::endl;
      std::cout << std::left << std::setw(20) << std::setfill(' ') << "^D";
      std::cout << std::left << std::setw(20) << std::setfill(' ') << "Exit app"
                << std::endl;
      std::cout << std::endl;
      std::cout << std::left << std::setw(20) << std::setfill(' ') << "shell";
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Toggle shell mode" << std::endl;
      std::cout << std::endl;

      std::cout << "App Mode" << std::endl;
      draw_line(76);
      // app mode help lines here
      std::cout << std::left << std::setw(20) << std::setfill(' ') << "input";
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Open Menu or run command indicated" << std::endl;
      std::cout << std::endl;

      std::cout << "Shell Mode" << std::endl;
      draw_line(76);
      // shell mode help lines here
      std::cout << std::left << std::setw(20) << std::setfill(' ') << "input";
      std::cout << std::left << std::setw(20) << std::setfill(' ')
                << "Any valid dml program" << std::endl;
      draw_line();
      std::cout << std::endl;
      std::cout << std::endl;
    } else if (std::strcmp(input, "shell") == 0) {
      if (shellmode) {
        errlog("Switching to app mode.", true);
        shellmode = false;
        // write shell history to file
        errlog("Writing shell history to .shellhist");
        if (write_history((shell_hist_file).c_str()) == 0) {
          errlog("Write Success");
        } else {
          errlog("Write Failure");
        }
        // clear history
        clear_history();
        // read app history
        errlog("Reading app history from .apphist");
        if (read_history((app_hist_file).c_str()) == 0) {
          errlog("Read Success");
        } else {
          errlog("Read Failure");
        }
      } else {
        errlog("Switching to shell mode. Commands are sent directly to engine.",
               true);
        shellmode = true;
        // write app history
        errlog("Writing app history to .apphist");
        if (write_history((app_hist_file).c_str()) == 0) {
          errlog("Write Success");
        } else {
          errlog("Write Failure");
        }
        // clear history
        clear_history();
        // read shell history
        errlog("Reading shell history from .shellhist");
        if (read_history((shell_hist_file).c_str()) == 0) {
          errlog("Read Success");
        } else {
          errlog("Read Failure");
        }
      }
    } else if (std::strcmp(input, "") == 0) {
      // nothing
    } else {
      if (shellmode) {
        if (dbengine.execSQL(input) != 0) {
          std::string errmsg = "Shell: " + std::string(input) + " FAILED.";
          errlog(errmsg);
          std::cerr << "Invalid Statement: " << input << std::endl;
        }
      } else {
        // app mode
        menuinput = std::string(input);
        std::string errstr = "App: Menu input: " + menuinput;
        errlog(errstr);
        if (menu.menu_exec(menuinput) == -1) {
          break;
        }
      }
    }

    // Free input.
    free(input);
  }

  // dbengine.execSQL("EXIT;");

  return 0;
}
