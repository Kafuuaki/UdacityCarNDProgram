#include <iostream>

// using json to decode the message

#include <uWS/uWS.h>
#include <cmath>
#include "json.hpp"
#include "PID.h"

using json = nlohmann::json;

// mission: create a simple server that can handle a single connection
// and send a message to the client after using pid to handle the message

// to confirm that there is data
std::string hasData(std::string s) {
    // when the string is not found, std::string::find will return std::string::npos

    // q: why need to find the first and last of the string?
    // q: why the first and last of the string is "[" and "]"?
    // a: the message is a json string, so the first and last of the string is "[" and "]"
    auto found_null = s.find("null");
    auto b1 = s.find_first_of("[");
    auto b2 = s.find_last_of("]");
    if (found_null != std::string::npos) {
        return "";
    }

    if (b1 != std::string::npos && b2 != std::string::npos) {
        return s.substr(b1, b2 - b1 + 1);
    }

    return "";
}



int main() {
    // create a hub
    // q: what is a hub?
    // a: a hub is a server that can handle multiple connections
    uWS::Hub h;

    // create a callback function that will be called when a message is received
    // PID pid_steer(0.534611, 0.000001, 80.05349);
    // PID pid_throttle(0.0616731, 0.0002, 0);

    PID pid_steer, pid_throttle;

    pid_steer.init(0.534611, 0.000001, 80.05349);
    pid_throttle.init(0.0616731, 0.0002, 0);


    // initilize the
    // what is h.onMessage?
    // a: h.onMessage is a function that will be called when a message is received
    // our onMessage take a function as an argument
    // the argument of the function is a websocket server, a char pointer (str), the length of the string, nad

    // using the lambda function, every time the message is received, the lambad function would be called
    // the lambda function use & to capture the variable by reference, what the lambda function do would reflect in outside of the function, like update error


    // listen to the message -> decode the message -> update the error -> send the message
    h.onMessage([&pid_steer, &pid_throttle](uWS::WebSocket<uWS::SERVER> ws, char* data, size_t length, uWS::OpCode opCode) {
        // 42 is the start of the websocket message, if it full fill this condition, it is a websocket event
        if (length && length > 2 && data[0] == '4' && data[1] == '2') {
            auto s = hasData(std::string(data).substr(0, length));
            if (s != "") {
                // this function return a basic_json object
                auto j = json::parse(s);

                // assume that the json object is an array, the j[0] would return the first element of it
                std::string event = j[0].get<std::string>();

                if (event == "telemetry") {
                    // decode this message
                    double cte = std::stod(j[1]["cte"].get<std::string>());
                    double speed = std::stod(j[1]["speed"].get<std::string>());
                    double andgle = std::stod(j[1]["steering_angle"].get<std::string>());

                    double steer_value, thottle_value;

                    // update the error
                    // handle the error
                    pid_steer.updateError(cte);
                    pid_throttle.updateError(std::fabs(cte));

                    steer_value = pid_steer.totalError();
                    thottle_value = 0.55 - pid_throttle.totalErrorWithoutI();


                    // std::cout << "steer value: " << steer_value << std::endl;
                    // std::cout << "thottle value: " << thottle_value << std::endl;

                    json msgJson;
                    msgJson["steering_angle"] = steer_value;
                    msgJson["throttle"] = thottle_value;
                    
                    // dump function conver the data into the json type
                    std::string msg = "42[\"steer\"," + msgJson.dump() + "]";

                    // unit test
                    // std::cout << "msg: " << msg << std::endl;
                    ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                } 
                // mis else, should be in here
            } else {
                std::string msg = "42[\"manual\",{}]";
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
        }
    });

    // h.httpRequestHandler([])
    h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
        const std::string s = "<h1>Hello world!</h1>";
        if (req.getUrl().valueLength == 1)
        {
        res->end(s.data(), s.length());
        }
        else
        {
        // i guess this should be done more gracefully?
        res->end(nullptr, 0);
        }
     });

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        std::cout << "Connected!!!" << std::endl;
    });

    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char* message, size_t length) {
        ws.close();
        std::cout << "Disconnected" << std::endl;
    });


    int port = 4567;

    if (h.listen(port)) {
        std::cout << "Listen to port" << port << std::endl;
    } else {
        std::cerr << "Failed to listen to port" << port << std::endl;
        return -1;
    }

    // without run, there will be
    // Assertion failed: (err == 0), function uv_loop_delete, file uv-common.c, line 886.
    // zsh: abort      ./main
    h.run();
}