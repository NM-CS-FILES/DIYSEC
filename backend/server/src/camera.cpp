#include "../include/camera.hpp"

std::unordered_map<int, std::shared_ptr<Camera>> CameraManager::_cameras = { };

Camera* CameraManager::make_camera(int id) {
    auto camera_ptr = std::make_shared<Camera>(id);
    _cameras[id] = camera_ptr;
    return camera_ptr.get();
}

Camera* CameraManager::get_camera(int id) {
    auto iter = _cameras.find(id);

    if (iter == _cameras.end()) {
        return nullptr;
    }
    
    return iter->second.get();
}

Camera* CameraManager::get_camera(const std::string& id) {
    int iid = strtol(id.data(), nullptr, 10);
    return get_camera(iid);
}   

std::vector<int> CameraManager::camera_ids() {
    std::vector<int> ids;

    ids.reserve(_cameras.size());

    for (auto& entry : _cameras) {
        ids.push_back(entry.first);
    }

    return ids;
}