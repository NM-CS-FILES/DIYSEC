#include <ixwebsocket/IXWebSocket.h>
#include <opencv4/opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <thread>

int get_id() {
    //return (rand() << 16) | (rand() & 0xFFFF);
    return 1;
}

int main() {
    srand(time(nullptr));

    // cv::VideoCapture cap(0);
    // if (!cap.isOpened()) {
    //     std::cout << "Failed To Open Device" << std::endl;
    //     exit(-1);
    // }

    cv::Mat image = cv::imread("banana.jpg", cv::IMREAD_COLOR);

    // TODO: broadcast server location, use that instead
    
    ix::WebSocket ws;
    ws.setUrl("ws://localhost:8888/camera/" + std::to_string(get_id()));
    ws.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << msg->str << std::endl;
                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Open)
            {
                std::cout << "Connection established" << std::endl;
                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Error)
            {
                std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
                std::cout << "> " << std::flush;
            }
        }
    );

    ws.start();
    
    while (true) {
        cv::Mat frame = image;

        std::vector<uint8_t> bytes;
        cv::imencode(".jpg", frame, bytes);

        ws.sendBinary(std::string(bytes.begin(), bytes.end()));

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}