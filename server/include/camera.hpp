#include <unordered_map>
#include <vector>
#include <cstdint>
#include <memory>
#include <thread>
#include <mutex>

#pragma once

class Camera {
    int _id;
    std::mutex _lock;
    std::vector<uint8_t> _last_frame;

public:
    inline Camera(int id) : _id(id) { }

    template<typename Iter>
    inline void update_frame(
        Iter begin,
        Iter end
    ) {
        _lock.lock();
        _last_frame.resize(0);
        _last_frame.insert(_last_frame.begin(), begin, end);
        _lock.unlock();
    }

    inline int id() const { return _id; }
    inline const std::vector<uint8_t>& frame() const { return _last_frame; }
};


class CameraManager {
    static std::unordered_map<int, std::shared_ptr<Camera>> _cameras;

public:
    static Camera* make_camera(int id);
    static Camera* get_camera(int id);
};