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
        return make_camera(id);
    }
    
    return iter->second.get();
}