#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
void parse_duration(const std::string& duration_str, int& hours, int& minutes, int& seconds) {
    hours = minutes = seconds = 0;
    int h = 0, m = 0, s = 0;
    size_t h_pos = duration_str.find('h');
    size_t m_pos = duration_str.find('m');
    size_t s_pos = duration_str.find('s');
    if (h_pos != std::string::npos)
        sscanf(duration_str.c_str(), "%dh", &h);
    if (m_pos != std::string::npos) {
        if (h_pos != std::string::npos)
            sscanf(duration_str.c_str() + h_pos + 1, "%dm", &m);
        else
            sscanf(duration_str.c_str(), "%dm", &m);
    }
    if (s_pos != std::string::npos) {
        if (m_pos != std::string::npos)
            sscanf(duration_str.c_str() + m_pos + 1, "%ds", &s);
        else if (h_pos != std::string::npos)
            sscanf(duration_str.c_str() + h_pos + 1, "%ds", &s);
        else
            sscanf(duration_str.c_str(), "%ds", &s);
    }
    hours = h;
    minutes = m;
    seconds = s;
}
void print_readable_time(const std::string& label, struct tm* timeinfo) {
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y at %I:%M:%S %p", timeinfo);
    std::cout << label << ": " << buffer << std::endl;
}
int main() {
    std::string input;
    while (true) {
        std::cout << "\nenter duration (e.g. 1h30m15s) or 'exit' to quit: ";
        std::getline(std::cin, input);
        if (input == "exit") {
            std::cout << "bai bai1!!\n";
            break;
        }
        int hours, minutes, seconds;
        parse_duration(input, hours, minutes, seconds);
        time_t now = time(NULL);
        struct tm now_tm = *localtime(&now);
        print_readable_time("current time", &now_tm);
        time_t future_time = now + (hours * 3600) + (minutes * 60) + seconds;
        struct tm future_tm = *localtime(&future_time);
        print_readable_time("time after duration", &future_tm);
    }
    return 0;
}
