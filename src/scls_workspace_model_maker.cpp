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

#ifndef SCLS_WORKSPACE_MODEL_MAKER_GEAR_SIZE
#define SCLS_WORKSPACE_MODEL_MAKER_GEAR_SIZE 4.0
#endif // SCLS_WORKSPACE_MODEL_MAKER_GEAR_SIZE

// The namespace "scls" is used to simplify the all.
namespace scls {

    //*********
	//
	// Enhanced models
	//
	//*********

    // Returns the points of a gear
    double __gear_size_by_one_angle(double one_angle) {
        double angle_width = std::sqrt(std::pow(std::cos(one_angle) - 1.0, 2) + std::pow(std::sin(one_angle), 2));
        double proportional_size = 0.517638 / angle_width;
        return proportional_size;
    };
    // Fixed radius center size
	std::shared_ptr<model_maker::Polygon> __gear_solid(double radius_center, unsigned int wheel_number) {
        // Configurate the creation
        double angle_sum = static_cast<double>((wheel_number - 2) * SCLS_PI);
        double angle_total = angle_sum / static_cast<double>(wheel_number);
        double current_angle = 0;
        double max_x = 0; double min_x = 0;
        double max_z = 0; double min_z = 0;
        double one_angle = SCLS_PI - angle_total;
        double proportional_size = __gear_size_by_one_angle(one_angle);
        double side_number = 8 * wheel_number;
        std::shared_ptr<model_maker::Polygon> to_return = std::make_shared<model_maker::Polygon>();
        // Configure the teeth
        double support_teeth_factor = 0.8;
        support_teeth_factor = std::pow(0.8, 12.0 / static_cast<double>(wheel_number));

        // Calculate each positions
        double angle_offset = SCLS_PI * 1.5 - one_angle / 2.0;
        double y = 0;
        for(unsigned short i = 0;i<wheel_number;i++) {
            // Calculate the position of the first point
            double x = std::cos(current_angle + angle_offset) * support_teeth_factor;
            double z = std::sin(current_angle + angle_offset) * support_teeth_factor;
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
            x = std::cos(current_angle + angle_offset + one_angle * (4.0 / 8.0)) * support_teeth_factor;
            z = std::sin(current_angle + angle_offset + one_angle * (4.0 / 8.0)) * support_teeth_factor;
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

        // Add the inner hole
        double exclusion_factor = (radius_center / 4.0);
        //exclusion_factor = 1.0 - std::pow(1.0 - exclusion_factor, 12.0 / static_cast<double>(wheel_number));
        exclusion_factor = exclusion_factor / proportional_size;
        std::shared_ptr<model_maker::Polygon> inner_points = model_maker::regular_polygon_points(20, 0, exclusion_factor);
        to_return.get()->exclusion_points.push_back(inner_points.get()->points);

        // Scale the polygon
        for(int i = 0;i<static_cast<int>(to_return.get()->points.size());i++) {
            // Scale the points
            model_maker::Point& point = to_return.get()->points[i];
            point.set_x(point.x() * proportional_size);
            point.set_z(point.z() * proportional_size);
        }
        for(int i = 0;i<static_cast<int>(to_return.get()->exclusion_points.size());i++) {
            for(int j = 0;j<static_cast<int>(to_return.get()->exclusion_points[i].size());j++) {
                // Scale the exclusion points
                model_maker::Point& point = to_return.get()->exclusion_points[i][j];
                point.set_x(point.x() * proportional_size);
                point.set_z(point.z() * proportional_size);
            }
        }

        return to_return;
	}

	// Returns the points of a pipe
	std::shared_ptr<model_maker::Polygon> __pipe_solid(double radius_center) {
	    std::shared_ptr<model_maker::Polygon> to_return = std::make_shared<model_maker::Polygon>();

	    // Add the outer hole
        std::shared_ptr<model_maker::Polygon> outer_points = model_maker::regular_polygon_points(20, 0, 1);
        for(int i = 0;i<static_cast<int>(outer_points.get()->points.size());i++){to_return.get()->points.push_back(outer_points.get()->points[i]);}

	    // Add the inner hole
        std::shared_ptr<model_maker::Polygon> inner_points = model_maker::regular_polygon_points(20, 0, radius_center);
        to_return.get()->exclusion_points.push_back(inner_points.get()->points);

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

        // Add the exclusion points
        if(layer_polygon.get()->exclusion_points.size() > 0) {
            for(int i = 0;i<static_cast<int>(layer_polygon.get()->exclusion_points[0].size());i++) {
                std::shared_ptr<model_maker::Point> current_point = std::make_shared<model_maker::Point>(layer_polygon.get()->exclusion_points[0][i]);
                current_point.get()->set_parent(to_add.get()->layer_face);
                to_add.get()->layer_face.get()->exclusion_points().push_back(current_point);
            }
        }

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
	    double x_1 = static_cast<double>((point_1->absolute_x() * multiplier + 0.5) * texture->width());
	    double x_2 = static_cast<double>((point_2->absolute_x() * multiplier + 0.5) * texture->width());
	    double y_1 = static_cast<double>(texture->height() - (point_1->absolute_z() * multiplier + 0.5) * texture->height());
	    double y_2 = static_cast<double>(texture->height() - (point_2->absolute_z() * multiplier + 0.5) * texture->height());

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

	// Draw a set of points on an image
    void __draw_points_in_image(Image* texture, const std::vector<std::shared_ptr<model_maker::Point>>& shape_to_draw, unsigned int point_width, Color point_color, unsigned int line_width, Color line_color) {
        // Draw the current lines
        Color current_lines_color = Color(0, 255, 0);
        unsigned int current_lines_width = 5;
        for(int i = 0;i<static_cast<int>(shape_to_draw.size()) - 1;i++) {
            __draw_line_in_image(texture, shape_to_draw.at(i).get(), shape_to_draw.at(i + 1).get(), line_width, line_color);
        }
        if(static_cast<int>(shape_to_draw.size()) > 1) __draw_line_in_image(texture, shape_to_draw.at(shape_to_draw.size() - 1).get(), shape_to_draw.at(0).get(), line_width, line_color);

        // Draw the current points
        Color current_points_color = Color(0, 255, 0);
        unsigned int current_points_width = 7;
        for(int i = 0;i<static_cast<int>(shape_to_draw.size());i++) {
            __draw_point_in_image(texture, shape_to_draw.at(i).get(), point_width, point_color);
        }
    }
    void __draw_points_in_image(Image* texture, const std::vector<model_maker::Point>& shape_to_draw, unsigned int point_width, Color point_color, unsigned int line_width, Color line_color) {
        // Draw the current lines
        Color current_lines_color = Color(0, 255, 0);
        unsigned int current_lines_width = 5;
        for(int i = 0;i<static_cast<int>(shape_to_draw.size()) - 1;i++) {
            __draw_line_in_image(texture, shape_to_draw.at(i), shape_to_draw.at(i + 1), line_width, line_color);
        }
        if(static_cast<int>(shape_to_draw.size()) > 1) __draw_line_in_image(texture, shape_to_draw.at(shape_to_draw.size() - 1), shape_to_draw.at(0), line_width, line_color);

        // Draw the current points
        Color current_points_color = Color(0, 255, 0);
        unsigned int current_points_width = 7;
        for(int i = 0;i<static_cast<int>(shape_to_draw.size());i++) {
            __draw_point_in_image(texture, shape_to_draw.at(i), point_width, point_color);
        }
    }

    // Draw a face on an image
    void __draw_face_in_image(Image* texture, model_maker::Face* face_to_draw) {
        // Draw the current exclusion points
        __draw_points_in_image(texture, face_to_draw->exclusion_points(), 7, Color(255, 0, 0), 5, Color(255, 0, 0));

        // Draw the current points
        __draw_points_in_image(texture, face_to_draw->points(), 7, Color(0, 255, 0), 5, Color(0, 255, 0));
    }

    // Draw a polygon on an image
    void __draw_polygon_in_image(Image* texture, model_maker::Polygon* polygon_to_draw) {
        // Draw the current exclusion points
        for(int i = 0;i<static_cast<int>(polygon_to_draw->exclusion_points.size());i++) __draw_points_in_image(texture, polygon_to_draw->exclusion_points[i], 7, Color(255, 0, 0), 5, Color(255, 0, 0));

        // Draw the current points
        __draw_points_in_image(texture, polygon_to_draw->points, 7, Color(0, 255, 0), 5, Color(0, 255, 0));
    }

	// Draw a shape 2D on an image
    void __draw_shape_2d_in_image(Image* texture, __Model_Maker_Shape* shape_to_draw) {
        // Draw the current exclusion points
        __draw_points_in_image(texture, shape_to_draw->exclusion_points, 7, Color(255, 0, 0), 5, Color(255, 0, 0));

        // Draw the current points
        __draw_points_in_image(texture, shape_to_draw->points, 7, Color(0, 255, 0), 5, Color(0, 255, 0));
    }

    // Draw a set of triangles on an image
    void __draw_triangles_in_image(Image* texture, const std::vector<std::shared_ptr<model_maker::Point>>& shape_to_draw, unsigned int point_width, Color point_color, unsigned int line_width, Color line_color) {
        // Draw the current lines
        for(int i = 0;i<static_cast<int>(shape_to_draw.size()) - 2;i+=3) {
            __draw_line_in_image(texture, shape_to_draw.at(i), shape_to_draw.at(i + 1), line_width, line_color);
            __draw_line_in_image(texture, shape_to_draw.at(i + 1), shape_to_draw.at(i + 2), line_width, line_color);
            __draw_line_in_image(texture, shape_to_draw.at(i), shape_to_draw.at(i + 2), line_width, line_color);
        }

        // Draw the current points
        for(int i = 0;i<static_cast<int>(shape_to_draw.size());i++) {
            __draw_point_in_image(texture, shape_to_draw.at(i), point_width, point_color);
        }
    }

	// SCLS_Workspace_Model_Maker_Page constructor
    SCLS_Workspace_Model_Maker_Page::SCLS_Workspace_Model_Maker_Page(_Window_Advanced_Struct* window_struct, std::string name) : GUI_Page(window_struct, name) {};

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
        else if(object_name == "layer_main_body_model_maker") {
            a_layer_main_body = *parent->new_object<GUI_Object>(object_name);
            return a_layer_main_body;
        }
        else if(object_name == "length_layer_main_body_model_maker") {
            a_length_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_length_layer_main_body;
        }
        else if(object_name == "name_layer_creator_body_model_maker") {
            a_name_layer_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_name_layer_creator_body;
        }
        else if(object_name == "name_shape_2d_creator_body_model_maker") {
            a_name_shape_2d_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_name_shape_2d_creator_body;
        }
        else if(object_name == "name_solid_creator_body_model_maker") {
            a_name_solid_creator_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_name_solid_creator_body;
        }
        else if(object_name == "new_layer_solid_main_footer_model_maker") {
            a_new_layer_solid_main_footer = *parent->new_object<GUI_Text>(object_name);
            return a_new_layer_solid_main_footer;
        }
        else if(object_name == "new_other_shape_layer_creator_body_model_maker") {
            a_new_other_shape_layer_creator = *parent->new_object<GUI_Text>(object_name);
            return a_new_other_shape_layer_creator;
        }
        else if(object_name == "other_shape_layer_creator_body_model_maker") {
            a_other_shape_layer_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_other_shape_layer_creator_body;
        }
        else if(object_name == "point_edition_shape_2d_footer_model_maker") {
            a_point_edition_shape_2d_footer = *parent->new_object<GUI_Object>(object_name);
            return a_point_edition_shape_2d_footer;
        }
        else if(object_name == "point_edition_x_shape_2d_footer_model_maker") {
            a_point_edition_x_shape_2d_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_point_edition_x_shape_2d_main_body;
        }
        else if(object_name == "point_edition_z_shape_2d_footer_model_maker") {
            a_point_edition_z_shape_2d_main_body = *parent->new_object<GUI_Text_Input>(object_name);
            return a_point_edition_z_shape_2d_main_body;
        }
        else if(object_name == "regulay_polygon_layer_creator_body_model_maker") {
            a_regular_polygon_layer_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_regular_polygon_layer_creator_body;
        }
        else if(object_name == "selection_other_shape_layer_creator_body_model_maker") {
            a_selection_other_shape_layer_creator_body = *parent->new_object<GUI_Scroller_Choice>(object_name);
            return a_selection_other_shape_layer_creator_body;
        }
        else if(object_name == "shape_2d_creator_body_model_maker") {
            a_shape_2d_creator_body = *parent->new_object<GUI_Object>(object_name);
            return a_shape_2d_creator_body;
        }
        else if(object_name == "shape_2d_body_model_maker") {
            a_shape_2d_body = *parent->new_object<GUI_Object>(object_name);

            // Create the current point object
            a_current_state.current_page_2d_point_object = *a_shape_2d_body->new_object<GUI_Object>("current_point_page_2d_model_maker");
            a_current_state.current_page_2d_point_object.get()->set_background_color(Color(0, 0, 255));
            a_current_state.current_page_2d_point_object.get()->set_height_in_pixel(15);
            a_current_state.current_page_2d_point_object.get()->set_width_in_pixel(15);
            a_current_state.current_page_2d_point_object.get()->set_x_in_object_scale(Fraction(1, 2));
            a_current_state.current_page_2d_point_object.get()->set_y_in_object_scale(Fraction(1, 2));

            return a_shape_2d_body;
        }
        else if(object_name == "shape_2d_footer_model_maker") {
            a_shape_2d_footer = *parent->new_object<GUI_Object>(object_name);
            return a_shape_2d_footer;
        }
        else if(object_name == "shape_2d_navigation_model_maker") {
            a_shape_2d_navigation = *parent->new_object<GUI_Scroller>(object_name);
            return a_shape_2d_navigation;
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
        else if(object_name == "point_edition_title_shape_2d_footer_model_maker") {
            a_title_point_edition_shape_2d_footer = *parent->new_object<GUI_Text>(object_name);
            return a_title_point_edition_shape_2d_footer;
        }
        else if(object_name == "title_solid_main_body_model_maker") {
            a_title_solid_main_body = *parent->new_object<GUI_Text>(object_name);
            return a_title_solid_main_body;
        }
        else if(object_name == "top_connection_layer_main_body_model_maker") {
            a_layer_main_top_connection_navigation = *parent->new_object<GUI_Scroller_Choice>(object_name);
            return a_layer_main_top_connection_navigation;
        }
        else if(object_name == "validate_layer_creator_body_model_maker") {
            a_validate_layer_creator_body = *parent->new_object<GUI_Text>(object_name);
            return a_validate_layer_creator_body;
        }
        else if(object_name == "validate_shape_2d_creator_body_model_maker") {
            a_validate_shape_2d_creator_body = *parent->new_object<GUI_Text>(object_name);
            return a_validate_shape_2d_creator_body;
        }
        else if(object_name == "validate_shape_2d_footer_model_maker") {
            a_validate_shape_2d_body = *parent->new_object<GUI_Text>(object_name);
            return a_validate_shape_2d_body;
        }
        else if(object_name == "validate_solid_creator_body_model_maker") {
            a_validate_solid_creator_body = *parent->new_object<GUI_Text>(object_name);
            return a_validate_solid_creator_body;
        }
        else if(object_name == "view_solid_main_body_model_maker"){a_view_solid_main_body = *parent->new_object<pleos::Graphic_Object>(object_name);return a_view_solid_main_body;}
        else if(object_name == "width_layer_main_body_model_maker"){a_width_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);return a_width_layer_main_body;}
        else if(object_name == "x_layer_main_body_model_maker"){a_x_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);return a_x_layer_main_body;}
        else if(object_name == "y_layer_main_body_model_maker"){a_y_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);return a_y_layer_main_body;}
        else if(object_name == "z_layer_main_body_model_maker"){a_z_layer_main_body = *parent->new_object<GUI_Text_Input>(object_name);return a_z_layer_main_body;}
        return GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    };

    // Hide all the agatha part
    void SCLS_Workspace_Model_Maker_Page::hide_all() {
        // Hide all the bodies
        if(a_layer_creator_body.get() != 0) a_layer_creator_body.get()->set_visible(false);
        if(a_layer_main_body.get() != 0) a_layer_main_body.get()->set_visible(false);
        if(a_shape_2d_body.get() != 0) a_shape_2d_body.get()->set_visible(false);
        if(a_shape_2d_creator_body.get() != 0) a_shape_2d_creator_body.get()->set_visible(false);
        if(a_solid_creator_body.get() != 0) a_solid_creator_body.get()->set_visible(false);
        if(a_solid_main_body.get() != 0) a_solid_main_body.get()->set_visible(false);

        // Hide all the footers
        if(a_layer_creator_footer.get() != 0) a_layer_creator_footer.get()->set_visible(false);
        if(a_shape_2d_footer.get() != 0) a_shape_2d_footer.get()->set_visible(false);
        if(a_solid_creator_footer.get() != 0) a_solid_creator_footer.get()->set_visible(false);
        if(a_solid_main_footer.get() != 0) a_solid_main_footer.get()->set_visible(false);

        // Hide all the navigations
        if(a_layer_creator_navigation.get() != 0) a_layer_creator_navigation.get()->set_visible(false);
        if(a_shape_2d_navigation.get() != 0) a_shape_2d_navigation.get()->set_visible(false);
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
    void SCLS_Workspace_Model_Maker_Page::display_shape_2d() {
        hide_all();
        if(a_shape_2d_body.get() != 0) a_shape_2d_body.get()->set_visible(true);
        if(a_shape_2d_footer.get() != 0) a_shape_2d_footer.get()->set_visible(true);
        if(a_shape_2d_navigation.get() != 0) a_shape_2d_navigation.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D;

        // Load the texture
        load_navigation_shape_2d();
        reset_page_2d_current_point();
        update_texture_2d_base();
        update_texture_2d();
    }

    // Display the shape 2D creator
    void SCLS_Workspace_Model_Maker_Page::display_shape_2d_creator() {
        hide_all();
        if(a_shape_2d_creator_body.get() != 0) a_shape_2d_creator_body.get()->set_visible(true);
        if(a_layer_creator_footer.get() != 0) a_layer_creator_footer.get()->set_visible(true);
        if(a_layer_creator_navigation.get() != 0) a_layer_creator_navigation.get()->set_visible(true);
        a_current_state.current_page = SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_CREATOR;
    }

    // Display the shape 2D point edition
    void SCLS_Workspace_Model_Maker_Page::display_shape_2d_point_edition() {
        a_point_edition_shape_2d_footer.get()->set_visible(true);

        // Change the GUI as needed
        if(current_shape_2d_point() == 0) {
            a_title_point_edition_shape_2d_footer.get()->set_text(scls::to_utf_8("Pas de point sélectionné"));
            a_point_edition_x_shape_2d_main_body.get()->set_text("0");
            a_point_edition_z_shape_2d_main_body.get()->set_text("0");
        }
        else {
            unsigned int point_id = current_shape_2d_point()->id();
            a_title_point_edition_shape_2d_footer.get()->set_text("Point " + std::to_string(point_id));
            a_point_edition_x_shape_2d_main_body.get()->set_text(format_number_to_text(current_shape_2d_point()->x()));
            a_point_edition_z_shape_2d_main_body.get()->set_text(format_number_to_text(current_shape_2d_point()->z()));
        }
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
    // Model maker layer handling
    //
    //*********

    // Adds a new layer to the model maker project
    void SCLS_Workspace_Model_Maker_Page::add_layer_solid() {
        if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR) {
            // Create a regular polygon
            unsigned int side_count = side_regular_polygon_layer_creator_body();
            current_solid()->add_layer(name_layer_creator_body(), model_maker::regular_polygon_points(side_count));
        }
        else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_PIPE_POLYGON_LAYER_CREATOR) {
            // Create a pipe
            double gear_size = 0.8;
            std::shared_ptr<model_maker::Polygon> pipe = __pipe_solid(gear_size);
            current_solid()->add_layer(name_layer_creator_body(), pipe);
        }
        else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR) {
            // Create a gear
            double gear_size = 1.1;
            unsigned int teeth_count = teeth_gear_layer_creator_body();
            std::shared_ptr<model_maker::Polygon> gear = __gear_solid(gear_size, teeth_count);
            current_solid()->add_layer(name_layer_creator_body(), gear);
        }
        else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR) {
            // Create an other shape
            std::string shape_name = name_shape_2d_layer_creator_body();
            if(chosen_shape_2d() != 0) current_solid()->add_layer(name_layer_creator_body(), chosen_shape_2d()->to_polygon());
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

    // Displays the gear page in the layer creator
    void SCLS_Workspace_Model_Maker_Page::display_layer_creator_gear() {
        hide_all_layer_creator();
        a_gear_layer_creator_body.get()->set_visible(true);
        a_teeth_gear_layer_creator_body.get()->set_text("");
    }

    // Displays the other shape page in the layer creator
    void SCLS_Workspace_Model_Maker_Page::display_layer_creator_other_shape() {
        hide_all_layer_creator();
        a_other_shape_layer_creator_body.get()->set_visible(true);
        load_selection_other_shape_layer_creator();
        a_layer_creator_navigation.get()->select_object(SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR);
    }

    // Displays the regular polygon page in the layer creator
    void SCLS_Workspace_Model_Maker_Page::display_layer_creator_regular_polygon() {
        hide_all_layer_creator();
        a_regular_polygon_layer_creator_body.get()->set_visible(true);
        a_side_regular_polygon_layer_creator_body.get()->set_text("");
    }

    // Loads the navigation of the other shape layer creator page
    void SCLS_Workspace_Model_Maker_Page::load_selection_other_shape_layer_creator() {
        unload_selection_other_shape_layer_creator();

        std::shared_ptr<GUI_Text> current_button;
        std::shared_ptr<GUI_Text> last_button;

        // Create each buttons
        for(int i = 0;i<static_cast<int>(a_loaded_shape_2d.size());i++) {
            // Create the button
            int real_i = (static_cast<int>(a_loaded_shape_2d.size()) - (i + 1));
            std::string selection_name = SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR + "-button" + std::to_string(real_i);
            current_button = *a_selection_other_shape_layer_creator_body.get()->new_object_in_scroller<GUI_Text>(selection_name);
            current_button.get()->set_border_width_in_pixel(1);
            current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            current_button.get()->set_height_in_pixel(40);
            current_button.get()->set_text(a_loaded_shape_2d[i].get()->name);
            current_button.get()->set_width_in_scale(Fraction(1));
            if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
            else current_button.get()->attach_top_of_object_in_parent(last_button);
            last_button = current_button;
            a_current_state.loaded_shape_2d_by_selection[selection_name] = a_loaded_shape_2d[i];
        }
        a_selection_other_shape_layer_creator_body.get()->check_scroller();
    }

    //*********
    //
    // Model maker shape 2D handling
    //
    //*********

    // Creates a new shape 2D
    std::shared_ptr<__Model_Maker_Shape> SCLS_Workspace_Model_Maker_Page::create_shape_2d() {
        std::string shape_name = name_shape_2d_creator_body();
        std::shared_ptr<__Model_Maker_Shape> to_return = std::make_shared<__Model_Maker_Shape>(shape_name);
        a_loaded_shape_2d.push_back(to_return);
        return to_return;
    }

    // Load each navigation buttons in the shape 2D page
    void SCLS_Workspace_Model_Maker_Page::load_navigation_shape_2d(bool reset_navigation) {
        if(reset_navigation) {
            unload_navigation_shape_2d();

            // Create each buttons
            for(int i = 0;i<static_cast<int>(current_shape_2d()->points.size());i++) {
                unsigned int real_i = static_cast<int>(current_shape_2d()->points.size()) - (i + 1);
                unsigned int point_id = current_shape_2d()->points[real_i].get()->id();
                std::shared_ptr<GUI_Text> current_button = *a_shape_2d_navigation.get()->new_object_in_scroller<GUI_Text>("shape_2d_navigation_model_maker_buttons_" + std::to_string(point_id));
                current_button.get()->set_border_width_in_pixel(1);
                current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                current_button.get()->set_height_in_pixel(40);
                current_button.get()->set_text("Point " + std::to_string(point_id));
                current_button.get()->set_width_in_scale(Fraction(1));

                a_loaded_shape_2d_point_by_button[current_button.get()] = current_shape_2d()->points[real_i];
                a_navigation_buttons_shape_2d.push_back(current_button);
            }

            // Create the "home shape" solid button
            std::shared_ptr<GUI_Text> current_button = *a_shape_2d_navigation.get()->new_object_in_scroller<GUI_Text>("shape_2d_navigation_model_maker_buttons_home");
            current_button.get()->set_border_width_in_pixel(1);
            current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            current_button.get()->set_height_in_pixel(40);
            current_button.get()->set_text(to_utf_8_code_point("Accueil de la forme"));
            current_button.get()->set_width_in_scale(Fraction(1));
            a_navigation_buttons_shape_2d.push_back(current_button);

            std::reverse(a_navigation_buttons_shape_2d.begin(), a_navigation_buttons_shape_2d.end());
        }
        else {
            // Create needed buttons
            while(a_navigation_buttons_shape_2d.size() <= current_shape_2d()->points.size()) {
                unsigned int real_i = a_navigation_buttons_shape_2d.size() - 1;
                unsigned int point_id = current_shape_2d()->points[real_i].get()->id();
                std::shared_ptr<GUI_Text> current_button = *a_shape_2d_navigation.get()->new_object_in_scroller<GUI_Text>("shape_2d_navigation_model_maker_buttons_" + std::to_string(point_id));
                current_button.get()->set_border_width_in_pixel(1);
                current_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
                current_button.get()->set_height_in_pixel(40);
                current_button.get()->set_text("Point " + std::to_string(point_id));
                current_button.get()->set_width_in_scale(Fraction(1));

                a_loaded_shape_2d_point_by_button[current_button.get()] = current_shape_2d()->points[real_i];
                a_navigation_buttons_shape_2d.push_back(current_button);
            }
        }

        // Place the buttons
        std::shared_ptr<GUI_Text> current_button;
        std::shared_ptr<GUI_Text> last_button;
        for(int i = 0;i<static_cast<int>(a_navigation_buttons_shape_2d.size());i++) {
            unsigned int real_i = static_cast<int>(a_navigation_buttons_shape_2d.size()) - (i + 1);
            current_button = a_navigation_buttons_shape_2d[real_i];
            if(last_button.get() == 0) current_button.get()->attach_bottom_in_parent();
            else current_button.get()->attach_top_of_object_in_parent(last_button);
            last_button = current_button;
        }

        a_shape_2d_navigation.get()->check_scroller();
    }

    // Update the texture 2D
    void SCLS_Workspace_Model_Maker_Page::update_texture_2d() {
        // Create the texture
        std::shared_ptr<Image> new_texture = std::make_shared<Image>(a_current_state.current_page_2d_texture.get());
        __draw_shape_2d_in_image(new_texture, current_shape_2d());

        // Copy the texture
        a_shape_2d_body.get()->texture()->set_image(new_texture);

        // Reset the state if necessary
        a_current_state.current_page_2d_texture_changed = false;
    }

    //*********
    //
    // Model maker solid handling
    //
    //*********

    // Create a new solid
    std::shared_ptr<__Model_Maker_Solid> SCLS_Workspace_Model_Maker_Page::create_solid() {
        std::string project_name = name_solid_creator_body();
        std::shared_ptr<__Model_Maker_Solid> to_return = std::make_shared<__Model_Maker_Solid>(project_name);
        return to_return;
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

                // Test triangulation
                /*std::shared_ptr<scls::model_maker::Face::__Triangulation_Datas> datas = current_face.get()->triangulate_start_datas(); int t = 0;
                while(!datas.get()->finished) {
                    if(current_face.get()->triangulation_step(datas)) {
                        std::shared_ptr<scls::Image> img = std::make_shared<scls::Image>(500,500, scls::Color(255, 255, 255));
                        __draw_face_in_image(img.get(), current_face.get());
                        __draw_triangles_in_image(img.get(), current_face.get()->points_for_rendering(), 2, scls::Color(0, 0, 255), 2, scls::Color(0, 0, 255));
                        img.get()->save_png("tests/img" + std::to_string(t) + ".png"); t++;
                    }
                } //*/

                // Triangulate the face
                current_face.get()->triangulate();

                solid.get()->add_face(current_solid()->layers()[i].get()->name, current_face, solid);

                // Apply the top connection
                if(current_solid()->layers()[i].get()->Top_Connection.type == SCLS_WORKSPACE_MODEL_MAKER_SAME_SHAPE_TOP_CONNECTION_LAYER) {
                    // The top is the same shape as the bottom
                    double height = current_solid()->layers()[i].get()->layer_face.get()->y() + current_solid()->layers()[i].get()->layer_face.get()->scale_y();
                    std::shared_ptr<model_maker::Face> new_face = current_solid()->layers()[i].get()->layer_face.get()->copy_with_new_points();

                    new_face.get()->triangulate();
                    new_face.get()->set_y(height);
                    solid.get()->add_face(current_solid()->layers()[i].get()->name + "-top", new_face, solid);
                    solid.get()->fill_faces_point_by_point(current_face, new_face, solid);
                }
            }
            solid.get()->binary_stl_complete(40).get()->save("tests/form.stl");
        }
        return solid;
    }

    // Hide all the page of the layer creator
    void SCLS_Workspace_Model_Maker_Page::hide_all_layer_creator() {
        a_gear_layer_creator_body.get()->set_visible(false);
        a_other_shape_layer_creator_body.get()->set_visible(false);
        a_regular_polygon_layer_creator_body.get()->set_visible(false);
    }

    // Loads the navigation of the layer creator page
    void SCLS_Workspace_Model_Maker_Page::load_navigation_layer_creator() {
        // Create the buttons
        a_layer_creator_navigation.get()->add_object(SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR, std::string("Polygône régulier"));
        a_layer_creator_navigation.get()->add_object(SCLS_WORKSPACE_MODEL_MAKER_PIPE_POLYGON_LAYER_CREATOR, std::string("Tuyau"));
        a_layer_creator_navigation.get()->add_object(SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR, std::string("Engrenage"));
        a_layer_creator_navigation.get()->add_object(SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR, std::string("Autre forme"));
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
        current_button = *a_solid_main_navigation.get()->new_object_in_scroller<GUI_Text>(std::string("welcome_navigation_model_maker_project_") + std::to_string(button)); button++;
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
        a_view_solid_main_body.get()->reset();

        // Add each layers
        for(int i = 0;i<static_cast<int>(current_solid()->layers().size());i++) {current_solid()->layers()[i].get()->add_to_graphic(a_view_solid_main_body.get()->graphic());}

        // Set the new texture
        a_view_solid_main_body.get()->update_texture();
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
                if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR && side_regular_polygon_layer_creator_body() > 2) {
                    add_layer_solid();
                    display_solid_main();
                }
                else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR && teeth_gear_layer_creator_body() > 3) {
                    add_layer_solid();
                    display_solid_main();
                }
                else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR && name_shape_2d_layer_creator_body() != "") {
                    add_layer_solid();
                    display_solid_main();
                }
                else {
                    add_layer_solid();
                    display_solid_main();
                }
            }
        }

        // Check if a new other shape should be created
        if(a_new_other_shape_layer_creator.get() != 0 && a_new_other_shape_layer_creator.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_shape_2d_creator();
        }

        // Check the layer type
        if(a_layer_creator_navigation.get()->choice_modified()) {
            if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_REGULAR_POLYGON_LAYER_CREATOR) {
                display_layer_creator_regular_polygon();
            }
            else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_OTHER_SHAPE_POLYGON_LAYER_CREATOR) {
                display_layer_creator_other_shape();
            }
            else if(a_layer_creator_navigation.get()->currently_selected_objects()[0].name() == SCLS_WORKSPACE_MODEL_MAKER_GEAR_POLYGON_LAYER_CREATOR) {
                display_layer_creator_gear();
            }
            else{hide_all_layer_creator();}
        }
    }

    // Check the movement of the current point in the page 2D
    void SCLS_Workspace_Model_Maker_Page::check_page_2d_current_point_movement() {
        // Check to move the point
        bool moved = false;
        double speed = 0.4;
        // Calculate the ratio
        Fraction image_ratio = a_shape_2d_body.get()->texture()->image_ratio();
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

        // Check the type of point
        if(window_struct()->key_pressed_during_this_frame("b")) a_current_state.current_shape_2d_point_type = SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_POINT;
        if(window_struct()->key_pressed_during_this_frame("n")) a_current_state.current_shape_2d_point_type = SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_EXCLUSION_POINT;

        // Check to register a point
        if(window_struct()->key_pressed_during_this_frame("e")) {
            // Create the point
            std::shared_ptr<model_maker::Point> new_point = std::make_shared<model_maker::Point>();
            double base_x = a_current_state.current_page_2d_point.get()->x();
            double base_z = a_current_state.current_page_2d_point.get()->z();
            // Setup the point
            new_point.get()->set_x(base_x);
            new_point.get()->set_z(base_z);
            add_point_current_shape_2d(new_point);
            a_current_state.current_page_2d_texture_changed = true;
            load_navigation_shape_2d(false);
            reset_page_2d_current_point();
            // Move the point to the last position
            moved = true;
            page_2d_current_point()->set_x(base_x);
            page_2d_current_point()->set_z(base_z);
        }

        // Move the object if necessary
        if(moved) move_shape_2d_current_point();
    }

    // Check the shape 2D events
    void SCLS_Workspace_Model_Maker_Page::check_shape_2d() {
        // Check the validation of the shape
        if(a_validate_shape_2d_body.get() != 0 && a_validate_shape_2d_body.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            display_layer_creator();
            display_layer_creator_other_shape();
        }

        // Check if a point is clicked
        for(int i = 0;i<static_cast<int>(a_navigation_buttons_shape_2d.size());i++) {
            if(a_navigation_buttons_shape_2d[i].get() != 0 && a_navigation_buttons_shape_2d[i].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                if(i == 0) {

                }
                else {
                    a_current_state.current_shape_2d_point = a_loaded_shape_2d_point_by_button[a_navigation_buttons_shape_2d[i].get()];
                    display_shape_2d_point_edition();
                }
            }
        }

        // Check if the selected point is modified
        bool texture_changed = false;
        if(a_point_edition_x_shape_2d_main_body.get()->input_during_this_frame()) {
            current_shape_2d_point()->set_x(point_edition_x_shape_2d_main_body());
            texture_changed = true;
        }
        if(a_point_edition_z_shape_2d_main_body.get()->input_during_this_frame()) {
            current_shape_2d_point()->set_z(point_edition_z_shape_2d_main_body());
            texture_changed = true;
        }
        if(texture_changed) update_texture_2d();
    }

    // Check the shape 2D creator events
    void SCLS_Workspace_Model_Maker_Page::check_shape_2d_creator() {
        // Check the creation of the shape
        if(a_validate_shape_2d_creator_body.get() != 0 && a_validate_shape_2d_creator_body.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // A shape should be created
            if(name_shape_2d_creator_body() != "") {
                a_current_state.current_shape_2d = create_shape_2d();
                display_shape_2d();
            }
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
    void SCLS_Workspace_Model_Maker_Page::check_solid_footer() {
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
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D) check_page_2d_current_point_movement();

        // Change the page 2D texture if necessary
        if(a_current_state.current_page_2d_texture_changed) {update_texture_2d();}

        // Check the shade 2D
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D) check_shape_2d();

        // Check the shape 2D creator
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SHAPE_2D_CREATOR) check_shape_2d_creator();

        // Check the solid creator
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SOLID_CREATOR) check_solid_creator();

        // Check the solid footer
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN || a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_LAYER_MAIN) check_solid_footer();

        // Check the solid navigation
        if(a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_SOLID_MAIN || a_current_state.current_page == SCLS_WORKSPACE_MODEL_MAKER_LAYER_MAIN) check_solid_navigation();
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
            unmodified_image = unmodified_image.get()->resize_adaptative(new_width, new_height);
            // Paste the good image
            a_current_state.current_page_2d_texture = std::make_shared<Image>(max_size, max_size, Color(255, 255, 255));
            if(new_width > new_height) a_current_state.current_page_2d_texture.get()->paste(unmodified_image.get(), 0, max_size / 2.0 - new_height / 2.0);
            else a_current_state.current_page_2d_texture.get()->paste(unmodified_image.get(), max_size / 2.0 - new_width / 2.0, 0);
        }
        else a_current_state.current_page_2d_texture = std::make_shared<Image>(1, 1, Color(255, 255, 255));
    }
}
