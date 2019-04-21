#include "json_io.h"
// JSON 

json get_forest_json(std::vector<std::vector<tree>> &trees,double y_mean){
    json result;
    result["num_sweeps"] = trees.size();
    result["num_trees"] = trees[0].size();
    result["num_classes"] = trees[0][0].theta_vector.size();
    result["y_mean"] = y_mean;
    //auto jsonObjects = json::array();

    //result[std::to_string(0)] = trees[0][0].to_json();
    for(size_t i =0; i< trees.size();i++){
        std::vector<tree> &tree_vec = trees[i];
        for(size_t j =0; j < tree_vec.size(); j++){
            result[std::to_string(i)][std::to_string(j)] = tree_vec[j].to_json();
            //jsonObjects.push_back(tree_vec[j].to_json());
        }
    }
    //result["trees"] = jsonObjects;
    return result;
}

void from_json_to_forest(std::string &json_string,vector<vector<tree>> &trees,double &y_mean){
    auto j3 = json::parse(json_string);
    
    size_t num_sweeps;
    j3.at("num_sweeps").get_to(num_sweeps);

    size_t num_trees;
    j3.at("num_trees").get_to(num_trees);

    size_t num_classes;
    j3.at("num_classes").get_to(num_classes);

    j3.at("y_mean").get_to(y_mean);


    // // Create trees
    trees.resize(num_sweeps);
    for (size_t i = 0; i < num_sweeps; i++)
    {
        trees[i] = vector<tree>(num_trees);
    }

    for(size_t i = 0; i< num_sweeps; i++){
        for(size_t j = 0;j<num_trees;j++){
            trees[i][j].from_json(j3[std::to_string(i)][std::to_string(j)],num_classes);
        }
    }

    return;


}
