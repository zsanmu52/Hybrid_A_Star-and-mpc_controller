/*******************************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2022 Zhang Zhimeng
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef HYBRID_A_STAR_HYBRID_A_STAR_FLOW_H
#define HYBRID_A_STAR_HYBRID_A_STAR_FLOW_H

#include "hybrid_a_star.h"
#include "costmap_subscriber.h"
#include "init_pose_subscriber.h"
#include "goal_pose_subscriber.h"
#include "hybrid_a_star/dynamicvoronoi.h"
#include "hybrid_a_star/smoother.h"

#include <rclcpp/rclcpp.hpp>

class HybridAStarFlow {
public:
    HybridAStarFlow() = default;

    explicit HybridAStarFlow(rclcpp::Node::SharedPtr node);

    void Run();

private:
    void InitPoseData();

    void ReadData();

    bool HasStartPose();

    bool HasGoalPose();

    void PublishPath(const VectorVec4d &path);
    void PublishPathSmoothed(const VectorVec4d &spath);
    void PublishSearchedTree(const VectorVec4d &searched_tree);

    void PublishVehiclePath(const VectorVec4d &path, double width,
                            double length, unsigned int vehicle_interval);

    void PublishCurrentStartAndGoal();
private:
    rclcpp::Node::SharedPtr node_;
    
    std::shared_ptr<HybridAStar> kinodynamic_astar_searcher_ptr_;
    std::shared_ptr<CostMapSubscriber> costmap_sub_ptr_;
    std::shared_ptr<InitPoseSubscriber2D> init_pose_sub_ptr_;
    std::shared_ptr<GoalPoseSubscriber2D> goal_pose_sub_ptr_;

    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr spath_pub_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr spathWithDirection_pub_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr searched_tree_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr vehicle_path_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pose_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr start_pose_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr path_forward_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr path_backward_pub_;


    /// The voronoi diagram
    DVORONOI::DynamicVoronoi voronoiDiagram; //Voroni Diagram
    SMOOTHER::Smoother smoother;//路径平滑实体

    std::deque<geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr> init_pose_deque_;
    std::deque<geometry_msgs::msg::PoseStamped::SharedPtr> goal_pose_deque_;
    std::deque<nav_msgs::msg::OccupancyGrid::SharedPtr> costmap_deque_;

    geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr current_init_pose_ptr_;
    geometry_msgs::msg::PoseStamped::SharedPtr current_goal_pose_ptr_;
    nav_msgs::msg::OccupancyGrid::SharedPtr current_costmap_ptr_;

    rclcpp::Time timestamp_;

    bool has_map_{};
};

#endif //HYBRID_A_STAR_HYBRID_A_STAR_FLOW_H
