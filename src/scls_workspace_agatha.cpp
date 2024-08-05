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
        if(object_name == "file_explorer") {
            a_file_explorer_body = *parent->new_object<GUI_File_Explorer>(object_name);
            return a_file_explorer_body;
        }
        else if(object_name == "help_footer") {
            a_help_footer = *parent->new_object<GUI_Object>(object_name);
            return a_help_footer;
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
        return GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    };

    //*********
    //
    // Displaying members
    //
    //*********

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
        load_pattern_project_navigation();
        if(currently_displayed_pattern_project() == 0) a_pattern_project_title.get()->set_text("Pas de projets disponibles");
        else a_pattern_project_title.get()->set_text("Projet : \"" + currently_displayed_pattern_project()->name() + "\"");
    }

    // Display the project pattern file page
    void SCLS_Workspace_Agatha_Page::display_pattern_project_file() {
        hide_all();
        if(a_pattern_project_file_body.get() != 0) a_pattern_project_file_body.get()->set_visible(true);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(true);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(true);

        // Add the needed datas
        a_current_state.current_page = SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE;
        if(currently_displayed_pattern_project_file() == 0) a_pattern_project_file_text_input.get()->set_text("Pas de fichiers disponibles");
        else a_pattern_project_file_text_input.get()->set_text(currently_displayed_pattern_project_file()->base_text());
    }

    // Hide all the agatha part
    void SCLS_Workspace_Agatha_Page::hide_all() {
        // Hide all the bodies
        if(a_file_explorer_body.get() != 0) a_file_explorer_body.get()->set_visible(false);
        if(a_help_body.get() != 0) a_help_body.get()->set_visible(false);
        if(a_pattern_project_file_body.get() != 0) a_pattern_project_file_body.get()->set_visible(false);
        if(a_pattern_project_main_body.get() != 0) a_pattern_project_main_body.get()->set_visible(false);

        // Hide all the footers
        if(a_help_footer.get() != 0) a_help_footer.get()->set_visible(false);
        if(a_pattern_project_main_footer.get() != 0) a_pattern_project_main_footer.get()->set_visible(false);

        // Hide all the navigations
        if(a_help_navigation.get() != 0) a_help_navigation.get()->set_visible(false);
        if(a_pattern_project_main_navigation.get() != 0) a_pattern_project_main_navigation.get()->set_visible(false);
    }

    //*********
    //
    // Event members
    //
    //*********

    // Check the events for the help footer
    void SCLS_Workspace_Agatha_Page::check_help_footer_events() {
        // Check the pattern open button
        if(a_pattern_open_button.get() != 0 && a_pattern_open_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_open_pattern();
        }
    }

    // Check the events for the file explorer
    void SCLS_Workspace_Agatha_Page::check_file_explorer_events() {
        // Check if a file is chosen
        if(a_file_explorer_body.get() != 0 && a_file_explorer_body.get()->file_chosen()) {
            std::string chose_file = a_file_explorer_body.get()->currently_selected_path();

            // Display the good page
            if(a_current_state.current_file_chosen == SCLS_WORKSPACE_AGATHA_OPEN_PATTERN) {
                // Load the project
                std::shared_ptr<Pattern_Project> project_loaded = load_pattern_project(chose_file);
                a_current_state.currently_displayed_pattern_project = project_loaded;
                display_pattern_project();
            }
        }
    }

    // Check the events for the pattern project main page
    void SCLS_Workspace_Agatha_Page::check_pattern_project_main_events() {

    }

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

    // Update the events of the page
    void SCLS_Workspace_Agatha_Page::update_event() {
        GUI_Page::update_event();

        // Help body page
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_HELP_PAGE || a_current_state.current_page == SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE) check_help_footer_events();

        // File explorer page
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_FILE_EXPLORER_PAGE) check_file_explorer_events();

        // Pattern project navigation
        if(a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_MAIN_PAGE || a_current_state.current_page == SCLS_WORKSPACE_AGATHA_PATTERN_PROJECT_FILE_PAGE) check_pattern_project_navigation_events();
    }

    //*********
    //
    // Pattern handling
    //
    //*********

    // Loads an existing pattern and returns it
    std::shared_ptr<Pattern_Project> SCLS_Workspace_Agatha_Page::load_pattern_project(std::string path) {
        std::shared_ptr<Pattern_Project> to_return;

        // Check some assert
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

    // Unloads the buttons in the pattern project navigation
    void SCLS_Workspace_Agatha_Page::unload_pattern_project_navigation() {
        a_current_state.pattern_project_navigation_files.clear();
        a_current_state.pattern_project_navigation_buttons.clear();
        a_pattern_project_main_navigation.get()->reset();
    }
}
