//******************
//
// scls_workspace_agatha.cpp
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Workspace of SCLS is a software made to handle development with SCLS more easily.
//
// This file contains the source code of scls_workspace_agatha.cpp.
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

#include "../headers/scls_workspace_agatha.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// SCLS_Workspace_Agatha_Page main members
	//
	//*********

	// SCLS_Workspace_Agatha_Page constructor
    SCLS_Workspace_Agatha_Page::SCLS_Workspace_Agatha_Page(_Window_Advanced_Struct* window_struct, std::string name) : GUI_Page(window_struct, name) {

    };

    // Create an object from a type
    std::shared_ptr<GUI_Object> SCLS_Workspace_Agatha_Page::__create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent) {
        if(object_name == "agatha_pattern_project_creator_body") {
            a_pattern_project_creator_body = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_creator_body;
        }
        else if(object_name == "agatha_pattern_project_creator_name") {
            a_pattern_project_creator_name = *parent->new_object<GUI_Text_Input>(object_name);
            return a_pattern_project_creator_name;
        }
        else if(object_name == "agatha_pattern_project_creator_path") {
            a_pattern_project_creator_path = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_creator_path;
        }
        else if(object_name == "agatha_pattern_project_creator_path_change") {
            a_create_pattern_project_path_change_button = *parent->new_object<GUI_Text>(object_name);
            return a_create_pattern_project_path_change_button;
        }
        else if(object_name == "agatha_pattern_project_creator_validate") {
            a_create_pattern_project_validate = *parent->new_object<GUI_Text>(object_name);
            return a_create_pattern_project_validate;
        }
        else if(object_name == "agatha_pattern_project_file_creator_body") {
            a_pattern_project_file_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_pattern_project_file_creator_body;
        }
        else if(object_name == "agatha_pattern_project_file_creator_name") {
            a_pattern_project_file_creator_name = *parent->new_object<GUI_Text_Input>(object_name);
            return a_pattern_project_file_creator_name;
        }
        else if(object_name == "agatha_pattern_project_file_creator_validate") {
            a_pattern_project_file_creator_validate = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_file_creator_validate;
        }
        else if(object_name == "agatha_pattern_project_main_footer_replica") {
            a_pattern_project_main_footer_replica = *parent->new_object<GUI_Scroller>(object_name);
            return a_pattern_project_main_footer_replica;
        }
        else if(object_name == "agatha_pattern_project_main_footer_new_pattern_file") {
            a_pattern_project_main_footer_new_pattern_file = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_main_footer_new_pattern_file;
        }
        else if(object_name == "agatha_pattern_project_main_footer_new_replica") {
            a_pattern_project_main_footer_new_replica = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_main_footer_new_replica;
        }
        else if(object_name == "agatha_pattern_project_main_footer_save") {
            a_pattern_project_main_footer_save = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_main_footer_save;
        }
        else if(object_name == "agatha_replica_file_edition") {
            a_replica_file_edition_body = *parent->new_object<GUI_Object>(object_name);
            return a_replica_file_edition_body;
        }
        else if(object_name == "agatha_replica_file_edition_title") {
            a_replica_file_edition_title = *parent->new_object<GUI_Text>(object_name);
            return a_replica_file_edition_title;
        }
        else if(object_name == "agatha_replica_file_edition_variable") {
            a_replica_file_edition_variable = *parent->new_object<GUI_Scroller>(object_name);
            return a_replica_file_edition_variable;
        }
        else if(object_name == "agatha_replica_file_variable_edition") {
            a_replica_file_variable_edition = *parent->new_object<GUI_Object>(object_name);
            return a_replica_file_variable_edition;
        }
        else if(object_name == "agatha_replica_file_variable_edition_content") {
            a_replica_file_variable_edition_content = *parent->new_object<GUI_Text_Input>(object_name);
            return a_replica_file_variable_edition_content;
        }
        else if(object_name == "agatha_replica_file_variable_edition_title") {
            a_replica_file_variable_edition_title = *parent->new_object<GUI_Text>(object_name);
            return a_replica_file_variable_edition_title;
        }
        else if(object_name == "agatha_replica_project_creator_body") {
            a_replica_project_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_replica_project_creator_body;
        }
        else if(object_name == "agatha_replica_project_creator_name") {
            a_replica_project_creator_name = *parent->new_object<GUI_Text_Input>(object_name);
            return a_replica_project_creator_name;
        }
        else if(object_name == "agatha_replica_project_creator_path") {
            a_replica_project_creator_path = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_creator_path;
        }
        else if(object_name == "agatha_replica_project_creator_path_change") {
            a_replica_project_creator_path_change_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_creator_path_change_button;
        }
        else if(object_name == "agatha_replica_project_creator_validate") {
            a_replica_project_creator_validate = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_creator_validate;
        }
        else if(object_name == "agatha_replica_project_main_footer_pattern") {
            a_replica_project_pattern_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_pattern_button;
        }
        else if(object_name == "file_explorer") {
            a_file_explorer_body = *parent->new_object<GUI_File_Explorer>(object_name);
            return a_file_explorer_body;
        }
        else if(object_name == "global_variable_replica_project_main") {
            a_replica_project_global_variables_body = *parent->new_object<GUI_Scroller>(object_name);
            return a_replica_project_global_variables_body;
        }
        else if(object_name == "help_footer") {
            a_help_footer = *parent->new_object<GUI_Object>(object_name);
            return a_help_footer;
        }
        else if(object_name == "help_footer_create_pattern") {
            a_help_create_pattern_project_button = *parent->new_object<GUI_Text>(object_name);
            return a_help_create_pattern_project_button;
        }
        else if(object_name == "help_footer_open_pattern") {
            a_pattern_open_button = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_open_button;
        }
        else if(object_name == "help_footer_open_replica") {
            a_replica_open_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_open_button;
        }
        else if(object_name == "help_navigation") {
            a_help_navigation = *parent->new_object<GUI_Scroller>(object_name);
            return a_help_navigation;
        }
        else if(object_name == "help_body") {
            a_help_body = *parent->new_object<GUI_Object>(object_name);
            return a_help_body;
        }
        else if(object_name == "pattern_project_file") {
            a_pattern_project_file_body = *parent->new_object<GUI_Object>(object_name);
            return a_pattern_project_file_body;
        }
        else if(object_name == "pattern_project_file_text") {
            a_pattern_project_file_text_input = *parent->new_object<GUI_Text_Input>(object_name);
            return a_pattern_project_file_text_input;
        }
        else if(object_name == "pattern_project_main") {
            a_pattern_project_main_body = *parent->new_object<GUI_Object>(object_name);
            return a_pattern_project_main_body;
        }
        else if(object_name == "pattern_project_main_footer") {
            a_pattern_project_main_footer = *parent->new_object<GUI_Object>(object_name);
            return a_pattern_project_main_footer;
        }
        else if(object_name == "pattern_project_main_navigation") {
            a_pattern_project_main_navigation = *parent->new_object<GUI_Scroller>(object_name);
            return a_pattern_project_main_navigation;
        }
        else if(object_name == "pattern_project_main_title") {
            a_pattern_project_title = *parent->new_object<GUI_Text>(object_name);
            return a_pattern_project_title;
        }
        else if(object_name == "replica_text_file_edition_agatha") {
            a_replica_text_file_edition_body = *parent->new_object<GUI_Object>(object_name);
            return a_replica_text_file_edition_body;
        }
        else if(object_name == "replica_global_variable_edition_agatha") {
            a_replica_global_variable_edition_body = *parent->new_object<GUI_Object>(object_name);
            return a_replica_global_variable_edition_body;
        }
        else if(object_name == "replica_project_export_main_footer") {
            a_replica_export_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_export_button;
        }
        else if(object_name == "replica_project_export_path") {
            a_replica_project_export_path = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_export_path;
        }
        else if(object_name == "replica_project_export_path_change") {
            a_replica_project_export_path_change_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_export_path_change_button;
        }
        else if(object_name == "replica_project_export") {
            a_replica_project_export_body = *parent->new_object<GUI_Object>(object_name);
            return a_replica_project_export_body;
        }
        else if(object_name == "replica_project_export_title") {
            a_replica_project_export_title = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_export_title;
        }
        else if(object_name == "replica_project_main") {
            a_replica_project_main_body = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_main_body;
        }
        else if(object_name == "replica_project_main_footer") {
            a_replica_project_main_footer = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_main_footer;
        }
        else if(object_name == "replica_project_main_navigation") {
            a_replica_project_main_navigation = *parent->new_object<GUI_Scroller>(object_name);
            return a_replica_project_main_navigation;
        }
        else if(object_name == "replica_project_main_title") {
            a_replica_project_title = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_title;
        }
        else if(object_name == "replica_project_save_main_footer") {
            a_replica_project_save_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_save_button;
        }
        else if(object_name == "validate_replica_project_export") {
            a_replica_project_validate_export_button = *parent->new_object<GUI_Text>(object_name);
            return a_replica_project_validate_export_button;
        }
        else if(object_name == "replica_text_file_edition_input_agatha") {
            a_replica_text_file_edition_text_input = *parent->new_object<GUI_Text_Input>(object_name);
            return a_replica_text_file_edition_text_input;
        }
        else if(object_name == "text_replica_global_variable_edition_agatha") {
            a_replica_global_variable_edition_text_input = *parent->new_object<GUI_Text_Input>(object_name);
            return a_replica_global_variable_edition_text_input;
        }
        return GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    };

    //*********
    //
    // Displaying members
    //
    //*********

    // Check the opened page to keep the modification
    void SCLS_Workspace_Agatha_Page::check_opened_page() {
        // Check if a global variable has been modified
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_GLOBAL_VARIABLE_PAGE) {
            currently_displayed_replica_project()->set_global_variable_value(currently_displayed_replica_global_variable(), a_replica_global_variable_edition_text_input.get()->text());
        }

        // Check if a pattern file has been modified
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE) {
            currently_displayed_pattern_project_file()->set_base_text(a_pattern_project_file_text_input.get()->text());

            // Parse the pattern
            currently_displayed_pattern_project()->parse_project();
        }

        // Check if a replica file variable has been modified
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_EDITION_PAGE) {
            currently_displayed_replica_file_variable()->content = a_replica_file_variable_edition_content.get()->text();
        }
    }

    // Display the open pattern page
    void SCLS_Workspace_Agatha_Page::display_open_pattern() {
        hide_all();
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(true);
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(true);
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(true);

        // Set the current state
        a_current_state.current_file_chosen = SCLS_WORKSPACE_AGATHA_OPEN_PATTERN;
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE;
        a_file_explorer_body.get()->set_current_user_document_directory();
    }

    // Display the project pattern page
    void SCLS_Workspace_Agatha_Page::display_pattern_project() {
        hide_all();
        if(a_pattern_project_main_body.get() != 0) a_pattern_project_main_body.get()->set_visible(true);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(true);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_MAIN_PAGE;
        load_pattern_project_navigation(); load_pattern_project_replica();
        if(currently_displayed_pattern_project() == 0) a_pattern_project_title.get()->set_text("Pas de projets disponibles");
        else a_pattern_project_title.get()->set_text("Projet : \"" + currently_displayed_pattern_project()->name() + "\"");
    }

    // Display the project pattern creator page
    void SCLS_Workspace_Agatha_Page::display_pattern_project_creator() {
        hide_all();
        if(a_pattern_project_creator_body.get() != 0) a_pattern_project_creator_body.get()->set_visible(true);
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(true);
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PAGE;
        if(a_pattern_project_creator_path.get() != 0) {
            if(currently_displayed_pattern_project_creator_path() == "") {
                a_pattern_project_creator_path.get()->set_text(scls::to_utf_8_code_point("Choisissez un chemin d'accés"));
            } else {
                a_pattern_project_creator_path.get()->set_text(scls::to_utf_8_code_point("Chemin d'accés : ") + currently_displayed_pattern_project_creator_path());
            }
        }
    }

    // Display the project pattern creator path change page
    void SCLS_Workspace_Agatha_Page::display_pattern_project_creator_path_change() {
        hide_all();
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(true);
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(true);
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(true);

        // Set the current state
        a_current_state.current_file_chosen = SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PATH;
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE;
        a_file_explorer_body.get()->set_current_user_document_directory();
    }

    // Display the project pattern file page
    void SCLS_Workspace_Agatha_Page::display_pattern_project_file() {
        hide_all();
        if(a_pattern_project_file_body.get() != 0) a_pattern_project_file_body.get()->set_visible(true);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(true);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE;
        load_pattern_project_navigation(); load_pattern_project_replica();
        if(currently_displayed_pattern_project_file() == 0) a_pattern_project_file_text_input.get()->set_text("Pas de fichiers disponibles");
        else a_pattern_project_file_text_input.get()->set_text(currently_displayed_pattern_project_file()->base_text());
    }

    // Display the project pattern file cretor page
    void SCLS_Workspace_Agatha_Page::display_pattern_project_file_creator() {
        hide_all();
        if(a_pattern_project_file_creator_body.get() != 0) a_pattern_project_file_creator_body.get()->set_visible(true);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(true);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_CREATOR_PAGE;
        load_pattern_project_navigation(); load_pattern_project_replica();
    }

    // Display the project file dition page
    void SCLS_Workspace_Agatha_Page::display_replica_file_edition() {
        hide_all();
        if(a_replica_file_edition_body.get() != 0) a_replica_file_edition_body.get()->set_visible(true);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(true);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_FILE_EDITION_PAGE;
        load_replica_file_edition_variable();
        if(a_replica_file_edition_title.get() != 0) {
            if(currently_displayed_replica_file() == 0) {
                a_replica_file_edition_title.get()->set_text(to_utf_8_code_point("Pas de fichier à afficher"));
            }
            else {
                a_replica_file_edition_title.get()->set_text(to_utf_8_code_point("Fichier réplique : ") + currently_displayed_replica_file()->internal_path);
            }
        }
    }

    // Display the project file variable edition page
    void SCLS_Workspace_Agatha_Page::display_replica_file_variable_edition() {
        hide_all();
        if(a_replica_file_variable_edition.get() != 0) a_replica_file_variable_edition.get()->set_visible(true);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(true);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_EDITION_PAGE;
        if(a_replica_file_variable_edition_title.get() != 0) {
            if(currently_displayed_replica_file_variable() == 0) {
                a_replica_file_variable_edition_content.get()->set_text("");
                a_replica_file_variable_edition_title.get()->set_text(to_utf_8_code_point("Pas de variable à afficher"));
            }
            else {
                a_replica_file_variable_edition_content.get()->set_text(currently_displayed_replica_file_variable()->content);
                a_replica_file_variable_edition_title.get()->set_text(to_utf_8_code_point("Variable : " + currently_displayed_replica_file_variable()->name));
            }
        }
    }

    // Display the project replica global variable page
    void SCLS_Workspace_Agatha_Page::display_replica_global_variable() {
        hide_all();
        if(a_replica_global_variable_edition_body.get() != 0) a_replica_global_variable_edition_body.get()->set_visible(true);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(true);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_GLOBAL_VARIABLE_PAGE;
        a_replica_global_variable_edition_text_input.get()->set_text(currently_displayed_replica_project()->global_variable_value(currently_displayed_replica_global_variable()));
    }

    // Display the open replica page
    void SCLS_Workspace_Agatha_Page::display_replica_open() {
        hide_all();
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(true);
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(true);
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(true);

        // Set the current state
        a_current_state.current_file_chosen = SCLS_WORKSPACE_AGATHA_OPEN_REPLICA;
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE;
        a_file_explorer_body.get()->set_current_user_document_directory();
    }

    // Display the project replica page
    void SCLS_Workspace_Agatha_Page::display_replica_project() {
        hide_all();
        if(a_replica_project_main_body.get() != 0) a_replica_project_main_body.get()->set_visible(true);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(true);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        load_global_variables_project_navigation();
        load_replica_project_navigation();
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_MAIN_PAGE;
        if(currently_displayed_replica_project() == 0) a_replica_project_title.get()->set_text("Pas de projets disponibles");
        else a_replica_project_title.get()->set_text("Projet : \"" + currently_displayed_replica_project()->name() + "\"");
    }

    // Display the replica project creator page
    void SCLS_Workspace_Agatha_Page::display_replica_project_creator() {
        hide_all();
        if(a_replica_project_creator_body.get() != 0) a_replica_project_creator_body.get()->set_visible(true);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(true);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PAGE;
        if(a_replica_project_creator_path.get() != 0) {
            if(currently_displayed_replica_project_creator_path() == "") {
                a_replica_project_creator_path.get()->set_text(scls::to_utf_8_code_point("Choisissez un chemin d'accés"));
            } else {
                a_replica_project_creator_path.get()->set_text(scls::to_utf_8_code_point("Chemin d'accés : ") + currently_displayed_replica_project_creator_path());
            }
        }
    }

    // Display the replica project creator path change page
    void SCLS_Workspace_Agatha_Page::display_replica_project_creator_path_change() {
        hide_all();
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(true);
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(true);
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(true);

        // Set the current state
        a_current_state.current_file_chosen = SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PATH;
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE;
        a_file_explorer_body.get()->set_current_user_document_directory();
    }

    // Display the project replica export page
    void SCLS_Workspace_Agatha_Page::display_replica_project_export() {
        hide_all();
        if(a_replica_project_export_body.get() != 0) a_replica_project_export_body.get()->set_visible(true);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(true);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PAGE;
        if(currently_displayed_replica_project() == 0) a_replica_project_export_title.get()->set_text("Pas de projets à exporter");
        else a_replica_project_export_title.get()->set_text("Exporter \"" + currently_displayed_replica_project()->name() + "\"");
        if(currently_displayed_export_path() == "") {a_replica_project_export_path.get()->set_text(to_utf_8_code_point("Veuillez choisir un chemin d'accés"));}
        else { a_replica_project_export_path.get()->set_text(to_utf_8_code_point("Chemin d'accés : " + currently_displayed_export_path())); }
    }

    // Display the project replica export path change page
    void SCLS_Workspace_Agatha_Page::display_replica_project_export_path_change() {
        hide_all();
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(true);
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(true);
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(true);

        // Set the current state
        a_current_state.current_file_chosen = SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PATH;
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE;
        a_file_explorer_body.get()->set_current_user_document_directory();
    }

    // Display the project file dition page
    void SCLS_Workspace_Agatha_Page::display_replica_text_file_edition() {
        hide_all();
        if(a_replica_text_file_edition_body.get() != 0) a_replica_text_file_edition_body.get()->set_visible(true);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(true);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_REPLICA_TEXT_FILE_EDITION_PAGE;
        if(a_replica_text_file_edition_text_input.get() != 0) {
            if(currently_displayed_replica_file() == 0) {
                a_replica_text_file_edition_text_input.get()->set_text("Pas de fichiers à afficher");
            }
            else {
                a_replica_text_file_edition_text_input.get()->set_text(currently_displayed_replica_file()->content_out_pattern);
            }
        }
    }

    // Hide all the agatha part
    void SCLS_Workspace_Agatha_Page::hide_all() {
        // Hide all the bodies
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(false);
        if(a_help_body.get() != 0) a_help_body.get()->set_visible(false);
        if(a_pattern_project_creator_body.get() != 0) a_pattern_project_creator_body.get()->set_visible(false);
        if(a_pattern_project_file_body.get() != 0) a_pattern_project_file_body.get()->set_visible(false);
        if(a_pattern_project_file_creator_body.get() != 0) a_pattern_project_file_creator_body.get()->set_visible(false);
        if(a_pattern_project_main_body.get() != 0) a_pattern_project_main_body.get()->set_visible(false);
        if(a_replica_file_edition_body.get() != 0) a_replica_file_edition_body.get()->set_visible(false);
        if(a_replica_file_variable_edition.get() != 0) a_replica_file_variable_edition.get()->set_visible(false);
        if(a_replica_text_file_edition_body.get() != 0) a_replica_text_file_edition_body.get()->set_visible(false);
        if(a_replica_global_variable_edition_body.get() != 0) a_replica_global_variable_edition_body.get()->set_visible(false);
        if(a_replica_project_creator_body.get() != 0) a_replica_project_creator_body.get()->set_visible(false);
        if(a_replica_project_export_body.get() != 0) a_replica_project_export_body.get()->set_visible(false);
        if(a_replica_project_main_body.get() != 0) a_replica_project_main_body.get()->set_visible(false);

        // Hide all the footers
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(false);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(false);
        if(a_replica_project_main_footer.get() != 0) a_replica_project_main_footer.get()->set_visible(false);

        // Hide all the navigations
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(false);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(false);
        if(a_replica_project_main_navigation.get() != 0) a_replica_project_main_navigation.get()->set_visible(false);

        check_opened_page();
    }

    //*********
    //
    // Event members
    //
    //*********

    // Check the events for the help pattern project creator
    void SCLS_Workspace_Agatha_Page::check_help_creator_pattern_project_events() {
        if(a_create_pattern_project_path_change_button.get() != 0 && a_create_pattern_project_path_change_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Change the path of the new pattern project
            display_pattern_project_creator_path_change();
        }

        if(a_create_pattern_project_validate.get() != 0 && a_create_pattern_project_validate.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Validate the creation of the pattern project
            if(currently_displayed_pattern_project_creator_path() != "" && currently_displayed_pattern_project_creator_name() != "")  {
                a_current_state.currently_displayed_pattern_project = create_pattern_project();
                display_pattern_project();
            }
        }
    }

    // Check the events for the help footer
    void SCLS_Workspace_Agatha_Page::check_help_footer_events() {
        // Check the pattern open button
        if(a_pattern_open_button.get() != 0 && a_pattern_open_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_open_pattern();
        }
        else if(a_help_create_pattern_project_button.get() != 0 && a_help_create_pattern_project_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_pattern_project_creator();
        }
        else if(a_replica_open_button.get() != 0 && a_replica_open_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_replica_open();
        }
    }

    // Check the events for the file explorer
    void SCLS_Workspace_Agatha_Page::check_file_explorer_events() {
        // Check if a file is chosen
        if(a_file_explorer_body.get() != 0 && a_file_explorer_body.get()->file_chosen()) {
            std::string chose_file = a_file_explorer_body.get()->currently_selected_path();

            // Display the good page
            if(a_current_state.current_file_chosen == SCLS_WORKSPACE_AGATHA_OPEN_PATTERN) {
                // Load the pattern project
                std::shared_ptr<Pattern_Project> project_loaded = load_pattern_project(chose_file);
                a_current_state.currently_displayed_pattern_project = project_loaded;
                display_pattern_project();
            }
            else if(a_current_state.current_file_chosen == SCLS_WORKSPACE_AGATHA_OPEN_REPLICA) {
                // Load the replica project
                std::shared_ptr<Replica_Project> project_loaded = load_replica_project(chose_file);
                a_current_state.currently_displayed_replica_project = project_loaded;
                display_replica_project();
            }
            else if(a_current_state.current_file_chosen == SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PATH) {
                // Change the pattern project creation path
                a_current_state.currently_displayed_pattern_project_creator_path = chose_file;
                display_pattern_project_creator();
            }
            else if(a_current_state.current_file_chosen == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PATH) {
                // Change the replica project export path
                a_current_state.currently_displayed_replica_project_creator_path = chose_file;
                display_replica_project_creator();
            }
            else if(a_current_state.current_file_chosen == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PATH) {
                // Change the replica project export path
                a_current_state.currently_displayed_export_path = chose_file;
                display_replica_project_export();
            }
        }
    }

    // Check the events for the pattern project file creator page
    void SCLS_Workspace_Agatha_Page::check_pattern_project_file_creator() {
        if(a_pattern_project_file_creator_validate.get() != 0 && a_pattern_project_file_creator_validate.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            if(currently_displayed_pattern_project_file_creator_name() != "") {
                // Validate the creation of the file
                a_current_state.currently_displayed_pattern_project_file = create_pattern_project_file();
                display_pattern_project_file();
            }
        }
    }

    // Check the events for the pattern project footer page
    void SCLS_Workspace_Agatha_Page::check_pattern_project_footer_events() {
        if(a_pattern_project_main_footer_save.get() != 0 && a_pattern_project_main_footer_save.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            if(currently_displayed_pattern_project() != 0) {
                // Save the current pattern project
                save_pattern_project();
            }
        }

        if(a_pattern_project_main_footer_new_pattern_file.get() != 0 && a_pattern_project_main_footer_new_pattern_file.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            if(currently_displayed_pattern_project() != 0) {
                // Create a new file in the current pattern project
                display_pattern_project_file_creator();
            }
        }

        if(a_pattern_project_main_footer_new_replica.get() != 0 && a_pattern_project_main_footer_new_replica.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            if(currently_displayed_pattern_project() != 0) {
                // Create a new replica from the current pattern project
                display_replica_project_creator();
            }
        }

        std::map<std::shared_ptr<GUI_Text>, std::shared_ptr<Replica_Project>>::iterator it = a_replica_project_by_pattern_footer_buttons.begin();
        for(;it!=a_replica_project_by_pattern_footer_buttons.end();it++) {
            if(it->first.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                // A replica button is clicked
                save_pattern_project();
                a_current_state.currently_displayed_replica_project = it->second;
                display_replica_project(); break;
            }
        }
    }

    // Check the events for the pattern project main page
    void SCLS_Workspace_Agatha_Page::check_pattern_project_main_events() {}

    // Check the events for the pattern project navigation page
    void SCLS_Workspace_Agatha_Page::check_pattern_project_navigation_events() {
        // Check each navigations buttons
        for(int i = 0;i<static_cast<int>(a_current_state.pattern_project_navigation_buttons.size());i++) {
            std::shared_ptr<GUI_Text> current_button = a_current_state.pattern_project_navigation_buttons[i];
            if(current_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                current_button.reset();
                if(i == 0) {
                    // Load the home page
                    display_pattern_project();
                }
                else if(i - 1 < a_current_state.pattern_project_navigation_files.size()) {
                    // Display a file
                    std::shared_ptr<Text_Pattern> chosen_pattern_file = a_current_state.pattern_project_navigation_files[i - 1];
                    a_current_state.currently_displayed_pattern_project_file = chosen_pattern_file;
                    display_pattern_project_file();
                }
                break;
            }
        }
    }

    // Check the events for the replica file edition page
    void SCLS_Workspace_Agatha_Page::check_replica_file_edition_events() {
        for(int i = 0;i<static_cast<int>(a_replica_file_edition_variable_buttons.size());i++) {
            if(a_replica_file_edition_variable_buttons[i].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                // Show the pattern variable edition page
                a_current_state.currently_displayed_replica_file_variable = a_replica_file_edition_variable_by_buttons[a_replica_file_edition_variable_buttons[i].get()];
                display_replica_file_variable_edition();
            }
        }
    }

    // Check the events for the replica project creator page
    void SCLS_Workspace_Agatha_Page::check_replica_project_creator_events() {
        if(a_replica_project_creator_path_change_button.get() != 0 && a_replica_project_creator_path_change_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Change the path of the new pattern project
            display_replica_project_creator_path_change();
        }

        if(a_replica_project_creator_validate.get() != 0 && a_replica_project_creator_validate.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Validate the creation of the pattern project
            if(currently_displayed_replica_project_creator_path() != "" && currently_displayed_replica_project_creator_name() != "")  {
                a_current_state.currently_displayed_replica_project = create_replica_project();
                display_replica_project();
            }
        }
    }

    // Check the events for the replica project page
    void SCLS_Workspace_Agatha_Page::check_replica_project_events() {
        for(int i = 0;i<static_cast<int>(a_replica_project_global_variables_navigation_buttons.size());i++) {
            if(a_replica_project_global_variables_navigation_buttons[i].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                // Show the global variable edition page
                a_current_state.currently_displayed_replica_global_variable = a_replica_project_global_variables_navigation_buttons[i].get()->text();
                display_replica_global_variable();
            }
        }
    }

    // Check the events for the replica project export page
    void SCLS_Workspace_Agatha_Page::check_replica_project_export_events() {
        if(a_replica_project_export_path_change_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Change the path of the project
            display_replica_project_export_path_change();
        }

        if(a_replica_project_validate_export_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            if(currently_displayed_export_path() != "") {
                // Export the project
                export_replica_project();
            }
        }
    }

    // Check the events for the replica project footer page
    void SCLS_Workspace_Agatha_Page::check_replica_project_footer_events() {
        if(a_replica_project_save_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Save the replica project
            save_replica_project();
        }

        if(a_replica_export_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Export the replica project
            display_replica_project_export();
        }

        if(a_replica_project_pattern_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Open the pattern of the replica project
            a_current_state.currently_displayed_pattern_project = currently_displayed_replica_project()->attached_pattern_shared_ptr();
            display_pattern_project();
        }
    }

    // Check the events for the replica project navigation page
    void SCLS_Workspace_Agatha_Page::check_replica_project_navigation_events() {
        for(int i = 0;i<static_cast<int>(a_replica_project_navigation_buttons.size());i++) {
            if(a_replica_project_navigation_buttons[i].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                if(i == 0) {
                    // Show the home of the replica project
                    display_replica_project();
                }
                else {
                    // Show a replica file edition
                    a_current_state.currently_displayed_replica_file = a_replica_file_by_replica_project_navigation_buttons[a_replica_project_navigation_buttons[i].get()];
                    if(currently_displayed_replica_file()->pattern == 0) {
                        display_replica_text_file_edition();
                    }
                    else {
                        display_replica_file_edition();
                    }
                }
            }
        }
    }

    // Update the events of the page
    void SCLS_Workspace_Agatha_Page::update_event() {
        GUI_Page::update_event();

        // Help body page
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_HELP_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PAGE) check_help_footer_events();

        // Help pattern project body page
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_CREATE_PATTERN_PROJECT_PAGE) check_help_creator_pattern_project_events();

        // File explorer page
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE) check_file_explorer_events();

        // Pattern project footer
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_MAIN_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_CREATOR_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PAGE) check_pattern_project_footer_events();

        // Pattern project file creator
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_CREATOR_PAGE) check_pattern_project_file_creator();

        // Pattern project navigation
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_MAIN_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_CREATOR_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PAGE) check_pattern_project_navigation_events();

        // Replica file
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_FILE_EDITION_PAGE) check_replica_file_edition_events();

        // Replica project creator
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_CREATOR_PAGE) check_replica_project_creator_events();

        // Replica project export main
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PAGE) check_replica_project_export_events();

        // Replica project main
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_MAIN_PAGE) check_replica_project_events();

        // Replica project navigation
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_FILE_EDITION_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_EDITION_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_GLOBAL_VARIABLE_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_MAIN_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_TEXT_FILE_EDITION_PAGE) check_replica_project_navigation_events();

        // Replica project footer
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_FILE_EDITION_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_FILE_VARIABLE_EDITION_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_GLOBAL_VARIABLE_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_EXPORT_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_PROJECT_MAIN_PAGE ||
           a_current_state.current_page == SCLS_WORKSPACE_AGATHA_REPLICA_TEXT_FILE_EDITION_PAGE) check_replica_project_footer_events();
    }

    //*********
    //
    // Pattern handling
    //
    //*********

    // Create a pattern project
    std::shared_ptr<Pattern_Project> SCLS_Workspace_Agatha_Page::create_pattern_project() {
        // Create the new pattern project
        std::string real_path = currently_displayed_pattern_project_creator_path() + "/" + currently_displayed_pattern_project_creator_name() + "/";
        if(!std::filesystem::exists(real_path)) std::filesystem::create_directory(real_path);
        std::shared_ptr<Pattern_Project> new_project = std::make_shared<Pattern_Project>(currently_displayed_pattern_project_creator_name(), real_path);
        a_loaded_patterns.push_back(new_project);

        return new_project;
    }

    // Create a pattern project file
    std::shared_ptr<Text_Pattern> SCLS_Workspace_Agatha_Page::create_pattern_project_file() {
        // Create the text pattern
        std::shared_ptr<Text_Pattern> new_pattern; if(currently_displayed_pattern_project() == 0) return new_pattern;
        new_pattern = *currently_displayed_pattern_project()->new_pattern(currently_displayed_pattern_project_file_creator_name(), "");

        return new_pattern;
    }

    // Create a replica project from this pattern project
    std::shared_ptr<Replica_Project> SCLS_Workspace_Agatha_Page::create_replica_project() {
        // Create the new replica project
        std::string real_path = currently_displayed_replica_project_creator_path() + "/" + currently_displayed_replica_project_creator_name() + "/";
        if(!std::filesystem::exists(real_path)) std::filesystem::create_directory(real_path);
        std::shared_ptr<Replica_Project> new_project = std::make_shared<Replica_Project>(currently_displayed_replica_project_creator_name(), real_path, a_current_state.currently_displayed_pattern_project);
        a_loaded_replicas.push_back(new_project);

        return new_project;
    }

    // Loads an existing pattern and returns it
    std::shared_ptr<Pattern_Project> SCLS_Workspace_Agatha_Page::load_pattern_project(std::string path) {
        std::shared_ptr<Pattern_Project> to_return;

        // Check some assert
        std::filesystem::path pattern_path = std::filesystem::path(path);
        path = pattern_path.generic_string();
        if(!std::filesystem::exists(path) || std::filesystem::is_directory(path)) return to_return;

        // Load the project
        to_return.reset(Pattern_Project::load_sda_0_1(path));
        return to_return;
    }

    // Loads the buttons in the pattern project navigation
    void SCLS_Workspace_Agatha_Page::load_pattern_project_navigation() {
        // Reset the navigation
        unload_pattern_project_navigation();

        if(currently_displayed_pattern_project() != 0) {
            // Create the first home button
            std::shared_ptr<GUI_Text> home_button = *a_pattern_project_main_navigation.get()->new_object<GUI_Text>("pattern_project_home_button");
            home_button.get()->set_font_size(40);
            home_button.get()->set_height_in_pixel(50);
            home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            home_button.get()->set_text("Accueil");
            home_button.get()->set_texture_alignment(Alignment_Texture::T_Fit);
            home_button.get()->set_width_in_scale(1);
            home_button.get()->set_x_in_scale(0);
            home_button.get()->set_y_in_scale(0);
            a_current_state.pattern_project_navigation_buttons.push_back(home_button);

            // Create the buttons
            std::vector<std::shared_ptr<Text_Pattern>> patterns = currently_displayed_pattern_project()->patterns();
            for(int i = 0;i<static_cast<int>(patterns.size());i++) {
                // Create the button
                home_button = *a_pattern_project_main_navigation.get()->new_object<GUI_Text>("pattern_project_button_" + std::to_string(i));
                home_button.get()->set_font_size(40);
                home_button.get()->set_height_in_pixel(50);
                home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                home_button.get()->set_text(patterns[i].get()->name().to_std_string());
                home_button.get()->set_texture_alignment(Alignment_Texture::T_Fit);
                home_button.get()->set_width_in_scale(1);
                home_button.get()->set_x_in_scale(0);
                a_current_state.pattern_project_navigation_buttons.push_back(home_button);
                a_current_state.pattern_project_navigation_files.push_back(patterns[i]);
            }

            // Place the buttons
            std::shared_ptr<GUI_Text> last_button = a_current_state.pattern_project_navigation_buttons[a_current_state.pattern_project_navigation_buttons.size() - 1];
            last_button.get()->attach_bottom_in_parent();
            for(int i = 1;i<static_cast<int>(a_current_state.pattern_project_navigation_buttons.size());i++) {
                unsigned int current_i = a_current_state.pattern_project_navigation_buttons.size() - (i + 1);
                a_current_state.pattern_project_navigation_buttons[current_i].get()->attach_top_of_object_in_parent(last_button);
                last_button = a_current_state.pattern_project_navigation_buttons[current_i];
            }

            // Finalize the creation
            a_pattern_project_main_navigation.get()->check_scroller();
        }
    }

    // Loads the buttons in the pattern project replicas
    void SCLS_Workspace_Agatha_Page::load_pattern_project_replica() {
        unload_pattern_project_replica();

        if(currently_displayed_pattern_project() != 0) {
            // Create the buttons
            std::shared_ptr<GUI_Text> home_button;
            std::vector<std::shared_ptr<Replica_Project>>& replicas = a_loaded_replicas;
            for(int i = 0;i<static_cast<int>(replicas.size());i++) {
                if(replicas[i].get()->attached_pattern() != currently_displayed_pattern_project()) {continue;}

                // Create the button
                home_button = *a_pattern_project_main_footer_replica.get()->new_object<GUI_Text>("pattern_project_replica_button_" + std::to_string(i));
                home_button.get()->set_font_size(40);
                home_button.get()->set_height_in_pixel(50);
                home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                home_button.get()->set_text(replicas[i].get()->name());
                home_button.get()->set_texture_alignment(Alignment_Texture::T_Fit);
                home_button.get()->set_width_in_scale(1);
                home_button.get()->set_x_in_scale(0);
                a_replica_project_by_pattern_footer_buttons[home_button] = replicas[i];
            }

            if(a_replica_project_by_pattern_footer_buttons.size() > 0) {
                // Place the buttons
                std::map<std::shared_ptr<GUI_Text>, std::shared_ptr<Replica_Project>>::iterator it = a_replica_project_by_pattern_footer_buttons.begin();
                std::shared_ptr<GUI_Text> last_button = it->first; it++;
                last_button.get()->attach_bottom_in_parent();
                for(;it!=a_replica_project_by_pattern_footer_buttons.end();it++) {
                    it->first.get()->attach_top_of_object_in_parent(last_button);
                    last_button = it->first;
                }
            }

            // Finalize the creation
            a_pattern_project_main_footer_replica.get()->check_scroller();
        }
    }

    // Saves the current pattern project
    void SCLS_Workspace_Agatha_Page::save_pattern_project() {
        if(currently_displayed_pattern_project() != 0) {
            check_opened_page();
            currently_displayed_pattern_project()->save_sda_0_1();
        }
    }

    // Unloads the buttons in the pattern project navigation
    void SCLS_Workspace_Agatha_Page::unload_pattern_project_navigation() {
        a_current_state.pattern_project_navigation_files.clear();
        a_current_state.pattern_project_navigation_buttons.clear();
        a_pattern_project_main_navigation.get()->reset();
    }

    //*********
    //
    // Replica handling
    //
    //*********

    // Exports the current replica project
    void SCLS_Workspace_Agatha_Page::export_replica_project() {
        // Export the project
        currently_displayed_replica_project()->export_project(currently_displayed_export_path(), window_struct()->text_image_generator());

        // Reset export datas
        a_current_state.currently_displayed_export_path = "";
        display_replica_project();
    }

    // Loads the global variables buttons to navigate in the project
    void SCLS_Workspace_Agatha_Page::load_global_variables_project_navigation() {
        unload_global_variables_project_navigation();

        // Load each global variables
        if(currently_displayed_replica_project() != 0) {
            // Create the buttons
            std::vector<std::shared_ptr<Pattern_Variable>>& global_variables = currently_displayed_replica_project()->global_variables();
            std::shared_ptr<GUI_Text> home_button;
            for(std::vector<std::shared_ptr<Pattern_Variable>>::iterator it = global_variables.begin();it!=global_variables.end();it++) {
                // Create the button
                home_button = *a_replica_project_global_variables_body.get()->new_object<GUI_Text>("global_variable_replica_project_" + it->get()->name);
                home_button.get()->set_font_size(40);
                home_button.get()->set_height_in_pixel(50);
                home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                home_button.get()->set_text(it->get()->name);
                home_button.get()->set_width_in_scale(1);
                home_button.get()->set_x_in_scale(0);
                a_replica_project_global_variables_navigation_buttons.push_back(home_button);
            }

            if(a_replica_project_global_variables_navigation_buttons.size() > 0) {
                // Place the buttons
                std::shared_ptr<GUI_Text> last_button = a_replica_project_global_variables_navigation_buttons[a_replica_project_global_variables_navigation_buttons.size() - 1];
                last_button.get()->attach_bottom_in_parent();
                for(int i = 1;i<static_cast<int>(a_replica_project_global_variables_navigation_buttons.size());i++) {
                    unsigned int current_i = a_replica_project_global_variables_navigation_buttons.size() - (i + 1);
                    a_replica_project_global_variables_navigation_buttons[current_i].get()->attach_top_of_object_in_parent(last_button);
                    last_button = a_replica_project_global_variables_navigation_buttons[current_i];
                }
            }

            // Finalize the creation
            a_replica_project_global_variables_body.get()->check_scroller();
        }
    }

    // Loads the button for the variable in a replica file project
    void SCLS_Workspace_Agatha_Page::load_replica_file_edition_variable() {
        unload_replica_file_edition_variable();

        // Create each buttons
        if(currently_displayed_replica_file() != 0) {
            // Create the buttons
            const std::vector<std::shared_ptr<Pattern_Variable>>& variables = currently_displayed_replica_file()->pattern->variables();
            std::shared_ptr<GUI_Text> current_button;
            for(int i = 0;i<static_cast<int>(variables.size());i++) {
                // Create the button
                if(variables[i].get() == 0 || variables[i].get()->global) continue;
                std::shared_ptr<Replica_File_Variable> current_variable = currently_displayed_replica_file()->variable_by_name(variables[i].get()->name);
                current_button = *a_replica_file_edition_variable.get()->new_object<GUI_Text>("replica_file_edition_variable_button_" + std::to_string(i));
                current_button.get()->set_font_size(40);
                current_button.get()->set_height_in_pixel(50);
                current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                current_button.get()->set_text(current_variable.get()->name);
                current_button.get()->set_width_in_scale(1);
                current_button.get()->set_x_in_scale(0);
                a_replica_file_edition_variable_buttons.push_back(current_button);
                a_replica_file_edition_variable_by_buttons[current_button.get()] = current_variable;
            }

            // Place the buttons
            std::shared_ptr<GUI_Text> last_button = a_replica_file_edition_variable_buttons[a_replica_file_edition_variable_buttons.size() - 1];
            last_button.get()->attach_bottom_in_parent();
            for(int i = 1;i<static_cast<int>(a_replica_file_edition_variable_buttons.size());i++) {
                unsigned int current_i = a_replica_file_edition_variable_buttons.size() - (i + 1);
                a_replica_file_edition_variable_buttons[current_i].get()->attach_top_of_object_in_parent(last_button);
                last_button = a_replica_file_edition_variable_buttons[current_i];
            }

            // Finalize the creation
            a_replica_file_edition_variable.get()->check_scroller();
        }
    }

    // Loads an existing replica and returns it
    std::shared_ptr<Replica_Project> SCLS_Workspace_Agatha_Page::load_replica_project(std::string path) {
        std::shared_ptr<Replica_Project> to_return = loaded_replica_by_path_shared_ptr(path);
        if(to_return.get() != 0) return to_return;

        // Check some assert
        if(!std::filesystem::exists(path) || std::filesystem::is_directory(path)) return to_return;

        // Get the pattern
        std::filesystem::path pattern_path = std::filesystem::path(Replica_Project::replica_attached_pattern_from_path_sda_0_2(path));
        std::string pattern_name = pattern_path.generic_string();
        std::shared_ptr<Pattern_Project> pattern_to_use = loaded_pattern_by_path(pattern_name);
        // Load the patter if necessary
        if(pattern_to_use.get() == 0) pattern_to_use = load_pattern_project(pattern_name);
        if(pattern_to_use.get() == 0) return to_return;

        // Load the project
        to_return.reset(Replica_Project::load_sda_0_2(path, pattern_to_use));
        a_loaded_replicas.push_back(to_return);
        return to_return;
    }

    // Loads the button to navigate in the project
    void SCLS_Workspace_Agatha_Page::load_replica_project_navigation() {
        unload_replica_project_navigation();

        // Load each navigation buttons
        if(currently_displayed_replica_project() != 0) {
            // Create the first home button
            std::shared_ptr<GUI_Text> home_button = *a_replica_project_main_navigation.get()->new_object<GUI_Text>("replica_file_home_button");
            home_button.get()->set_font_size(40);
            home_button.get()->set_height_in_pixel(50);
            home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            home_button.get()->set_text(to_utf_8_code_point("Accueil de la réplique"));
            home_button.get()->set_texture_alignment(Alignment_Texture::T_Fit);
            home_button.get()->set_width_in_scale(1);
            home_button.get()->set_x_in_scale(0);
            home_button.get()->set_y_in_scale(0);
            a_replica_project_navigation_buttons.push_back(home_button);

            // Create the buttons
            std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> replicas = currently_displayed_replica_project()->replica_files_sorted_by_path();
            for(int i = 0;i<static_cast<int>(replicas.get()->size());i++) {
                // Create the button
                home_button = *a_replica_project_main_navigation.get()->new_object<GUI_Text>("replica_file_button_" + std::to_string(i));
                home_button.get()->set_font_size(40);
                home_button.get()->set_height_in_pixel(50);
                home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                home_button.get()->set_text(replicas.get()->at(i).get()->internal_path);
                home_button.get()->set_texture_alignment(Alignment_Texture::T_Fit);
                home_button.get()->set_width_in_scale(1);
                home_button.get()->set_x_in_scale(0);
                a_replica_file_by_replica_project_navigation_buttons[home_button.get()] = replicas.get()->at(i);
                a_replica_project_navigation_buttons.push_back(home_button);
            }

            // Place the buttons
            std::shared_ptr<GUI_Text> last_button = a_replica_project_navigation_buttons[a_replica_project_navigation_buttons.size() - 1];
            last_button.get()->attach_bottom_in_parent();
            for(int i = 1;i<static_cast<int>(a_replica_project_navigation_buttons.size());i++) {
                unsigned int current_i = a_replica_project_navigation_buttons.size() - (i + 1);
                a_replica_project_navigation_buttons[current_i].get()->attach_top_of_object_in_parent(last_button);
                last_button = a_replica_project_navigation_buttons[current_i];
            }

            // Finalize the creation
            a_replica_project_main_navigation.get()->check_scroller();
        }
    }

    // Save the current replica project
    void SCLS_Workspace_Agatha_Page::save_replica_project() {
        if(currently_displayed_replica_project() != 0) {
            check_opened_page();
            currently_displayed_replica_project()->save_sda_0_2();
        }
    }
}
