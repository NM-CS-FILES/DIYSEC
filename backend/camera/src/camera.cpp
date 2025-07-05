#include <ixwebsocket/IXWebSocket.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <fstream>

#include <message.hpp>

// TODO: Not this, terrible, terrible, terrible
std::string get_id() {
    std::ifstream fin("/etc/machine-id");

    if (!fin.is_open()) {
        return "";
    }

    std::string id;
    std::getline(fin, id);

    return id;
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
    ws.setUrl("ws://localhost:8888/camera/" + get_id());
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

        Message frame_msg = Message::make_frame(get_id(), frame);

        std::string message;

        if (!Message::serialize(frame_msg, message)) {
            // TODO ERROR
            continue;
        }

        ws.sendText(message);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}