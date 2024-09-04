//******************
//
// scls_workspace_agatha.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Workspace of SCLS is a software made to handle development with SCLS more easily.
//
// This file contains the window for the Agatha part of the software.
//
//******************
//
// License (LGPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SCLS_WORKSPACE_AGATHA
#define SCLS_WORKSPACE_AGATHA

#include "../../scls-graphic-benoit/scls_graphic.h"
#include "../../scls-documentalist-agatha/scls_documentalist.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// SCLS_Workspace_Agatha_Page class
	//
	//*********

	class SCLS_Workspace_Agatha_Page : public GUI_Page {
	    // Class representating the agatha part page of SCLS Workspace
    public:

        //*********
        //
        // SCLS_Workspace_Agatha_Page main members
        //
        //*********

        // SCLS_Workspace_Agatha_Page constructor
        SCLS_Workspace_Agatha_Page(_Window_Advanced_Struct* window_struct, std::string name);

        // Load an object in a page from XML
        virtual std::shared_ptr<GUI_Object> __create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent);

        //*********
        //
        // Displaying members
        //
        //*********

        // Display the open pattern page
        void display_open_pattern();
        // Display the project pattern page
        void display_pattern_project();
        // Display the project pattern file page
        void display_pattern_project_file();
        // Display the project file dition page
        void display_replica_file_edition();
        // Display the project replica global variable page
        void display_replica_global_variable();
        // Display the open replica page
        void display_replica_open();
        // Display the project replica page
        void display_replica_project();
        // Display the project replica export page
        void display_replica_project_export();
        // Display the project replica export path change page
        void display_replica_project_export_path_change();

        // Hide all the agatha part
        void hide_all();

        //*********
        //
        // Event members
        //
        //*********

        // Check the events for the file explorer
        void check_file_explorer_events();
        // Check the events for the help footer
        void check_help_footer_events();
        // Check the events for the pattern project main page
        void check_pattern_project_main_events();
        // Check the events for the pattern project navigation page
        void check_pattern_project_navigation_events();
        // Check the events for the replica project page
        void check_replica_project_events();
        // Check the events for the replica project export page
        void check_replica_project_export_events();
        // Check the events for the replica project footer page
        void check_replica_project_footer_events();
        // Check the events for the replica project navigation page
        void check_replica_project_navigation_events();

        // Update the events of the page
        virtual void update_event();

        // Getters and setters
        inline Pattern_Project* currently_displayed_pattern_project() const {return a_current_state.currently_displayed_pattern_project.get();};
        inline Text_Pattern* currently_displayed_pattern_project_file() const {return a_current_state.currently_displayed_pattern_project_file.get();};
        inline Replica_Project* currently_displayed_replica_project() const {return a_current_state.currently_displayed_replica_project.get();};

        //*********
        //
        // Pattern handling
        //
        //*********

        // Returns a loaded pattern by its path
        inline std::shared_ptr<Pattern_Project> loaded_pattern_by_path(std::string path) {
            for(int i = 0;i<static_cast<int>(a_loaded_patterns.size());i++) {
                if(a_loaded_patterns[i].get()->path() == path) return a_loaded_patterns[i];
            }
            return std::shared_ptr<Pattern_Project>();
        };
        // Loads an existing pattern and returns it
        std::shared_ptr<Pattern_Project> load_pattern_project(std::string path);
        // Loads the buttons in the pattern project navigation
        void load_pattern_project_navigation();
        // Unloads the buttons in the pattern project navigation
        void unload_pattern_project_navigation();

        //*********
        //
        // Replica handling
        //
        //*********

        // Returns the currently displayed export path
        inline std::string currently_displayed_export_path() const {return a_current_state.currently_displayed_export_path;};
        // Returns the name of the currently displayed replica global variable
        inline std::string currently_displayed_replica_global_variable() const {return a_current_state.currently_displayed_replica_global_variable;};
        // Returns the currently displayed replica file
        inline Replica_File* currently_displayed_replica_file() {return a_current_state.currently_displayed_replica_file.get();};

        // Exports the current replica project
        void export_replica_project();
        // Loads an existing replica and returns it
        std::shared_ptr<Replica_Project> load_replica_project(std::string path);
        // Loads the global variables buttons to navigate in the project
        void load_global_variables_project_navigation();
        // Loads the button to navigate in the project
        void load_replica_project_navigation();
        // Save the current replica project
        void save_replica_project();
        // Unloads the global variables buttons to navigate in the project
        void unload_global_variables_project_navigation(){a_replica_project_global_variables_navigation_buttons.clear();a_replica_project_global_variables_body.get()->reset();};
        // Unoads the button to navigate in the project
        void unload_replica_project_navigation(){a_replica_file_by_replica_project_navigation_buttons.clear();a_replica_project_navigation_buttons.clear();a_replica_project_main_navigation.get()->reset();};

	private:

	    //*********
        //
        // Pattern handling
        //
        //*********

	    // Every loaded patterns in the software
        std::vector<std::shared_ptr<Pattern_Project>> a_loaded_patterns = std::vector<std::shared_ptr<Pattern_Project>>();

	    //*********
        //
        // Current state of the page
        //
        //*********

        // Struct representating the current state of the page
        struct {
            // Define each possible current pages
            #define SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE 1
            #define SCLS_WORKSPACE_AGATHA_HELP_PAGE 0
            #define SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE 3
            #define SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_MAIN_PAGE 2
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_MAIN_PAGE 4
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_EDITION_PAGE 5
            #define SCLS_WORKSPACE_AGATHA_REPLICA_GLOBAL_VARIABLE_PAGE 6
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PAGE 7
            // Define each possible file chosen
            #define SCLS_WORKSPACE_AGATHA_OPEN_PATTERN 0
            #define SCLS_WORKSPACE_AGATHA_OPEN_REPLICA 1
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PATH 2

            // Current file chosen in Agatha
            unsigned short current_file_chosen = SCLS_WORKSPACE_AGATHA_OPEN_PATTERN;
            // Current page of Agatha
            unsigned short current_page = SCLS_WORKSPACE_AGATHA_HELP_PAGE;

            // Currently displayed pattern project
            std::shared_ptr<Pattern_Project> currently_displayed_pattern_project;
            // Currently displayed pattern project file
            std::shared_ptr<Text_Pattern> currently_displayed_pattern_project_file;
            // File in the pattern project navigation connected to the button
            std::vector<std::shared_ptr<Text_Pattern>> pattern_project_navigation_files = std::vector<std::shared_ptr<Text_Pattern>>();
            // Buttons in the pattern project navigation
            std::vector<std::shared_ptr<GUI_Text>> pattern_project_navigation_buttons = std::vector<std::shared_ptr<GUI_Text>>();

            // Currently displayed pattern project
            std::shared_ptr<Replica_Project> currently_displayed_replica_project;

            // Currently chosen export path
            std::string currently_displayed_export_path = "";
            // Name of the currently displayed replica global variable
            std::string currently_displayed_replica_global_variable = "";
            // Currently displayed replica file
            std::shared_ptr<Replica_File> currently_displayed_replica_file = 0;
        } a_current_state;

        //*********
        //
        // Replica handling
        //
        //*********

        // Buttons in the replica project navigation for the global variables
        std::vector<std::shared_ptr<GUI_Text>> a_replica_project_global_variables_navigation_buttons = std::vector<std::shared_ptr<GUI_Text>>();

        // Replica file by buttons in the replica project navigation
        std::map<GUI_Text*, std::shared_ptr<Replica_File>> a_replica_file_by_replica_project_navigation_buttons = std::map<GUI_Text*, std::shared_ptr<Replica_File>>();
        // Buttons in the replica project navigation
        std::vector<std::shared_ptr<GUI_Text>> a_replica_project_navigation_buttons = std::vector<std::shared_ptr<GUI_Text>>();

	    //*********
        //
        // GUI stuffs
        //
        //*********

        // Bodies / footers / navigation

        // Body of the file explorer
        std::shared_ptr<GUI_File_Explorer> a_file_explorer_body;
        // Body of the help part
        std::shared_ptr<GUI_Object> a_help_body;
        // Body of the help part
        std::shared_ptr<GUI_Object> a_help_footer;
        // Navigation of the help part
        std::shared_ptr<GUI_Scroller> a_help_navigation;
        // Body of the pattern project part
        std::shared_ptr<GUI_Object> a_pattern_project_file_body;
        // Body of the pattern project part
        std::shared_ptr<GUI_Object> a_pattern_project_main_body;
        // Footer of the pattern project part
        std::shared_ptr<GUI_Object> a_pattern_project_main_footer;
        // Navigation of the pattern project part
        std::shared_ptr<GUI_Scroller> a_pattern_project_main_navigation;
        // Body of the replica file edition part
        std::shared_ptr<GUI_Object> a_replica_text_file_edition_body;
        // Body of the replica global variable edition part
        std::shared_ptr<GUI_Object> a_replica_global_variable_edition_body;
        // Body of the replica project export part
        std::shared_ptr<GUI_Object> a_replica_project_export_body;
        // Body of the replica global variables part
        std::shared_ptr<GUI_Scroller> a_replica_project_global_variables_body;
        // Body of the replica project part
        std::shared_ptr<GUI_Object> a_replica_project_main_body;
        // Footer of the replica project part
        std::shared_ptr<GUI_Object> a_replica_project_main_footer;
        // Navigation of the replica project part
        std::shared_ptr<GUI_Scroller> a_replica_project_main_navigation;

        // Text / text inputs

        // Text input of the pattern project body
        std::shared_ptr<GUI_Text_Input> a_pattern_project_file_text_input;
        // Title of the pattern project body
        std::shared_ptr<GUI_Text> a_pattern_project_title;
        // Text input of the replica file edition body
        std::shared_ptr<GUI_Text_Input> a_replica_text_file_edition_text_input;
        // Text input of the replica global variable edition body
        std::shared_ptr<GUI_Text_Input> a_replica_global_variable_edition_text_input;
        // Path of the replica project export body
        std::shared_ptr<GUI_Text> a_replica_project_export_path;
        // Title of the replica project export body
        std::shared_ptr<GUI_Text> a_replica_project_export_title;
        // Title of the replica project body
        std::shared_ptr<GUI_Text> a_replica_project_title;

        // Buttons

        // Button to open a pattern
        std::shared_ptr<GUI_Text> a_pattern_open_button;
        // Button to export a replica
        std::shared_ptr<GUI_Text> a_replica_export_button;
        // Button to open a replica
        std::shared_ptr<GUI_Text> a_replica_open_button;
        // Button to change a path in an export of a replica project
        std::shared_ptr<GUI_Text> a_replica_project_export_path_change_button;
        // Button to save a replica project
        std::shared_ptr<GUI_Text> a_replica_project_save_button;
        // Button to validate an export of a replica project
        std::shared_ptr<GUI_Text> a_replica_project_validate_export_button;
	};
}

#endif // SCLS_WORKSPACE_AGATHA
