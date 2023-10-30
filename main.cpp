#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

int main() {
    // Leitura do arquivo config.cfg
    std::ifstream configFile("conf.d/config.cfg");
    if (!configFile.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo de configuração 'config.cfg'" << std::endl;
        return 1;
    }

    // Lê as configurações do arquivo
    std::string screenResolution, videoStreamLink, videoPort;
    if (configFile >> screenResolution >> videoStreamLink >> videoPort) {
        // Constrói o comando para chamar o VLC com as configurações
        std::stringstream command;
        command << "vlc -I dummy " << videoStreamLink << " --screen-fps=30 --screen-width=" << screenResolution << " --screen-height=" << screenResolution << " --sout '#transcode{vcodec=h264,vb=800,scale=1,acodec=mp3,ab=128,channels=2}:std{access=udp,mux=ts,dst=:" << videoPort << "}'";

        // Executa o comando para iniciar o stream
        int result = system(command.str().c_str());
        if (result != 0) {
            std::cerr << "Erro ao executar o VLC" << std::endl;
            return 1;
        }

        // Encerra a execução após o streaming
        return 0;
    } else {
        std::cerr << "Erro: O arquivo de configuração está incompleto" << std::endl;
        return 1;
    }
}
