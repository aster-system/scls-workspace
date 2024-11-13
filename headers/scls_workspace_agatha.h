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
        // Pattern handling
        //
        //*********

        // Returns the currently displayed pattern project creator name
        inline std::string currently_displayed_pattern_project_creator_name() const {return a_pattern_project_creator_name.get()->text();};
        // Returns the currently displayed pattern project creator path
        inline std::string currently_displayed_pattern_project_creator_path() const {return a_current_state.currently_displayed_pattern_project_creator_path;};
        // Returns the currently displayed pattern project file creator name
        inline std::string currently_displayed_pattern_project_file_creator_name() const {return a_pattern_project_file_creator_name.get()->text();};
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
        // Loads the buttons in the pattern project replicas
        void load_pattern_project_replica();
        // Unloads the buttons in the pattern project navigation
        void unload_pattern_project_navigation();
        // Unloads the buttons in the pattern project replicas
        void unload_pattern_project_replica(){a_replica_project_by_pattern_footer_buttons.clear();a_pattern_project_main_footer_replica.get()->reset();};

        // Create a pattern project
        std::shared_ptr<Pattern_Project> create_pattern_project();
        // Create a pattern project file
        std::shared_ptr<Text_Pattern> create_pattern_project_file();
        // Create a replica project from this pattern project
        std::shared_ptr<Replica_Project> create_replica_project();
        // Saves the current pattern project
        void save_pattern_project();

        //*********
        //
        // Replica handling
        //
        //*********

        // Returns the currently displayed export path
        inline std::string currently_displayed_export_path() const {return a_current_state.currently_displayed_export_path;};
        // Returns the currently displayed replica file creator name
        inline std::string currently_displayed_replica_file_creator_name() const {return a_replica_file_creator_name.get()->text();};
        // Returns the currently displayed replica project creator name
        inline std::string currently_displayed_replica_project_creator_name() const {return a_replica_project_creator_name.get()->text();};
        // Returns the currently displayed replica project creator path
        inline std::string currently_displayed_replica_project_creator_path() const {return a_current_state.currently_displayed_replica_project_creator_path;};
        // Returns the name of the currently displayed replica global variable
        inline std::string currently_displayed_replica_global_variable() const {return a_current_state.currently_displayed_replica_global_variable;};
        // Returns the currently displayed replica file
        inline Replica_File* currently_displayed_replica_file() {return a_current_state.currently_displayed_replica_file.get();};
        // Returns the currently displayed replica file variable
        inline Replica_File_Variable* currently_displayed_replica_file_variable() {return a_current_state.currently_displayed_replica_file_variable.get();};
        // Returns the currently displayed replica file variable list
        inline Replica_File_Variable_List* currently_displayed_replica_file_variable_list() {
            if(!currently_displayed_replica_file_variable()->listed()) return 0;
            return reinterpret_cast<Replica_File_Variable_List*>(currently_displayed_replica_file_variable());
        };

        // Loads the button for the variable in a replica file project
        void load_replica_file_edition_variable();
        // Unloads the button for the variable in a replica file project
        void unload_replica_file_edition_variable(){a_replica_file_edition_variable_by_buttons.clear();a_replica_file_edition_variable_buttons.clear();a_replica_file_edition_variable.get()->reset();};

        // Creates a new replica file and returns it
        std::shared_ptr<Replica_File> create_replica_file();
        // Creates a new replica file variable element and returns it
        std::shared_ptr<Replica_File_Variable_Element> create_replica_file_variable_element(std::shared_ptr<Replica_File_Variable> parent_variable);
        // Exports the current replica project
        void export_replica_project();
        // Returns a loaded replica by its path
        inline std::shared_ptr<Replica_Project> loaded_replica_by_path_shared_ptr(std::string path) const {
            for(int i = 0;i<static_cast<int>(a_loaded_replicas.size());i++) {
                if(a_loaded_replicas[i].get()->path() == path) return a_loaded_replicas.at(i);
            } return std::shared_ptr<Replica_Project>();
        };
        inline Replica_Project* loaded_replica_by_path(std::string path) const {return loaded_replica_by_path_shared_ptr(path).get();};
        // Loads an existing replica and returns it
        std::shared_ptr<Replica_Project> load_replica_project(std::string path);
        // Loads the global variables buttons to navigate in the project
        void load_global_variables_project_navigation();
        // Loads the button to navigate in the replica file creator
        void load_replica_file_creator_navigation();
        // Loads the button to navigate in the replica file variable element
        void load_replica_file_variable_element_navigation();
        void unload_replica_file_variable_element_navigation(){a_replica_file_variable_element_edition_buttons.clear();a_replica_file_variable_element_edition_by_buttons.clear();a_replica_file_variable_element_edition_scroller.get()->reset();};
        // Loads the button to navigate in the replica file variable list
        void load_replica_file_variable_list_navigation();
        // Loads the button to navigate in the project
        void load_replica_project_navigation();
        // Save the current replica project
        void save_replica_project();
        // Unloads the global variables buttons to navigate in the project
        inline void unload_global_variables_project_navigation(){a_replica_project_global_variables_navigation_buttons.clear();a_replica_project_global_variables_body.get()->reset();};
        // Unloads the button to navigate in the replica file creator
        inline void unload_replica_file_creator_navigation(){a_replica_file_creator_navigation_buttons_with_pattern.clear();a_replica_file_creator_navigation_buttons.clear();a_replica_file_creator_navigation.get()->reset();};
        // Loads the button to navigate in the replica file variable list
        inline void unload_replica_file_variable_list_navigation(){a_replica_file_edition_variable_list_by_buttons.clear();a_replica_file_variable_edition_list_buttons.clear();a_replica_file_variable_list_edition_scroller.get()->reset();};
        // Unloads the button to navigate in the project
        inline void unload_replica_project_navigation(){a_replica_file_by_replica_project_navigation_buttons.clear();a_replica_project_navigation_buttons.clear();a_replica_project_main_navigation.get()->reset();};

        // Returns the name of a replica file variable list button
        inline std::string replica_file_variable_list_button_name(int position) {if(position<0)position+=currently_displayed_replica_file_variable_list()->elements.size();return std::string("replica_file_edition_variable_list_button_") + std::to_string(position);};

        //*********
        //
        // Displaying members
        //
        //*********

        // Display the open pattern page
        void display_open_pattern();
        // Display the project pattern page
        void display_pattern_project();
        // Display the project pattern creator page
        void display_pattern_project_creator();
        // Display the project pattern creator path change page
        void display_pattern_project_creator_path_change();
        // Display the project pattern file page
        void display_pattern_project_file(std::shared_ptr<Text_Pattern> chosen_pattern_file);
        // Display the project pattern file cretor page
        void display_pattern_project_file_creator();
        // Display the replica project file creator page
        void display_replica_file_creator();
        // Display the project file edition page
        void display_replica_file_edition();
        // Display the project file settings page
        void display_replica_file_settings();
        // Display the project file variable edition page
        void display_replica_file_variable_edition();
        // Display the project file variable element edition page
        void display_replica_file_variable_element_edition();
        // Display the project file variable list edition page
        void display_replica_file_variable_list_edition();
        // Display the project replica global variable page
        void display_replica_global_variable();
        // Display the open replica page
        void display_replica_open();
        // Display the project replica page
        void display_replica_project();
        // Display the replica project creator page
        void display_replica_project_creator();
        // Display the replica project creator path change page
        void display_replica_project_creator_path_change();
        // Display the project replica export page
        void display_replica_project_export();
        // Display the project replica export path change page
        void display_replica_project_export_path_change();
        // Display the project text file edition page
        void display_replica_text_file_edition();

        // Check the opened page to keep the modification
        void check_opened_page();
        // Hide all the agatha part
        void hide_all();

        //*********
        //
        // Event members
        //
        //*********

        // Check the events for the help pattern project creator
        void check_help_creator_pattern_project_events();
        // Check the events for the file explorer
        void check_file_explorer_events();
        // Check the events for the help footer
        void check_help_footer_events();
        // Check the events for the pattern project file creator page
        void check_pattern_project_file_creator();
        // Check the events for the pattern project footer page
        void check_pattern_project_footer_events();
        // Check the events for the pattern project main page
        void check_pattern_project_main_events();
        // Check the events for the pattern project navigation page
        void check_pattern_project_navigation_events();
        // Check the events for the replica file creation page
        void check_replica_file_creator_events();
        // Check the events for the replica file edition page
        void check_replica_file_edition_events();
        // Check the events for the replica file settings page
        void check_replica_file_settings_events();
        // Check the events for the replica file variable edition page and returns if the page changed
        bool check_replica_file_variable_edition_events();
        // Check the events for the replica file variable element page and returns if the page changed
        bool check_replica_file_variable_element_edition_events();
        // Check the events for the replica file variable list page
        void check_replica_file_variable_list_events();
        // Check the events for the replica project creator page
        void check_replica_project_creator_events();
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
        inline __Replica_File_Variable_Element_Base* currently_displayed_replica_file_variable_element() const {return a_current_state.currently_displayed_replica_file_variable_element.get();};
        inline Replica_Project* currently_displayed_replica_project() const {return a_current_state.currently_displayed_replica_project.get();};

	private:

	    //*********
        //
        // Current state of the page
        //
        //*********

        // Struct representating the current state of the page
        struct {
            // Define each possible current pages
            #define SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PAGE 10
            #define SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE 1
            #define SCLS_WORKSPACE_AGATHA_HELP_PAGE 0
            #define SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE 3
            #define SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_CREATOR_PAGE 11
            #define SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_MAIN_PAGE 2
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_MAIN_PAGE 4
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_CREATOR_PAGE 13
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_EDITION_PAGE 5
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_SETTINGS_PAGE 16
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_EDITION_PAGE 9
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_ELEMENT_EDITION_PAGE 15
            #define SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_LIST_EDITION_PAGE 14
            #define SCLS_WORKSPACE_AGATHA_REPLICA_GLOBAL_VARIABLE_PAGE 6
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PAGE 12
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PAGE 7
            #define SCLS_WORKSPACE_AGATHA_REPLICA_TEXT_FILE_EDITION_PAGE 8
            // Define each possible file chosen
            #define SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PATH 3
            #define SCLS_WORKSPACE_AGATHA_OPEN_PATTERN 0
            #define SCLS_WORKSPACE_AGATHA_OPEN_REPLICA 1
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PATH 4
            #define SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PATH 2

            // Current file chosen in Agatha
            unsigned short current_file_chosen = SCLS_WORKSPACE_AGATHA_OPEN_PATTERN;
            // Current page of Agatha
            unsigned short current_page = SCLS_WORKSPACE_AGATHA_HELP_PAGE;

            // Currently displayed pattern project
            std::shared_ptr<Pattern_Project> currently_displayed_pattern_project;
            // Currently displayed pattern project file
            std::shared_ptr<Text_Pattern> currently_displayed_pattern_project_file;
            // Currently chosen pattern project creator path
            std::string currently_displayed_pattern_project_creator_path = "";
            // File in the pattern project navigation connected to the button
            std::vector<std::shared_ptr<Text_Pattern>> pattern_project_navigation_files = std::vector<std::shared_ptr<Text_Pattern>>();
            // Buttons in the pattern project navigation
            std::vector<std::shared_ptr<GUI_Text>> pattern_project_navigation_buttons = std::vector<std::shared_ptr<GUI_Text>>();

            // Currently displayed pattern project
            std::shared_ptr<Replica_Project> currently_displayed_replica_project;

            // Currently chosen export path
            std::string currently_displayed_export_path = "";
            // Currently displayed replica file variable
            std::shared_ptr<Replica_File_Variable> currently_displayed_replica_file_variable;
            // Currently displayed replica file variable element
            std::shared_ptr<__Replica_File_Variable_Element_Base> currently_displayed_replica_file_variable_element;
            // Currently chosen creator path
            std::string currently_displayed_replica_project_creator_path = "";
            // Name of the currently displayed replica global variable
            std::string currently_displayed_replica_global_variable = "";
            // Currently displayed replica file
            std::shared_ptr<Replica_File> currently_displayed_replica_file;
            // Currently asked delete text for a replica file ement
            bool currently_replica_file_variable_list_delete_state = false;
        } a_current_state;

        //*********
        //
        // Pattern handling
        //
        //*********

	    // Every loaded patterns in the software
        std::vector<std::shared_ptr<Pattern_Project>> a_loaded_patterns = std::vector<std::shared_ptr<Pattern_Project>>();

        // Pattern variable by buttons in the replica project navigation
        std::map<std::shared_ptr<GUI_Text>, std::shared_ptr<Replica_Project>> a_replica_project_by_pattern_footer_buttons = std::map<std::shared_ptr<GUI_Text>, std::shared_ptr<Replica_Project>>();

        //*********
        //
        // Replica handling
        //
        //*********

        // Every loaded replicas in the software
        std::vector<std::shared_ptr<Replica_Project>> a_loaded_replicas = std::vector<std::shared_ptr<Replica_Project>>();

        // Buttons in the replica project navigation
        std::vector<std::shared_ptr<GUI_Text>> a_replica_file_edition_variable_buttons = std::vector<std::shared_ptr<GUI_Text>>();
        // Pattern variable by buttons in the replica project navigation
        std::map<GUI_Text*, std::shared_ptr<Replica_File_Variable>> a_replica_file_edition_variable_by_buttons = std::map<GUI_Text*, std::shared_ptr<Replica_File_Variable>>();

        // Buttons in the replica file variable list edition navigation
        std::vector<std::shared_ptr<GUI_Text>> a_replica_file_variable_edition_list_buttons = std::vector<std::shared_ptr<GUI_Text>>();
        std::map<GUI_Text*, std::shared_ptr<__Replica_File_Variable_Element_Base>> a_replica_file_edition_variable_list_by_buttons = std::map<GUI_Text*, std::shared_ptr<__Replica_File_Variable_Element_Base>>();

        // Buttons in the replica file variable element edition navigation
        std::vector<std::shared_ptr<GUI_Text>> a_replica_file_variable_element_edition_buttons = std::vector<std::shared_ptr<GUI_Text>>();
        std::map<GUI_Text*, std::shared_ptr<Replica_File_Variable>> a_replica_file_variable_element_edition_by_buttons = std::map<GUI_Text*, std::shared_ptr<Replica_File_Variable>>();

        // Buttons in the replica project navigation for the global variables
        std::vector<std::shared_ptr<GUI_Text>> a_replica_project_global_variables_navigation_buttons = std::vector<std::shared_ptr<GUI_Text>>();

        // Replica file by buttons in the replica project navigation
        std::map<GUI_Text*, std::shared_ptr<Replica_File>> a_replica_file_by_replica_project_navigation_buttons = std::map<GUI_Text*, std::shared_ptr<Replica_File>>();
        // Buttons in the replica file creator navigation
        std::vector<std::shared_ptr<GUI_Text>> a_replica_file_creator_navigation_buttons = std::vector<std::shared_ptr<GUI_Text>>();
        std::map<std::string, std::shared_ptr<scls::Text_Pattern>> a_replica_file_creator_navigation_buttons_with_pattern = std::map<std::string, std::shared_ptr<scls::Text_Pattern>>();
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
        // Body of the pattern project creator part
        std::shared_ptr<GUI_Object> a_pattern_project_creator_body;
        // Body of the pattern project file part
        std::shared_ptr<GUI_Object> a_pattern_project_file_body;
        // Body of the pattern project file creator part
        std::shared_ptr<GUI_Object> a_pattern_project_file_creator_body;
        // Body of the pattern project part
        std::shared_ptr<GUI_Object> a_pattern_project_main_body;
        // Footer of the pattern project part
        std::shared_ptr<GUI_Object> a_pattern_project_main_footer;
        // Replica container of the pattern project footer part
        std::shared_ptr<GUI_Scroller> a_pattern_project_main_footer_replica;
        // Navigation of the pattern project part
        std::shared_ptr<GUI_Scroller> a_pattern_project_main_navigation;
        // Body of the replica file creator part
        std::shared_ptr<GUI_Object> a_replica_file_creator_body;
        // Navigation of the replica file creator part
        std::shared_ptr<GUI_Scroller_Choice> a_replica_file_creator_navigation;
        // Body of the replica file edition part
        std::shared_ptr<GUI_Object> a_replica_file_edition_body;
        // Body of the replica file edition variable part
        std::shared_ptr<GUI_Scroller> a_replica_file_edition_variable;
        // Body of the replica file settings part
        std::shared_ptr<GUI_Object> a_replica_file_settings_body;
        // Body of the replica file variable edition part
        std::shared_ptr<GUI_Object> a_replica_file_variable_edition;
        // Body of the replica file variable element edition part
        std::shared_ptr<GUI_Object> a_replica_file_variable_element_edition;
        // Scroller of the replica file variable element edition part
        std::shared_ptr<GUI_Scroller_Choice> a_replica_file_variable_element_edition_scroller;
        // Body of the replica file variable list edition part
        std::shared_ptr<GUI_Object> a_replica_file_variable_list_edition;
        // Scroller of the replica file variable list edition part
        std::shared_ptr<GUI_Scroller_Choice> a_replica_file_variable_list_edition_scroller;
        // Body of the replica global variable edition part
        std::shared_ptr<GUI_Object> a_replica_global_variable_edition_body;
        // Body of the replica project creator part
        std::shared_ptr<GUI_Object> a_replica_project_creator_body;
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
        // Body of the replica text file edition part
        std::shared_ptr<GUI_Object> a_replica_text_file_edition_body;

        // Text / text inputs

        // Name of the pattern project creator
        std::shared_ptr<GUI_Text_Input> a_pattern_project_creator_name;
        // Path of the pattern project creator
        std::shared_ptr<GUI_Text> a_pattern_project_creator_path;
        // Name input of the pattern project creator body
        std::shared_ptr<GUI_Text_Input> a_pattern_project_file_creator_name;
        // Text input of the pattern project body
        std::shared_ptr<GUI_Text_Input> a_pattern_project_file_text_input;
        // Title of the pattern project body
        std::shared_ptr<GUI_Text> a_pattern_project_title;
        // Name of the replica file creator
        std::shared_ptr<GUI_Text_Input> a_replica_file_creator_name;
        // Title of the replica file edition body
        std::shared_ptr<GUI_Text> a_replica_file_edition_title;
        // Content of the replica file variable edition body
        std::shared_ptr<GUI_Text_Input> a_replica_file_variable_edition_content;
        // Title of the replica file variable edition body
        std::shared_ptr<GUI_Text> a_replica_file_variable_edition_title;
        // Title of the replica file variable element edition body
        std::shared_ptr<GUI_Text> a_replica_file_variable_element_edition_title;
        // Title of the replica file variable list edition body
        std::shared_ptr<GUI_Text> a_replica_file_variable_list_edition_title;
        // Text input of the replica global variable edition body
        std::shared_ptr<GUI_Text_Input> a_replica_global_variable_edition_text_input;
        // Name of the replica project creator body
        std::shared_ptr<GUI_Text_Input> a_replica_project_creator_name;
        // Path of the replica project creator body
        std::shared_ptr<GUI_Text> a_replica_project_creator_path;
        // Path of the replica project export body
        std::shared_ptr<GUI_Text> a_replica_project_export_path;
        // Title of the replica project export body
        std::shared_ptr<GUI_Text> a_replica_project_export_title;
        // Title of the replica project body
        std::shared_ptr<GUI_Text> a_replica_project_title;
        // Text input of the replica file edition body
        std::shared_ptr<GUI_Text_Input> a_replica_text_file_edition_text_input;

        // Buttons

        // Button to create a pattern project
        std::shared_ptr<GUI_Text> a_help_create_pattern_project_button;
        // Button to change the page for the creation of a pattern project
        std::shared_ptr<GUI_Text> a_create_pattern_project_path_change_button;
        // Button to validate the creation of a pattern project
        std::shared_ptr<GUI_Text> a_create_pattern_project_validate;
        // Button to open a pattern
        std::shared_ptr<GUI_Text> a_pattern_open_button;
        // Button to validate the creation of a pattern project file
        std::shared_ptr<GUI_Text> a_pattern_project_file_creator_validate;
        // Button to create a new pattern file in the pattern project
        std::shared_ptr<GUI_Text> a_pattern_project_main_footer_new_pattern_file;
        // Button to create a new replica project from the pattern project
        std::shared_ptr<GUI_Text> a_pattern_project_main_footer_new_replica;
        // Button to save a pattern project
        std::shared_ptr<GUI_Text> a_pattern_project_main_footer_save;
        // Button to export a replica
        std::shared_ptr<GUI_Text> a_replica_export_button;
        // Button to validate the creation of a replica file
        std::shared_ptr<GUI_Text> a_replica_file_creator_validate;
        // Button to go to the settings of a replica file
        std::shared_ptr<GUI_Text> a_replica_file_edition_settings;
        // Button to go back in a replica file setting project
        std::shared_ptr<GUI_Text> a_replica_file_settings_back;
        // Button to delete a replica file in a project
        std::shared_ptr<GUI_Text> a_replica_file_settings_delete;
        // Button to validate the creation of a replica file variable element
        std::shared_ptr<GUI_Text> a_replica_file_variable_element_create;
        // Button to delete a replica file variable element
        std::shared_ptr<GUI_Text> a_replica_file_variable_list_element_delete;
        // Button to move downward a replica file variable element
        std::shared_ptr<GUI_Text> a_replica_file_variable_list_element_down;
        // Button to move upward a replica file variable element
        std::shared_ptr<GUI_Text> a_replica_file_variable_list_element_up;
        // Button to open a replica
        std::shared_ptr<GUI_Text> a_replica_open_button;
        // Button to change a path in an creator of a replica project
        std::shared_ptr<GUI_Text> a_replica_project_creator_path_change_button;
        // Button to validate the creation of a replica project
        std::shared_ptr<GUI_Text> a_replica_project_creator_validate;
        // Button to change a path in an export of a replica project
        std::shared_ptr<GUI_Text> a_replica_project_export_path_change_button;
        // Button to add a replica file to a replica project
        std::shared_ptr<GUI_Text> a_replica_project_footer_new_replica_file_button;
        // Pattern button of the replica footer
        std::shared_ptr<GUI_Text> a_replica_project_pattern_button;
        // Button to save a replica project
        std::shared_ptr<GUI_Text> a_replica_project_save_button;
        // Button to validate an export of a replica project
        std::shared_ptr<GUI_Text> a_replica_project_validate_export_button;
	};
}

#endif // SCLS_WORKSPACE_AGATHA
