//******************
//
// scls_workspace_model_maker.cpp
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Workspace of SCLS is a software made to handle development with SCLS more easily.
//
// This file contains the source code of scls_workspace_model_maker.h.
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

#include "../headers/scls_workspace_model_maker.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// Enhanced models
	//
	//*********

    // Returns the point of a gear
	std::shared_ptr<model_maker::Polygon> __gear_solid(unsigned int wheel_number) {
        // Configurate the creation
        double angle_sum = static_cast<double>((wheel_number - 2) * SCLS_PI);
        double current_angle = 0;
        double max_x = 0; double min_x = 0;
        double max_z = 0; double min_z = 0;
        double one_angle = SCLS_PI - angle_sum / static_cast<double>(wheel_number);
        std::shared_ptr<model_maker::Polygon> to_return = std::make_shared<model_maker::Polygon>();

        // Calculate each positions
        double angle_offset = SCLS_PI * 1.5 - one_angle / 2.0;
        double y = 0;
        for(unsigned short i = 0;i<wheel_number;i++) {
            // Calculate the position of the first point
            double x = std::cos(current_angle + angle_offset) * 0.8;
            double z = std::sin(current_angle + angle_offset) * 0.8;
            if(x > max_x) max_x = x; if(x < min_x) min_x = x;
            if(z > max_z) max_z = z; if(z < min_z) min_z = z;

            // Create the point
            model_maker::Point point = model_maker::Point();
            point.move_xyz(x, y, z);
            to_return.get()->points.push_back(point);

            // Calculate the position of the first point
            x = std::cos(current_angle + angle_offset + one_angle * (1.0 / 8.0));
            z = std::sin(current_angle + angle_offset + one_angle * (1.0 / 8.0));
            if(x > max_x) max_x = x; if(x < min_x) min_x = x;
            if(z > max_z) max_z = z; if(z < min_z) min_z = z;

            // Create the point
            point = model_maker::Point();
            point.move_xyz(x, y, z);
            to_return.get()->points.push_back(point);

            // Calculate the position of the third point
            x = std::cos(current_angle + angle_offset + one_angle * (3.0 / 8.0));
            z = std::sin(current_angle + angle_offset + one_angle * (3.0 / 8.0));
            if(x > max_x) max_x = x; if(x < min_x) min_x = x;
            if(z > max_z) max_z = z; if(z < min_z) min_z = z;

            // Create the point
            point = model_maker::Point();
            point.move_xyz(x, y, z);
            to_return.get()->points.push_back(point);

            // Calculate the position of the fourth point
            x = std::cos(current_angle + angle_offset + one_angle * (4.0 / 8.0)) * 0.8;
            z = std::sin(current_angle + angle_offset + one_angle * (4.0 / 8.0)) * 0.8;
            if(x > max_x) max_x = x; if(x < min_x) min_x = x;
            if(z > max_z) max_z = z; if(z < min_z) min_z = z;

            // Create the point
            point = model_maker::Point();
            point.move_xyz(x, y, z);
            to_return.get()->points.push_back(point);

            current_angle += one_angle;
        }
        to_return.get()->max_x = max_x;
        to_return.get()->max_z = max_z;
        to_return.get()->min_x = min_x;
        to_return.get()->min_z = min_z;
        to_return.get()->size_x = max_x - min_x;
        to_return.get()->size_z = max_z - min_z;

        // Calculate the size for normalization
        double multiplier = (1 / to_return.get()->size_x);
        double size_ratio = to_return.get()->size_z / to_return.get()->size_x;
        to_return.get()->size_x = 1;
        to_return.get()->size_z = size_ratio;

        // Normalize each positions
        for(int i = 0;i<static_cast<int>(to_return.get()->points.size());i++) {
            // Normalize the point
            model_maker::Point& point = to_return.get()->points[i];
            point.set_x(point.x() * multiplier);
            point.set_z(point.z() * multiplier);
        }
        to_return.get()->max_x *= multiplier;
        to_return.get()->max_z *= multiplier;
        to_return.get()->min_x *= multiplier;
        to_return.get()->min_z *= multiplier;

        return to_return;
	}

	//*********
	//
	// Model Maker project
	//
	//*********

	// __Model_Maker_Solid constructor
    __Model_Maker_Solid::__Model_Maker_Solid(std::string name) : a_name(name) {}

    // Add a layer to the project
    void __Model_Maker_Solid::add_layer(std::string layer_name, std::shared_ptr<model_maker::Polygon> layer_polygon) {
        std::shared_ptr<__Model_Maker_Layer> to_add = std::make_shared<__Model_Maker_Layer>();
        to_add.get()->name = layer_name;

        // Add the points
        for(int i = 0;i<static_cast<int>(layer_polygon.get()->points.size());i++) {
            std::shared_ptr<model_maker::Point> current_point = std::make_shared<model_maker::Point>(layer_polygon.get()->points[i]);
            current_point.get()->set_parent(to_add.get()->layer_face);
            to_add.get()->points.push_back(current_point);
        }

        layers().push_back(to_add);
    }

    //*********
	//
	// SCLS_Workspace_Model_Maker main members
	//
	//*********

	// Draw a line on an image
	void __draw_line_in_image(Image* texture, model_maker::Point* point_1, model_maker::Point* point_2, unsigned short line_width, Color line_color, double multiplier) {
	    // Get the X and Y of the first point
	    double x_1 = static_cast<double>((point_1->absolute_x() * multiplier + 0.5) * texture->width()) - static_cast<double>(line_width) / 2.0;
	    double x_2 = static_cast<double>((point_2->absolute_x() * multiplier + 0.5) * texture->width()) - static_cast<double>(line_width) / 2.0;
	    double y_1 = static_cast<double>(texture->height() - (point_1->absolute_z() * multiplier + 0.5) * texture->height()) - static_cast<double>(line_width) / 2.0;
	    double y_2 = static_cast<double>(texture->height() - (point_2->absolute_z() * multiplier + 0.5) * texture->height()) - static_cast<double>(line_width) / 2.0;

	    // Draw the line
	    texture->draw_line(x_1, y_1, x_2, y_2, line_color, line_width);
	}

	// Draw a point on an image
	void __draw_point_in_image(Image* texture, model_maker::Point* point_to_draw, unsigned short point_width, Color point_color, double multiplicator) {
	    // Get the X and Y of the point
	    double x = static_cast<double>((point_to_draw->absolute_x() * multiplicator + 0.5) * texture->width()) - static_cast<double>(point_width) / 2.0;
	    double y = static_cast<double>(texture->height() - (point_to_draw->absolute_z() * multiplicator + 0.5) * texture->height()) - static_cast<double>(point_width) / 2.0;

	    // Draw the point
	    texture->fill_rect(x, y, point_width, point_width, point_color);
	}

	// SCLS_Workspace_Model_Maker_Page constructor
    SCLS_Workspace_Model_Maker_Page::SCLS_Workspace_Model_Maker_Page(_Window_Advanced_Struct* window_struct, std::string name) : GUI_Page(window_struct, name) {
        std::shared_ptr<model_maker::Solid> gear = model_maker::polygon_3d(__gear_solid(16));
        gear.get()->binary_stl_complete().get()->save("form.stl");
    };

    // Create an object from a type
    std::shared_ptr<GUI_Object> SCLS_Workspace_Model_Maker_Page::__create_loaded_object_from_type(std::string object_name, std::string object_type, GUI_Object* parent) {
        if(object_name == "gear_layer_creator_body_model_maker") {
            a_gear_layer_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_gear_layer_creator_body;
        }
        else if(object_name == "height_layer_main_body_model_maker") {
            a_height_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_height_layer_main_body;
        }
        else if(object_name == "layer_creator_body_model_maker") {
            a_layer_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_layer_creator_body;
        }
        else if(object_name == "layer_creator_navigation_model_maker") {
            a_layer_creator_navigation = *parent->new_object<GUI_Scroller_Choice>(object_name);
            return a_layer_creator_navigation;
        }
        else if(object_name == "layer_creator_footer_model_maker") {
            a_layer_creator_footer = *parent->new_object<GUI_Object>(object_name);
            return a_layer_creator_footer;
        }
        else if(object_name == "top_connection_layer_main_body_model_maker") {
            a_layer_main_top_connection_navigation = *parent->new_object<GUI_Scroller_Choice>(object_name);
            return a_layer_main_top_connection_navigation;
        }
        else if(object_name == "regulay_polygon_layer_creator_body_model_maker") {
            a_regular_polygon_layer_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_regular_polygon_layer_creator_body;
        }
        else if(object_name == "layer_main_body_model_maker") {
            a_layer_main_body = *parent->new_object<GUI_Object>(object_name);
            return a_layer_main_body;
        }
        else if(object_name == "length_layer_main_body_model_maker") {
            a_length_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_length_layer_main_body;
        }
        else if(object_name == "plane_2d_body_model_maker") {
            a_page_2d_body = *parent->new_object<GUI_Object>(object_name);

            // Create the current point object
            a_current_state.current_page_2d_point_object = *a_page_2d_body->new_object<GUI_Object>("current_point_page_2d_model_maker");
            a_current_state.current_page_2d_point_object.get()->set_background_color(Color(0, 0, 255));
            a_current_state.current_page_2d_point_object.get()->set_height_in_pixel(15);
            a_current_state.current_page_2d_point_object.get()->set_width_in_pixel(15);
            a_current_state.current_page_2d_point_object.get()->set_x_in_object_scale(Fraction(1, 2));
            a_current_state.current_page_2d_point_object.get()->set_y_in_object_scale(Fraction(1, 2));

            return a_page_2d_body;
        }
        else if(object_name == "plane_2d_footer_model_maker") {
            a_page_2d_footer = *parent->new_object<GUI_Object>(object_name);
            return a_page_2d_footer;
        }
        else if(object_name == "plane_2d_add_point") {
            a_page_2d_add_point = *parent->new_object<GUI_Text>(object_name);
            return a_page_2d_add_point;
        }
        else if(object_name == "name_layer_creator_body_model_maker") {
            a_name_layer_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_name_layer_creator_body;
        }
        else if(object_name == "name_solid_creator_body_model_maker") {
            a_name_solid_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_name_solid_creator_body;
        }
        else if(object_name == "new_layer_solid_main_footer_model_maker") {
            a_new_layer_solid_main_footer = *parent->new_object<GUI_Text>(object_name);
            return a_new_layer_solid_main_footer;
        }
        else if(object_name == "side_regulay_polygon_layer_creator_body_model_maker") {
            a_side_regular_polygon_layer_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_side_regular_polygon_layer_creator_body;
        }
        else if(object_name == "solid_creator_body_model_maker") {
            a_solid_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_solid_creator_body;
        }
        else if(object_name == "solid_creator_footer_model_maker") {
            a_solid_creator_footer = *parent->new_object<GUI_Object>(object_name);
            return a_solid_creator_footer;
        }
        else if(object_name == "solid_main_body_model_maker") {
            a_solid_main_body = *parent->new_object<GUI_Object>(object_name);
            return a_solid_main_body;
        }
        else if(object_name == "solid_main_footer_model_maker") {
            a_solid_main_footer = *parent->new_object<GUI_Object>(object_name);
            return a_solid_main_footer;
        }
        else if(object_name == "solid_main_navigation_model_maker") {
            a_solid_main_navigation = *parent->new_object<GUI_Scroller>(object_name);
            return a_solid_main_navigation;
        }
        else if(object_name == "teeth_gear_layer_creator_body_model_maker") {
            a_teeth_gear_layer_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_teeth_gear_layer_creator_body;
        }
        else if(object_name == "title_layer_main_body_model_maker") {
            a_title_layer_main_body = *parent->new_object<GUI_Text>(object_name);
            return a_title_layer_main_body;
        }
        else if(object_name == "title_solid_main_body_model_maker") {
            a_title_solid_main_body = *parent->new_object<GUI_Text>(object_name);
            return a_title_solid_main_body;
        }
        else if(object_name == "validate_layer_creator_body_model_maker") {
            a_validate_layer_creator_body = *parent->new_object<GUI_Text>(object_name);
            return a_validate_layer_creator_body;
        }
        else if(object_name == "validate_solid_creator_body_model_maker") {
            a_validate_solid_creator_body = *parent->new_object<GUI_Text>(object_name);
            return a_validate_solid_creator_body;
        }
        else if(object_name == "view_solid_main_body_model_maker") {
            a_view_solid_main_body = *parent->new_object<GUI_Object>(object_name);
            return a_view_solid_main_body;
        }
        else if(object_name == "width_layer_main_body_model_maker") {
            a_width_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_width_layer_main_body;
        }
        else if(object_name == "x_layer_main_body_model_maker") {
            a_x_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_x_layer_main_body;
        }
        else if(object_name == "y_layer_main_body_model_maker") {
            a_y_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_y_layer_main_body;
        }
        else if(object_name == "z_layer_main_body_model_maker") {
            a_z_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_z_layer_main_body;
        }
        return GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    };

    // Hide all the agatha part
    void SCLS_Workspace_Model_Maker_Page::hide_all() {
        // Hide all the bodies
        if(a_layer_creator_body.get() != 0) a_layer_creator_body.get()->set_visible(false);
        if(a_layer_main_body.get() != 0) a_layer_main_body.get()->set_visible(false);
        if(a_page_2d_body.get() != 0) a_page_2d_body.get()->set_visible(false);
        if(a_solid_creator_body.get() != 0) a_solid_creator_body.get()->set_visible(false);
        if(a_solid_main_body.get() != 0) a_solid_main_body.get()->set_visible(false);

        // Hide all the footers
        if(a_layer_creator_footer.get() != 0) a_layer_creator_footer.get()->set_visible(false);
        if(a_page_2d_footer.get() != 0) a_page_2d_footer.get()->set_visible(false);
        if(a_solid_creator_footer.get() != 0) a_solid_creator_footer.get()->set_visible(false);
        if(a_solid_main_footer.get() != 0) a_solid_main_footer.get()->set_visible(false);

        // Hide all the navigations
        if(a_layer_creator_navigation.get() != 0) a_layer_creator_navigation.get()->set_visible(false);
        if(a_solid_main_navigation.get() != 0) a_solid_main_navigation.get()->set_visible(false);

        // Reset the layer
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_LAYER_MAIN) apply_layer_modification();
    }

    //*********
    //
    // Displaying members
    //
    //*********

    // Display the layer creator
    void SCLS_Workspace_Model_Maker_Page::display_layer_creator() {
        hide_all();
        if(a_layer_creator_body.get() != 0) a_layer_creator_body.get()->set_visible(true);
        if(a_layer_creator_footer.get() != 0) a_layer_creator_footer.get()->set_visible(true);
        if(a_layer_creator_navigation.get() != 0) a_layer_creator_navigation.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_LAYER_CREATOR;

        // Setup the page
        a_layer_creator_navigation.get()->select_object(SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR);
        display_layer_creator_regular_polygon();
        a_name_layer_creator_body.get()->set_text("");
    }

    // Display the layer main
    void SCLS_Workspace_Model_Maker_Page::display_layer_main() {
        hide_all();
        if(a_layer_main_body.get() != 0) a_layer_main_body.get()->set_visible(true);
        if(a_solid_main_footer.get() != 0) a_solid_main_footer.get()->set_visible(true);
        if(a_solid_main_navigation.get() != 0) a_solid_main_navigation.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_LAYER_MAIN;

        // Setup the page
        load_navigation_solid();
        if(a_title_layer_main_body.get() != 0) {
            if(current_layer() == 0) {
                a_height_layer_main_body.get()->set_text("0");
                a_length_layer_main_body.get()->set_text("0");
                a_title_layer_main_body.get()->set_text("Pas de couche à afficher");
                a_x_layer_main_body.get()->set_text("0");
                a_width_layer_main_body.get()->set_text("0");
                a_y_layer_main_body.get()->set_text("0");
                a_z_layer_main_body.get()->set_text("0");
            }
            else {
                a_height_layer_main_body.get()->set_text(format_number_to_text(current_layer()->layer_face.get()->scale_y()));
                a_length_layer_main_body.get()->set_text(format_number_to_text(current_layer()->layer_face.get()->scale_z()));
                a_title_layer_main_body.get()->set_text("Couche \"" + current_layer()->name + "\"");
                a_width_layer_main_body.get()->set_text(format_number_to_text(current_layer()->layer_face.get()->scale_x()));
                a_x_layer_main_body.get()->set_text(format_number_to_text(current_layer()->layer_face.get()->x()));
                a_y_layer_main_body.get()->set_text(format_number_to_text(current_layer()->layer_face.get()->y()));
                a_z_layer_main_body.get()->set_text(format_number_to_text(current_layer()->layer_face.get()->z()));
            }
        }
    }

    // Display the page 2D
    void SCLS_Workspace_Model_Maker_Page::display_page_2d() {
        hide_all();
        if(a_page_2d_body.get() != 0) a_page_2d_body.get()->set_visible(true);
        if(a_page_2d_footer.get() != 0) a_page_2d_footer.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_2D_PAGE;

        // Load the texture
        if(page_2d_current_point() == 0) reset_page_2d_current_point();
        update_texture_2d_base();
        update_texture_2d();
    }

    // Display the solid creator
    void SCLS_Workspace_Model_Maker_Page::display_solid_creator() {
        hide_all();
        if(a_solid_creator_body.get() != 0) a_solid_creator_body.get()->set_visible(true);
        if(a_solid_creator_footer.get() != 0) a_solid_creator_footer.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_SOLID_CREATOR;
    }

    // Display the project main
    void SCLS_Workspace_Model_Maker_Page::display_solid_main() {
        hide_all();
        if(a_solid_main_body.get() != 0) a_solid_main_body.get()->set_visible(true);
        if(a_solid_main_footer.get() != 0) a_solid_main_footer.get()->set_visible(true);
        if(a_solid_main_navigation.get() != 0) a_solid_main_navigation.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN;

        generate_solid();

        // Setup the page
        load_navigation_solid();
        if(a_title_solid_main_body.get() != 0) {
            if(current_solid() == 0) {
                a_title_solid_main_body.get()->set_text("Pas de solide à afficher");
            }
            else {
                a_title_solid_main_body.get()->set_text("Solide \"" + current_solid()->name() + "\"");
            }
        }
        update_solid_view();
    }

    //*********
    //
    // Model maker solid handling
    //
    //*********

    // Adds a new layer to the model maker project
    void SCLS_Workspace_Model_Maker_Page::add_layer_solid() {
        if(a_layer_creator_navigation.get()->currently_selected_objects()[0] == SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR) {
            // Create a regular polygon
            unsigned int side_count = side_regular_polygon_layer_creator_body();
            current_solid()->add_layer(name_layer_creator_body(), model_maker::regular_polygon_points(side_count));
        }
        else if(a_layer_creator_navigation.get()->currently_selected_objects()[0] == SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR) {
            // Create a gear
            unsigned int teeth_count = teeth_gear_layer_creator_body();
            current_solid()->add_layer(name_layer_creator_body(), __gear_solid(teeth_count));
        }
    }

    // Apply the modifications of a layer
    void SCLS_Workspace_Model_Maker_Page::apply_layer_modification() {
        if(current_layer() != 0) {
            // Move the layer
            double new_x = string_to_double(a_x_layer_main_body.get()->text());
            double new_y = string_to_double(a_y_layer_main_body.get()->text());
            double new_z = string_to_double(a_z_layer_main_body.get()->text());
            current_layer()->layer_face.get()->set_x(new_x);
            current_layer()->layer_face.get()->set_y(new_y);
            current_layer()->layer_face.get()->set_z(new_z);

            // Scale the layer
            double new_scale_x = string_to_double(a_width_layer_main_body.get()->text());
            double new_scale_y = string_to_double(a_height_layer_main_body.get()->text());
            double new_scale_z = string_to_double(a_length_layer_main_body.get()->text());
            current_layer()->layer_face.get()->set_scale_x(new_scale_x);
            current_layer()->layer_face.get()->set_scale_y(new_scale_y);
            current_layer()->layer_face.get()->set_scale_z(new_scale_z);

            current_layer()->layer_face.get()->update_real_local_position();
        }
    }

    // Create a new solid
    std::shared_ptr<__Model_Maker_Solid> SCLS_Workspace_Model_Maker_Page::create_solid() {
        std::string project_name = name_solid_creator_body();
        std::shared_ptr<__Model_Maker_Solid> to_return = std::make_shared<__Model_Maker_Solid>(project_name);
        return to_return;
    }

    // Displays the gear page in the layer creator
    void SCLS_Workspace_Model_Maker_Page::display_layer_creator_gear() {
        hide_all_layer_creator();
        a_gear_layer_creator_body.get()->set_visible(true);
        a_teeth_gear_layer_creator_body.get()->set_text("");
    }

    // Displays the regular polygon page in the layer creator
    void SCLS_Workspace_Model_Maker_Page::display_layer_creator_regular_polygon() {
        hide_all_layer_creator();
        a_regular_polygon_layer_creator_body.get()->set_visible(true);
        a_side_regular_polygon_layer_creator_body.get()->set_text("");
    }

    // Generate the solid
    std::shared_ptr<model_maker::Solid> SCLS_Workspace_Model_Maker_Page::generate_solid() {
        std::shared_ptr<model_maker::Solid> solid;
        if(current_solid() != 0 && current_solid()->layers().size() > 0) {
            // Create the solid
            solid = std::make_shared<model_maker::Solid>();

            for(int i = 0;i<static_cast<int>(current_solid()->layers().size());i++) {
                // Create the needed face
                std::shared_ptr<model_maker::Face> current_face = current_solid()->layers()[i].get()->layer_face;
                current_face.get()->convex_triangulation();
                solid.get()->add_face(current_solid()->layers()[i].get()->name, current_face, solid);
            }
            solid.get()->binary_stl_complete().get()->save("form.stl");
        }
        return solid;
    }

    // Hide all the page of the layer creator
    void SCLS_Workspace_Model_Maker_Page::hide_all_layer_creator() {
        a_gear_layer_creator_body.get()->set_visible(false);
        a_regular_polygon_layer_creator_body.get()->set_visible(false);
    }

    // Loads the navigation of the layer creator page
    void SCLS_Workspace_Model_Maker_Page::load_navigation_layer_creator() {
        std::shared_ptr<GUI_Text> current_button;
        std::shared_ptr<GUI_Text> last_button;

        // Create the "gear" solid button
        current_button = *a_layer_creator_navigation.get()->new_object_in_scroller<GUI_Text>(SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR);
        current_button.get()->set_border_width_in_pixel(1);
        current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        current_button.get()->set_height_in_pixel(40);
        current_button.get()->set_text(to_utf_8_code_point("Engrenage"));
        current_button.get()->set_width_in_scale(Fraction(1));
        if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
        else current_button.get()->attach_top_of_object_in_parent(last_button);
        a_navigation_buttons_solid.push_back(current_button);
        last_button = current_button;

        // Create the "regular polygon" solid button
        current_button = *a_layer_creator_navigation.get()->new_object_in_scroller<GUI_Text>(SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR);
        current_button.get()->set_border_width_in_pixel(1);
        current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        current_button.get()->set_height_in_pixel(40);
        current_button.get()->set_text(to_utf_8_code_point("Polygône régulier"));
        current_button.get()->set_width_in_scale(Fraction(1));
        if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
        else current_button.get()->attach_top_of_object_in_parent(last_button);
        a_navigation_buttons_solid.push_back(current_button);
        last_button = current_button;

        a_layer_creator_navigation.get()->check_scroller();
    }

    // Loads the navigation of the model maker project
    void SCLS_Workspace_Model_Maker_Page::load_navigation_solid() {
        unload_navigation_solid();
        if(current_solid() == 0) return;

        unsigned int button = 0;
        std::shared_ptr<GUI_Text> current_button;
        std::shared_ptr<GUI_Text> last_button;

        // Create each layer button
        for(int i = 0;i<static_cast<int>(current_solid()->layers().size());i++) {
            unsigned int real_i = static_cast<int>(current_solid()->layers().size()) - (i + 1);
            current_button = *a_solid_main_navigation.get()->new_object_in_scroller<GUI_Text>("button" + std::to_string(real_i) + "_navigation_model_maker_project"); button++;
            current_button.get()->set_border_width_in_pixel(1);
            current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            current_button.get()->set_height_in_pixel(40);
            current_button.get()->set_text(current_solid()->layers()[real_i].get()->name);
            current_button.get()->set_width_in_scale(Fraction(1));
            if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
            else current_button.get()->attach_top_of_object_in_parent(last_button);

            last_button = current_button;
            a_layer_by_navigation_buttons_solid[current_button.get()] = current_solid()->layers()[real_i];
            a_navigation_buttons_solid.push_back(current_button);
        }

        // Create the "welcome" solid button
        current_button = *a_solid_main_navigation.get()->new_object_in_scroller<GUI_Text>("welcome_navigation_model_maker_project"); button++;
        current_button.get()->set_border_width_in_pixel(1);
        current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        current_button.get()->set_height_in_pixel(40);
        current_button.get()->set_text("Accueil du solide");
        current_button.get()->set_width_in_scale(Fraction(1));
        if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
        else current_button.get()->attach_top_of_object_in_parent(last_button);
        a_navigation_buttons_solid.push_back(current_button);

        a_solid_main_navigation.get()->check_scroller();
    }

    // Loads the top connection navigation of the layer main page
    void SCLS_Workspace_Model_Maker_Page::load_top_connection_layer_main() {
        std::shared_ptr<GUI_Text> current_button;
        std::shared_ptr<GUI_Text> last_button;

        // Create the "gear" solid button
        current_button = *a_layer_main_top_connection_navigation.get()->new_object_in_scroller<GUI_Text>(SCLS_WORKSPACE_MODEL_MAKER_SAME_SHAPE_TOP_CONNECTION_LAYER_MAIN);
        current_button.get()->set_border_width_in_pixel(1);
        current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        current_button.get()->set_height_in_pixel(40);
        current_button.get()->set_text(to_utf_8_code_point("Dupliquer la forme"));
        current_button.get()->set_width_in_scale(Fraction(1));
        if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
        else current_button.get()->attach_top_of_object_in_parent(last_button);
        a_navigation_buttons_solid.push_back(current_button);
        last_button = current_button;

        a_layer_main_top_connection_navigation.get()->check_scroller();
    }

    // Update the view of the solid main
    void SCLS_Workspace_Model_Maker_Page::update_solid_view() {
        // Create the image for the new texture
        std::shared_ptr<Image> new_image = std::make_shared<Image>(500, 500, Color(255, 255, 255));
        Color lines_color = Color(0, 255, 0);
        unsigned int lines_width = 6;
        Color point_color = Color(0, 255, 0);
        unsigned int point_width = 15;

        // Draw each layers
        for(int i = 0;i<static_cast<int>(current_solid()->layers().size());i++) {
            std::shared_ptr<__Model_Maker_Layer> current_layer = current_solid()->layers()[i];

            // Draw each lines of the layer
            for(int j = 0;j<static_cast<int>(current_layer.get()->points.size()) - 1;j++) {
                __draw_line_in_image(new_image, current_layer.get()->points[j].get(), current_layer.get()->points[j + 1].get(), lines_width, lines_color, 0.8);
            }
            if(static_cast<int>(current_layer.get()->points.size()) > 1)__draw_line_in_image(new_image, current_layer.get()->points[static_cast<int>(current_layer.get()->points.size()) - 1].get(), current_layer.get()->points[0].get(), lines_width, lines_color, 0.8);

            // Draw each points of the layer
            for(int j = 0;j<static_cast<int>(current_layer.get()->points.size());j++) {
                __draw_point_in_image(new_image, current_layer.get()->points[j], point_width, point_color, 0.8);
            }
        }

        // Set the new texture
        a_view_solid_main_body.get()->texture()->set_image(new_image);
    }

    //*********
    //
    // Event members
    //
    //*********

    // Check the layer creator events
    void SCLS_Workspace_Model_Maker_Page::check_layer_creator() {
        // Check if the layer creation is validate
        if(a_validate_layer_creator_body.get() != 0 && a_validate_layer_creator_body.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // A layer should be created
            if(name_layer_creator_body() != "") {
                if(a_layer_creator_navigation.get()->currently_selected_objects()[0] == SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR && side_regular_polygon_layer_creator_body() > 2) {
                    add_layer_solid();
                    display_solid_main();
                }
                else if(a_layer_creator_navigation.get()->currently_selected_objects()[0] == SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR && teeth_gear_layer_creator_body() > 3) {
                    add_layer_solid();
                    display_solid_main();
                }
            }
        }

        // Check the layer type
        if(a_layer_creator_navigation.get()->choice_modified()) {
            if(a_layer_creator_navigation.get()->currently_selected_objects()[0] == SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR) {
                display_layer_creator_regular_polygon();
            }
            else if(a_layer_creator_navigation.get()->currently_selected_objects()[0] == SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR) {
                display_layer_creator_gear();
            }
        }
    }

    // Check the movement of the current point in the page 2D
    void SCLS_Workspace_Model_Maker_Page::check_page_2d_current_point_movement() {
        // Check to move the point
        bool moved = false;
        double speed = 0.4;
        // Calculate the ratio
        Fraction image_ratio = a_page_2d_body.get()->texture()->image_ratio();
        double x_ratio = 1;
        double z_ratio = 1;
        if(image_ratio < Fraction(1)) z_ratio = image_ratio.to_double();
        if(window_struct()->key_pressed("z")) {
            page_2d_current_point()->move_z(speed * window_struct()->delta_time() * z_ratio);
            moved = true;
        }
        if(window_struct()->key_pressed("s")) {
            page_2d_current_point()->move_z(-speed * window_struct()->delta_time() * z_ratio);
            moved = true;
        }
        if(window_struct()->key_pressed("d")) {
            page_2d_current_point()->move_x(speed * window_struct()->delta_time() * x_ratio);
            moved = true;
        }
        if(window_struct()->key_pressed("q")) {
            page_2d_current_point()->move_x(-speed * window_struct()->delta_time() * x_ratio);
            moved = true;
        }

        // Check to register a point
        if(a_page_2d_add_point.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT) || window_struct()->key_pressed_during_this_frame("e")) {
            // Create the point
            std::shared_ptr<model_maker::Point> new_point = std::make_shared<model_maker::Point>();
            double base_x = a_current_state.current_page_2d_point.get()->x();
            double base_z = a_current_state.current_page_2d_point.get()->z();
            // Setup the point
            new_point.get()->set_x(base_x);
            new_point.get()->set_z(base_z);
            a_current_state.current_page_2d_points.push_back(new_point);
            a_current_state.current_page_2d_texture_changed = true;
            reset_page_2d_current_point();
            // Move the point to the last position
            page_2d_current_point()->set_x(base_x);
            page_2d_current_point()->set_z(base_z);
            moved = true;
        }

        // Move the object if necessary
        if(moved) {
            glm::vec4 texture_final_rect = a_page_2d_body.get()->texture_rect();
            // Move the object
            page_2d_current_point_object()->set_x_in_pixel((0.5 + page_2d_current_point()->x() * texture_final_rect[2]) * static_cast<double>(a_page_2d_body.get()->width_in_pixel()) - (static_cast<double>(page_2d_current_point_object()->width_in_pixel()) / 2.0));
            page_2d_current_point_object()->set_y_in_pixel((0.5 + page_2d_current_point()->z() * texture_final_rect[3]) * static_cast<double>(a_page_2d_body.get()->height_in_pixel()) - (static_cast<double>(page_2d_current_point_object()->height_in_pixel()) / 2.0));
        }
    }

    // Check the solid creator events
    void SCLS_Workspace_Model_Maker_Page::check_solid_creator() {
        // Check the creation of the solid
        if(a_validate_solid_creator_body.get() != 0 && a_validate_solid_creator_body.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // A solid should be created
            if(name_solid_creator_body() != "") {
                a_current_state.current_solid = create_solid();
                display_solid_main();
            }
        }
    }

    // Check the solid main events
    void SCLS_Workspace_Model_Maker_Page::check_solid_main() {
        // Check the creation of the layer
        if(a_new_layer_solid_main_footer.get() != 0 && a_new_layer_solid_main_footer.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_layer_creator();
        }
    }

    // Check the solid navigation events
    void SCLS_Workspace_Model_Maker_Page::check_solid_navigation() {
        // Check each buttons in the solid navigation
        for(int i = 0;i<static_cast<int>(a_navigation_buttons_solid.size());i++) {
            if(a_navigation_buttons_solid[i].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                if(i == static_cast<int>(a_navigation_buttons_solid.size()) - 1) {
                    // Show the main solid page
                    if(a_current_state.current_page != SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN)display_solid_main();
                }
                else {
                    // Show a layer
                    apply_layer_modification();
                    a_current_state.current_layer = a_layer_by_navigation_buttons_solid[a_navigation_buttons_solid[i].get()];
                    a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN;
                    display_layer_main();
                }
            }
        }
    }

    // Update the events of the page
    void SCLS_Workspace_Model_Maker_Page::update_event() {
        GUI_Page::update_event();

        // Check the layer creator
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_LAYER_CREATOR) check_layer_creator();

        // Check the page 2D events
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_2D_PAGE) check_page_2d_current_point_movement();

        // Change the page 2D texture if necessary
        if(a_current_state.current_page_2d_texture_changed) {
            update_texture_2d();
        }

        // Check the solid creator
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SOLID_CREATOR) check_solid_creator();

        // Check the solid main
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN) check_solid_main();

        // Check the solid navigation
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN || a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_LAYER_MAIN) check_solid_navigation();
    }

    // Update the texture 2D
    void SCLS_Workspace_Model_Maker_Page::update_texture_2d() {
        // Create the texture
        std::shared_ptr<Image> new_texture = std::make_shared<Image>(a_current_state.current_page_2d_texture.get());

        // Draw the current lines
        Color current_lines_color = Color(0, 255, 0);
        unsigned int current_lines_width = 5;
        for(int i = 0;i<static_cast<int>(a_current_state.current_page_2d_points.size()) - 1;i++) {
            __draw_line_in_image(new_texture, a_current_state.current_page_2d_points[i].get(), a_current_state.current_page_2d_points[i + 1].get(), current_lines_width, current_lines_color);
        }

        // Draw the current points
        Color current_points_color = Color(0, 255, 0);
        unsigned int current_points_width = 7;
        for(int i = 0;i<static_cast<int>(a_current_state.current_page_2d_points.size());i++) {
            __draw_point_in_image(new_texture, a_current_state.current_page_2d_points[i].get(), current_points_width, current_points_color);
        }

        // Copy the texture
        a_page_2d_body.get()->texture()->set_image(new_texture);

        // Reset the state if necessary
        a_current_state.current_page_2d_texture_changed = false;
    }

    // Update the base of the texture 2D
    void SCLS_Workspace_Model_Maker_Page::update_texture_2d_base() {
        // Create the texture
        a_current_state.current_page_2d_texture_path = window_struct()->loaded_variable("model_maker_texture_path");
        if(a_current_state.current_page_2d_texture_path != "") {
            std::shared_ptr<Image> unmodified_image = std::make_shared<Image>(a_current_state.current_page_2d_texture_path);

            // Get the resizing values
            unsigned int max_size = 500;
            double new_height = unmodified_image.get()->height();
            double new_width = unmodified_image.get()->width();
            double resize_ratio = static_cast<double>(max_size) / new_height;
            if(new_width >= new_height) {double resize_ratio = static_cast<double>(max_size) / new_width;}
            new_height *= resize_ratio;
            new_width *= resize_ratio;
            // Resize the image
            a_current_state.current_page_2d_texture = unmodified_image.get()->resize_adaptative(new_width, new_height);
        }
        else a_current_state.current_page_2d_texture = std::make_shared<Image>(1, 1, Color(255, 255, 255));
    }
}
